/******************************************
 > Copyright(C):    湖南大学
 > File name:       c_map_analysis.cpp
 > Author:          jh(HaoJiangYit@163.com)
 > Created Time:    2021/11/24
 > Brief:           编写并构建程序框架,完成函数功能,完善程序逻辑
 * ****************************************/
/*
    Park map analysis
*/
#include "../include/c_map_analysis.h"

const std ::string CConfigureIO ::map_file_name = "src/map/map.json";

const int CConfigureIO ::INF2 = 1e9;


bool CConfigureIO ::GetMap(std::vector<Single_Zone>& all_zones, Directed_Graph& road_directed_graph,
                           GlobalPlanning::tarRviz& tar_rviz) {
    char* buffer;
    int   length = 0;

    // char *file_name = (char *)"src/global_planning/map/map_shulan.json"; // 舒南
    char* file_name = (char*)"src/global_planning/map/map_lunan.json"; // 鲁南
    FILE* file      = fopen(file_name, "rb+");
    if (!file) {
        std::cout << "GetMap->open failed " << std::endl;
        return false;
    }
    else {
        std::cout << "open succeed " << std::endl;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    buffer = new char[length + 1];
    fseek(file, 0, SEEK_SET);
    memset(buffer, 0, length + 1);
    fread(buffer, length, 1, file);


    rapidjson::Document doc;
    doc.Parse(buffer);
    if (doc.HasParseError()) {
        doc.GetParseError();
        doc.GetErrorOffset();
        std::cout << "parse failed......" << std::endl;
        // return false;
    }
    doc.GetAllocator();
    // 有向图
    if (doc.HasMember("Road_Directed_Graph")) {
        Value& val = doc["Road_Directed_Graph"];

        if (val.IsObject()) {
            if (val.HasMember("graph") && val["graph"].IsArray()) {
                const rapidjson::Value& array = val["graph"].GetArray();
                size_t                  len   = array.Size();
                for (size_t i = 0; i < len; i++) {
                    const rapidjson::Value& arrayy = array[i];
                    size_t                  lenn   = arrayy.Size();
                    std::vector<double>     ppt;
                    for (size_t j = 0; j < lenn; j++) {
                        double temp_ppt;
                        temp_ppt = arrayy[j].GetDouble();
                        if (fabs(temp_ppt - 0.0) < 1e-6) {
                            temp_ppt = 10000;
                        }
                        ppt.push_back(temp_ppt);
                    }
                    road_directed_graph.graph.push_back(ppt);
                }
            }
        }
    }
    std::cout << "11111" << std::endl;
    if (doc.HasMember("all_zone_atr")) {
        Value& val = doc["all_zone_atr"];
        if (val.IsArray() && !val.Empty()) {
            for (size_t i = 0; i < val.Size(); ++i) {
                Value& tempval = val[i];
                if (tempval.IsObject()) {
                    Single_Zone pt;
                    if (tempval.HasMember("zone_id")) {
                        pt.zone_id = tempval["zone_id"].GetInt();
                    }
                    if (tempval.HasMember("max_speed")) {
                        pt.max_speed = tempval["max_speed"].GetFloat();
                    }
                    if (tempval.HasMember("zone_type")) {
                        pt.zone_type = tempval["zone_type"].GetInt();
                    }
                    // parking_points
                    if (tempval.HasMember("parking_points")) {
                        Value& temp_park_points = tempval["parking_points"];
                        if (temp_park_points.IsArray() && !temp_park_points.Empty()) {
                            for (size_t i = 0; i < temp_park_points.Size(); ++i) {
                                rapidjson::Value& tempobj = temp_park_points[i];
                                if (tempobj.IsObject()) {
                                    _SinglePoint point;
                                    point.x   = tempobj["x"].GetDouble();
                                    point.y   = tempobj["y"].GetDouble();
                                    point.z   = tempobj["z"].GetFloat();
                                    point.yaw = tempobj["yaw"].GetFloat();
                                    pt.parking_points.push_back(point);
                                }
                            }
                        }
                    }
                    // load_points
                    if (tempval.HasMember("load_points")) {
                        Value& temp = tempval["load_points"];
                        if (temp.IsArray() && !temp.Empty()) {
                            for (size_t i = 0; i < temp.Size(); ++i) {
                                rapidjson::Value& tempobj = temp[i];
                                if (tempobj.IsObject()) {
                                    _SinglePoint point;
                                    point.x   = tempobj["x"].GetDouble();
                                    point.y   = tempobj["y"].GetDouble();
                                    point.z   = tempobj["z"].GetFloat();
                                    point.yaw = tempobj["yaw"].GetFloat();
                                    pt.load_points.push_back(point);
                                }
                            }
                        }
                    }
                    // unload_points
                    if (tempval.HasMember("unload_points")) {
                        Value& temp = tempval["unload_points"];
                        if (temp.IsArray() && !temp.Empty()) {
                            for (size_t i = 0; i < temp.Size(); ++i) {
                                rapidjson::Value& tempobj = temp[i];
                                if (tempobj.IsObject()) {
                                    _SinglePoint point;
                                    point.x   = tempobj["x"].GetDouble();
                                    point.y   = tempobj["y"].GetDouble();
                                    point.z   = tempobj["z"].GetFloat();
                                    point.yaw = tempobj["yaw"].GetFloat();
                                    pt.unload_points.push_back(point);
                                }
                            }
                        }
                    }

                    // inner_borders
                    if (tempval.HasMember("inner_borders")) {
                        Value& temp = tempval["inner_borders"];
                        for (size_t i = 0; i < temp.Size(); ++i) {
                            rapidjson::Value& tempobj = temp[i];
                            if (tempobj.IsObject()) {
                                Single_Border border;
                                if (tempobj.HasMember("point_num")) {
                                    border.point_num = tempobj["point_num"].GetInt64();
                                }
                                if (tempobj.HasMember("border_points")) {
                                    Single_Border_Point temp_inner_border;
                                    for (size_t j = 0; j < temp.Size(); ++j) {
                                        Value& tempborder      = tempobj[j];
                                        temp_inner_border.x    = tempborder["x"].GetDouble();
                                        temp_inner_border.y    = tempborder["y"].GetDouble();
                                        temp_inner_border.z    = tempborder["z"].GetFloat();
                                        temp_inner_border.type = tempborder["type"].GetInt();
                                        border.border_points.push_back(temp_inner_border);
                                    }
                                }

                                pt.inner_borders.push_back(border);
                            }
                        }
                    }

                    // external_border
                    if (tempval.HasMember("external_border")) {
                        Value& temp = tempval["external_border"];
                        if (temp.IsObject()) {
                            Single_Border border;
                            if (temp.HasMember("point_num")) {
                                border.point_num = temp["point_num"].GetUint();
                            }
                            if (temp.HasMember("border_points")) {
                                Value&              temp_border_points = temp["border_points"];
                                Single_Border_Point temp_external_border;
                                for (size_t j = 0; j < temp_border_points.Size(); ++j) {
                                    Value& tempborder = temp_border_points[j];

                                    temp_external_border.x    = tempborder["x"].GetDouble();
                                    temp_external_border.y    = tempborder["y"].GetDouble();
                                    temp_external_border.z    = tempborder["z"].GetFloat();
                                    temp_external_border.type = tempborder["type"].GetInt();
                                    pt.external_border.border_points.push_back(temp_external_border);
                                }
                            }
                        }
                    }

                    // 参考路径
                    if (tempval.HasMember("reference_trajs") && tempval["reference_trajs"].IsArray()) {
                        rapidjson::Value& temp_reference_trajs = tempval["reference_trajs"].GetArray();
                        for (size_t j = 0; j < temp_reference_trajs.Size(); j++) {
                            Single_Trajectory tra;
                            Value&            temp = temp_reference_trajs[j];
                            if (temp.HasMember("start_zone_id")) {
                                tra.start_zone_id = temp["start_zone_id"].GetInt();
                            }
                            if (temp.HasMember("current_zone_id")) {
                                tra.current_zone_id = temp["current_zone_id"].GetInt();
                            }
                            if (temp.HasMember("end_zone_id")) {
                                tra.end_zone_id = temp["end_zone_id"].GetInt();
                            }
                            if (temp.HasMember("traj_point_num")) {
                                tra.traj_point_num = temp["traj_point_num"].GetInt();
                            }
                            if (temp.HasMember("id")) {
                                tra.id = temp["id"].GetInt();
                            }
                            if (temp.HasMember("trajectory")) {
                                rapidjson::Value& tempobj = temp["trajectory"];
                                Trajectory_Point  temp_tra;
                                for (size_t j = 0; j < tempobj.Size(); ++j) {
                                    Value& temppoint     = tempobj[j];
                                    temp_tra.x           = temppoint["x"].GetDouble();
                                    temp_tra.y           = temppoint["y"].GetDouble();
                                    temp_tra.z           = temppoint["z"].GetFloat();
                                    temp_tra.yaw         = temppoint["yaw"].GetFloat();
                                    temp_tra.yaw         = temp_tra.yaw / 180.0 * M_PI;
                                    temp_tra.left        = temppoint["left"].GetDouble();
                                    temp_tra.right       = temppoint["right"].GetDouble();
                                    temp_tra.slope       = temppoint["slope"].GetFloat();
                                    temp_tra.speed       = temppoint["speed"].GetFloat();
                                    temp_tra.speed_limit = temppoint["speed_limit"].GetFloat();

                                    temp_tra.attribute = temppoint["attribute"].GetDouble();
                                    temp_tra.curvature = temppoint["curvature"].GetFloat();
                                    temp_tra.direction = temppoint["direction"].GetInt();

                                    tra.trajectory.push_back(temp_tra);
                                    geometry_msgs::Point temp_border_points;
                                    temp_border_points.x = temp_tra.x;
                                    temp_border_points.y = temp_tra.y;
                                    temp_border_points.z = temp_tra.z;
                                    tar_rviz.vec_point.push_back(temp_border_points);
                                }
                            }
                            pt.reference_trajs.push_back(tra);
                        }
                    }
                    all_zones.push_back(pt);
                }
            }
        }
    }
    for (size_t index = 0; index < all_zones.size(); index++) {
        std::vector<Single_Border_Point>::iterator iter = all_zones.at(index).external_border.border_points.begin();
        for (; iter != all_zones.at(index).external_border.border_points.end(); iter++) {
            // if(iter -> type == 0)
            // {
            geometry_msgs::Point temp_border_points;
            temp_border_points.x = iter->x;
            temp_border_points.y = iter->y;
            temp_border_points.z = iter->z;
            tar_rviz.vec_point.push_back(temp_border_points);
            // }
        }
    }

    return true;
}

bool CConfigureIO ::GetVehicleParam(vehicle_param& vehicle_param) {
    char* buffer;
    int   length = 0;
    FILE* file;
    // 设置一个config文件，设置判断值，来选择车辆参数

    file = fopen("src/global_planning/config/vehicle_param.json", "rb+");

    if (!file) {
        std::cout << "车参数文件open failed " << std::endl;
        return false;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    buffer = new char[length + 1];
    fseek(file, 0, SEEK_SET);
    memset(buffer, 0, length + 1);
    fread(buffer, length, 1, file);

    tar_start_end       veh_start_end;
    rapidjson::Document doc;
    doc.Parse(buffer);
    if (doc.HasParseError()) {
        cout << "parse失败......" << endl;
        return false;
    }
    doc.GetAllocator();

    if (doc.HasMember("m_Veh_Param")) {
        Value& val = doc["m_Veh_Param"];
        if (val.IsObject()) {
            // 车辆参数
            if (val.HasMember("radious")) veh_start_end.m_Veh_Param.radious = val["radious"].GetDouble();
            if (val.HasMember("wheel_base")) veh_start_end.m_Veh_Param.wheel_base = val["wheel_base"].GetDouble();
            if (val.HasMember("max_steering"))
                veh_start_end.m_Veh_Param.max_steering = val["max_steering"].GetDouble() * M_PI / 180.0;
            if (val.HasMember("min_steering"))
                veh_start_end.m_Veh_Param.min_steering = val["min_steering"].GetDouble() * M_PI / 180.0;
            if (val.HasMember("safe_margin_bound")) {
                veh_start_end.m_Veh_Param.safe_margin_bound = val["safe_margin_bound"].GetDouble();
                cout << "veh_start_end.m_Veh_Param.safe_margin_bound :" << veh_start_end.m_Veh_Param.safe_margin_bound
                     << endl;
            }

            if (val.HasMember("veh_center_2_side"))
                veh_start_end.m_Veh_Param.veh_center_2_side = val["veh_center_2_side"].GetDouble();
            if (val.HasMember("veh_center_2_front"))
                veh_start_end.m_Veh_Param.veh_center_2_front = val["veh_center_2_front"].GetDouble();
            if (val.HasMember("safe_margin_obstacle"))
                veh_start_end.m_Veh_Param.safe_margin_obstacle = val["safe_margin_obstacle"].GetDouble();
            if (val.HasMember("veh_center_2_rear_bound"))
                veh_start_end.m_Veh_Param.veh_center_2_rear_bound = val["veh_center_2_rear_bound"].GetDouble();
            if (val.HasMember("veh_center_2_rear_obstacle"))
                veh_start_end.m_Veh_Param.veh_center_2_rear_obstacle = val["veh_center_2_rear_obstacle"].GetDouble();
            // 算法参数
            if (val.HasMember("delta_s")) veh_start_end.m_Veh_Param.delta_s = val["delta_s"].GetDouble();
            if (val.HasMember("delta_dist")) veh_start_end.m_Veh_Param.delta_dist = val["delta_dist"].GetDouble();
            if (val.HasMember("grid_dist")) veh_start_end.m_Veh_Param.grid_dist = val["grid_dist"].GetDouble();
            if (val.HasMember("max_kappa")) veh_start_end.m_Veh_Param.max_kappa = val["max_kappa"].GetDouble();
            if (val.HasMember("error_term")) veh_start_end.m_Veh_Param.error_term = val["error_term"].GetDouble();
            if (val.HasMember("grid_angle"))
                veh_start_end.m_Veh_Param.grid_angle = val["grid_angle"].GetDouble() * M_PI / 180.0;
            if (val.HasMember("step_length")) veh_start_end.m_Veh_Param.step_length = val["step_length"].GetDouble();
            if (val.HasMember("curvature_term"))
                veh_start_end.m_Veh_Param.curvature_term = val["curvature_term"].GetDouble();
            if (val.HasMember("switch_penalty"))
                veh_start_end.m_Veh_Param.switch_penalty = val["switch_penalty"].GetDouble();
            if (val.HasMember("forward_penalty"))
                veh_start_end.m_Veh_Param.forward_penalty = val["forward_penalty"].GetDouble();
            if (val.HasMember("min_path_Length"))
                veh_start_end.m_Veh_Param.min_path_Length = val["min_path_Length"].GetDouble();
            if (val.HasMember("start_offset_distance"))
                veh_start_end.m_Veh_Param.start_offset_distance = val["start_offset_distance"].GetDouble();
            if (val.HasMember("end_offset_distance"))
                veh_start_end.m_Veh_Param.end_offset_distance = val["end_offset_distance"].GetDouble();
            if (val.HasMember("smoothness_term"))
                veh_start_end.m_Veh_Param.smoothness_term = val["smoothness_term"].GetDouble();
            if (val.HasMember("backward_penalty"))
                veh_start_end.m_Veh_Param.backward_penalty = val["backward_penalty"].GetDouble();
            if (val.HasMember("turnning_penalty"))
                veh_start_end.m_Veh_Param.turnning_penalty = val["turnning_penalty"].GetDouble();
            if (val.HasMember("angle_discrete_num"))
                veh_start_end.m_Veh_Param.angle_discrete_num = val["angle_discrete_num"].GetUint();
            if (val.HasMember("max_fitting_radius"))
                veh_start_end.m_Veh_Param.max_fitting_radius = val["max_fitting_radius"].GetDouble();
            if (val.HasMember("max_iterations_opti"))
                veh_start_end.m_Veh_Param.max_iterations_opti = val["max_iterations_opti"].GetDouble();

            if (val.HasMember("backward_search_range"))
                veh_start_end.m_Veh_Param.backward_search_range = val["backward_search_range"].GetDouble();
            if (val.HasMember("cusp_extension_distance"))
                veh_start_end.m_Veh_Param.cusp_extension_distance = val["cusp_extension_distance"].GetUint();
            if (val.HasMember("linear_preferred_distance_square"))
                veh_start_end.m_Veh_Param.linear_preferred_distance_square =
                    val["linear_preferred_distance_square"].GetDouble();
            if (val.HasMember("min_speed_limit"))
                veh_start_end.m_Veh_Param.min_speed_limit = val["min_speed_limit"].GetFloat();
            if (val.HasMember("mid_speed_limit"))
                veh_start_end.m_Veh_Param.mid_speed_limit = val["mid_speed_limit"].GetFloat();
            if (val.HasMember("max_speed_limit"))
                veh_start_end.m_Veh_Param.max_speed_limit = val["max_speed_limit"].GetFloat();
            if (val.HasMember("min_curvature"))
                veh_start_end.m_Veh_Param.min_curvature = val["min_curvature"].GetFloat();
            if (val.HasMember("max_curvature"))
                veh_start_end.m_Veh_Param.max_curvature = val["max_curvature"].GetFloat();


            if (val.HasMember("lat_min_distance_struct"))
                veh_start_end.m_Veh_Param.lat_min_distance_struct = val["lat_min_distance_struct"].GetDouble();

            if (val.HasMember("safe_margin_error"))
                veh_start_end.m_Veh_Param.safe_margin_error = val["safe_margin_error"].GetDouble();

            if (val.HasMember("offset_enable"))
                veh_start_end.m_Veh_Param.offset_enable = val["offset_enable"].GetDouble();
            if (val.HasMember("multi_section_speed_limit_enable"))
                veh_start_end.m_Veh_Param.multi_section_speed_limit_enable =
                    val["multi_section_speed_limit_enable"].GetDouble();
            if (val.HasMember("light_regular_road_speed_limit"))
                veh_start_end.m_Veh_Param.light_regular_road_speed_limit =
                    val["light_regular_road_speed_limit"].GetDouble();
            if (val.HasMember("light_bumpy_road_speed_limit"))
                veh_start_end.m_Veh_Param.light_bumpy_road_speed_limit =
                    val["light_bumpy_road_speed_limit"].GetDouble();
            if (val.HasMember("light_slope_road_speed_limit"))
                veh_start_end.m_Veh_Param.light_slope_road_speed_limit =
                    val["light_slope_road_speed_limit"].GetDouble();
            if (val.HasMember("light_narrow_road_speed_limit"))
                veh_start_end.m_Veh_Param.light_narrow_road_speed_limit =
                    val["light_narrow_road_speed_limit"].GetDouble();
            if (val.HasMember("light_intersection_road_speed_limit"))
                veh_start_end.m_Veh_Param.light_intersection_road_speed_limit =
                    val["light_intersection_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_regular_road_speed_limit"))
                veh_start_end.m_Veh_Param.heavy_regular_road_speed_limit =
                    val["heavy_regular_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_bumpy_road_speed_limit"))
                veh_start_end.m_Veh_Param.heavy_bumpy_road_speed_limit =
                    val["heavy_bumpy_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_narrow_road_speed_limit"))
                veh_start_end.m_Veh_Param.heavy_narrow_road_speed_limit =
                    val["heavy_narrow_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_intersection_road_speed_limit"))
                veh_start_end.m_Veh_Param.heavy_intersection_road_speed_limit =
                    val["heavy_intersection_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_slope_road_speed_limit"))
                veh_start_end.m_Veh_Param.heavy_slope_road_speed_limit =
                    val["heavy_slope_road_speed_limit"].GetDouble();
            if (val.HasMember("weather")) veh_start_end.m_Veh_Param.weather = val["weather"].GetDouble();
            if (val.HasMember("s_curve_speed_limit"))
                veh_start_end.m_Veh_Param.s_curve_speed_limit = val["s_curve_speed_limit"].GetUint();
            if (val.HasMember("task_type")) {
                cout << "task_type:" << val["task_type"].GetUint() << endl;
                veh_start_end.m_Veh_Param.task_type = val["task_type"].GetUint();
            }
            else
                cout << "NO task_type 参数" << endl;
            if (val.HasMember("reverse_speed")) {
                veh_start_end.m_Veh_Param.reverse_speed = val["reverse_speed"].GetDouble();
            }
            else {
                cout << "NO reverse_speed 参数" << endl;
            }
            if (val.HasMember("kMaxAcceleration"))
                veh_start_end.m_Veh_Param.kMaxAcceleration = val["kMaxAcceleration"].GetFloat();
            if (val.HasMember("kMinAcceleration"))
                veh_start_end.m_Veh_Param.kMinAcceleration = val["kMinAcceleration"].GetFloat();
            if (val.HasMember("kDeltaSpeed")) veh_start_end.m_Veh_Param.kDeltaSpeed = val["kDeltaSpeed"].GetFloat();
            if (val.HasMember("kErrorTerm")) veh_start_end.m_Veh_Param.kErrorTerm = val["kErrorTerm"].GetFloat();
            if (val.HasMember("kSmoothnessTerm"))
                veh_start_end.m_Veh_Param.kSmoothnessTerm = val["kSmoothnessTerm"].GetFloat();
            if (val.HasMember("kDiscreteNumber"))
                veh_start_end.m_Veh_Param.kDiscreteNumber = val["kDiscreteNumber"].GetFloat();
            if (val.HasMember("max_l")) veh_start_end.m_Veh_Param.max_l = val["max_l"].GetFloat();
            if (val.HasMember("sita")) veh_start_end.m_Veh_Param.sita = val["sita"].GetFloat();
            if (val.HasMember("base")) veh_start_end.m_Veh_Param.base = val["base"].GetFloat();
        }
        vehicle_param = veh_start_end.m_Veh_Param;
    }
    return true;
}


#endif