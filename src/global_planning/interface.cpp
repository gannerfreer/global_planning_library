/**
 * Created Time: 2024.07.10
 * File name:    interface.cpp
 * Author:      yanyifeng(yanyifeng@wicri.org)
 * Brief:        规划库编译为动态库后，对外的接口函数  GetMap 、 GlobalPlanning
 * Include:      Class: GlobalVariable 单例类，相当于整个系统的全局变量
 * Copyright:    2024 WICRI
 */

#include "interface.h"

#include "mine_global_planning/planning.h"


bool GetMap(char* parea) {
    cout << "GlobalPathPlanning-IDS_Global_Planning_version: G_V1.0.1.20240903_RC" << endl;
    cout << "规划库版本号:G_V1.0.1.20240903_RC" << endl;
    auto              currentTime = std::chrono::system_clock::now();
    std::time_t       timestamp   = std::chrono::system_clock::to_time_t(currentTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
    std::string   timeStr = ss.str();
    std::ofstream record;
    record.open("GetMap_record.txt", std::ios_base::app);
    record << timeStr << " ，收到更新地图请求" << endl;
    record.close();
    if (GlobalPlanning::Parser::GetMap(parea)) {
        record.open("GlobalPlanning_record.txt", std::ios_base::app);
        record << timeStr << " 地图更新成功" << endl;
        record.close();
        return true;
    }
    else {
        record.open("GlobalPlanning_record.txt", std::ios_base::app);
        record << timeStr << " 地图更新失败" << endl;
        record.close();
        return false;
    }
}
char* GlobalPathPlanning(char* point_veh_start_end) {
    cout << "**********************欢迎光临后台全局规划库************************************" << endl;
    cout << "规划库版本号:G_V1.0.1.20240903_RC" << endl;
    time_t start_time, end_time;
    time(&start_time);
    Planning                      planning;
    std::vector<_TrajectoryPoint> path;
    // 解析传入的参数
    cout << "point_veh_start_end.size()  " << strlen(point_veh_start_end) << endl;
    _TarStartEnd veh_start_end;
    {
        std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->parse_func_write_lock);
        veh_start_end = GlobalPlanning::Parser::ParseJson(point_veh_start_end);
        planning.key_ = veh_start_end.my_key;
    }

    std::string vehicle_code = std::to_string(veh_start_end.veh_param.vehicle_code);

    planning.vehicle_code_        = vehicle_code;
    auto              currentTime = std::chrono::system_clock::now();
    std::time_t       timestamp   = std::chrono::system_clock::to_time_t(currentTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
    std::string timeStr = ss.str();

    {
        std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->record_file_write_lock);
        std::ofstream                       record;
        record.open("GlobalPlanning_record.txt", std::ios_base::app);
        record << timeStr << " ，收到规划请求，请求号：" << veh_start_end.my_key << "，车辆编号：" << vehicle_code << endl;
        record.close();
    }

    // 创建 log 目录
    std::string dirPath = "log/" + vehicle_code;
    filesystem::create_directories(dirPath);
    // 构造文件路径
    std::string        filePath = dirPath + "/log_" + timeStr + ".txt";
    std::ostringstream oss;
    int                num = GlobalVariable::getInstance()->GetDispatchNums();
    GlobalVariable::getInstance()->SetDispatchNums(num++);
    oss << GlobalVariable::getInstance()->GetDispatchNums();
    vehicle_code += oss.str();


    planning.threadLogger_ = spdlog::rotating_logger_mt(vehicle_code, filePath, 10 * 2048 * 2048, 5, true);
    planning.threadLogger_->flush_on(spdlog::level::info);
    // planning.my_optimal_path_.threadLogger_ = planning.threadLogger_;
    planning.threadLogger_->info(vehicle_code);
    planning.threadLogger_->info("point_veh_start_end.strlen().size:{}", strlen(point_veh_start_end));
    planning.threadLogger_->info("veh_start_end.my_key:{}", veh_start_end.my_key);
    planning.threadLogger_->info("GlobalPathPlanning-IDS_Global_Planning_version: G_V1.0.1.20240903_RC");


    {
        std::shared_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->assignment_operation_lock);
        planning.threadLogger_->info("地图路网规模:{}", GlobalVariable::getInstance()->GetAllReferencelines().size());
        if (GlobalVariable::getInstance()->GetReferencelineGraph().size() == 0) {
            planning.error_type_ = ErrorType::NO_MAP;
            {
                std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
                planning.threadLogger_->info("进锁成功");
                string temp_string      = GlobalPlanning::Parser::VecWaypoint2json(path, planning);
                int    temp_string_size = temp_string.size();

                GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
                if (temp_string_size < 10) {
                    cout << "temp_string还没接就被释放了" << endl;
                    planning.threadLogger_->info("出锁成功");
                }
                planning.threadLogger_->info("VecWaypoint2json successfully");

                planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
                planning.threadLogger_->info("出锁成功");
                return GlobalVariable::getInstance()->GetReceivePtr();
            }
        }

        // 给planning对象的有向图、地图边界、路段进行赋值
        planning.road_directed_graph_ = GlobalVariable::getInstance()->GetReferencelineGraph();
        planning.map_border_          = GlobalVariable::getInstance()->GetMapBorder();
        planning.all_referencelines_  = GlobalVariable::getInstance()->GetAllReferencelines();
        planning.sequence_mapping_    = GlobalVariable::getInstance()->GetSequenceMapping();
        planning.threadLogger_->info("road_directed_graph_:{}", planning.road_directed_graph_.size());
        planning.threadLogger_->info("map_border_:{}", planning.map_border_.size());
        planning.threadLogger_->info("all_referencelines_:{}", planning.all_referencelines_.size());
        planning.threadLogger_->info("sequence_mapping_:{}", planning.sequence_mapping_.size());

    } // 获取传入的内边界并将其存入对应的r区域内

    if (!veh_start_end.inner_borders.empty()) {
        cout << "入参传入" << veh_start_end.inner_borders.size() << "组内边界" << endl;
        try {
            planning.inner_borders_ = veh_start_end.inner_borders;
        } catch (const std::exception& e) {
            cout << "异常赋值" << endl;
            // planning.threadLogger_->info("temp_zone_id:{}-------all_zones_.size():{}", temp_zone_id,
            // planning.all_zones_.size());
            planning.error_type_ = ErrorType::ALGORITHM_ERROR;
            {
                std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
                planning.threadLogger_->info("进锁成功");
                string temp_string      = GlobalPlanning::Parser::VecWaypoint2json(path, planning);
                int    temp_string_size = temp_string.size();

                GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
                if (temp_string_size < 10) {
                    cout << "temp_string还没接就被释放了" << endl;
                    planning.threadLogger_->info("出锁成功");
                }
                planning.threadLogger_->info("VecWaypoint2json successfully");

                planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
                planning.threadLogger_->info("出锁成功");
                return GlobalVariable::getInstance()->GetReceivePtr();
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
        planning.error_type_ = ErrorType::ALGORITHM_ERROR;
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            planning.threadLogger_->info("进锁成功");
            string temp_string      = GlobalPlanning::Parser::VecWaypoint2json(path, planning);
            int    temp_string_size = temp_string.size();

            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
                planning.threadLogger_->info("出锁成功");
            }
            planning.threadLogger_->info("VecWaypoint2json successfully");

            planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
            planning.threadLogger_->info("出锁成功");
            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    } catch (const std::out_of_range& e) {
        // 处理数组越界异常
        cout << "调用全局规划库内部出现异常" << endl;
        planning.threadLogger_->info("调用全局规划库内部出现异常");
        planning.error_type_ = ErrorType::ALGORITHM_ERROR;
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            planning.threadLogger_->info("进锁成功");
            string temp_string      = GlobalPlanning::Parser::VecWaypoint2json(path, planning);
            int    temp_string_size = temp_string.size();

            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
                planning.threadLogger_->info("出锁成功");
            }
            planning.threadLogger_->info("VecWaypoint2json successfully");

            planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
            planning.threadLogger_->info("出锁成功");
            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    }

    try {
        cout << "最后一步，返回字符指针" << endl;
        planning.threadLogger_->info("最后一步，返回字符指针");

        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            planning.threadLogger_->info("进锁成功");
            string temp_string      = GlobalPlanning::Parser::VecWaypoint2json(path, planning);
            int    temp_string_size = temp_string.size();

            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
                planning.threadLogger_->info("出锁成功");
            }
            planning.threadLogger_->info("VecWaypoint2json successfully");

            planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
            planning.threadLogger_->info("出锁成功");
            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    } catch (const std::exception& e) {
        cout << "全局轨迹规划库内部，返参出现异常" << endl;
        planning.threadLogger_->info("全局轨迹规划库内部，返参出现异常");
        planning.error_type_ = ErrorType::ALGORITHM_ERROR;
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            planning.threadLogger_->info("进锁成功");
            string temp_string      = GlobalPlanning::Parser::VecWaypoint2json(path, planning);
            int    temp_string_size = temp_string.size();

            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
                planning.threadLogger_->info("出锁成功");
            }
            planning.threadLogger_->info("VecWaypoint2json successfully");

            planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
            planning.threadLogger_->info("出锁成功");
            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    } catch (const std::out_of_range& e) {
        // 处理数组越界异常
        cout << "全局轨迹规划库内部，返参出现异常" << endl;
        planning.threadLogger_->info("全局轨迹规划库内部，返参出现异常");
        planning.error_type_ = ErrorType::ALGORITHM_ERROR;
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            planning.threadLogger_->info("进锁成功");
            string temp_string      = GlobalPlanning::Parser::VecWaypoint2json(path, planning);
            int    temp_string_size = temp_string.size();

            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
                planning.threadLogger_->info("出锁成功");
            }
            planning.threadLogger_->info("VecWaypoint2json successfully");

            planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
            planning.threadLogger_->info("出锁成功");
            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    }
}
