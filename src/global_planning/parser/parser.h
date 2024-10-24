/***************************************************/
/*            Author: cxp                          */
/*            Contact: chenxinpeng_hnu@163.com     */
/*            Last update: 2021-07-27              */
/***************************************************/
/*
Description: This is a collection of helper functions that are used throughout the project.
*/
#ifndef HELPER_H
#define HELPER_H
#include "../common/common_struct.h"
#include "../globalvariable.h"
#include "../mine_global_planning/planning.h"

namespace GlobalPlanning {

namespace Parser {
using namespace rapidjson;

_TarStartEnd ParseJson(char* str) {
    _TarStartEnd        veh_start_end;
    rapidjson::Document doc;
    doc.Parse(str);
    if (doc.HasParseError()) {
        cout << "parse失败......" << endl;
    }
    doc.GetAllocator();
    // 任务类型
    if (doc.HasMember("task_type")) {
        cout << "解析 task_type 中" << endl;
        veh_start_end.task_type = static_cast<TaskType>(doc["task_type"].GetUint());
        cout << "veh_start_end.m_task_type = " << static_cast<int>(veh_start_end.task_type) << endl;
    }


    // 起始点
    if (doc.HasMember("m_Start_Point")) {
        cout << "解析 m_Start_Point 中" << endl;
        Value& val = doc["m_Start_Point"];
        if (val.IsObject()) {
            if (val.HasMember("x")) veh_start_end.start_point.x = val["x"].GetDouble();
            if (val.HasMember("y")) veh_start_end.start_point.y = val["y"].GetDouble();
            if (val.HasMember("z")) veh_start_end.start_point.z = val["z"].GetFloat();
            if (val.HasMember("yaw")) veh_start_end.start_point.yaw = val["yaw"].GetFloat();
        }
    }

    // 目标点
    if (doc.HasMember("m_End_Point")) {
        cout << "解析 m_End_Point 中" << endl;
        Value& val = doc["m_End_Point"];
        if (val.IsObject()) {
            if (val.HasMember("x")) veh_start_end.end_point.x = val["x"].GetDouble();
            if (val.HasMember("y")) veh_start_end.end_point.y = val["y"].GetDouble();
            if (val.HasMember("z")) veh_start_end.end_point.z = val["z"].GetFloat();
            if (val.HasMember("yaw")) veh_start_end.end_point.yaw = val["yaw"].GetFloat();
        }
    }

    if (doc.HasMember("m_Veh_Param")) {
        cout << "解析 m_Veh_Param 中" << endl;
        Value& val = doc["m_Veh_Param"];
        if (val.IsObject()) {
            // 车辆参数
            if (val.HasMember("radious")) {
                veh_start_end.veh_param.radious = val["radious"].GetDouble();
            }

            if (val.HasMember("wheel_base")) veh_start_end.veh_param.wheel_base = val["wheel_base"].GetDouble();

            if (val.HasMember("max_steering")) veh_start_end.veh_param.max_steering = val["max_steering"].GetDouble() * M_PI / 180.0;
            if (val.HasMember("min_steering")) veh_start_end.veh_param.min_steering = val["min_steering"].GetDouble() * M_PI / 180.0;
            if (val.HasMember("safe_margin_bound")) {
                veh_start_end.veh_param.safe_margin_bound = val["safe_margin_bound"].GetDouble();
                cout << "veh_start_end.veh_param.safe_margin_bound:" << veh_start_end.veh_param.safe_margin_bound << endl;
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
            if (val.HasMember("end_offset_distance")) veh_start_end.veh_param.end_offset_distance = val["end_offset_distance"].GetDouble();
            if (val.HasMember("smoothness_term")) veh_start_end.veh_param.smoothness_term = val["smoothness_term"].GetDouble();
            if (val.HasMember("backward_penalty")) veh_start_end.veh_param.backward_penalty = val["backward_penalty"].GetDouble();
            if (val.HasMember("turnning_penalty")) veh_start_end.veh_param.turnning_penalty = val["turnning_penalty"].GetDouble();
            if (val.HasMember("angle_discrete_num")) veh_start_end.veh_param.angle_discrete_num = val["angle_discrete_num"].GetUint();
            if (val.HasMember("max_fitting_radius")) veh_start_end.veh_param.max_fitting_radius = val["max_fitting_radius"].GetDouble();
            if (val.HasMember("max_iterations_opti")) veh_start_end.veh_param.max_iterations_opti = val["max_iterations_opti"].GetDouble();

            if (val.HasMember("backward_search_range")) veh_start_end.veh_param.backward_search_range = val["backward_search_range"].GetDouble();
            if (val.HasMember("cusp_extension_distance")) veh_start_end.veh_param.cusp_extension_distance = val["cusp_extension_distance"].GetFloat();
            if (val.HasMember("linear_preferred_distance_square")) veh_start_end.veh_param.linear_preferred_distance_square = val["linear_preferred_distance_square"].GetDouble();
            if (val.HasMember("min_speed_limit")) veh_start_end.veh_param.min_speed_limit = val["min_speed_limit"].GetFloat();
            if (val.HasMember("mid_speed_limit")) veh_start_end.veh_param.mid_speed_limit = val["mid_speed_limit"].GetFloat();
            if (val.HasMember("max_speed_limit")) veh_start_end.veh_param.max_speed_limit = val["max_speed_limit"].GetFloat();
            if (val.HasMember("min_curvature")) veh_start_end.veh_param.min_curvature = val["min_curvature"].GetFloat();
            if (val.HasMember("max_curvature")) veh_start_end.veh_param.max_curvature = val["max_curvature"].GetFloat();


            if (val.HasMember("lat_min_distance_struct")) veh_start_end.veh_param.lat_min_distance_struct = val["lat_min_distance_struct"].GetDouble();

            if (val.HasMember("safe_margin_error")) veh_start_end.veh_param.safe_margin_error = val["safe_margin_error"].GetDouble();
            if (val.HasMember("kErrorTerm")) veh_start_end.veh_param.kErrorTerm = val["kErrorTerm"].GetFloat();
            if (val.HasMember("kDeltaSpeed")) veh_start_end.veh_param.kDeltaSpeed = val["kDeltaSpeed"].GetFloat();
            if (val.HasMember("kDiscreteNumber")) veh_start_end.veh_param.kDiscreteNumber = val["kDiscreteNumber"].GetFloat();
            if (val.HasMember("kSmoothnessTerm")) veh_start_end.veh_param.kSmoothnessTerm = val["kSmoothnessTerm"].GetFloat();
            if (val.HasMember("kMaxAcceleration")) veh_start_end.veh_param.kMaxAcceleration = val["kMaxAcceleration"].GetFloat();
            if (val.HasMember("kMinAcceleration")) veh_start_end.veh_param.kMinAcceleration = val["kMinAcceleration"].GetFloat();
            if (val.HasMember("reverse_speed")) veh_start_end.veh_param.reverse_speed = val["reverse_speed"].GetFloat();
            if (val.HasMember("border_change_range")) veh_start_end.veh_param.border_change_range = val["border_change_range"].GetFloat();
            if (val.HasMember("border_sample_inter")) veh_start_end.veh_param.border_sample_inter = val["border_sample_inter"].GetUint();

            if (val.HasMember("light_narrow_road_speed_limit"))
                veh_start_end.veh_param.light_narrow_road_speed_limit = val["light_narrow_road_speed_limit"].GetFloat();
            else {
                cout << "无法找到 light_narrow_road_speed_limit" << endl;
                veh_start_end.veh_param.light_narrow_road_speed_limit = 1.0;
            }

            if (val.HasMember("light_slope_road_speed_limit"))
                veh_start_end.veh_param.light_slope_road_speed_limit = val["light_slope_road_speed_limit"].GetFloat();
            else {
                cout << "无法找到 light_slope_road_speed_limit" << endl;
                veh_start_end.veh_param.light_slope_road_speed_limit = 1.0;
            }

            if (val.HasMember("light_intersection_road_speed_limit"))
                veh_start_end.veh_param.light_intersection_road_speed_limit = val["light_intersection_road_speed_limit"].GetFloat();
            else {
                cout << "无法找到 light_intersection_road_speed_limit" << endl;
                veh_start_end.veh_param.light_intersection_road_speed_limit = 1.0;
            }

            if (val.HasMember("light_bumpy_road_speed_limit"))
                veh_start_end.veh_param.light_bumpy_road_speed_limit = val["light_bumpy_road_speed_limit"].GetFloat();
            else {
                cout << "无法找到 light_bumpy_road_speed_limit" << endl;
                veh_start_end.veh_param.light_bumpy_road_speed_limit = 1.0;
            }

            if (val.HasMember("light_regular_road_speed_limit"))
                veh_start_end.veh_param.light_regular_road_speed_limit = val["light_regular_road_speed_limit"].GetFloat();
            else {
                cout << "无法找到 light_regular_road_speed_limit" << endl;
                veh_start_end.veh_param.light_regular_road_speed_limit = 1.0;
            }

            if (val.HasMember("heavy_narrow_road_speed_limit"))
                veh_start_end.veh_param.heavy_narrow_road_speed_limit = val["heavy_narrow_road_speed_limit"].GetFloat();
            else {
                cout << "无法找到 heavy_narrow_road_speed_limit" << endl;
                veh_start_end.veh_param.heavy_narrow_road_speed_limit = 1.0;
            }

            if (val.HasMember("heavy_slope_road_speed_limit")) {
                veh_start_end.veh_param.heavy_slope_road_speed_limit = val["heavy_slope_road_speed_limit"].GetFloat();
                cout << "find heavy_slope_road_speed_limit " << veh_start_end.veh_param.heavy_slope_road_speed_limit << endl;
            }
            else {
                cout << "无法找到 heavy_slope_road_speed_limit" << endl;
                veh_start_end.veh_param.heavy_slope_road_speed_limit = 1.0;
            }

            if (val.HasMember("heavy_intersection_road_speed_limit"))
                veh_start_end.veh_param.heavy_intersection_road_speed_limit = val["heavy_intersection_road_speed_limit"].GetFloat();
            else {
                cout << "无法找到 heavy_intersection_road_speed_limit" << endl;
                veh_start_end.veh_param.heavy_intersection_road_speed_limit = 1.0;
            }

            if (val.HasMember("heavy_bumpy_road_speed_limit"))
                veh_start_end.veh_param.heavy_bumpy_road_speed_limit = val["heavy_bumpy_road_speed_limit"].GetFloat();
            else {
                cout << "无法找到 heavy_bumpy_road_speed_limit" << endl;
                veh_start_end.veh_param.heavy_bumpy_road_speed_limit = 1.0;
            }

            if (val.HasMember("heavy_regular_road_speed_limit"))
                veh_start_end.veh_param.heavy_regular_road_speed_limit = val["heavy_regular_road_speed_limit"].GetFloat();
            else {
                cout << "无法找到 heavy_regular_road_speed_limit" << endl;
                veh_start_end.veh_param.heavy_regular_road_speed_limit = 1.0;
            }

            if (val.HasMember("vehicle_code"))
                veh_start_end.veh_param.vehicle_code = val["vehicle_code"].GetUint();
            else {
                cout << "无法找到 vehicle_code" << endl;
                veh_start_end.veh_param.vehicle_code = 9999;
            }

            if (val.HasMember("offset_enable"))
                veh_start_end.veh_param.offset_enable = val["offset_enable"].GetUint();
            else {
                cout << "无法找到 offset_enable" << endl;
                veh_start_end.veh_param.offset_enable = 0;
            }

            if (val.HasMember("multi_section_speed_limit_enable"))
                veh_start_end.veh_param.multi_section_speed_limit_enable = val["multi_section_speed_limit_enable"].GetUint();
            else {
                cout << "无法找到 multi_section_speed_limit_enable" << endl;
                veh_start_end.veh_param.multi_section_speed_limit_enable = 0;
            }

            if (val.HasMember("s_curve_speed_limit"))
                veh_start_end.veh_param.s_curve_speed_limit = val["s_curve_speed_limit"].GetUint();
            else {
                cout << "无法找到 s_curve_speed_limit" << endl;
                veh_start_end.veh_param.s_curve_speed_limit = 0;
            }
            if (val.HasMember("weather"))
                veh_start_end.veh_param.weather = val["weather"].GetUint();
            else {
                cout << "无法找到 weather" << endl;
                veh_start_end.veh_param.weather = 1;
            }
            if (val.HasMember("start_offset_distance"))
                veh_start_end.veh_param.start_offset_distance = val["start_offset_distance"].GetFloat();
            else {
                cout << "无法找到 start_offset_distance" << endl;
                veh_start_end.veh_param.start_offset_distance = 4.0;
            }
            if (val.HasMember("end_offset_distance"))
                veh_start_end.veh_param.end_offset_distance = val["end_offset_distance"].GetFloat();
            else {
                cout << "无法找到 end_offset_distance" << endl;
                veh_start_end.veh_param.end_offset_distance = 2.0;
            }
            if (val.HasMember("max_l")) {
                veh_start_end.veh_param.max_l = val["max_l"].GetFloat();
                if (fabs(veh_start_end.veh_param.max_l) > 0.5) {
                    veh_start_end.veh_param.max_l = 0.5;
                }
            }
            else {
                cout << "无法找到 max_l" << endl;
                veh_start_end.veh_param.max_l = 0.2;
            }
            if (val.HasMember("is_light")) {
                veh_start_end.veh_param.is_light = val["is_light"].GetBool();
            }
            if (val.HasMember("hybrid_h_use_rs")) veh_start_end.veh_param.hybrid_h_use_rs = val["hybrid_h_use_rs"].GetBool();
            if (val.HasMember("hybrid_h_use_a_star")) veh_start_end.veh_param.hybrid_h_use_a_star = val["hybrid_h_use_a_star"].GetBool();
            if (val.HasMember("hybrid_h_use_max")) veh_start_end.veh_param.hybrid_h_use_max = val["hybrid_h_use_max"].GetBool();

            if (val.HasMember("kVoronoiTerm")) veh_start_end.veh_param.kVoronoiTerm = val["kVoronoiTerm"].GetFloat();
            if (val.HasMember("vonoroi_grid_dist"))
                veh_start_end.veh_param.vonoroi_grid_dist = val["vonoroi_grid_dist"].GetFloat();
            else
                veh_start_end.veh_param.vonoroi_grid_dist = 0.1;
        }
    }


    if (doc.HasMember("Inner_Borders")) {
        cout << "解析 Inner_Borders 中" << endl;
        Value& val = doc["Inner_Borders"];
        for (size_t i = 0; i < val.Size(); i++) {
            Value&               temp_val = val[i];
            vector<_BorderPoint> inner_border;

            if (temp_val.HasMember("inner_borders")) {
                Value& temp_value = temp_val["inner_borders"];
                for (size_t j = 0; j < temp_value.Size(); j++) {
                    Value& temp_vall = temp_value[j];

                    if (temp_vall.HasMember("border_points")) {
                        Value&       temp_val_1 = temp_vall["border_points"];
                        _BorderPoint temp_point;

                        for (size_t j = 0; j < temp_val_1.Size(); j++) {
                            Value& temp_val_2 = temp_val_1[j];
                            temp_point.x      = temp_val_2["x"].GetDouble();
                            temp_point.y      = temp_val_2["y"].GetDouble();
                            temp_point.z      = temp_val_2["z"].GetFloat();
                            temp_point.type   = temp_val_2["type"].GetUint();
                            inner_border.push_back(temp_point);
                        }
                    }
                }
            }
            veh_start_end.inner_borders.emplace_back(inner_border);
        }
    }
    if (doc.HasMember("key")) {
        cout << "解析 key 中" << endl;
        veh_start_end.my_key = doc["key"].GetString();
    }
    return veh_start_end;
}

// 将路点信息转换为json格式 返回给调用方
string VecWaypoint2json(vector<_TrajectoryPoint>& vec_wp, Planning& plan_obj) {
    cout << "enter VecWaypoint2json" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "VecWaypoint2json..." << endl;

    if (plan_obj.error_type_ != ErrorType::SUCCESS) {
        cout << "即将返回特殊轨迹给后台" << endl;
        vec_wp.clear();
    }

    time_t start_time, end_time;
    time(&start_time);
    rapidjson::StringBuffer                    strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);

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

    writer.Key("vec_path");
    writer.StartArray();
    if (plan_obj.road_sequence_.size() == 0) {
        writer.Uint(plan_obj.sequence_mapping_.at(plan_obj.start_key_));
    }
    else {
        for (size_t j = 0; j < plan_obj.road_sequence_.size(); j++) {
            writer.Uint(plan_obj.sequence_mapping_.at(plan_obj.road_sequence_.at(j)));
        }
    }

    writer.EndArray();

    writer.Key("error_type");
    writer.Uint(static_cast<unsigned char>(plan_obj.error_type_));
    // writer.Key("ID");
    // writer.String(vehicle_code_.c_str(), vehicle_code_.size());

    writer.EndObject();

    cout << "writer.EndObject()" << endl;

    GlobalVariable::getInstance()->SetGlobalStr(strbuf.GetString());
    auto         currentTime = chrono::system_clock::now();
    time_t       timestamp   = chrono::system_clock::to_time_t(currentTime);
    stringstream ss;
    ss << put_time(localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
    string timeStr = ss.str();

    // 构造文件路径
    string filePath = timeStr + "_" + plan_obj.vehicle_code_ + "_output.json";

    ofstream outputFile(filePath);
    // 将JSON数据写入文件
    outputFile << GlobalVariable::getInstance()->GetGlobalStr();
    // 关闭文件流
    outputFile.close();


    cout << "规划库成功返回轨迹，欢迎下次光临" << endl;
    time(&end_time);

    {
        unique_lock<shared_mutex> lock(GlobalVariable::getInstance()->record_file_write_lock);
        ofstream                  record;
        record.open("GlobalPlanning_record.txt", ios_base::app);
        record << timeStr << " ，处理完规划请求，请求号：" << plan_obj.key_ << "，车辆编号：" << plan_obj.vehicle_code_ << "规划库版本号:G_V1.0.1.20241024_RC" << endl;
        record.close();
    }

    return GlobalVariable::getInstance()->GetGlobalStr();
}

bool GetMap(char* parea) {
    rapidjson::Document doc;
    doc.Parse(parea);
    if (doc.HasParseError()) {
        doc.GetParseError();
        doc.GetErrorOffset();
    }
    doc.GetAllocator();


    // 解析border_points
    const Value&         borderPointsArray = doc["external_border"];
    _BorderPoint         bp;
    vector<_BorderPoint> v_bp;
    for (SizeType i = 0; i < borderPointsArray.Size(); i++) {
        bp.x    = borderPointsArray[i]["x"].GetDouble();
        bp.y    = borderPointsArray[i]["y"].GetDouble();
        bp.z    = borderPointsArray[i]["z"].GetDouble();
        bp.type = static_cast<unsigned char>(borderPointsArray[i]["type"].GetInt());
        if (bp.type == 0) {
            v_bp.emplace_back(bp);
        }
    }
    GlobalVariable::getInstance()->SetMapBorder(v_bp);

    // 解析reference_trajs
    const Value&          trajsArray = doc["reference_trajs"];
    map<int, _SingleTraj> m_traj;
    _SingleTraj           traj;
    _TrajectoryPoint      tp;
    for (SizeType i = 0; i < trajsArray.Size(); i++) {
        traj.trajectory.clear();
        traj.id                      = trajsArray[i]["id"].GetInt();
        const Value& trajPointsArray = trajsArray[i]["trajectory"];
        for (SizeType j = 0; j < trajPointsArray.Size(); j++) {
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
    GlobalVariable::getInstance()->SetAllReferencelines(m_traj);


    // 解析relation
    const Value&          relationObj = doc["relation"];
    map<int, vector<int>> m_relation;
    int                   key;
    vector<int>           relVec;
    for (Value::ConstMemberIterator itr = relationObj.MemberBegin(); itr != relationObj.MemberEnd(); ++itr) {
        key                   = stoi(itr->name.GetString());
        const Value& relArray = itr->value;
        relVec.clear();
        for (SizeType k = 0; k < relArray.Size(); k++) {
            relVec.push_back(relArray[k].GetInt());
        }
        m_relation[key] = relVec;
    }
    GlobalVariable::getInstance()->SetReferencelineRelation(m_relation);
    GlobalVariable::getInstance()->CreateSequenceMapping(GlobalVariable::getInstance()->GetAllReferencelines());

    // 调用GlobalVariable类内部的CreateDirectedGraph来生成referenceline_graph_
    GlobalVariable::getInstance()->CreateDirectedGraph(GlobalVariable::getInstance()->GetReferencelineRelation());

    return true;
}


} // namespace Parser
} // namespace GlobalPlanning

#endif // HELPER_H
