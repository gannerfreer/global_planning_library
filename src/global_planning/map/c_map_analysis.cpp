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
    cout << "解析border_points完毕,边界点数量：" << map_border_.size() << endl;

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
            tp.attribute = static_cast<PointAttribute>(trajPointsArray[j]["attribute"].GetInt());
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
        cout << "解析 m_Veh_Param 中" << endl;
        Value& val = doc["m_Veh_Param"];
        if (val.IsObject()) {
            // 车辆参数


            if (val.HasMember("radious")) {
                veh_start_end.veh_param.radious = val["radious"].GetDouble();
            }
            else {
                veh_start_end.veh_param.radious = 13;
                cout << "无法找到车参 radious ，即将赋予默认值" << endl;
            }

            if (val.HasMember("wheel_base")) {
                veh_start_end.veh_param.wheel_base = val["wheel_base"].GetDouble();
            }
            else {
                veh_start_end.veh_param.wheel_base = 6.91;
                cout << "无法找到车参 wheel_base ，即将赋予默认值" << endl;
            }

            if (val.HasMember("max_steering")) {
                veh_start_end.veh_param.max_steering = val["max_steering"].GetDouble() * M_PI / 180.0;
            }
            else {
                veh_start_end.veh_param.max_steering = 28;
                cout << "无法找到车参 max_steering ，即将赋予默认值" << endl;
            }

            if (val.HasMember("min_steering")) {
                veh_start_end.veh_param.min_steering = val["min_steering"].GetDouble() * M_PI / 180.0;
            }
            else {
                veh_start_end.veh_param.min_steering = -28;
                cout << "无法找到车参 min_steering ，即将赋予默认值" << endl;
            }

            if (val.HasMember("safe_margin_bound")) {
                veh_start_end.veh_param.safe_margin_bound = val["safe_margin_bound"].GetDouble();
            }
            else {
                veh_start_end.veh_param.safe_margin_bound = 0.5;
                cout << "无法找到车参 safe_margin_bound ，即将赋予默认值" << endl;
            }

            if (val.HasMember("veh_center_2_side")) {
                veh_start_end.veh_param.veh_center_2_side = val["veh_center_2_side"].GetDouble();
            }
            else {
                veh_start_end.veh_param.veh_center_2_side = 1.735;
                cout << "无法找到车参 veh_center_2_side ，即将赋予默认值" << endl;
            }

            if (val.HasMember("veh_center_2_front")) {
                veh_start_end.veh_param.veh_center_2_front = val["veh_center_2_front"].GetDouble();
            }
            else {
                veh_start_end.veh_param.veh_center_2_front = 7.3;
                cout << "无法找到车参 veh_center_2_front ，即将赋予默认值" << endl;
            }

            if (val.HasMember("safe_margin_obstacle")) {
                veh_start_end.veh_param.safe_margin_obstacle = val["safe_margin_obstacle"].GetDouble();
            }
            else {
                veh_start_end.veh_param.safe_margin_obstacle = 2.0;
                cout << "无法找到车参 safe_margin_obstacle ，即将赋予默认值" << endl;
            }

            if (val.HasMember("veh_center_2_rear_bound")) {
                veh_start_end.veh_param.veh_center_2_rear_bound = val["veh_center_2_rear_bound"].GetDouble();
            }
            else {
                veh_start_end.veh_param.veh_center_2_rear_bound = 0.5;
                cout << "无法找到车参 veh_center_2_rear_bound ，即将赋予默认值" << endl;
            }

            if (val.HasMember("veh_center_2_rear_obstacle")) {
                veh_start_end.veh_param.veh_center_2_rear_obstacle = val["veh_center_2_rear_obstacle"].GetDouble();
            }
            else {
                veh_start_end.veh_param.veh_center_2_rear_obstacle = 2.77;
                cout << "无法找到车参 veh_center_2_rear_obstacle ，即将赋予默认值" << endl;
            }

            if (val.HasMember("delta_dist")) {
                veh_start_end.veh_param.delta_dist = val["delta_dist"].GetDouble();
            }
            else {
                veh_start_end.veh_param.delta_dist = 2.0;
                cout << "无法找到车参 delta_dist ，即将赋予默认值" << endl;
            }

            if (val.HasMember("grid_dist")) {
                veh_start_end.veh_param.grid_dist = val["grid_dist"].GetDouble();
            }
            else {
                veh_start_end.veh_param.grid_dist = 1.0;
                cout << "无法找到车参 grid_dist ，即将赋予默认值" << endl;
            }

            if (val.HasMember("max_kappa")) {
                veh_start_end.veh_param.max_kappa = val["max_kappa"].GetDouble();
            }
            else {
                veh_start_end.veh_param.max_kappa = 0.07;
                cout << "无法找到车参 max_kappa ，即将赋予默认值" << endl;
            }

            if (val.HasMember("path_error_term")) {
                veh_start_end.veh_param.path_error_term = val["path_error_term"].GetDouble();
            }
            else {
                veh_start_end.veh_param.path_error_term = 0.0;
                cout << "无法找到车参 path_error_term ，即将赋予默认值" << endl;
            }

            if (val.HasMember("grid_angle")) {
                veh_start_end.veh_param.grid_angle = val["grid_angle"].GetDouble() * M_PI / 180.0;
            }
            else {
                veh_start_end.veh_param.grid_angle = 1.0;
                cout << "无法找到车参 grid_angle ，即将赋予默认值" << endl;
            }
            if (val.HasMember("hybridastar_step_length")) {
                veh_start_end.veh_param.hybridastar_step_length = val["hybridastar_step_length"].GetDouble();
            }
            else {
                veh_start_end.veh_param.hybridastar_step_length = 1.0;
                cout << "无法找到车参 hybridastar_step_length ，即将赋予默认值" << endl;
            }

            if (val.HasMember("path_curvature_term")) {
                veh_start_end.veh_param.path_curvature_term = val["path_curvature_term"].GetDouble();
            }
            else {
                veh_start_end.veh_param.path_curvature_term = 0.0;
                cout << "无法找到车参 path_curvature_term ，即将赋予默认值" << endl;
            }

            if (val.HasMember("switch_penalty")) {
                veh_start_end.veh_param.switch_penalty = val["switch_penalty"].GetDouble();
            }
            else {
                veh_start_end.veh_param.switch_penalty = 10;
                cout << "无法找到车参 switch_penalty ，即将赋予默认值" << endl;
            }
            if (val.HasMember("forward_penalty")) {
                veh_start_end.veh_param.forward_penalty = val["forward_penalty"].GetDouble();
            }
            else {
                veh_start_end.veh_param.forward_penalty = 1.0;
                cout << "无法找到车参 forward_penalty ，即将赋予默认值" << endl;
            }

            if (val.HasMember("path_smoothness_term")) {
                veh_start_end.veh_param.path_smoothness_term = val["path_smoothness_term"].GetDouble();
            }
            else {
                veh_start_end.veh_param.path_smoothness_term = 0.1;
                cout << "无法找到车参 path_smoothness_term ，即将赋予默认值" << endl;
            }
            if (val.HasMember("backward_penalty")) {
                veh_start_end.veh_param.backward_penalty = val["backward_penalty"].GetDouble();
            }
            else {
                veh_start_end.veh_param.backward_penalty = 5.5;
                cout << "无法找到车参 backward_penalty ，即将赋予默认值" << endl;
            }

            if (val.HasMember("turnning_penalty")) {
                veh_start_end.veh_param.turnning_penalty = val["turnning_penalty"].GetDouble();
            }
            else {
                veh_start_end.veh_param.turnning_penalty = 2.468;
                cout << "无法找到车参 turnning_penalty ，即将赋予默认值" << endl;
            }

            if (val.HasMember("angle_discrete_num")) {
                veh_start_end.veh_param.angle_discrete_num = val["angle_discrete_num"].GetUint();
            }
            else {
                veh_start_end.veh_param.angle_discrete_num = 3;
                cout << "无法找到车参 angle_discrete_num ，即将赋予默认值" << endl;
            }
            cout << "390" << endl;
            if (val.HasMember("max_fitting_radius")) {
                veh_start_end.veh_param.max_fitting_radius = val["max_fitting_radius"].GetDouble();
            }
            else {
                veh_start_end.veh_param.max_fitting_radius = 100;
                cout << "无法找到车参 max_fitting_radius ，即将赋予默认值" << endl;
            }

            if (val.HasMember("max_iterations_opti")) {
                veh_start_end.veh_param.max_iterations_opti = val["max_iterations_opti"].GetDouble();
            }
            else {
                veh_start_end.veh_param.max_iterations_opti = 100;
                cout << "无法找到车参 max_iterations_opti ，即将赋予默认值" << endl;
            }


            if (val.HasMember("cusp_extension_distance")) {
                veh_start_end.veh_param.cusp_extension_distance = val["cusp_extension_distance"].GetFloat();
            }
            else {
                veh_start_end.veh_param.cusp_extension_distance = 3.0;
                cout << "无法找到车参 cusp_extension_distance ，即将赋予默认值" << endl;
            }

            if (val.HasMember("linear_preferred_distance")) {
                veh_start_end.veh_param.linear_preferred_distance = val["linear_preferred_distance"].GetDouble();
            }
            else {
                veh_start_end.veh_param.linear_preferred_distance = 3.0;
                cout << "无法找到车参 linear_preferred_distance ，即将赋予默认值" << endl;
            }
            cout << "line431" << endl;
            if (val.HasMember("safe_margin_error")) {
                veh_start_end.veh_param.safe_margin_error = val["safe_margin_error"].GetDouble();
            }
            else {
                veh_start_end.veh_param.safe_margin_error = 0.0;
                cout << "无法找到车参 safe_margin_error ，即将赋予默认值" << endl;
            }

            if (val.HasMember("speed_error_term")) {
                veh_start_end.veh_param.speed_error_term = val["speed_error_term"].GetFloat();
            }
            else {
                veh_start_end.veh_param.speed_error_term = 0.1;
                cout << "无法找到车参 speed_error_term ，即将赋予默认值" << endl;
            }

            if (val.HasMember("speed_smooth_term")) {
                veh_start_end.veh_param.speed_smooth_term = val["speed_smooth_term"].GetFloat();
            }
            else {
                veh_start_end.veh_param.speed_smooth_term = 0.01;
                cout << "无法找到车参 speed_smooth_term ，即将赋予默认值" << endl;
            }

            if (val.HasMember("max_acceleration")) {
                veh_start_end.veh_param.max_acceleration = val["max_acceleration"].GetFloat();
            }
            else {
                veh_start_end.veh_param.max_acceleration = 0.3;
                cout << "无法找到车参 max_acceleration ，即将赋予默认值" << endl;
            }

            if (val.HasMember("min_acceleration")) {
                veh_start_end.veh_param.min_acceleration = val["min_acceleration"].GetFloat();
            }
            else {
                veh_start_end.veh_param.min_acceleration = -0.4;
                cout << "无法找到车参 min_acceleration ，即将赋予默认值" << endl;
            }

            if (val.HasMember("reverse_speed")) {
                veh_start_end.veh_param.reverse_speed = val["reverse_speed"].GetFloat();
            }
            else {
                veh_start_end.veh_param.reverse_speed = 1.0;
                cout << "无法找到车参 reverse_speed ，即将赋予默认值" << endl;
            }

            if (val.HasMember("narrow_road_speed_limit")) {
                veh_start_end.veh_param.narrow_road_speed_limit = val["narrow_road_speed_limit"].GetFloat();
            }
            else {
                cout << "无法找到车参 narrow_road_speed_limit ，即将赋予默认值" << endl;
                veh_start_end.veh_param.narrow_road_speed_limit = 3;
            }

            if (val.HasMember("slope_road_speed_limit")) {
                veh_start_end.veh_param.slope_road_speed_limit = val["slope_road_speed_limit"].GetFloat();
            }
            else {
                cout << "无法找到 slope_road_speed_limit" << endl;
                veh_start_end.veh_param.slope_road_speed_limit = 3.0;
            }

            if (val.HasMember("intersection_road_speed_limit")) {
                veh_start_end.veh_param.intersection_road_speed_limit = val["intersection_road_speed_limit"].GetFloat();
            }
            else {
                cout << "无法找到 intersection_road_speed_limit" << endl;
                veh_start_end.veh_param.intersection_road_speed_limit = 3.0;
            }

            if (val.HasMember("bumpy_road_speed_limit")) {
                veh_start_end.veh_param.bumpy_road_speed_limit = val["bumpy_road_speed_limit"].GetFloat();
            }
            else {
                cout << "无法找到 bumpy_road_speed_limit" << endl;
                veh_start_end.veh_param.bumpy_road_speed_limit = 3.0;
            }

            if (val.HasMember("regular_road_speed_limit")) {
                veh_start_end.veh_param.regular_road_speed_limit = val["regular_road_speed_limit"].GetFloat();
            }
            else {
                cout << "无法找到 regular_road_speed_limit" << endl;
                veh_start_end.veh_param.regular_road_speed_limit = 3.0;
            }
            cout << "line528" << endl;
            if (val.HasMember("vehicle_code")) {
                veh_start_end.veh_param.vehicle_code = val["vehicle_code"].GetUint();
            }
            else {
                cout << "无法找到 vehicle_code" << endl;
                veh_start_end.veh_param.vehicle_code = 9999;
            }

            if (val.HasMember("uniform_compaction_enable")) {
                veh_start_end.veh_param.uniform_compaction_enable = val["uniform_compaction_enable"].GetBool();
            }
            else {
                cout << "无法找到 uniform_compaction_enable" << endl;
                veh_start_end.veh_param.uniform_compaction_enable = true;
            }


            if (val.HasMember("is_light")) {
                veh_start_end.veh_param.is_light = val["is_light"].GetBool();
            }
            else {
                cout << "无法找到车参 is_light ，即将赋予默认值" << endl;
                veh_start_end.veh_param.is_light = false;
            }

            if (val.HasMember("path_voronoi_term")) {
                veh_start_end.veh_param.path_voronoi_term = val["path_voronoi_term"].GetFloat();
            }
            else {
                cout << "无法找到车参 path_voronoi_term ，即将赋予默认值" << endl;
                veh_start_end.veh_param.path_voronoi_term = 0.1;
            }

            if (val.HasMember("vonoroi_grid_dist")) {
                veh_start_end.veh_param.vonoroi_grid_dist = val["vonoroi_grid_dist"].GetFloat();
            }
            else {
                cout << "无法找到车参 vonoroi_grid_dist ，即将赋予默认值" << endl;
                veh_start_end.veh_param.vonoroi_grid_dist = 0.1;
            }

            if (val.HasMember("curvature_threshold")) {
                veh_start_end.veh_param.curvature_threshold = val["curvature_threshold"].GetFloat();
            }
            else {
                cout << "无法找到车参 curvature_threshold ，即将赋予默认值" << endl;
                veh_start_end.veh_param.curvature_threshold = 0.1;
            }

            if (val.HasMember("task_type")) {
                veh_start_end.veh_param.task_type = val["task_type"].GetUint();
            }
            else {
                cout << "无法找到车参 task_type ，即将赋予默认值" << endl;
                veh_start_end.veh_param.task_type = 2;
            }

            if (val.HasMember("speed_limit_level")) {
                veh_start_end.veh_param.speed_limit_level = static_cast<SpeedLimitLevel>(val["speed_limit_level"].GetUint());
            }
            else {
                cout << "无法找到车参 speed_limit_level ，即将赋予默认值" << endl;
                veh_start_end.veh_param.speed_limit_level = SpeedLimitLevel::three;
            }

            if (val.HasMember("load_point_end_offset_distance")) {
                veh_start_end.veh_param.load_point_end_offset_distance = val["load_point_end_offset_distance"].GetUint();
            }
            else {
                cout << "无法找到车参 load_point_end_offset_distance ，即将赋予默认值" << endl;
                veh_start_end.veh_param.load_point_end_offset_distance = 8;
            }

            if (val.HasMember("load_point_start_offset_distance") && val["load_point_start_offset_distance"].IsNumber()) {
                veh_start_end.veh_param.load_point_start_offset_distance = val["load_point_start_offset_distance"].GetUint();
            }
            else {
                cout << "无法找到车参 load_point_start_offset_distance ，即将赋予默认值" << endl;
                veh_start_end.veh_param.load_point_start_offset_distance = 3;
            }


            if (val.HasMember("obsMax") && val["obsMax"].IsNumber()) {
                veh_start_end.veh_param.obsMax = val["obsMax"].GetFloat();
            }
            else {
                cout << "无法找到车参 obsMax ，即将赋予默认值" << endl;
                veh_start_end.veh_param.obsMax = 2.5;
            }

            if (val.HasMember("rs_min_length") && val["rs_min_length"].IsNumber()) {
                veh_start_end.veh_param.rs_min_length = val["rs_min_length"].GetFloat();
            }
            else {
                cout << "无法找到车参 rs_min_length ，即将赋予默认值" << endl;
                veh_start_end.veh_param.rs_min_length = 2;
            }

            if (val.HasMember("load_start_straight_length") && val["load_start_straight_length"].IsNumber()) {
                veh_start_end.veh_param.load_start_straight_length = val["load_start_straight_length"].GetFloat();
            }
            else {
                cout << "无法找到车参 load_start_straight_length ，即将赋予默认值" << endl;
                veh_start_end.veh_param.load_start_straight_length = 1;
            }

            if (val.HasMember("offset_distance") && val["offset_distance"].IsNumber()) {
                veh_start_end.veh_param.offset_distance = val["offset_distance"].GetFloat();
                veh_start_end.veh_param.offset_distance = std::min(std::max(veh_start_end.veh_param.offset_distance, float(0)), float(0.5));
            }
            else {
                cout << "无法找到车参 offset_distance ，即将赋予默认值" << endl;
                veh_start_end.veh_param.offset_distance = 0.3;
            }

            if (val.HasMember("max_steering_wheel_speed") && val["max_steering_wheel_speed"].IsNumber()) {
                veh_start_end.veh_param.max_steering_wheel_speed = val["max_steering_wheel_speed"].GetFloat();
            }
            else {
                cout << "无法找到车参 max_steering_wheel_speed ，即将赋予默认值" << endl;
                veh_start_end.veh_param.max_steering_wheel_speed = 0.1396;
            }
        }
    }
    vehicle_param = veh_start_end.veh_param;
    return true;
}