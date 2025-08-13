/**
 * Created Time: 2024.07.10
 * File name:    interface.cpp
 * Author:      yanyifeng(yanyifeng@wicri.org)
 * Brief:        规划库编译为动态库后，对外的接口函数  GetMap 、 GlobalPlanning
 * Include:      Class: GlobalVariable 单例类，相当于整个系统的全局变量
 * Copyright:    2024 WICRI
 */

#include "interface.h"

#include "common/common_struct.h"
#include "globalvariable.h"
#include "load_area_planning/load_area_planning.h"
#include "mine_global_planning/planning.h"
#include "mine_global_planning/predicting.h"


bool GetMap(char* parea) {
    {
        std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->parse_func_write_lock);
        cout << "GlobalPathPlanning-IDS_Global_Planning_version: G_V1.4.0.20250310_beta" << endl;
        cout << "规划库版本号:G_V1.4.0.20250310_beta" << endl;
        auto              currentTime = std::chrono::system_clock::now();
        std::time_t       timestamp   = std::chrono::system_clock::to_time_t(currentTime);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
        std::string   timeStr = ss.str();
        std::ofstream record;
        std::string   folderPath = "record_file";
        std::string   filePath   = folderPath + "/GetMap_record.txt";
        if (!fs::exists(folderPath)) {
            try {
                fs::create_directory(folderPath);
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error creating directory: " << e.what() << std::endl;
            }
        }
        record.open(filePath, ios_base::app);
        // record.open("/record_file/GetMap_record.txt", std::ios_base::app);
        record << timeStr << " ，收到更新地图请求" << endl;
        record.close();
        if (GlobalPlanning::Parser::GetMap(parea)) {
            record.open(filePath, ios_base::app);
            ss.str("");
            ss << std::put_time(std::localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
            timeStr = ss.str();
            record << timeStr << "， 地图更新成功***************************G_V1.4.0.20250310_beta" << endl;
            record.close();
            return true;
        }
        else {
            record.open(filePath, ios_base::app);
            ss.str("");
            ss << std::put_time(std::localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
            timeStr = ss.str();
            record << timeStr << " ，地图更新失败***************************G_V1.4.0.20250310_beta" << endl;
            record.close();
            return false;
        }
    }
}
char* GlobalPathPlanning(char* point_veh_start_end) {
    auto              currentTime = std::chrono::system_clock::now();
    std::time_t       timestamp   = std::chrono::system_clock::to_time_t(currentTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
    std::string timeStr = ss.str();
    cout << "**********************欢迎光临后台全局规划库,版本号:G_V1.4.0.20250310_beta************************************" << timeStr << endl;
    time_t start_time, end_time;
    time(&start_time);
    Planning                      planning;
    std::vector<_TrajectoryPoint> path;
    // 解析传入的参数
    cout << "本次入參大小： " << strlen(point_veh_start_end) << "strlen()计算方式" << endl;
    _TarStartEnd veh_start_end;
    try {
        std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->parse_func_write_lock); // 这里之所以加解析锁，是因为之前采用jna方案时，测试多线程调用时，出现解析混乱情况
        veh_start_end = GlobalPlanning::Parser::ParseGlobalPlanningJson(point_veh_start_end);
        planning.key_ = veh_start_end.my_key;
    } catch (...) {
        // 捕获所有类型的异常
        std::cerr << "捕获到一个异常" << std::endl;
    }
    std::string vehicle_code = std::to_string(veh_start_end.veh_param.vehicle_code);
    planning.vehicle_code_   = vehicle_code;
    {
        std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->record_file_write_lock);
        std::ofstream                       record;
        std::string                         folderPath = "record_file";
        std::string                         filePath   = folderPath + "/GlobalPlanning_record.txt";
        if (!fs::exists(folderPath)) {
            try {
                fs::create_directory(folderPath);
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error creating directory: " << e.what() << std::endl;
            }
        }
        record.open(filePath, std::ios_base::app);
        record << timeStr << " ，收到规划请求，请求号：" << veh_start_end.my_key << "，车辆编号：" << vehicle_code << "    规划库版本号:G_V1.4.0.20250310_beta" << endl;
        record.close();
    }
    cout << "收到规划请求，请求号:" << veh_start_end.my_key << endl;

    // 创建 log 目录
    std::string dirPath = "log/" + vehicle_code;
    filesystem::create_directories(dirPath);
    // 构造文件路径
    std::string        filePath = dirPath + "/log_" + timeStr + ".log";
    std::ostringstream oss;
    int                num = GlobalVariable::getInstance()->GetDispatchNums();
    GlobalVariable::getInstance()->SetDispatchNums(num++);
    oss << GlobalVariable::getInstance()->GetDispatchNums();
    vehicle_code += oss.str();


    planning.threadLogger_ = spdlog::rotating_logger_mt(vehicle_code, filePath, 10 * 2048 * 2048, 5, true);
    planning.threadLogger_->flush_on(spdlog::level::info);
    planning.threadLogger_->info(vehicle_code);
    planning.threadLogger_->info("point_veh_start_end.strlen().size:{}", strlen(point_veh_start_end));
    planning.threadLogger_->info("veh_start_end.my_key:{}", veh_start_end.my_key);
    planning.threadLogger_->info("GlobalPathPlanning-IDS_Global_Planning_version: G_V1.4.0.20250310_beta");

    {
        std::shared_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->assignment_operation_lock);
        planning.threadLogger_->info("地图路网规模:{}", GlobalVariable::getInstance()->GetAllSelfDrivingReferencelines().size());
        if (GlobalVariable::getInstance()->GetAllSelfDrivingReferencelines().size() == 0) {
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
        planning.road_directed_graph_ = GlobalVariable::getInstance()->GetSelfDrivingReferencelineGraph();
        planning.map_border_          = GlobalVariable::getInstance()->GetMapBorder();
        planning.all_referencelines_  = GlobalVariable::getInstance()->GetAllSelfDrivingReferencelines();
        planning.sequence_mapping_    = GlobalVariable::getInstance()->GetSelfDrivingSequenceMapping();
        planning.threadLogger_->info("road_directed_graph_:{}", planning.road_directed_graph_.size());
        planning.threadLogger_->info("map_border_:{}", planning.map_border_.size());
        planning.threadLogger_->info("all_referencelines_:{}", planning.all_referencelines_.size());
        planning.threadLogger_->info("sequence_mapping_:{}", planning.sequence_mapping_.size());

    } // 获取传入的内边界并将其存入对应的r区域内

    if (!veh_start_end.machine_borders.empty()) {
        cout << "入参传入" << veh_start_end.machine_borders.size() << "组挖机边界" << endl;
        try {
            planning.machine_borders_ = veh_start_end.machine_borders;
        } catch (const std::exception& e) {
            cout << "规划库入参数解析，将内边界赋值给planning对象的成员变量时出现异常" << endl;
            planning.error_type_ = ErrorType::ALGORITHM_ERROR_PARAS_PARSE_FAIL;
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

    if (!veh_start_end.wall_borders.empty()) {
        cout << "入参传入" << veh_start_end.wall_borders.size() << "组挡墙边界" << endl;
        try {
            planning.wall_borders_ = veh_start_end.wall_borders;
        } catch (const std::exception& e) {
            cout << "规划库入参数解析，将内边界赋值给planning对象的成员变量时出现异常" << endl;
            planning.error_type_ = ErrorType::ALGORITHM_ERROR_PARAS_PARSE_FAIL;
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
        planning.threadLogger_->error("此次任务无dynamic_border信息");
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
    planning.end_point_       = veh_start_end.end_point;
    planning.reference_paths_ = veh_start_end.reference_paths;
    planning.threadLogger_->info("第三通道 reference_paths_:{}", planning.reference_paths_.size());
    try {
        planning.GlobalPathPlanningInterface(path);
    } catch (const std::exception& e) {
        cout << "规划库执行GlobalPathPlanningIntface时出现 exception 抛出" << endl;
        planning.threadLogger_->info("规划库执行GlobalPathPlanningIntface时出现 exception 抛出");
        planning.error_type_ = ErrorType::ALGORITHM_ERROR_TRY_CATCH_ERROR;
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            planning.threadLogger_->info("进 return_write_lock 锁成功");
            cout << "进 return_write_lock 锁成功" << endl;
            string temp_string      = GlobalPlanning::Parser::VecWaypoint2json(path, planning);
            int    temp_string_size = temp_string.size();
            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
                planning.threadLogger_->info("temp_string还没接就被释放了");
            }
            planning.threadLogger_->info("VecWaypoint2json successfully");
            planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
            planning.threadLogger_->info("即将出  return_write_lock 锁");
            cout << "即将出  return_write_lock 锁" << endl;
            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    } catch (const std::out_of_range& e) {
        // 处理数组越界异常
        cout << "规划库执行GlobalPathPlanningIntface时出现 out_of_range 抛出" << endl;
        planning.threadLogger_->info("规划库执行GlobalPathPlanningIntface时出现 out_of_range 抛出");
        planning.error_type_ = ErrorType::ALGORITHM_ERROR_TRY_CATCH_ERROR;
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
        cout << "最后一步，将规划结果转为json格式字符串并返回" << endl;
        planning.threadLogger_->info("最后一步，返回字符指针");
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            planning.threadLogger_->info("进锁成功");
            string temp_string      = GlobalPlanning::Parser::VecWaypoint2json(path, planning);
            int    temp_string_size = temp_string.size();
            cout << "temp_string_size:" << temp_string_size << endl;
            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            cout << "执行完 GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data())" << endl;
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
                planning.threadLogger_->info("出锁成功");
            }
            cout << "返回轨迹" << endl;
            planning.threadLogger_->info("VecWaypoint2json successfully");
            planning.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
            planning.threadLogger_->info("出锁成功");
            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    } catch (const std::exception& e) {
        cout << "规划库执行 VecWaypoint2json 时出现 exception 抛出" << endl;
        planning.threadLogger_->info("规划库执行 VecWaypoint2json 时出现 exception 抛出");
        planning.error_type_ = ErrorType::ALGORITHM_ERROR_TRY_CATCH_ERROR;
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
        cout << "规划库执行 VecWaypoint2json 时出现 out_of_range 抛出" << endl;
        planning.threadLogger_->info("规划库执行 VecWaypoint2json 时出现 out_of_range 抛出");
        planning.error_type_ = ErrorType::ALGORITHM_ERROR_TRY_CATCH_ERROR;
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

char* PathPredicting(char* input_info) {
    auto              currentTime = std::chrono::system_clock::now();
    std::time_t       timestamp   = std::chrono::system_clock::to_time_t(currentTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
    std::string timeStr = ss.str();
    cout << "**********************欢迎光临有人车路径预测接口,版本号:P_V1.4.0.20250310_beta************************************" << timeStr << endl;
    time_t start_time, end_time;
    time(&start_time);
    Predicting                                                   predicting;
    std::map<string, std::vector<std::vector<_TrajectoryPoint>>> all_path;
    // 解析传入的参数
    cout << "本次入參大小： " << strlen(input_info) << "strlen()计算方式" << endl;
    _AllHumanVechicleInfos all_human_vechicle_infos;
    try {
        std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->parse_func_write_lock); // 这里之所以加解析锁，是因为之前采用jna方案时，测试多线程调用时，出现解析混乱情况
        all_human_vechicle_infos = GlobalPlanning::Parser::ParseHumanVehPredictingJson(input_info);
    } catch (...) {
        // 捕获所有类型的异常
        std::cerr << "捕获到一个异常" << std::endl;
    }

    {
        std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->record_file_write_lock);
        std::ofstream                       record;
        std::string                         folderPath = "record_file";
        std::string                         filePath   = folderPath + "/HumanVehPredicting_record.txt";
        if (!fs::exists(folderPath)) {
            try {
                fs::create_directory(folderPath);
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error creating directory: " << e.what() << std::endl;
            }
        }
        record.open(filePath, std::ios_base::app);
        record << timeStr << " ，收到预测请求，请求号：" << all_human_vechicle_infos.my_key << "    预测库版本号:G_V1.4.0.20250310_beta" << endl;
        record.close();
    }
    cout << "收到预测请求，请求号:" << all_human_vechicle_infos.my_key << endl;

    // 创建 log 目录
    std::string dirPath = "log/" + all_human_vechicle_infos.my_key;
    filesystem::create_directories(dirPath);
    // 构造文件路径
    std::string filePath = dirPath + "/log_" + timeStr + ".log";


    predicting.threadLogger_ = spdlog::rotating_logger_mt(all_human_vechicle_infos.my_key, filePath, 10 * 2048 * 2048, 5, true);
    predicting.threadLogger_->flush_on(spdlog::level::info);
    predicting.threadLogger_->info("input_info.strlen().size:{}", strlen(input_info));
    predicting.threadLogger_->info("all_human_vechicle_infos.my_key:{}", all_human_vechicle_infos.my_key);
    predicting.threadLogger_->info("HumanVehPredicting-IDS_version: P_V1.4.0.20250310_beta");

    {
        std::shared_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->assignment_operation_lock);
        predicting.threadLogger_->info("地图路网规模:{}", GlobalVariable::getInstance()->GetAllHumanDrivingReferencelines().size());
        if (GlobalVariable::getInstance()->GetAllHumanDrivingReferencelines().size() == 0) {
            predicting.error_type_ = ErrorType::NO_MAP;
            {
                std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
                predicting.threadLogger_->info("进锁成功");
                string temp_string      = GlobalPlanning::Parser::HumanVehFurtureVecWaypoint2json(all_path, predicting);
                int    temp_string_size = temp_string.size();
                GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
                if (temp_string_size < 10) {
                    cout << "temp_string还没接就被释放了" << endl;
                    predicting.threadLogger_->info("出锁成功");
                }
                predicting.threadLogger_->info("HumanVehFurtureVecWaypoint2json successfully");
                predicting.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
                predicting.threadLogger_->info("出锁成功");
                return GlobalVariable::getInstance()->GetReceivePtr();
            }
        }

        // 给predicting对象的有向图、地图边界、路段进行赋值
        predicting.all_referencelines_     = GlobalVariable::getInstance()->GetAllHumanDrivingReferencelines();
        predicting.referenceline_relation_ = GlobalVariable::getInstance()->GetHumanDrivingReferencelineRelation();
        predicting.threadLogger_->info("all_referencelines_:{}", predicting.all_referencelines_.size());

    } // 获取传入的内边界并将其存入对应的区域内

    _HumanVechicleInfo                         veh_info;
    std::vector<std::vector<_TrajectoryPoint>> path;
    for (int i = 0; i < all_human_vechicle_infos.human_vechicle_infos.size(); i++) {
        veh_info = all_human_vechicle_infos.human_vechicle_infos.at(i);
        predicting.threadLogger_->info("id:{} pos:({},{},{})", veh_info.id, veh_info.pos.x, veh_info.pos.y, veh_info.pos.yaw);
        // 起点
        predicting.start_point_ = veh_info.pos;
        try {
            predicting.PredictingInterface(path, all_human_vechicle_infos.predicting_distance);
            all_path[veh_info.id] = path;
        } catch (const std::exception& e) {
            cout << "预测库执行PredictingInterface时出现 exception 抛出" << endl;
            predicting.threadLogger_->info("预测库执行PredictingInterface时出现 exception 抛出");
            predicting.error_type_ = ErrorType::ALGORITHM_ERROR_TRY_CATCH_ERROR;
            {
                std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
                predicting.threadLogger_->info("进 return_write_lock 锁成功");
                cout << "进 return_write_lock 锁成功" << endl;
                string temp_string      = GlobalPlanning::Parser::HumanVehFurtureVecWaypoint2json(all_path, predicting);
                int    temp_string_size = temp_string.size();
                GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
                if (temp_string_size < 10) {
                    cout << "temp_string还没接就被释放了" << endl;
                    predicting.threadLogger_->info("temp_string还没接就被释放了");
                }
                predicting.threadLogger_->info("HumanVehFurtureVecWaypoint2json successfully");
                predicting.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
                predicting.threadLogger_->info("即将出  return_write_lock 锁");
                cout << "即将出  return_write_lock 锁" << endl;
                return GlobalVariable::getInstance()->GetReceivePtr();
            }
        } catch (const std::out_of_range& e) {
            // 处理数组越界异常
            cout << "预测库执行PredictingInterface时出现 out_of_range 抛出" << endl;
            predicting.threadLogger_->info("预测库执行PredictingInterface时出现 out_of_range 抛出");
            predicting.error_type_ = ErrorType::ALGORITHM_ERROR_TRY_CATCH_ERROR;
            {
                std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
                predicting.threadLogger_->info("进锁成功");
                string temp_string      = GlobalPlanning::Parser::HumanVehFurtureVecWaypoint2json(all_path, predicting);
                int    temp_string_size = temp_string.size();
                GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
                if (temp_string_size < 10) {
                    cout << "temp_string还没接就被释放了" << endl;
                    predicting.threadLogger_->info("出锁成功");
                }
                predicting.threadLogger_->info("HumanVehFurtureVecWaypoint2json successfully");
                predicting.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
                predicting.threadLogger_->info("出锁成功");
                return GlobalVariable::getInstance()->GetReceivePtr();
            }
        }
    }
    try {
        cout << "最后一步，将规划结果转为json格式字符串并返回" << endl;
        predicting.threadLogger_->info("最后一步，返回字符指针");
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            predicting.threadLogger_->info("进锁成功");
            string temp_string      = GlobalPlanning::Parser::HumanVehFurtureVecWaypoint2json(all_path, predicting);
            int    temp_string_size = temp_string.size();
            cout << "temp_string_size:" << temp_string_size << endl;
            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            cout << "执行完 GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data())" << endl;
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
                predicting.threadLogger_->info("出锁成功");
            }
            cout << "返回轨迹" << endl;
            predicting.threadLogger_->info("HumanVehFurtureVecWaypoint2json successfully");
            predicting.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
            predicting.threadLogger_->info("出锁成功");
            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    } catch (const std::exception& e) {
        cout << "预测库执行 HumanVehFurtureVecWaypoint2json 时出现 exception 抛出" << endl;
        predicting.threadLogger_->info("预测库执行 HumanVehFurtureVecWaypoint2json 时出现 exception 抛出");
        predicting.error_type_ = ErrorType::ALGORITHM_ERROR_TRY_CATCH_ERROR;
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            predicting.threadLogger_->info("进锁成功");
            string temp_string      = GlobalPlanning::Parser::HumanVehFurtureVecWaypoint2json(all_path, predicting);
            int    temp_string_size = temp_string.size();

            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
                predicting.threadLogger_->info("出锁成功");
            }
            predicting.threadLogger_->info("HumanVehFurtureVecWaypoint2json successfully");

            predicting.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
            predicting.threadLogger_->info("出锁成功");
            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    } catch (const std::out_of_range& e) {
        // 处理数组越界异常
        cout << "预测库执行 HumanVehFurtureVecWaypoint2json 时出现 out_of_range 抛出" << endl;
        predicting.threadLogger_->info("预测库执行 HumanVehFurtureVecWaypoint2json 时出现 out_of_range 抛出");
        predicting.error_type_ = ErrorType::ALGORITHM_ERROR_TRY_CATCH_ERROR;
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            predicting.threadLogger_->info("进锁成功");
            string temp_string      = GlobalPlanning::Parser::HumanVehFurtureVecWaypoint2json(all_path, predicting);
            int    temp_string_size = temp_string.size();
            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
                predicting.threadLogger_->info("出锁成功");
            }
            predicting.threadLogger_->info("HumanVehFurtureVecWaypoint2json successfully");
            predicting.threadLogger_->info("GlobalVariable::getInstance()->receive_ptr.strlen().size()::{}", strlen(GlobalVariable::getInstance()->GetReceivePtr()));
            predicting.threadLogger_->info("出锁成功");
            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    }
}

char* QueuePointGenerator(char* point_veh_start_end) {
    auto              currentTime = std::chrono::system_clock::now();
    std::time_t       timestamp   = std::chrono::system_clock::to_time_t(currentTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
    std::string timeStr = ss.str();
    cout << "**********************欢迎装载排队点自动生成库,版本号:G_V1.4.0.20250310_beta************************************" << timeStr << endl;
    time_t start_time, end_time;
    time(&start_time);
    LoadAreaPlanning::LoadAreaPlanning                                                                       planning;
    std::tuple<int, GlobalPlanning::Point, GlobalPlanning::Path, GlobalPlanning::Path, GlobalPlanning::Path> path;
    // 解析传入的参数
    cout << "本次入參大小： " << strlen(point_veh_start_end) << "strlen()计算方式" << endl;

    _LoadAreaPlanningInfos veh_start_end;
    try {
        std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->parse_func_write_lock); // 这里之所以加解析锁，是因为之前采用jna方案时，测试多线程调用时，出现解析混乱情况
        veh_start_end = GlobalPlanning::Parser::ParseLoadAreaPlanningJson(point_veh_start_end);
        cout << "execute_mode:" << veh_start_end.planning_mode << endl;
        cout << "load_point:(" << veh_start_end.load_point.x << "," << veh_start_end.load_point.y << ")" << endl;
    } catch (...) {
        // 捕获所有类型的异常
        std::cerr << "捕获到一个异常" << std::endl;
    }


    {
        std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->record_file_write_lock);
        std::ofstream                       record;
        std::string                         folderPath = "record_file";
        std::string                         filePath   = folderPath + "/LoadAreaPlanning_record.txt";
        if (!fs::exists(folderPath)) {
            try {
                fs::create_directory(folderPath);
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error creating directory: " << e.what() << std::endl;
            }
        }
        record.open(filePath, std::ios_base::app);
        record << timeStr << " ，收到请求" << "    装载区路径生成库版本号:G_V1.4.0.20250310_beta" << endl;
        record.close();
    }

    // 创建 log 目录
    string      id      = "load_point_test";
    std::string dirPath = "log/" + id;
    filesystem::create_directories(dirPath);
    // 构造文件路径
    std::string        filePath = dirPath + "/log_" + timeStr + ".log";
    std::ostringstream oss;
    int                num = GlobalVariable::getInstance()->GetDispatchNums();
    GlobalVariable::getInstance()->SetDispatchNums(num++);
    oss << GlobalVariable::getInstance()->GetDispatchNums();
    id += oss.str();

    planning.threadLogger_ = spdlog::rotating_logger_mt(id, filePath, 10 * 2048 * 2048, 5, true);
    planning.threadLogger_->flush_on(spdlog::level::info);
    planning.threadLogger_->info(id);
    planning.threadLogger_->info("point_veh_start_end.strlen().size:{}", strlen(point_veh_start_end));
    planning.threadLogger_->info("LoadAreaPlanning-IDS_LoadAreaPlanning_version: G_V1.4.0.20250310_beta");

    {
        std::shared_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->assignment_operation_lock);
        planning.threadLogger_->info("地图路网规模:{}", GlobalVariable::getInstance()->GetAllSelfDrivingReferencelines().size());
        if (GlobalVariable::getInstance()->GetAllSelfDrivingReferencelines().size() == 0) {
            get<0>(path) = 0;
            {
                std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
                string temp_string      = GlobalPlanning::Parser::LoadAreaPathVecWaypoint2json(path);
                int    temp_string_size = temp_string.size();
                GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
                if (temp_string_size < 10) {
                    cout << "temp_string还没接就被释放了" << endl;
                }
                return GlobalVariable::getInstance()->GetReceivePtr();
            }
        }

        // 给planning对象的有向图、地图边界、路段进行赋值
        planning.threadLogger_->info("map_border_:{}", GlobalVariable::getInstance()->GetMapBorder().size());
        planning.threadLogger_->info("装载区驶入引导路径:{}", GlobalVariable::getInstance()->GetInGuidingPaths().size());
        planning.threadLogger_->info("装载区驶出引导路径:{}", GlobalVariable::getInstance()->GetOutGuidingPaths().size());


    } // 获取传入的内边界并将其存入对应的r区域内

    planning.threadLogger_->info("wait_point.x ={}", veh_start_end.wait_point.x);
    planning.threadLogger_->info("wait_point.y ={}", veh_start_end.wait_point.y);
    planning.threadLogger_->info("wait_point.z ={}", veh_start_end.wait_point.z);
    planning.threadLogger_->info("wait_point.yaw ={}", veh_start_end.wait_point.yaw);
    planning.threadLogger_->info("load_point.x ={}", veh_start_end.load_point.x);
    planning.threadLogger_->info("load_point.y ={}", veh_start_end.load_point.y);
    planning.threadLogger_->info("load_point.z ={}", veh_start_end.load_point.z);
    planning.threadLogger_->info("load_point.yaw ={}", veh_start_end.load_point.yaw);




    // 构建碰撞检测对象
    CollisonCheck collison_check;

    collison_check.InitParam(veh_start_end.veh_param);
    Bound                map_border_v;
    vector<_BorderPoint> map_border;
    map_border = GlobalVariable::getInstance()->GetMapBorder();
    vector<Coordinate> vC;
    for (unsigned int i = 0; i < map_border.size(); ++i) {
        Coordinate temp_point;
        temp_point.z = 0;
        temp_point.x = map_border.at(i).x;
        temp_point.y = map_border.at(i).y;
        vC.push_back(temp_point);
    }
    map_border_v.push_back(vC);
    collison_check.InitBoundMap(map_border_v);

    Bound                              wall_border_v;
    const vector<vector<_BorderPoint>> wall_border = veh_start_end.wall_borders;
    cout << "收到挡墙" << wall_border.size() << "组" << endl;
    vC.clear();
    for (unsigned int i = 0; i < wall_border.size(); ++i) {
        for (unsigned int j = 0; j < wall_border.at(i).size(); ++j) {
            Coordinate temp_point;
            temp_point.z = 0;
            temp_point.x = wall_border.at(i).at(j).x;
            temp_point.y = wall_border.at(i).at(j).y;
            vC.push_back(temp_point);
        }
    }
    wall_border_v.push_back(vC);
    collison_check.InitWallMap(wall_border_v);

    Bound                        machine_border_v;
    vector<vector<_BorderPoint>> machine_border = veh_start_end.machine_borders;
    vC.clear();
    cout << "收到挖掘" << machine_border.size() << "组" << endl;
    for (unsigned int i = 0; i < machine_border.size(); ++i) {
        for (unsigned int j = 0; j < machine_border.at(i).size(); ++j) {
            Coordinate temp_point;
            temp_point.z = 0;
            temp_point.x = machine_border.at(i).at(j).x;
            temp_point.y = machine_border.at(i).at(j).y;
            vC.push_back(temp_point);
        }
    }
    machine_border_v.push_back(vC);
    collison_check.InitObstacleMap(machine_border_v);


    Path                input_path, out_path;
    vector<_SingleTraj> input_paths, output_paths;
    input_paths  = GlobalVariable::getInstance()->GetInGuidingPaths();
    output_paths = GlobalVariable::getInstance()->GetOutGuidingPaths();
    cout << "驶入引导路径一共" << input_paths.size() << "条" << endl;
    cout << "驶出引导路径一共" << output_paths.size() << "条" << endl;

    int    neares_idx  = -1;
    double nearest_dis = numeric_limits<double>::max();
    for (int i = 0; i < input_paths.size(); i++) {
        for (int j = 0; j < input_paths.at(i).trajectory.size(); j++) {
            double temp_dis = hypot(veh_start_end.load_point.x - input_paths.at(i).trajectory.at(j).x, veh_start_end.load_point.y - input_paths.at(i).trajectory.at(j).y);
            if (temp_dis < nearest_dis) {
                nearest_dis = temp_dis;
                neares_idx  = i;
            }
        }
    }
    Point temp_point;
    for (int i = 0; i < input_paths.at(neares_idx).trajectory.size(); i++) {
        temp_point.x         = input_paths.at(neares_idx).trajectory.at(i).x;
        temp_point.y         = input_paths.at(neares_idx).trajectory.at(i).y;
        temp_point.z         = input_paths.at(neares_idx).trajectory.at(i).z;
        temp_point.angle     = input_paths.at(neares_idx).trajectory.at(i).yaw / M_PI * 180.0;
        temp_point.curvature = input_paths.at(neares_idx).trajectory.at(i).curvature;
        temp_point.distance  = input_paths.at(neares_idx).trajectory.at(i).distance;
        temp_point.direction = static_cast<MotionDirection>(input_paths.at(neares_idx).trajectory.at(i).direction);
        input_path.push_back(temp_point);
    }
    cout << "结合当前load_point位置，挑选出的驶入引导路径第一个点坐标为:(" << input_path.front().x << "," << input_path.front().y << ")" << endl;

    nearest_dis = numeric_limits<double>::max();
    for (int i = 0; i < output_paths.size(); i++) {
        for (int j = 0; j < output_paths.at(i).trajectory.size(); j++) {
            double temp_dis = hypot(veh_start_end.load_point.x - output_paths.at(i).trajectory.at(j).x, veh_start_end.load_point.y - output_paths.at(i).trajectory.at(j).y);
            if (temp_dis < nearest_dis) {
                nearest_dis = temp_dis;
                neares_idx  = i;
            }
        }
    }
    for (int i = 0; i < output_paths.at(neares_idx).trajectory.size(); i++) {
        temp_point.x         = output_paths.at(neares_idx).trajectory.at(i).x;
        temp_point.y         = output_paths.at(neares_idx).trajectory.at(i).y;
        temp_point.z         = output_paths.at(neares_idx).trajectory.at(i).z;
        temp_point.angle     = output_paths.at(neares_idx).trajectory.at(i).yaw / M_PI * 180.0;
        temp_point.curvature = output_paths.at(neares_idx).trajectory.at(i).curvature;
        temp_point.distance  = output_paths.at(neares_idx).trajectory.at(i).distance;
        temp_point.direction = static_cast<MotionDirection>(output_paths.at(neares_idx).trajectory.at(i).direction);
        out_path.push_back(temp_point);
    }
    cout << "结合当前load_point位置，挑选出的驶出引导路径第一个点坐标为:(" << out_path.front().x << "," << out_path.front().y << ")" << endl;


    GlobalPlanning::Point wait_point, load_point;
    wait_point.x     = veh_start_end.wait_point.x;
    wait_point.y     = veh_start_end.wait_point.y;
    wait_point.z     = veh_start_end.wait_point.z;
    wait_point.angle = veh_start_end.wait_point.yaw;

    load_point.x     = veh_start_end.load_point.x;
    load_point.y     = veh_start_end.load_point.y;
    load_point.z     = veh_start_end.load_point.z;
    load_point.angle = veh_start_end.load_point.yaw;

    {
        planning.max_curve_length_                 = veh_start_end.max_curve_length;                 // 圆弧直线倒车最大曲线长度
        planning.min_curve_length_                 = veh_start_end.min_curve_length;                 // 圆弧直线倒车最小曲线长度
        planning.delta_curve_length_               = veh_start_end.delta_curve_length;               // 圆弧直线倒车曲线长度采样间距
        planning.wheel_base_length_                = veh_start_end.wheel_base_length;                // 车辆轴距
        planning.center2side_                      = veh_start_end.center2side;                      // 车辆宽度
        planning.max_straight_length_              = veh_start_end.max_straight_length;              // 圆弧直线倒车最大直线长度
        planning.min_straight_length_              = veh_start_end.min_straight_length;              // 圆弧直线倒车最小直线长度
        planning.delta_straight_length_            = veh_start_end.delta_straight_length;            // 圆弧直线倒车直线采样间距
        planning.max_steering_angle_               = veh_start_end.max_steering_angle;               // 圆弧直线倒车最大转向角
        planning.min_steering_angle_               = veh_start_end.min_steering_angle;               // 圆弧直线倒车最小转向角
        planning.delta_steering_angle_             = veh_start_end.delta_steering_angle;             // 圆弧直线倒车转角采样间距
        planning.standard_steering_angle_          = veh_start_end.standard_steering_angle;          // 标准倒车转角
        planning.weight_length_                    = veh_start_end.weight_length;                    // 圆弧直线倒车长度评分权重
        planning.weight_curve_                     = veh_start_end.weight_curve;                     // 圆弧直线倒车转角评分权重
        planning.load_path_straight_length_weight_ = veh_start_end.load_path_straight_length_weight; // 前往装载点路径直线长度权重
        planning.load_path_curvature_weight_       = veh_start_end.load_path_curvature_weight;       // 前往装载点路径曲率权重
        planning.out_put_path_dense_               = veh_start_end.out_put_path_dense;               // 输出路径密度
        planning.search_range_                     = veh_start_end.search_range;                     // 寻找周围路径范围
        planning.jump_dense_                       = veh_start_end.jump_dense;                       // 在目标路径上取点的密度
        planning.length_weight_                    = veh_start_end.length_weight;                    // 前进路径直线长度权重
        planning.critical_length_                  = veh_start_end.critical_length;                  // 前进路径长度标准值
        planning.curvature_weight_                 = veh_start_end.curvature_weight;                 // 前进路径曲率权重
        planning.min_straight_length_depart_       = veh_start_end.min_straight_length_depart;       // 驶离路径最短直线长度
        planning.max_straight_length_depart_       = veh_start_end.max_straight_length_depart;       // 驶离路径最长直线长度
        planning.delta_straight_length_depart_     = veh_start_end.delta_straight_length_depart;     // 驶离路径长度采样间距
        planning.min_straight_length_wait_         = veh_start_end.min_straight_length_wait;         // 前往等待点路径直线长度最大值
        planning.max_straight_length_wait_         = veh_start_end.max_straight_length_wait;         // 前往等待点路径直线长度最小值
        planning.delta_straight_length_wait_       = veh_start_end.delta_straight_length_wait;       // 前往等待点路径直线长度采样间距
        planning.min_straight_length_load_         = veh_start_end.min_straight_length_load;         // 前往装载点路径直线长度最小值
        planning.max_straight_length_load_         = veh_start_end.max_straight_length_load;         // 前往装载点路径直线长度最大值
        planning.delta_straight_length_load_       = veh_start_end.delta_straight_length_load;       // 前往装载点路径直线长度采样间距
        planning.center2front_                     = veh_start_end.veh_param.veh_center_2_front;
        planning.center2rear_                      = veh_start_end.veh_param.veh_center_2_rear_bound;
        planning.center2side_                      = veh_start_end.veh_param.veh_center_2_side;
        planning.safe_margin_front_                = veh_start_end.safe_margin_front;
        planning.safe_margin_rear_                 = veh_start_end.safe_margin_rear;
        planning.safe_margin_side_                 = veh_start_end.safe_margin_side;
        planning.collision_weight_                 = veh_start_end.collision_weight;
        planning.veh_param                         = veh_start_end.veh_param;
    }

    cout<<"line670    planning.veh_param.light_forward_max_steering: "<<planning.veh_param.light_forward_max_steering<<endl;


    try {
        cout << "开始调用LoadAreaPlanningInterface()" << endl;
        planning.threadLogger_->info("开始调用LoadAreaPlanningInterface()");
        path = planning.LoadAreaPlanningInterface(veh_start_end.planning_mode, wait_point, load_point, input_path, out_path, collison_check);
        cout << "LoadAreaPlanningInterface()返回信息汇总" << endl;
        cout << get<0>(path) << endl;
        cout << "(" << get<1>(path).x << "," << get<1>(path).y << ")" << endl;
        cout << get<2>(path).size() << " " << get<3>(path).size() << " " << get<4>(path).size() << endl;


        cout << "打印第一条路" << endl;
        for (int i = 0; i < get<2>(path).size(); i++) {
            cout << "x:" << get<2>(path).at(i).x << " y:" << get<2>(path).at(i).y << " yaw:" << get<2>(path).at(i).angle << endl;
        }

        cout << "打印第二条路" << endl;
        for (int i = 0; i < get<3>(path).size(); i++) {
            cout << "x:" << get<3>(path).at(i).x << " y:" << get<3>(path).at(i).y << " yaw:" << get<3>(path).at(i).angle << endl;
        }

        cout << "打印第三条路" << endl;
        for (int i = 0; i < get<4>(path).size(); i++) {
            cout << "x:" << get<4>(path).at(i).x << " y:" << get<4>(path).at(i).y << " yaw:" << get<4>(path).at(i).angle << endl;
        }
    } catch (const std::exception& e) {
        cout << "规划库执行GlobalPathPlanningIntface时出现 exception 抛出" << endl;
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            cout << "进 return_write_lock 锁成功" << endl;
            string temp_string      = GlobalPlanning::Parser::LoadAreaPathVecWaypoint2json(path);
            int    temp_string_size = temp_string.size();
            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
            }
            cout << "即将出  return_write_lock 锁" << endl;
            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    } catch (const std::out_of_range& e) {
        // 处理数组越界异常
        cout << "规划库执行GlobalPathPlanningIntface时出现 out_of_range 抛出" << endl;
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            string temp_string      = GlobalPlanning::Parser::LoadAreaPathVecWaypoint2json(path);
            int    temp_string_size = temp_string.size();
            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
            }
            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    }

    try {
        cout << "最后一步，将规划结果转为json格式字符串并返回" << endl;
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            string temp_string      = GlobalPlanning::Parser::LoadAreaPathVecWaypoint2json(path);
            int    temp_string_size = temp_string.size();
            cout << "temp_string_size:" << temp_string_size << endl;
            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            cout << "执行完 GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data())" << endl;
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
            }
            cout << "返回轨迹" << endl;
            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    } catch (const std::exception& e) {
        cout << "规划库执行 VecWaypoint2json 时出现 exception 抛出" << endl;
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            string temp_string      = GlobalPlanning::Parser::LoadAreaPathVecWaypoint2json(path);
            int    temp_string_size = temp_string.size();

            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
            }

            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    } catch (const std::out_of_range& e) {
        // 处理数组越界异常
        cout << "规划库执行 VecWaypoint2json 时出现 out_of_range 抛出" << endl;
        {
            std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->return_write_lock);
            string temp_string      = GlobalPlanning::Parser::LoadAreaPathVecWaypoint2json(path);
            int    temp_string_size = temp_string.size();
            GlobalVariable::getInstance()->SetReceivePtr((char*)GlobalVariable::getInstance()->GetGlobalStr().data());
            if (temp_string_size < 10) {
                cout << "temp_string还没接就被释放了" << endl;
            }
            return GlobalVariable::getInstance()->GetReceivePtr();
        }
    }
}
