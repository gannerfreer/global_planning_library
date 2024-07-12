#include "planning.h"
// string g_StrData;
// namespace fs = std::filesystem;
// zones m_map_Area;
// const float64 eps = 1e-8;
// std::mutex filemutex;
// string temp_str;
// std::mutex mutexxx;
// std::mutex filemutex1;
// std::mutex filemutex2;
// static std::shared_mutex global_variable_mutex;
// static std::shared_mutex return_receive_ptr_mutex;
// static std::shared_mutex write_record_file_mutex;
// int sumnum = 0;
// // unordered_map<string, int> vehicle_mutex_map;
// char *receive_ptr;
// // INITIALIZE_EASYLOGGINGPP

// Planning::Planning()
// {
//     InitialFunction();
// }
// Planning::~Planning()
// {
//     cout << "析构函数已被调用" << endl;
// }
// // 解析从数据库传来的地图数据
// void GetMap(char *parea)
// {
//     // cout << "GlobalPathPlanning-IDS_Global_Planning_version: G_V1.0.1.20240702_RC" << endl;
//     // cout << "规划库版本号:G_V1.0.1.20240702_RC" << endl;
//     cout << "规划库版本号:bianji" << endl;
//     zones retarea;
//     float64 rand_dist = 0.0;
//     rapidjson::Document doc;
//     doc.Parse(parea);
//     if (doc.HasParseError())
//     {
//         doc.GetParseError();
//         doc.GetErrorOffset();
//     }
//     doc.GetAllocator();

//     if (doc.HasMember("Road_Directed_Graph"))
//     {
//         cout << "解析 Road_Directed_Graph 中" << endl;
//         Value &val = doc["Road_Directed_Graph"];

//         if (val.IsObject())
//         {
//             if (val.HasMember("graph") && val["graph"].IsArray())
//             {
//                 const rapidjson::Value &array = val["graph"].GetArray();
//                 size_t len = array.Size();
//                 for (size_t i = 0; i < len; i++)
//                 {
//                     const rapidjson::Value &arrayy = array[i];
//                     size_t lenn = arrayy.Size();
//                     std::vector<double> ppt;
//                     for (size_t j = 0; j < lenn; j++)
//                     {
//                         double temp_ppt;
//                         temp_ppt = arrayy[j].GetDouble();
//                         if (fabs(temp_ppt - 0.0) <= DBL_MIN)
//                         {
//                             temp_ppt = 10000;
//                         }
//                         ppt.push_back(temp_ppt);
//                     }
//                     retarea.Road_Directed_Graph.graph.push_back(ppt);
//                 }
//             }
//         }
//         {
//             std::unique_lock<std::shared_mutex> lock(global_variable_mutex);
//             m_map_Area.Road_Directed_Graph.Clear();
//             m_map_Area.Road_Directed_Graph = retarea.Road_Directed_Graph;
//         }
//     }
//     else
//     {
//         cout << "无 Road_Directed_Graph 参数" << endl;
//     }

//     if (doc.HasMember("all_zone_atr"))
//     {
//         Value &val = doc["all_zone_atr"];
//         if (val.IsArray() && !val.Empty())
//         {
//             for (size_t i = 0; i < val.Size(); ++i)
//             {
//                 Value &tempval = val[i];
//                 if (tempval.IsObject())
//                 {
//                     Single_Zone pt;
//                     if (tempval.HasMember("zone_id"))
//                     {
//                         pt.zone_id = tempval["zone_id"].GetInt();
//                     }
//                     if (tempval.HasMember("max_speed"))
//                     {
//                         pt.max_speed = tempval["max_speed"].GetFloat();
//                     }
//                     if (tempval.HasMember("zone_type"))
//                     {
//                         pt.zone_type = tempval["zone_type"].GetInt();
//                     }
//                     // parking_points
//                     if (tempval.HasMember("parking_points"))
//                     {
//                         Value &temp_park_points = tempval["parking_points"];
//                         if (temp_park_points.IsArray() && !temp_park_points.Empty())
//                         {
//                             for (size_t i = 0; i < temp_park_points.Size(); ++i)
//                             {
//                                 rapidjson::Value &tempobj = temp_park_points[i];
//                                 if (tempobj.IsObject())
//                                 {
//                                     Single_Point point;
//                                     point.x = tempobj["x"].GetDouble();
//                                     point.y = tempobj["y"].GetDouble();
//                                     point.z = tempobj["z"].GetFloat();
//                                     point.yaw = tempobj["yaw"].GetFloat();
//                                     pt.parking_points.push_back(point);
//                                 }
//                             }
//                         }
//                     }
//                     // load_points
//                     if (tempval.HasMember("load_points"))
//                     {
//                         Value &temp = tempval["load_points"];
//                         if (temp.IsArray() && !temp.Empty())
//                         {
//                             for (size_t i = 0; i < temp.Size(); ++i)
//                             {
//                                 rapidjson::Value &tempobj = temp[i];
//                                 if (tempobj.IsObject())
//                                 {
//                                     Single_Point point;
//                                     point.x = tempobj["x"].GetDouble();
//                                     point.y = tempobj["y"].GetDouble();
//                                     point.z = tempobj["z"].GetFloat();
//                                     point.yaw = tempobj["yaw"].GetFloat();
//                                     pt.load_points.push_back(point);
//                                 }
//                             }
//                         }
//                     }
//                     // unload_points
//                     if (tempval.HasMember("unload_points"))
//                     {
//                         Value &temp = tempval["unload_points"];
//                         if (temp.IsArray() && !temp.Empty())
//                         {
//                             for (size_t i = 0; i < temp.Size(); ++i)
//                             {
//                                 rapidjson::Value &tempobj = temp[i];
//                                 if (tempobj.IsObject())
//                                 {
//                                     Single_Point point;
//                                     point.x = tempobj["x"].GetDouble();
//                                     point.y = tempobj["y"].GetDouble();
//                                     point.z = tempobj["z"].GetFloat();
//                                     point.yaw = tempobj["yaw"].GetFloat();
//                                     pt.unload_points.push_back(point);
//                                 }
//                             }
//                         }
//                     }

//                     // inner_borders
//                     if (tempval.HasMember("inner_borders"))
//                     {
//                         Value &temp = tempval["inner_borders"];
//                         for (size_t i = 0; i < temp.Size(); ++i)
//                         {
//                             rapidjson::Value &tempobj = temp[i];
//                             if (tempobj.IsObject())
//                             {
//                                 Single_Border border;
//                                 if (tempobj.HasMember("point_num"))
//                                 {
//                                     border.point_num = tempobj["point_num"].GetInt64();
//                                 }
//                                 if (tempobj.HasMember("border_points"))
//                                 {
//                                     Single_Border_Point temp_inner_border;
//                                     for (size_t j = 0; j < temp.Size(); ++j)
//                                     {
//                                         Value &tempborder = tempobj[j];
//                                         temp_inner_border.x = tempborder["x"].GetDouble();
//                                         temp_inner_border.y = tempborder["y"].GetDouble();
//                                         temp_inner_border.z = tempborder["z"].GetFloat();
//                                         temp_inner_border.type = tempborder["type"].GetInt();
//                                         border.border_points.push_back(temp_inner_border);
//                                     }
//                                 }

//                                 pt.inner_borders.push_back(border);
//                             }
//                         }
//                     }

//                     // external_border
//                     if (tempval.HasMember("external_border"))
//                     {
//                         Value &temp = tempval["external_border"];
//                         if (temp.IsObject())
//                         {
//                             Single_Border border;
//                             if (temp.HasMember("point_num"))
//                             {
//                                 border.point_num = temp["point_num"].GetUint();
//                             }
//                             if (temp.HasMember("border_points"))
//                             {
//                                 Value &temp_border_points = temp["border_points"];
//                                 Single_Border_Point temp_external_border;
//                                 for (size_t j = 0; j < temp_border_points.Size(); ++j)
//                                 {
//                                     Value &tempborder = temp_border_points[j];

//                                     temp_external_border.x = tempborder["x"].GetDouble();
//                                     temp_external_border.y = tempborder["y"].GetDouble();
//                                     temp_external_border.z = tempborder["z"].GetFloat();
//                                     temp_external_border.type = tempborder["type"].GetInt();
//                                     pt.external_border.border_points.push_back(temp_external_border);
//                                 }
//                             }
//                         }
//                     }

//                     // 参考路径
//                     if (tempval.HasMember("reference_trajs") && tempval["reference_trajs"].IsArray())
//                     {
//                         rapidjson::Value &temp_reference_trajs = tempval["reference_trajs"].GetArray();
//                         for (size_t j = 0; j < temp_reference_trajs.Size(); j++)
//                         {
//                             Single_Trajectory tra;
//                             Value &temp = temp_reference_trajs[j];
//                             if (temp.HasMember("start_zone_id"))
//                             {
//                                 tra.start_zone_id = temp["start_zone_id"].GetInt();
//                             }
//                             if (temp.HasMember("current_zone_id"))
//                             {
//                                 tra.current_zone_id = temp["current_zone_id"].GetInt();
//                             }
//                             if (temp.HasMember("end_zone_id"))
//                             {
//                                 tra.end_zone_id = temp["end_zone_id"].GetInt();
//                             }
//                             if (temp.HasMember("traj_point_num"))
//                             {
//                                 tra.traj_point_num = temp["traj_point_num"].GetInt();
//                             }
//                             if (temp.HasMember("id"))
//                             {
//                                 tra.id = temp["id"].GetInt();
//                             }
//                             if (temp.HasMember("trajectory"))
//                             {
//                                 rapidjson::Value &tempobj = temp["trajectory"];
//                                 Trajectory_Point temp_tra;
//                                 for (size_t j = 0; j < tempobj.Size(); ++j)
//                                 {
//                                     Value &temppoint = tempobj[j];
//                                     temp_tra.x = temppoint["x"].GetDouble();
//                                     temp_tra.y = temppoint["y"].GetDouble();
//                                     temp_tra.z = temppoint["z"].GetFloat();
//                                     temp_tra.yaw = temppoint["yaw"].GetFloat();
//                                     temp_tra.yaw = temp_tra.yaw / 180 * M_PI;
//                                     temp_tra.left = temppoint["left"].GetDouble();
//                                     temp_tra.right = temppoint["right"].GetDouble();
//                                     temp_tra.slope = temppoint["slope"].GetFloat();
//                                     temp_tra.speed = temppoint["speed"].GetFloat();
//                                     temp_tra.speed_limit = temppoint["speed_limit"].GetFloat();
//                                     //    temp_tra.distance    = temppoint["distance"].GetFloat();
//                                     temp_tra.attribute = temppoint["attribute"].GetDouble();
//                                     temp_tra.curvature = temppoint["curvature"].GetFloat();
//                                     temp_tra.direction = temppoint["direction"].GetInt();
//                                     //    temp_tra.areaid      = temppoint["areaid"].GetInt();
//                                     //                                   temp_tra.x           =
//                                     temppoint["x"].GetDouble() + rand_dist*cos(temp_tra.yaw + M_PI/2);
//                                     //                                   temp_tra.y           =
//                                     temppoint["y"].GetDouble() + rand_dist*sin(temp_tra.yaw + M_PI/2);
//                                     tra.trajectory.push_back(temp_tra);
//                                 }
//                             }
//                             pt.reference_trajs.push_back(tra);
//                         }
//                     }
//                     retarea.all_zone_atr.push_back(pt);
//                 }
//             }
//         }
//         {
//             std::unique_lock<std::shared_mutex> lock(global_variable_mutex);
//             m_map_Area.all_zone_atr.clear();
//             m_map_Area.all_zone_atr.insert(m_map_Area.all_zone_atr.end(), retarea.all_zone_atr.begin(),
//             retarea.all_zone_atr.end()); cout << "GetMap函数内" << m_map_Area.all_zone_atr.size() << endl;
//         }
//     }

//     // 测试hriedisi是否能够连接成
//     //  创建连接对象

//     return;
// }

// /**
//  * @brief 类初始化函数，进行地图文件读取，相关参数初始化
//  * @param [in] 无
//  * @param [return] true：初始化成功，false：初始化失败
//  */
// bool Planning::InitialFunction()
// {

//     all_zones_.clear(); // 储存所有区域信息的容器
//     road_directed_graph_.Clear();
//     global_path_.clear(); // 全局路径

//     last_task_type_ = static_cast<uint8>(TaskType::RESERVED);
//     task_type_ = static_cast<uint8>(TaskType::RESERVED);

//     start_point_out_border_ = false;
//     end_point_out_border_ = false;
//     reverse_flag_ = false;

// #ifdef SKIP_HEADER
// #else
//     if (ReadAllMapFile())
//     {
//         printf(" The map file is readed \n");
//         return true;
//     }
//     else
//     {
//         printf(" Failed to read the map file \n");
//         return false;
//     }
// #endif
//     return true;
// }
// bool Planning::ReadAllMapFile()
// {
// #ifdef SKIP_HEADER
// #else
//     memset(&m_tar_rviz_data_, 0, sizeof(tarRviz));
//     m_tar_rviz_data_.minx = INF;
//     m_tar_rviz_data_.miny = INF;
//     // 读取地图信息
//     if (!configio_.GetMap(all_zones_, road_directed_graph_, m_tar_rviz_data_) ||
//     !configio_.GetVehicleParam(vehicle_param_))
//     {
//         return false;
//     }
//     else
//     {
//         task_type_ = vehicle_param_.task_type;
//         return true;
//     }

// #endif
// }

// char *GlobalPathPlanning(char *point_veh_start_end)
// {
//     cout << "**********************欢迎光临后台全局规划库************************************" << endl;
//     // cout << "规划库版本号:G_V1.0.1.20240702_RC" << endl;
//     cout << "规划库版本号:bianji" << endl;
//     time_t start_time, end_time;
//     time(&start_time);
//     Planning planning;
//     std::vector<Trajectory_Point> path;
//     // 解析传入的参数
//     cout << "point_veh_start_end.size()  " << strlen(point_veh_start_end) << endl;
//     filemutex1.lock();
//     GlobalPlanning ::tar_start_end veh_start_end;
//     veh_start_end = planning.ParseInputInfo(point_veh_start_end);
//     planning.key_ = veh_start_end.my_key;
//     filemutex1.unlock();

//     std::string vehicle_code = std::to_string(veh_start_end.m_Veh_Param.vehicle_code);

//     planning.vehicle_code_ = vehicle_code;
//     auto currentTime = std::chrono::system_clock::now();
//     std::time_t timestamp = std::chrono::system_clock::to_time_t(currentTime);
//     std::stringstream ss;
//     ss << std::put_time(std::localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
//     std::string timeStr = ss.str();

//     {
//         std::unique_lock<std::shared_mutex> lock(write_record_file_mutex);
//         std::ofstream record;
//         record.open("record.txt", std::ios_base::app);
//         record << timeStr << " ，收到规划请求，请求号：" << veh_start_end.my_key << "，车辆编号：" << vehicle_code <<
//         endl; record.close();
//     }

//     // 创建 log 目录
//     std::string dirPath = "log/" + vehicle_code;
//     fs::create_directories(dirPath);
//     // 构造文件路径
//     std::string filePath = dirPath + "/log_" + timeStr + ".txt";
//     std::ostringstream oss;
//     sumnum++;
//     oss << sumnum;
//     vehicle_code += oss.str();
//     cout << "begin creating rotating_logger_mt" << endl;
//     try
//     {
//         planning.threadLogger_ = spdlog::rotating_logger_mt(vehicle_code, filePath, 10 * 2048 * 2048, 5, true);
//         planning.threadLogger_->flush_on(spdlog::level::info);
//         planning.my_optimal_path_.threadLogger_ = planning.threadLogger_;
//         planning.threadLogger_->info(vehicle_code);
//         planning.threadLogger_->info("point_veh_start_end.strlen().size:{}", strlen(point_veh_start_end));
//         planning.threadLogger_->info("veh_start_end.my_key:{}", veh_start_end.my_key);
//         planning.threadLogger_->info("GlobalPathPlanning-IDS_Global_Planning_version: G_V1.0.1.20240702_RC");
//     }
//     catch (const std::exception &e)
//     {
//         cout << "异常赋值" << endl;
//         // planning.threadLogger_->close();
//         // planning.threadLogger_->info("temp_zone_id:{}-------all_zones_.size():{}", temp_zone_id,
//         planning.all_zones_.size()); planning.error_type_ = static_cast<uint>(ErrorType::ALGORITHM_ERROR);
//         {
//             std::unique_lock<std::shared_mutex> lock(return_receive_ptr_mutex);

//             string temp_string = planning.VecWaypoint2json(path);
//             int temp_string_size = temp_string.size();
//             receive_ptr = (char *)g_StrData.data();
//             cout << "receive_ptr.strlen().size():" << strlen(receive_ptr) << endl;
//             return receive_ptr;
//         }
//     }

//     {
//         std::shared_lock<std::shared_mutex> lock(global_variable_mutex);
//         planning.threadLogger_->info("m_map_Area.Road_Directed_Graph.graph.size():{}",
//         m_map_Area.Road_Directed_Graph.graph.size());
//         planning.threadLogger_->info("m_map_Area.all_zone_atr.size():{}", m_map_Area.all_zone_atr.size());
//         if (m_map_Area.Road_Directed_Graph.graph.size() == 0)
//         {
//             planning.error_type_ = static_cast<uint>(ErrorType::NO_MAP);
//             {
//                 std::unique_lock<std::shared_mutex> lock(return_receive_ptr_mutex);
//                 planning.threadLogger_->info("进锁成功");
//                 string temp_string = planning.VecWaypoint2json(path);
//                 int temp_string_size = temp_string.size();

//                 receive_ptr = (char *)g_StrData.data();
//                 if (temp_string_size < 10)
//                 {
//                     cout << "temp_string还没接就被释放了" << endl;
//                     planning.threadLogger_->info("出锁成功");
//                 }
//                 planning.threadLogger_->info("VecWaypoint2json successfully");
//                 cout << "receive_ptr.strlen().size():" << strlen(receive_ptr) << endl;
//                 planning.threadLogger_->info("receive_ptr.strlen().size()::{}", strlen(receive_ptr));
//                 planning.threadLogger_->info("出锁成功");
//                 return receive_ptr;
//             }
//         }
//         // 打印一下m_map_Area具体信息
//         for (int i = 0; i < m_map_Area.all_zone_atr.size(); i++)
//         {
//             int size = m_map_Area.all_zone_atr.at(i).reference_trajs.size();

//             planning.threadLogger_->info("区域{}有{}条参考路径", i + 1, size);
//             cout << "区域" << i + 1 << "有" << size << "条参考路径" << endl;
//         }
//         cout << "m_map_Area.Road_Directed_Graph.graph.size():" << m_map_Area.Road_Directed_Graph.graph.size() <<
//         endl; cout << "m_map_Area.all_zone_atr.size():" << m_map_Area.all_zone_atr.size() << endl;
//         planning.road_directed_graph_ = m_map_Area.Road_Directed_Graph;
//         planning.all_zones_ = m_map_Area.all_zone_atr;
//     } // 获取传入的内边界并将其存入对应的r区域内
//     uint8 temp_zone_id;
//     cout << "成功创建日志对象" << endl;
//     cout << "地图有" << planning.all_zones_.size() << "个区域" << endl;
//     if (!veh_start_end.inner_borders.empty())
//     {
//         try
//         {
//             for (size_t i = 0; i < veh_start_end.inner_borders.size(); i++)
//             {
//                 if (!veh_start_end.inner_borders.at(i).inner_border.empty())
//                 {
//                     temp_zone_id = veh_start_end.inner_borders.at(i).zone_id;
//                     planning.all_zones_.at(temp_zone_id - 1).inner_borders =
//                     veh_start_end.inner_borders.at(i).inner_border;
//                     // planning.my_inner_border = veh_start_end.inner_borders.at(i).inner_border;
//                 }
//             }
//         }
//         catch (const std::exception &e)
//         {
//             cout << "异常赋值" << endl;
//             // planning.threadLogger_->info("temp_zone_id:{}-------all_zones_.size():{}", temp_zone_id,
//             planning.all_zones_.size()); planning.error_type_ = static_cast<uint>(ErrorType::ALGORITHM_ERROR);
//             {
//                 std::unique_lock<std::shared_mutex> lock(return_receive_ptr_mutex);
//                 planning.threadLogger_->info("进锁成功");
//                 string temp_string = planning.VecWaypoint2json(path);
//                 int temp_string_size = temp_string.size();

//                 receive_ptr = (char *)g_StrData.data();
//                 if (temp_string_size < 10)
//                 {
//                     cout << "temp_string还没接就被释放了" << endl;
//                     planning.threadLogger_->info("出锁成功");
//                 }
//                 planning.threadLogger_->info("VecWaypoint2json successfully");
//                 cout << "receive_ptr.strlen().size():" << strlen(receive_ptr) << endl;
//                 planning.threadLogger_->info("receive_ptr.strlen().size()::{}", strlen(receive_ptr));
//                 planning.threadLogger_->info("出锁成功");
//                 return receive_ptr;
//             }
//         }
//     }
//     else
//     {
//         planning.threadLogger_->error("此次任务无inner_borders信息");
//     }
//     planning.task_type_ = veh_start_end.m_task_type;
//     planning.vehicle_param_ = veh_start_end.m_Veh_Param;
//     planning.threadLogger_->info("m_start_point.x ={}", veh_start_end.m_Start_Point.x);
//     planning.threadLogger_->info("m_start_point.y ={}", veh_start_end.m_Start_Point.y);
//     planning.threadLogger_->info("m_start_point.z ={}", veh_start_end.m_Start_Point.z);
//     planning.threadLogger_->info("m_start_point.yaw ={}", veh_start_end.m_Start_Point.yaw);
//     planning.threadLogger_->info("m_End_Point.x ={}", veh_start_end.m_End_Point.x);
//     planning.threadLogger_->info("m_End_Point.y ={}", veh_start_end.m_End_Point.y);
//     planning.threadLogger_->info("m_End_Point.z ={}", veh_start_end.m_End_Point.z);
//     planning.threadLogger_->info("m_End_Point.yaw ={}", veh_start_end.m_End_Point.yaw);
//     // 起点
//     planning.start_point_ = veh_start_end.m_Start_Point;
//     // 终点
//     planning.end_point_ = veh_start_end.m_End_Point;
//     // spdlog::shutdown();
//     try
//     {
//         planning.GlobalPathPlanningIntface(path);
//     }
//     catch (const std::exception &e)
//     {
//         cout << "调用全局规划库内部出现异常" << endl;
//         planning.threadLogger_->info("调用全局规划库内部出现异常");
//         planning.error_type_ = static_cast<uint>(ErrorType::ALGORITHM_ERROR);
//         {
//             std::unique_lock<std::shared_mutex> lock(return_receive_ptr_mutex);
//             planning.threadLogger_->info("进锁成功");
//             string temp_string = planning.VecWaypoint2json(path);
//             int temp_string_size = temp_string.size();

//             receive_ptr = (char *)g_StrData.data();
//             if (temp_string_size < 10)
//             {
//                 cout << "temp_string还没接就被释放了" << endl;
//                 planning.threadLogger_->info("出锁成功");
//             }
//             planning.threadLogger_->info("VecWaypoint2json successfully");
//             cout << "receive_ptr.strlen().size():" << strlen(receive_ptr) << endl;
//             planning.threadLogger_->info("receive_ptr.strlen().size()::{}", strlen(receive_ptr));
//             planning.threadLogger_->info("出锁成功");
//             return receive_ptr;
//         }
//     }
//     catch (const std::out_of_range &e)
//     {
//         // 处理数组越界异常
//         cout << "调用全局规划库内部出现异常" << endl;
//         planning.threadLogger_->info("调用全局规划库内部出现异常");
//         planning.error_type_ = static_cast<uint>(ErrorType::ALGORITHM_ERROR);
//         {
//             std::unique_lock<std::shared_mutex> lock(return_receive_ptr_mutex);
//             planning.threadLogger_->info("进锁成功");
//             string temp_string = planning.VecWaypoint2json(path);
//             receive_ptr = (char *)temp_string.data();
//             planning.threadLogger_->info("VecWaypoint2json successfully");
//             cout << "receive_ptr.strlen().size():" << strlen(receive_ptr) << endl;

//             planning.threadLogger_->info("receive_ptr.strlen().size()::{}", strlen(receive_ptr));
//             planning.threadLogger_->info("出锁成功");
//             return receive_ptr;
//         }
//     }

//     try
//     {
//         cout << "最后一步，返回字符指针" << endl;
//         planning.threadLogger_->info("最后一步，返回字符指针");

//         {
//             std::unique_lock<std::shared_mutex> lock(return_receive_ptr_mutex);
//             planning.threadLogger_->info("进锁成功");
//             string temp_string = planning.VecWaypoint2json(path);
//             int temp_string_size = temp_string.size();

//             receive_ptr = (char *)g_StrData.data();
//             if (temp_string_size < 10)
//             {
//                 cout << "temp_string还没接就被释放了" << endl;
//                 planning.threadLogger_->info("出锁成功");
//             }
//             planning.threadLogger_->info("VecWaypoint2json successfully");
//             cout << "receive_ptr.strlen().size():" << strlen(receive_ptr) << endl;
//             planning.threadLogger_->info("receive_ptr.strlen().size()::{}", strlen(receive_ptr));
//             planning.threadLogger_->info("出锁成功");
//             return receive_ptr;
//         }
//     }
//     catch (const std::exception &e)
//     {
//         cout << "全局轨迹规划库内部，返参出现异常" << endl;
//         planning.threadLogger_->info("全局轨迹规划库内部，返参出现异常");
//         planning.error_type_ = static_cast<uint>(ErrorType::ALGORITHM_ERROR);
//         {
//             std::unique_lock<std::shared_mutex> lock(return_receive_ptr_mutex);
//             planning.threadLogger_->info("进锁成功");
//             string temp_string = planning.VecWaypoint2json(path);
//             int temp_string_size = temp_string.size();

//             receive_ptr = (char *)g_StrData.data();
//             if (temp_string_size < 10)
//             {
//                 cout << "temp_string还没接就被释放了" << endl;
//                 planning.threadLogger_->info("出锁成功");
//             }
//             planning.threadLogger_->info("VecWaypoint2json successfully");
//             cout << "receive_ptr.strlen().size():" << strlen(receive_ptr) << endl;
//             planning.threadLogger_->info("receive_ptr.strlen().size()::{}", strlen(receive_ptr));
//             planning.threadLogger_->info("出锁成功");
//             return receive_ptr;
//         }
//     }
//     catch (const std::out_of_range &e)
//     {
//         // 处理数组越界异常
//         cout << "全局轨迹规划库内部，返参出现异常" << endl;
//         planning.threadLogger_->info("全局轨迹规划库内部，返参出现异常");
//         planning.error_type_ = static_cast<uint>(ErrorType::ALGORITHM_ERROR);
//         {
//             std::unique_lock<std::shared_mutex> lock(return_receive_ptr_mutex);
//             planning.threadLogger_->info("进锁成功");
//             string temp_string = planning.VecWaypoint2json(path);
//             int temp_string_size = temp_string.size();

//             receive_ptr = (char *)g_StrData.data();
//             if (temp_string_size < 10)
//             {
//                 cout << "temp_string还没接就被释放了" << endl;
//                 planning.threadLogger_->info("出锁成功");
//             }
//             planning.threadLogger_->info("VecWaypoint2json successfully");
//             cout << "receive_ptr.strlen().size():" << strlen(receive_ptr) << endl;
//             planning.threadLogger_->info("receive_ptr.strlen().size()::{}", strlen(receive_ptr));
//             planning.threadLogger_->info("出锁成功");
//             return receive_ptr;
//         }
//     }
// }
void Planning::GlobalPathPlanningIntface(std::vector<_TrajectoryPoint>& path) {
    path.clear();
    // 路径规划
    PathPlanning();
    // 均匀碾压
    if (vehicle_param_.offset_enable == true) {}
    // 速度规划
    SpeedPlanning();


    // if (!global_path_.size())
    // {
    //     threadLogger_->error("...The size of the global path is 0...");

    //     error_type_ = static_cast<uint>(ErrorType::PLANNING_FAIL);
    //     last_task_type_ = task_type_;
    //     return;
    // }
    // else
    // {
    //     if (global_path_.size() == 2)
    //     {
    //         CalDistance(global_path_); // 计算路径的位移信息
    //         global_path_.at(0).speed = 0;
    //         global_path_.at(0).speed_limit = 100;
    //         global_path_.at(1).speed = 0;
    //         global_path_.at(1).speed_limit = 100;
    //         path = global_path_;
    //         return;
    //     }
    //     if (reverse_flag_)
    //     {
    //         cout << "有必要对短距离倒车进行方向属性更改" << endl;
    //         threadLogger_->info("有必要对短距离倒车进行方向属性更改");
    //         for (int i = 0; i < global_path_.size(); i++)
    //         {
    //             if (global_path_.at(i).direction == 0)
    //             {
    //                 global_path_.at(i).direction = 1;
    //                 cout << "路径属性修改为倒车属性" << endl;
    //                 threadLogger_->info("路径属性修改为倒车属性");
    //             }
    //         }
    //     }
    //     cout << "global_path_.size():" << global_path_.size() << endl;
    //     threadLogger_->info("global_path_.size():{}", global_path_.size());

    //     // 删除重复点
    //     cout << "去重检查" << endl;
    //     threadLogger_->info("去重检查");
    //     std::vector<Trajectory_Point> temp1;
    //     temp1 = global_path_;
    //     removeDuplicates(temp1, global_path_);
    //     cout << "检查完毕" << endl;
    //     threadLogger_->info("检查完毕");

    //     // 将终点添加到全局路径中
    //     // 判断终点与全局路径最后一个点的角度偏差，基于角度偏差信息来判断是否 将其抛弃
    //     float end_point_last_point_angle_diff;
    //     end_point_last_point_angle_diff = atan2(end_point_.y - global_path_.back().y, end_point_.x -
    //     global_path_.back().x); if (end_point_last_point_angle_diff < 0)
    //     {
    //         end_point_last_point_angle_diff += 2 * M_PI; // 将终点与全局路径最后一个点的角度偏差规范[0,2π）
    //     }
    //     // 如果最后一个点位于终点后面，需要进行删除
    //     // 如果最后一个点没有位于终点后，但是基本与终点重合，也需要进行删除
    //     float64 end_point_last_point_distance;
    //     end_point_last_point_distance = sqrt(pow(end_point_.x - global_path_.back().x, 2) + pow(end_point_.y -
    //     global_path_.back().y, 2)); if ((fabs(end_point_last_point_angle_diff - global_path_.back().yaw) * 180.0
    //     / M_PI > 90 && fabs(end_point_last_point_angle_diff - global_path_.back().yaw) * 180.0 / M_PI < 270) ||
    //     (fabs(end_point_.x - global_path_.back().x) <= 0.3 && fabs(end_point_.y - global_path_.back().y) <=
    //     0.3))
    //     {
    //         global_path_.pop_back();
    //         threadLogger_->info("全局路径最后一个位于实际终点后面，或者最后一个点就是终点，现予以去除");
    //     }
    //     else
    //     {
    //         threadLogger_->info("全局路径最后一个位于实际终点前面，不予以去除");
    //     }

    //     Trajectory_Point last_point;
    //     last_point.x = end_point_.x;
    //     last_point.y = end_point_.y;
    //     last_point.z = end_point_.z;
    //     last_point.yaw = end_point_.yaw;
    //     last_point.speed_limit = 0;
    //     last_point.left = 0;
    //     last_point.right = 0;
    //     last_point.speed = 0;
    //     last_point.curvature = 0;
    //     last_point.slope = 0;
    //     last_point.distance = 0;
    //     last_point.direction = global_path_.back().direction;
    //     global_path_.push_back(last_point);
    //     threadLogger_->info("将规划终点作为最后一个点添加进global_path的末尾");

    //     std::vector<Trajectory_Point> temp;
    //     temp = global_path_;
    //     // 对参考线进行随机偏移
    //     if (vehicle_param_.offset_enable == true)
    //     {
    //         threadLogger_->info("均匀碾压功能开启");

    //         global_path_.clear();
    //         for (int i = 0; i < temp.size(); i++)
    //         {
    //             temp.at(i).offset_flag = true; // 先将所有路径点的offset_flag属性设置为true
    //         }
    //         //
    //         设置temp中，每个点的offset_flag信息，来确定此次规划任务需要偏移的路段，true表示需要偏移，false表示不需要偏移
    //         for (int i = 0; i < temp.size(); i++)
    //         {
    //             if (temp.at(i).attribute == 6 || temp.at(i).attribute == 7)
    //             {
    //                 for (int j = i - 10; j < i + 10; j++)
    //                 {
    //                     if (j >= 0 && j < temp.size())
    //                     {
    //                         temp.at(j).offset_flag = false; // 将过磅点和洗车点左右10m设置为无需偏移的路段
    //                     }
    //                 }
    //             }
    //             if (temp.at(i).direction == 1)
    //             {
    //                 temp.at(i).offset_flag = false; // 将倒车的路段offset_flag也设置为false,即不需要进行偏移
    //             }
    //         }
    //         // threadLogger_->info("打印偏移属性信息");
    //         // for (int i = 0; i < temp.size(); i++)
    //         // {
    //         //     threadLogger_->info(temp.at(i).offset_flag);
    //         // }
    //         // threadLogger_->info("打印偏移属性信息结束");
    //         global_path_ = RandomOffsetWithoutCuravture(temp); // 不基于曲率的轨迹偏移

    //         if (global_path_.empty())
    //         {
    //             error_type_ = static_cast<uint>(ErrorType::OFFSET_FAIL);
    //             last_task_type_ = task_type_;
    //             return;
    //         }
    //         threadLogger_->info("RandomOffsetWithoutCuravture() successfully");
    //     }
    //     // 这步之前，已将路径点规划完毕，下面将为每个路点赋值速度、曲率、distance等属性
    //     CalDistance(global_path_); // 计算路径的位移信息
    //     threadLogger_->info("CalDistance() successfully");
    //     threadLogger_->info("...The length of the global path is {}", global_path_.back().distance);

    //     CalCurv(global_path_); //
    //     计算路径的曲率信息,建议打开，基于map.json和三次样条插值算出的曲率来计算，而不是直接用他们原始的曲率，因为三次样条插值算出的曲率变化不连续
    //     threadLogger_->info("CalCurv() successfully");
    //     Calrad2deg(global_path_);
    //     threadLogger_->info("Calrad2deg() successfully");
    //     // 根据曲率重新给弯道部分限速
    //     ReplanPointMaxSpeed(global_path_);
    //     std::ofstream file_out1;
    //     // file_out1.open("temp_data.txt");
    //     // for (size_t index = 0; index < global_path_.size(); index++)
    //     // {
    //     //     file_out1 << 0.0 << " " << global_path_.at(index).speed_limit << endl;
    //     // }
    //     // file_out1.close();
    //     threadLogger_->info("ReplanPointMaxSpeed() successfully");
    //     my_speed_planning_.threadLogger_ = threadLogger_;

    //     if (!my_speed_planning_.SpeedPlanning(global_path_, vehicle_param_))
    //     {
    //         threadLogger_->error("SpeedPlanning  failed !!!");

    //         error_type_ = static_cast<uint>(ErrorType::SPEED_PLANNING_FAIL);
    //     }
    //     threadLogger_->info("SpeedPlanning() end");

    //     // 路径前进点和倒车点属性检查，基于每个点的朝向和相邻点的向量的角度的偏差
    //     // CheckDirection();

    //     // 路径断裂检查
    //     if (checkPathFracture(global_path_))
    //     {
    //         threadLogger_->error("Path Fracture !!!");

    //         error_type_ = static_cast<uint>(ErrorType::PATH_FRACTURE);
    //         cout << "路径断裂" << endl;
    //         threadLogger_->error("路径断裂");
    //     }

    //     cout << "开始路径超速检查" << endl;
    //     // 路径断裂检查
    //     if (OverSpeedCheck(global_path_))
    //     {
    //         threadLogger_->error("speed over !!!");

    //         error_type_ = static_cast<uint>(ErrorType::SPEED_PLANNING_FAIL);
    //         cout << "路径超速" << endl;
    //         threadLogger_->error("路径超速");
    //     }
    //     cout << "路径超速检查完毕" << endl;

    //     // 删除重复点
    //     cout << "第二次去重检查" << endl;
    //     threadLogger_->info("第二次去重检查");
    //     std::vector<Trajectory_Point> temp2;
    //     temp2 = global_path_;
    //     removeDuplicates(temp2, global_path_);
    //     cout << "第二次去重检查完毕" << endl;
    //     threadLogger_->info("第二次去重检查完毕");
    //     CalDistance(global_path_); // 计算路径的位移信息

    //     path = global_path_;
    //     time(&end_time);
    //     threadLogger_->info("IDS_Global_Planning time(ms) = {} ms", (end_time - start_time));

    //     std::ofstream file_out;

    //     last_task_type_ = task_type_;
    return;
}

// void Planning::Calrad2deg(std::vector<Trajectory_Point> &temp_path)
// {
//     for (size_t index = 0; index < temp_path.size(); index++)
//     {
//         float temp_angle = temp_path.at(index).yaw;
//         temp_path.at(index).yaw = temp_angle / M_PI * 180;
//     }
// }

// /**
//  * @brief: 根据曲率对路径不同部分进行重新限速
//  * @param temp_path:传入路径
//  * @return 实现结果
//  */
// void Planning::ReplanPointMaxSpeed(std::vector<Trajectory_Point> &temp_path)
// {

//     // 先通过direction属性，将前进后退轨迹进行区分(direction 0:前进 1:后退),后退轨迹限速均为1m/s
//     std::vector<Trajectory_Point>::iterator iter = temp_path.begin();
//     // 三段式速度约束
//     for (; iter != temp_path.end(); iter++)
//     {
//         if (iter->direction == 0)
//         {
//             // 此时，该点为前进路径上的点
//             if (fabs(iter->curvature) < vehicle_param_.min_curvature)
//             {
//                 // 其绝对值<0.001(近似直线段) 限速5m/s-8.5m/s
//                 iter->speed_limit = vehicle_param_.max_speed_limit;
//             }
//             else if (vehicle_param_.min_curvature <= fabs(iter->curvature) && fabs(iter->curvature) <
//             vehicle_param_.max_curvature)
//             {
//                 // 其绝对值>0.01 <0.1 限速4m/s
//                 iter->speed_limit = vehicle_param_.mid_speed_limit;
//             }
//             else if (fabs(iter->curvature) >= vehicle_param_.max_curvature)
//             {
//                 // 其绝对值>0.01 限速3m/s
//                 iter->speed_limit = vehicle_param_.min_speed_limit;
//             }
//         }
//         else
//         {
//             // 此时，该点为后退路径上的点,后退轨迹限速均为2m/s
//             iter->speed_limit = vehicle_param_.reverse_speed;
//         }
//     }
//     // 基于道路属性的速度约束
//     if (vehicle_param_.multi_section_speed_limit_enable)
//     {
//         threadLogger_->info("基于路况的分段速度规划开启");

//         iter = temp_path.begin();
//         int tasktype = 1;
//         if (vehicle_param_.weather == 1) // 晴天
//         {
//             // 添加任务类型和路况决定的限速，与上面曲率计算出来的限速相结合，取小原则
//             if (task_type_ == static_cast<uint>(TaskType::GO_LOAD_POINT) || task_type_ ==
//             static_cast<uint>(TaskType::GO_LOAD_TRANSITIONS_POINT) || task_type_ ==
//             static_cast<uint>(TaskType::GO_LOADAREA_WAITAREA) || task_type_ ==
//             static_cast<uint>(TaskType::GO_PARKLOT_POINT) || task_type_ == static_cast<uint>(TaskType::GO_PARK_AREA))
//             // 空载情况
//             {
//                 for (; iter != temp_path.end(); iter++)
//                 {
//                     if (iter->direction == 0)
//                     {
//                         if (iter->attribute == 0) // 正常路
//                         {
//                             if (iter->speed_limit > vehicle_param_.light_regular_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.light_regular_road_speed_limit;
//                         }
//                         else if (iter->attribute == 1) // 窄路
//                         {
//                             if (iter->speed_limit > vehicle_param_.light_narrow_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.light_narrow_road_speed_limit;
//                         }
//                         else if (iter->attribute == 2) // 路口
//                         {
//                             if (iter->speed_limit > vehicle_param_.light_intersection_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.light_intersection_road_speed_limit;
//                         }
//                         else if (iter->attribute == 3) // 坡路
//                         {
//                             if (iter->speed_limit > vehicle_param_.light_slope_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.light_slope_road_speed_limit;
//                         }
//                         else if (iter->attribute == 4) // 颠簸路
//                         {
//                             if (iter->speed_limit > vehicle_param_.light_bumpy_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.light_bumpy_road_speed_limit;
//                         }
//                         else if (iter->attribute == 5) // 水泥路
//                         {
//                             if (iter->speed_limit > vehicle_param_.light_regular_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.light_regular_road_speed_limit;
//                         }
//                         else
//                         {
//                         }
//                     }
//                     else
//                     {
//                         // 此时，该点为后退路径上的点,后退轨迹限速均为2m/s
//                         iter->speed_limit = vehicle_param_.reverse_speed;
//                     }
//                 }
//             }
//             else // 满载情况
//             {
//                 for (; iter != temp_path.end(); iter++)
//                 {
//                     if (iter->direction == 0)
//                     {
//                         if (iter->attribute == 0) // 正常路
//                         {
//                             if (iter->speed_limit > vehicle_param_.heavy_regular_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.heavy_regular_road_speed_limit;
//                         }
//                         else if (iter->attribute == 1) // 窄路
//                         {
//                             if (iter->speed_limit > vehicle_param_.heavy_narrow_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.heavy_narrow_road_speed_limit;
//                         }
//                         else if (iter->attribute == 2) // 路口
//                         {
//                             if (iter->speed_limit > vehicle_param_.heavy_intersection_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.heavy_intersection_road_speed_limit;
//                         }
//                         else if (iter->attribute == 3) // 坡路
//                         {
//                             if (iter->speed_limit > vehicle_param_.heavy_slope_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.heavy_slope_road_speed_limit;
//                         }
//                         else if (iter->attribute == 4) // 颠簸路
//                         {
//                             if (iter->speed_limit > vehicle_param_.heavy_bumpy_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.heavy_bumpy_road_speed_limit;
//                         }
//                         else if (iter->attribute == 5) // 水泥路
//                         {
//                             if (iter->speed_limit > vehicle_param_.heavy_regular_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.heavy_regular_road_speed_limit;
//                         }
//                         else
//                         {
//                         }
//                     }
//                     else
//                     {
//                         // 此时，该点为后退路径上的点,后退轨迹限速均为2m/s
//                         iter->speed_limit = vehicle_param_.reverse_speed;
//                     }
//                 }
//             }
//         }
//         else // 雨天、雪天
//         {
//             // 添加任务类型和路况决定的限速，与上面曲率计算出来的限速相结合，取小原则
//             if (task_type_ == static_cast<uint>(TaskType::GO_LOAD_POINT) || task_type_ ==
//             static_cast<uint>(TaskType::GO_LOADAREA_WAITAREA) || task_type_ ==
//             static_cast<uint>(TaskType::GO_PARKLOT_POINT) || task_type_ == static_cast<uint>(TaskType::GO_PARK_AREA))
//             // 空载情况
//             {
//                 for (; iter != temp_path.end(); iter++)
//                 {
//                     if (iter->direction == 0)
//                     {
//                         if (iter->attribute == 0) // 正常路
//                         {
//                             if (iter->speed_limit > vehicle_param_.light_regular_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.light_regular_road_speed_limit;
//                         }
//                         else if (iter->attribute == 1) // 窄路
//                         {
//                             if (iter->speed_limit > vehicle_param_.light_narrow_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.light_narrow_road_speed_limit;
//                         }
//                         else if (iter->attribute == 2) // 路口
//                         {
//                             if (iter->speed_limit > vehicle_param_.light_intersection_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.light_intersection_road_speed_limit;
//                         }
//                         else if (iter->attribute == 3) // 坡路
//                         {
//                             if (iter->speed_limit > vehicle_param_.light_slope_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.light_slope_road_speed_limit;
//                         }
//                         else if (iter->attribute == 4) // 颠簸路
//                         {
//                             if (iter->speed_limit > vehicle_param_.light_bumpy_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.light_bumpy_road_speed_limit;
//                         }
//                         else if (iter->attribute == 5) // 水泥路
//                         {
//                             if (iter->speed_limit > vehicle_param_.light_regular_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.light_regular_road_speed_limit;
//                         }
//                         else
//                         {
//                         }
//                     }
//                     else
//                     {
//                         // 此时，该点为后退路径上的点,后退轨迹限速均为2m/s
//                         iter->speed_limit = vehicle_param_.reverse_speed;
//                     }
//                 }
//             }
//             else // 满载情况
//             {
//                 for (; iter != temp_path.end(); iter++)
//                 {
//                     if (iter->direction == 0)
//                     {
//                         if (iter->attribute == 0) // 正常路
//                         {
//                             if (iter->speed_limit > vehicle_param_.heavy_regular_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.heavy_regular_road_speed_limit;
//                         }
//                         else if (iter->attribute == 1) // 窄路
//                         {
//                             if (iter->speed_limit > vehicle_param_.heavy_narrow_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.heavy_narrow_road_speed_limit;
//                         }
//                         else if (iter->attribute == 2) // 路口
//                         {
//                             if (iter->speed_limit > vehicle_param_.heavy_intersection_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.heavy_intersection_road_speed_limit;
//                         }
//                         else if (iter->attribute == 3) // 坡路
//                         {
//                             if (iter->speed_limit > vehicle_param_.heavy_slope_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.heavy_slope_road_speed_limit;
//                         }
//                         else if (iter->attribute == 4) // 颠簸路
//                         {
//                             if (iter->speed_limit > vehicle_param_.heavy_bumpy_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.heavy_bumpy_road_speed_limit;
//                         }
//                         else if (iter->attribute == 5) // 水泥路
//                         {
//                             if (iter->speed_limit > vehicle_param_.heavy_regular_road_speed_limit)
//                                 iter->speed_limit = vehicle_param_.heavy_regular_road_speed_limit;
//                         }
//                         else
//                         {
//                         }
//                     }
//                     else
//                     {
//                         // 此时，该点为后退路径上的点,后退轨迹限速均为2m/s
//                         iter->speed_limit = vehicle_param_.reverse_speed;
//                     }
//                 }
//             }
//         }
//     }

//     threadLogger_->info("s_curve_speed_limit:{}", vehicle_param_.s_curve_speed_limit);

//     if (vehicle_param_.s_curve_speed_limit)
//     {
//         std::ofstream file_out;
//         // file_out.open("speed_limit_before.txt");
//         // for (size_t index = 0; index < temp_path.size(); index++)
//         // {
//         //     file_out << 0.0 << " " << temp_path.at(index).speed_limit << endl;
//         // }
//         // file_out.close();

//         // 遍历整个temp_path，检核每个点的限速是否合理；根据方向盘最大转速以及每个点的瞬时曲率来确定每个点的合理限速
//         // vector<float> vec_exceeding_speed_index; // 存放整条路径中限速超标的点的索引
//         float L_vehicle = 5.95;
//         float max_Steering_wheel_speed = 0.175;
//         float temp_max_speed;
//         float wheel_delta_angle, wheel_angle1, wheel_angle2;
//         float sampling_distance = 1;
//         vector<float> vec_temp_max_speed; // 记录全局路径上基于曲率变化算出限速信息
//         threadLogger_->info("打印temp_max_speed信息");

//         for (int i = 0; i < temp_path.size() - 1; i++) //
//         {
//             wheel_angle1 = atan(L_vehicle * temp_path.at(i).curvature);
//             wheel_angle2 = atan(L_vehicle * temp_path.at(i + 1).curvature);
//             temp_max_speed = sampling_distance * max_Steering_wheel_speed / (fabs(wheel_angle1 - wheel_angle2) +
//             eps); // 根据控制给的方向盘最高转速和预定的采样距离算出的每个点的最大限速 if (temp_max_speed >= 10)
//                 temp_max_speed = 10;
//             vec_temp_max_speed.push_back(temp_max_speed);
//         }

//         for (int i = 0; i < vec_temp_max_speed.size(); i++)
//         {
//             if (vec_temp_max_speed.at(i) < temp_path.at(i).speed_limit)
//             {
//                 if (temp_path.at(i).direction == 0)
//                 {
//                     temp_path.at(i).speed_limit = vec_temp_max_speed.at(i);
//                     // 为了便于控制跟踪，将i附近的10(10m)路径点限速也降低i为vec_temp_max_speed.at(i)
//                     for (int j = i - 5; j < i + 5; j++)
//                     {
//                         if (j >= 0 && j < vec_temp_max_speed.size())
//                         {
//                             if (temp_path.at(j).direction == 0)
//                             {
//                                 temp_path.at(j).speed_limit = vec_temp_max_speed.at(i);
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//         // std::ofstream file_out;
//         // file_out.open("speed_limit_after.txt");
//         // for (size_t index = 0; index < temp_path.size(); index++)
//         // {
//         //     file_out << 0.0 << " " << temp_path.at(index).speed_limit << endl;
//         // }
//         // file_out.close();
//     }
//     // 再添加一个曲率约束
//     for (; iter != temp_path.end(); iter++)
//     {
//         if (iter->speed_limit > sqrt(0.2 / fabs(iter->curvature)))
//         {
//             iter->speed_limit = sqrt(0.2 / fabs(iter->curvature));
//         }
//     }
// }

// 将路点信息转换为json格式 返回给调用方
string Planning::VecWaypoint2json(vector<_TrajectoryPoint>& vec_wp) {
    cout << "enter VecWaypoint2json" << endl;
    threadLogger_->info("enter VecWaypoint2json");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cout << "VecWaypoint2json..." << endl;
    threadLogger_->info("VecWaypoint2json...");

    if (error_type_ > 0) {
        threadLogger_->error("error_type_:{}", (int)error_type_);
        threadLogger_->error("有错误");
        cout << "即将返回特殊轨迹给后台" << endl;
        vec_wp.clear();
    }

    time_t start_time, end_time;
    time(&start_time);
    rapidjson::StringBuffer                    strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    threadLogger_->info("开始写json");
    cout << "开始写json" << endl;
    writer.StartObject();

    writer.Key("trajectory_info");
    writer.StartArray();
    if (vec_wp.size() == 0) {
        writer.StartObject();
        writer.Key("x");
        writer.Double(0.0);

        writer.Key("y");
        writer.Double(0.0);

        writer.Key("z");
        writer.Double(0.0);

        writer.Key("yaw");
        writer.Double(0.0);

        writer.Key("curvature");
        writer.Double(0.0);

        writer.Key("speed");
        writer.Double(0.0);

        writer.Key("distance");
        writer.Double(0.0);

        writer.Key("attribute");
        writer.Uint(0);

        writer.Key("speed_limit");
        writer.Double(0.0);

        writer.Key("direction");
        writer.Int(0);
        writer.EndObject();
    }

    for (size_t i = 0; i < vec_wp.size(); i++) {
        writer.StartObject();
        writer.Key("x");
        writer.Double(vec_wp.at(i).x);

        writer.Key("y");
        writer.Double(vec_wp.at(i).y);

        writer.Key("z");
        writer.Double(vec_wp.at(i).z);

        writer.Key("yaw");
        writer.Double(vec_wp.at(i).yaw);

        writer.Key("curvature");
        writer.Double(vec_wp.at(i).curvature);

        writer.Key("speed");
        writer.Double(vec_wp.at(i).speed);

        writer.Key("distance");
        writer.Double(vec_wp.at(i).distance);

        writer.Key("attribute");
        writer.Uint(vec_wp.at(i).attribute);

        writer.Key("speed_limit");
        writer.Double(vec_wp.at(i).speed_limit);

        writer.Key("direction");
        writer.Int(vec_wp.at(i).direction);
        writer.EndObject();
    }
    writer.EndArray();

    writer.Key("vec_path_");
    writer.StartArray();
    // if (zone_sequence_.size() == 0)
    // {
    //     writer.Uint(start_node_);
    // }
    // else
    // {
    //     for (size_t j = 0; j < zone_sequence_.size(); j++)
    //     {
    //         writer.Uint(zone_sequence_.at(j));
    //     }
    // }

    writer.EndArray();

    writer.Key("error_type_");
    writer.Uint(error_type_);
    // writer.Key("ID");
    // writer.String(vehicle_code_.c_str(), vehicle_code_.size());

    writer.EndObject();
    threadLogger_->info("writer.EndObject()");
    cout << "writer.EndObject()" << endl;

    GlobalVariable::getInstance()->global_str = strbuf.GetString();
    auto              currentTime             = std::chrono::system_clock::now();
    std::time_t       timestamp               = std::chrono::system_clock::to_time_t(currentTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
    std::string timeStr = ss.str();

    // 构造文件路径
    std::string filePath = timeStr + "_" + vehicle_code_ + "_output.json";

    ofstream outputFile(filePath);
    // 将JSON数据写入文件
    outputFile << GlobalVariable::getInstance()->global_str;
    // 关闭文件流
    outputFile.close();

    threadLogger_->info("规划库服务结束 ");
    cout << "规划库成功返回轨迹，欢迎下次光临" << endl;
    time(&end_time);
    threadLogger_->info("VecWaypoint2json time(ms) ={} ms ", (end_time - start_time));
    {
        std::unique_lock<std::shared_mutex> lock(GlobalVariable::getInstance()->record_file_write_lock);
        std::ofstream                       record;
        record.open("record.txt", std::ios_base::app);
        record << timeStr << " ，处理完规划请求，请求号：" << key_ << "，车辆编号：" << vehicle_code_ << endl;
        record.close();
    }

    return GlobalVariable::getInstance()->global_str;
}

// // 区域内临时挪车
// ErrorType Planning::PlanningCase7()
// {
//     threadLogger_->info("Enter PlanningCase7");
//     global_path_.clear();
//     std::vector<Trajectory_Point> temp_trajectory;
//     // rule_id:5n前向规划失败，换rule_id:0的普通规划
//     if (!ApplyHibridAStar(start_point_, end_point_, start_node_, temp_trajectory, 5))
//     {
//         threadLogger_->error("Hybird A*无法规划出当前起点至终点的路径");
//         return ErrorType::PLANNING_FAIL;
//         // 反馈hybird A*直接搜索起点到终点的失败error
//     }
//     global_path_.insert(global_path_.end(), temp_trajectory.begin(), temp_trajectory.end());
//     return ErrorType::SUCCESS;
// }
// ErrorType Planning::PlanningCase8()
// {
//     threadLogger_->info("Enter PlanningCase8");

//     global_path_.clear();
//     std::vector<Trajectory_Point> temp_trajectory;
//     // rule_id:5n前向规划失败，换rule_id:0的普通规划
//     if (!ApplyHibridAStar(start_point_, end_point_, vec_path_, temp_trajectory, 0))
//     {
//         threadLogger_->error("Hybird A*无法规划出当前起点至终点的路径");

//         return ErrorType::PLANNING_FAIL;
//         // 反馈hybird A*直接搜索起点到终点的失败error
//     }

//     global_path_.insert(global_path_.end(), temp_trajectory.begin(), temp_trajectory.end());
//     return ErrorType::SUCCESS;
// }
// // 前往装载点
// ErrorType Planning::PlanningCase9()
// {

//     threadLogger_->info("Enter PlanningCase9");

//     global_path_.clear();
//     // vehicle_param_.end_offset_distance = 4.0;
//     // vehicle_param_.start_offset_distance = 4.0;
//     std::vector<Trajectory_Point> temp_trajectory;
//     // rule_id:5n前向规划失败，换rule_id:0的普通规划

//     if (!ApplyHibridAStar(start_point_, end_point_, start_node_, temp_trajectory, 2))
//     {
//         threadLogger_->error("Hybird A*无法规划出当前起点至终点的路径");

//         return ErrorType::TOO_CLOSE_TO_LOADING_POINT;
//         // 反馈hybird A*直接搜索起点到终点的失败error
//     }
//     // 反馈hybird A*直接搜索起点到终点的失败error

//     // if (!ApplyHibridAStar(start_point_, end_point_, start_node_, temp_trajectory, 4))
//     // {
//     //     threadLogger_->error("纯倒车不行，先往前开开，再倒车");

//     //     if (!ApplyHibridAStar(start_point_, end_point_, start_node_, temp_trajectory, 2))
//     //     {
//     //         threadLogger_->error("Hybird A*无法规划出当前起点至终点的路径");

//     //         return ErrorType::TOO_CLOSE_TO_LOADING_POINT;
//     //         // 反馈hybird A*直接搜索起点到终点的失败error
//     //     }
//     //     // 反馈hybird A*直接搜索起点到终点的失败error
//     // }

//     global_path_.insert(global_path_.end(), temp_trajectory.begin(), temp_trajectory.end());
//     return ErrorType::SUCCESS;
// }

// ErrorType Planning::PlanningCase10() // 前往驶离装载点
// {
//     threadLogger_->info("Enter PlanningCase10");

//     global_path_.clear();
//     std::vector<Trajectory_Point> temp_trajectory;
//     // rule_id:5n前向规划失败，换rule_id:0的普通规划
//     if (!ApplyHibridAStar(start_point_, end_point_, start_node_, temp_trajectory, 5))
//     {
//         threadLogger_->error("Hybird A*无法规划出当前起点至终点的路径");

//         return ErrorType::TOO_CLOSE_TO_LOADING_POINT;
//         // 反馈hybird A*直接搜索起点到终点的失败error
//     }

//     global_path_.insert(global_path_.end(), temp_trajectory.begin(), temp_trajectory.end());

//     // 针对这种情况进行特殊检查,temp_trajectory可能饶了一个大圈，也可能走了一条蛇形路线，这两种情况不可以输出轨迹
//     // 如果temp_trajectory
//     return ErrorType::SUCCESS;
//     threadLogger_->info("Enter PlanningCase10");
// }
// /**
//  * @brief 起始点和终止点在同一区域，且该区域为结构化道路
//  * @param [in] 无
//  * @param [return] true: 规划成功；false：规划失败
//  */
// ErrorType Planning::PlanningCase1() //
// 暂时只考虑单车道的场景，后续扩展为多车道需修改函数PlanningCase1()到PlanningCase6()
// {
//     threadLogger_->info("Enter PlanningCase1");

//     ErrorType temp_error_type;
//     unsigned int start_nearest_id;
//     unsigned int end_nearest_id;
//     uint8 start_path_id = -1;
//     uint8 end_path_id = -1;
//     global_path_.clear();
//     map<uint8, double> v_id_start, v_id_end;
//     vector<Single_Trajectory> temp_all_trajectories;

//     temp_all_trajectories = all_zones_.at(start_node_ - 1).reference_trajs;

//     if (temp_all_trajectories.size()) // 区域内有参考路径才进行后续的规划
//     {
//         zone_sequence_.clear();
//         threadLogger_->info("寻找当前规划起点的对应参考路径");
//         threadLogger_->info(" ");

//         double dis = 0; // 初始搜索半径20m
//         vector<double> dis_v = {20, 10, 8, 6, 4, 2, 1, 0.4};
//         // 采用循环的方式，从大半径到小半径，依次超找共同的参考路径
//         int same_road_num = 100;
//         int index_dis = 0;
//         while (same_road_num > 1 && index_dis <= dis_v.size() - 1)
//         {
//             dis = dis_v.at(index_dis);
//             index_dis++;
//             threadLogger_->info("planningcase1  当前搜索半径：{}", dis);
//             temp_error_type = FindReferencePath(start_point_, temp_all_trajectories, start_nearest_id, start_path_id,
//             true, v_id_start, dis); if (temp_error_type != ErrorType::SUCCESS) // 找到区域内与起始点最近的参考路径
//             {
//                 threadLogger_->error("...Planningcase1 起点没找到对应的参考线...");
//                 return temp_error_type;
//             }

//             threadLogger_->info("寻找当前规划终点的对应参考路径");
//             threadLogger_->info(" ");
//             temp_error_type = FindReferencePath(end_point_, temp_all_trajectories, end_nearest_id, end_path_id,
//             false, v_id_end, dis); if (temp_error_type != ErrorType::SUCCESS) // 找到区域内与目标点最近的参考路径
//             {
//                 threadLogger_->error("...Planningcase1 终点没找到对应的参考线...");
//                 return temp_error_type;
//             }

//             threadLogger_->info("v_id_start 信息如下");
//             for (const auto &pair : v_id_start)
//                 threadLogger_->info(pair.first);
//             threadLogger_->info("v_id_end 信息如下");
//             for (const auto &pair : v_id_end)
//                 threadLogger_->info(pair.first);

//             same_road_num = 0;
//             std::unordered_set<uint8> ids;
//             for (const auto &pair : v_id_start)
//                 ids.insert(pair.first);

//             for (const auto &pair : v_id_end)
//             {
//                 if (ids.count(pair.first))
//                 {
//                     same_road_num++;
//                 }
//             }

//             threadLogger_->info("找到{}条共同的参考路径", same_road_num);
//         }
//         if (same_road_num == 0)
//         {
//             return ErrorType::START_POINT_UNREASONABLE;
//         }

//         // 从v_id_start和v_id_end中找出共同的道路id,如果共同参考路径超过1条，以起点匹配上的为准
//         bool find_same_road = false;
//         int sum = 0;
//         std::unordered_set<uint8> ids;
//         vector<uint8> same_id_road;
//         for (const auto &pair : v_id_start)
//             ids.insert(pair.first);

//         for (const auto &pair : v_id_end)
//         {
//             if (ids.count(pair.first))
//             {
//                 sum++;
//                 same_id_road.push_back(pair.first);
//             }
//         }
//         if (sum == 1)
//         {
//             for (const auto &pair : v_id_end)
//             {
//                 if (ids.count(pair.first))
//                 {
//                     start_path_id = pair.first;
//                     start_nearest_id = 0; // 先暂时将 起点、终点的匹配index设置为0
//                     end_path_id = pair.first;
//                     end_nearest_id = 0;
//                     find_same_road = true;
//                     break;
//                 }
//             }
//         }
//         else
//         {
//             // 起点、终点附近参考路径比较密集
//             double min_dis = 10000;
//             double index = -1;
//             for (int i = 0; i < same_id_road.size(); i++)
//             {
//                 if (v_id_start.at(same_id_road.at(i)) < min_dis)
//                 {
//                     min_dis = v_id_start.at(same_id_road.at(i));
//                     index = i;
//                 }
//             }
//             start_path_id = same_id_road.at(index);
//             start_nearest_id = 0; // 先暂时将 起点、终点的匹配index设置为0
//             end_path_id = start_path_id;
//             end_nearest_id = 0;
//             find_same_road = true;
//         }

//         if (!find_same_road)
//         {
//             return ErrorType::REFERENCELINE_LOSS;
//         }
//         threadLogger_->info("start_path_id:{}, end_path_id:{}", start_path_id, end_path_id);

//         // 开始为start_nearest_id和end_nearest_id确定准确的值
//         Single_Trajectory start_trajectory;
//         Trajectory_Point temp_point;
//         float64 distance_min = 1000000;
//         start_trajectory = temp_all_trajectories.at(start_path_id);
//         for (unsigned int i = 0; i < start_trajectory.trajectory.size(); i++)
//         {
//             temp_point = start_trajectory.trajectory.at(i);

//             if (pow(start_point_.x - temp_point.x, 2) + pow(start_point_.y - temp_point.y, 2) < distance_min)
//             {
//                 distance_min = pow(start_point_.x - temp_point.x, 2) + pow(start_point_.y - temp_point.y, 2);
//                 start_nearest_id = i;
//             }
//         }
//         threadLogger_->info("start_nearest_id:{}, distance:{}", start_nearest_id, sqrt(distance_min));

//         Single_Trajectory end_trajectory;
//         distance_min = 1000000;
//         end_trajectory = temp_all_trajectories.at(start_path_id);
//         for (unsigned int j = 0; j < end_trajectory.trajectory.size(); j++)
//         {
//             temp_point = end_trajectory.trajectory.at(j);

//             if (pow(end_point_.x - temp_point.x, 2) + pow(end_point_.y - temp_point.y, 2) < distance_min)
//             {
//                 distance_min = pow(end_point_.x - temp_point.x, 2) + pow(end_point_.y - temp_point.y, 2);
//                 end_nearest_id = j;
//             }
//         }
//         threadLogger_->info("end_nearest_id:{}, distance:{}", end_nearest_id, sqrt(distance_min));

//         // 计算规划起点与规划终点与对于参考线的位置关系，以此来判断是否需要对其进行hybird A*拼接
//         bool start_flag = false, end_flag = false;
//         threadLogger_->info("起点匹配上的参考轨迹ID：{}  ,索引：{}", float(start_path_id + 1), start_nearest_id);
//         threadLogger_->info("起点所在 的参考轨迹总长：{} ", start_trajectory.trajectory.size());
//         threadLogger_->info("终点匹配上的参考轨迹ID： {}, 索引：{}", float(end_path_id + 1), end_nearest_id);
//         threadLogger_->info("终点所在的参考轨迹总长：{} ", end_trajectory.trajectory.size());

//         // 判断规划点与其对应参考线的位置关系，横向距离小于阈值，且偏差角度小于10°的，不需要hybird A*进行轨迹拼接
//         float lat_distance = 0.0;
//         threadLogger_->info("判断终点是否需要进行hybirdA*规划");
//         end_flag = DetermineIfOrNoHybirdAStar(end_point_, end_trajectory.trajectory, end_nearest_id, lat_distance);
//         threadLogger_->info("判断起点是否需要进行hybirdA*规划");
//         start_flag = DetermineIfOrNoHybirdAStar(start_point_, start_trajectory.trajectory, start_nearest_id,
//         lat_distance);
//         // 根据起点和终点
//         // 计算规划起点与规划终点与对于参考线起点、终点的几何距离，部分情况需要跨区域搜索拟合点
//         bool start_point_to_next_area = false, end_point_to_pre_area = false;
//         distance_min = 1000000;
//         unsigned int temp_distance;

//         temp_distance = fabs(start_trajectory.trajectory.size() - start_nearest_id); // 每个index代表1m
//         if (temp_distance < 37)                                                      //
//         37m是矿卡能够正常规划的极限距离
//         {
//             threadLogger_->info("start_point_to_next_area = true");
//             start_point_to_next_area = true;
//         }
//         temp_distance = fabs(end_nearest_id);
//         if (temp_distance < 37)
//         {
//             threadLogger_->info("end_point_to_pre_area = true");
//             end_point_to_pre_area = true;
//         }

//         std::vector<Trajectory_Point> temp_tra_start, temp_tra_end; // 分别存储起点、终点处的hybirdA*拼接轨迹
//         // 起始点和目标点在同一路径上
//         int32 Splice_Point_start_index = -1; //
//         起点横向偏离参考轨迹较大，拟合轨迹终点的索引，下一区域拼接轨迹时，轨迹拼接的起点 int32 Splice_Point_end_index
//         = -1;   // 终点横向偏离参考轨迹较大，拟合轨迹起点的索引，下一区域拼接轨迹时，轨迹拼接的终点

//         threadLogger_->info("【起点、终点位于同一参考轨迹】");

//         vector<Trajectory_Point> temp_traj = temp_all_trajectories.at(start_path_id).trajectory;

//         int distance_threshold = 2;
//         if (end_nearest_id < start_nearest_id) // 需要倒车
//         {
//             if (start_nearest_id - end_nearest_id > 20)
//             {
//                 threadLogger_->info("【起点、终点位于同一参考轨迹且起点在终点前，距离超过20m，需要倒车，不安全任务，不予以规划】");
//                 return ErrorType::NO_LONG_DISTANCE_BACK;
//             }
//             else
//             {
//                 threadLogger_->info("【起点、终点位于同一参考轨迹且起点在终点前，需要倒车，鉴于距离小于20m，规划库予以规划】");
//                 if (start_flag)
//                 {
//                     return ErrorType::START_POINT_UNREASONABLE;
//                 }
//                 if (end_flag)
//                 {
//                     return ErrorType::END_POINT_UNREASONABLE;
//                 }
//                 std ::vector<Trajectory_Point> reverse_tra;
//                 reverse_tra.insert(reverse_tra.end(), temp_traj.begin() + end_nearest_id, temp_traj.begin() +
//                 start_nearest_id + 1); reverse(reverse_tra.begin(), reverse_tra.end()); reverse_flag_ = true;
//                 global_path_.insert(global_path_.end(), reverse_tra.begin(), reverse_tra.end());
//             }
//         }
//         else if (end_nearest_id > start_nearest_id) //  【起点、终点位于同一参考轨迹且起点在终点后】
//         {
//             threadLogger_->info("【起点、终点位于同一参考轨迹且起点在终点后】");

//             if (start_flag)
//             {
//                 threadLogger_->info("起点经过判定需要采用Hybird A*进行拟合");

//                 // 参数顺序解释：输入点、hybird
//                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                 uint8 hybird_rule_id = 5;

//                 if (!ProgressiveHybirdAStar(start_point_, start_node_, true, start_trajectory.trajectory,
//                 start_nearest_id, Splice_Point_start_index, temp_tra_start, hybird_rule_id))
//                 {
//                     // 反馈规划起点附近hybird A*轨迹拼接失败
//                     threadLogger_->info("规划起点附近hybird A*轨迹拼接失败");

//                     return ErrorType::PLANNING_FAIL;
//                 }
//             }
//             else
//             {
//                 threadLogger_->info("起点经过判定不需要采用Hybird A*进行拟合");
//             }
//             if (end_flag)
//             {
//                 threadLogger_->info("终点经过判定需要采用Hybird A*进行拟合");

//                 // 参数顺序解释：输入点、hybird
//                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                 uint8 hybird_rule_id = 5;

//                 if (!ProgressiveHybirdAStar(end_point_, end_node_, false, end_trajectory.trajectory, end_nearest_id,
//                 Splice_Point_end_index, temp_tra_end, hybird_rule_id))
//                 {
//                     // 反馈规划终点附近hybird A*轨迹拼接失败
//                     threadLogger_->info("规划终点附近hybird A*轨迹拼接失败");

//                     return ErrorType::PLANNING_FAIL;
//                 }
//             }
//             else
//             {
//                 threadLogger_->info("终点经过判定不需要采用Hybird A*进行拟合");
//             }
//             // 分析以上两个ProgressiveHybirdAStar算出的轨迹拼接点是否合理
//             if (Splice_Point_start_index > Splice_Point_end_index && Splice_Point_end_index > 0)
//             {
//                 threadLogger_->info("起点与终点两者搜索出的拟合轨迹点位置存在冲突");

//                 // 反馈搜索出的两个轨迹拼接点存在冲突的error
//                 return ErrorType::PLANNING_FAIL;
//             }

//             if (start_flag)
//             {
//                 if (end_flag)
//                 {
//                     global_path_.insert(global_path_.end(), temp_tra_start.begin(), temp_tra_start.end());
//                     global_path_.insert(global_path_.end(), temp_traj.begin() + Splice_Point_start_index + 1,
//                     temp_traj.begin() + Splice_Point_end_index); global_path_.insert(global_path_.end(),
//                     temp_tra_end.begin(), temp_tra_end.end());
//                 }
//                 else
//                 {
//                     global_path_.insert(global_path_.end(), temp_tra_start.begin(), temp_tra_start.end());
//                     global_path_.insert(global_path_.end(), temp_traj.begin() + Splice_Point_start_index + 1,
//                     temp_traj.begin() + end_nearest_id + 1);
//                 }
//             }
//             else
//             {
//                 if (end_flag)
//                 {
//                     global_path_.insert(global_path_.end(), temp_traj.begin() + start_nearest_id, temp_traj.begin() +
//                     Splice_Point_end_index); global_path_.insert(global_path_.end(), temp_tra_end.begin(),
//                     temp_tra_end.end());
//                 }
//                 else
//                 {
//                     global_path_.insert(global_path_.end(), temp_traj.begin() + start_nearest_id, temp_traj.begin() +
//                     end_nearest_id + 1);
//                 }
//             }
//         }
//         else // 起点终点相距很近
//         {
//             Trajectory_Point p1, p2;
//             p1.x = start_point_.x;
//             p1.y = start_point_.y;
//             p1.z = start_point_.z;
//             p1.yaw = start_point_.yaw;
//             p1.speed_limit = 0;
//             p1.left = 0;
//             p1.right = 0;
//             p1.speed = 0;
//             p1.curvature = 0;
//             p1.slope = 0;
//             p1.distance = 0;

//             p2.x = end_point_.x;
//             p2.y = end_point_.y;
//             p2.z = end_point_.z;
//             p2.yaw = end_point_.yaw;
//             p2.speed_limit = 0;
//             p2.left = 0;
//             p2.right = 0;
//             p2.speed = 0;
//             p2.curvature = 0;
//             p2.slope = 0;
//             float dis = sqrt(pow(start_point_.x - end_point_.x, 2) + pow(end_point_.y - start_point_.y, 2));
//             p2.distance = dis;
//             float64 angle;
//             angle = atan2(end_point_.y - start_point_.y, end_point_.x - start_point_.x);
//             if (angle < 0)
//             {
//                 angle += 2 * M_PI;
//             }
//             if (fabs(angle - start_point_.yaw) / M_PI * 180 < 90 || fabs(angle - start_point_.yaw) / M_PI * 180 >
//             270)
//             {
//                 p1.direction = 0;
//                 p2.direction = 0;
//             }
//             else
//             {
//                 p1.direction = 1;
//                 p2.direction = 1;
//             }

//             global_path_.push_back(p1);
//             global_path_.push_back(p2);
//             threadLogger_->info("超近距离规划");
//         }

//         return ErrorType::SUCCESS;
//     }
//     else
//     {
//         threadLogger_->info("此结构化区域无参考轨迹");
//         return ErrorType::NO_REFERENCELINE;
//     }
// }

// /**
//  * @brief 起始点和终止点在同一区域，且该区域为非结构化道路
//  * @param [in] 无
//  * @param [return] true: 规划成功；false：规划失败
//  */
// ErrorType Planning::PlanningCase2()
// {
//     threadLogger_->info("Enter PlanningCase2");

//     vector<Trajectory_Point> temp_traj;
//     uint8 rule;
//     global_path_.clear();
//     if (task_type_ == static_cast<uint>(TaskType::GO_LOADAREA_WAITAREA) || task_type_ ==
//     static_cast<uint>(TaskType::GO_UNLOADAREA_WAITAREA))
//         rule = 5;
//     else
//         rule = 2;
//     cout << "rule:" << (int)rule << endl;
//     if (ApplyHibridAStar(start_point_, end_point_, start_node_, temp_traj, rule)) // 只允许倒车规划
//     {
//         global_path_ = temp_traj;
//         return ErrorType::SUCCESS;
//     }
//     else
//     {
//         threadLogger_->error(" Hybrid A star in zone{} failed ", static_cast<float>(start_node_));
//         return ErrorType::PLANNING_FAIL;
//     }
// }

// /**
//  * @brief 起始点和终止点不在同一区域，且起点、终点为结构化道路
//  * @param [in] 无
//  * @param [return] true: 规划成功；false：规划失败
//  */
// ErrorType Planning::PlanningCase3()
// {
//     threadLogger_->info("Enter PlanningCase3");

//     ErrorType temp_error_type;
//     map<uint8, double> v_id;
//     if (zone_sequence_.size() < 2) // planningcase3不会出现此情况
//     {
//         return ErrorType::PLANNING_FAIL;
//     }
//     global_path_.clear();                    // 清空全局轨迹容器
//     uint8 start_path_id, end_path_id;        // 记录规划起点、规划终点在其对应结构化区域内的参考线索引
//     unsigned int start_nearest_id, end_nearest_id; // 记录规划起点、规划终点在参考线上的投影点索引
//     vector<Single_Trajectory> start_all_trajectories, end_all_trajectories;
//     start_all_trajectories = all_zones_.at(start_node_ - 1).reference_trajs;
//     end_all_trajectories = all_zones_.at(end_node_ - 1).reference_trajs;
//     if (start_all_trajectories.size() && end_all_trajectories.size()) // 区域内均有参考路径才进行后续的规划
//     {
//         threadLogger_->info("寻找当前规划起点的对应参考路径");
//         threadLogger_->info(" ");

//         temp_error_type = FindReferencePath(start_point_, start_all_trajectories, start_nearest_id, start_path_id,
//         true, v_id, 0); if (temp_error_type != ErrorType::SUCCESS) // 找到区域内与起始点最近的参考路径
//         {
//             threadLogger_->error("...Failed to find the nearest point for the start point...");

//             return temp_error_type;
//         }
//         threadLogger_->info("寻找当前规划终点的对应参考路径");
//         threadLogger_->info(" ");

//         temp_error_type = FindReferencePath(end_point_, end_all_trajectories, end_nearest_id, end_path_id, false,
//         v_id, 0); if (temp_error_type != ErrorType::SUCCESS) // 找到区域内与目标点最近的参考路径
//         {
//             threadLogger_->error("...Failed to find the nearest point for the end point...");

//             return temp_error_type;
//         }
//         // 记录规划起点、规划终点的参考路径
//         Single_Trajectory start_trajectory, end_trajectory;
//         start_trajectory = start_all_trajectories.at(start_path_id);
//         end_trajectory = end_all_trajectories.at(end_path_id);
//         threadLogger_->info("起点匹配上的参考轨迹ID：{}, ,索引：{} ", float(start_path_id + 1), start_nearest_id);

//         threadLogger_->info("起点所在 的参考轨迹总长：{} ", start_trajectory.trajectory.size());

//         threadLogger_->info("终点匹配上的参考轨迹ID：{},索引：{}", float(end_path_id + 1), end_nearest_id);

//         threadLogger_->info("终点所在 的参考轨迹总长：{} ", end_trajectory.trajectory.size());

//         // 通过判断当前规划起点、终点距离参考轨迹的横向距离、匹配点的角度差来确定是否需要进行hybird A*拟合
//         float lat_distance = 0.0;

//         threadLogger_->info("判断终点是否需要进行hybirdA*规划");
//         bool end_flag = DetermineIfOrNoHybirdAStar(end_point_, end_trajectory.trajectory, end_nearest_id,
//         lat_distance); threadLogger_->info("判断起点是否需要进行hybirdA*规划"); bool start_flag =
//         DetermineIfOrNoHybirdAStar(start_point_, start_trajectory.trajectory, start_nearest_id, lat_distance);

//         // 计算规划起点与规划终点与对于参考线起点、终点的几何距离，部分情况需要跨区域搜索拟合点
//         bool start_point_to_next_area = false, end_point_to_pre_area = false;
//         unsigned int temp_distance;
//         temp_distance = fabs(start_trajectory.trajectory.size() - start_nearest_id);
//         if (temp_distance < 37)
//         {
//             threadLogger_->info("start_point_to_next_area=true");

//             start_point_to_next_area = true;
//         }
//         temp_distance = fabs(end_nearest_id);
//         if (temp_distance < 37)
//         {
//             threadLogger_->info("end_point_to_pre_area = true");

//             end_point_to_pre_area = true;
//         }

//         vector<Trajectory_Point> temp_traj; // 记录针对哪条参考轨迹进行裁剪

//         Single_Point input_point;                                         // ProgressiveHybirdAStar 渐进式hybird
//         A*搜索函数输入形参-规划输入点 uint8 search_zone;                                                //
//         ProgressiveHybirdAStar 渐进式hybird A*搜索函数输入形参-当前规划区域 vector<Trajectory_Point>
//         Trajectory_be_searched;                  // ProgressiveHybirdAStar 渐进式hybird
//         A*搜索函数输入形参-在哪条参考轨迹上搜索hybird A*拟合点 unsigned int serach_start_index = 0; //
//         ProgressiveHybirdAStar 渐进式hybird A*搜索函数输入形参-从哪个索引处开始搜索 std::vector<Trajectory_Point>
//         temp_tra_start, temp_tra_end;       // ProgressiveHybirdAStar 渐进式hybird A*搜索函数输入形参-搜索出的轨迹
//         int32 Splice_Point_start_index = -1, Splice_Point_end_index = -1; // ProgressiveHybirdAStar 渐进式hybird
//         A*搜索函数输入形参-记录规划起点、规划终点处的hybird A*拼接轨迹分别记录规划起点、规划终点的hybird
//         A*拼接点的索引

//         float64 distance_min = 1000000;
//         std::vector<Trajectory_Point> temp_trajectory; // 存储HybirdA* 的规划轨迹
//         Trajectory_Point temp_point;
//         // 下面开始遍历dijkstra算法的搜索结果，在遍历到的区域进行轨迹规划，代码较多
//         for (size_t i = 0; i < zone_sequence_.size(); i++)
//         {
//             if (i == 0) //
//             planningcase3为结构化区域到结构化区域，所以zone_sequence里面存的第一个区域一定是结构化区域,同理，
//             最后一个区域也是结构化区域
//             {
//                 threadLogger_->info("遍历到第{}个结构化区域*", i + 1);

//                 if (zone_sequence_.size() > 2) // 【当前区域：起点、结构化——下一个区域：非终点】
//                 {
//                     threadLogger_->info("【当前区域：起点、结构化——下一个区域：非终点】");

//                     threadLogger_->info("【当前区域：起点、结构化——下一个区域：常规、结构化】");

//                     if (start_point_to_next_area) //  【当前区域：起点、结构化、
//                     规划起点靠近下一个区域——下一个区域：非终点、结构化】
//                     {
//                         threadLogger_->info("【当前区域：起点、结构化、
//                         规划起点靠近下一个区域——下一个区域：非终点、结构化】");

//                         if (start_flag)
//                         {
//                             threadLogger_->info("规划起点需要hybird A*进行拟合");
//                             // 遍历到终点所在节点再进行处理
//                             threadLogger_->info("do nothing");
//                         }
//                         else
//                         {
//                             threadLogger_->info("规划起点不需要hybird A*进行拟合");

//                             temp_traj = start_all_trajectories.at(start_path_id).trajectory;

//                             global_path_.insert(global_path_.end(), temp_traj.begin() + start_nearest_id,
//                             temp_traj.end());
//                         }
//                     }
//                     else //   【当前区域：起点、结构化、 规划起点距离下一区域较远——下一个区域：非终点、结构化】
//                     {
//                         threadLogger_->info("【当前区域：起点、结构化、
//                         规划起点距离下一区域较远——下一个区域：非终点、结构化】");

//                         if (start_flag)
//                         {
//                             threadLogger_->info("起点经过判定需要采用Hybird A*进行拟合");

//                             // 参数顺序解释：输入点、hybird
//                             A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                             input_point = start_point_;
//                             search_zone = zone_sequence_.at(i);
//                             Trajectory_be_searched = start_all_trajectories.at(start_path_id).trajectory;
//                             serach_start_index = start_nearest_id;
//                             uint8 hybird_rule_id = 5;

//                             if (!ProgressiveHybirdAStar(input_point, search_zone, true, Trajectory_be_searched,
//                             serach_start_index, Splice_Point_start_index, temp_tra_start, hybird_rule_id))
//                             {
//                                 // 反馈规划起点附近hybird A*轨迹拼接失败
//                                 threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                 return ErrorType::PLANNING_FAIL;
//                             }
//                         }
//                         // 将2段轨迹进行拼接，存入global_path
//                         temp_traj = start_all_trajectories.at(start_path_id).trajectory;
//                         if (start_flag)
//                         {
//                             global_path_.insert(global_path_.end(), temp_tra_start.begin(), temp_tra_start.end());
//                             global_path_.insert(global_path_.end(), temp_traj.begin() + Splice_Point_start_index + 1,
//                             temp_traj.end());
//                         }
//                         else
//                         {
//                             global_path_.insert(global_path_.end(), temp_traj.begin() + start_nearest_id,
//                             temp_traj.end());
//                         }
//                     }
//                 }
//                 else // 下一个区域是终点所在区域,在planningcase3中只可能是结构化区域
//                 【当前区域：起点、结构化——————下一个区域：终点、结构化】
//                 {
//                     threadLogger_->info("【当前区域：起点、结构化——————下一个区域：终点、结构化】");

//                     if (start_point_to_next_area) // 【当前区域：起点、结构化、
//                     起点靠近下一个区域——————下一个区域：终点、结构化】
//                     {
//                         threadLogger_->info("【当前区域：起点、结构化、
//                         起点靠近下一个区域——————下一个区域：终点、结构化】");

//                         if (end_point_to_pre_area) // 【当前区域：起点、结构化、
//                         起点靠近下一个区域——————下一个区域：终点、结构化、 终点靠近上一个区域】
//                         {
//                             threadLogger_->info("【当前区域：起点、结构化、
//                             起点靠近下一个区域——————下一个区域：终点、结构化、 终点靠近上一个区域】");

//                             threadLogger_->info(" do nothing，此部分任务交于后续逻辑来 处理");
//                         }
//                         else // 【当前区域：起点、结构化、 起点靠近下一个区域——————下一个区域：终点、结构化、
//                         终点远离前一个区域】
//                         {
//                             threadLogger_->info("【当前区域：起点、结构化、
//                             起点靠近下一个区域——————下一个区域：终点、结构化、 终点远离前一个区域】");

//                             if (start_flag)
//                             {
//                                 threadLogger_->info("规划起点需要进行hybird A*拟合");

//                                 threadLogger_->info("do nothing");
//                             }
//                             else
//                             {
//                                 threadLogger_->info("规划起点不需要进行hybird A*拟合");

//                                 temp_traj = start_all_trajectories.at(start_path_id).trajectory;
//                                 global_path_.insert(global_path_.end(), temp_traj.begin() + start_nearest_id,
//                                 temp_traj.end());
//                             }
//                         }
//                     }
//                     else // 【当前区域：起点、结构化、 起点远离下一个区域——————下一个区域：终点、结构化、直走】
//                     {
//                         threadLogger_->info("【当前区域：起点、结构化、
//                         起点远离下一个区域——————下一个区域：终点、结构化、直走】");

//                         if (end_point_to_pre_area) // 【当前区域：起点、结构化、
//                         起点远离下一个区域——————下一个区域：终点、结构化、 终点靠近上一个区域】
//                         {
//                             threadLogger_->info("【当前区域：起点、结构化、
//                             起点远离下一个区域——————下一个区域：终点、结构化、 终点靠近上一个区域】");

//                             if (start_flag)
//                             {
//                                 // 参数顺序解释：输入点、hybird
//                                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                                 input_point = start_point_;
//                                 search_zone = zone_sequence_.at(i);
//                                 Trajectory_be_searched = start_all_trajectories.at(start_path_id).trajectory;
//                                 serach_start_index = start_nearest_id;
//                                 uint8 hybird_rule_id = 5;

//                                 if (!ProgressiveHybirdAStar(input_point, search_zone, true, Trajectory_be_searched,
//                                 serach_start_index, Splice_Point_start_index, temp_tra_start, hybird_rule_id))
//                                 {
//                                     // 反馈规划起点附近hybird A*轨迹拼接失败
//                                     threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                     return ErrorType::PLANNING_FAIL;
//                                 }
//                             }
//                             else
//                             {
//                                 threadLogger_->info("规划起点不需要进行hybird A*拟合");
//                             }
//                             if (end_flag)
//                             {
//                                 threadLogger_->info("规划终点需要进行hybird A*拟合");

//                                 // 参数顺序解释：输入点、hybird
//                                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                                 input_point = end_point_;
//                                 search_zone = zone_sequence_.at(i);
//                                 Trajectory_be_searched = start_all_trajectories.at(start_path_id).trajectory;
//                                 serach_start_index = start_all_trajectories.at(start_path_id).trajectory.size() - 1;
//                                 uint8 hybird_rule_id = 5;

//                                 if (!ProgressiveHybirdAStar(input_point, search_zone, false, Trajectory_be_searched,
//                                 serach_start_index, Splice_Point_end_index, temp_tra_end, hybird_rule_id))
//                                 {
//                                     // 反馈规划起点附近hybird A*轨迹拼接失败
//                                     threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                     return ErrorType::PLANNING_FAIL;
//                                 }
//                             }
//                             else
//                             {
//                                 threadLogger_->info("规划终点不需要进行hybird A*拟合");
//                             }
//                             // 分析以上两个ProgressiveHybirdAStar算出的轨迹拼接点是否合理
//                             if (Splice_Point_start_index > Splice_Point_end_index && Splice_Point_end_index > 0)
//                             {
//                                 threadLogger_->error("起点与终点两者搜索出的拟合轨迹点位置存在冲突");

//                                 // 反馈搜索出的两个轨迹拼接点存在冲突的error
//                                 return ErrorType::PLANNING_FAIL;
//                             }
//                             temp_traj = start_all_trajectories.at(start_path_id).trajectory;
//                             if (start_flag)
//                             {
//                                 if (end_flag)
//                                 {
//                                     global_path_.insert(global_path_.end(), temp_tra_start.begin(),
//                                     temp_tra_start.end()); global_path_.insert(global_path_.end(), temp_traj.begin()
//                                     + Splice_Point_start_index + 1, temp_traj.begin() + Splice_Point_end_index - 1);
//                                     global_path_.insert(global_path_.end(), temp_tra_end.begin(),
//                                     temp_tra_end.end());
//                                 }
//                                 else
//                                 {
//                                     global_path_.insert(global_path_.end(), temp_tra_start.begin(),
//                                     temp_tra_start.end()); global_path_.insert(global_path_.end(), temp_traj.begin()
//                                     + Splice_Point_start_index + 1, temp_traj.end());
//                                 }
//                             }
//                             else
//                             {
//                                 if (end_flag)
//                                 {
//                                     global_path_.insert(global_path_.end(), temp_traj.begin() + start_nearest_id,
//                                     temp_traj.begin() + Splice_Point_end_index - 1);
//                                     global_path_.insert(global_path_.end(), temp_tra_end.begin(),
//                                     temp_tra_end.end());
//                                 }
//                                 else
//                                 {
//                                     global_path_.insert(global_path_.end(), temp_traj.begin() + start_nearest_id,
//                                     temp_traj.end());
//                                 }
//                             }
//                         }
//                         else // 【当前区域：起点、结构化、 起点远离下一个区域——————下一个区域：终点、结构化、
//                         终点远离上一个区域】
//                         {
//                             threadLogger_->info("【当前区域：起点、结构化、
//                             起点远离下一个区域——————下一个区域：终点、结构化、 终点远离上一个区域】");

//                             if (start_flag)
//                             {
//                                 // 参数顺序解释：输入点、hybird
//                                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                                 input_point = start_point_;
//                                 search_zone = zone_sequence_.at(i);
//                                 Trajectory_be_searched = start_all_trajectories.at(start_path_id).trajectory;
//                                 serach_start_index = start_nearest_id;
//                                 uint8 hybird_rule_id = 5;

//                                 if (!ProgressiveHybirdAStar(input_point, search_zone, true, Trajectory_be_searched,
//                                 serach_start_index, Splice_Point_start_index, temp_tra_start, hybird_rule_id))
//                                 {
//                                     // 反馈规划起点附近hybird A*轨迹拼接失败
//                                     threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                     return ErrorType::PLANNING_FAIL;
//                                 }
//                             }
//                             temp_traj = start_all_trajectories.at(start_path_id).trajectory;

//                             if (start_flag)
//                             {
//                                 global_path_.insert(global_path_.end(), temp_tra_start.begin(),
//                                 temp_tra_start.end()); global_path_.insert(global_path_.end(), temp_traj.begin() +
//                                 Splice_Point_start_index + 1, temp_traj.end());
//                             }
//                             else
//                             {
//                                 global_path_.insert(global_path_.end(), temp_traj.begin() + start_nearest_id,
//                                 temp_traj.end());
//                             }
//                         }
//                     }
//                 }
//             }
//             else if ((zone_sequence_.size() - 1) == i) // 当前区域为最后一个结构化区域
//             {
//                 threadLogger_->info("遍历到第{}个结构化区域", i + 1);

//                 if (zone_sequence_.size() == 2) // 【上一个区域：起点、结构化———当前区域：终点、结构化】
//                 {
//                     threadLogger_->info("【上一个区域：起点、结构化———当前区域：终点、结构化】");

//                     if (start_point_to_next_area) // 【上一个区域：起点、结构化、
//                     规划起点靠近当前区域———当前区域：终点、结构化、直走】
//                     {
//                         threadLogger_->info("【上一个区域：起点、结构化、
//                         规划起点靠近当前区域———当前区域：终点、结构化、直走】");

//                         if (end_point_to_pre_area) // 【上一个区域：起点、结构化、
//                         规划起点靠近当前区域———当前区域：终点、结构化、 规划终点靠近上一个区域】
//                         {
//                             threadLogger_->info("【上一个区域：起点、结构化、
//                             规划起点靠近当前区域———当前区域：终点、结构化、 规划终点靠近上一个区域】"); if
//                             ((!start_flag) && (!end_flag))
//                             {
//                                 global_path_.insert(global_path_.end(), start_trajectory.trajectory.begin() +
//                                 start_nearest_id, start_trajectory.trajectory.end());
//                                 global_path_.insert(global_path_.end(), end_trajectory.trajectory.begin(),
//                                 end_trajectory.trajectory.begin() + end_nearest_id); return ErrorType::SUCCESS;
//                             }

//                             threadLogger_->info("规划起点距离规划终点很接近，且需要采用hybird A*算法进行拟合");

//                             if (!ApplyHibridAStar(start_point_, end_point_, start_node_, temp_trajectory, 5))
//                             {
//                                 threadLogger_->error("Hybird A*无法规划出当前起点至终点的路径");

//                                 return ErrorType::PLANNING_FAIL;
//                                 // 反馈hybird A*直接搜索起点到终点的失败error
//                             }

//                             global_path_.insert(global_path_.end(), temp_trajectory.begin(), temp_trajectory.end());
//                         }
//                         else // 【上一个区域：起点、结构化、 规划起点靠近当前区域———当前区域：终点、结构化、
//                         规划终点远离上一个区域】
//                         {
//                             threadLogger_->info("【上一个区域：起点、结构化、
//                             规划起点靠近当前区域———当前区域：终点、结构化、 规划终点远离上一个区域】");

//                             if (start_flag)
//                             {
//                                 threadLogger_->info("规划起点需要进行hybird A*拼接");

//                                 // 参数顺序解释：输入点、hybird
//                                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                                 input_point = start_point_;
//                                 search_zone = zone_sequence_.at(i);
//                                 Trajectory_be_searched = end_all_trajectories.at(end_path_id).trajectory;
//                                 serach_start_index = 0;
//                                 uint8 hybird_rule_id = 5;

//                                 if (!ProgressiveHybirdAStar(input_point, search_zone, true, Trajectory_be_searched,
//                                 serach_start_index, Splice_Point_start_index, temp_tra_start, hybird_rule_id))
//                                 {
//                                     // 反馈规划起点附近hybird A*轨迹拼接失败
//                                     threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                     return ErrorType::PLANNING_FAIL;
//                                 }
//                             }

//                             if (end_flag)
//                             {
//                                 threadLogger_->info("规划终点需要进行hybird A*拼接");

//                                 // 参数顺序解释：输入点、hybird
//                                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                                 input_point = end_point_;
//                                 search_zone = zone_sequence_.at(i);
//                                 Trajectory_be_searched = end_all_trajectories.at(end_path_id).trajectory;
//                                 serach_start_index = end_nearest_id;
//                                 uint8 hybird_rule_id = 5;

//                                 if (!ProgressiveHybirdAStar(input_point, search_zone, false, Trajectory_be_searched,
//                                 serach_start_index, Splice_Point_end_index, temp_tra_end, hybird_rule_id))
//                                 {
//                                     // 反馈规划起点附近hybird A*轨迹拼接失败
//                                     threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                     return ErrorType::PLANNING_FAIL;
//                                 }
//                             }
//                             // 分析以上两个ProgressiveHybirdAStar算出的轨迹拼接点是否合理
//                             if (Splice_Point_start_index > Splice_Point_end_index && Splice_Point_end_index > 0)
//                             {
//                                 threadLogger_->error("起点与终点两者搜索出的拟合轨迹点位置存在冲突");

//                                 // 反馈搜索出的两个轨迹拼接点存在冲突的error
//                                 return ErrorType::PLANNING_FAIL;
//                             }
//                             temp_traj = end_all_trajectories.at(end_path_id).trajectory;
//                             if (start_flag)
//                             {
//                                 if (end_flag)
//                                 {
//                                     global_path_.insert(global_path_.end(), temp_tra_start.begin(),
//                                     temp_tra_start.end()); global_path_.insert(global_path_.end(), temp_traj.begin()
//                                     + Splice_Point_start_index + 1, temp_traj.begin() + Splice_Point_end_index);
//                                     global_path_.insert(global_path_.end(), temp_tra_end.begin(),
//                                     temp_tra_end.end());
//                                 }
//                                 else
//                                 {
//                                     global_path_.insert(global_path_.end(), temp_tra_start.begin(),
//                                     temp_tra_start.end()); global_path_.insert(global_path_.end(), temp_traj.begin()
//                                     + Splice_Point_start_index + 1, temp_traj.begin() + end_nearest_id + 1);
//                                 }
//                             }
//                             else
//                             {
//                                 if (end_flag)
//                                 {
//                                     threadLogger_->info("Splice_Point_end_index:{}",
//                                     static_cast<int>(Splice_Point_end_index));

//                                     global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() +
//                                     Splice_Point_end_index); global_path_.insert(global_path_.end(),
//                                     temp_tra_end.begin(), temp_tra_end.end());
//                                 }
//                                 else
//                                 {
//                                     global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() +
//                                     end_nearest_id + 1);
//                                 }
//                             }
//                         }
//                     }
//                     else // 【上一个区域：起点、结构化、 规划起点远离当前区域———当前区域：终点、结构化、直走】
//                     {
//                         threadLogger_->info("【上一个区域：起点、结构化、
//                         规划起点远离当前区域———当前区域：终点、结构化、直走】");

//                         if (end_point_to_pre_area) // 【上一个区域：起点、结构化、
//                         规划起点远离当前区域———当前区域：终点、结构化、 规划终点靠近上一个区域】
//                         {
//                             threadLogger_->info("【上一个区域：起点、结构化、
//                             规划起点远离当前区域———当前区域：终点、结构化、 规划终点靠近上一个区域】");

//                             if (end_flag)
//                             {
//                                 threadLogger_->info("do nothing");

//                                 // do nothing
//                             }
//                             else
//                             {
//                                 temp_traj = end_all_trajectories.at(end_path_id).trajectory;
//                                 global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() +
//                                 end_nearest_id + 1);
//                             }
//                         }
//                         else // 【上一个区域：起点、结构化、 规划起点远离当前区域———当前区域：终点、结构化、
//                         规划终点远离上一个区域】
//                         {
//                             threadLogger_->info("【上一个区域：起点、结构化、
//                             规划起点远离当前区域———当前区域：终点、结构化、 规划终点远离上一个区域】");

//                             if (end_flag)
//                             {
//                                 // 参数顺序解释：输入点、hybird
//                                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                                 input_point = end_point_;
//                                 search_zone = zone_sequence_.at(i);
//                                 Trajectory_be_searched = end_all_trajectories.at(end_path_id).trajectory;
//                                 serach_start_index = end_nearest_id;
//                                 uint8 hybird_rule_id = 5;

//                                 if (!ProgressiveHybirdAStar(input_point, search_zone, false, Trajectory_be_searched,
//                                 serach_start_index, Splice_Point_end_index, temp_tra_end, hybird_rule_id))
//                                 {
//                                     // 反馈规划起点附近hybird A*轨迹拼接失败
//                                     threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                     return ErrorType::PLANNING_FAIL;
//                                 }
//                             }
//                             temp_traj = end_all_trajectories.at(end_path_id).trajectory;
//                             if (end_flag)
//                             {

//                                 global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() +
//                                 Splice_Point_end_index - 1); global_path_.insert(global_path_.end(),
//                                 temp_tra_end.begin(), temp_tra_end.end());
//                             }
//                             else
//                             {

//                                 global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() +
//                                 end_nearest_id + 1);
//                             }
//                         }
//                     }
//                 }
//                 else // 【上一个区域：非起点———当前区域：终点、结构化】
//                 {
//                     threadLogger_->info("【上一个区域：非起点———当前区域：终点、结构化】");

//                     threadLogger_->info("【上一个区域：非起点、结构化———当前区域：终点、结构化】");

//                     if (end_point_to_pre_area) //
//                     【上一个区域：非起点、结构化———当前区域：终点、结构化、终点靠近上一个区域】
//                     {
//                         threadLogger_->info("【上一个区域：非起点、结构化———当前区域：终点、结构化、终点靠近上一个区域】");

//                         if (end_flag)
//                         {
//                             threadLogger_->info("do nothing");

//                             // do nothing
//                         }
//                         else
//                         {
//                             temp_traj = end_all_trajectories.at(end_path_id).trajectory;
//                             global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() +
//                             end_nearest_id + 1);
//                         }
//                     }
//                     else // 【上一个区域：非起点、结构化———当前区域：终点、结构化、终点远离上一个区域】
//                     {
//                         threadLogger_->info("【上一个区域：非起点、结构化———当前区域：终点、结构化、终点远离上一个区域】");

//                         if (end_flag)
//                         {
//                             threadLogger_->info("终点需要hybird A*拟合");

//                             // 参数顺序解释：输入点、hybird
//                             A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                             input_point = end_point_;
//                             search_zone = zone_sequence_.at(i);
//                             Trajectory_be_searched = end_all_trajectories.at(end_path_id).trajectory;
//                             serach_start_index = end_nearest_id;
//                             uint8 hybird_rule_id = 5;

//                             if (!ProgressiveHybirdAStar(input_point, search_zone, false, Trajectory_be_searched,
//                             serach_start_index, Splice_Point_end_index, temp_tra_end, hybird_rule_id))
//                             {
//                                 // 反馈规划起点附近hybird A*轨迹拼接失败
//                                 threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                 return ErrorType::PLANNING_FAIL;
//                             }
//                         }
//                         else
//                         {
//                             threadLogger_->info("规划终点不需要进行hybird A*拼接");
//                         }
//                         temp_traj = end_all_trajectories.at(end_path_id).trajectory;
//                         if (end_flag)
//                         {
//                             global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() +
//                             Splice_Point_end_index); global_path_.insert(global_path_.end(), temp_tra_end.begin(),
//                             temp_tra_end.end());
//                         }
//                         else
//                         {
//                             global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() +
//                             end_nearest_id + 1);
//                         }
//                     }
//                 }
//             }
//             else // 当前区域为中间的结构化区域 【上一个区域：未知———当前区域：常规、结构化——下一个区域：未知】
//             {
//                 threadLogger_->info("遍历到第{}个结构化区域", i + 1);

//                 uint8 temp_path_id = 0;
//                 if (!FindPathId(zone_sequence_.at(i - 1), zone_sequence_.at(i), zone_sequence_.at(i + 1),
//                 all_zones_.at(zone_sequence_.at(i) - 1).reference_trajs, temp_path_id))
//                 {
//                     threadLogger_->error(" The map file for zone{} does not have path for turn over",
//                     static_cast<float>(zone_sequence_.at(i)));

//                     return ErrorType::PLANNING_FAIL;
//                 }
//                 temp_traj = all_zones_.at(zone_sequence_.at(i) - 1).reference_trajs.at(temp_path_id).trajectory;
//                 int32 Crop_start_Point = -1, Crop_end_Point = -1;
//                 bool has_start_hy = false, has_end_hy = false;
//                 if (i != 1) // 【上一个区域：常规———当前区域：常规、结构化】
//                 {
//                     threadLogger_->info("【上一个区域：常规———当前区域：常规、结构化】");

//                     if (all_zones_.at(zone_sequence_.at(i - 1) - 1).zone_type == 1) //
//                     【上一个区域：常规、结构化———当前区域：常规、结构化】
//                     {
//                         threadLogger_->info("【上一个区域：常规、结构化———当前区域：常规、结构化】");

//                         Crop_start_Point = 0;
//                     }
//                     else // 【上一个区域：常规、非结构化———当前区域：常规、结构化】
//                     {
//                         threadLogger_->info("【上一个区域：常规、非结构化———当前区域：常规、结构化】");

//                         Crop_start_Point = Splice_Point_start_index;
//                     }
//                 }
//                 else // 【上一个区域：起点、结构化———当前区域：常规、结构化】
//                 {
//                     threadLogger_->info("【上一个区域：起点、结构化———当前区域：常规、结构化】");

//                     threadLogger_->info("【上一个区域：起点、结构化、直走———当前区域：常规、结构化】");

//                     if (start_point_to_next_area) // 【上一个区域：起点、结构化、
//                     规划起点靠近当前区域———当前区域：常规、结构化】
//                     {
//                         threadLogger_->info("【上一个区域：起点、结构化、
//                         规划起点靠近当前区域———当前区域：常规、结构化】");

//                         if (start_flag)
//                         {
//                             threadLogger_->info("规划起点需要进行hybird A*拼接");

//                             // 参数顺序解释：输入点、hybird
//                             A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                             input_point = start_point_;
//                             search_zone = zone_sequence_.at(i);
//                             Trajectory_be_searched = temp_traj;
//                             serach_start_index = 0;
//                             uint8 hybird_rule_id = 5;

//                             if (!ProgressiveHybirdAStar(input_point, search_zone, true, Trajectory_be_searched,
//                             serach_start_index, Splice_Point_start_index, temp_tra_start, hybird_rule_id))
//                             {
//                                 // 反馈规划起点附近hybird A*轨迹拼接失败
//                                 threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                 return ErrorType::PLANNING_FAIL;
//                             }
//                             has_start_hy = true;
//                             Crop_start_Point = Splice_Point_start_index;
//                         }
//                         else
//                         {
//                             threadLogger_->info("规划起点不需要进行hybird A*拼接");

//                             Crop_start_Point = 0;
//                         }
//                     }
//                     else // 【上一个区域：起点、结构化、 规划起点远离当前区域———当前区域：常规、结构化】
//                     {
//                         threadLogger_->info("【上一个区域：起点、结构化、
//                         规划起点远离当前区域———当前区域：常规、结构化】");

//                         Crop_start_Point = 0;
//                     }
//                 }
//                 if (i + 1 != zone_sequence_.size() - 1) // 【当前区域：常规、结构化——下一个区域：常规】
//                 {
//                     threadLogger_->info("【当前区域：常规、结构化——下一个区域：常规】");

//                     Crop_end_Point = temp_traj.size() - 1;
//                 }
//                 else // 【当前区域：常规、结构化——下一个区域：终点、结构化】
//                 {
//                     threadLogger_->info("【当前区域：常规、结构化——下一个区域：终点、结构化】");

//                     if (end_point_to_pre_area) //
//                     【当前区域：常规、结构化——下一个区域：终点、结构化、规划终点靠近当前区域】
//                     {
//                         threadLogger_->info("【当前区域：常规、结构化——下一个区域：终点、结构化、规划终点靠近当前区域】");

//                         if (end_flag)
//                         {
//                             // 参数顺序解释：输入点、hybird
//                             A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                             input_point = end_point_;
//                             search_zone = zone_sequence_.at(i);
//                             Trajectory_be_searched = temp_traj;
//                             serach_start_index = temp_traj.size() - 1;
//                             uint8 hybird_rule_id = 5;

//                             if (!ProgressiveHybirdAStar(input_point, search_zone, false, Trajectory_be_searched,
//                             serach_start_index, Splice_Point_end_index, temp_tra_end, hybird_rule_id))
//                             {
//                                 // 反馈规划起点附近hybird A*轨迹拼接失败
//                                 threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                 return ErrorType::PLANNING_FAIL;
//                             }
//                             has_end_hy = true;
//                             Crop_end_Point = Splice_Point_end_index;
//                         }
//                         else
//                         {
//                             threadLogger_->info("规划终点不需要进行hybird A*拟合");

//                             Crop_end_Point = temp_traj.size() - 1;
//                         }
//                     }
//                     else // 【当前区域：常规、结构化——下一个区域：终点、结构化、规划终点远离当前区域】
//                     {
//                         threadLogger_->info("【当前区域：常规、结构化——下一个区域：终点、结构化、规划终点远离当前区域】");

//                         Crop_end_Point = temp_traj.size() - 1;
//                     }
//                 }
//                 // 开始拼接轨迹
//                 if (has_start_hy)
//                 {
//                     if (has_end_hy)
//                     {
//                         global_path_.insert(global_path_.end(), temp_tra_start.begin(), temp_tra_start.end());
//                         global_path_.insert(global_path_.end(), temp_traj.begin() + Crop_start_Point + 1,
//                         temp_traj.begin() + Crop_end_Point - 1); global_path_.insert(global_path_.end(),
//                         temp_tra_end.begin(), temp_tra_end.end());
//                     }
//                     else
//                     {
//                         global_path_.insert(global_path_.end(), temp_tra_start.begin(), temp_tra_start.end());
//                         global_path_.insert(global_path_.end(), temp_traj.begin() + Crop_start_Point + 1,
//                         temp_traj.end());
//                     }
//                 }
//                 else
//                 {
//                     if (has_end_hy)
//                     {
//                         global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() + Crop_end_Point
//                         - 1); global_path_.insert(global_path_.end(), temp_tra_end.begin(), temp_tra_end.end());
//                     }
//                     else
//                     {
//                         global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.end());
//                     }
//                 }
//             }
//         }
//         return ErrorType::SUCCESS;
//     }
//     else
//     {
//         threadLogger_->info("The map file for zone {}  does not have any reference path", (float)start_node_);

//         threadLogger_->info("The map file for zone {} does not have any reference path", (float)end_node_);

//         return ErrorType::NO_REFERENCELINE;
//     }
// }

// /**
//  * @brief 起始点和终止点不在同一区域，且起点为结构化道路、终点为非结构化道路
//  * @param [in] 无
//  * @param [return] true: 规划成功；false：规划失败
//  */
// ErrorType Planning::PlanningCase4()
// {
//     threadLogger_->info("Enter PlanningCase4");

//     ErrorType temp_error_type;
//     map<uint8, double> v_id;
//     if (zone_sequence_.size() < 2) // planningcase4不会出现此情况
//     {
//         return ErrorType::NO_REFERENCELINE;
//     }

//     global_path_.clear();    // 清空全局轨迹容器
//     uint8 start_path_id;     // 记录规划起点在其对应结构化区域内的参考线索引
//     unsigned int start_nearest_id; // 记录规划起点在参考线上的投影点索引
//     vector<Single_Trajectory> start_all_trajectories = all_zones_.at(start_node_ - 1).reference_trajs;

//     if (start_all_trajectories.size()) // 区域内均有参考路径才进行后续的规划
//     {
//         threadLogger_->info("寻找当前规划起点的对应参考路径");
//         threadLogger_->info(" ");

//         temp_error_type = FindReferencePath(start_point_, start_all_trajectories, start_nearest_id, start_path_id,
//         true, v_id, 0); if (temp_error_type != ErrorType::SUCCESS) // 找到区域内与终点最近的参考路径
//         {
//             threadLogger_->error("...Failed to find the nearest point for the start point...");

//             return temp_error_type;
//         }

//         // 记录规划起点、规划终点的参考路径
//         Single_Trajectory start_trajectory;
//         start_trajectory = start_all_trajectories.at(start_path_id);

//         threadLogger_->info("起点匹配上的参考轨迹ID：{}  ,索引：{}", float(start_path_id + 1), start_nearest_id);

//         threadLogger_->info("起点所在 的参考轨迹总长:{}", start_trajectory.trajectory.size());

//         // 通过判断当前规划起点、终点距离参考轨迹的横向距离、匹配点的角度差来确定是否需要进行hybird A*拟合
//         float lat_distance = 0.0;
//         threadLogger_->info("判断起点是否需要进行hybirdA*规划");
//         bool start_flag = DetermineIfOrNoHybirdAStar(start_point_, start_trajectory.trajectory, start_nearest_id,
//         lat_distance);

//         // 计算规划起点与规划终点与对于参考线起点、终点的几何距离，部分情况需要跨区域搜索拟合点
//         bool start_point_to_next_area = false;
//         unsigned int temp_distance;

//         temp_distance = fabs(start_trajectory.trajectory.size() - start_nearest_id);

//         if (temp_distance < 37)
//         {
//             start_point_to_next_area = true;
//         }

//         // 记录针对哪条参考轨迹进行裁剪
//         vector<Trajectory_Point> temp_traj;

//         Single_Point input_point;                                         // ProgressiveHybirdAStar 渐进式hybird
//         A*搜索函数输入形参-规划输入点 uint8 search_zone;                                                //
//         ProgressiveHybirdAStar 渐进式hybird A*搜索函数输入形参-当前规划区域 vector<Trajectory_Point>
//         Trajectory_be_searched;                  // ProgressiveHybirdAStar 渐进式hybird
//         A*搜索函数输入形参-在哪条参考轨迹上搜索hybird A*拟合点 unsigned int serach_start_index = 0; //
//         ProgressiveHybirdAStar 渐进式hybird A*搜索函数输入形参-从哪个索引处开始搜索 std::vector<Trajectory_Point>
//         temp_tra_start, temp_tra_end;       // ProgressiveHybirdAStar 渐进式hybird A*搜索函数输入形参-搜索出的轨迹
//         int32 Splice_Point_start_index = -1, Splice_Point_end_index = -1; // ProgressiveHybirdAStar 渐进式hybird
//         A*搜索函数输入形参-记录规划起点、规划终点处的hybird A*拼接轨迹分别记录规划起点、规划终点的hybird
//         A*拼接点的索引

//         float64 distance_min = 1000000;
//         std::vector<Trajectory_Point> temp_trajectory;
//         Trajectory_Point temp_point;

//         // 下面开始遍历dijkstra算法的搜索结果，在遍历到的区域进行轨迹规划，代码较多
//         for (size_t i = 0; i < zone_sequence_.size(); i++)
//         {
//             uint8 temp_area_type;                                               // 0:非结构化 1:结构化
//             temp_area_type = all_zones_.at(zone_sequence_.at(i) - 1).zone_type; // 当前遍历到的区域的类型

//             if (temp_area_type == 1)
//             {
//                 if (i == 0) //
//                 planningcase4为结构化区域到非结构化区域，所以zone_sequence里面存的第一个区域一定是结构化区域
//                 {
//                     threadLogger_->info("遍历到第{}个结构化区域*", i + 1);

//                     if (zone_sequence_.size() > 2) // 【当前区域：起点、结构化——下一个区域：非终点】
//                     {
//                         threadLogger_->info("【当前区域：起点、结构化——下一个区域：非终点】");

//                         threadLogger_->info("【当前区域：起点、结构化——下一个区域：常规、结构化】");

//                         if (start_point_to_next_area) //  【当前区域：起点、结构化、
//                         规划起点靠近下一个区域——下一个区域：非终点、结构化】
//                         {
//                             threadLogger_->info("【当前区域：起点、结构化、
//                             规划起点靠近下一个区域——下一个区域：非终点、结构化】");

//                             if (start_flag)
//                             {
//                                 threadLogger_->info("规划起点需要hybird A*进行轨迹拼接");

//                                 threadLogger_->info("do nothing");
//                             }
//                             else
//                             {
//                                 threadLogger_->info("规划起点不需要hybird A*进行轨迹拼接");

//                                 temp_traj = start_all_trajectories.at(start_path_id).trajectory;

//                                 global_path_.insert(global_path_.end(), temp_traj.begin() + start_nearest_id,
//                                 temp_traj.end());
//                             }
//                         }
//                         else //   【当前区域：起点、结构化、 规划起点距离下一区域较远——下一个区域：非终点、结构化】
//                         {
//                             threadLogger_->info("【当前区域：起点、结构化、
//                             规划起点距离下一区域较远——下一个区域：非终点、结构化】");

//                             if (start_flag)
//                             {
//                                 threadLogger_->info("起点经过判定需要采用Hybird A*进行拟合");

//                                 // 参数顺序解释：输入点、hybird
//                                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                                 input_point = start_point_;
//                                 search_zone = zone_sequence_.at(i);
//                                 Trajectory_be_searched = start_all_trajectories.at(start_path_id).trajectory;
//                                 serach_start_index = start_nearest_id;
//                                 uint8 hybird_rule_id = 5;

//                                 if (!ProgressiveHybirdAStar(input_point, search_zone, true, Trajectory_be_searched,
//                                 serach_start_index, Splice_Point_start_index, temp_tra_start, hybird_rule_id))
//                                 {
//                                     // 反馈规划起点附近hybird A*轨迹拼接失败
//                                     threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                     return ErrorType::PLANNING_FAIL;
//                                 }
//                             }

//                             // 将2段轨迹进行拼接，存入global_path
//                             temp_traj = start_all_trajectories.at(start_path_id).trajectory;
//                             if (start_flag)
//                             {

//                                 global_path_.insert(global_path_.end(), temp_tra_start.begin(),
//                                 temp_tra_start.end()); global_path_.insert(global_path_.end(), temp_traj.begin() +
//                                 Splice_Point_start_index + 1, temp_traj.end());
//                             }
//                             else
//                             {

//                                 global_path_.insert(global_path_.end(), temp_traj.begin() + start_nearest_id,
//                                 temp_traj.end());
//                             }
//                         }
//                     }
//                     else // 下一个区域是终点所在区域,在planningcase4中只可能是非结构化区域
//                     【当前区域：起点、结构化——————下一个区域：终点、非结构化】
//                     {
//                         threadLogger_->info("【当前区域：起点、结构化——————下一个区域：终点、非结构化】");

//                         threadLogger_->info("【当前区域：起点、结构化、直走——————下一个区域：终点、非结构化】");

//                         if (start_point_to_next_area) // 【当前区域：起点、结构化、
//                         起点靠近下一个区域——————下一个区域：终点、非结构化】
//                         {
//                             threadLogger_->info("【当前区域：起点、结构化、
//                             起点靠近下一个区域——————下一个区域：终点、非结构化】");

//                             threadLogger_->info("do nothing");
//                         }
//                         else // 【当前区域：起点、结构化、 起点远离下一个区域——————下一个区域：终点、非结构化】
//                         {
//                             threadLogger_->info("【当前区域：起点、结构化、
//                             起点远离下一个区域——————下一个区域：终点、非结构化】");

//                             if (start_flag)
//                             {
//                                 threadLogger_->info("规划起点需要进行hybird A*轨迹拼接");

//                                 // 参数顺序解释：输入点、hybird
//                                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                                 input_point = start_point_;
//                                 search_zone = zone_sequence_.at(i);
//                                 Trajectory_be_searched = start_all_trajectories.at(start_path_id).trajectory;
//                                 serach_start_index = start_nearest_id;
//                                 uint8 hybird_rule_id = 5;

//                                 if (!ProgressiveHybirdAStar(input_point, search_zone, true, Trajectory_be_searched,
//                                 serach_start_index, Splice_Point_start_index, temp_tra_start, hybird_rule_id))
//                                 {
//                                     // 反馈规划起点附近hybird A*轨迹拼接失败
//                                     threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                     return ErrorType::PLANNING_FAIL;
//                                 }
//                             }

//                             // Trajectory_Point temp_point;
//                             distance_min = 1000000;
//                             unsigned int nearest_id;
//                             temp_traj = start_all_trajectories.at(start_path_id).trajectory;

//                             for (unsigned int i = 0; i < temp_traj.size(); i++)
//                             {
//                                 temp_point = temp_traj.at(i);

//                                 if (pow(end_point_.x - temp_point.x, 2) + pow(end_point_.y - temp_point.y, 2) <
//                                 distance_min)
//                                 {
//                                     distance_min = pow(end_point_.x - temp_point.x, 2) + pow(end_point_.y -
//                                     temp_point.y, 2); nearest_id = i;
//                                 }
//                             }
//                             bool Need_hybird_A_star = true;
//                             // 判断找到 的最近的点距离den_point之间的几何距离，小于0.2m就不进行hybird A*拟合
//                             float dis = sqrt(pow(temp_traj.at(nearest_id).x - end_point_.x, 2) +
//                             pow(temp_traj.at(nearest_id).y - end_point_.y, 2));
//                             threadLogger_->info("终点与匹配上的参考轨迹的最近点的几何距离：{}", dis);

//                             if (dis > 0.1)
//                                 Need_hybird_A_star = true;
//                             else
//                                 Need_hybird_A_star = false;
//                             threadLogger_->info("Need_hybird_A_star:{}", (int)Need_hybird_A_star);

//                             if (Need_hybird_A_star)
//                             {
//                                 // 参数顺序解释：输入点、hybird
//                                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                                 input_point = end_point_;
//                                 search_zone = zone_sequence_.at(i);
//                                 Trajectory_be_searched = start_all_trajectories.at(start_path_id).trajectory;
//                                 serach_start_index = nearest_id;
//                                 uint8 hybird_rule_id = 0;
//                                 // if (dis < 5)
//                                 //     hybird_rule_id = 5;
//                                 // else
//                                 //     hybird_rule_id = 0;

//                                 if (!ProgressiveHybirdAStar(input_point, search_zone, false, Trajectory_be_searched,
//                                 serach_start_index, Splice_Point_end_index, temp_tra_end, hybird_rule_id))
//                                 {
//                                     // 反馈规划起点附近hybird A*轨迹拼接失败
//                                     threadLogger_->error("规划终点附近hybird A*轨迹拼接失败");

//                                     return ErrorType::PLANNING_FAIL;
//                                 }

//                                 // 分析以上两个ProgressiveHybirdAStar算出的轨迹拼接点是否合理
//                                 if (Splice_Point_start_index > Splice_Point_end_index && Splice_Point_end_index > 0)
//                                 {
//                                     threadLogger_->error("起点与终点两者搜索出的拟合轨迹点位置存在冲突");

//                                     // 反馈搜索出的两个轨迹拼接点存在冲突的error
//                                     return ErrorType::PLANNING_FAIL;
//                                 }
//                             }
//                             else
//                             {
//                                 Splice_Point_end_index = Trajectory_be_searched.size() - 1;
//                             }

//                             temp_traj = start_all_trajectories.at(start_path_id).trajectory;

//                             if (start_flag)
//                             {

//                                 global_path_.insert(global_path_.end(), temp_tra_start.begin(),
//                                 temp_tra_start.end()); global_path_.insert(global_path_.end(), temp_traj.begin() +
//                                 Splice_Point_start_index + 1, temp_traj.begin() + Splice_Point_end_index);
//                                 global_path_.insert(global_path_.end(), temp_tra_end.begin(), temp_tra_end.end());
//                             }
//                             else
//                             {

//                                 global_path_.insert(global_path_.end(), temp_traj.begin() + start_nearest_id,
//                                 temp_traj.begin() + Splice_Point_end_index); global_path_.insert(global_path_.end(),
//                                 temp_tra_end.begin(), temp_tra_end.end());
//                             }
//                         }
//                     }
//                 }
//                 else // 当前区域为中间的结构化区域 【上一个区域：未知———当前区域：常规、结构化——下一个区域：未知】
//                 {

//                     threadLogger_->info("遍历到第{} 个结构化区域", i + 1);

//                     uint8 temp_path_id = 0;
//                     if (!FindPathId(zone_sequence_.at(i - 1), zone_sequence_.at(i), zone_sequence_.at(i + 1),
//                     all_zones_.at(zone_sequence_.at(i) - 1).reference_trajs, temp_path_id))
//                     {
//                         threadLogger_->error(" The map file for zone {} does not have path for turn over ",
//                         static_cast<float>(zone_sequence_.at(i)));

//                         return ErrorType::PLANNING_FAIL;
//                     }
//                     temp_traj = all_zones_.at(zone_sequence_.at(i) - 1).reference_trajs.at(temp_path_id).trajectory;
//                     int32 Crop_start_Point = -1, Crop_end_Point = -1;
//                     bool has_start_hy = false, has_end_hy = false;
//                     if (i != 1) // 【上一个区域：常规———当前区域：常规、结构化】
//                     {
//                         threadLogger_->info("【上一个区域：常规———当前区域：常规、结构化】");

//                         if (all_zones_.at(zone_sequence_.at(i - 1) - 1).zone_type == 1) //
//                         【上一个区域：常规、结构化———当前区域：常规、结构化】
//                         {
//                             threadLogger_->info("【上一个区域：常规、结构化———当前区域：常规、结构化】");

//                             Crop_start_Point = 0;
//                         }
//                         else // 【上一个区域：常规、非结构化———当前区域：常规、结构化】
//                         {
//                             threadLogger_->info("【上一个区域：常规、非结构化———当前区域：常规、结构化】");

//                             Crop_start_Point = Splice_Point_start_index;
//                         }
//                     }
//                     else // 【上一个区域：起点、结构化———当前区域：常规、结构化】
//                     {
//                         threadLogger_->info("【上一个区域：起点、结构化———当前区域：常规、结构化】");

//                         threadLogger_->info("【上一个区域：起点、结构化、直走———当前区域：常规、结构化】");

//                         if (start_point_to_next_area) // 【上一个区域：起点、结构化、
//                         规划起点靠近当前区域———当前区域：常规、结构化】
//                         {
//                             threadLogger_->info("【上一个区域：起点、结构化、
//                             规划起点靠近当前区域———当前区域：常规、结构化】");

//                             if (start_flag)
//                             {
//                                 threadLogger_->info("规划起点需要hybird A*轨迹拼接");

//                                 // 参数顺序解释：输入点、hybird
//                                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                                 input_point = start_point_;
//                                 search_zone = zone_sequence_.at(i);
//                                 Trajectory_be_searched = temp_traj;
//                                 serach_start_index = 0;
//                                 uint8 hybird_rule_id = 5;
//                                 if (!ProgressiveHybirdAStar(input_point, search_zone, true, Trajectory_be_searched,
//                                 serach_start_index, Splice_Point_start_index, temp_tra_start, hybird_rule_id))
//                                 {
//                                     // 反馈规划起点附近hybird A*轨迹拼接失败
//                                     threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                     return ErrorType::PLANNING_FAIL;
//                                 }
//                                 has_start_hy = true;
//                                 Crop_start_Point = Splice_Point_start_index;
//                             }
//                             else
//                             {
//                                 threadLogger_->info("规划起点不需要hybird A*轨迹拼接");

//                                 Crop_start_Point = 0;
//                             }
//                         }
//                         else // 【上一个区域：起点、结构化、 规划起点远离当前区域———当前区域：常规、结构化】
//                         {
//                             threadLogger_->info("【上一个区域：起点、结构化、
//                             规划起点远离当前区域———当前区域：常规、结构化】");

//                             Crop_start_Point = 0;
//                         }
//                     }
//                     if (i + 1 != zone_sequence_.size() - 1) // 【当前区域：常规、结构化——下一个区域：常规】
//                     {
//                         threadLogger_->info("【当前区域：常规、结构化——下一个区域：常规】");

//                         Crop_end_Point = temp_traj.size() - 1;
//                     }
//                     else // 【当前区域：常规、结构化——下一个区域：终点、非结构化】
//                     {
//                         threadLogger_->info("【当前区域：常规、结构化——下一个区域：终点、非结构化】");

//                         //
//                         由于结构化区域的参考轨迹可能伸入到非结构化区域，需要找到参考线上距离终点的最近点，以此点为搜索起点
//                         // Trajectory_Point temp_point;
//                         distance_min = 1000000;
//                         unsigned int nearest_id;
//                         for (unsigned int i = 0; i < temp_traj.size(); i++)
//                         {
//                             temp_point = temp_traj.at(i);

//                             if (pow(end_point_.x - temp_point.x, 2) + pow(end_point_.y - temp_point.y, 2) <
//                             distance_min)
//                             {
//                                 distance_min = pow(end_point_.x - temp_point.x, 2) + pow(end_point_.y - temp_point.y,
//                                 2); nearest_id = i;
//                             }
//                         }
//                         threadLogger_->info("即将进行hybird A*轨迹拼接,nearest_id:{}", nearest_id);

//                         // 参数顺序解释：输入点、hybird
//                         A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                         input_point = end_point_;
//                         search_zone = zone_sequence_.at(i);
//                         Trajectory_be_searched = temp_traj;
//                         serach_start_index = nearest_id;
//                         uint8 hybird_rule_id = 5;
//                         if (!ProgressiveHybirdAStar(input_point, search_zone, false, Trajectory_be_searched,
//                         serach_start_index, Splice_Point_end_index, temp_tra_end, hybird_rule_id))
//                         {
//                             // 反馈规划起点附近hybird A*轨迹拼接失败
//                             threadLogger_->error("规划终点附近hybird A*轨迹拼接失败");

//                             return ErrorType::PLANNING_FAIL;
//                         }
//                         has_end_hy = true;
//                         Crop_end_Point = Splice_Point_end_index;
//                     }
//                     // 开始拼接轨迹
//                     if (has_start_hy)
//                     {
//                         if (has_end_hy)
//                         {
//                             global_path_.insert(global_path_.end(), temp_tra_start.begin(), temp_tra_start.end());
//                             global_path_.insert(global_path_.end(), temp_traj.begin() + Crop_start_Point + 1,
//                             temp_traj.begin() + Crop_end_Point);

//                             global_path_.insert(global_path_.end(), temp_tra_end.begin(), temp_tra_end.end());
//                         }
//                         else
//                         {
//                             global_path_.insert(global_path_.end(), temp_tra_start.begin(), temp_tra_start.end());
//                             global_path_.insert(global_path_.end(), temp_traj.begin() + Crop_start_Point + 1,
//                             temp_traj.end());
//                         }
//                     }
//                     else
//                     {
//                         if (has_end_hy)
//                         {
//                             global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() +
//                             Crop_end_Point); global_path_.insert(global_path_.end(), temp_tra_end.begin(),
//                             temp_tra_end.end());
//                         }
//                         else
//                         {
//                             global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.end());
//                         }
//                     }
//                 }
//             }
//             else // 当前遍历到的区域为非结构化区域，在planningcase4中，非结构化区域只能是中间区域、或最后一个区域
//             {
//                 if (i != zone_sequence_.size() - 1)
//                 {
//                     threadLogger_->info("遍历到第{}个非结构化区域 ", i + 1);

//                     Single_Point temp_start_point;
//                     if (i != 1) // 【上一个区域：常规 、结构化——当前区域：常规、非结构化】
//                     {
//                         threadLogger_->info("【上一个区域：常规 、结构化——当前区域：常规、非结构化】");

//                         temp_start_point.x = global_path_.back().x;
//                         temp_start_point.y = global_path_.back().y;
//                         temp_start_point.z = global_path_.back().z;
//                         temp_start_point.yaw = global_path_.back().yaw;
//                     }
//                     else // 【上一个区域：起点 、结构化——当前区域：常规、非结构化】
//                     {
//                         threadLogger_->info("【上一个区域：起点 、结构化——当前区域：常规、非结构化】");

//                         threadLogger_->info("【上一个区域：起点 、结构化、直走——当前区域：常规、非结构化】");

//                         if (start_point_to_next_area) // 【上一个区域：起点 、结构化、
//                         规划起点靠近当前区域——当前区域：常规、非结构化】
//                         {
//                             threadLogger_->info("【上一个区域：起点 、结构化、
//                             规划起点靠近当前区域——当前区域：常规、非结构化】");

//                             temp_start_point = start_point_;
//                         }
//                         else // 【上一个区域：起点 、结构化、 规划起点远离当前区域——当前区域：常规、非结构化】
//                         {
//                             threadLogger_->info("【上一个区域：起点 、结构化、
//                             规划起点远离当前区域——当前区域：常规、非结构化】");

//                             temp_start_point.x = global_path_.back().x;
//                             temp_start_point.y = global_path_.back().y;
//                             temp_start_point.z = global_path_.back().z;
//                             temp_start_point.yaw = global_path_.back().yaw;
//                         }
//                     }

//                     threadLogger_->info("【当前区域：常规、非结构化——下一个区域：常规 、结构化】");

//                     uint8 temp_path_id = 0;
//                     if (!FindPathId(zone_sequence_.at(i), zone_sequence_.at(i + 1), zone_sequence_.at(i + 2),
//                     all_zones_.at(zone_sequence_.at(i + 1) - 1).reference_trajs, temp_path_id))
//                     {
//                         threadLogger_->error(" The map file for zone {} does not have path for turn over",
//                         static_cast<float>(zone_sequence_.at(i + 1)));

//                         return ErrorType::PLANNING_FAIL;
//                     }
//                     temp_traj = all_zones_.at(zone_sequence_.at(i + 1) -
//                     1).reference_trajs.at(temp_path_id).trajectory;
//                     // 通过hybird A*算法在下一个区域的参考线上搜点

//                     // 参数顺序解释：输入点、hybird
//                     A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                     input_point = temp_start_point;
//                     search_zone = zone_sequence_.at(i);
//                     Trajectory_be_searched = temp_traj;
//                     serach_start_index = 0;
//                     // std::vector<Trajectory_Point> temp_trajectory;
//                     uint8 hybird_rule_id = 5;
//                     if (!ProgressiveHybirdAStar(input_point, search_zone, true, Trajectory_be_searched,
//                     serach_start_index, Splice_Point_start_index, temp_trajectory, hybird_rule_id))
//                     {
//                         // 反馈规划起点附近hybird A*轨迹拼接失败
//                         threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                         return ErrorType::PLANNING_FAIL;
//                     }

//                     global_path_.insert(global_path_.end(), temp_trajectory.begin(), temp_trajectory.end());
//                 }
//                 else // 最后一个非结构化区域
//                 {
//                     threadLogger_->info("遍历到第{} 个非结构化区域", i + 1);

//                     if (zone_sequence_.size() == 2) // 【上一个区域：起点、结构化———当前区域：终点、非结构化】
//                     {
//                         threadLogger_->info("【上一个区域：起点、结构化———当前区域：终点、非结构化】");

//                         threadLogger_->info("【上一个区域：起点、结构化、直走———当前区域：终点、非结构化】");

//                         if (start_point_to_next_area) // 【上一个区域：起点、结构化、
//                         规划起点靠近当前区域———当前区域：终点、非结构化】
//                         {
//                             threadLogger_->info("【上一个区域：起点、结构化、
//                             规划起点靠近当前区域———当前区域：终点、非结构化】");

//                             threadLogger_->info("规划起点距离规划终点很接近，直接采用hybird A*算法进行拟合");

//                             if (!ApplyHibridAStar(start_point_, end_point_, start_node_, temp_trajectory, 5))
//                             {
//                                 threadLogger_->error("Hybird A*无法规划出当前起点至终点的路径");

//                                 return ErrorType::PLANNING_FAIL;
//                                 // 反馈hybird A*直接搜索起点到终点的失败error
//                             }
//                             global_path_.insert(global_path_.end(), temp_trajectory.begin(), temp_trajectory.end());
//                         }
//                         else // 【上一个区域：起点、结构化、 规划起点远离当前区域———当前区域：终点、非结构化】
//                         {
//                             threadLogger_->info("【上一个区域：起点、结构化、
//                             规划起点远离当前区域———当前区域：终点、非结构化】");

//                             threadLogger_->info("do nothing");

//                             // do nothing
//                         }
//                     }
//                     else // 【上一个区域：非起点———当前区域：终点、非结构化】
//                     {
//                         threadLogger_->info("【上一个区域：非起点———当前区域：终点、非结构化】");

//                         threadLogger_->info("【上一个区域：非起点、结构化———当前区域：终点、非结构化】");

//                         threadLogger_->info("do nothing");
//                     }
//                 }
//             }
//         }
//         return ErrorType::SUCCESS;
//         ;
//     }
//     else
//     {
//         threadLogger_->info("The map file for zone {} does not have any reference path", (float)start_node_);

//         threadLogger_->info("The map file for zone {} does not have any reference path", (float)end_node_);

//         return ErrorType::NO_REFERENCELINE;
//     }
// }

// /**
//  * @brief 起始点和终止点不在同一区域，且起点为非结构化道路、终点为结构化道路
//  * @param [in] 无
//  * @param [return] true: 规划成功；false：规划失败
//  */
// ErrorType Planning::PlanningCase5()
// {

//     threadLogger_->info("Enter PlanningCase5");

//     ErrorType temp_error_type;
//     map<uint8, double> v_id;
//     if (zone_sequence_.size() < 2) // planningcase5不会出现此情况
//     {
//         return ErrorType::PLANNING_FAIL;
//     }
//     global_path_.clear();  // 清空全局轨迹容器
//     uint8 end_path_id;     // 记录规划起点在其对应结构化区域内的参考线索引
//     unsigned int end_nearest_id; // 记录规划起点在参考线上的投影点索引
//     vector<Single_Trajectory> end_all_trajectories = all_zones_.at(end_node_ - 1).reference_trajs;

//     if (end_all_trajectories.size()) // 区域内均有参考路径才进行后续的规划
//     {
//         threadLogger_->info("寻找当前规划终点的对应参考路径");
//         threadLogger_->info(" ");

//         temp_error_type = FindReferencePath(end_point_, end_all_trajectories, end_nearest_id, end_path_id, false,
//         v_id, 0);

//         if (temp_error_type != ErrorType::SUCCESS) // 找到区域内与终点最近的参考路径
//         {
//             threadLogger_->error("...Failed to find the nearest point for the end point...");

//             return temp_error_type;
//         }

//         // 记录规划起点、规划终点的参考路径
//         Single_Trajectory end_trajectory;
//         end_trajectory = end_all_trajectories.at(end_path_id);

//         threadLogger_->info("终点匹配上的参考轨迹ID：{}  ,索引：{}", float(end_path_id + 1), end_nearest_id);

//         threadLogger_->info("终点所在 的参考轨迹总长：{} ", end_trajectory.trajectory.size());

//         // 通过判断当前规划起点、终点距离参考轨迹的横向距离、匹配点的角度差来确定是否需要进行hybird A*拟合
//         float lat_distance = 0.0;
//         threadLogger_->info("判断终点是否需要进行hybirdA*规划");
//         bool end_flag = DetermineIfOrNoHybirdAStar(end_point_, end_trajectory.trajectory, end_nearest_id,
//         lat_distance);

//         // 计算规划起点与规划终点与对于参考线起点、终点的几何距离，部分情况需要跨区域搜索拟合点
//         bool end_point_to_pre_area = false;
//         unsigned int temp_distance;

//         temp_distance = fabs(end_nearest_id);
//         if (temp_distance < 100)
//         {
//             end_point_to_pre_area = true;
//         }

//         // 记录针对哪条参考轨迹进行裁剪
//         vector<Trajectory_Point> temp_traj;

//         Single_Point input_point;                                         // ProgressiveHybirdAStar 渐进式hybird
//         A*搜索函数输入形参-规划输入点 uint8 search_zone;                                                //
//         ProgressiveHybirdAStar 渐进式hybird A*搜索函数输入形参-当前规划区域 vector<Trajectory_Point>
//         Trajectory_be_searched;                  // ProgressiveHybirdAStar 渐进式hybird
//         A*搜索函数输入形参-在哪条参考轨迹上搜索hybird A*拟合点 unsigned int serach_start_index = 0; //
//         ProgressiveHybirdAStar 渐进式hybird A*搜索函数输入形参-从哪个索引处开始搜索 std::vector<Trajectory_Point>
//         temp_tra_start, temp_tra_end;       // ProgressiveHybirdAStar 渐进式hybird A*搜索函数输入形参-搜索出的轨迹
//         int32 Splice_Point_start_index = -1, Splice_Point_end_index = -1; // ProgressiveHybirdAStar 渐进式hybird
//         A*搜索函数输入形参-记录规划起点、规划终点处的hybird A*拼接轨迹分别记录规划起点、规划终点的hybird
//         A*拼接点的索引

//         float64 distance_min = 1000000;
//         std::vector<Trajectory_Point> temp_trajectory;
//         Trajectory_Point temp_point;

//         // 下面开始遍历dijkstra算法的搜索结果，在遍历到的区域进行轨迹规划，代码较多
//         for (size_t i = 0; i < zone_sequence_.size(); i++)
//         {
//             uint8 temp_area_type;                                               // 0:非结构化 1:结构化
//             temp_area_type = all_zones_.at(zone_sequence_.at(i) - 1).zone_type; // 当前遍历到的区域的类型

//             if (temp_area_type == 0)
//             {

//                 threadLogger_->info("遍历到第{}个非结构化区域*", i + 1);

//                 if (zone_sequence_.size() > 2) // 【当前区域：起点、非结构化——下一个区域：非终点】
//                 {
//                     threadLogger_->info("【当前区域：起点、非结构化——下一个区域：非终点】");

//                     threadLogger_->info("【当前区域：起点、非结构化——下一个区域：常规、结构化】");

//                     uint8 temp_path_id = 0;
//                     if (!FindPathId(zone_sequence_.at(i), zone_sequence_.at(i + 1), zone_sequence_.at(i + 2),
//                     all_zones_.at(zone_sequence_.at(i + 1) - 1).reference_trajs, temp_path_id))
//                     {
//                         threadLogger_->error(" The map file for zone {}  does not have path for turn over",
//                         static_cast<float>(zone_sequence_.at(i + 1)));

//                         return ErrorType::PLANNING_FAIL;
//                     }
//                     temp_traj = all_zones_.at(zone_sequence_.at(i + 1) -
//                     1).reference_trajs.at(temp_path_id).trajectory;

//                     // Trajectory_Point temp_point;
//                     distance_min = 1000000;
//                     unsigned int nearest_id;
//                     for (unsigned int i = 0; i < temp_traj.size(); i++)
//                     {
//                         temp_point = temp_traj.at(i);

//                         if (pow(start_point_.x - temp_point.x, 2) + pow(start_point_.y - temp_point.y, 2) <
//                         distance_min)
//                         {
//                             distance_min = pow(start_point_.x - temp_point.x, 2) + pow(start_point_.y - temp_point.y,
//                             2); nearest_id = i;
//                         }
//                     }
//                     threadLogger_->info("规划起点匹配到的nearest_id：{}", nearest_id);

//                     // 参数顺序解释：输入点、hybird
//                     A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                     input_point = start_point_;
//                     search_zone = zone_sequence_.at(i);
//                     Trajectory_be_searched = temp_traj;
//                     serach_start_index = nearest_id;
//                     uint8 hybird_rule_id = 5;
//                     if (!ProgressiveHybirdAStar(input_point, search_zone, true, Trajectory_be_searched,
//                     serach_start_index, Splice_Point_start_index, temp_tra_start, hybird_rule_id))
//                     {
//                         // 反馈规划起点附近hybird A*轨迹拼接失败
//                         threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                         return ErrorType::PLANNING_FAIL;
//                     }

//                     global_path_.insert(global_path_.end(), temp_tra_start.begin(), temp_tra_start.end());
//                 }
//                 else // 下一个区域是终点所在区域,在planningcase5中只可能是结构化区域
//                 【当前区域：起点、非结构化——————下一个区域：终点、结构化】
//                 {
//                     threadLogger_->info("【当前区域：起点、非结构化——————下一个区域：终点、结构化】");

//                     threadLogger_->info("【当前区域：起点、非结构化——————下一个区域：终点、结构化、直走】");

//                     if (end_point_to_pre_area) // 【当前区域：起点、非结构化——————下一个区域：终点、结构化、
//                     终点靠近前一个区域】
//                     {
//                         // std::vector<Trajectory_Point> temp_trajectory;

//                         // rule_id:5n前向规划失败，换rule_id:0的普通规划
//                         if (!ApplyHibridAStar(start_point_, end_point_, start_node_, temp_trajectory, 0))
//                         {
//                             threadLogger_->error("Hybird A*无法规划出当前起点至终点的路径");

//                             return ErrorType::PLANNING_FAIL;
//                             // 反馈hybird A*直接搜索起点到终点的失败error
//                         }

//                         global_path_.insert(global_path_.end(), temp_trajectory.begin(), temp_trajectory.end());
//                     }
//                     else // 【当前区域：起点、非结构化——————下一个区域：终点、结构化、 终点远离前一个区域】
//                     {
//                         threadLogger_->info("【当前区域：起点、非结构化——————下一个区域：终点、结构化、
//                         终点远离前一个区域】");

//                         // Trajectory_Point temp_point;
//                         distance_min = 1000000;
//                         unsigned int nearest_id;
//                         temp_traj = end_trajectory.trajectory;
//                         for (unsigned int i = 0; i < temp_traj.size(); i++)
//                         {
//                             temp_point = temp_traj.at(i);

//                             if (pow(start_point_.x - temp_point.x, 2) + pow(start_point_.y - temp_point.y, 2) <
//                             distance_min)
//                             {
//                                 distance_min = pow(start_point_.x - temp_point.x, 2) + pow(start_point_.y -
//                                 temp_point.y, 2); nearest_id = i;
//                             }
//                         }

//                         threadLogger_->info("规划起点即将进行Hybird A*轨迹拟合");

//                         // 参数顺序解释：输入点、hybird
//                         A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                         input_point = start_point_;
//                         search_zone = zone_sequence_.at(i);
//                         Trajectory_be_searched = temp_traj;
//                         serach_start_index = nearest_id;
//                         uint8 hybird_rule_id = 5;
//                         if (!ProgressiveHybirdAStar(input_point, search_zone, true, Trajectory_be_searched,
//                         serach_start_index, Splice_Point_start_index, temp_tra_start, hybird_rule_id))
//                         {
//                             // 反馈规划起点附近hybird A*轨迹拼接失败
//                             threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                             return ErrorType::PLANNING_FAIL;
//                         }
//                         global_path_.insert(global_path_.end(), temp_tra_start.begin(), temp_tra_start.end());
//                     }
//                 }
//             }
//             else // 当前遍历到的区域为结构化区域，在planningcase5中，结构化区域只能是中间区域、或最后一个区域
//             {
//                 if (i != zone_sequence_.size() - 1) // 当前区域为中间的结构化区域
//                 【上一个区域：未知———当前区域：常规、结构化——下一个区域：未知】
//                 {
//                     threadLogger_->info("遍历到第{} 个结构化区域", i + 1);

//                     uint8 temp_path_id = 0;
//                     if (!FindPathId(zone_sequence_.at(i - 1), zone_sequence_.at(i), zone_sequence_.at(i + 1),
//                     all_zones_.at(zone_sequence_.at(i) - 1).reference_trajs, temp_path_id))
//                     {
//                         threadLogger_->error(" The map file for zone {}  does not have path for turn over ",
//                         static_cast<float>(zone_sequence_.at(i)));

//                         return ErrorType::PLANNING_FAIL;
//                     }
//                     temp_traj = all_zones_.at(zone_sequence_.at(i) - 1).reference_trajs.at(temp_path_id).trajectory;
//                     int32 Crop_start_Point = -1, Crop_end_Point = -1;
//                     bool has_start_hy = false, has_end_hy = false;
//                     if (i != 1) // 【上一个区域：常规———当前区域：常规、结构化】
//                     {
//                         threadLogger_->info("【上一个区域：常规———当前区域：常规、结构化】");

//                         if (all_zones_.at(zone_sequence_.at(i - 1) - 1).zone_type == 1) //
//                         【上一个区域：常规、结构化———当前区域：常规、结构化】
//                         {
//                             threadLogger_->info("【上一个区域：常规、结构化———当前区域：常规、结构化】");

//                             Crop_start_Point = 0;
//                         }
//                         else // 【上一个区域：常规、非结构化———当前区域：常规、结构化】
//                         {
//                             threadLogger_->info("【上一个区域：常规、非结构化———当前区域：常规、结构化】");

//                             has_start_hy = true;
//                             Crop_start_Point = Splice_Point_start_index;
//                         }
//                     }
//                     else // 【上一个区域：起点、非结构化———当前区域：常规、结构化】
//                     {
//                         threadLogger_->info("【上一个区域：起点、非结构化———当前区域：常规、结构化】");

//                         has_start_hy = true;
//                         Crop_start_Point = Splice_Point_start_index;
//                     }
//                     if (i + 1 != zone_sequence_.size() - 1) // 【当前区域：常规、结构化——下一个区域：常规】
//                     {
//                         threadLogger_->info("【当前区域：常规、结构化——下一个区域：常规】");

//                         Crop_end_Point = temp_traj.size() - 1;
//                     }
//                     else // 【当前区域：常规、结构化——下一个区域：终点、结构化】
//                     {
//                         threadLogger_->info("【当前区域：常规、结构化——下一个区域：终点、结构化】");

//                         threadLogger_->info("【当前区域：常规、结构化——下一个区域：终点、结构化、直走】");

//                         if (end_point_to_pre_area) // 【当前区域：常规、结构化——————下一个区域：终点、结构化、
//                         终点靠近当前区域】
//                         {
//                             threadLogger_->info("【当前区域：常规、结构化——————下一个区域：终点、结构化、
//                             终点靠近当前区域】");

//                             if (end_flag)
//                             {
//                                 threadLogger_->info("规划终点需要进行hybird A*拟合");

//                                 // 参数顺序解释：输入点、hybird
//                                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                                 input_point = end_point_;
//                                 search_zone = zone_sequence_.at(i);
//                                 Trajectory_be_searched = temp_traj;
//                                 serach_start_index = temp_traj.size() - 1;
//                                 uint8 hybird_rule_id = 5;
//                                 if (!ProgressiveHybirdAStar(input_point, search_zone, false, Trajectory_be_searched,
//                                 serach_start_index, Splice_Point_end_index, temp_tra_end, hybird_rule_id))
//                                 {
//                                     // 反馈规划起点附近hybird A*轨迹拼接失败
//                                     threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                     return ErrorType::PLANNING_FAIL;
//                                 }
//                                 has_end_hy = true;
//                                 Crop_end_Point = Splice_Point_end_index;
//                             }
//                             else
//                             {
//                                 threadLogger_->info("规划终点不需要进行hybird A*拟合");

//                                 Crop_end_Point = temp_traj.size() - 1;
//                             }
//                         }
//                         else // 【当前区域：常规、结构化——————下一个区域：终点、结构化、 终点远离前一个区域】
//                         {
//                             threadLogger_->info("【当前区域：常规、结构化——————下一个区域：终点、结构化、
//                             终点远离前一个区域】");

//                             Crop_end_Point = temp_traj.size() - 1;
//                         }
//                     }
//                     if (Crop_end_Point < Crop_start_Point && Crop_end_Point > 0)
//                     {
//                         return ErrorType::PLANNING_FAIL;
//                     }
//                     // 开始拼接轨迹
//                     if (has_start_hy)
//                     {
//                         if (has_end_hy)
//                         {

//                             global_path_.insert(global_path_.end(), temp_traj.begin() + Crop_start_Point + 1,
//                             temp_traj.begin() + Crop_end_Point); global_path_.insert(global_path_.end(),
//                             temp_tra_end.begin(), temp_tra_end.end());
//                         }
//                         else
//                         {
//                             global_path_.insert(global_path_.end(), temp_traj.begin() + Crop_start_Point + 1,
//                             temp_traj.end());
//                         }
//                     }
//                     else
//                     {
//                         if (has_end_hy)
//                         {

//                             global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() +
//                             Crop_end_Point); global_path_.insert(global_path_.end(), temp_tra_end.begin(),
//                             temp_tra_end.end());
//                         }
//                         else
//                         {
//                             global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.end());
//                         }
//                     }
//                 }
//                 else // 最后一个结构化区域
//                 {
//                     threadLogger_->info("遍历到第{} 个结构化区域", i + 1);

//                     temp_traj = end_trajectory.trajectory;
//                     if (zone_sequence_.size() == 2) // 【上一个区域：起点、非结构化———当前区域：终点、结构化】
//                     {
//                         threadLogger_->info("【上一个区域：起点、非结构化———当前区域：终点、结构化】");

//                         threadLogger_->info("【上一个区域：起点、非结构化———当前区域：终点、结构化、直走】");

//                         if (end_point_to_pre_area) // 【上一个区域：起点、非结构化———当前区域：终点、结构化、
//                         规划终点靠近上一个区域】
//                         {
//                             threadLogger_->info("【上一个区域：起点、非结构化———当前区域：终点、结构化、
//                             规划终点靠近上一个区域】");

//                             threadLogger_->info("do nothing");

//                             // do nothing
//                         }
//                         else // 【上一个区域：起点、非结构化———当前区域：终点、结构化、 规划终点远离上一个区域】
//                         {
//                             threadLogger_->info("【上一个区域：起点、非结构化———当前区域：终点、结构化、
//                             规划终点远离上一个区域】");

//                             if (end_flag)
//                             {
//                                 threadLogger_->info("规划终点需要hybird A*軌跡拼接");

//                                 // 参数顺序解释：输入点、hybird
//                                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                                 input_point = end_point_;
//                                 search_zone = zone_sequence_.at(i);
//                                 Trajectory_be_searched = temp_traj;
//                                 serach_start_index = end_nearest_id;
//                                 uint8 hybird_rule_id = 5;
//                                 if (!ProgressiveHybirdAStar(input_point, search_zone, false, Trajectory_be_searched,
//                                 serach_start_index, Splice_Point_end_index, temp_tra_end, hybird_rule_id))
//                                 {
//                                     // 反馈规划起点附近hybird A*轨迹拼接失败
//                                     threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                     return ErrorType::PLANNING_FAIL;
//                                 }
//                             }
//                             if (end_flag)
//                             {
//                                 global_path_.insert(global_path_.end(), temp_traj.begin() + Splice_Point_start_index
//                                 + 1, temp_traj.begin() + Splice_Point_end_index);
//                                 global_path_.insert(global_path_.end(), temp_tra_end.begin(), temp_tra_end.end());
//                             }
//                             else
//                             {
//                                 threadLogger_->info("Splice_Point_start_index:{}", Splice_Point_start_index);

//                                 global_path_.insert(global_path_.end(), temp_traj.begin() + Splice_Point_start_index
//                                 + 1, temp_traj.begin() + end_nearest_id + 1);
//                             }
//                         }
//                     }
//                     else // 【上一个区域：非起点———当前区域：终点、结构化】
//                     {
//                         threadLogger_->info("【上一个区域：非起点———当前区域：终点、结构化】");

//                         if (all_zones_.at(zone_sequence_.at(i - 1) - 1).zone_type == 1) //
//                         【上一个区域：常规、结构化———当前区域：终点、结构化】
//                         {
//                             threadLogger_->info("【上一个区域：常规、结构化———当前区域：终点、结构化】");

//                             if (end_point_to_pre_area) // 【上一个区域：常规、结构化———当前区域：终点、结构化、
//                             规划终点靠近上一个区域】
//                             {
//                                 threadLogger_->info("【上一个区域：常规、结构化———当前区域：终点、结构化、
//                                 规划终点靠近上一个区域】");

//                                 if (end_flag)
//                                 {
//                                     threadLogger_->info("do nothing");

//                                     // do nothing
//                                 }
//                                 else
//                                 {
//                                     threadLogger_->info("temp_traj.size(): {}", temp_traj.size());

//                                     global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() +
//                                     end_nearest_id + 1);
//                                 }
//                             }
//                             else // 【上一个区域：常规、结构化———当前区域：终点、结构化、 规划终点远离上一个区域】
//                             {
//                                 threadLogger_->info("【上一个区域：常规、结构化———当前区域：终点、结构化、
//                                 规划终点远离上一个区域】");

//                                 if (end_flag)
//                                 {
//                                     threadLogger_->info("规划终点需要进行hybird A*拼接");

//                                     // 参数顺序解释：输入点、hybird
//                                     A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                                     input_point = end_point_;
//                                     search_zone = zone_sequence_.at(i);
//                                     Trajectory_be_searched = end_trajectory.trajectory;
//                                     serach_start_index = end_nearest_id;
//                                     uint8 hybird_rule_id = 5;
//                                     if (!ProgressiveHybirdAStar(input_point, search_zone, false,
//                                     Trajectory_be_searched, serach_start_index, Splice_Point_end_index, temp_tra_end,
//                                     hybird_rule_id))
//                                     {
//                                         // 反馈规划起点附近hybird A*轨迹拼接失败
//                                         threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                         return ErrorType::PLANNING_FAIL;
//                                     }
//                                 }
//                                 else
//                                 {
//                                     threadLogger_->info("规划终点不需要进行hybird A*拼接");
//                                 }
//                                 if (end_flag)
//                                 {
//                                     global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() +
//                                     Splice_Point_end_index); global_path_.insert(global_path_.end(),
//                                     temp_tra_end.begin(), temp_tra_end.end());
//                                 }
//                                 else
//                                 {
//                                     global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() +
//                                     end_nearest_id + 1);
//                                 }
//                             }
//                         }
//                         else // 【上一个区域：常规、非结构化———当前区域：终点、结构化】
//                         {
//                             threadLogger_->info("【上一个区域：常规、非结构化———当前区域：终点、结构化】");

//                             threadLogger_->info("【上一个区域：常规、非结构化———当前区域：终点、结构化、直走】");

//                             if (end_point_to_pre_area) // 【上一个区域：常规、非结构化———当前区域：终点、结构化、
//                             规划终点靠近上一个区域】
//                             {
//                                 threadLogger_->info("【上一个区域：常规、非结构化———当前区域：终点、结构化、
//                                 规划终点靠近上一个区域】");

//                                 if (end_flag)
//                                 {
//                                     threadLogger_->info("do nothing");

//                                     // do nothing
//                                 }
//                             }
//                             else // 【上一个区域：常规、非结构化———当前区域：终点、结构化、 规划终点远离上一个区域】
//                             {
//                                 threadLogger_->info("【上一个区域：常规、非结构化———当前区域：终点、结构化、
//                                 规划终点远离上一个区域】");

//                                 if (end_flag)
//                                 {
//                                     // 参数顺序解释：输入点、hybird
//                                     A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                                     input_point = end_point_;
//                                     search_zone = zone_sequence_.at(i);
//                                     Trajectory_be_searched = end_trajectory.trajectory;
//                                     serach_start_index = end_nearest_id;
//                                     uint8 hybird_rule_id = 5;
//                                     if (!ProgressiveHybirdAStar(input_point, search_zone, false,
//                                     Trajectory_be_searched, serach_start_index, Splice_Point_end_index, temp_tra_end,
//                                     hybird_rule_id))
//                                     {
//                                         // 反馈规划起点附近hybird A*轨迹拼接失败
//                                         threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                                         return ErrorType::PLANNING_FAIL;
//                                     }
//                                 }
//                                 if (end_flag)
//                                 {
//                                     global_path_.insert(global_path_.end(), temp_traj.begin() +
//                                     Splice_Point_start_index + 1, temp_traj.begin() + Splice_Point_end_index - 1);
//                                     global_path_.insert(global_path_.end(), temp_tra_end.begin(),
//                                     temp_tra_end.end());
//                                 }
//                                 else
//                                 {
//                                     global_path_.insert(global_path_.end(), temp_traj.begin() +
//                                     Splice_Point_start_index + 1, temp_traj.begin() + end_nearest_id + 1);
//                                 }
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//         return ErrorType::SUCCESS;
//     }
//     else
//     {
//         threadLogger_->info("The map file for zone {} does not have any reference path ", (float)end_node_);

//         return ErrorType::NO_REFERENCELINE;
//     }
// }

// /**
//  * @brief 起始点和终止点不在同一区域，且起点、终点为非结构化道路
//  * @param [in] 无
//  * @param [return] true: 规划成功；false：规划失败
//  */
// ErrorType Planning::PlanningCase6()
// {
//     threadLogger_->info("Enter PlanningCase6");

//     if (zone_sequence_.size() < 2) // planningcase6不会出现此情况
//     {
//         return ErrorType::PLANNING_FAIL;
//     }
//     global_path_.clear(); // 清空全局轨迹容器

//     // 记录针对哪条参考轨迹进行裁剪
//     vector<Trajectory_Point> temp_traj;

//     Single_Point input_point;                                         // ProgressiveHybirdAStar 渐进式hybird
//     A*搜索函数输入形参-规划输入点 uint8 search_zone;                                                //
//     ProgressiveHybirdAStar 渐进式hybird A*搜索函数输入形参-当前规划区域 vector<Trajectory_Point>
//     Trajectory_be_searched;                  // ProgressiveHybirdAStar 渐进式hybird
//     A*搜索函数输入形参-在哪条参考轨迹上搜索hybird A*拟合点 unsigned int serach_start_index = 0; //
//     ProgressiveHybirdAStar 渐进式hybird A*搜索函数输入形参-从哪个索引处开始搜索 std::vector<Trajectory_Point>
//     temp_tra_start, temp_tra_end;
//     // ProgressiveHybirdAStar 渐进式hybird A*搜索函数输入形参-搜索出的轨迹 int32 Splice_Point_start_index = -1,
//     Splice_Point_end_index = -1; // ProgressiveHybirdAStar 渐进式hybird
//     A*搜索函数输入形参-记录规划起点、规划终点处的hybird A*拼接轨迹分别记录规划起点、规划终点的hybird A*拼接点的索引

//     float64 distance_min = 1000000;
//     std::vector<Trajectory_Point> temp_trajectory;
//     Trajectory_Point temp_point;

//     // 下面开始遍历dijkstra算法的搜索结果，在遍历到的区域进行轨迹规划，代码较多
//     for (size_t i = 0; i < zone_sequence_.size(); i++)
//     {
//         uint8 temp_area_type;                                               // 0:非结构化 1:结构化
//         temp_area_type = all_zones_.at(zone_sequence_.at(i) - 1).zone_type; // 当前遍历到的区域的类型

//         if (temp_area_type == 0)
//         {
//             if (i == 0) // 第一个非结构化区域
//             {
//                 threadLogger_->info("遍历到第{}个非结构化区域*", i + 1);

//                 threadLogger_->info("【当前区域：起点、非结构化——下一个区域：非终点】");

//                 threadLogger_->info("【当前区域：起点、非结构化——下一个区域：常规、结构化】");

//                 uint8 temp_path_id = 0;
//                 if (!FindPathId(zone_sequence_.at(i), zone_sequence_.at(i + 1), zone_sequence_.at(i + 2),
//                 all_zones_.at(zone_sequence_.at(i + 1) - 1).reference_trajs, temp_path_id))
//                 {
//                     threadLogger_->error(" The map file for zone {} does not have path for turn over ",
//                     static_cast<float>(zone_sequence_.at(i + 1)));

//                     return ErrorType::PLANNING_FAIL;
//                 }
//                 temp_traj = all_zones_.at(zone_sequence_.at(i + 1) - 1).reference_trajs.at(temp_path_id).trajectory;

//                 // Trajectory_Point temp_point;
//                 distance_min = 1000000;
//                 unsigned int nearest_id;
//                 for (unsigned int i = 0; i < temp_traj.size(); i++)
//                 {
//                     temp_point = temp_traj.at(i);

//                     if (pow(start_point_.x - temp_point.x, 2) + pow(start_point_.y - temp_point.y, 2) < distance_min)
//                     {
//                         distance_min = pow(start_point_.x - temp_point.x, 2) + pow(start_point_.y - temp_point.y, 2);
//                         nearest_id = i;
//                     }
//                 }
//                 threadLogger_->info("规划起点匹配到的nearest_id：{}", nearest_id);
//                 // 参数顺序解释：输入点、hybird
//                 A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                 input_point = start_point_;
//                 search_zone = zone_sequence_.at(i);
//                 Trajectory_be_searched = temp_traj;
//                 serach_start_index = nearest_id;
//                 uint8 hybird_rule_id = 5;
//                 if (!ProgressiveHybirdAStar(input_point, search_zone, true, Trajectory_be_searched,
//                 serach_start_index, Splice_Point_start_index, temp_tra_start, hybird_rule_id))
//                 {
//                     // 反馈规划起点附近hybird A*轨迹拼接失败
//                     threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                     return ErrorType::PLANNING_FAIL;
//                 }
//                 global_path_.insert(global_path_.end(), temp_tra_start.begin(), temp_tra_start.end());
//             }
//             else
//             {
//                 threadLogger_->info("遍历到第{}个非结构化区域", i + 1);

//                 threadLogger_->info("上一个区域：常规 、结构化——当前区域：终点、非结构化");

//                 threadLogger_->info("do nothing");

//                 // do nothing
//             }
//         }
//         else // 当前遍历到的区域为结构化区域，在planningcase6中，结构化区域只可能是中间区域
//         {

//             threadLogger_->info("遍历到第{} 个结构化区域", i + 1);

//             uint8 temp_path_id = 0;
//             if (!FindPathId(zone_sequence_.at(i - 1), zone_sequence_.at(i), zone_sequence_.at(i + 1),
//             all_zones_.at(zone_sequence_.at(i) - 1).reference_trajs, temp_path_id))
//             {
//                 threadLogger_->error(" The map file for zone {} does not have path for turn over",
//                 static_cast<float>(zone_sequence_.at(i)));

//                 return ErrorType::PLANNING_FAIL;
//             }
//             temp_traj = all_zones_.at(zone_sequence_.at(i) - 1).reference_trajs.at(temp_path_id).trajectory;
//             int32 Crop_start_Point = -1, Crop_end_Point = -1;
//             bool has_start_hy = false, has_end_hy = false;
//             if (i != 1) // 【上一个区域：常规———当前区域：常规、结构化】
//             {
//                 threadLogger_->info("【上一个区域：常规———当前区域：常规、结构化】");

//                 if (all_zones_.at(zone_sequence_.at(i - 1) - 1).zone_type == 1) //
//                 【上一个区域：常规、结构化———当前区域：常规、结构化】
//                 {
//                     threadLogger_->info("【上一个区域：常规、结构化———当前区域：常规、结构化】");

//                     Crop_start_Point = 0;
//                 }
//                 else // 【上一个区域：常规、非结构化———当前区域：常规、结构化】
//                 {
//                     threadLogger_->info("【上一个区域：常规、非结构化———当前区域：常规、结构化】");

//                     has_start_hy = true;
//                     Crop_start_Point = Splice_Point_start_index;
//                 }
//             }
//             else // 【上一个区域：起点、非结构化———当前区域：常规、结构化】
//             {
//                 threadLogger_->info("【上一个区域：起点、非结构化———当前区域：常规、结构化】");

//                 has_start_hy = true;
//                 Crop_start_Point = Splice_Point_start_index;
//             }
//             if (i + 1 != zone_sequence_.size() - 1) // 【当前区域：常规、结构化——下一个区域：常规】
//             {
//                 threadLogger_->info("【当前区域：常规、结构化——下一个区域：常规】");

//                 Crop_end_Point = temp_traj.size() - 1;
//                 // 开始拼接轨迹
//                 if (has_start_hy)
//                 {

//                     global_path_.insert(global_path_.end(), temp_traj.begin() + Crop_start_Point, temp_traj.begin() +
//                     Crop_end_Point);
//                 }
//                 else
//                 {

//                     global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() + Crop_end_Point);
//                 }
//             }
//             else // 【当前区域：常规、结构化——下一个区域：终点、非结构化】
//             {
//                 threadLogger_->info("【当前区域：常规、结构化——下一个区域：终点、非结构化】");

//                 // 由于结构化区域的参考轨迹可能伸入到非结构化区域，需要找到参考线上距离终点的最近点，以此点为搜索起点

//                 distance_min = 1000000;
//                 unsigned int nearest_id;
//                 for (unsigned int i = 0; i < temp_traj.size(); i++)
//                 {
//                     temp_point = temp_traj.at(i);

//                     if (pow(end_point_.x - temp_point.x, 2) + pow(end_point_.y - temp_point.y, 2) < distance_min)
//                     {
//                         distance_min = pow(end_point_.x - temp_point.x, 2) + pow(end_point_.y - temp_point.y, 2);
//                         nearest_id = i;
//                     }
//                 }
//                 threadLogger_->info("检索的最近点的距离信息：{}", sqrt(distance_min));

//                 bool Need_hybird_A_star = true;
//                 // 判断找到 的最近的点距离den_point之间的几何距离，小于0.2m就不进行hybird A*拟合
//                 float dis = sqrt(pow(temp_traj.at(nearest_id).x - end_point_.x, 2) + pow(temp_traj.at(nearest_id).y -
//                 end_point_.y, 2)); threadLogger_->info("终点与匹配上的参考轨迹的最近点的几何距离：{}", dis);

//                 if (dis > 0.1)
//                     Need_hybird_A_star = true;
//                 else
//                     Need_hybird_A_star = false;
//                 threadLogger_->info("Need_hybird_A_star:{}", (int)Need_hybird_A_star);

//                 if (Need_hybird_A_star)
//                 {
//                     // 参数顺序解释：输入点、hybird
//                     A*规划区域、搜索方向、在哪条轨迹上搜索、从当前轨迹上哪个索引处开始搜索、搜索到的轨迹点索引、hybirdA*最终拟合出的轨迹
//                     input_point = end_point_;
//                     search_zone = zone_sequence_.at(i);
//                     Trajectory_be_searched = temp_traj;
//                     serach_start_index = nearest_id;
//                     uint8 hybird_rule_id = 5;
//                     // if (dis < 5)
//                     //     hybird_rule_id = 5;
//                     // else
//                     //     hybird_rule_id = 0;
//                     if (!ProgressiveHybirdAStar(input_point, search_zone, false, Trajectory_be_searched,
//                     serach_start_index, Splice_Point_end_index, temp_tra_end, hybird_rule_id))
//                     {
//                         // 反馈规划起点附近hybird A*轨迹拼接失败
//                         threadLogger_->error("规划起点附近hybird A*轨迹拼接失败");

//                         return ErrorType::PLANNING_FAIL;
//                     }

//                     Crop_end_Point = Splice_Point_end_index;
//                     if (Crop_end_Point < Crop_start_Point && Crop_end_Point > 0)
//                     {
//                         threadLogger_->error("拼接點衝突");

//                         return ErrorType::PLANNING_FAIL;
//                     }
//                 }
//                 else
//                 {
//                     Crop_end_Point = temp_traj.size() - 1;
//                 }

//                 // 开始拼接轨迹
//                 if (has_start_hy)
//                 {
//                     global_path_.insert(global_path_.end(), temp_traj.begin() + Crop_start_Point + 1,
//                     temp_traj.begin() + Crop_end_Point); threadLogger_->info("temp_tra_end.size():{}",
//                     temp_tra_end.size()); global_path_.insert(global_path_.end(), temp_tra_end.begin(),
//                     temp_tra_end.end());
//                 }
//                 else
//                 {

//                     global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.begin() + Crop_end_Point);
//                     threadLogger_->info("temp_tra_end.size():{}", temp_tra_end.size());
//                     global_path_.insert(global_path_.end(), temp_tra_end.begin(), temp_tra_end.end());
//                 }
//             }
//         }
//     }
//     return ErrorType::SUCCESS;
// }

// /**
//  * @brief 设置非结构化得到路径的限速（设置为区域限速），倒车的限速设置在全局速度规划模块有处理
//  * @param [in] temp_path：需设置的路径； max_speed：最大速度
//  * @param [return]
//  */
// void Planning::SetMaxSpeed(std::vector<Trajectory_Point> &temp_path, float max_speed)
// {
//     for (int i = 0; i < temp_path.size(); i++)
//     {
//         temp_path.at(i).speed_limit = max_speed;
//     }
// }

// float Planning::CalNearestDistance(Single_Point point, Single_Border border_points)
// {
//     float temp_distance, min_distance;
//     min_distance = DBL_MAX;
//     for (size_t i = 0; i < border_points.border_points.size(); i++)
//     {
//         temp_distance = sqrt(pow((point.x - border_points.border_points.at(i).x), 2) +
//                              pow((point.y - border_points.border_points.at(i).y), 2));
//         if (min_distance > (fabs(temp_distance) + 1e-2))
//         {
//             min_distance = temp_distance;
//         }
//     }
//     return min_distance;
// }
// /**


// /**
//  * @brief 判断点是否在给定的区域边界
//  * @param [in] 点，区域边界点集
//  * @param [return] true：在该边界内部；false：在该边界外部 或者 边上
//  */
// bool Planning::PointInZone(Single_Point point, Single_Border border)
// {
//     int nCross = 0;                                       // 定义变量，统计目标点向右画射线与多边形相交次数
//     for (int i = 0; i < border.border_points.size(); i++) // 遍历多边形每一个节点
//     {
//         Single_Border_Point p1;
//         Single_Border_Point p2;

//         p1 = border.border_points.at(i);
//         p2 = border.border_points.at((i + 1) % border.border_points.size()); //
//         p1是这个节点，p2是下一个节点，两点连线是多边形的一条边
//                                                                              // 以下算法是用是先以y轴坐标来判断的
//         if (p1.y == p2.y)
//             continue;                  // 如果这条边是水平的，跳过
//         if (point.y < min(p1.y, p2.y)) // 如果目标点低于这个线段，跳过
//             continue;
//         if (point.y >= max(p1.y, p2.y)) // 如果目标点高于这个线段，跳过
//             continue;
//         // 那么下面的情况就是：如果过p1画水平线，过p2画水平线，目标点在这两条线中间
//         double x = (double)(point.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;
//         // 这段的几何意义是 过目标点，画一条水平线，x是这条线与多边形当前边的交点x坐标
//         if (x > point.x)
//             nCross++; //
//             如果交点在右边，统计加一。这等于从目标点向右发一条射线（ray），与多边形各边的相交（crossing）次数
//     }
//     if (nCross % 2 == 1)
//         return true; // 如果是奇数，说明在多边形里
//     else
//         return false; // 否则在多边形外 或 边上
// }

// ErrorType Planning::FindReferencePath(Single_Point point, vector<Single_Trajectory> &trajs, unsigned int &nearest_id,
// uint8 &path_id, bool flag, map<uint8, double> &v_id, double search_distance)
// {
//     v_id.clear();
//     if (flag == true)
//     {
//         threadLogger_->info("为起点寻找参考线");
//     }
//     else
//     {
//         threadLogger_->info("为终点寻找参考线");
//     }

//     if (!trajs.size())
//     {
//         threadLogger_->info(" The trajectory.size() = 0  ");
//         return ErrorType::NO_REFERENCELINE;
//     }
//     bool temp_bool = false;
//     unsigned int temp_nearest_id;
//     float temp_distance, min_distance;
//     min_distance = 1000000;
//     // 匹配原则
//     // 同一区域找大致
//     // 不同区域找最近，并需要结合dijkstra搜索结果进行参考路径筛选
//     unsigned int type = 0;
//     double lat_distance = 0;
//     for (unsigned int i = 0; i < trajs.size(); i++)
//     {
//         threadLogger_->info("当前匹配轨迹ID:{},start:{},curr:{},end:{}", (int)trajs.at(i).id,
//         (int)trajs.at(i).start_zone_id, (int)trajs.at(i).current_zone_id, (int)trajs.at(i).end_zone_id);

//         if (start_node_ == end_node_)
//         {
//             if (FindSuitableReferenceLine(point, trajs.at(i), search_distance, lat_distance)) //
//             寻找大致合适的参考路径
//             {
//                 threadLogger_->info("当前匹配轨迹符合要求，纳入候选列表");
//                 temp_bool = true;
//                 v_id.insert(pair<uint8, double>(i, lat_distance));
//             }
//         }
//         else
//         {

//             if (flag == true)
//             {
//                 if (trajs.at(i).end_zone_id != zone_sequence_.at(1))
//                 {
//                     continue;
//                 }
//             }
//             else
//             {
//                 if (trajs.at(i).start_zone_id != zone_sequence_.at(zone_sequence_.size() - 2))
//                 {
//                     continue;
//                 }
//             }
//             if (FindNearestPoint(point, trajs.at(i), temp_distance, temp_nearest_id))
//             {
//                 if (temp_distance < min_distance)
//                 {
//                     min_distance = temp_distance;
//                     threadLogger_->info("min_distance:{}", min_distance);
//                     nearest_id = temp_nearest_id;
//                     temp_bool = true;
//                     path_id = i;
//                     threadLogger_->info("min_distance:{} , nearest_id:{},ID:{}", min_distance, nearest_id, i + 1);
//                 }
//             }
//         }
//     }

//     if (temp_bool == true)
//     {
//         return ErrorType::SUCCESS;
//     }

//     threadLogger_->info("没有符合要求的参考路径");
//     if (flag == true)
//     {
//         return ErrorType::START_POINT_UNREASONABLE;
//     }
//     else
//     {
//         return ErrorType::END_POINT_UNREASONABLE;
//     }
// }

// bool Planning::FindSuitableReferenceLine(Single_Point point, Single_Trajectory traj, double search_distance, double
// lat_dis)
// {
//     float64 distance_min2 = 1000000;
//     if (!traj.trajectory.size())
//     {
//         threadLogger_->info(" The trajectory does not have points, can not find the nearest point ");

//         return false;
//     }
//     // 找到最近的参考点，判断该参考点是否满足固定要求
//     Trajectory_Point temp_traj_point;
//     threadLogger_->info("traj.trajectory.size():{}", traj.trajectory.size());
//     int nearest_point_index = -1;
//     for (unsigned int i = 0; i < traj.trajectory.size(); i++)
//     {
//         temp_traj_point = traj.trajectory.at(i);
//         float64 temp_distance2 = pow(point.x - temp_traj_point.x, 2) + pow(point.y - temp_traj_point.y, 2);
//         if (temp_distance2 < distance_min2 && ((fabs(point.yaw - temp_traj_point.yaw) / M_PI * 180) < 90 ||
//         (fabs(point.yaw - temp_traj_point.yaw) / M_PI * 180) > 270))
//         {
//             distance_min2 = temp_distance2;
//             nearest_point_index = i;
//         }
//     }

//     // 参考轨迹匹配上的最近点小于2m即纳入备选路径
//     if (distance_min2 < search_distance * search_distance)
//     {
//         Single_Point nearest_point;
//         nearest_point.x = traj.trajectory.at(nearest_point_index).x;
//         nearest_point.y = traj.trajectory.at(nearest_point_index).y;
//         nearest_point.z = traj.trajectory.at(nearest_point_index).z;
//         nearest_point.yaw = traj.trajectory.at(nearest_point_index).yaw;

//         float64 lat_distance; // 起点与参考轨迹最近点的横向距离
//         lat_distance = -(point.x - nearest_point.x) * sin(nearest_point.yaw) + (point.y - nearest_point.y) *
//         cos(nearest_point.yaw); lat_dis = fabs(lat_distance); threadLogger_->info("find suitable referenceline");
//         return true;
//     }
//     else
//     {
//         threadLogger_->info("Cannot find suitable referenceline");
//         return false;
//     }
// }

// /**
//  * @brief 找到最近点id
//  * @param [in] 点坐标，路径，最近距离(引用)，最近点id(引用)
//  * @param [return] true：成功；false：失败
//  */
// bool Planning::FindNearestPoint(Single_Point point, Single_Trajectory traj, float &distance, unsigned int
// &nearest_id)
// {
//     threadLogger_->info("Enter FindnearestPoint function");

//     threadLogger_->info("point-yaw:{}", point.yaw);
//     float64 distance_min2 = 1000000;
//     bool temp_bool = false;
//     if (!traj.trajectory.size())
//     {
//         threadLogger_->info(" The trajectory does not have points, can not find the nearest point ");

//         return false;
//     }
//     Trajectory_Point temp_traj_point;
//     bool flag = false;
//     for (unsigned int i = 0; i < traj.trajectory.size(); i++)
//     {

//         temp_traj_point = traj.trajectory.at(i);
//         float64 temp_distance2 = pow(point.x - temp_traj_point.x, 2) + pow(point.y - temp_traj_point.y, 2);

//         if (temp_distance2 < distance_min2 && ((fabs(point.yaw - temp_traj_point.yaw) / M_PI * 180) < 90 ||
//         (fabs(point.yaw - temp_traj_point.yaw) / M_PI * 180) > 270))
//         {
//             flag = true;
//             distance_min2 = temp_distance2;
//             nearest_id = i;
//             temp_bool = true;
//         }
//     }
//     if (flag == false)
//     {
//         threadLogger_->info("这条轨迹方向与待匹配点的朝向不符");
//     }
//     else
//     {
//         distance = sqrt(distance_min2);
//         threadLogger_->info("这条轨迹方向与待匹配点的朝向存在相符的片段，找到的最近点几何距离为：{},索引为：{}",
//         distance, nearest_id);
//     }
//     return temp_bool;
// }

// /**
//  * @brief 根据起始区域、经过区域、到达区域找到路径id
//  * @param [in] 起始区域id，经过区域id，到达区域id，路径的容器，路径id(引用)
//  * @param [return] true：成功；false：失败
//  */
// bool Planning::FindPathId(uint8 s_id, uint8 c_id, uint8 e_id, vector<Single_Trajectory> &trajs, uint8 &path_id)
// {
//     bool temp = false;
//     //      threadLogger_->info("...the s_id is "<<(float)s_id<<"...\n";
//     //      threadLogger_->info("...the c_id is "<<(float)c_id<<"...\n";
//     //      threadLogger_->info("...the e_id is "<<(float)e_id<<"...\n";
//     for (int i = 0; i < trajs.size(); i++)
//     {
//         uint8 temp_s_id = trajs.at(i).start_zone_id;
//         uint8 temp_c_id = trajs.at(i).current_zone_id;
//         uint8 temp_e_id = trajs.at(i).end_zone_id;
//         //  threadLogger_->info("...the temp_s_id is {}", (float)temp_s_id << "...\n";
//         //  threadLogger_->info("...the temp_c_id is {}", (float)temp_c_id << "...\n";
//         //  threadLogger_->info("...the temp_e_id is {}", (float)temp_e_id << "...\n"
//         //            << "\n";

//         if (s_id == temp_s_id && c_id == temp_c_id && e_id == temp_e_id) //
//         目前假定一个方向只有一个参考路径，找到一个满足要求的即可
//         {
//             path_id = i;
//             temp = true;
//             break;
//         }
//     }
//     return temp;
// }

// /**
//  * @brief 两个点之间的三次样条曲线插值
//  * @param [in] 无
//  * @param [return] 无
//  */
// void Planning::Interpolate(float64 x0, float64 y0, float theta0,
//                            float64 x1, float64 y1, float theta1,
//                            std::vector<Trajectory_Point> &path)
// {
//     /*
//         1. 将起点和终点的角度取值范围转换为[-π,π]；
//         2. 计算坐标旋转角度，其等于起点角度加终点角度的一半；
//         3. 将坐标系进行旋转平移，得到新坐标系下起点和终点的位置与角度信息；
//         4. 计算三次样条曲线的各项参数。
//         5. 从起点开始，以0.01m的采样距离对x坐标进行等距采样，并计算相应的y坐标、角度和曲率；
//         6. 将坐标系还原，得到还原后每个采样点的坐标，输出路径
//     */

//     Mod2Pi(theta0);
//     Mod2Pi(theta1);

//     /* 坐标系旋转角度 */
//     float64 theta_r = mod((theta1 + theta0) / 2, 2 * M_PI);
//     /* 旋转 */
//     float64 thet1_r = mod(theta0 - theta_r, 2 * M_PI);
//     float64 x2_r = (x1 - x0) * cos(theta_r) + (y1 - y0) * sin(theta_r);
//     float64 y2_r = (y1 - y0) * cos(theta_r) - (x1 - x0) * sin(theta_r);
//     float64 theta2_r = mod(theta1 - theta_r, 2 * M_PI);
//     /* 三次样条曲线插值 */
//     float64 a = (tan(theta2_r) * x2_r - 2 * y2_r + tan(thet1_r) * x2_r) / pow(x2_r, 3);
//     float64 b = (y2_r - tan(thet1_r) * x2_r - a * pow(x2_r, 3)) / pow(x2_r, 2);
//     float64 c = tan(thet1_r);
//     float64 d = 0.0;
//     std::vector<Trajectory_Point> path_r;
//     float64 x = 0.0;
//     float64 y;
//     float theta;
//     float64 k; // 曲率
//     Trajectory_Point temp_path_r;

//     unsigned int num = floor(fabs(x2_r) / 0.01);
//     float64 delta_x = 0.01 * siG(x2_r);
//     while (num-- > 0) // 间距0.01m一个点
//     {
//         y = a * pow(x, 3) + b * pow(x, 2) + c * x + d;
//         theta = atan(3 * a * pow(x, 2) + 2 * b * x + c);
//         if (theta > 0)
//             theta = mod(theta, 2 * M_PI);
//         else
//             theta = mod(theta + 2 * M_PI, 2 * M_PI);
//         k = fabs(6 * a * x + 2 * b) / pow(1 + pow(3 * a * pow(x, 2) + 2 * b * x + c, 2), 3 / 2);
//         temp_path_r.x = x;
//         temp_path_r.y = y;
//         temp_path_r.yaw = theta;
//         temp_path_r.curvature = k;
//         path_r.push_back(temp_path_r);
//         x += delta_x;
//     }

//     /* 将旋转平移坐标系下的路径点还原至原坐标系下 */
//     for (size_t index = 0; index < path_r.size(); index++)
//     {
//         x = path_r.at(index).x * cos(-theta_r) + path_r.at(index).y * sin(-theta_r) + x0;
//         y = path_r.at(index).y * cos(-theta_r) - path_r.at(index).x * sin(-theta_r) + y0;
//         theta = mod(path_r.at(index).yaw + theta_r, 2 * M_PI);
//         temp_path_r.x = x;
//         temp_path_r.y = y;
//         temp_path_r.yaw = theta * 180.0 / M_PI;
//         temp_path_r.curvature = path_r.at(index).curvature;
//         path.push_back(temp_path_r);
//     }
// }
// void Planning::CalAcc(std::vector<Trajectory_Point> &temp_path)
// {
//     float last_acc;
//     float delta_length = 1.0;
//     for (int i = 0; i < temp_path.size() - 10; i++)
//     {

//         double delta_speed_square = pow(temp_path.at(i + 10).speed, 2) - pow(temp_path.at(i).speed, 2);
//         temp_path.at(i).acc = delta_speed_square / (2 * delta_length);
//         last_acc = delta_speed_square / (2 * delta_length);
//     }
//     for (int i = temp_path.size() - 10; i < temp_path.size(); i++)
//     {
//         temp_path.at(i).acc = last_acc;
//     }
// }
// /*
//  * @brief 计算路径的曲率信息
//  * @param [in]  temp_path
//  * 返回 temp_path 中的曲率信息
//  */
// void Planning::CalCurv(std::vector<Trajectory_Point> &temp_path)
// {
// #if 1
//     vector<double> vec_x, vec_y, vec_angle;
//     int delta_length = 4;
//     int halflengthmark = 0;
//     double distance_halflength = 0;
//     int s = temp_path.size();
//     for (int i = 0; i < s; i++)
//     {
//         vec_x.push_back(temp_path.at(i).x);
//         vec_y.push_back(temp_path.at(i).y);
//         vec_angle.push_back(temp_path.at(i).yaw);
//     }
//     // 计算前0.5m的点的位置halflengthmark
//     int j = 0;
//     while (j < s - 1)
//     {
//         distance_halflength = distance_halflength + sqrt(pow(vec_x.at(j + 1) - vec_x.at(j), 2) + pow(vec_y.at(j + 1)
//         - vec_y.at(j), 2)); if (distance_halflength >= delta_length / 2)
//         {
//             halflengthmark = j + 1;
//             break;
//         }
//         j++;
//     }

//     // 计算前1.0m点的曲率
//     for (int i = 0; i <= halflengthmark; i++)
//     {
//         double distance_front = 0, distance_back = 0;
//         int k = i;
//         // 计算当前点距离第一个点的距离
//         while (k > 0)
//         {
//             distance_back = distance_back + sqrt(pow(vec_x.at(k) - vec_x.at(k - 1), 2) + pow(vec_y.at(k) - vec_y.at(k
//             - 1), 2)); k--;
//         }
//         k = i;
//         while (k < s - 1)
//         {
//             distance_front = distance_front + sqrt(pow(vec_x.at(k + 1) - vec_x.at(k), 2) + pow(vec_y.at(k + 1) -
//             vec_y.at(k), 2)); if (distance_front >= (delta_length - distance_back))
//             {
//                 double anglew_front = vec_angle.at(k + 1); // 当前点0.5后的点角度
//                 double delta_anglew = anglew_front - vec_angle.at(0);
//                 delta_anglew = fmod((delta_anglew + 3 * M_PI), (2 * M_PI)) - M_PI; //
//                 角度插值转化，避免-180和180处出问题 temp_path.at(i).curvature = delta_anglew / delta_length; break;
//             }
//             k++;
//         }
//     }

//     // 计算末尾前0.5m点的位置
//     double distance_last_halflength = 0;
//     int lasthalflengthmark = 0;
//     j = s - 1;
//     while (j > 0)
//     {
//         distance_last_halflength = distance_last_halflength + sqrt(pow(vec_x.at(j) - vec_x.at(j - 1), 2) +
//         pow(vec_y.at(j) - vec_y.at(j - 1), 2)); if (distance_last_halflength >= (delta_length / 2))
//         {
//             lasthalflengthmark = j - 1;
//             break;
//         }
//         j--;
//     }

//     //%计算末尾0.5米曲率
//     for (int i = lasthalflengthmark; i <= s - 1; i++)
//     {
//         double distance_back = 0;
//         double distance_front = 0;
//         int k = i;
//         while (k < s - 1)
//         {
//             distance_back = distance_back + sqrt(pow(vec_x.at(k + 1) - vec_x.at(k), 2) + pow(vec_y.at(k + 1) -
//             vec_y.at(k), 2)); k++;
//         }
//         k = i;
//         while (k > 0)
//         {
//             distance_front = distance_front + sqrt(pow(vec_x.at(k) - vec_x.at(k - 1), 2) + pow(vec_y.at(k) -
//             vec_y.at(k - 1), 2)); if (distance_front >= (delta_length - distance_back))
//             {
//                 double anglew_back = vec_angle.at(k - 1);
//                 double delta_anglew = vec_angle.at(temp_path.size() - 1) - anglew_back;
//                 delta_anglew = fmod((delta_anglew + 3 * M_PI), (2 * M_PI)) - M_PI;
//                 temp_path.at(i).curvature = delta_anglew / delta_length;
//                 break;
//             }
//             k--;
//         }
//     }

//     // 计算中间曲率
//     for (int i = halflengthmark + 1; i <= lasthalflengthmark - 1; i++)
//     {
//         double distance_back = 0;
//         double distance_front = 0;
//         double anglew_front = 0;
//         double anglew_back = 0;
//         int k = i;
//         while (k < s - 1)
//         {

//             distance_front = distance_front + sqrt(pow(vec_x.at(k + 1) - vec_x.at(k), 2) + pow(vec_y.at(k + 1) -
//             vec_y.at(k), 2)); if (distance_front >= delta_length / 2)
//             {
//                 anglew_front = vec_angle.at(k + 1); // 当前点0.5后的点角度
//                 break;
//             }
//             k++;
//         }
//         k = i;
//         while (k > 0)
//         {

//             distance_back = distance_back + sqrt(pow(vec_x.at(k) - vec_x.at(k - 1), 2) + pow(vec_y.at(k) - vec_y.at(k
//             - 1), 2)); if (distance_back >= delta_length / 2)
//             {
//                 anglew_back = vec_angle.at(k - 1);
//                 break;
//             }
//             k--;
//         }
//         double delta_anglew = anglew_front - anglew_back;
//         delta_anglew = fmod((delta_anglew + 3 * M_PI), (2 * M_PI)) - M_PI;
//         temp_path.at(i).curvature = delta_anglew / delta_length;
//     }
// #endif
// #if 0
//    unsigned int nums = 100;
//    for(unsigned int i = 0; i<temp_path.size(); i++)
//    {
//      unsigned int id1;
//      if (i <= nums)
//        id1 = 0;
//      else
//        id1 = i - nums;
//      unsigned int id2 = i + nums < temp_path.size() ? i + nums : temp_path.size()-1;
//      float delta_d =
//      sqrt(pow(temp_path.at(id1).x-temp_path.at(id2).x,2)+pow(temp_path.at(id1).y-temp_path.at(id2).y,2));//两点之间的弦长
//      float delta_angle = (temp_path.at(id2).yaw - temp_path.at(id1).yaw) / M_PI * 180.0;//两点之间的角度差
//      delta_angle = fmod(delta_angle+720,360);
//      if(delta_angle > 180)
//        delta_angle = -(360 - delta_angle);
//      float curv = delta_angle/delta_d/180*3.1415926;
//      temp_path.at(i).curvature = curv;
//    }
// #endif
//     // 将曲率保存到本地
//     // std::ofstream file_out;
//     // file_out.open("curvature_after.txt");
//     // for (size_t index = 0; index < temp_path.size(); index++)
//     // {
//     //     file_out << 0.0 << " " << temp_path.at(index).curvature << endl;
//     // }
//     // file_out.close();
//     threadLogger_->info("CalCurv() function");
// }

// /*
//  * @brief 计算路径的位移信息
//  * @param [in]  temp_path
//  * 返回 temp_path 中的位移信息
//  */
// void Planning::CalDistance(std::vector<Trajectory_Point> &temp_path)
// {
//     temp_path.at(0).distance = 0;
//     double s = 0;
//     for (unsigned int i = 1; i < temp_path.size(); i++)
//     {
//         float64 dx = temp_path.at(i).x - temp_path.at(i - 1).x;
//         float64 dy = temp_path.at(i).y - temp_path.at(i - 1).y;
//         s += sqrt(dx * dx + dy * dy);
//         temp_path.at(i).distance = s;
//     }
//     threadLogger_->info("CalDistance() function");
// }

// /*
//  * @brief 路径的三次曲线插值
//  * @param [in]  temp_path
//  * 返回 无
//  */
// void Planning::Path_Interpolation(std::vector<Trajectory_Point> global_path_, std::vector<Trajectory_Point>
// &temp_path)
// {
//     std::vector<Trajectory_Point> path_s;
//     //    Trajectory_Point temp_point;
//     unsigned int index0 = 0;
//     float64 x0 = global_path_.at(index0).x;
//     float64 y0 = global_path_.at(index0).y;
//     float theta0 = global_path_.at(index0).yaw * M_PI / 180.0;
//     float speed0 = global_path_.at(index0).speed;
//     float64 x1;
//     float64 y1;
//     float theta1;
//     float speed1;
//     temp_path.clear();
//     path_s.clear();
//     for (unsigned int i = 1; i < global_path_.size(); i++)
//     {
//         float delta_dis = global_path_.at(i).distance - global_path_.at(index0).distance;
//         if (delta_dis >= 2 || i == global_path_.size() - 1)
//         {
//             x1 = global_path_.at(i).x;
//             y1 = global_path_.at(i).y;
//             theta1 = global_path_.at(i).yaw * M_PI / 180.0;
//             speed1 = global_path_.at(i).speed;
//             Interpolate(x0, y0, theta0, x1, y1, theta1, path_s);
//             uint16 path_length = path_s.size() - 1 > 0 ? path_s.size() - 1 : 1;
//             for (uint16 j = 0; j <= path_length; j++)
//                 path_s.at(j).speed = speed0 + j * (speed1 - speed0) / path_length;
//             temp_path.insert(temp_path.end(), path_s.begin(), path_s.end());
//             path_s.clear();
//             x0 = x1;
//             y0 = y1;
//             theta0 = theta1;
//             speed0 = speed1;
//             index0 = i;
//         }
//     }
//     threadLogger_->info("Path_interpolation() function");
// }

// /*
//  * @brief 路径的线性插值
//  * @param [in]  temp_path
//  * 返回
//  */
// void Planning::Path_Interpolation_Linear(std::vector<Trajectory_Point> global_path_, std::vector<Trajectory_Point>
// &temp_path)
// {
//     std::vector<Trajectory_Point> path_s;
//     Trajectory_Point temp_point;
//     unsigned int index0 = 0;
//     float64 x0 = global_path_.at(index0).x;
//     float64 y0 = global_path_.at(index0).y;
//     float theta0 = global_path_.at(index0).yaw;
//     float speed0 = global_path_.at(index0).speed;
//     float curvature0 = global_path_.at(index0).curvature;
//     float64 x1;
//     float64 y1;
//     float theta1;
//     float speed1;
//     float curvature1;
//     temp_path.clear();
//     path_s.clear();
//     for (unsigned int i = 1; i < global_path_.size(); i++)
//     {
//         float delta_dis = global_path_.at(i).distance - global_path_.at(index0).distance;
//         if (delta_dis >= 0.1 || i == global_path_.size() - 1)
//         {
//             x1 = global_path_.at(i).x;
//             y1 = global_path_.at(i).y;
//             theta1 = global_path_.at(i).yaw;
//             speed1 = global_path_.at(i).speed;
//             curvature1 = global_path_.at(i).curvature;
//             uint16 nums = floor(delta_dis / 0.01) > 0 ? floor(delta_dis / 0.01) : 1;
//             for (uint16 j = 1; j <= nums; j++)
//             {
//                 float effec = (0.1 * j) / (0.1 * nums);
//                 temp_point.x = x0 + effec * (x1 - x0);
//                 temp_point.y = y0 + effec * (y1 - y0);
//                 float d_theta = theta1 - theta0;
//                 d_theta = fmod(d_theta + 540, 360) - 180;
//                 temp_point.yaw = theta0 + effec * d_theta;
//                 temp_point.yaw = fmod(temp_point.yaw + 360, 360);
//                 temp_point.speed = speed0 + effec * (speed1 - speed0);
//                 temp_point.curvature = curvature0 + effec * (curvature1 - curvature0);
//                 temp_path.push_back(temp_point);
//             }
//             x0 = x1;
//             y0 = y1;
//             theta0 = theta1;
//             speed0 = speed1;
//             curvature0 = curvature1;
//             index0 = i;
//         }
//     }
//     threadLogger_->info("Path_interpolation() function   ");
// }

// /*
//  * @brief 调用hibrid A star算法进行路径规划的接口函数
//  * @param [in] 起始点坐标，目标点坐标，区域外边界，区域内障碍物边界,规划规则
//  * @param [return] true：成功；false：失败
//  */
// bool Planning::ApplyHibridAStar(Single_Point s_point,
//                                 Single_Point e_point,
//                                 uint8 temp_zone_id,
//                                 vector<Trajectory_Point> &traj,
//                                 uint8 plan_rule_id)
// {

//     std::vector<uint8> connected_zones;
//     threadLogger_->info("当前区域id：{}", static_cast<int>(temp_zone_id));
//     connected_zones.emplace_back(temp_zone_id);
//     // 为hybird A*求取外边界，应该用于后续的碰撞检测
//     for (int i = 0; i < road_directed_graph_.graph.size(); i++)
//     {
//         if (fabs(road_directed_graph_.graph.at(temp_zone_id - 1).at(i) - 10000) > 1e-6)
//         {
//             vector<uint8>::iterator it;
//             it = find(connected_zones.begin(), connected_zones.end(), i + 1);
//             if (it == connected_zones.end())
//                 connected_zones.emplace_back(i + 1);
//         }
//         if (fabs(road_directed_graph_.graph.at(i).at(temp_zone_id - 1) - 10000) > 1e-6)
//         {
//             vector<uint8>::iterator it;
//             it = find(connected_zones.begin(), connected_zones.end(), i + 1);
//             if (it == connected_zones.end())
//                 connected_zones.emplace_back(i + 1);
//         }
//     }
//     //  threadLogger_->info("与当前区域存在连通的区域为如下：");
//     //  for (size_t index = 0; index < connected_zones.size(); index++)
//     //  {
//     //      threadLogger_->info("  {}", static_cast<int>(connected_zones.at(index)) << " ";
//     //  }

//     /*结构转换*/

//     // 起始点、目标点结构转换
//     HybridAStar ::Point temp_start_point(s_point.x, s_point.y, s_point.z, s_point.yaw, HybridAStar ::MotionDirection
//     ::Forward); HybridAStar ::Point temp_end_point(e_point.x, e_point.y, e_point.z, e_point.yaw, HybridAStar
//     ::MotionDirection ::Forward);

//     // 区域外边界、区域内边界转换
//     HybridAStar::Bound road_outer_bound;
//     HybridAStar::Bound road_inner_bound;
//     vector<HybridAStar::Coordinate> v_road_outer_bound;
//     vector<HybridAStar::Coordinate> v_road_inner_bound;
//     HybridAStar::Coordinate temp_Coordinate;
//     // 获取道路边界
//     for (int32 i = 0; i < connected_zones.size(); i++)
//     {
//         Single_Border ext_border = all_zones_.at(connected_zones.at(i) - 1).external_border;
//         vector<Single_Border> obs_borders = all_zones_.at(connected_zones.at(i) - 1).inner_borders;
//         // threadLogger_->info("obs_borders.size():{}", obs_borders.size());

//         // 获取道路外边界 (以传入参数的外边界点作为道路外边界)
//         for (int32 index = 0; index < ext_border.border_points.size(); index++)
//         {
//             if (ext_border.border_points.at(index).type == 0) // 只传不可穿越的边界点
//             {
//                 temp_Coordinate.x = ext_border.border_points.at(index).x;
//                 temp_Coordinate.y = ext_border.border_points.at(index).y;
//                 temp_Coordinate.z = ext_border.border_points.at(index).z;
//                 v_road_outer_bound.emplace_back(temp_Coordinate);
//             }
//         }
//         // 获取道路内边界 (暂时以传入参数的障碍物边界作为道路内边界)
//         for (int32 index = 0; index < obs_borders.size(); index++)
//         {
//             for (int32 j = 0; j < obs_borders.at(index).border_points.size(); j++)
//             {
//                 temp_Coordinate.x = obs_borders.at(index).border_points.at(j).x;
//                 temp_Coordinate.y = obs_borders.at(index).border_points.at(j).y;
//                 temp_Coordinate.z = obs_borders.at(index).border_points.at(j).z;
//                 v_road_inner_bound.emplace_back(temp_Coordinate);
//             }
//         }
//     }
//     // for (int32 i = 0; i < my_inner_border.size(); i++)
//     // {
//     //     for (int32 j = 0; j < my_inner_border.at(i).border_points.size(); j++)
//     //     {
//     //         temp_Coordinate.x = my_inner_border.at(i).border_points.at(j).x;
//     //         temp_Coordinate.y = my_inner_border.at(i).border_points.at(j).y;
//     //         temp_Coordinate.z = my_inner_border.at(i).border_points.at(j).z;
//     //         v_road_inner_bound.emplace_back(temp_Coordinate);
//     //     }
//     // }
//     road_inner_bound.emplace_back(v_road_inner_bound);
//     road_outer_bound.emplace_back(v_road_outer_bound);
//     // 搜索获取轨迹
//     traj.clear();
//     HybridAStar::Path final_path;
//     HybridAStar::PlanRule planrule = static_cast<HybridAStar::PlanRule>(plan_rule_id);

// #ifdef SKIP_HEADER
// #else
//     my_optimal_path_.threadLogger_ = threadLogger_;
// #endif
//     // my_optimal_path_.threadLogger_ = threadLogger_;
//     if (my_optimal_path_.SearchGlobalPath(temp_start_point, temp_end_point, road_outer_bound, road_inner_bound,
//     vehicle_param_,
//                                           final_path, planrule) == HybridAStar::PlanResult::Plan_OK)
//     {
//         Trajectory_Point temp_point;
//         for (int32 i = 0; i < final_path.size(); i++)
//         {
//             temp_point.Clear();
//             temp_point.x = final_path.at(i).x;
//             temp_point.y = final_path.at(i).y;
//             temp_point.z = final_path.at(i).z;
//             temp_point.yaw = final_path.at(i).angle;
//             temp_point.left = final_path.at(i).left;
//             temp_point.right = final_path.at(i).right;
//             temp_point.direction = final_path.at(i).direction;
//             temp_point.attribute = 4;
//             temp_point.curvature = final_path.at(i).curvature;
//             traj.emplace_back(temp_point);
//         }
//         // 针对rule:5的情况，进行绕圈检查，检查原理：判断两个点之间的距离进行判断，是否有间距小于0.8m的点
//         if (plan_rule_id == 5 || plan_rule_id == 4)
//         {
//             // for (int32 i = 1; i < traj.size() - 1; i++)
//             // {
//             //     for (int32 j = i - 1; j > 0; j--)
//             //     {
//             //         if (pow(fabs(traj.at(i).x - traj.at(j).x), 2) + pow(fabs(traj.at(i).y - traj.at(j).y), 2) <
//             0.8 * 0.8)
//             //         {
//             //             threadLogger_->info("检测到绕圈轨迹，pass");
//             //             return false;
//             //         }
//             //     }
//             // }
//             // 针对rule:5的情况，进行绕圈检查，检查原理：判断角度是否产生0~2M_PI的变化
//             if (doesTrajectorySelfIntersect(final_path))
//             {
//                 threadLogger_->info("检测到绕圈轨迹，pass");
//                 return false;
//             }
//         }
//         return true;
//     }
//     else
//     {
//         threadLogger_->info("本次采样规划失败，下一位 ");

//         return false;
//     }
//     return true;
// }
// bool Planning::ApplyHibridAStar(Single_Point s_point,
//                                 Single_Point e_point,
//                                 std::vector<uint8> related_zones,
//                                 vector<Trajectory_Point> &traj,
//                                 uint8 plan_rule_id)
// {
//     // std::vector<uint8> connected_zones;
//     // for (uint i = 0; i < related_zones.size(); i++)
//     // {
//     //     threadLogger_->info("涉及区域id:{}", static_cast<int>(related_zones.at(i)) );
//     // }
//     // connected_zones = related_zones;
//     // // 为hybird A*求取外边界，应该用于后续的碰撞检测
//     // for (int i = 0; i < road_directed_graph_.graph.size(); i++)
//     // {
//     //     if (fabs(road_directed_graph_.graph.at(temp_zone_id - 1).at(i) - 100000000) > 1e-6)
//     //     {
//     //         vector<uint8>::iterator it;
//     //         it = find(connected_zones.begin(), connected_zones.end(), i + 1);
//     //         if (it == connected_zones.end())
//     //             connected_zones.emplace_back(i + 1);
//     //     }
//     //     if (fabs(road_directed_graph_.graph.at(i).at(temp_zone_id - 1) - 100000000) > 1e-6)
//     //     {
//     //         vector<uint8>::iterator it;
//     //         it = find(connected_zones.begin(), connected_zones.end(), i + 1);
//     //         if (it == connected_zones.end())
//     //             connected_zones.emplace_back(i + 1);
//     //     }
//     // }
//     threadLogger_->info("与当前区域存在连通的区域为如下：");

//     for (size_t index = 0; index < related_zones.size(); index++)
//     {
//         threadLogger_->info(static_cast<int>(related_zones.at(index)));
//     }

//     /*结构转换*/

//     // 起始点、目标点结构转换
//     HybridAStar ::Point temp_start_point(s_point.x, s_point.y, s_point.z, s_point.yaw, HybridAStar ::MotionDirection
//     ::Forward); HybridAStar ::Point temp_end_point(e_point.x, e_point.y, e_point.z, e_point.yaw, HybridAStar
//     ::MotionDirection ::Forward);

//     // 区域外边界、区域内边界转换
//     HybridAStar::Bound road_outer_bound;
//     HybridAStar::Bound road_inner_bound;
//     vector<HybridAStar::Coordinate> v_road_outer_bound;
//     vector<HybridAStar::Coordinate> v_road_inner_bound;
//     HybridAStar::Coordinate temp_Coordinate;
//     // 获取道路边界
//     for (int32 i = 0; i < related_zones.size(); i++)
//     {
//         Single_Border ext_border = all_zones_.at(related_zones.at(i) - 1).external_border;
//         vector<Single_Border> obs_borders = all_zones_.at(related_zones.at(i) - 1).inner_borders;
//         // 获取道路外边界 (以传入参数的外边界点作为道路外边界)
//         for (int32 index = 0; index < ext_border.border_points.size(); index++)
//         {
//             if (ext_border.border_points.at(index).type == 0) // 只传不可穿越的边界点
//             {
//                 temp_Coordinate.x = ext_border.border_points.at(index).x;
//                 temp_Coordinate.y = ext_border.border_points.at(index).y;
//                 temp_Coordinate.z = ext_border.border_points.at(index).z;
//                 v_road_outer_bound.emplace_back(temp_Coordinate);
//             }
//         }
//         // 获取道路内边界 (暂时以传入参数的障碍物边界作为道路内边界)
//         for (int32 index = 0; index < obs_borders.size(); index++)
//         {
//             for (int32 j = 0; j < obs_borders.at(index).border_points.size(); j++)
//             {
//                 temp_Coordinate.x = obs_borders.at(index).border_points.at(j).x;
//                 temp_Coordinate.y = obs_borders.at(index).border_points.at(j).y;
//                 temp_Coordinate.z = obs_borders.at(index).border_points.at(j).z;
//                 v_road_inner_bound.emplace_back(temp_Coordinate);
//             }
//         }
//     }
//     // for (int32 i = 0; i < my_inner_border.size(); i++)
//     // {
//     //     for (int32 j = 0; j < my_inner_border.at(i).border_points.size(); j++)
//     //     {
//     //         temp_Coordinate.x = my_inner_border.at(i).border_points.at(j).x;
//     //         temp_Coordinate.y = my_inner_border.at(i).border_points.at(j).y;
//     //         temp_Coordinate.z = my_inner_border.at(i).border_points.at(j).z;
//     //         v_road_inner_bound.emplace_back(temp_Coordinate);
//     //     }
//     // }
//     road_inner_bound.emplace_back(v_road_inner_bound);
//     road_outer_bound.emplace_back(v_road_outer_bound);
//     // 搜索获取轨迹
//     traj.clear();
//     HybridAStar::Path final_path;
//     HybridAStar::PlanRule planrule = static_cast<HybridAStar::PlanRule>(plan_rule_id);
// #ifdef SKIP_HEADER
// #else
//     my_optimal_path_.threadLogger_ = threadLogger_;
// #endif

//     // my_optimal_path_.threadLogger_ = threadLogger_;

//     if (my_optimal_path_.SearchGlobalPath(temp_start_point, temp_end_point, road_outer_bound, road_inner_bound,
//     vehicle_param_,
//                                           final_path, planrule) == HybridAStar::PlanResult::Plan_OK)
//     {
//         Trajectory_Point temp_point;
//         for (int32 i = 0; i < final_path.size(); i++)
//         {
//             temp_point.Clear();
//             temp_point.x = final_path.at(i).x;
//             temp_point.y = final_path.at(i).y;
//             temp_point.z = final_path.at(i).z;
//             temp_point.yaw = final_path.at(i).angle;
//             temp_point.left = final_path.at(i).left;
//             temp_point.right = final_path.at(i).right;
//             temp_point.direction = final_path.at(i).direction;
//             traj.emplace_back(temp_point);
//         }
//         // 针对rule:5的情况，进行绕圈检查，检查原理：判断两个点之间的距离进行判断，是否有间距小于0.8m的点
//         if (plan_rule_id == 5 || plan_rule_id == 4)
//         {
//             // for (int32 i = 1; i < traj.size() - 1; i++)
//             // {
//             //     for (int32 j = i - 1; j > 0; j--)
//             //     {
//             //         if (pow(fabs(traj.at(i).x - traj.at(j).x), 2) + pow(fabs(traj.at(i).y - traj.at(j).y), 2) <
//             0.8 * 0.8)
//             //         {
//             //             threadLogger_->info("检测到绕圈轨迹，pass");
//             //             return false;
//             //         }
//             //     }
//             // }
//             // 针对rule:5的情况，进行绕圈检查，检查原理：判断角度是否产生0~2M_PI的变化
//             if (doesTrajectorySelfIntersect(final_path))
//             {
//                 threadLogger_->info("检测到绕圈轨迹，pass");
//                 return false;
//             }
//         }
//         return true;
//     }
//     else
//     {
//         threadLogger_->info("本次采样规划失败，下一位 ");

//         return false;
//     }
//     return true;
// }

_TarStartEnd Planning::ParseInputInfo(char* str) {
    _TarStartEnd veh_start_end;
    // zones retarea;
    // rapidjson::Document doc;
    // doc.Parse(str);
    // if (doc.HasParseError())
    // {
    //     cout << "parse失败......" << endl;
    // }
    // doc.GetAllocator();
    // // 任务类型
    // if (doc.HasMember("task_type_"))
    // {
    //     cout << "解析 task_type_ 中" << endl;
    //     veh_start_end.m_task_type = doc["task_type"].GetUint();
    //     cout << "veh_start_end.m_task_type = " << veh_start_end.m_task_type << endl;
    // }
    // else
    // {
    //     cout << "无 task_type 参数" << endl;
    // }
    // // 有向图
    // // if (doc.HasMember("road_directed_graph_"))
    // // {
    // //     cout << "解析 road_directed_graph_ 中" << endl;
    // //     Value &val = doc["road_directed_graph_"];

    // //     if (val.IsObject())
    // //     {
    // //         if (val.HasMember("graph") && val["graph"].IsArray())
    // //         {
    // //             const rapidjson::Value &array = val["graph"].GetArray();
    // //             size_t len = array.Size();
    // //             for (size_t i = 0; i < len; i++)
    // //             {
    // //                 const rapidjson::Value &arrayy = array[i];
    // //                 size_t lenn = arrayy.Size();
    // //                 std::vector<double> ppt;
    // //                 for (size_t j = 0; j < lenn; j++)
    // //                 {
    // //                     double temp_ppt;
    // //                     temp_ppt = arrayy[j].GetDouble();
    // //                     if (fabs(temp_ppt - 0.0) <= DBL_MIN)
    // //                     {
    // //                         temp_ppt = 10000;
    // //                     }
    // //                     ppt.push_back(temp_ppt);
    // //                 }
    // //                 retarea.road_directed_graph_.graph.push_back(ppt);
    // //             }
    // //         }
    // //     }
    // //     road_directed_graph_.Clear();
    // //     road_directed_graph_ = retarea.road_directed_graph_;
    // // }
    // // else
    // // {
    // //     cout << "无 road_directed_graph_ 参数" << endl;
    // // }
    // // 起始点
    // if (doc.HasMember("m_Start_Point"))
    // {
    //     cout << "解析 m_Start_Point 中" << endl;
    //     Value &val = doc["m_Start_Point"];
    //     if (val.IsObject())
    //     {
    //         if (val.HasMember("x"))
    //             veh_start_end.m_Start_Point.x = val["x"].GetDouble();
    //         if (val.HasMember("y"))
    //             veh_start_end.m_Start_Point.y = val["y"].GetDouble();
    //         if (val.HasMember("z"))
    //             veh_start_end.m_Start_Point.z = val["z"].GetFloat();
    //         if (val.HasMember("yaw"))
    //             veh_start_end.m_Start_Point.yaw = val["yaw"].GetFloat();
    //     }
    // }
    // else
    // {
    //     cout << " 无 m_Start_Point 参数" << endl;
    // }
    // // 目标点
    // if (doc.HasMember("m_End_Point"))
    // {
    //     cout << "解析 m_End_Point 中" << endl;
    //     Value &val = doc["m_End_Point"];
    //     if (val.IsObject())
    //     {
    //         if (val.HasMember("x"))
    //             veh_start_end.m_End_Point.x = val["x"].GetDouble();
    //         if (val.HasMember("y"))
    //             veh_start_end.m_End_Point.y = val["y"].GetDouble();
    //         if (val.HasMember("z"))
    //             veh_start_end.m_End_Point.z = val["z"].GetFloat();
    //         if (val.HasMember("yaw"))
    //             veh_start_end.m_End_Point.yaw = val["yaw"].GetFloat();
    //     }
    // }
    // else
    // {
    //     cout << " 无 m_End_Point 参数" << endl;
    // }

    // if (doc.HasMember("m_Veh_Param"))
    // {
    //     cout << "解析 m_Veh_Param 中" << endl;
    //     Value &val = doc["m_Veh_Param"];
    //     if (val.IsObject())
    //     {
    //         // 车辆参数
    //         if (val.HasMember("radious"))
    //         {
    //             veh_start_end.m_Veh_Param.radious = val["radious"].GetDouble();
    //         }

    //         if (val.HasMember("wheel_base"))
    //             veh_start_end.m_Veh_Param.wheel_base = val["wheel_base"].GetDouble();
    //         //            if(val.HasMember("front_radious"))
    //         //                veh_start_end.m_Veh_Param.front_radious = val["front_radious"].GetDouble();
    //         //            veh_start_end.m_Veh_Param.max_steering = atan(veh_start_end.m_Veh_Param.wheel_base /
    //         veh_start_end.m_Veh_Param.front_radious) / M_PI * 180;
    //         //            veh_start_end.m_Veh_Param.min_steering = -veh_start_end.m_Veh_Param.max_steering;
    //         if (val.HasMember("max_steering"))
    //             veh_start_end.m_Veh_Param.max_steering = val["max_steering"].GetDouble() * M_PI / 180.0;
    //         if (val.HasMember("min_steering"))
    //             veh_start_end.m_Veh_Param.min_steering = val["min_steering"].GetDouble() * M_PI / 180.0;
    //         if (val.HasMember("safe_margin_bound"))
    //         {
    //             veh_start_end.m_Veh_Param.safe_margin_bound = val["safe_margin_bound"].GetDouble();
    //             cout << "veh_start_end.m_Veh_Param.safe_margin_bound:" << veh_start_end.m_Veh_Param.safe_margin_bound
    //             << endl;
    //         }

    //         if (val.HasMember("veh_center_2_side"))
    //             veh_start_end.m_Veh_Param.veh_center_2_side = val["veh_center_2_side"].GetDouble();
    //         if (val.HasMember("veh_center_2_front"))
    //             veh_start_end.m_Veh_Param.veh_center_2_front = val["veh_center_2_front"].GetDouble();
    //         if (val.HasMember("safe_margin_obstacle"))
    //             veh_start_end.m_Veh_Param.safe_margin_obstacle = val["safe_margin_obstacle"].GetDouble();
    //         if (val.HasMember("veh_center_2_rear_bound"))
    //             veh_start_end.m_Veh_Param.veh_center_2_rear_bound = val["veh_center_2_rear_bound"].GetDouble();
    //         if (val.HasMember("veh_center_2_rear_obstacle"))
    //             veh_start_end.m_Veh_Param.veh_center_2_rear_obstacle = val["veh_center_2_rear_obstacle"].GetDouble();
    //         // 算法参数
    //         if (val.HasMember("delta_s"))
    //             veh_start_end.m_Veh_Param.delta_s = val["delta_s"].GetDouble();
    //         if (val.HasMember("delta_dist"))
    //             veh_start_end.m_Veh_Param.delta_dist = val["delta_dist"].GetDouble();
    //         if (val.HasMember("grid_dist"))
    //             veh_start_end.m_Veh_Param.grid_dist = val["grid_dist"].GetDouble();
    //         if (val.HasMember("max_kappa"))
    //             veh_start_end.m_Veh_Param.max_kappa = val["max_kappa"].GetDouble();
    //         if (val.HasMember("error_term"))
    //             veh_start_end.m_Veh_Param.error_term = val["error_term"].GetDouble();
    //         if (val.HasMember("grid_angle"))
    //             veh_start_end.m_Veh_Param.grid_angle = val["grid_angle"].GetDouble() * M_PI / 180.0;
    //         if (val.HasMember("step_length"))
    //             veh_start_end.m_Veh_Param.step_length = val["step_length"].GetDouble();
    //         if (val.HasMember("curvature_term"))
    //             veh_start_end.m_Veh_Param.curvature_term = val["curvature_term"].GetDouble();
    //         if (val.HasMember("switch_penalty"))
    //             veh_start_end.m_Veh_Param.switch_penalty = val["switch_penalty"].GetDouble();
    //         if (val.HasMember("forward_penalty"))
    //             veh_start_end.m_Veh_Param.forward_penalty = val["forward_penalty"].GetDouble();
    //         if (val.HasMember("min_path_Length"))
    //             veh_start_end.m_Veh_Param.min_path_Length = val["min_path_Length"].GetDouble();
    //         if (val.HasMember("end_offset_distance"))
    //             veh_start_end.m_Veh_Param.end_offset_distance = val["end_offset_distance"].GetDouble();
    //         if (val.HasMember("smoothness_term"))
    //             veh_start_end.m_Veh_Param.smoothness_term = val["smoothness_term"].GetDouble();
    //         if (val.HasMember("backward_penalty"))
    //             veh_start_end.m_Veh_Param.backward_penalty = val["backward_penalty"].GetDouble();
    //         if (val.HasMember("turnning_penalty"))
    //             veh_start_end.m_Veh_Param.turnning_penalty = val["turnning_penalty"].GetDouble();
    //         if (val.HasMember("angle_discrete_num"))
    //             veh_start_end.m_Veh_Param.angle_discrete_num = val["angle_discrete_num"].GetUint();
    //         if (val.HasMember("max_fitting_radius"))
    //             veh_start_end.m_Veh_Param.max_fitting_radius = val["max_fitting_radius"].GetDouble();
    //         if (val.HasMember("max_iterations_opti"))
    //             veh_start_end.m_Veh_Param.max_iterations_opti = val["max_iterations_opti"].GetDouble();
    //         if (val.HasMember("max_iterations_astar"))
    //             veh_start_end.m_Veh_Param.max_iterations_astar = val["max_iterations_astar"].GetUint();
    //         if (val.HasMember("backward_search_range"))
    //             veh_start_end.m_Veh_Param.backward_search_range = val["backward_search_range"].GetDouble();
    //         if (val.HasMember("cusp_extension_distance"))
    //             veh_start_end.m_Veh_Param.cusp_extension_distance = val["cusp_extension_distance"].GetFloat();
    //         if (val.HasMember("linear_preferred_distance_square"))
    //             veh_start_end.m_Veh_Param.linear_preferred_distance_square =
    //             val["linear_preferred_distance_square"].GetDouble();
    //         if (val.HasMember("min_speed_limit"))
    //             veh_start_end.m_Veh_Param.min_speed_limit = val["min_speed_limit"].GetFloat();
    //         if (val.HasMember("mid_speed_limit"))
    //             veh_start_end.m_Veh_Param.mid_speed_limit = val["mid_speed_limit"].GetFloat();
    //         if (val.HasMember("max_speed_limit"))
    //             veh_start_end.m_Veh_Param.max_speed_limit = val["max_speed_limit"].GetFloat();
    //         if (val.HasMember("min_curvature"))
    //             veh_start_end.m_Veh_Param.min_curvature = val["min_curvature"].GetFloat();
    //         if (val.HasMember("max_curvature"))
    //             veh_start_end.m_Veh_Param.max_curvature = val["max_curvature"].GetFloat();
    //         if (val.HasMember("min_distance"))
    //             veh_start_end.m_Veh_Param.min_distance = val["min_distance"].GetDouble();
    //         if (val.HasMember("lat_min_distance"))
    //             veh_start_end.m_Veh_Param.lat_min_distance = val["lat_min_distance"].GetDouble();
    //         if (val.HasMember("lon_min_distance"))
    //             veh_start_end.m_Veh_Param.lon_min_distance = val["lon_min_distance"].GetDouble();

    //         if (val.HasMember("lat_min_distance_struct"))
    //             veh_start_end.m_Veh_Param.lat_min_distance_struct = val["lat_min_distance_struct"].GetDouble();
    //         if (val.HasMember("bfs_search"))
    //             veh_start_end.m_Veh_Param.bfs_search = val["bfs_search"].GetBool();
    //         if (val.HasMember("safe_margin_error"))
    //             veh_start_end.m_Veh_Param.safe_margin_error = val["safe_margin_error"].GetDouble();
    //         if (val.HasMember("kErrorTerm"))
    //             veh_start_end.m_Veh_Param.kErrorTerm = val["kErrorTerm"].GetFloat();
    //         if (val.HasMember("kDeltaSpeed"))
    //             veh_start_end.m_Veh_Param.kDeltaSpeed = val["kDeltaSpeed"].GetFloat();
    //         if (val.HasMember("kDiscreteNumber"))
    //             veh_start_end.m_Veh_Param.kDiscreteNumber = val["kDiscreteNumber"].GetFloat();
    //         if (val.HasMember("kSmoothnessTerm"))
    //             veh_start_end.m_Veh_Param.kSmoothnessTerm = val["kSmoothnessTerm"].GetFloat();
    //         if (val.HasMember("kMaxAcceleration"))
    //             veh_start_end.m_Veh_Param.kMaxAcceleration = val["kMaxAcceleration"].GetFloat();
    //         if (val.HasMember("kMinAcceleration"))
    //             veh_start_end.m_Veh_Param.kMinAcceleration = val["kMinAcceleration"].GetFloat();
    //         if (val.HasMember("reverse_speed"))
    //             veh_start_end.m_Veh_Param.reverse_speed = val["reverse_speed"].GetFloat();
    //         if (val.HasMember("border_change_range"))
    //             veh_start_end.m_Veh_Param.border_change_range = val["border_change_range"].GetFloat();
    //         if (val.HasMember("border_sample_inter"))
    //             veh_start_end.m_Veh_Param.border_sample_inter = val["border_sample_inter"].GetUint();

    //         if (val.HasMember("light_narrow_road_speed_limit"))
    //             veh_start_end.m_Veh_Param.light_narrow_road_speed_limit =
    //             val["light_narrow_road_speed_limit"].GetFloat();
    //         else
    //         {
    //             cout << "无法找到 light_narrow_road_speed_limit" << endl;
    //             veh_start_end.m_Veh_Param.light_narrow_road_speed_limit = 1.0;
    //         }

    //         if (val.HasMember("light_slope_road_speed_limit"))
    //             veh_start_end.m_Veh_Param.light_slope_road_speed_limit =
    //             val["light_slope_road_speed_limit"].GetFloat();
    //         else
    //         {
    //             cout << "无法找到 light_slope_road_speed_limit" << endl;
    //             veh_start_end.m_Veh_Param.light_slope_road_speed_limit = 1.0;
    //         }

    //         if (val.HasMember("light_intersection_road_speed_limit"))
    //             veh_start_end.m_Veh_Param.light_intersection_road_speed_limit =
    //             val["light_intersection_road_speed_limit"].GetFloat();
    //         else
    //         {
    //             cout << "无法找到 light_intersection_road_speed_limit" << endl;
    //             veh_start_end.m_Veh_Param.light_intersection_road_speed_limit = 1.0;
    //         }

    //         if (val.HasMember("light_bumpy_road_speed_limit"))
    //             veh_start_end.m_Veh_Param.light_bumpy_road_speed_limit =
    //             val["light_bumpy_road_speed_limit"].GetFloat();
    //         else
    //         {
    //             cout << "无法找到 light_bumpy_road_speed_limit" << endl;
    //             veh_start_end.m_Veh_Param.light_bumpy_road_speed_limit = 1.0;
    //         }

    //         if (val.HasMember("light_regular_road_speed_limit"))
    //             veh_start_end.m_Veh_Param.light_regular_road_speed_limit =
    //             val["light_regular_road_speed_limit"].GetFloat();
    //         else
    //         {
    //             cout << "无法找到 light_regular_road_speed_limit" << endl;
    //             veh_start_end.m_Veh_Param.light_regular_road_speed_limit = 1.0;
    //         }

    //         if (val.HasMember("heavy_narrow_road_speed_limit"))
    //             veh_start_end.m_Veh_Param.heavy_narrow_road_speed_limit =
    //             val["heavy_narrow_road_speed_limit"].GetFloat();
    //         else
    //         {
    //             cout << "无法找到 heavy_narrow_road_speed_limit" << endl;
    //             veh_start_end.m_Veh_Param.heavy_narrow_road_speed_limit = 1.0;
    //         }

    //         if (val.HasMember("heavy_slope_road_speed_limit"))
    //         {
    //             veh_start_end.m_Veh_Param.heavy_slope_road_speed_limit =
    //             val["heavy_slope_road_speed_limit"].GetFloat(); cout << "find heavy_slope_road_speed_limit " <<
    //             veh_start_end.m_Veh_Param.heavy_slope_road_speed_limit << endl;
    //         }
    //         else
    //         {
    //             cout << "无法找到 heavy_slope_road_speed_limit" << endl;
    //             veh_start_end.m_Veh_Param.heavy_slope_road_speed_limit = 1.0;
    //         }

    //         if (val.HasMember("heavy_intersection_road_speed_limit"))
    //             veh_start_end.m_Veh_Param.heavy_intersection_road_speed_limit =
    //             val["heavy_intersection_road_speed_limit"].GetFloat();
    //         else
    //         {
    //             cout << "无法找到 heavy_intersection_road_speed_limit" << endl;
    //             veh_start_end.m_Veh_Param.heavy_intersection_road_speed_limit = 1.0;
    //         }

    //         if (val.HasMember("heavy_bumpy_road_speed_limit"))
    //             veh_start_end.m_Veh_Param.heavy_bumpy_road_speed_limit =
    //             val["heavy_bumpy_road_speed_limit"].GetFloat();
    //         else
    //         {
    //             cout << "无法找到 heavy_bumpy_road_speed_limit" << endl;
    //             veh_start_end.m_Veh_Param.heavy_bumpy_road_speed_limit = 1.0;
    //         }

    //         if (val.HasMember("heavy_regular_road_speed_limit"))
    //             veh_start_end.m_Veh_Param.heavy_regular_road_speed_limit =
    //             val["heavy_regular_road_speed_limit"].GetFloat();
    //         else
    //         {
    //             cout << "无法找到 heavy_regular_road_speed_limit" << endl;
    //             veh_start_end.m_Veh_Param.heavy_regular_road_speed_limit = 1.0;
    //         }

    //         if (val.HasMember("vehicle_code"))
    //             veh_start_end.m_Veh_Param.vehicle_code = val["vehicle_code"].GetUint();
    //         else
    //         {
    //             cout << "无法找到 vehicle_code" << endl;
    //             veh_start_end.m_Veh_Param.vehicle_code = 9999;
    //         }

    //         if (val.HasMember("offset_enable"))
    //             veh_start_end.m_Veh_Param.offset_enable = val["offset_enable"].GetUint();
    //         else
    //         {
    //             cout << "无法找到 offset_enable" << endl;
    //             veh_start_end.m_Veh_Param.offset_enable = 0;
    //         }

    //         if (val.HasMember("multi_section_speed_limit_enable"))
    //             veh_start_end.m_Veh_Param.multi_section_speed_limit_enable =
    //             val["multi_section_speed_limit_enable"].GetUint();
    //         else
    //         {
    //             cout << "无法找到 multi_section_speed_limit_enable" << endl;
    //             veh_start_end.m_Veh_Param.multi_section_speed_limit_enable = 0;
    //         }

    //         if (val.HasMember("s_curve_speed_limit"))
    //             veh_start_end.m_Veh_Param.s_curve_speed_limit = val["s_curve_speed_limit"].GetUint();
    //         else
    //         {
    //             cout << "无法找到 s_curve_speed_limit" << endl;
    //             veh_start_end.m_Veh_Param.s_curve_speed_limit = 0;
    //         }
    //         if (val.HasMember("weather"))
    //             veh_start_end.m_Veh_Param.weather = val["weather"].GetUint();
    //         else
    //         {
    //             cout << "无法找到 weather" << endl;
    //             veh_start_end.m_Veh_Param.weather = 1;
    //         }
    //         if (val.HasMember("start_offset_distance"))
    //             veh_start_end.m_Veh_Param.start_offset_distance = val["start_offset_distance"].GetFloat();
    //         else
    //         {
    //             cout << "无法找到 start_offset_distance" << endl;
    //             veh_start_end.m_Veh_Param.start_offset_distance = 4.0;
    //         }
    //         if (val.HasMember("end_offset_distance"))
    //             veh_start_end.m_Veh_Param.end_offset_distance = val["end_offset_distance"].GetFloat();
    //         else
    //         {
    //             cout << "无法找到 end_offset_distance" << endl;
    //             veh_start_end.m_Veh_Param.end_offset_distance = 2.0;
    //         }
    //         if (val.HasMember("max_l"))
    //         {
    //             veh_start_end.m_Veh_Param.max_l = val["max_l"].GetFloat();
    //             if (fabs(veh_start_end.m_Veh_Param.max_l) > 0.5)
    //             {
    //                 veh_start_end.m_Veh_Param.max_l = 0.5;
    //             }
    //         }

    //         else
    //         {
    //             cout << "无法找到 max_l" << endl;
    //             veh_start_end.m_Veh_Param.max_l = 0.2;
    //         }
    //     }
    // }
    // else
    // {
    //     cout << " 无 m_Veh_Param 参数" << endl;
    // }

    // if (doc.HasMember("Inner_Borders"))
    // {
    //     cout << "解析 Inner_Borders 中" << endl;
    //     Value &val = doc["Inner_Borders"];
    //     for (size_t i = 0; i < val.Size(); i++)
    //     {
    //         Value &temp_val = val[i];
    //         zone_inner_border single_b;
    //         if (temp_val.HasMember("zone_id"))
    //         {
    //             single_b.zone_id = temp_val["zone_id"].GetUint();
    //         }
    //         else
    //         {
    //             cout << "未找到zone_id" << endl;
    //         }
    //         try
    //         {
    //             if (temp_val.HasMember("inner_borders"))
    //             {
    //                 Value &temp_value = temp_val["inner_borders"];
    //                 for (size_t j = 0; j < temp_value.Size(); j++)
    //                 {
    //                     Single_Border single_bd;
    //                     Value &temp_vall = temp_value[j];
    //                     if (temp_vall.HasMember("point_num"))
    //                     {
    //                         single_bd.point_num = temp_vall["point_num"].GetUint();
    //                     }
    //                     else
    //                     {
    //                         cout << "未找到point_num" << endl;
    //                     }
    //                     if (temp_vall.HasMember("border_points"))
    //                     {
    //                         Value &temp_val_1 = temp_vall["border_points"];
    //                         Single_Border_Point temp_point;
    //                         for (size_t j = 0; j < temp_val_1.Size(); j++)
    //                         {
    //                             Value &temp_val_2 = temp_val_1[j];
    //                             temp_point.x = temp_val_2["x"].GetDouble();
    //                             temp_point.y = temp_val_2["y"].GetDouble();
    //                             temp_point.z = temp_val_2["z"].GetFloat();
    //                             temp_point.type = temp_val_2["type"].GetUint();
    //                             single_bd.border_points.emplace_back(temp_point);
    //                         }
    //                     }
    //                     else
    //                     {
    //                         cout << "未找到border_points" << endl;
    //                     }
    //                     single_b.inner_border.emplace_back(single_bd);
    //                 }
    //             }
    //             else
    //             {
    //                 cout << "未找到inner_borders" << endl;
    //             }
    //         }
    //         catch (...)
    //         {
    //             return veh_start_end;
    //         }
    //         veh_start_end.inner_borders.emplace_back(single_b);
    //     }
    // }
    // else
    // {
    //     cout << "未找到内边界参数" << endl;
    // }

    // if (doc.HasMember("key_"))
    // {
    //     cout << "解析 key_ 中" << endl;
    //     veh_start_end.my_key = doc["key_"].GetString();
    //     // veh_start_end.my_key = temp_str.c_str();
    //     cout << "veh_start_end.my_key = " << veh_start_end.my_key << endl;
    // }
    // else
    // {
    //     cout << "无 key_ 参数" << endl;
    // }

    return veh_start_end;
}

// bool Planning::ProgressiveHybirdAStar(Single_Point &input_point, uint8 input_node, bool search_direction,
// std::vector<Trajectory_Point> &input_trajectory, unsigned int search_start, int32 &search_index,
// std::vector<Trajectory_Point> &result_trajectory, uint8 rule_id)
// {
//     int64 time_threshold = 0.8 * 1000 * 1000;
//     uint16 counter = 0;
//     uint8 success_flag = false;
//     Single_Point temp_start, temp_end;
//     int8 cal = 0;
//     threadLogger_->info("搜索起点索引：{}  搜索方向  -- 1(顺着参考线)  --0(逆着参考线)：{}", search_start,
//     search_direction); if (search_direction == true) // 顺着参考线进行搜索，这种case为找拼接终点
//     {
//         cal = 0;
//         for (int32 i = search_start; i < input_trajectory.size(); i += 5)
//         {
//             cal++;
//             counter++;
//             temp_end.x = input_trajectory.at(i).x;
//             temp_end.y = input_trajectory.at(i).y;
//             temp_end.z = input_trajectory.at(i).z;
//             temp_end.yaw = input_trajectory.at(i).yaw;
//             threadLogger_->info("第 {}个候选点，其索引：{} rule_id:{}", float(cal), i, float(rule_id));
//             // 到8个点的时候，时间得提升到800ms
//             if (counter > 4)
//                 time_threshold = 0.8 * 1000 * 1000;
//             if (ApplyHibridAStarWithTime(input_point, temp_end, input_node, result_trajectory, rule_id,
//             time_threshold)) // rule_id:5，只前进
//             {
//                 search_index = i;
//                 success_flag = true;
//                 break;
//             }
//             if (counter > 8)
//             {
//                 threadLogger_->info("最多搜索8个点");
//                 return false;
//             }
//         }
//     }
//     else
//     { // 逆着参考线进行搜索，这种case为找拼接起点
//         cal = 0;
//         counter = 0;
//         for (int32 i = search_start; i > 0; i -= 5)
//         {
//             cal++;
//             counter++;
//             temp_start.x = input_trajectory.at(i).x;
//             temp_start.y = input_trajectory.at(i).y;
//             temp_start.z = input_trajectory.at(i).z;
//             temp_start.yaw = input_trajectory.at(i).yaw;
//             threadLogger_->info("第{}个候选点，其索引：{} rule_id:{}", float(cal), i, float(rule_id));
//             if (counter > 4)
//                 time_threshold = 0.8 * 1000 * 1000;
//             if (ApplyHibridAStarWithTime(temp_start, input_point, input_node, result_trajectory, rule_id,
//             time_threshold)) // rule_id:5，只前进
//             {
//                 search_index = i;
//                 success_flag = true;
//                 break;
//             }
//             if (counter > 8)
//             {
//                 threadLogger_->info("最多搜索16个点，不搜了");
//                 return false;
//             }
//         }
//     }
//     if (success_flag == true)
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }

// bool Planning::ApplyHibridAStarWithTime(Single_Point s_point,
//                                         Single_Point e_point,
//                                         uint8 temp_zone_id,
//                                         vector<Trajectory_Point> &traj,
//                                         uint8 plan_rule_id,
//                                         int64 time_threshold)
// {
//     int16 cal = 0;
//     std::vector<uint8> connected_zones;
//     cal++;
//     threadLogger_->info("第 {} 次调用ApplyHibridAStarWithTime", cal);
//     threadLogger_->info("当前区域id：{}", static_cast<int>(temp_zone_id));

//     connected_zones.emplace_back(temp_zone_id);
//     // 为hybird A*求取外边界，应该用于后续的碰撞检测
//     for (int i = 0; i < road_directed_graph_.graph.size(); i++)
//     {
//         if (fabs(road_directed_graph_.graph.at(temp_zone_id - 1).at(i) - 10000) > 1e-6)
//         {
//             vector<uint8>::iterator it;
//             it = find(connected_zones.begin(), connected_zones.end(), i + 1);
//             if (it == connected_zones.end())
//                 connected_zones.emplace_back(i + 1);
//         }
//         if (fabs(road_directed_graph_.graph.at(i).at(temp_zone_id - 1) - 10000) > 1e-6)
//         {
//             vector<uint8>::iterator it;
//             it = find(connected_zones.begin(), connected_zones.end(), i + 1);
//             if (it == connected_zones.end())
//                 connected_zones.emplace_back(i + 1);
//         }
//     }
//     threadLogger_->info("与当前区域存在连通的区域为如下：");

//     for (size_t index = 0; index < connected_zones.size(); index++)
//     {
//         threadLogger_->info(static_cast<int>(connected_zones.at(index)));
//     }

//     //  vector<HybridAStar::Coordinate> Spanable_bound;
//     // HybridAStar::Bound Classified_spanable_bound;

//     /*结构转换*/

//     // 起始点、目标点结构转换
//     HybridAStar ::Point temp_start_point(s_point.x, s_point.y, s_point.z, s_point.yaw, HybridAStar ::MotionDirection
//     ::Forward); HybridAStar ::Point temp_end_point(e_point.x, e_point.y, e_point.z, e_point.yaw, HybridAStar
//     ::MotionDirection ::Forward);

//     // 区域外边界、区域内边界转换
//     HybridAStar::Bound road_outer_bound;
//     HybridAStar::Bound road_inner_bound;
//     vector<HybridAStar::Coordinate> v_road_outer_bound;
//     vector<HybridAStar::Coordinate> v_road_inner_bound;
//     HybridAStar::Coordinate temp_Coordinate;
//     // 获取道路边界
//     for (int32 i = 0; i < connected_zones.size(); i++)
//     {
//         Single_Border ext_border = all_zones_.at(connected_zones.at(i) - 1).external_border;
//         vector<Single_Border> obs_borders = all_zones_.at(connected_zones.at(i) - 1).inner_borders;

//         // 获取道路外边界 (以传入参数的外边界点作为道路外边界)
//         for (int32 index = 0; index < ext_border.border_points.size(); index++)
//         {
//             if (ext_border.border_points.at(index).type == 0) // 只传不可穿越的边界点
//             {
//                 temp_Coordinate.x = ext_border.border_points.at(index).x;
//                 temp_Coordinate.y = ext_border.border_points.at(index).y;
//                 temp_Coordinate.z = ext_border.border_points.at(index).z;
//                 v_road_outer_bound.emplace_back(temp_Coordinate);
//             }
//         }
//         // 获取道路内边界 (暂时以传入参数的障碍物边界作为道路内边界)
//         for (int32 index = 0; index < obs_borders.size(); index++)
//         {
//             for (int32 j = 0; j < obs_borders.at(index).border_points.size(); j++)
//             {
//                 temp_Coordinate.x = obs_borders.at(index).border_points.at(j).x;
//                 temp_Coordinate.y = obs_borders.at(index).border_points.at(j).y;
//                 temp_Coordinate.z = obs_borders.at(index).border_points.at(j).z;
//                 v_road_inner_bound.emplace_back(temp_Coordinate);
//             }
//         }
//     }
//     road_inner_bound.emplace_back(v_road_inner_bound);
//     road_outer_bound.emplace_back(v_road_outer_bound);
//     // 搜索获取轨迹
//     traj.clear();
//     HybridAStar::Path final_path;
//     HybridAStar::PlanRule planrule = static_cast<HybridAStar::PlanRule>(plan_rule_id);
// #ifdef SKIP_HEADER
// #else
//     my_optimal_path_.threadLogger_ = threadLogger_;
// #endif
//     if (my_optimal_path_.SearchGlobalPath1(temp_start_point, temp_end_point, road_outer_bound, road_inner_bound,
//     vehicle_param_,
//                                            final_path, time_threshold, planrule) == HybridAStar::PlanResult::Plan_OK)
//     {
//         Trajectory_Point temp_point;
//         for (int32 i = 0; i < final_path.size(); i++)
//         {
//             temp_point.Clear();
//             temp_point.x = final_path.at(i).x;
//             temp_point.y = final_path.at(i).y;
//             temp_point.z = final_path.at(i).z;
//             temp_point.yaw = final_path.at(i).angle;
//             temp_point.left = final_path.at(i).left;
//             temp_point.right = final_path.at(i).right;
//             temp_point.direction = final_path.at(i).direction;
//             temp_point.attribute = 4;
//             temp_point.curvature = final_path.at(i).curvature;
//             traj.emplace_back(temp_point);
//         }
//         // 针对rule:5的情况，进行绕圈检查，检查原理：判断两个点之间的距离进行判断，是否有间距小于0.8m的点
//         if (plan_rule_id == 5 || plan_rule_id == 4)
//         {
//             // for (int32 i = 1; i < traj.size() - 1; i++)
//             // {
//             //     for (int32 j = i - 1; j > 0; j--)
//             //     {
//             //         if (pow(fabs(traj.at(i).x - traj.at(j).x), 2) + pow(fabs(traj.at(i).y - traj.at(j).y), 2) <
//             0.8 * 0.8)
//             //         {
//             //             threadLogger_->info("检测到绕圈轨迹，pass");
//             //             return false;
//             //         }
//             //     }
//             // }
//             // 针对rule:5的情况，进行绕圈检查，检查原理：判断角度是否产生0~2M_PI的变化
//             cout << "line5851" << endl;
//             if (doesTrajectorySelfIntersect(final_path))
//             {
//                 threadLogger_->info("检测到绕圈轨迹，pass");
//                 return false;
//             }
//             cout << "line5857" << endl;
//         }

//         // if (path.size() < 4) return false; // 少于4个点无法交叉
//         // for (size_t i = 0; i < path.size() - 3; ++i) {
//         //     for (size_t j = i + 2; j < path.size() - 1; ++j) {
//         //         if (doSegmentsIntersect(path[i], path[i + 1], path[j], path[j + 1])) {
//         //             return true;
//         //         }
//         //     }
//         // }

//         // return false;

//         return true;
//     }
//     else
//     {
//         threadLogger_->error(" Failed to plan the path by hibrid A star  ");

//         return false;
//     }
//     return true;
// }

// bool Planning::DetermineIfOrNoHybirdAStar(Single_Point &input_point, std::vector<Trajectory_Point> &traj, unsigned
// int nearest_point_index, float &lat_distance_)
// {
//     int max_size = traj.size() - 1;
//     Single_Point nearest_point;
//     nearest_point.x = traj.at(nearest_point_index).x;
//     nearest_point.y = traj.at(nearest_point_index).y;
//     nearest_point.z = traj.at(nearest_point_index).z;
//     nearest_point.yaw = traj.at(nearest_point_index).yaw;

//     float64 lat_distance; // 起点与参考轨迹最近点的横向距离
//     lat_distance = -(input_point.x - nearest_point.x) * sin(nearest_point.yaw) + (input_point.y - nearest_point.y) *
//     cos(nearest_point.yaw); lat_distance_ = fabs(lat_distance); threadLogger_->info("lat_distance:{}",
//     lat_distance_); if (pow(nearest_point.x - input_point.x, 2) + pow(nearest_point.y - input_point.y, 2) >
//     pow(fabs(lat_distance) + 1.5, 2))
//     {
//         threadLogger_->info("几何距离：{}", sqrt(pow(nearest_point.x - input_point.x, 2) + pow(nearest_point.y -
//         input_point.y, 2))); threadLogger_->info("与匹配点纵向距离太远，需要进行hybird A*拟合");

//         return true;
//     }
//     float64 delta_angle = fabs(fmod(input_point.yaw - nearest_point.yaw + 3 * M_PI, 2 * M_PI) - M_PI);
//     threadLogger_->info("横向距离：{},和匹配点的角度偏差：{}", fabs(lat_distance), delta_angle);
//     if (fabs(lat_distance) < (vehicle_param_.lat_min_distance_struct + eps) && fabs(delta_angle) < (M_PI / 18 + eps))
//     {
//         return false;
//     }
//     else
//     {
//         if (fabs(lat_distance) > (vehicle_param_.lat_min_distance_struct + eps))
//         {
//             threadLogger_->info("横向距离超阈值,需要hybird A*规划");
//         }
//         if (fabs(delta_angle) > (M_PI / 18 + eps))
//         {
//             threadLogger_->info("角度偏差超阈值,需要hybird A*规划");
//         }
//         return true;
//     }
// }

// bool Planning::removeDuplicates(vector<Trajectory_Point> &input, std::vector<Trajectory_Point> &result)
// {
//     result.clear();
//     result.push_back(input.front());
//     bool flag = false;
//     for (int i = 1; i < input.size(); i++)
//     {
//         if (fabs(input.at(i).x - input.at(i - 1).x) <= 0.3 && fabs(input.at(i).y - input.at(i - 1).y) <= 0.3)
//         {
//             flag = true;
//             threadLogger_->error("检测到重复点");
//             cout << "检测到重复点" << endl;
//             continue;
//         }
//         result.push_back(input.at(i));
//     }

//     return flag;
// }

// // 成功：true，失败：false
// vector<Trajectory_Point> Planning::RandomOffsetWithoutCuravture(vector<Trajectory_Point> &path)
// {
//     // std::ofstream file_write;
//     // file_write.open("curvature_input.txt");
//     // for (int i = 0; i < path.size(); i++)
//     // {
//     //     file_write << 0.0 << " " << path.at(i).curvature << endl;
//     // }
//     // file_write.close();
//     vector<Trajectory_Point> input_points, temp_path, result_path, path_;

//     std::random_device rd;
//     std::mt19937 gen(rd());

//     // 定义您想要生成的浮点数的集合
//     std::vector<float> weights = {-1.0, -0.75, -0.5, -0.25, 0, 0.25, 0.5, 0.75, 1.0};

//     // 使用uniform_int_distribution从集合中随机选择一个索引
//     std::uniform_int_distribution<std::size_t> dis(0, weights.size() - 1);
//     float weight = 0.0;

//     // 打印结果
//     std::cout << "Random weight: " << weight << std::endl;

//     int num = 0;
//     do
//     {
//         result_path.clear();
//         num++;
//         cout << "num:" << num << endl;
//         if (num > 50)
//         {
//             return result_path;
//         }

//         path_ = path;
//         // 从集合中随机选择一个权重
//         weight = weights[dis(gen)];
//         vector<pair<int, int>> reverse_section, forward_section;

//         int start = 0, end = 0;
//         bool flag1;

//         if (path_.front().offset_flag == true) // 起步就是需要偏移的路段
//         {
//             threadLogger_->info("起步就是需要偏移的路段");

//             flag1 = true;
//             for (int i = 0; i < path_.size() - 1; i++)
//             {
//                 if (path_.at(i + 1).offset_flag != path_.at(i).offset_flag)
//                 {
//                     end = i;
//                     if (flag1 == true)
//                     {
//                         forward_section.push_back(make_pair(start, end));
//                         flag1 = false;
//                     }
//                     else
//                     {
//                         reverse_section.push_back(make_pair(start, end));
//                         flag1 = true;
//                     }
//                     start = i + 1;
//                 }
//             }
//         }
//         else // 起步就是不需要偏移的路段
//         {
//             threadLogger_->info("起步就是不需要偏移的路段");

//             flag1 = false;
//             for (int i = 0; i < path_.size() - 1; i++)
//             {
//                 if (path_.at(i + 1).offset_flag != path_.at(i).offset_flag)
//                 {
//                     end = i;
//                     if (flag1 == true)
//                     {
//                         forward_section.push_back(make_pair(start, end));
//                         flag1 = false;
//                     }
//                     else
//                     {
//                         reverse_section.push_back(make_pair(start, end));
//                         flag1 = true;
//                     }
//                     start = i + 1;
//                 }
//             }
//         }
//         if (path_.back().offset_flag == true) // 最后一段为需要偏移的道路
//         {
//             cout << "最后一段需要偏移" << endl;
//             forward_section.push_back(make_pair(start, path_.size() - 1));
//         }
//         else
//         {
//             cout << "最后一段不需要偏移" << endl;
//             reverse_section.push_back(make_pair(start, path_.size() - 1));
//         }

//         threadLogger_->info("规划出的路径包含{}个偏移路段，{}个不偏移路段", forward_section.size(),
//         reverse_section.size());

//         for (int i = 0; i < forward_section.size(); i++)
//         {
//             threadLogger_->info("偏移路段索引：({},{})", forward_section.at(i).first, forward_section.at(i).second);
//         }

//         for (int i = 0; i < reverse_section.size(); i++)
//         {
//             threadLogger_->info("不偏移路段索引：({},{})", reverse_section.at(i).first,
//             reverse_section.at(i).second);
//         }

//         float off_set = 0.0;
//         // std::ofstream file_out;
//         // file_out.open("off_set.txt");
//         // 如果先前
//         if (path_.front().direction == 0)
//         {
//             int j = 0;
//             for (int i = 0; i < forward_section.size(); i++)
//             {
//                 start = forward_section.at(i).first;
//                 end = forward_section.at(i).second;
//                 int a = 0, sum = 0;
//                 input_points.clear();
//                 for (int m = start; m <= end; m = m + 1)
//                 {
//                     sum++;
//                 }

//                 int m;
//                 vector<float> vec_off_set;
//                 for (m = start; m <= end; m = m + 1)
//                 {
//                     a++;
//                     if (end - start > 250)
//                     {
//                         off_set = CalculateOffSetWithoutCuravture(a, sum + 1, weight); //
//                         off_set的大小决定偏移幅度，正负决定偏移方向
//                     }
//                     else // 如果改段路太短，不进行偏移
//                     {
//                         off_set = 0.0;
//                     }

//                     path_.at(m).x = path_.at(m).x + off_set * cos(path_.at(m).yaw + M_PI / 2);
//                     path_.at(m).y = path_.at(m).y + off_set * sin(path_.at(m).yaw + M_PI / 2);
//                     if (fabs(path_.at(m).left) > eps && fabs(path_.at(m).right > eps))
//                     {
//                         path_.at(m).left = path_.at(m).left - off_set;
//                         path_.at(m).right = path_.at(m).right + off_set;
//                     }

//                     input_points.push_back(path_.at(m));
//                     vec_off_set.push_back(off_set);
//                 }

//                 // for (size_t index = 0; index < vec_off_set.size(); index++)
//                 // {
//                 //     file_out << 0.0 << " " << vec_off_set.at(index) << endl;
//                 // }

//                 // // 将最后一个点放入temp_path中
//                 // if (m != end + 1)
//                 // {
//                 //     input_points.push_back(path_.at(end));
//                 // }
//                 // string file_name = "input_points.txt";
//                 threadLogger_->info("输入点的数量：{}", input_points.size());
//                 // temp_path.clear();
//                 threadLogger_->info("当前偏移的权重：{}", weight);

//                 // CalculateCubicSplineCurve(input_points, temp_path);

//                 // result_path.insert(result_path.end(), temp_path.begin(), temp_path.end());
//                 result_path.insert(result_path.end(), input_points.begin(), input_points.end());

//                 threadLogger_->info("input_points.size():{}", input_points.size());

//                 // threadLogger_->info("resule_path.size():{}", result_path.size());

//                 if (j < reverse_section.size())
//                 {
//                     result_path.insert(result_path.end(), path_.begin() + reverse_section.at(j).first, path_.begin()
//                     + reverse_section.at(j).second + 1); j++;
//                 }
//             }
//         }
//         else
//         {
//             int i = 0;
//             for (int j = 0; j < reverse_section.size(); j++)
//             {
//                 result_path.insert(result_path.end(), path_.begin() + reverse_section.at(j).first, path_.begin() +
//                 reverse_section.at(j).second + 1); if (i < forward_section.size())
//                 {
//                     start = forward_section.at(i).first;
//                     end = forward_section.at(i).second;
//                     int a = 0, sum = 0;
//                     input_points.clear();
//                     for (int m = start; m <= end; m = m + 1)
//                     {
//                         sum++;
//                     }

//                     int m;
//                     for (m = start; m <= end; m = m + 1)
//                     {
//                         a++;
//                         off_set = CalculateOffSetWithoutCuravture(a, sum + 1, weight); //
//                         off_set的大小决定偏移幅度，正负决定偏移方向

//                         path_.at(m).x = path_.at(m).x + off_set * cos(path_.at(m).yaw + M_PI / 2);
//                         path_.at(m).y = path_.at(m).y + off_set * sin(path_.at(m).yaw + M_PI / 2);
//                         if (fabs(path_.at(m).left) > eps && fabs(path_.at(m).right > eps))
//                         {
//                             path_.at(m).left = path_.at(m).left - off_set;
//                             path_.at(m).right = path_.at(m).right + off_set;
//                         }
//                         input_points.push_back(path_.at(m));
//                     }

//                     // 将最后一个点放入temp_path中
//                     if (m != end + 1)
//                     {
//                         input_points.push_back(path_.at(end));
//                     }
//                     // string file_name = "input_points.txt";
//                     threadLogger_->info("输入点的数量：{}", input_points.size());
//                     temp_path.clear();
//                     threadLogger_->info("当前偏移的权重：{}", weight);

//                     // CalculateCubicSplineCurve(input_points, temp_path);
//                     // result_path.insert(result_path.end(), temp_path.begin(), temp_path.end());
//                     result_path.insert(result_path.end(), input_points.begin(), input_points.end());
//                     threadLogger_->info("input_points.size():{}", input_points.size());

//                     // threadLogger_->info("resule_path.size():{}", result_path.size());

//                     i++;
//                 }
//             }
//         }
//         // file_out.close();

//         // } while (PathCollisionCheck(result_path) || !CheckCurvature(result_path)); // 碰撞检测通过、曲率校验通过
//     } while (!CheckCurvature(result_path)); // 碰撞检测通过、曲率校验通过
//     threadLogger_->info("找到合适的权重：{}", weight);

//     return result_path;
// }
// float Planning::CalculateOffSetWithoutCuravture(int index, int sum, float weight)
// {
//     // threadLogger_->info("weight:{}", weight);
//     float max_l = vehicle_param_.max_l;
//     float L = max_l * weight; // 控制默认偏移量
//     L = L * WeightFunction(index, sum);
//     return L;
// }
// void Planning::CalculateCubicSplineCurve(const std::vector<Trajectory_Point> points, std::vector<Trajectory_Point>
// &cubicspline_path)
// {
//     std::vector<float64> x_set;
//     std::vector<float64> y_set;
//     x_set.reserve(points.size());
//     y_set.reserve(points.size());
//     for (const auto &pt : points)
//     {

//         x_set.push_back(pt.x);
//         y_set.push_back(pt.y);
//     }
//     threadLogger_->info("x_set.size():{}", x_set.size());

//     threadLogger_->info("x_set.back():{}", x_set.back());

//     threadLogger_->info("y_set.size():{}", y_set.size());

//     threadLogger_->info("y_set.back():{}", y_set.back());

//     CalculateStation(x_set, y_set);
//     sx_.set_points(s_, x_set);
//     sy_.set_points(s_, y_set);
//     threadLogger_->info("line10758  s_.size():{}", s_.size());

//     kDeltaS_ = 0.1;
//     threadLogger_->info("s_.back():{}", s_.back());

//     vector<pair<pair<float, float>, unsigned char>> vec;
//     pair<pair<float, float>, unsigned char> temp;
//     float left = 0.0, right = 0.0;
//     float dis_sum = 0.0;
//     for (int i = 1; i < points.size(); i++)
//     {
//         dis_sum += sqrt(pow(points.at(i).x - points.at(i - 1).x, 2) + pow(points.at(i).y - points.at(i - 1).y, 2));
//         if (points.at(i).attribute != points.at(i - 1).attribute)
//         {
//             right = dis_sum;
//             temp.first.first = left;
//             temp.first.second = right;
//             temp.second = points.at(i - 1).attribute;
//             vec.push_back(temp);
//             left = right + 0.01;
//         }
//     }
//     temp.first.first = left;
//     temp.first.second = dis_sum;
//     temp.second = points.back().attribute;
//     vec.push_back(temp);
//     threadLogger_->info("vec的具体信息如下：vec.size():{}", vec.size());

//     for (int i = 0; i < vec.size(); i++)
//     {
//         threadLogger_->info("[{},{}]:{}", vec.at(i).first.first, vec.at(i).first.second, (int)vec.at(i).second);
//     }

//     float epsilon = 0.0001; // 容差值
//     for (float64 s = 0.0; s <= s_.back(); s += kDeltaS_)
//     {

//         float64 dx = sx_.deriv(1, s);
//         float64 dy = sy_.deriv(1, s);

//         float64 ddx = sx_.deriv(2, s);
//         float64 ddy = sy_.deriv(2, s);

//         float angle = atan(dy / dx);
//         if (dx < 0)
//             angle = angle + M_PI;
//         else if (dx >= 0 && dy < 0)
//             angle = angle + 2 * M_PI;
//         //  threadLogger_->info("angle = {}", angle );
//         float64 cur = (ddy * dx - ddx * dy) / pow(dx * dx + dy * dy, 3.0 / 2);
//         unsigned char attri;
//         for (int i = 0; i < vec.size(); i++)
//         {
//             if (s - vec.at(i).first.first > -epsilon && vec.at(i).first.second - s > -epsilon)
//             {
//                 attri = vec.at(i).second;
//             }
//         }
//         Trajectory_Point temp_point;
//         temp_point.x = sx_(s);
//         temp_point.y = sy_(s);
//         temp_point.yaw = angle;
//         temp_point.curvature = cur;
//         temp_point.direction = 0;
//         temp_point.attribute = attri;
//         temp_point.distance = s;
//         cubicspline_path.emplace_back(temp_point);
//     }
//     threadLogger_->info("cubicspline_path.size():{}", cubicspline_path.size());
// }

// bool Planning::PathCollisionCheck(std::vector<Trajectory_Point> Path)
// {
//     // 确定所有的区域的外边界和内边界
//     std::vector<uint8> zones;
//     if (zone_sequence_.size() == 0)
//     {
//         zones.push_back(start_node_);
//     }
//     else
//     {
//         zones = zone_sequence_;
//     }
//     Single_Point midpoint_;
//     midpoint_.x = (start_point_.x + end_point_.x) / 2;
//     midpoint_.y = (start_point_.y + end_point_.y) / 2;
//     midpoint_.z = 0;
//     threadLogger_->info("start_point_.x:{} ,start_point_.y:{}, end_point_.x:{},end_point_.y:{}, midpoint_.x:{},
//     midpoint_.y:{}", start_point_.x, start_point_.y, end_point_.x, end_point_.y, midpoint_.x, midpoint_.y);

//     // 为了方便计算哈希值，将外边界、内边界每个坐标点统一减去固定值
//     HybridAStar::Bound road_outer_bound;
//     HybridAStar::Bound road_inner_bound;
//     vector<HybridAStar::Coordinate> v_road_outer_bound;
//     vector<HybridAStar::Coordinate> v_road_inner_bound;
//     HybridAStar::Coordinate temp_Coordinate;
//     threadLogger_->info("zones.size():{}", zones.size());

//     for (int32 i = 0; i < zones.size(); i++)
//     {
//         Single_Border ext_border = all_zones_.at(zones.at(i) - 1).external_border;
//         vector<Single_Border> obs_borders = all_zones_.at(zones.at(i) - 1).inner_borders;

//         // 获取道路外边界 (以传入参数的外边界点作为道路外边界)
//         for (int32 index = 0; index < ext_border.border_points.size(); index++)
//         {
//             if (ext_border.border_points.at(index).type == 0) // 只传不可穿越的边界点
//             {
//                 temp_Coordinate.x = ext_border.border_points.at(index).x - midpoint_.x;
//                 temp_Coordinate.y = ext_border.border_points.at(index).y - midpoint_.y;
//                 temp_Coordinate.z = ext_border.border_points.at(index).z - midpoint_.z;
//                 v_road_outer_bound.emplace_back(temp_Coordinate);
//             }
//         }

//         // 获取道路内边界 (暂时以传入参数的障碍物边界作为道路内边界)
//         for (int32 index = 0; index < obs_borders.size(); index++)
//         {
//             for (int32 j = 0; j < obs_borders.at(index).border_points.size(); j++)
//             {
//                 temp_Coordinate.x = obs_borders.at(index).border_points.at(j).x - midpoint_.x;
//                 temp_Coordinate.y = obs_borders.at(index).border_points.at(j).y - midpoint_.y;
//                 temp_Coordinate.z = obs_borders.at(index).border_points.at(j).z - midpoint_.z;
//                 v_road_inner_bound.emplace_back(temp_Coordinate);
//             }
//         }
//     }
//     road_inner_bound.emplace_back(v_road_inner_bound);
//     road_outer_bound.emplace_back(v_road_outer_bound);

//     // 由于为了对Path进行碰撞检测，也统一对每个Path点减去固定值
//     for (int i = 0; i < Path.size(); i++)
//     {
//         Path.at(i).x -= midpoint_.x;
//         Path.at(i).y -= midpoint_.y;
//         Path.at(i).z -= midpoint_.z;
//     }

//     collison_check_.InitParam(vehicle_param_);
//     collison_check_.InitBoundMap(road_outer_bound);
//     collison_check_.InitObstacleMap(road_inner_bound);
//     threadLogger_->info("Path.size():{}", Path.size());

//     for (int i = 0; i < Path.size(); i++)
//     {
//         Point temp_point(Path.at(i).x, Path.at(i).y, Path.at(i).z, Path.at(i).yaw, MotionDirection::Forward);
//         if (collison_check_.IsVehicleCollision(temp_point))
//         {
//             threadLogger_->info("路径点{}碰撞检测不通过 ", i);

//             return true;
//         }
//     }
//     return false;
// }
// void Planning::CalculateStation(const std::vector<float64> &xs, const std::vector<float64> &ys)
// {
//     float64 cum = 0.0;
//     s_.clear();
//     s_.push_back(cum);

//     for (unsigned int i = 1; i < xs.size(); i++)
//     {
//         float64 dx = xs.at(i) - xs.at(i - 1);
//         float64 dy = ys.at(i) - ys.at(i - 1);
//         cum += std::hypot(dx, dy);

//         s_.push_back(cum);
//     }
//     threadLogger_->info("****s_.back():{}", s_.back());
// }
// bool Planning::CheckCurvature(std::vector<Trajectory_Point> &tra)
// {
//     float threshold = 0.15;
//     for (int i = 0; i < tra.size(); i++)
//     {
//         if (fabs(tra.at(i).curvature) > threshold)
//         {
//             threadLogger_->info("第{}个点曲率值为：{}，该值超标", i, tra.at(i).curvature);

//             return false;
//         }
//     }
//     return true;
// }

// float Planning::WeightFunction(int k, int sum)
// {
//     // int sita = vehicle_param_.sita;
//     int sita = 200;
//     int x;
//     if (k < sum / 2)
//     {
//         x = k;
//     }
//     else
//     {
//         x = sum - 1 - k;
//     }
//     // return 1.0 / (1 + pow(vehicle_param_.base, (-(x - sita))));
//     return 1.0 / (1 + pow(1.1, (-(x - sita))));
// }

// bool Planning::doesTrajectorySelfIntersect(Path &path)
// {
//     // 通过判断yaw的变化了分析是否画圈
//     // 判断方法，设置36个if else，36个标志位，如果超过24个标志为被置为true，即被判定为绕圈

//     vector<int> vec(36, 0);
//     for (int i = 0; i < path.size(); i++)
//     {
//         std::cout << path.at(i).angle << endl;
//     }
//     for (int i = 0; i < path.size(); i++)
//     {
//         vec.at(floor(path.at(i).angle * 18.0 / M_PI)) = 1;
//     }
//     int sum = 0;
//     for (int i = 0; i < vec.size(); i++)
//     {
//         if (vec.at(i) == 1)
//         {
//             sum++;
//         }
//     }
//     double percent = sum / 36.0;
//     if (percent < 0.75)
//     {
//         threadLogger_->info("绕圈检测，百分比为{}，检测通过", percent);
//         return false;
//     }
//     else
//     {
//         threadLogger_->warn("绕圈检测，百分比为{}，检测不通过", percent);
//         return true;
//     }
// }

// // bool Planning::CheckDirection(Path &input_path)
// // {
// //     double angle;
// //     for (int i = 0; i < input_path.size() - 1; i++)
// //     {
// //         angle = atan((input_path.at(i + 1).y - input_path.at(i).y) / (input_path.at(i + 1).x -
// input_path.at(i).x));
// //         if (angle)
// //     }
// // }

// bool Planning::checkPathFracture(std::vector<Trajectory_Point> &input_path)
// {
//     double dis = 0;
//     for (int i = 0; i < input_path.size() - 1; i++)
//     {
//         dis = pow(input_path.at(i).x - input_path.at(i + 1).x, 2) + pow(input_path.at(i).y - input_path.at(i + 1).y,
//         2); if (dis > 9)
//         {
//             return false; // 如果相邻点间距大于3m，说明路径产生断裂
//         }
//     }
// }

// bool Planning::OverSpeedCheck(std::vector<Trajectory_Point> &input_path)
// {
//     bool flag = false;
//     for (int i = 0; i < input_path.size() - 1; i++)
//     {
//         if (input_path.at(i).speed > input_path.at(i).speed_limit + 0.5)
//         {
//             cout << "i:" << i << "speed:" << input_path.at(i).speed << "speed_limit:" << input_path.at(i).speed_limit
//             << endl; threadLogger_->info("i:{}  speed:{}   speed_limit:{}", i, input_path.at(i).speed,
//             input_path.at(i).speed_limit); flag = true;
//         }
//     }
//     if (flag == true)
//         return true;
//     return false;
// }
// 全局轨迹规划--路径规划
void Planning::PathPlanning() {
    threadLogger_->info("Enter PathPlanning");
    time_t start_time, end_time;
    time(&start_time);
    start_point_.yaw = start_point_.yaw / 180.0 * M_PI;
    end_point_.yaw   = end_point_.yaw / 180.0 * M_PI;
    threadLogger_->info(" task_type_: {}", (int)task_type_);
    ErrorType temp_error_type;
    if (task_type_ == static_cast<uint>(TaskType::TEMP_MOVE_CAR)) {
        // 临时挪车不走参考路径
        temp_error_type = MoveCar();
    }
    else {
        temp_error_type = LuWangPlanning();
    }
    if (temp_error_type != ErrorType::SUCCESS) {
        threadLogger_->info(" ... Planning Failed...");
        error_type_     = static_cast<uint>(temp_error_type);
        last_task_type_ = task_type_;
    }
}
// 挪车
ErrorType Planning::MoveCar() {}

// 沿路网路径规划
ErrorType Planning::LuWangPlanning() {
    // 定义一个搜索

    //  起点设定初始search_dis.at(0)的搜索半径
    //     没有搜索到路径，提高搜索半径
    //   搜索到，将搜索到的路径存入vector<int> a
    //     对终点设置初始search_dis.at(0)的搜索半径
    //       没有搜索到路径，提高搜索半径
    //     搜索到，将搜索到的路径存入vector<int> b
    //       从a和b中找到联通的一对
    std::pair<int, int> success_pair;
    bool                found = false;                             // 用于跟踪是否找到了成功的路径对
    vector<double>      search_dis{0.5, 1, 5, 10, 20, 40, 60, 70}; // 离散搜索半径

    vector<int> start_path_vec, end_path_vec;
    for (auto end_search_radius : search_dis) {
        if (FindReferencePath(end_point_, GlobalVariable::getInstance()->all_referencelines_, end_search_radius,
                              end_path_vec)) {
            for (auto start_search_radius : search_dis) {
                if (FindReferencePath(start_point_, GlobalVariable::getInstance()->all_referencelines_,
                                      start_search_radius, start_path_vec)) {
                    // 在start_path_vec和end_path_vec中查找连通路径
                    for (auto start : start_path_vec) {
                        for (auto end : end_path_vec) {
                            if (CheckIsOrNotConnect(start, end)) {
                                success_pair = std::make_pair(start, end);
                                found        = true; // 标记为已找到
                                break;               // 退出内层循环
                            }
                        }
                        if (found) break; // 如果已找到，退出中间层循环
                    }
                    if (found) break; // 如果已找到，退出外层循环
                }
            }
        }
    }
    // 找到起点、终点对应的索引
    int    start_index, end_index;
    double start_lat_dis, start_lon_dis;
    double end_lat_dis, end_lon_dis;
    double temp_dis;
    double min_distance = std::numeric_limits<double>::max();
    for (int i = 0; i < GlobalVariable::getInstance()->all_referencelines_.at(success_pair.first).size(); i++) {
        temp_dis =
            sqrt(pow(start_point_.x - GlobalVariable::getInstance()->all_referencelines_.at(success_pair.first).x, 2) +
                 pow(start_point_.y - GlobalVariable::getInstance()->all_referencelines_.at(success_pair.first).y, 2));
        if (temp_dis < min_distance) {
            min_distance = temp_dis;
            start_index  = i;
        }
    }


    // 路径裁剪拼接
    PathClipAndSplice();
}
bool Planning::FindReferencePath(_SinglePoint point, vector<_SingleTraj>& trajs, double radius, vector<int> vec) {
    vec.clear();
    if (!trajs.size()) {
        threadLogger_->info(" The trajectory.size() = 0  ");
        return ErrorType::NO_REFERENCELINE;
    }
    bool temp_bool = false;

    double nearest_dis = std::numeric_limits<double>::max();
    double temp_dis;
    for (unsigned int i = 0; i < trajs.size(); i++) {
        nearest_dis = std::numeric_limits<double>::max();
        for (unsigned int j = 0; j < trajs.at(i).size(); j++) {
            temp_dis = sqrt(pow(point.x - trajs.at(i).at(j).x, 2) + pow(point.y - trajs.at(i).at(j).y, 2));
            if (temp_dis < nearest_dis) {
                nearest_dis = temp_dis;
            }
        }
        if (nearest_dis < radius) {
            vec.push_back(i);
            temp_bool = true;
        }
    }


    if (temp_bool)
        return true;
    else
        return false;
}

bool Planning::CheckIsOrNotConnect(int start, int end) {
    dijkstra_.InitialDijkstra(road_directed_graph_.graph);
    if (dijkstra_.searchpath(start, end)) {
        return true;
    }
    else {
        return false;
    }
}

void Planning::GetNearestPoint(_SinglePoint point, int index, double& dis, double& lat, double& lon) {
    double minDistance   = std::numeric_limits<double>::max();
    doubel min_dis       = -1;
    int    nearest_index = -1;
    for (const auto& traj : GlobalVariable::getInstance()->all_referencelines_.at(index)) {
        for (int i = 0; i < traj.size(); i++) {
            min_dis = sqrt(pow(point.x - p.x, 2) + pow(point.y - p.y, 2));
            if (min_dis < minDistance) {
                minDistance   = min_dis;
                nearest_index = i;
            }
        }

        lat = -(point.x - traj.at(nearest_index).x) * sin(traj.at(nearest_index).yaw) +
              (point.y - traj.at(nearest_index).y) * cos(traj.at(nearest_index).yaw);
        lat = fabs(point.);
        lon = (traj.at(nearest_index).y - point.y) / sin(traj.at(nearest_index).yaw) +
              lat / tan(traj.at(nearest_index).yaw);
    }
}