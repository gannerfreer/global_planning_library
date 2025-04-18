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
        planning.all_referencelines_  = GlobalVariable::getInstance()->GetAllSelfDrivingReferencelines();
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
        predicting.threadLogger_->info("地图路网规模:{}", GlobalVariable::getInstance()->GetAllReferencelines().size());
        if (GlobalVariable::getInstance()->GetReferencelineGraph().size() == 0) {
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
        predicting.all_referencelines_ = GlobalVariable::getInstance()->GetAllHumanDrivingReferencelines();
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
            cout << "规划库执行GlobalPathPlanningIntface时出现 exception 抛出" << endl;
            predicting.threadLogger_->info("规划库执行GlobalPathPlanningIntface时出现 exception 抛出");
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
            cout << "规划库执行GlobalPathPlanningIntface时出现 out_of_range 抛出" << endl;
            predicting.threadLogger_->info("规划库执行GlobalPathPlanningIntface时出现 out_of_range 抛出");
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
        cout << "规划库执行 HumanVehFurtureVecWaypoint2json 时出现 exception 抛出" << endl;
        predicting.threadLogger_->info("规划库执行 HumanVehFurtureVecWaypoint2json 时出现 exception 抛出");
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
        cout << "规划库执行 HumanVehFurtureVecWaypoint2json 时出现 out_of_range 抛出" << endl;
        predicting.threadLogger_->info("规划库执行 HumanVehFurtureVecWaypoint2json 时出现 out_of_range 抛出");
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
