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
#include <filesystem>

#include "../common/common_struct.h"
#include "../globalvariable.h"
#include "../mine_global_planning/planning.h"
#include "../mine_global_planning/predicting.h"
namespace fs = std::filesystem;
namespace GlobalPlanning {

namespace Parser {
using namespace rapidjson;

_TarStartEnd ParseGlobalPlanningJson(char* str) {
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
            if (val.HasMember("radious") && val["radious"].IsNumber()) {
                veh_start_end.veh_param.radious = val["radious"].GetDouble();
                cout << "veh_start_end.veh_param.radious " << veh_start_end.veh_param.radious << endl;
            }
            else {
                veh_start_end.veh_param.radious = 13;
                cout << "无法找到车参 radious ，即将赋予默认值" << endl;
            }

            if (val.HasMember("wheel_base") && val["wheel_base"].IsNumber()) {
                veh_start_end.veh_param.wheel_base = val["wheel_base"].GetDouble();
                cout << "veh_start_end.veh_param.wheel_base " << veh_start_end.veh_param.wheel_base << endl;
            }
            else {
                veh_start_end.veh_param.wheel_base = 6.91;
                cout << "无法找到车参 wheel_base ，即将赋予默认值" << endl;
            }

            if (val.HasMember("heavy_forward_max_steering")) {
                veh_start_end.veh_param.heavy_forward_max_steering = val["heavy_forward_max_steering"].GetDouble() * M_PI / 180.0;
            }
            else {
                veh_start_end.veh_param.heavy_forward_max_steering = 27.24 * M_PI / 180.0;
                cout << "无法找到车参 heavy_forward_max_steering ，即将赋予默认值" << endl;
            }

            if (val.HasMember("heavy_backward_max_steering")) {
                veh_start_end.veh_param.heavy_backward_max_steering = val["heavy_backward_max_steering"].GetDouble() * M_PI / 180.0;
            }
            else {
                veh_start_end.veh_param.heavy_backward_max_steering = 22.39 * M_PI / 180.0;
                cout << "无法找到车参 heavy_backward_max_steering ，即将赋予默认值" << endl;
            }

            if (val.HasMember("light_backward_max_steering")) {
                veh_start_end.veh_param.light_backward_max_steering = val["light_backward_max_steering"].GetDouble() * M_PI / 180.0;
            }
            else {
                veh_start_end.veh_param.light_backward_max_steering = 27.24 * M_PI / 180.0;
                cout << "无法找到车参 light_backward_max_steering ，即将赋予默认值" << endl;
            }

            if (val.HasMember("light_forward_max_steering")) {
                veh_start_end.veh_param.light_forward_max_steering = val["light_forward_max_steering"].GetDouble() * M_PI / 180.0;
            }
            else {
                veh_start_end.veh_param.light_forward_max_steering = 30.63 * M_PI / 180.0;
                cout << "无法找到车参 light_forward_max_steering ，即将赋予默认值" << endl;
            }

            if (val.HasMember("safe_margin_bound") && val["safe_margin_bound"].IsNumber()) {
                veh_start_end.veh_param.safe_margin_bound = val["safe_margin_bound"].GetDouble();
                cout << "veh_start_end.veh_param.safe_margin_bound " << veh_start_end.veh_param.safe_margin_bound << endl;
            }
            else {
                veh_start_end.veh_param.safe_margin_bound = 0.5;
                cout << "无法找到车参 safe_margin_bound ，即将赋予默认值" << endl;
            }

            if (val.HasMember("veh_center_2_side") && val["veh_center_2_side"].IsNumber()) {
                veh_start_end.veh_param.veh_center_2_side = val["veh_center_2_side"].GetDouble();
                cout << "veh_start_end.veh_param.veh_center_2_side " << veh_start_end.veh_param.veh_center_2_side << endl;
            }
            else {
                veh_start_end.veh_param.veh_center_2_side = 1.735;
                cout << "无法找到车参 veh_center_2_side ，即将赋予默认值" << endl;
            }

            if (val.HasMember("veh_center_2_front") && val["veh_center_2_front"].IsNumber()) {
                veh_start_end.veh_param.veh_center_2_front = val["veh_center_2_front"].GetDouble();
                cout << "veh_start_end.veh_param.veh_center_2_front " << veh_start_end.veh_param.veh_center_2_front << endl;
            }
            else {
                veh_start_end.veh_param.veh_center_2_front = 7.3;
                cout << "无法找到车参 veh_center_2_front ，即将赋予默认值" << endl;
            }

            if (val.HasMember("safe_margin_obstacle") && val["safe_margin_obstacle"].IsNumber()) {
                veh_start_end.veh_param.safe_margin_obstacle = val["safe_margin_obstacle"].GetDouble();
                cout << "veh_start_end.veh_param.safe_margin_obstacle " << veh_start_end.veh_param.safe_margin_obstacle << endl;
            }
            else {
                veh_start_end.veh_param.safe_margin_obstacle = 2.0;
                cout << "无法找到车参 safe_margin_obstacle ，即将赋予默认值" << endl;
            }

            if (val.HasMember("veh_center_2_rear_bound") && val["veh_center_2_rear_bound"].IsNumber()) {
                veh_start_end.veh_param.veh_center_2_rear_bound = val["veh_center_2_rear_bound"].GetDouble();
                cout << "veh_start_end.veh_param.veh_center_2_rear_bound " << veh_start_end.veh_param.veh_center_2_rear_bound << endl;
            }
            else {
                veh_start_end.veh_param.veh_center_2_rear_bound = 0.5;
                cout << "无法找到车参 veh_center_2_rear_bound ，即将赋予默认值" << endl;
            }


            if (val.HasMember("delta_dist") && val["delta_dist"].IsNumber()) {
                veh_start_end.veh_param.delta_dist = val["delta_dist"].GetDouble();
                cout << "veh_start_end.veh_param.delta_dist " << veh_start_end.veh_param.delta_dist << endl;
            }
            else {
                veh_start_end.veh_param.delta_dist = 2.0;
                cout << "无法找到车参 delta_dist ，即将赋予默认值" << endl;
            }

            if (val.HasMember("grid_dist") && val["grid_dist"].IsNumber()) {
                veh_start_end.veh_param.grid_dist = val["grid_dist"].GetDouble();
                cout << "veh_start_end.veh_param.grid_dist " << veh_start_end.veh_param.grid_dist << endl;
            }
            else {
                veh_start_end.veh_param.grid_dist = 1.0;
                cout << "无法找到车参 grid_dist ，即将赋予默认值" << endl;
            }

            if (val.HasMember("max_kappa") && val["max_kappa"].IsNumber()) {
                veh_start_end.veh_param.max_kappa = val["max_kappa"].GetDouble();
                cout << "veh_start_end.veh_param.max_kappa " << veh_start_end.veh_param.max_kappa << endl;
            }
            else {
                veh_start_end.veh_param.max_kappa = 0.07;
                cout << "无法找到车参 max_kappa ，即将赋予默认值" << endl;
            }

            if (val.HasMember("path_error_term") && val["path_error_term"].IsNumber()) {
                veh_start_end.veh_param.path_error_term = val["path_error_term"].GetDouble();
                cout << "veh_start_end.veh_param.path_error_term " << veh_start_end.veh_param.path_error_term << endl;
            }
            else {
                veh_start_end.veh_param.path_error_term = 0.0;
                cout << "无法找到车参 path_error_term ，即将赋予默认值" << endl;
            }

            if (val.HasMember("grid_angle") && val["grid_angle"].IsNumber()) {
                veh_start_end.veh_param.grid_angle = val["grid_angle"].GetDouble() * M_PI / 180.0;
                cout << "veh_start_end.veh_param.grid_angle " << veh_start_end.veh_param.grid_angle << endl;
            }
            else {
                veh_start_end.veh_param.grid_angle = 1.0;
                cout << "无法找到车参 grid_angle ，即将赋予默认值" << endl;
            }

            if (val.HasMember("hybridastar_step_length") && val["hybridastar_step_length"].IsNumber()) {
                veh_start_end.veh_param.hybridastar_step_length = val["hybridastar_step_length"].GetDouble();
                cout << "veh_start_end.veh_param.hybridastar_step_length " << veh_start_end.veh_param.hybridastar_step_length << endl;
            }
            else {
                veh_start_end.veh_param.hybridastar_step_length = 1.0;
                cout << "无法找到车参 hybridastar_step_length ，即将赋予默认值" << endl;
            }

            if (val.HasMember("path_curvature_term") && val["path_curvature_term"].IsNumber()) {
                veh_start_end.veh_param.path_curvature_term = val["path_curvature_term"].GetDouble();
                cout << "veh_start_end.veh_param.path_curvature_term " << veh_start_end.veh_param.path_curvature_term << endl;
            }
            else {
                veh_start_end.veh_param.path_curvature_term = 0.0;
                cout << "无法找到车参 path_curvature_term ，即将赋予默认值" << endl;
            }

            if (val.HasMember("switch_penalty") && val["switch_penalty"].IsNumber()) {
                veh_start_end.veh_param.switch_penalty = val["switch_penalty"].GetDouble();
                cout << "veh_start_end.veh_param.switch_penalty " << veh_start_end.veh_param.switch_penalty << endl;
            }
            else {
                veh_start_end.veh_param.switch_penalty = 10;
                cout << "无法找到车参 switch_penalty ，即将赋予默认值" << endl;
            }

            if (val.HasMember("forward_penalty") && val["forward_penalty"].IsNumber()) {
                veh_start_end.veh_param.forward_penalty = val["forward_penalty"].GetDouble();
                cout << "veh_start_end.veh_param.forward_penalty " << veh_start_end.veh_param.forward_penalty << endl;
            }
            else {
                veh_start_end.veh_param.forward_penalty = 1.0;
                cout << "无法找到车参 forward_penalty ，即将赋予默认值" << endl;
            }


            if (val.HasMember("path_smoothness_term") && val["path_smoothness_term"].IsNumber()) {
                veh_start_end.veh_param.path_smoothness_term = val["path_smoothness_term"].GetDouble();
                cout << "veh_start_end.veh_param.path_smoothness_term " << veh_start_end.veh_param.path_smoothness_term << endl;
            }
            else {
                veh_start_end.veh_param.path_smoothness_term = 0.1;
                cout << "无法找到车参 path_smoothness_term ，即将赋予默认值" << endl;
            }

            if (val.HasMember("backward_penalty") && val["backward_penalty"].IsNumber()) {
                veh_start_end.veh_param.backward_penalty = val["backward_penalty"].GetDouble();
                cout << "veh_start_end.veh_param.backward_penalty " << veh_start_end.veh_param.backward_penalty << endl;
            }
            else {
                veh_start_end.veh_param.backward_penalty = 5.5;
                cout << "无法找到车参 backward_penalty ，即将赋予默认值" << endl;
            }

            if (val.HasMember("turnning_penalty") && val["turnning_penalty"].IsNumber()) {
                veh_start_end.veh_param.turnning_penalty = val["turnning_penalty"].GetDouble();
                cout << "veh_start_end.veh_param.turnning_penalty " << veh_start_end.veh_param.turnning_penalty << endl;
            }
            else {
                veh_start_end.veh_param.turnning_penalty = 2.468;
                cout << "无法找到车参 turnning_penalty ，即将赋予默认值" << endl;
            }

            if (val.HasMember("angle_discrete_num") && val["angle_discrete_num"].IsNumber()) {
                veh_start_end.veh_param.angle_discrete_num = val["angle_discrete_num"].GetUint();
                cout << "veh_start_end.veh_param.angle_discrete_num " << veh_start_end.veh_param.angle_discrete_num << endl;
            }
            else {
                veh_start_end.veh_param.angle_discrete_num = 3;
                cout << "无法找到车参 angle_discrete_num ，即将赋予默认值" << endl;
            }

            if (val.HasMember("max_fitting_radius") && val["max_fitting_radius"].IsNumber()) {
                veh_start_end.veh_param.max_fitting_radius = val["max_fitting_radius"].GetDouble();
                cout << "veh_start_end.veh_param.max_fitting_radius " << veh_start_end.veh_param.max_fitting_radius << endl;
            }
            else {
                veh_start_end.veh_param.max_fitting_radius = 100;
                cout << "无法找到车参 max_fitting_radius ，即将赋予默认值" << endl;
            }

            if (val.HasMember("max_iterations_opti") && val["max_iterations_opti"].IsNumber()) {
                veh_start_end.veh_param.max_iterations_opti = val["max_iterations_opti"].GetDouble();
                cout << "veh_start_end.veh_param.max_iterations_opti " << veh_start_end.veh_param.max_iterations_opti << endl;
            }
            else {
                veh_start_end.veh_param.max_iterations_opti = 100;
                cout << "无法找到车参 max_iterations_opti ，即将赋予默认值" << endl;
            }


            if (val.HasMember("cusp_extension_distance") && val["cusp_extension_distance"].IsNumber()) {
                veh_start_end.veh_param.cusp_extension_distance = val["cusp_extension_distance"].GetFloat();
                cout << "veh_start_end.veh_param.cusp_extension_distance " << veh_start_end.veh_param.cusp_extension_distance << endl;
            }
            else {
                veh_start_end.veh_param.cusp_extension_distance = 3.0;
                cout << "无法找到车参 cusp_extension_distance ，即将赋予默认值" << endl;
            }

            if (val.HasMember("linear_preferred_distance") && val["linear_preferred_distance"].IsNumber()) {
                veh_start_end.veh_param.linear_preferred_distance = val["linear_preferred_distance"].GetDouble();
                cout << "veh_start_end.veh_param.linear_preferred_distance " << veh_start_end.veh_param.linear_preferred_distance << endl;
            }
            else {
                veh_start_end.veh_param.linear_preferred_distance = 3.0;
                cout << "无法找到车参 linear_preferred_distance ，即将赋予默认值" << endl;
            }

            if (val.HasMember("safe_margin_error") && val["safe_margin_error"].IsNumber()) {
                veh_start_end.veh_param.safe_margin_error = val["safe_margin_error"].GetDouble();
                cout << "veh_start_end.veh_param.safe_margin_error " << veh_start_end.veh_param.safe_margin_error << endl;
            }
            else {
                veh_start_end.veh_param.safe_margin_error = 0.0;
                cout << "无法找到车参 safe_margin_error ，即将赋予默认值" << endl;
            }

            if (val.HasMember("speed_error_term") && val["speed_error_term"].IsNumber()) {
                veh_start_end.veh_param.speed_error_term = val["speed_error_term"].GetFloat();
                cout << "veh_start_end.veh_param.speed_error_term " << veh_start_end.veh_param.speed_error_term << endl;
            }
            else {
                veh_start_end.veh_param.speed_error_term = 0.1;
                cout << "无法找到车参 speed_error_term ，即将赋予默认值" << endl;
            }


            if (val.HasMember("speed_smooth_term") && val["speed_smooth_term"].IsNumber()) {
                veh_start_end.veh_param.speed_smooth_term = val["speed_smooth_term"].GetFloat();
                cout << "veh_start_end.veh_param.speed_smooth_term " << veh_start_end.veh_param.speed_smooth_term << endl;
            }
            else {
                veh_start_end.veh_param.speed_smooth_term = 0.01;
                cout << "无法找到车参 speed_smooth_term ，即将赋予默认值" << endl;
            }

            if (val.HasMember("max_acceleration") && val["max_acceleration"].IsNumber()) {
                veh_start_end.veh_param.max_acceleration = val["max_acceleration"].GetFloat();
                cout << "veh_start_end.veh_param.max_acceleration " << veh_start_end.veh_param.max_acceleration << endl;
            }
            else {
                veh_start_end.veh_param.max_acceleration = 0.3;
                cout << "无法找到车参 max_acceleration ，即将赋予默认值" << endl;
            }

            if (val.HasMember("min_acceleration") && val["min_acceleration"].IsNumber()) {
                veh_start_end.veh_param.min_acceleration = val["min_acceleration"].GetFloat();
                cout << "veh_start_end.veh_param.min_acceleration " << veh_start_end.veh_param.min_acceleration << endl;
            }
            else {
                veh_start_end.veh_param.min_acceleration = -0.4;
                cout << "无法找到车参 min_acceleration ，即将赋予默认值" << endl;
            }

            if (val.HasMember("reverse_speed") && val["reverse_speed"].IsNumber()) {
                veh_start_end.veh_param.reverse_speed = val["reverse_speed"].GetFloat();
                cout << "veh_start_end.veh_param.reverse_speed " << veh_start_end.veh_param.reverse_speed << endl;
            }
            else {
                veh_start_end.veh_param.reverse_speed = 1.0;
                cout << "无法找到车参 reverse_speed ，即将赋予默认值" << endl;
            }


            if (val.HasMember("narrow_road_speed_limit") && val["narrow_road_speed_limit"].IsNumber()) {
                veh_start_end.veh_param.narrow_road_speed_limit = val["narrow_road_speed_limit"].GetFloat();
                cout << "veh_start_end.veh_param.narrow_road_speed_limit " << veh_start_end.veh_param.narrow_road_speed_limit << endl;
            }
            else {
                cout << "无法找到车参 narrow_road_speed_limit ，即将赋予默认值" << endl;
                veh_start_end.veh_param.narrow_road_speed_limit = 3;
            }

            if (val.HasMember("slope_road_speed_limit") && val["slope_road_speed_limit"].IsNumber()) {
                veh_start_end.veh_param.slope_road_speed_limit = val["slope_road_speed_limit"].GetFloat();
                cout << "veh_start_end.veh_param.slope_road_speed_limit " << veh_start_end.veh_param.slope_road_speed_limit << endl;
            }
            else {
                cout << "无法找到车参 slope_road_speed_limit" << endl;
                veh_start_end.veh_param.slope_road_speed_limit = 3.0;
            }

            if (val.HasMember("intersection_road_speed_limit") && val["intersection_road_speed_limit"].IsNumber()) {
                veh_start_end.veh_param.intersection_road_speed_limit = val["intersection_road_speed_limit"].GetFloat();
                cout << "veh_start_end.veh_param.intersection_road_speed_limit " << veh_start_end.veh_param.intersection_road_speed_limit << endl;
            }
            else {
                cout << "无法找到车参 intersection_road_speed_limit" << endl;
                veh_start_end.veh_param.intersection_road_speed_limit = 3.0;
            }

            if (val.HasMember("bumpy_road_speed_limit") && val["bumpy_road_speed_limit"].IsNumber()) {
                veh_start_end.veh_param.bumpy_road_speed_limit = val["bumpy_road_speed_limit"].GetFloat();
                cout << "veh_start_end.veh_param.bumpy_road_speed_limit " << veh_start_end.veh_param.bumpy_road_speed_limit << endl;
            }
            else {
                cout << "无法找到车参 bumpy_road_speed_limit" << endl;
                veh_start_end.veh_param.bumpy_road_speed_limit = 3.0;
            }

            if (val.HasMember("regular_road_speed_limit") && val["regular_road_speed_limit"].IsNumber()) {
                veh_start_end.veh_param.regular_road_speed_limit = val["regular_road_speed_limit"].GetFloat();
                cout << "veh_start_end.veh_param.regular_road_speed_limit " << veh_start_end.veh_param.regular_road_speed_limit << endl;
            }
            else {
                cout << "无法找到车参 regular_road_speed_limit" << endl;
                veh_start_end.veh_param.regular_road_speed_limit = 3.0;
            }


            if (val.HasMember("vehicle_code") && val["vehicle_code"].IsNumber()) {
                veh_start_end.veh_param.vehicle_code = val["vehicle_code"].GetUint();
                cout << "veh_start_end.veh_param.vehicle_code " << veh_start_end.veh_param.vehicle_code << endl;
            }
            else {
                cout << "无法找到车参 vehicle_code" << endl;
                veh_start_end.veh_param.vehicle_code = 9999;
            }

            if (val.HasMember("uniform_compaction_enable") && val["uniform_compaction_enable"].IsBool()) {
                veh_start_end.veh_param.uniform_compaction_enable = val["uniform_compaction_enable"].GetBool();
                cout << "veh_start_end.veh_param.uniform_compaction_enable " << veh_start_end.veh_param.uniform_compaction_enable << endl;
            }
            else {
                cout << "无法找到车参 uniform_compaction_enable" << endl;
                veh_start_end.veh_param.uniform_compaction_enable = true;
            }


            if (val.HasMember("is_light") && val["is_light"].IsBool()) {
                veh_start_end.veh_param.is_light = val["is_light"].GetBool();
                cout << "veh_start_end.veh_param.is_light " << veh_start_end.veh_param.is_light << endl;
            }
            else {
                cout << "无法找到车参 is_light ，即将赋予默认值" << endl;
                veh_start_end.veh_param.is_light = false;
            }


            

            if (val.HasMember("speed_limit_level") && val["speed_limit_level"].IsNumber() && val["speed_limit_level"].GetUint() >= 1 && val["speed_limit_level"].GetUint() <= 3) {
                veh_start_end.veh_param.speed_limit_level = static_cast<SpeedLimitLevel>(val["speed_limit_level"].GetUint());
                cout << "veh_start_end.veh_param.speed_limit_level " << static_cast<int>(veh_start_end.veh_param.speed_limit_level) << endl;
            }
            else {
                cout << "无法找到车参 speed_limit_level ，即将赋予默认值" << endl;
                veh_start_end.veh_param.speed_limit_level = SpeedLimitLevel::three;
            }

            if (val.HasMember("L2") && val["L2"].IsNumber()) {
                veh_start_end.veh_param.L2 = val["L2"].GetUint();
            }
            else {
                cout << "无法找到车参 L2 ，即将赋予默认值" << endl;
                veh_start_end.veh_param.L2 = 8;
            }

            if (val.HasMember("L3") && val["L3"].IsNumber()) {
                veh_start_end.veh_param.L3 = val["L3"].GetUint();
            }
            else {
                cout << "无法找到车参 L3 ，即将赋予默认值" << endl;
                veh_start_end.veh_param.L3 = 8;
            }


            if (val.HasMember("rs_min_length") && val["rs_min_length"].IsNumber()) {
                veh_start_end.veh_param.rs_min_length = val["rs_min_length"].GetFloat();
            }
            else {
                cout << "无法找到车参 rs_min_length ，即将赋予默认值" << endl;
                veh_start_end.veh_param.rs_min_length = 1;
            }

            if (val.HasMember("L1") && val["L1"].IsNumber()) {
                veh_start_end.veh_param.L1 = val["L1"].GetFloat();
            }
            else {
                cout << "无法找到车参 L1 ，即将赋予默认值" << endl;
                veh_start_end.veh_param.L1 = 3;
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


            if (val.HasMember("sample_num") && val["sample_num"].IsNumber()) {
                veh_start_end.veh_param.sample_num = val["sample_num"].GetUint();
            }
            else {
                cout << "无法找到车参 sample_num ，即将赋予默认值" << endl;
                veh_start_end.veh_param.sample_num = 40;
            }

            if (val.HasMember("plan_time") && val["plan_time"].IsNumber()) {
                veh_start_end.veh_param.plan_time = val["plan_time"].GetFloat();
            }
            else {
                cout << "无法找到车参 plan_time ，即将赋予默认值" << endl;
                veh_start_end.veh_param.plan_time = 0.2;
            }

            if (val.HasMember("dis_threshold") && val["dis_threshold"].IsNumber()) {
                veh_start_end.veh_param.dis_threshold = val["dis_threshold"].GetFloat();
            }
            else {
                cout << "无法找到车参 dis_threshold ，即将赋予默认值" << endl;
                veh_start_end.veh_param.dis_threshold = 2.0;
            }
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
    // this_thread::sleep_for(chrono::milliseconds(100));
    // cout << "VecWaypoint2json..." << endl;

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
    cout << "执行完代码 writer.StartObject();" << endl;

    writer.Key("trajectory_info");
    cout << "执行完代码 writer.Key(trajectory_info )" << endl;
    writer.StartArray();
    cout << "执行完代码 writer.StartArray();" << endl;
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
    cout << "执行完代码 if (vec_wp.size() == 0)" << endl;

    for (size_t i = 0; i < vec_wp.size(); i++) {
        writer.StartObject();
        writer.Key("x");
        writer.Double(vec_wp.at(i).x);

        writer.Key("y");
        writer.Double(vec_wp.at(i).y);

        writer.Key("z");
        writer.Double(0);

        writer.Key("yaw");
        writer.Double(vec_wp.at(i).yaw);

        writer.Key("curvature");
        writer.Double(vec_wp.at(i).curvature);

        writer.Key("speed");
        writer.Double(vec_wp.at(i).speed);

        writer.Key("distance");
        writer.Double(vec_wp.at(i).distance);

        writer.Key("attribute");
        writer.Uint(static_cast<int>(vec_wp.at(i).attribute));

        writer.Key("speed_limit");
        writer.Double(vec_wp.at(i).speed_limit);

        writer.Key("direction");
        writer.Int(vec_wp.at(i).direction);
        writer.EndObject();
    }
    cout << "执行完代码  for (size_t i = 0; i < vec_wp.size(); i++)" << endl;
    writer.EndArray();
    cout << "执行完代码 writer.EndArray();" << endl;

    writer.Key("vec_path");
    cout << "执行完代码 writer.Key(vec_path);" << endl;
    writer.StartArray();
    cout << "执行完代码 writer.StartArray();" << endl;
    if (plan_obj.road_sequence_.size() == 0) {
        writer.Uint(999);
        cout << "执行完代码 writer.Uint(plan_obj.sequence_mapping_.at(plan_obj.start_key_))" << endl;
    }
    else {
        for (size_t j = 0; j < plan_obj.road_sequence_.size(); j++) {
            writer.Uint(plan_obj.sequence_mapping_.at(plan_obj.road_sequence_.at(j)));
        }
        cout << "执行完代码 writer.Uint(plan_obj.sequence_mapping_.at(plan_obj.road_sequence_.at(j)));" << endl;
    }

    writer.EndArray();
    cout << "执行完代码 writer.EndArray();" << endl;

    writer.Key("error_type");
    writer.Uint(static_cast<unsigned char>(plan_obj.error_type_));
    cout << "执行完代码 writer.Uint(static_cast<unsigned char>(plan_obj.error_type_));" << endl;


    writer.EndObject();

    cout << "执行完代码 writer.EndObject();" << endl;

    GlobalVariable::getInstance()->SetGlobalStr(strbuf.GetString());
    auto         currentTime = chrono::system_clock::now();
    time_t       timestamp   = chrono::system_clock::to_time_t(currentTime);
    stringstream ss;
    ss << put_time(localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
    string timeStr = ss.str();

    // 构造文件路径
    string filePath = timeStr + "_" + plan_obj.vehicle_code_ + "_output.json";

    ofstream outputFile(filePath);
    cout << "执行完代码 ofstream outputFile(filePath);;" << endl;
    // 将JSON数据写入文件
    outputFile << GlobalVariable::getInstance()->GetGlobalStr();
    cout << "执行完代码 outputFile << GlobalVariable::getInstance()->GetGlobalStr();" << endl;
    // 关闭文件流
    outputFile.close();


    cout << "规划库成功返回轨迹，欢迎下次光临                 " << timeStr << endl;
    time(&end_time);

    {
        unique_lock<shared_mutex> lock(GlobalVariable::getInstance()->record_file_write_lock);
        ofstream                  record;
        std::string               folderPath = "record_file";
        std::string               filePath   = folderPath + "/GlobalPlanning_record.txt";
        if (!fs::exists(folderPath)) {
            try {
                fs::create_directory(folderPath);
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error creating directory: " << e.what() << std::endl;
            }
        }
        record.open(filePath, ios_base::app);
        record << timeStr << " ，处理完规划请求，请求号：" << plan_obj.key_ << "，车辆编号：" << plan_obj.vehicle_code_ << "  规划库版本号:G_V1.4.0.20250310_beta" << endl;
        record.close();
    }

    return GlobalVariable::getInstance()->GetGlobalStr();
}


bool GetMap(char* parea) {
    Document doc;
    doc.Parse(parea);
    if (doc.HasParseError()) {
        doc.GetParseError();
        doc.GetErrorOffset();
    }
    doc.GetAllocator();

    // 清空所有的地图边界、参考路径、relation、
    GlobalVariable::getInstance()->ClearData();

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
    std::cout << "解析border_points完毕,边界点数量：" << v_bp.size() << std::endl;

    // 解析reference_trajs
    const Value&               trajsArray = doc["reference_trajs"];
    std::map<int, _SingleTraj> m_traj_self_driving, m_traj_human_driving;
    _SingleTraj                traj;
    _TrajectoryPoint           tp;
    int                        traj_type = -1;
    for (SizeType i = 0; i < trajsArray.Size(); i++) {
        traj.trajectory.clear();
        traj.id = trajsArray[i]["id"].GetInt();
        if (trajsArray[i].HasMember("type")) {
            traj_type = trajsArray[i]["type"].GetInt();
        }
        else {
            traj_type = 2;
        }

        const Value& trajPointsArray = trajsArray[i]["trajectory"];
        for (SizeType j = 0; j < trajPointsArray.Size(); j++) {
            tp.x         = trajPointsArray[j]["x"].GetDouble();
            tp.y         = trajPointsArray[j]["y"].GetDouble();
            tp.z         = trajPointsArray[j]["z"].GetDouble();
            tp.yaw       = trajPointsArray[j]["yaw"].GetDouble() / 180.0 * M_PI;
            tp.curvature = trajPointsArray[j]["curvature"].GetDouble();
            tp.attribute = static_cast<PointAttribute>(trajPointsArray[j]["attribute"].GetInt());
            tp.direction = static_cast<unsigned char>(trajPointsArray[j]["direction"].GetInt());
            traj.trajectory.push_back(tp);
        }
        if (traj_type == 2) {
            m_traj_self_driving[traj.id]  = traj;
            m_traj_human_driving[traj.id] = traj;
        }
        if (traj_type == 0) {
            m_traj_self_driving[traj.id] = traj;
        }
        else if (traj_type == 1) {
            m_traj_human_driving[traj.id] = traj;
        }
    }
    GlobalVariable::getInstance()->SetAllSelfDrivingReferencelines(m_traj_self_driving);
    GlobalVariable::getInstance()->SetAllHumanDrivingReferencelines(m_traj_human_driving);

    // 解析relation
    const Value&                    relationObj = doc["relation"];
    std::map<int, std::vector<int>> m_relation_self_driving;  // 无人车专用relation
    std::map<int, std::vector<int>> m_relation_human_driving; // 有人车专用relation
    int                             key;
    std::vector<int>                relVec;
    for (Value::ConstMemberIterator itr = relationObj.MemberBegin(); itr != relationObj.MemberEnd(); ++itr) {
        key                   = stoi(itr->name.GetString());
        const Value& relArray = itr->value;
        relVec.clear();
        for (SizeType k = 0; k < relArray.Size(); k++) {
            relVec.push_back(relArray[k].GetInt());
        }

        // 根据路径类型区分无人车和有人车专用的relation
        if (m_traj_self_driving.find(key) != m_traj_self_driving.end()) {
            m_relation_self_driving[key] = relVec;
        }
        if (m_traj_human_driving.find(key) != m_traj_human_driving.end()) {
            m_relation_human_driving[key] = relVec;
        }
    }
    GlobalVariable::getInstance()->SetSelfDrivingReferencelineRelation(m_relation_self_driving);
    GlobalVariable::getInstance()->SetHumanDrivingReferencelineRelation(m_relation_human_driving);

    GlobalVariable::getInstance()->CreateSelfDrivingSequenceMapping(GlobalVariable::getInstance()->GetAllSelfDrivingReferencelines());
    // 构建无人车的DirectedGraph
    GlobalVariable::getInstance()->CreateSelfDrivingDirectedGraph(GlobalVariable::getInstance()->GetSelfDrivingReferencelineRelation());

    return true;
}


_AllHumanVechicleInfos ParseHumanVehPredictingJson(char* str) {
    _AllHumanVechicleInfos all_human_vehicle_infos;
    rapidjson::Document    doc;
    doc.Parse(str);
    if (doc.HasParseError()) {
        cout << "parse失败......" << endl;
    }
    doc.GetAllocator();

    const Value& vehInfoArray = doc["veh_info"];
    cout << "vehInfoArray.size():" << vehInfoArray.Size() << endl;


    for (SizeType i = 0; i < vehInfoArray.Size(); i++) {
        const Value& vehInfo = vehInfoArray[i];

        if (!vehInfo.IsObject()) {
            std::cerr << "JSON 格式错误: veh_info 数组中的元素不是对象" << std::endl;
            continue;
        }

        _HumanVechicleInfo humanVechicleInfo;

        if (vehInfo.HasMember("x") && vehInfo["x"].IsDouble()) {
            humanVechicleInfo.pos.x = vehInfo["x"].GetDouble();
        }
        else {
            std::cerr << "JSON 格式错误: 缺少或类型错误的 x 字段" << std::endl;
            continue;
        }

        if (vehInfo.HasMember("y") && vehInfo["y"].IsDouble()) {
            humanVechicleInfo.pos.y = vehInfo["y"].GetDouble();
        }
        else {
            std::cerr << "JSON 格式错误: 缺少或类型错误的 y 字段" << std::endl;
            continue;
        }

        if (vehInfo.HasMember("yaw") && vehInfo["yaw"].IsDouble()) {
            humanVechicleInfo.pos.yaw = vehInfo["yaw"].GetDouble();
        }
        else {
            std::cerr << "JSON 格式错误: 缺少或类型错误的 yaw 字段" << std::endl;
            continue;
        }

        if (vehInfo.HasMember("vehicle_code") && vehInfo["vehicle_code"].IsString()) {
            humanVechicleInfo.id = vehInfo["vehicle_code"].GetString();
        }
        else {
            std::cerr << "JSON 格式错误: 缺少或类型错误的 vehicle_code 字段" << std::endl;
            continue;
        }

        all_human_vehicle_infos.human_vechicle_infos.push_back(humanVechicleInfo);
    }
    if (doc.HasMember("predicting_distance")) {
        cout << "解析 predicting_distance 中" << endl;
        all_human_vehicle_infos.predicting_distance = doc["predicting_distance"].GetUint();
    }
    if (doc.HasMember("key")) {
        cout << "解析 key 中" << endl;
        all_human_vehicle_infos.my_key = doc["key"].GetString();
    }
    cout << "收到" << all_human_vehicle_infos.human_vechicle_infos.size() << "个车辆信息" << endl;
    return all_human_vehicle_infos;
}


string HumanVehFurtureVecWaypoint2json(std::map<string, std::vector<std::vector<_TrajectoryPoint>>>& all_path, Predicting& obj) {
    cout << "enter VecWaypoint2json" << endl;


    time_t start_time, end_time;
    time(&start_time);
    rapidjson::StringBuffer                    strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);

    std::cout << "开始写json" << std::endl;
    writer.StartObject();
    std::cout << "执行完代码 writer.StartObject();" << std::endl;

    writer.Key("pathInfo");
    std::cout << "执行完代码 writer.Key(pathInfo )" << std::endl;
    writer.StartArray();
    std::cout << "执行完代码 writer.StartArray();" << std::endl;

    for (const auto& pair : all_path) {
        writer.StartObject();
        writer.Key("vehicleCode");
        writer.String(pair.first.c_str());

        writer.Key("paths");
        writer.StartArray();
        for (const auto& path : pair.second) {
            writer.StartObject();
            writer.Key("pathPoints");
            writer.StartArray();
            for (const auto& point : path) {
                writer.StartObject();
                writer.Key("x");
                writer.Double(point.x);

                writer.Key("y");
                writer.Double(point.y);


                writer.Key("yaw");
                writer.Double(point.yaw);

                writer.Key("curvature");
                writer.Double(point.curvature);

                writer.Key("direction");
                writer.Int(point.direction);
                writer.EndObject();
            }
            writer.EndArray();
            writer.EndObject();
        }
        writer.EndArray();
        writer.EndObject();
    }
    std::cout << "执行完代码  for (const auto& pair : all_path)" << std::endl;
    writer.EndArray();
    std::cout << "执行完代码 writer.EndArray();" << std::endl;

    writer.EndObject();


    cout << "执行完代码 writer.EndObject();" << endl;

    GlobalVariable::getInstance()->SetGlobalStr(strbuf.GetString());
    auto         currentTime = chrono::system_clock::now();
    time_t       timestamp   = chrono::system_clock::to_time_t(currentTime);
    stringstream ss;
    ss << put_time(localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
    string timeStr = ss.str();

    // 构造文件路径
    string filePath = timeStr + "_" + obj.key_ + "_output.json";

    ofstream outputFile(filePath);
    cout << "执行完代码 ofstream outputFile(filePath);;" << endl;
    // 将JSON数据写入文件
    outputFile << GlobalVariable::getInstance()->GetGlobalStr();
    cout << "执行完代码 outputFile << GlobalVariable::getInstance()->GetGlobalStr();" << endl;
    // 关闭文件流
    outputFile.close();


    cout << "规划库成功返回轨迹，欢迎下次光临                 " << timeStr << endl;
    time(&end_time);

    {
        unique_lock<shared_mutex> lock(GlobalVariable::getInstance()->record_file_write_lock);
        ofstream                  record;
        std::string               folderPath = "record_file";
        std::string               filePath   = folderPath + "/HumanVehPredicting_record.txt";
        if (!fs::exists(folderPath)) {
            try {
                fs::create_directory(folderPath);
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error creating directory: " << e.what() << std::endl;
            }
        }
        record.open(filePath, ios_base::app);
        record << timeStr << " ，处理完规划请求，请求号：" << obj.key_ << "  库版本号:G_V1.4.0.20250310_beta" << endl;
        record.close();
    }

    return GlobalVariable::getInstance()->GetGlobalStr();
}


} // namespace Parser
} // namespace GlobalPlanning

#endif // HELPER_H
