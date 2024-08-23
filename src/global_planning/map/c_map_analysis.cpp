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
#include "c_map_analysis.h"


bool CConfigureIO::GetMap(vector<vector<double>>& road_directed_graph_, vector<_BorderPoint>& map_border_, map<int, _SingleTraj>& all_referencelines_, vector<int>& sequence_mapping_, tarRviz& tar_rviz) {
    char* buffer;
    int   length = 0;

    // char *file_name = (char *)"src/global_planning/map/map_shulan.json"; // 舒南
    // char* file_name = (char*)"src/global_planning/map/map.json"; // 鲁南
    char* file_name = (char*)"src/global_planning/map/map.json"; // 鲁南

    FILE* file = fopen(file_name, "rb+");
    if (!file) {
        cout << "GetMap->open failed " << endl;

        return false;
    }
    else {
        cout << "open succeed " << endl;
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
        cout << "parse failed......" << endl;
        // return false;
    }
    doc.GetAllocator();


    // 解析border_points
    // const Value&         borderPointsArray = doc["external_border"]["border_points"];
    const Value&         borderPointsArray = doc["external_border"];
    _BorderPoint         bp;
    vector<_BorderPoint> v_bp;
    for (int i = 0; i < borderPointsArray.Size(); i++) {
        bp.x    = borderPointsArray[i]["x"].GetDouble();
        bp.y    = borderPointsArray[i]["y"].GetDouble();
        bp.z    = borderPointsArray[i]["z"].GetDouble();
        bp.type = static_cast<unsigned char>(borderPointsArray[i]["type"].GetInt());
        if (bp.type == 0) {
            v_bp.emplace_back(bp);
        }
    }
    map_border_ = v_bp;
    cout << "解析border_points完毕" << endl;

    // 解析reference_trajs
    const Value&          trajsArray = doc["reference_trajs"];
    map<int, _SingleTraj> m_traj;
    _SingleTraj           traj;
    _TrajectoryPoint      tp;
    cout << "trajsArray.Size():" << trajsArray.Size() << endl;
    for (int i = 0; i < trajsArray.Size(); i++) {
        traj.trajectory.clear();
        traj.id                      = trajsArray[i]["id"].GetInt();
        const Value& trajPointsArray = trajsArray[i]["trajectory"];
        cout << "trajPointsArray.Size()：" << trajPointsArray.Size() << endl;
        for (int j = 0; j < trajPointsArray.Size(); j++) {
            tp.x         = trajPointsArray[j]["x"].GetDouble();
            tp.y         = trajPointsArray[j]["y"].GetDouble();
            tp.z         = trajPointsArray[j]["z"].GetDouble();
            tp.yaw       = trajPointsArray[j]["yaw"].GetDouble() / 180.0 * M_PI;
            tp.curvature = trajPointsArray[j]["curvature"].GetDouble();
            tp.attribute = static_cast<unsigned char>(trajPointsArray[j]["attribute"].GetInt());
            tp.direction = static_cast<unsigned char>(trajPointsArray[j]["direction"].GetInt());
            traj.trajectory.push_back(tp);
        }
        m_traj[traj.id] = traj;
    }
    all_referencelines_ = m_traj;
    cout << "解析reference_trajs完毕" << endl;
    cout << "m_traj.size():" << m_traj.size() << endl;
    for (auto iter : m_traj) {
        cout << "id:" << iter.first << "数量：" << iter.second.trajectory.size() << endl;
    }


    // 解析relation
    const Value&          relationObj = doc["relation"];
    map<int, vector<int>> m_relation;
    int                   key;
    vector<int>           relVec;
    for (Value::ConstMemberIterator itr = relationObj.MemberBegin(); itr != relationObj.MemberEnd(); ++itr) {
        key = stoi(itr->name.GetString());
        cout << "key:" << key << endl;
        const Value& relArray = itr->value;
        relVec.clear();
        for (int k = 0; k < relArray.Size(); k++) {
            relVec.push_back(relArray[k].GetInt());
        }
        m_relation[key] = relVec;
    }

    cout << "解析relation完毕,relation.size():" << m_relation.size() << endl;

    // 调用GlobalVariable类内部的CreateDirectedGraph来生成referenceline_graph_


    GlobalVariable::getInstance()->CreateSequenceMapping(all_referencelines_);
    sequence_mapping_ = GlobalVariable::getInstance()->GetSequenceMapping();
    cout << "sequence_mapping_.size():" << sequence_mapping_.size() << endl;


    GlobalVariable::getInstance()->CreateDirectedGraph(m_relation);

    road_directed_graph_ = GlobalVariable::getInstance()->GetReferencelineGraph();

    cout << "生成sequence_mapping_和referenceline_graph_完毕" << endl;
    // 将地图边界和参考路径放进tar_rviz.vec_point中

    for (int i = 0; i < map_border_.size(); i++) {
        geometry_msgs::Point temp_border_points;
        temp_border_points.x = map_border_.at(i).x;
        temp_border_points.y = map_border_.at(i).y;
        temp_border_points.z = map_border_.at(i).z;
        tar_rviz.vec_point.push_back(temp_border_points);
    }
    for (const auto& pair : all_referencelines_) {
        for (int i = 0; i < pair.second.trajectory.size(); i++) {
            geometry_msgs::Point temp_referenceline_points;
            temp_referenceline_points.x = pair.second.trajectory.at(i).x;
            temp_referenceline_points.y = pair.second.trajectory.at(i).y;
            temp_referenceline_points.z = pair.second.trajectory.at(i).z;
            tar_rviz.vec_point.push_back(temp_referenceline_points);
            if (i == 0 || i == pair.second.trajectory.size() - 1) {
                tar_rviz.road_node.push_back(temp_referenceline_points);
            }
        }
    }


    cout << "生成tar_rviz.vec_point完毕" << endl;

    return true;
}


bool CConfigureIO::GetVehicleParam(_VehicleParam& vehicle_param) {
    char* buffer;
    int   length = 0;
    FILE* file;
    // 设置一个config文件，设置判断值，来选择车辆参数

    file = fopen("src/global_planning/config/vehicle_param.json", "rb+");

    if (!file) {
        cout << "车参数文件open failed " << endl;
        return false;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    buffer = new char[length + 1];
    fseek(file, 0, SEEK_SET);
    memset(buffer, 0, length + 1);
    fread(buffer, length, 1, file);

    _TarStartEnd        veh_start_end;
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
            if (val.HasMember("radious")) veh_start_end.veh_param.radious = val["radious"].GetDouble();
            if (val.HasMember("wheel_base")) veh_start_end.veh_param.wheel_base = val["wheel_base"].GetDouble();
            if (val.HasMember("max_steering")) veh_start_end.veh_param.max_steering = val["max_steering"].GetDouble() * M_PI / 180.0;
            if (val.HasMember("min_steering")) veh_start_end.veh_param.min_steering = val["min_steering"].GetDouble() * M_PI / 180.0;
            if (val.HasMember("safe_margin_bound")) {
                veh_start_end.veh_param.safe_margin_bound = val["safe_margin_bound"].GetDouble();
                cout << "veh_start_end. veh_param.safe_margin_bound :" << veh_start_end.veh_param.safe_margin_bound << endl;
            }

            if (val.HasMember("veh_center_2_side")) veh_start_end.veh_param.veh_center_2_side = val["veh_center_2_side"].GetDouble();
            if (val.HasMember("veh_center_2_front")) veh_start_end.veh_param.veh_center_2_front = val["veh_center_2_front"].GetDouble();
            if (val.HasMember("safe_margin_obstacle")) veh_start_end.veh_param.safe_margin_obstacle = val["safe_margin_obstacle"].GetDouble();
            if (val.HasMember("veh_center_2_rear_bound")) veh_start_end.veh_param.veh_center_2_rear_bound = val["veh_center_2_rear_bound"].GetDouble();
            if (val.HasMember("veh_center_2_rear_obstacle")) veh_start_end.veh_param.veh_center_2_rear_obstacle = val["veh_center_2_rear_obstacle"].GetDouble();
            // 算法参数
            if (val.HasMember("delta_s")) veh_start_end.veh_param.delta_s = val["delta_s"].GetDouble();
            if (val.HasMember("delta_dist")) veh_start_end.veh_param.delta_dist = val["delta_dist"].GetDouble();
            if (val.HasMember("grid_dist")) veh_start_end.veh_param.grid_dist = val["grid_dist"].GetDouble();
            if (val.HasMember("max_kappa")) veh_start_end.veh_param.max_kappa = val["max_kappa"].GetDouble();
            if (val.HasMember("error_term")) veh_start_end.veh_param.error_term = val["error_term"].GetDouble();
            if (val.HasMember("grid_angle")) veh_start_end.veh_param.grid_angle = val["grid_angle"].GetDouble() * M_PI / 180.0;
            if (val.HasMember("step_length")) veh_start_end.veh_param.step_length = val["step_length"].GetDouble();
            if (val.HasMember("curvature_term")) veh_start_end.veh_param.curvature_term = val["curvature_term"].GetDouble();
            if (val.HasMember("switch_penalty")) veh_start_end.veh_param.switch_penalty = val["switch_penalty"].GetDouble();
            if (val.HasMember("forward_penalty")) veh_start_end.veh_param.forward_penalty = val["forward_penalty"].GetDouble();
            if (val.HasMember("min_path_Length")) veh_start_end.veh_param.min_path_Length = val["min_path_Length"].GetDouble();
            if (val.HasMember("start_offset_distance")) veh_start_end.veh_param.start_offset_distance = val["start_offset_distance"].GetDouble();
            if (val.HasMember("end_offset_distance")) veh_start_end.veh_param.end_offset_distance = val["end_offset_distance"].GetDouble();
            if (val.HasMember("smoothness_term")) veh_start_end.veh_param.smoothness_term = val["smoothness_term"].GetDouble();
            if (val.HasMember("backward_penalty")) veh_start_end.veh_param.backward_penalty = val["backward_penalty"].GetDouble();
            if (val.HasMember("turnning_penalty")) veh_start_end.veh_param.turnning_penalty = val["turnning_penalty"].GetDouble();
            if (val.HasMember("angle_discrete_num")) veh_start_end.veh_param.angle_discrete_num = val["angle_discrete_num"].GetUint();
            if (val.HasMember("max_fitting_radius")) veh_start_end.veh_param.max_fitting_radius = val["max_fitting_radius"].GetDouble();
            if (val.HasMember("max_iterations_opti")) veh_start_end.veh_param.max_iterations_opti = val["max_iterations_opti"].GetDouble();

            if (val.HasMember("backward_search_range")) veh_start_end.veh_param.backward_search_range = val["backward_search_range"].GetDouble();
            if (val.HasMember("cusp_extension_distance")) veh_start_end.veh_param.cusp_extension_distance = val["cusp_extension_distance"].GetUint();
            if (val.HasMember("linear_preferred_distance_square")) veh_start_end.veh_param.linear_preferred_distance_square = val["linear_preferred_distance_square"].GetDouble();
            if (val.HasMember("min_speed_limit")) veh_start_end.veh_param.min_speed_limit = val["min_speed_limit"].GetFloat();
            if (val.HasMember("mid_speed_limit")) veh_start_end.veh_param.mid_speed_limit = val["mid_speed_limit"].GetFloat();
            if (val.HasMember("max_speed_limit")) veh_start_end.veh_param.max_speed_limit = val["max_speed_limit"].GetFloat();
            if (val.HasMember("min_curvature")) veh_start_end.veh_param.min_curvature = val["min_curvature"].GetFloat();
            if (val.HasMember("max_curvature")) veh_start_end.veh_param.max_curvature = val["max_curvature"].GetFloat();


            if (val.HasMember("lat_min_distance_struct")) veh_start_end.veh_param.lat_min_distance_struct = val["lat_min_distance_struct"].GetDouble();

            if (val.HasMember("safe_margin_error")) veh_start_end.veh_param.safe_margin_error = val["safe_margin_error"].GetDouble();

            if (val.HasMember("offset_enable")) veh_start_end.veh_param.offset_enable = val["offset_enable"].GetDouble();
            if (val.HasMember("multi_section_speed_limit_enable")) veh_start_end.veh_param.multi_section_speed_limit_enable = val["multi_section_speed_limit_enable"].GetDouble();
            if (val.HasMember("light_regular_road_speed_limit")) veh_start_end.veh_param.light_regular_road_speed_limit = val["light_regular_road_speed_limit"].GetDouble();
            if (val.HasMember("light_bumpy_road_speed_limit")) veh_start_end.veh_param.light_bumpy_road_speed_limit = val["light_bumpy_road_speed_limit"].GetDouble();
            if (val.HasMember("light_slope_road_speed_limit")) veh_start_end.veh_param.light_slope_road_speed_limit = val["light_slope_road_speed_limit"].GetDouble();
            if (val.HasMember("light_narrow_road_speed_limit")) veh_start_end.veh_param.light_narrow_road_speed_limit = val["light_narrow_road_speed_limit"].GetDouble();
            if (val.HasMember("light_intersection_road_speed_limit")) veh_start_end.veh_param.light_intersection_road_speed_limit = val["light_intersection_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_regular_road_speed_limit")) veh_start_end.veh_param.heavy_regular_road_speed_limit = val["heavy_regular_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_bumpy_road_speed_limit")) veh_start_end.veh_param.heavy_bumpy_road_speed_limit = val["heavy_bumpy_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_narrow_road_speed_limit")) veh_start_end.veh_param.heavy_narrow_road_speed_limit = val["heavy_narrow_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_intersection_road_speed_limit")) veh_start_end.veh_param.heavy_intersection_road_speed_limit = val["heavy_intersection_road_speed_limit"].GetDouble();
            if (val.HasMember("heavy_slope_road_speed_limit")) veh_start_end.veh_param.heavy_slope_road_speed_limit = val["heavy_slope_road_speed_limit"].GetDouble();
            if (val.HasMember("weather")) veh_start_end.veh_param.weather = val["weather"].GetDouble();
            if (val.HasMember("s_curve_speed_limit")) veh_start_end.veh_param.s_curve_speed_limit = val["s_curve_speed_limit"].GetUint();
            if (val.HasMember("task_type")) {
                cout << "task_type:" << val["task_type"].GetUint() << endl;
                veh_start_end.veh_param.task_type = val["task_type"].GetUint();
            }
            else
                cout << "NO task_type 参数" << endl;
            if (val.HasMember("reverse_speed")) {
                veh_start_end.veh_param.reverse_speed = val["reverse_speed"].GetDouble();
            }
            else {
                cout << "NO reverse_speed 参数" << endl;
            }
            if (val.HasMember("kMaxAcceleration")) veh_start_end.veh_param.kMaxAcceleration = val["kMaxAcceleration"].GetFloat();
            if (val.HasMember("kMinAcceleration")) veh_start_end.veh_param.kMinAcceleration = val["kMinAcceleration"].GetFloat();
            if (val.HasMember("kDeltaSpeed")) veh_start_end.veh_param.kDeltaSpeed = val["kDeltaSpeed"].GetFloat();
            if (val.HasMember("kErrorTerm")) veh_start_end.veh_param.kErrorTerm = val["kErrorTerm"].GetFloat();
            if (val.HasMember("kSmoothnessTerm")) veh_start_end.veh_param.kSmoothnessTerm = val["kSmoothnessTerm"].GetFloat();
            if (val.HasMember("kDiscreteNumber")) veh_start_end.veh_param.kDiscreteNumber = val["kDiscreteNumber"].GetFloat();
            if (val.HasMember("max_l")) veh_start_end.veh_param.max_l = val["max_l"].GetFloat();
            if (val.HasMember("sita")) veh_start_end.veh_param.sita = val["sita"].GetFloat();
            if (val.HasMember("base")) veh_start_end.veh_param.base = val["base"].GetFloat();
            if (val.HasMember("hybrid_h_use_rs")) veh_start_end.veh_param.hybrid_h_use_rs = val["hybrid_h_use_rs"].GetBool();
            if (val.HasMember("hybrid_h_use_a_star")) veh_start_end.veh_param.hybrid_h_use_a_star = val["hybrid_h_use_a_star"].GetBool();
            if (val.HasMember("hybrid_h_use_max")) veh_start_end.veh_param.hybrid_h_use_max = val["hybrid_h_use_max"].GetBool();
        }
        vehicle_param = veh_start_end.veh_param;
    }
    return true;
}