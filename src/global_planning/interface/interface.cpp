/**
 * Created Time: 2024.07.10
 * File name:    interface.cpp
 * Author:      Yanyifeng(yanyifeng@wicri.org)
 * Brief:        规划库编译为动态库后，对外的接口函数  GetMap 、 GlobalPlanning
 * Include:      Class: GlobalVariable 单例类，相当于整个系统的全局变量
 * Copyright:    2024 WICRI
 */

#include "interface.h"

#include "../planning.h"
using namespace rapidjson;
// 静态成员初始化
GlobalVariable* GlobalVariable::instance = nullptr;
// std::mutex GlobalVariable::mtx;

bool GetMap(char* parea) {
    cout << "GlobalPathPlanning-IDS_Global_Planning_version: G_V1.0.1.20240702_RC" << endl;
    cout << "规划库版本号:G_V1.0.1.20240702_RC" << endl;
    rapidjson::Document doc;
    doc.Parse(parea);
    if (doc.HasParseError()) {
        doc.GetParseError();
        doc.GetErrorOffset();
    }
    doc.GetAllocator();

    // 清空全局变量
    GlobalVariable::getInstance()->map_border_.clear();
    GlobalVariable::getInstance()->all_referencelines_.clear();
    GlobalVariable::getInstance()->referenceline_relation_.clear();
    GlobalVariable::getInstance()->referenceline_graph_.clear();
    GlobalVariable::getInstance()->sequence_mapping_.clear();

    // 解析border_points
    const Value& borderPointsArray = doc["external_border"]["border_points"];
    for (SizeType i = 0; i < borderPointsArray.Size(); i++) {
        _BorderPoint bp;
        bp.x    = borderPointsArray[i]["x"].GetDouble();
        bp.y    = borderPointsArray[i]["y"].GetDouble();
        bp.z    = borderPointsArray[i]["z"].GetDouble();
        bp.type = static_cast<unsigned char>(borderPointsArray[i]["type"].GetInt());
        GlobalVariable::getInstance()->map_border_.push_back(bp);
    }

    // 解析reference_trajs
    const Value& trajsArray = doc["reference_trajs"];
    for (SizeType i = 0; i < trajsArray.Size(); i++) {
        _SingleTraj traj;
        traj.id                      = trajsArray[i]["id"].GetInt();
        const Value& trajPointsArray = trajsArray[i]["trajectory"];
        for (SizeType j = 0; j < trajPointsArray.Size(); j++) {
            _TrajectoryPoint tp;
            tp.x         = trajPointsArray[j]["x"].GetDouble();
            tp.y         = trajPointsArray[j]["y"].GetDouble();
            tp.z         = trajPointsArray[j]["z"].GetDouble();
            tp.yaw       = trajPointsArray[j]["yaw"].GetDouble();
            tp.curvature = trajPointsArray[j]["curvature"].GetDouble();
            tp.attribute = static_cast<unsigned char>(trajPointsArray[j]["attribute"].GetInt());
            tp.direction = static_cast<unsigned char>(trajPointsArray[j]["direction"].GetInt());
            traj.trajectory.push_back(tp);
        }
        GlobalVariable::getInstance()->all_referencelines_.push_back(traj);
    }

    // 解析relation
    const Value& relationObj = doc["relation"];
    for (Value::ConstMemberIterator itr = relationObj.MemberBegin(); itr != relationObj.MemberEnd(); ++itr) {
        int          key      = stoi(itr->name.GetString());
        const Value& relArray = itr->value;
        vector<int>  relVec;
        for (SizeType k = 0; k < relArray.Size(); k++) {
            relVec.push_back(relArray[k].GetInt());
        }
        GlobalVariable::getInstance()->referenceline_relation_[key] = relVec;
    }
    // 调用GlobalVariable类内部的CreateDirectedGraph来生成referenceline_graph_
    if (!GlobalVariable::getInstance()->CreateDirectedGraph(GlobalVariable::getInstance()->referenceline_relation_)) {
        return false;
    }

    return true;
}
char* GlobalPathPlanning(char* point_veh_start_end) {
    cout << "**********************欢迎光临后台全局规划库************************************" << endl;
    cout << "规划库版本号:G_V1.0.1.20240702_RC" << endl;
    time_t start_time, end_time;
    time(&start_time);
    Planning                      planning;
    std::vector<_TrajectoryPoint> path;
    // 解析传入的参数
    cout << "point_veh_start_end.size()  " << strlen(point_veh_start_end) << endl;
    _TarStartEnd veh_start_end;
    {
        std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->parse_func_write_lock);
        veh_start_end = planning.ParseInputInfo(point_veh_start_end);
        planning.key_ = veh_start_end.my_key;
    }

    std::string vehicle_code = std::to_string(veh_start_end.veh_param.vehicle_code);

    planning.vehicle_code_        = vehicle_code;
    auto              currentTime = std::chrono::system_clock::now();
    std::time_t       timestamp   = std::chrono::system_clock::to_time_t(currentTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timestamp), "%Y-%m-%doc-%H-%M-%S");
    std::string timeStr = ss.str();

    {
        std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->record_file_write_lock);
        std::ofstream                       record;
        record.open("record.txt", std::ios_base::app);
        record << timeStr << " ，收到规划请求，请求号：" << veh_start_end.my_key << "，车辆编号：" << vehicle_code
               << endl;
        record.close();
    }

    // 创建 log 目录
    std::string dirPath = "log/" + vehicle_code;
    filesystem::create_directories(dirPath);
    // 构造文件路径
    std::string        filePath = dirPath + "/log_" + timeStr + ".txt";
    std::ostringstream oss;
    GlobalVariable::getInstance()->dispatch_nums++;
    oss << GlobalVariable::getInstance()->dispatch_nums;
    vehicle_code += oss.str();
    try {
        cout << "begin creating rotating_logger_mt" << endl;
        planning.threadLogger_ = spdlog::rotating_logger_mt(vehicle_code, filePath, 10 * 2048 * 2048, 5, true);
        planning.threadLogger_->flush_on(spdlog::level::info);
        // planning.my_optimal_path_.threadLogger_ = planning.threadLogger_;
        planning.threadLogger_->info(vehicle_code);
        planning.threadLogger_->info("point_veh_start_end.strlen().size:{}", strlen(point_veh_start_end));
        planning.threadLogger_->info("veh_start_end.my_key:{}", veh_start_end.my_key);
        planning.threadLogger_->info("GlobalPathPlanning-IDS_Global_Planning_version: G_V1.0.1.20240702_RC");
        cout << "成功创建日志对象" << endl;
    } catch (const std::exception& e) {
        cout << "异常赋值" << endl;

        planning.error_type_ = static_cast<uint>(ErrorType::ALGORITHM_ERROR);
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);

            string temp_string                         = planning.VecWaypoint2json(path);
            int    temp_string_size                    = temp_string.size();
            GlobalVariable::getInstance()->receive_ptr = (char*)GlobalVariable::getInstance()->global_str.data();
            cout << "GlobalVariable::getInstance()->receive_ptr.strlen().size():"
                 << strlen(GlobalVariable::getInstance()->receive_ptr) << endl;
            return GlobalVariable::getInstance()->receive_ptr;
        }
    }

    {
        std::shared_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->assignment_operation_lock);
        planning.threadLogger_->info("地图路网规模:{}", GlobalVariable::getInstance()->referenceline_graph_.size());
        if (GlobalVariable::getInstance()->referenceline_graph_.size() == 0) {
            planning.error_type_ = static_cast<uint>(ErrorType::NO_MAP);
            {
                std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
                planning.threadLogger_->info("进锁成功");
                string temp_string      = planning.VecWaypoint2json(path);
                int    temp_string_size = temp_string.size();

                GlobalVariable::getInstance()->receive_ptr = (char*)GlobalVariable::getInstance()->global_str.data();
                if (temp_string_size < 10) {
                    cout << "temp_string还没接就被释放了" << endl;
                    planning.threadLogger_->info("出锁成功");
                }
                planning.threadLogger_->info("VecWaypoint2json successfully");
                cout << "GlobalVariable::getInstance()->receive_ptr.strlen().size():"
                     << strlen(GlobalVariable::getInstance()->receive_ptr) << endl;
                planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}",
                                             strlen(GlobalVariable::getInstance()->receive_ptr));
                planning.threadLogger_->info("出锁成功");
                return GlobalVariable::getInstance()->receive_ptr;
            }
        }

        // 给planning对象的有向图、地图边界、路段进行赋值
        planning.road_directed_graph_ = GlobalVariable::getInstance()->referenceline_graph_;
        planning.map_border_          = GlobalVariable::getInstance()->map_border_;
        planning.all_referencelines_  = GlobalVariable::getInstance()->all_referencelines_;
    } // 获取传入的内边界并将其存入对应的r区域内

    if (!veh_start_end.inner_borders.empty()) {
        cout << "入参传入" << veh_start_end.inner_borders.size() << "组内边界" << endl;
        try {
            planning.inner_borders_ = veh_start_end.inner_borders;
        } catch (const std::exception& e) {
            cout << "异常赋值" << endl;
            // planning.threadLogger_->info("temp_zone_id:{}-------all_zones_.size():{}", temp_zone_id,
            // planning.all_zones_.size());
            planning.error_type_ = static_cast<uint>(ErrorType::ALGORITHM_ERROR);
            {
                std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
                planning.threadLogger_->info("进锁成功");
                string temp_string      = planning.VecWaypoint2json(path);
                int    temp_string_size = temp_string.size();

                GlobalVariable::getInstance()->receive_ptr = (char*)GlobalVariable::getInstance()->global_str.data();
                if (temp_string_size < 10) {
                    cout << "temp_string还没接就被释放了" << endl;
                    planning.threadLogger_->info("出锁成功");
                }
                planning.threadLogger_->info("VecWaypoint2json successfully");
                cout << "GlobalVariable::getInstance()->receive_ptr.strlen().size():"
                     << strlen(GlobalVariable::getInstance()->receive_ptr) << endl;
                planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}",
                                             strlen(GlobalVariable::getInstance()->receive_ptr));
                planning.threadLogger_->info("出锁成功");
                return GlobalVariable::getInstance()->receive_ptr;
            }
        }
    }
    else {
        planning.threadLogger_->error("此次任务无inner_borders信息");
    }
    planning.task_type_     = veh_start_end.task_type;
    planning.vehicle_param_ = veh_start_end.veh_param;
    planning.threadLogger_->info("start_point.x ={}", veh_start_end.start_point.x);
    planning.threadLogger_->info("start_point.y ={}", veh_start_end.start_point.y);
    planning.threadLogger_->info("start_point.z ={}", veh_start_end.start_point.z);
    planning.threadLogger_->info("start_point.yaw ={}", veh_start_end.start_point.yaw);
    planning.threadLogger_->info("end_point.x ={}", veh_start_end.end_point.x);
    planning.threadLogger_->info("end_point.y ={}", veh_start_end.end_point.y);
    planning.threadLogger_->info("end_point.z ={}", veh_start_end.end_point.z);
    planning.threadLogger_->info("end_point.yaw ={}", veh_start_end.end_point.yaw);
    // 起点
    planning.start_point_ = veh_start_end.start_point;
    // 终点
    planning.end_point_ = veh_start_end.end_point;
    // spdlog::shutdown();
    try {
        planning.GlobalPathPlanningIntface(path);
    } catch (const std::exception& e) {
        cout << "调用全局规划库内部出现异常" << endl;
        planning.threadLogger_->info("调用全局规划库内部出现异常");
        planning.error_type_ = static_cast<uint>(ErrorType::ALGORITHM_ERROR);
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            planning.threadLogger_->info("进锁成功");
            string temp_string      = planning.VecWaypoint2json(path);
            int    temp_string_size = temp_string.size();

            GlobalVariable::getInstance()->receive_ptr = (char*)GlobalVariable::getInstance()->global_str.data();
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
                planning.threadLogger_->info("出锁成功");
            }
            planning.threadLogger_->info("VecWaypoint2json successfully");
            cout << "GlobalVariable::getInstance()->receive_ptr.strlen().size():"
                 << strlen(GlobalVariable::getInstance()->receive_ptr) << endl;
            planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}",
                                         strlen(GlobalVariable::getInstance()->receive_ptr));
            planning.threadLogger_->info("出锁成功");
            return GlobalVariable::getInstance()->receive_ptr;
        }
    } catch (const std::out_of_range& e) {
        // 处理数组越界异常
        cout << "调用全局规划库内部出现异常" << endl;
        planning.threadLogger_->info("调用全局规划库内部出现异常");
        planning.error_type_ = static_cast<uint>(ErrorType::ALGORITHM_ERROR);
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            planning.threadLogger_->info("进锁成功");
            string temp_string                         = planning.VecWaypoint2json(path);
            GlobalVariable::getInstance()->receive_ptr = (char*)temp_string.data();
            planning.threadLogger_->info("VecWaypoint2json successfully");
            cout << "GlobalVariable::getInstance()->receive_ptr.strlen().size():"
                 << strlen(GlobalVariable::getInstance()->receive_ptr) << endl;

            planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}",
                                         strlen(GlobalVariable::getInstance()->receive_ptr));
            planning.threadLogger_->info("出锁成功");
            return GlobalVariable::getInstance()->receive_ptr;
        }
    }

    try {
        cout << "最后一步，返回字符指针" << endl;
        planning.threadLogger_->info("最后一步，返回字符指针");

        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            planning.threadLogger_->info("进锁成功");
            string temp_string      = planning.VecWaypoint2json(path);
            int    temp_string_size = temp_string.size();

            GlobalVariable::getInstance()->receive_ptr = (char*)GlobalVariable::getInstance()->global_str.data();
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
                planning.threadLogger_->info("出锁成功");
            }
            planning.threadLogger_->info("VecWaypoint2json successfully");
            cout << "GlobalVariable::getInstance()->receive_ptr.strlen().size():"
                 << strlen(GlobalVariable::getInstance()->receive_ptr) << endl;
            planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}",
                                         strlen(GlobalVariable::getInstance()->receive_ptr));
            planning.threadLogger_->info("出锁成功");
            return GlobalVariable::getInstance()->receive_ptr;
        }
    } catch (const std::exception& e) {
        cout << "全局轨迹规划库内部，返参出现异常" << endl;
        planning.threadLogger_->info("全局轨迹规划库内部，返参出现异常");
        planning.error_type_ = static_cast<uint>(ErrorType::ALGORITHM_ERROR);
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            planning.threadLogger_->info("进锁成功");
            string temp_string      = planning.VecWaypoint2json(path);
            int    temp_string_size = temp_string.size();

            GlobalVariable::getInstance()->receive_ptr = (char*)GlobalVariable::getInstance()->global_str.data();
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
                planning.threadLogger_->info("出锁成功");
            }
            planning.threadLogger_->info("VecWaypoint2json successfully");
            cout << "GlobalVariable::getInstance()->receive_ptr.strlen().size():"
                 << strlen(GlobalVariable::getInstance()->receive_ptr) << endl;
            planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}",
                                         strlen(GlobalVariable::getInstance()->receive_ptr));
            planning.threadLogger_->info("出锁成功");
            return GlobalVariable::getInstance()->receive_ptr;
        }
    } catch (const std::out_of_range& e) {
        // 处理数组越界异常
        cout << "全局轨迹规划库内部，返参出现异常" << endl;
        planning.threadLogger_->info("全局轨迹规划库内部，返参出现异常");
        planning.error_type_ = static_cast<uint>(ErrorType::ALGORITHM_ERROR);
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            planning.threadLogger_->info("进锁成功");
            string temp_string      = planning.VecWaypoint2json(path);
            int    temp_string_size = temp_string.size();

            GlobalVariable::getInstance()->receive_ptr = (char*)GlobalVariable::getInstance()->global_str.data();
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
                planning.threadLogger_->info("出锁成功");
            }
            planning.threadLogger_->info("VecWaypoint2json successfully");
            cout << "GlobalVariable::getInstance()->receive_ptr.strlen().size():"
                 << strlen(GlobalVariable::getInstance()->receive_ptr) << endl;
            planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}",
                                         strlen(GlobalVariable::getInstance()->receive_ptr));
            planning.threadLogger_->info("出锁成功");
            return GlobalVariable::getInstance()->receive_ptr;
        }
    }
}
bool GlobalVariable::CreateDirectedGraph(map<int, vector<int>>& referenceline_relation_) {
    // 遍历referenceline_relation_，将所有的key存入sequence_mapping_中
    int total_size = 0;
    for (const auto& pair : referenceline_relation_) {
        sequence_mapping_.at(total_size++) = pair.first;
    }
    // 预设二维权重矩阵referenceline_graph_空间，并先统统设置为0
    referenceline_graph_.resize(total_size);
    for (auto& row : referenceline_graph_) {
        row.resize(total_size, 0);
    }
    // 遍历referenceline_relation_，结合映射序列来给referenceline_graph_赋值

    int row_index = 0, col_index = 0;
    for (const auto& pair : referenceline_relation_) {
        for (int num : pair.second) {
            // 给referenceline_graph_中的每个位置赋值，col_index要根据piar.second()中的内容，结合sequence_mapping_进行反映射
            col_index = BinarySearch(sequence_mapping_, num);
            if (col_index != -1) {
                referenceline_graph_.at(row_index).at(col_index) = 1;
            }
        }
    }
}
int GlobalVariable::BinarySearch(vector<int>& input_vec, int target) {
    int left = 0, right = 0, mid = 0, size = 0;
    size  = input_vec.size();
    right = size - 1;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (input_vec.at(mid) < target) {
            right = mid - 1;
        }
        else if (input_vec.at(mid) > target) {
            left = mid + 1;
        }
        else
            return mid;
    }
    return -1;
}
