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

void CConfigureIO ::rand_param(float64 &rand_dist)
{
    // 每次导入地图时，随机平移参考轨迹 -0.3~0.3
    // 生成随机数
    //    int a = 0,b = 2
    //    int t;
    //    srand((unsigned int)time(NULL));
    //    t = rand()%(b-a) + a + 1;
    //    rand_dist = 0.3 * (pow(-1,t)*rand() / float64(RAND_MAX));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(-5, 1);

    rand_dist = distrib(gen) * 0.1;
    std::cout << "rand_dist = " << rand_dist << "\n";
}

bool CConfigureIO ::GetMap(std::vector<Single_Zone> &all_zones, Directed_Graph &road_directed_graph, GlobalPlanning::tarRviz &tar_rviz)
{
    char *buffer;
    int length = 0;

    // char *file_name = (char *)"src/global_planning/map/map_shulan.json"; // 舒南
    char *file_name = (char *)"src/global_planning/map/map_lunan.json"; // 鲁南
    FILE *file = fopen(file_name, "rb+");
    if (!file)
    {
        std::cout << "GetMap->open failed " << std::endl;
        return false;
    }
    else
    {
        std::cout << "open succeed " << std::endl;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    buffer = new char[length + 1];
    fseek(file, 0, SEEK_SET);
    memset(buffer, 0, length + 1);
    fread(buffer, length, 1, file);

    // float64 rand_dist;
    // rand_param(rand_dist);

    rapidjson::Document doc;
    doc.Parse(buffer);
    if (doc.HasParseError())
    {
        doc.GetParseError();
        doc.GetErrorOffset();
        std::cout << "parse failed......" << std::endl;
        // return false;
    }
    doc.GetAllocator();
    // 有向图
    if (doc.HasMember("Road_Directed_Graph"))
    {
        Value &val = doc["Road_Directed_Graph"];

        if (val.IsObject())
        {
            if (val.HasMember("graph") && val["graph"].IsArray())
            {
                const rapidjson::Value &array = val["graph"].GetArray();
                size_t len = array.Size();
                for (size_t i = 0; i < len; i++)
                {
                    const rapidjson::Value &arrayy = array[i];
                    size_t lenn = arrayy.Size();
                    std::vector<double> ppt;
                    for (size_t j = 0; j < lenn; j++)
                    {
                        double temp_ppt;
                        temp_ppt = arrayy[j].GetDouble();
                        if (fabs(temp_ppt - 0.0) < 1e-6)
                        {
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
    if (doc.HasMember("all_zone_atr"))
    {
        Value &val = doc["all_zone_atr"];
        if (val.IsArray() && !val.Empty())
        {
            for (size_t i = 0; i < val.Size(); ++i)
            {
                Value &tempval = val[i];
                if (tempval.IsObject())
                {
                    Single_Zone pt;
                    if (tempval.HasMember("zone_id"))
                    {
                        pt.zone_id = tempval["zone_id"].GetInt();
                    }
                    if (tempval.HasMember("max_speed"))
                    {
                        pt.max_speed = tempval["max_speed"].GetFloat();
                    }
                    if (tempval.HasMember("zone_type"))
                    {
                        pt.zone_type = tempval["zone_type"].GetInt();
                    }
                    // parking_points
                    if (tempval.HasMember("parking_points"))
                    {
                        Value &temp_park_points = tempval["parking_points"];
                        if (temp_park_points.IsArray() && !temp_park_points.Empty())
                        {
                            for (size_t i = 0; i < temp_park_points.Size(); ++i)
                            {
                                rapidjson::Value &tempobj = temp_park_points[i];
                                if (tempobj.IsObject())
                                {
                                    Single_Point point;
                                    point.x = tempobj["x"].GetDouble();
                                    point.y = tempobj["y"].GetDouble();
                                    point.z = tempobj["z"].GetFloat();
                                    point.yaw = tempobj["yaw"].GetFloat();
                                    pt.parking_points.push_back(point);
                                }
                            }
                        }
                    }
                    // load_points
                    if (tempval.HasMember("load_points"))
                    {
                        Value &temp = tempval["load_points"];
                        if (temp.IsArray() && !temp.Empty())
                        {
                            for (size_t i = 0; i < temp.Size(); ++i)
                            {
                                rapidjson::Value &tempobj = temp[i];
                                if (tempobj.IsObject())
                                {
                                    Single_Point point;
                                    point.x = tempobj["x"].GetDouble();
                                    point.y = tempobj["y"].GetDouble();
                                    point.z = tempobj["z"].GetFloat();
                                    point.yaw = tempobj["yaw"].GetFloat();
                                    pt.load_points.push_back(point);
                                }
                            }
                        }
                    }
                    // unload_points
                    if (tempval.HasMember("unload_points"))
                    {
                        Value &temp = tempval["unload_points"];
                        if (temp.IsArray() && !temp.Empty())
                        {
                            for (size_t i = 0; i < temp.Size(); ++i)
                            {
                                rapidjson::Value &tempobj = temp[i];
                                if (tempobj.IsObject())
                                {
                                    Single_Point point;
                                    point.x = tempobj["x"].GetDouble();
                                    point.y = tempobj["y"].GetDouble();
                                    point.z = tempobj["z"].GetFloat();
                                    point.yaw = tempobj["yaw"].GetFloat();
                                    pt.unload_points.push_back(point);
                                }
                            }
                        }
                    }

                    // inner_borders
                    if (tempval.HasMember("inner_borders"))
                    {
                        Value &temp = tempval["inner_borders"];
                        for (size_t i = 0; i < temp.Size(); ++i)
                        {
                            rapidjson::Value &tempobj = temp[i];
                            if (tempobj.IsObject())
                            {
                                Single_Border border;
                                if (tempobj.HasMember("point_num"))
                                {
                                    border.point_num = tempobj["point_num"].GetInt64();
                                }
                                if (tempobj.HasMember("border_points"))
                                {
                                    Single_Border_Point temp_inner_border;
                                    for (size_t j = 0; j < temp.Size(); ++j)
                                    {
                                        Value &tempborder = tempobj[j];
                                        temp_inner_border.x = tempborder["x"].GetDouble();
                                        temp_inner_border.y = tempborder["y"].GetDouble();
                                        temp_inner_border.z = tempborder["z"].GetFloat();
                                        temp_inner_border.type = tempborder["type"].GetInt();
                                        border.border_points.push_back(temp_inner_border);
                                    }
                                }

                                pt.inner_borders.push_back(border);
                            }
                        }
                    }

                    // external_border
                    if (tempval.HasMember("external_border"))
                    {
                        Value &temp = tempval["external_border"];
                        if (temp.IsObject())
                        {
                            Single_Border border;
                            if (temp.HasMember("point_num"))
                            {
                                border.point_num = temp["point_num"].GetUint();
                            }
                            if (temp.HasMember("border_points"))
                            {
                                Value &temp_border_points = temp["border_points"];
                                Single_Border_Point temp_external_border;
                                for (size_t j = 0; j < temp_border_points.Size(); ++j)
                                {
                                    Value &tempborder = temp_border_points[j];

                                    temp_external_border.x = tempborder["x"].GetDouble();
                                    temp_external_border.y = tempborder["y"].GetDouble();
                                    temp_external_border.z = tempborder["z"].GetFloat();
                                    temp_external_border.type = tempborder["type"].GetInt();
                                    pt.external_border.border_points.push_back(temp_external_border);
                                }
                            }
                        }
                    }

                    // 参考路径
                    if (tempval.HasMember("reference_trajs") && tempval["reference_trajs"].IsArray())
                    {
                        rapidjson::Value &temp_reference_trajs = tempval["reference_trajs"].GetArray();
                        for (size_t j = 0; j < temp_reference_trajs.Size(); j++)
                        {
                            Single_Trajectory tra;
                            Value &temp = temp_reference_trajs[j];
                            if (temp.HasMember("start_zone_id"))
                            {
                                tra.start_zone_id = temp["start_zone_id"].GetInt();
                            }
                            if (temp.HasMember("current_zone_id"))
                            {
                                tra.current_zone_id = temp["current_zone_id"].GetInt();
                            }
                            if (temp.HasMember("end_zone_id"))
                            {
                                tra.end_zone_id = temp["end_zone_id"].GetInt();
                            }
                            if (temp.HasMember("traj_point_num"))
                            {
                                tra.traj_point_num = temp["traj_point_num"].GetInt();
                            }
                            if (temp.HasMember("id"))
                            {
                                tra.id = temp["id"].GetInt();
                            }
                            if (temp.HasMember("trajectory"))
                            {
                                rapidjson::Value &tempobj = temp["trajectory"];
                                Trajectory_Point temp_tra;
                                for (size_t j = 0; j < tempobj.Size(); ++j)
                                {
                                    Value &temppoint = tempobj[j];
                                    temp_tra.x = temppoint["x"].GetDouble();
                                    temp_tra.y = temppoint["y"].GetDouble();
                                    temp_tra.z = temppoint["z"].GetFloat();
                                    temp_tra.yaw = temppoint["yaw"].GetFloat();
                                    temp_tra.yaw = temp_tra.yaw / 180.0 * M_PI;
                                    temp_tra.left = temppoint["left"].GetDouble();
                                    temp_tra.right = temppoint["right"].GetDouble();
                                    temp_tra.slope = temppoint["slope"].GetFloat();
                                    temp_tra.speed = temppoint["speed"].GetFloat();
                                    temp_tra.speed_limit = temppoint["speed_limit"].GetFloat();
                                    //    temp_tra.distance    = temppoint["distance"].GetFloat();
                                    temp_tra.attribute = temppoint["attribute"].GetDouble();
                                    temp_tra.curvature = temppoint["curvature"].GetFloat();
                                    temp_tra.direction = temppoint["direction"].GetInt();
                                    // temp_tra.x = temppoint["x"].GetDouble() + rand_dist * cos(temp_tra.yaw + M_PI / 2);
                                    // temp_tra.y = temppoint["y"].GetDouble() + rand_dist * sin(temp_tra.yaw + M_PI / 2);
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
    for (size_t index = 0; index < all_zones.size(); index++)
    {
        std::vector<Single_Border_Point>::iterator iter = all_zones.at(index).external_border.border_points.begin();
        for (; iter != all_zones.at(index).external_border.border_points.end(); iter++)
        {
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

#if 0
    // 将边界输出
    std ::vector<Single_Border_Point> ext_border1;
    std ::vector<Single_Border_Point> ext_border;
    std::ofstream outfile3;
    outfile3.open("src/global_planning/map/area_path_jiuzhi.txt", std::ios::out);
    if (!outfile3)
    {
        std::cout << "open failed!!!!" << std::endl;
    }
    for (size_t index = 0; index < all_zones.size(); index++)
    {
        //        if(index == 4)
        //        {
        ext_border1.insert(ext_border1.end(), all_zones.at(index).external_border.border_points.begin(),
                           all_zones.at(index).external_border.border_points.end());
        //        }
    }

    for (size_t jndex = 0; jndex < ext_border1.size(); jndex++)
    {

        ext_border.push_back(ext_border1.at(jndex));
    }
    for (size_t i = 0; i < ext_border.size(); i++)
    {

        outfile3 << std ::setprecision(15)
                 << ext_border.at(i).x << " "
                 << ext_border.at(i).y << " "
                 << ext_border.at(i).z << std::endl;
    }
    outfile3.close();
#endif
    return true;
}

bool CConfigureIO ::GetVehicleParam(vehicle_param &vehicle_param)
{
    char *buffer;
    int length = 0;
    FILE *file;
    // 设置一个config文件，设置判断值，来选择车辆参数

    file = fopen("src/global_planning/config/vehicle_param.json", "rb+");

    if (!file)
    {
        std::cout << "车参数文件open failed " << std::endl;
        return false;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    buffer = new char[length + 1];
    fseek(file, 0, SEEK_SET);
    memset(buffer, 0, length + 1);
    fread(buffer, length, 1, file);

    tar_start_end veh_start_end;
    rapidjson::Document doc;
    doc.Parse(buffer);
    if (doc.HasParseError())
    {
        cout << "parse失败......" << endl;
        return false;
    }
    doc.GetAllocator();

    if (doc.HasMember("m_Veh_Param"))
    {
        Value &val = doc["m_Veh_Param"];
        if (val.IsObject())
        {
            // 车辆参数
            if (val.HasMember("radious"))
                veh_start_end.m_Veh_Param.radious = val["radious"].GetDouble();
            if (val.HasMember("wheel_base"))
                veh_start_end.m_Veh_Param.wheel_base = val["wheel_base"].GetDouble();
            if (val.HasMember("max_steering"))
                veh_start_end.m_Veh_Param.max_steering = val["max_steering"].GetDouble() * M_PI / 180.0;
            if (val.HasMember("min_steering"))
                veh_start_end.m_Veh_Param.min_steering = val["min_steering"].GetDouble() * M_PI / 180.0;
            if (val.HasMember("safe_margin_bound"))
            {
                veh_start_end.m_Veh_Param.safe_margin_bound = val["safe_margin_bound"].GetDouble();
                cout << "veh_start_end.m_Veh_Param.safe_margin_bound :" << veh_start_end.m_Veh_Param.safe_margin_bound << endl;
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
            if (val.HasMember("delta_s"))
                veh_start_end.m_Veh_Param.delta_s = val["delta_s"].GetDouble();
            if (val.HasMember("delta_dist"))
                veh_start_end.m_Veh_Param.delta_dist = val["delta_dist"].GetDouble();
            if (val.HasMember("grid_dist"))
                veh_start_end.m_Veh_Param.grid_dist = val["grid_dist"].GetDouble();
            if (val.HasMember("max_kappa"))
                veh_start_end.m_Veh_Param.max_kappa = val["max_kappa"].GetDouble();
            if (val.HasMember("error_term"))
                veh_start_end.m_Veh_Param.error_term = val["error_term"].GetDouble();
            if (val.HasMember("grid_angle"))
                veh_start_end.m_Veh_Param.grid_angle = val["grid_angle"].GetDouble() * M_PI / 180.0;
            if (val.HasMember("step_length"))
                veh_start_end.m_Veh_Param.step_length = val["step_length"].GetDouble();
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
            if (val.HasMember("max_iterations_astar"))
                veh_start_end.m_Veh_Param.max_iterations_astar = val["max_iterations_astar"].GetUint();
            if (val.HasMember("backward_search_range"))
                veh_start_end.m_Veh_Param.backward_search_range = val["backward_search_range"].GetDouble();
            if (val.HasMember("cusp_extension_distance"))
                veh_start_end.m_Veh_Param.cusp_extension_distance = val["cusp_extension_distance"].GetUint();
            if (val.HasMember("linear_preferred_distance_square"))
                veh_start_end.m_Veh_Param.linear_preferred_distance_square = val["linear_preferred_distance_square"].GetDouble();
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
            if (val.HasMember("min_distance"))
                veh_start_end.m_Veh_Param.min_distance = val["min_distance"].GetDouble();
            if (val.HasMember("lat_min_distance"))
                veh_start_end.m_Veh_Param.lat_min_distance = val["lat_min_distance"].GetDouble();
            if (val.HasMember("lon_min_distance"))
                veh_start_end.m_Veh_Param.lon_min_distance = val["lon_min_distance"].GetDouble();
            if (val.HasMember("lat_min_distance_struct"))
                veh_start_end.m_Veh_Param.lat_min_distance_struct = val["lat_min_distance_struct"].GetDouble();
            if (val.HasMember("bfs_search"))
                veh_start_end.m_Veh_Param.bfs_search = val["bfs_search"].GetBool();
            if (val.HasMember("safe_margin_error"))
                veh_start_end.m_Veh_Param.safe_margin_error = val["safe_margin_error"].GetDouble();

            if (val.HasMember("offset_enable"))
                veh_start_end.m_Veh_Param.offset_enable = val["offset_enable"].GetDouble();
            if (val.HasMember("multi_section_speed_limit_enable"))
                veh_start_end.m_Veh_Param.multi_section_speed_limit_enable = val["multi_section_speed_limit_enable"].GetDouble();
            if (val.HasMember("light_regular_road_speed_limit"))
                veh_start_end.m_Veh_Param.light_regular_road_speed_limit = val["light_regular_road_speed_limit"].GetDouble();
            if (val.HasMember("light_bumpy_road_speed_limit"))
                veh_start_end.m_Veh_Param.light_bumpy_road_speed_limit = val["light_bumpy_road_speed_limit"].GetDouble();
            if (val.HasMember("light_slope_road_speed_limit"))
                veh_start_end.m_Veh_Param.light_slope_road_speed_limit = val["light_slope_road_speed_limit"].GetDouble();
            if (val.HasMember("light_narrow_road_speed_limit"))
                veh_start_end.m_Veh_Param.light_narrow_road_speed_limit = val["light_narrow_road_speed_limit"].GetDouble();
            if (val.HasMember("light_intersection_road_speed_limit"))
                veh_start_end.m_Veh_Param.light_intersection_road_speed_limit = val["light_intersection_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_regular_road_speed_limit"))
                veh_start_end.m_Veh_Param.heavy_regular_road_speed_limit = val["heavy_regular_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_bumpy_road_speed_limit"))
                veh_start_end.m_Veh_Param.heavy_bumpy_road_speed_limit = val["heavy_bumpy_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_narrow_road_speed_limit"))
                veh_start_end.m_Veh_Param.heavy_narrow_road_speed_limit = val["heavy_narrow_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_intersection_road_speed_limit"))
                veh_start_end.m_Veh_Param.heavy_intersection_road_speed_limit = val["heavy_intersection_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_slope_road_speed_limit"))
                veh_start_end.m_Veh_Param.heavy_slope_road_speed_limit = val["heavy_slope_road_speed_limit"].GetDouble();
            if (val.HasMember("weather"))
                veh_start_end.m_Veh_Param.weather = val["weather"].GetDouble();
            if (val.HasMember("s_curve_speed_limit"))
                veh_start_end.m_Veh_Param.s_curve_speed_limit = val["s_curve_speed_limit"].GetUint();
            if (val.HasMember("task_type"))
            {
                cout << "task_type:" << val["task_type"].GetUint() << endl;
                veh_start_end.m_Veh_Param.task_type = val["task_type"].GetUint();
            }
            else
                cout << "NO task_type 参数" << endl;
            if (val.HasMember("reverse_speed"))
            {
                veh_start_end.m_Veh_Param.reverse_speed = val["reverse_speed"].GetDouble();
            }
            else
            {
                cout << "NO reverse_speed 参数" << endl;
            }
            if (val.HasMember("kMaxAcceleration"))
                veh_start_end.m_Veh_Param.kMaxAcceleration = val["kMaxAcceleration"].GetFloat();
            if (val.HasMember("kMinAcceleration"))
                veh_start_end.m_Veh_Param.kMinAcceleration = val["kMinAcceleration"].GetFloat();
            if (val.HasMember("kDeltaSpeed"))
                veh_start_end.m_Veh_Param.kDeltaSpeed = val["kDeltaSpeed"].GetFloat();
            if (val.HasMember("kErrorTerm"))
                veh_start_end.m_Veh_Param.kErrorTerm = val["kErrorTerm"].GetFloat();
            if (val.HasMember("kSmoothnessTerm"))
                veh_start_end.m_Veh_Param.kSmoothnessTerm = val["kSmoothnessTerm"].GetFloat();
            if (val.HasMember("kDiscreteNumber"))
                veh_start_end.m_Veh_Param.kDiscreteNumber = val["kDiscreteNumber"].GetFloat();
            if (val.HasMember("max_l"))
                veh_start_end.m_Veh_Param.max_l = val["max_l"].GetFloat();
            if (val.HasMember("sita"))
                veh_start_end.m_Veh_Param.sita = val["sita"].GetFloat();
            if (val.HasMember("base"))
                veh_start_end.m_Veh_Param.base = val["base"].GetFloat();
        }
        vehicle_param = veh_start_end.m_Veh_Param;
    }
    return true;
}

#if 0
bool CConfigureIO :: Get_Map_SingleZone(g_Map,std :: string& strVersion,std :: vector<GlobalPlanning :: Single_Zone>& ve_singzo)
{
#if 1
    int nArea_Num = 0;
    Get_Map_Common(nArea_Num,strVersion);
    nArea_Num = 
    if(nArea_Num <= 0)
        return false;

    for(int index = 1 ; index <= nArea_Num; index++)
    {
        GlobalPlanning :: Single_Zone singzo;
        std :: string strid;
        //获取区域id,区域类型,区域属性,最大速度
        Get_Map_Zone(index,singzo.zone_id,singzo.zone_type,singzo.zone_attribute,singzo.max_speed);           
        //获取区域内的停车点集
        Get_Map_Parking_Spot(index,singzo.parking_points);
        //获取区域内的装载点集
        Get_Map_Load(index,singzo.load_points);
        //获取区域内的卸载点集
        Get_Map_Unload(index,singzo.unload_points);
        //获取区域的内、外边界
        Get_Map_Border(index,singzo.external_border,singzo.inner_borders,tar_rviz);
        //获取区域内的参考路径
        Get_Map_Reference_Path(index,singzo.reference_trajs);
        ve_singzo.emplace_back(singzo);
    }
#endif
   return true;
}

bool CConfigureIO :: Get_Map_Zone(const int num,uint8& id,uint8& type,uint8& attribute,float32& max_speed)
{
   std :: string str; 
   std :: stringstream stream;
   stream << std :: setw(3) << std :: setfill('0') << num;
   stream >> str;
   std :: string key = "Attribute_" + str + ":area_id";
   std :: string get = "";
   get = iniparser_getstring(init_path_txt_,key.c_str(),"null");
   id = atoi(get.c_str());
   printf("区域ID = %d\n",id);

   key = "Attribute_" + str + ":area_type";
   get = iniparser_getstring(init_path_txt_,key.c_str(),"null");
   type =  atoi(get.c_str());
   printf("区域类型 = %d\n",type);

   key = "Attribute_" + str + ":area_attribute";
   get = iniparser_getstring(init_path_txt_,key.c_str(),"null");
   attribute = atoi(get.c_str());
   printf("区域属性 = %d\n",attribute);

   key = "Attribute_" + str + ":max_speed";
   max_speed = iniparser_getdouble(init_path_txt_,key.c_str(),-1);
   printf("最大速度 = %f\n",max_speed);
   return true;
}

bool CConfigureIO :: Get_Map_Parking_Spot(const int num,std :: vector<GlobalPlanning :: Single_Point>& single_point)
{
    std :: string str; 
    std :: stringstream stream;
    stream << std :: setw(3) << std :: setfill('0') << num;
    stream >> str;
    std :: string key = "ParkingSpot_" + str + ":spot_num";

    int n_num = iniparser_getint(init_path_txt_,key.c_str(),0);
    n_num = 0;

    if(n_num <= 0)
    {
        return false;
    }
    std :: string str2 = "";
    std :: string key2;
    std :: vector<std :: string> str_point;
    stream.clear();
    for(int index = 1; index <= n_num; index++)
    {
        stream << index;
        stream >> str2;
        stream.clear();
        key2 = "ParkingSpot_" + str + ":parking_spot_" + str2;
        std :: string temp_tr = iniparser_getstring(init_path_txt_,key2.c_str(),"null");
        cout << "temp_tr = " << temp_tr << endl;
        str_point.emplace_back(temp_tr);
    }
    std :: vector<std :: string> temp_point;
    stream.clear();
    for(int index = 0; index < str_point.size(); index++)
    {
        SplitString(str_point.at(index),temp_point,"_");
        GlobalPlanning :: Single_Point point;
        for(int jndex = 0; jndex < temp_point.size(); jndex++)
        {
            stream << std :: setprecision(6) << temp_point.at(jndex);
            if(0 == jndex)
            {
                stream >> point.x;
                cout << "point.x = " << point.x << endl;
            }
            else if(1 == jndex)
            {
                stream >> point.y;
                cout << "point.y = " << point.y << endl;
            }
            else if(2 == jndex)
            {
                stream >> point.z;
                cout << "point.z = " << point.z << endl;
            }
                
            else if(3 == jndex)
            {
                stream >> point.yaw;
                cout << "point.yaw = " << point.yaw << endl;
            }
            stream.clear();
        }
        single_point.emplace_back(point);
        temp_point.clear();
    }
    cout << "single_point.size = " << single_point.size() << endl;
    return true;
}

//区域内的装载点集
bool CConfigureIO :: Get_Map_Load(const int num,std :: vector<GlobalPlanning :: Single_Point>& single_point)
{
    std :: string str;
    std :: stringstream stream;
    stream << std :: setw(3) << std :: setfill('0') << num;
    stream >> str;
    std :: string key = "Load_" + str + ":spot_num";
    int n_num = iniparser_getint(init_path_txt_,key.c_str(),0);
    n_num = 0;
    cout << "n_num = " << n_num << endl;
    if(n_num <= 0)
    {
        return false;
    }
    std :: string str2 = "";
    std :: string key2;
    std :: vector<std :: string> str_point;
    stream.clear();
    for(int index = 1; index <= n_num; index++)
    {
        stream << index;
        stream >> str2;
        stream.clear();
        key2 = "Load_" + str + ":load_spot_" + str2;
        std :: string temp_tr = iniparser_getstring(init_path_txt_,key2.c_str(),"null");
        cout << "temp_tr = " << temp_tr << endl;
        str_point.emplace_back(temp_tr);
    }
    std :: vector<std :: string> temp_point;
    stream.clear();
    for(int index = 0; index < str_point.size(); index++)
    {
        SplitString(str_point.at(index),temp_point,"_");
        GlobalPlanning :: Single_Point point;
        for(int jndex = 0; jndex < temp_point.size(); jndex++)
        {
            stream << std :: setprecision(6) << temp_point.at(jndex);
            if(0 == jndex)
            {
                stream >> point.x;
            }
            else if(1 == jndex)
            {
                stream >> point.y;
            }
            else if(2 == jndex)
            {
                stream >> point.z;
            }
                
            else if(3 == jndex)
            {
                stream >> point.yaw;
            }
            stream.clear();
        }
        single_point.emplace_back(point);
        temp_point.clear();
    }
    cout << "single_point.size = " << single_point.size() << endl;
    return true;
}


//区域内的卸载点集
bool CConfigureIO :: Get_Map_Unload(const int num,std :: vector<GlobalPlanning :: Single_Point>& single_point)
{
    std :: string str; 
    std :: stringstream stream;
    stream << std :: setw(3) << std :: setfill('0') << num;
    stream >> str;
    std :: string key = "Unload_" + str + ":spot_num";
    int n_num = iniparser_getint(init_path_txt_,key.c_str(),0);
    n_num = 0;
    cout << "n_num = " << n_num << endl;
    if(n_num <= 0)
    {
        return false;
    }
    std :: string str2 = "";
    std :: string key2;
    std :: vector<std :: string> str_point;
    stream.clear();
    for(int index = 1; index <= n_num; index++)
    {
        stream << index;
        stream >> str2;
        stream.clear();        
        key2 = "Unload_" + str + ":unload_spot_" + str2;
        std :: string temp_tr = iniparser_getstring(init_path_txt_,key2.c_str(),"null");
        cout << "temp_tr = " << temp_tr << endl;
        str_point.emplace_back(temp_tr);
    }
    std :: vector<std :: string> temp_point;
    stream.clear();
    for(int index = 0; index < str_point.size(); index++)
    {
        SplitString(str_point.at(index),temp_point,"_");
        GlobalPlanning :: Single_Point point;
        for(int jndex = 0; jndex < temp_point.size(); jndex++)
        {
            stream << std :: setprecision(6) << temp_point.at(jndex);
            if(0 == jndex)
            {
                stream >> point.x;
            }
            else if(1 == jndex)
            {
                stream >> point.y;
            }
            else if(2 == jndex)
            {
                stream >> point.z;
            }
                
            else if(3 == jndex)
            {
                stream >> point.yaw;
            }
            stream.clear();
        }
        single_point.emplace_back(point);
        temp_point.clear();
    }
    cout << "single_point.size = " << single_point.size() << endl;
    return true;
}

//区域内的外边界
//todo:目前不知如何确定内外边界
bool CConfigureIO :: Get_Map_Border(const int num,GlobalPlanning :: Single_Border& outer_boundary,
                                    std :: vector<GlobalPlanning :: Single_Border>& inner_boundary,GlobalPlanning :: tarRviz &tar_rviz)
{
    std :: string str = ""; 
    std :: stringstream stream;
    stream << std :: setw(3) << std :: setfill('0') << num;
    stream >> str;
    std :: string key = "Border_" + str + ":point_num";
    outer_boundary.point_num = iniparser_getint(init_path_txt_,key.c_str(),0);
    cout << "outer_boundary.point_num = " << outer_boundary.point_num << endl;
    if(outer_boundary.point_num <= 0)
    {
        return false;
    }
    std :: string str2 = "";
    std :: string key2;
    std :: vector<std :: string> str_point;
    stream.clear();
    for(int index = 1; index <= outer_boundary.point_num; ++index)
    {
        stream << index;
        stream >> str2;
        stream.clear();
        key2 = "Border_" + str + ":point_" + str2;
        std :: string temp_tr =  iniparser_getstring(init_path_txt_,key2.c_str(),"null");
        str_point.emplace_back(temp_tr);
    }

    std :: vector<std :: string> temp_point;
    // std :: vector<std :: vector<std :: string>> temp_v_point;
    stream.clear();
    for(int index = 0; index < str_point.size(); index++)
    {
        SplitString(str_point.at(index),temp_point,"_");
        // temp_v_point.emplace_back(temp_point);
        GlobalPlanning :: Single_Border_Point coord_point;
        // Point_3d msg_pt;
        geometry_msgs::Point msg_pt;
        for(int jndex = 0; jndex < temp_point.size(); jndex++)
        {
            stream << std :: setprecision(6) << temp_point.at(jndex);
            if(0 == jndex)
            {
                stream >> coord_point.x;
                msg_pt.x = coord_point.x;
            }
            else if(1 == jndex)
            {
                stream >> coord_point.y;
                msg_pt.y = coord_point.y;
            }
            else if(2 == jndex)
            {
                stream >> coord_point.z;
                msg_pt.z = coord_point.z;
            }
            else if(3 == jndex)
            {
                float32 temp_type;
                stream >> temp_type;
                coord_point.type = static_cast<uint8> (temp_type);
            }
            stream.clear();
        }    
        outer_boundary.border_points.emplace_back(coord_point);
        if(tar_rviz.minx > coord_point.x)
            tar_rviz.minx = coord_point.x;
        if(tar_rviz.miny > coord_point.y)
            tar_rviz.miny = coord_point.y;
        tar_rviz.vec_point.emplace_back(msg_pt);
        temp_point.clear();
    }
    cout << "bord.vec_area_point.size = " << outer_boundary.border_points.size() << endl;
    cout << "tar_rviz.vec_point.size = " << tar_rviz.vec_point.size() << endl;
    return true;
}

bool CConfigureIO :: Get_Map_Reference_Path(const int num,std :: vector<GlobalPlanning :: Single_Trajectory>& ref)
{
    std :: string str; 
    std :: stringstream stream;
    stream << std :: setw(3) << std :: setfill('0') << num;
    stream >> str;
    std :: string key = "ReferencePath_" + str + ":path_num";
    // ref.n_num = iniparser_getint(init_path_txt_,key.c_str(),0);
    int n_num = iniparser_getint(init_path_txt_,key.c_str(),0);
    cout << "partspot.n_num = " << n_num << endl;
    if(n_num <= 0)
    {
        return false;
    }
    std :: string str2 = "";
    std :: string key2;
    stream.clear();
    for(int index = 1; index <= n_num; index++)
    {
        // vector<Point> vec_ref;
        GlobalPlanning :: Single_Trajectory vec_ref;
        stream << index;
        stream >> str2;
        stream.clear();
        key2 = "ReferencePath_" + str + ":id" + str2;
        cout << "key2 = " << key2 << endl;
        std :: string temp_tr = iniparser_getstring(init_path_txt_,key2.c_str(),"null");
        cout << "temp_tr = " << temp_tr << endl;
        Get_Reference_Path(temp_tr,vec_ref);
        ref.emplace_back(vec_ref);
    }
    return true;
}

bool CConfigureIO::Get_Reference_Path(const std :: string strref, GlobalPlanning :: Single_Trajectory& single_tr)
{
    if(!strref.empty())
    {
        std :: string temp_start_id = strref.substr(0,3);
        std :: string temp_current_id = strref.substr(3,3);
        std :: string temp_end_id = strref.substr(6,3);
        //路径起始区域id
        single_tr.start_zone_id = atoi(temp_start_id.c_str());
        //路径经过区域id
        single_tr.current_zone_id = atoi(temp_current_id.c_str());
        //路径到达区域id
        single_tr.end_zone_id = atoi(temp_end_id.c_str());
        printf("路径起始区域id = %d,路径经过区域id = %d,路径到达区域id = %d\n",single_tr.start_zone_id,single_tr.current_zone_id,single_tr.end_zone_id);
    }
    std :: string str;
    std :: stringstream stream;
    std :: string key = strref + ":point_num";
    cout << "key = " << key << endl;
    single_tr.traj_point_num = iniparser_getint(reference_txt_,key.c_str(),0);
    cout << "single_tr.traj_point_num = " << single_tr.traj_point_num << endl;

    if(single_tr.traj_point_num <= 0)
    {
        return false;
    }
    std :: string key2;
    std :: vector<std :: string> str_point;
    stream.clear();
    for(int index = 1; index <= single_tr.traj_point_num; index++)
    {
        stream << index;
        stream >> str;
        stream.clear();
        key2 = strref + ":path_point_" + str;
        std :: string temp_tr = iniparser_getstring(reference_txt_,key2.c_str(),"null");
        str_point.emplace_back(temp_tr);
    }

    std :: vector<std :: string> temp_point;
    stream.clear();
    vector<geometry_msgs::Point> gec_ve;
    for(int index = 0; index < str_point.size(); index++)
    {
        SplitString(str_point.at(index),temp_point,"_");
        // Point point;
        GlobalPlanning :: Trajectory_Point point;
        geometry_msgs::Point ge_Point;
        for(int jndex = 0; jndex < temp_point.size(); jndex++)
        {
            stream << std :: setprecision(6) << temp_point.at(jndex);
            if(0 == jndex)
            {
                stream >> point.x;
                // stream >> ge_Point.x;
                ge_Point.x = point.x;
            }
            else if(1 == jndex)
            {
                stream >> point.y;
                // stream >> ge_Point.y;
                ge_Point.y = point.y;
            }
            else if(2 == jndex)
            {
                stream >> point.z;
                // stream >> ge_Point.z;
                ge_Point.z = point.z;
            }
            else if(3 == jndex)
            {
                stream >> point.yaw;
            }
            else if(4 == jndex)
            {
                // stream >> point.speed;

                stream >> point.speed_limit;
            }
            else if(5 == jndex)
            {
                // stream >> point.curvature;
                
                
                //距左边界值
                stream >> point.left;
            }
            else if(6 == jndex)
            {
                // stream >> point.slope;


                //距右边界值
                stream >> point.right;
            }
            else if(7 == jndex)
            {
                float32 temp_type;
                stream >> temp_type;
                point.direction = static_cast<uint8> (temp_type);
            }
            else if(8 == jndex)
            {
                stream >> point.speed;
            }
            // else if(9 == jndex)
            // {
            //     stream >> point.direction;
            // }
            // else if(10 == jndex)
            // {
            //     stream >> point.t;
            // }
            // else if(11 == jndex)
            // {
            //     stream >> point.speed_limit;
            // }
            stream.clear();
        }
        single_tr.trajectory.emplace_back(point);
        gec_ve.emplace_back(ge_Point);
        temp_point.clear();
    }
    // global_path_.emplace_back(vec_point);
    global_path_.emplace_back(gec_ve);
    cout << "single_tr.trajectory.size = " << single_tr.trajectory.size() << endl;
    return true;
}

bool CConfigureIO :: Get_Directed_Graph(GlobalPlanning :: Directed_Graph& dire_graph)
{
    std :: string str; 
    std :: stringstream stream;
    std :: string key = "Attribute:vertex_num";
    std :: string get = iniparser_getstring(graph_map_txt_,key.c_str(),"null");
    dire_graph.node_num = atoi(get.c_str());
    if(dire_graph.node_num <= 0)
    {
        return false;
    }
    key = "Attribute:vertex_name";
    str = iniparser_getstring(graph_map_txt_,key.c_str(),"null");
    cout << "Get_UnDirected_Graph str = " << str << endl;
    stream.clear();
    std :: string str2 = "";
    std :: string key2;
    std :: vector<std :: string> str_point;
    for(int index = 1; index <= dire_graph.node_num; index++)
    {
        stream << index;
        stream >> str2;
        stream.clear();
        key2 = "Attribute:vertex_" + str2;
        std :: string temp_tr = iniparser_getstring(graph_map_txt_,key2.c_str(),"null");
        cout << "temp_tr = " << temp_tr << endl;
        str_point.emplace_back(temp_tr);
    }
    std :: vector<std :: string> temp_point;
    stream.clear();
    for(int index = 0; index < str_point.size(); index++)
    {
        SplitString(str_point.at(index),temp_point,",");
        vector<double> vec_undire;
        Separate_StringList_To_Double(temp_point,vec_undire);
        dire_graph.graph.emplace_back(vec_undire);
        vec_undire.clear();
        temp_point.clear();
    }
    cout << "dire_graph.graph.size = " << dire_graph.graph.size() << endl;

    return true;
}

void CConfigureIO :: SplitString(const std::string &s, std::vector<std::string> &v, const std::string &c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
}

void CConfigureIO::Separate_StringList_To_Double(const std::vector<string> & strlist, vector<double>& vec)
{
    for(int i  = 0; i < strlist.size();i++)
    {
        std :: string strtemp = strlist.at(i);
        if(strlist.at(i) != "INF")
        {
            vec.push_back(atof(strlist.at(i).c_str()));
        }   
        else
           vec.push_back(INF2);
    }
    return;
}

#endif