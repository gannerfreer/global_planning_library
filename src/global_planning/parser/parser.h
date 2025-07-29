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

    _TrajectoryPoint pp;
    if (doc.HasMember("reference_paths")) {
        cout << "解析 reference_paths 中" << endl;
        Value& val = doc["reference_paths"];
        for (size_t i = 0; i < val.Size(); i++) {
            Value&                   pathPointsArray = val[i]["reference_path"];
            vector<_TrajectoryPoint> temp_reference_path;
            for (SizeType j = 0; j < pathPointsArray.Size(); j++) {
                pp.x         = pathPointsArray[j]["x"].GetDouble();
                pp.y         = pathPointsArray[j]["y"].GetDouble();
                pp.yaw       = pathPointsArray[j]["yaw"].GetDouble();
                pp.direction = pathPointsArray[j]["direction"].GetInt();
                pp.attribute = PointAttribute::dump_road;
                temp_reference_path.push_back(pp);
            }
            veh_start_end.reference_paths.push_back(temp_reference_path);
        }
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
    std::vector<_SingleTraj>   input_paths, output_paths;
    _SingleTraj                traj;
    _TrajectoryPoint           tp;
    int                        traj_type   = -1;
    double                     speed_limit = -1;
    int                        guid_type   = 0;
    for (SizeType i = 0; i < trajsArray.Size(); i++) {
        traj.trajectory.clear();
        traj.id = trajsArray[i]["id"].GetInt();
        if (trajsArray[i].HasMember("type")) {
            traj_type = trajsArray[i]["type"].GetInt();
        }
        else {
            traj_type = 2;
        }

        if (trajsArray[i].HasMember("speed_limit")) {
            speed_limit = trajsArray[i]["speed_limit"].GetDouble();
        }
        if (trajsArray[i].HasMember("guid_type")) {
            guid_type = trajsArray[i]["guid_type"].GetInt();
        }

        const Value& trajPointsArray = trajsArray[i]["trajectory"];
        for (SizeType j = 0; j < trajPointsArray.Size(); j++) {
            tp.x           = trajPointsArray[j]["x"].GetDouble();
            tp.y           = trajPointsArray[j]["y"].GetDouble();
            tp.z           = trajPointsArray[j]["z"].GetDouble();
            tp.yaw         = trajPointsArray[j]["yaw"].GetDouble() / 180.0 * M_PI;
            tp.curvature   = trajPointsArray[j]["curvature"].GetDouble();
            tp.attribute   = static_cast<PointAttribute>(trajPointsArray[j]["attribute"].GetInt());
            tp.direction   = static_cast<unsigned char>(trajPointsArray[j]["direction"].GetInt());
            tp.speed_limit = speed_limit;
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

        if (guid_type == 1) {
            input_paths.push_back(traj);
        }
        if (guid_type == 2) {
            output_paths.push_back(traj);
        }
    }
    GlobalVariable::getInstance()->SetAllSelfDrivingReferencelines(m_traj_self_driving);
    GlobalVariable::getInstance()->SetAllHumanDrivingReferencelines(m_traj_human_driving);
    GlobalVariable::getInstance()->SetInGuidingPaths(input_paths);
    GlobalVariable::getInstance()->SetOutGuidingPaths(output_paths);

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

_LoadAreaPlanningInfos ParseLoadAreaPlanningJson(char* str) {
    _LoadAreaPlanningInfos planning_info;
    rapidjson::Document    doc;

    // 解析JSON字符串
    doc.Parse(str);
    if (doc.HasParseError()) {
        std::cerr << "JSON解析失败，错误码: " << doc.GetParseError() << std::endl;
        return planning_info;
    }

    // 解析等待点(Wait_Point) - 兼容字段不存在或为空的情况
    if (doc.HasMember("Wait_Point") && doc["Wait_Point"].IsObject()) {
        const rapidjson::Value& Wait_Point = doc["Wait_Point"];

        // 解析x坐标，兼容字段不存在或类型错误
        if (Wait_Point.HasMember("x") && Wait_Point["x"].IsDouble()) {
            planning_info.wait_point.x = Wait_Point["x"].GetDouble();
            std::cout << "解析 Wait_Point.x: " << planning_info.wait_point.x << std::endl;
        }
        else {
            planning_info.wait_point.x = 0.0;
            std::cerr << "wait_point.x 不存在或格式错误，赋予默认值: " << planning_info.Wait_Point.x << std::endl;
        }

        // 解析y坐标
        if (Wait_Point.HasMember("y") && Wait_Point["y"].IsDouble()) {
            planning_info.wait_point.y = Wait_Point["y"].GetDouble();
            std::cout << "解析 Wait_Point.y: " << planning_info.wait_point.y << std::endl;
        }
        else {
            planning_info.wait_point.y = 0.0;
            std::cerr << "Wait_Point.y 不存在或格式错误，赋予默认值: " << planning_info.wait_point.y << std::endl;
        }

        // 解析z坐标
        if (Wait_Point.HasMember("z") && Wait_Point["z"].IsDouble()) {
            planning_info.wait_point.z = Wait_Point["z"].GetDouble();
            std::cout << "解析 Wait_Point.z: " << planning_info.wait_point.z << std::endl;
        }
        else {
            planning_info.wait_point.z = 0.0;
            std::cerr << "Wait_Point.z 不存在或格式错误，赋予默认值: " << planning_info.wait_point.z << std::endl;
        }

        // 解析yaw角度
        if (Wait_Point.HasMember("yaw") && Wait_Point["yaw"].IsDouble()) {
            planning_info.wait_point.yaw = Wait_Point["yaw"].GetDouble();
            std::cout << "解析 Wait_Point.yaw: " << planning_info.wait_point.yaw << std::endl;
        }
        else {
            planning_info.wait_point.yaw = 0.0;
            std::cerr << "Wait_Point.yaw 不存在或格式错误，赋予默认值: " << planning_info.wait_point.yaw << std::endl;
        }
    }

    // 解析加载点(Load_Point)
    if (doc.HasMember("Load_Point") && doc["Load_Point"].IsObject()) {
        const rapidjson::Value& load_point = doc["Load_Point"];

        if (Load_Point.HasMember("x") && Load_Point["x"].IsDouble()) {
            planning_info.load_point.x = Load_Point["x"].GetDouble();
            std::cout << "解析 Load_Point.x: " << planning_info.load_point.x << std::endl;
        }
        else {
            planning_info.load_point.x = 0.0;
            std::cerr << "Load_Point.x 不存在或格式错误，赋予默认值: " << planning_info.load_point.x << std::endl;
        }

        if (Load_Point.HasMember("y") && Load_Point["y"].IsDouble()) {
            planning_info.load_point.y = Load_Point["y"].GetDouble();
            std::cout << "解析 Load_Point.y: " << planning_info.load_point.y << std::endl;
        }
        else {
            planning_info.load_point.y = 0.0;
            std::cerr << "Load_Point.y 不存在或格式错误，赋予默认值: " << planning_info.load_point.y << std::endl;
        }

        if (Load_Point.HasMember("z") && Load_Point["z"].IsDouble()) {
            planning_info.load_point.z = Load_Point["z"].GetDouble();
            std::cout << "解析 Load_Point.z: " << planning_info.load_point.z << std::endl;
        }
        else {
            planning_info.load_point.z = 0.0;
            std::cerr << "Load_Point.z 不存在或格式错误，赋予默认值: " << planning_info.load_point.z << std::endl;
        }

        if (Load_Point.HasMember("yaw") && Load_Point["yaw"].IsDouble()) {
            planning_info.load_point.yaw = Load_Point["yaw"].GetDouble();
            std::cout << "解析 Load_Point.yaw: " << planning_info.load_point.yaw << std::endl;
        }
        else {
            planning_info.load_point.yaw = 0.0;
            std::cerr << "Load_Point.yaw 不存在或格式错误，赋予默认值: " << planning_info.load_point.yaw << std::endl;
        }
    }

    // 解析车辆参数(m_Veh_Param)
    if (doc.HasMember("m_Veh_Param") && doc["m_Veh_Param"].IsObject()) {
        const rapidjson::Value& veh_param = doc["m_Veh_Param"];
        _VehicleParam&          param     = planning_info.veh_param;
        std::cout << "开始解析车辆参数..." << std::endl;

        // 曲线长度参数
        if (veh_param.HasMember("max_curve_length") && veh_param["max_curve_length"].IsInt()) {
            param.max_curve_length = veh_param["max_curve_length"].GetInt();
            std::cout << "param.max_curve_length: " << param.max_curve_length << std::endl;
        }
        else {
            param.max_curve_length = 1;
            std::cerr << "无法找到车参 max_curve_length ，赋予默认值: " << param.max_curve_length << std::endl;
        }

        if (veh_param.HasMember("min_curve_length") && veh_param["min_curve_length"].IsInt()) {
            param.min_curve_length = veh_param["min_curve_length"].GetInt();
            std::cout << "param.min_curve_length: " << param.min_curve_length << std::endl;
        }
        else {
            param.min_curve_length = 1;
            std::cerr << "无法找到车参 min_curve_length ，赋予默认值: " << param.min_curve_length << std::endl;
        }

        if (veh_param.HasMember("delta_curve_length") && veh_param["delta_curve_length"].IsInt()) {
            param.delta_curve_length = veh_param["delta_curve_length"].GetInt();
            std::cout << "param.delta_curve_length: " << param.delta_curve_length << std::endl;
        }
        else {
            param.delta_curve_length = 1;
            std::cerr << "无法找到车参 delta_curve_length ，赋予默认值: " << param.delta_curve_length << std::endl;
        }

        // 车辆基础参数
        if (veh_param.HasMember("wheel_base_length") && veh_param["wheel_base_length"].IsInt()) {
            param.wheel_base_length = veh_param["wheel_base_length"].GetInt();
            std::cout << "param.wheel_base_length: " << param.wheel_base_length << std::endl;
        }
        else {
            param.wheel_base_length = 2700; // 典型轴距默认值(mm)
            std::cerr << "无法找到车参 wheel_base_length ，赋予默认值: " << param.wheel_base_length << std::endl;
        }

        if (veh_param.HasMember("center2side") && veh_param["center2side"].IsInt()) {
            param.center2side = veh_param["center2side"].GetInt();
            std::cout << "param.center2side: " << param.center2side << std::endl;
        }
        else {
            param.center2side = 800; // 典型轮距默认值(mm)
            std::cerr << "无法找到车参 center2side ，赋予默认值: " << param.center2side << std::endl;
        }

        // 直线长度参数
        if (veh_param.HasMember("max_straight_length") && veh_param["max_straight_length"].IsInt()) {
            param.max_straight_length = veh_param["max_straight_length"].GetInt();
            std::cout << "param.max_straight_length: " << param.max_straight_length << std::endl;
        }
        else {
            param.max_straight_length = 10000;
            std::cerr << "无法找到车参 max_straight_length ，赋予默认值: " << param.max_straight_length << std::endl;
        }

        if (veh_param.HasMember("min_straight_length") && veh_param["min_straight_length"].IsInt()) {
            param.min_straight_length = veh_param["min_straight_length"].GetInt();
            std::cout << "param.min_straight_length: " << param.min_straight_length << std::endl;
        }
        else {
            param.min_straight_length = 1000;
            std::cerr << "无法找到车参 min_straight_length ，赋予默认值: " << param.min_straight_length << std::endl;
        }

        if (veh_param.HasMember("delta_straight_length") && veh_param["delta_straight_length"].IsInt()) {
            param.delta_straight_length = veh_param["delta_straight_length"].GetInt();
            std::cout << "param.delta_straight_length: " << param.delta_straight_length << std::endl;
        }
        else {
            param.delta_straight_length = 500;
            std::cerr << "无法找到车参 delta_straight_length ，赋予默认值: " << param.delta_straight_length << std::endl;
        }

        // 转向角参数
        if (veh_param.HasMember("max_steering_angle") && veh_param["max_steering_angle"].IsInt()) {
            param.max_steering_angle = veh_param["max_steering_angle"].GetInt();
            std::cout << "param.max_steering_angle: " << param.max_steering_angle << std::endl;
        }
        else {
            param.max_steering_angle = 35; // 典型最大转向角(度)
            std::cerr << "无法找到车参 max_steering_angle ，赋予默认值: " << param.max_steering_angle << std::endl;
        }

        if (veh_param.HasMember("min_steering_angle") && veh_param["min_steering_angle"].IsInt()) {
            param.min_steering_angle = veh_param["min_steering_angle"].GetInt();
            std::cout << "param.min_steering_angle: " << param.min_steering_angle << std::endl;
        }
        else {
            param.min_steering_angle = -35; // 典型最小转向角(度)
            std::cerr << "无法找到车参 min_steering_angle ，赋予默认值: " << param.min_steering_angle << std::endl;
        }

        if (veh_param.HasMember("delta_steering_angle") && veh_param["delta_steering_angle"].IsInt()) {
            param.delta_steering_angle = veh_param["delta_steering_angle"].GetInt();
            std::cout << "param.delta_steering_angle: " << param.delta_steering_angle << std::endl;
        }
        else {
            param.delta_steering_angle = 5;
            std::cerr << "无法找到车参 delta_steering_angle ，赋予默认值: " << param.delta_steering_angle << std::endl;
        }

        if (veh_param.HasMember("standard_steering_angle") && veh_param["standard_steering_angle"].IsInt()) {
            param.standard_steering_angle = veh_param["standard_steering_angle"].GetInt();
            std::cout << "param.standard_steering_angle: " << param.standard_steering_angle << std::endl;
        }
        else {
            param.standard_steering_angle = 0; // 标准转向角(直行)
            std::cerr << "无法找到车参 standard_steering_angle ，赋予默认值: " << param.standard_steering_angle << std::endl;
        }

        // 权重参数
        if (veh_param.HasMember("weight_length") && veh_param["weight_length"].IsInt()) {
            param.weight_length = veh_param["weight_length"].GetInt();
            std::cout << "param.weight_length: " << param.weight_length << std::endl;
        }
        else {
            param.weight_length = 1;
            std::cerr << "无法找到车参 weight_length ，赋予默认值: " << param.weight_length << std::endl;
        }

        if (veh_param.HasMember("weight_curve") && veh_param["weight_curve"].IsInt()) {
            param.weight_curve = veh_param["weight_curve"].GetInt();
            std::cout << "param.weight_curve: " << param.weight_curve << std::endl;
        }
        else {
            param.weight_curve = 1;
            std::cerr << "无法找到车参 weight_curve ，赋予默认值: " << param.weight_curve << std::endl;
        }

        if (veh_param.HasMember("load_path_straight_length_weight") && veh_param["load_path_straight_length_weight"].IsInt()) {
            param.load_path_straight_length_weight = veh_param["load_path_straight_length_weight"].GetInt();
            std::cout << "param.load_path_straight_length_weight: " << param.load_path_straight_length_weight << std::endl;
        }
        else {
            param.load_path_straight_length_weight = 1;
            std::cerr << "无法找到车参 load_path_straight_length_weight ，赋予默认值: " << param.load_path_straight_length_weight << std::endl;
        }

        if (veh_param.HasMember("load_path_curvature_weight") && veh_param["load_path_curvature_weight"].IsInt()) {
            param.load_path_curvature_weight = veh_param["load_path_curvature_weight"].GetInt();
            std::cout << "param.load_path_curvature_weight: " << param.load_path_curvature_weight << std::endl;
        }
        else {
            param.load_path_curvature_weight = 1;
            std::cerr << "无法找到车参 load_path_curvature_weight ，赋予默认值: " << param.load_path_curvature_weight << std::endl;
        }

        // 路径规划参数
        if (veh_param.HasMember("out_put_path_dense") && veh_param["out_put_path_dense"].IsInt()) {
            param.out_put_path_dense = veh_param["out_put_path_dense"].GetInt();
            std::cout << "param.out_put_path_dense: " << param.out_put_path_dense << std::endl;
        }
        else {
            param.out_put_path_dense = 50; // 路径点密度默认值(mm)
            std::cerr << "无法找到车参 out_put_path_dense ，赋予默认值: " << param.out_put_path_dense << std::endl;
        }

        if (veh_param.HasMember("search_range") && veh_param["search_range"].IsInt()) {
            param.search_range = veh_param["search_range"].GetInt();
            std::cout << "param.search_range: " << param.search_range << std::endl;
        }
        else {
            param.search_range = 5000; // 搜索范围默认值(mm)
            std::cerr << "无法找到车参 search_range ，赋予默认值: " << param.search_range << std::endl;
        }

        if (veh_param.HasMember("jump_dense") && veh_param["jump_dense"].IsInt()) {
            param.jump_dense = veh_param["jump_dense"].GetInt();
            std::cout << "param.jump_dense: " << param.jump_dense << std::endl;
        }
        else {
            param.jump_dense = 100;
            std::cerr << "无法找到车参 jump_dense ，赋予默认值: " << param.jump_dense << std::endl;
        }

        if (veh_param.HasMember("length_weight") && veh_param["length_weight"].IsInt()) {
            param.length_weight = veh_param["length_weight"].GetInt();
            std::cout << "param.length_weight: " << param.length_weight << std::endl;
        }
        else {
            param.length_weight = 1;
            std::cerr << "无法找到车参 length_weight ，赋予默认值: " << param.length_weight << std::endl;
        }

        if (veh_param.HasMember("critical_length") && veh_param["critical_length"].IsInt()) {
            param.critical_length = veh_param["critical_length"].GetInt();
            std::cout << "param.critical_length: " << param.critical_length << std::endl;
        }
        else {
            param.critical_length = 5000;
            std::cerr << "无法找到车参 critical_length ，赋予默认值: " << param.critical_length << std::endl;
        }

        if (veh_param.HasMember("curvature_weight") && veh_param["curvature_weight"].IsInt()) {
            param.curvature_weight = veh_param["curvature_weight"].GetInt();
            std::cout << "param.curvature_weight: " << param.curvature_weight << std::endl;
        }
        else {
            param.curvature_weight = 1;
            std::cerr << "无法找到车参 curvature_weight ，赋予默认值: " << param.curvature_weight << std::endl;
        }

        // 场景特定直线长度参数
        if (veh_param.HasMember("min_straight_length_depart") && veh_param["min_straight_length_depart"].IsInt()) {
            param.min_straight_length_depart = veh_param["min_straight_length_depart"].GetInt();
            std::cout << "param.min_straight_length_depart: " << param.min_straight_length_depart << std::endl;
        }
        else {
            param.min_straight_length_depart = 1000;
            std::cerr << "无法找到车参 min_straight_length_depart ，赋予默认值: " << param.min_straight_length_depart << std::endl;
        }

        if (veh_param.HasMember("max_straight_length_depart") && veh_param["max_straight_length_depart"].IsInt()) {
            param.max_straight_length_depart = veh_param["max_straight_length_depart"].GetInt();
            std::cout << "param.max_straight_length_depart: " << param.max_straight_length_depart << std::endl;
        }
        else {
            param.max_straight_length_depart = 5000;
            std::cerr << "无法找到车参 max_straight_length_depart ，赋予默认值: " << param.max_straight_length_depart << std::endl;
        }

        if (veh_param.HasMember("delta_straight_length_depart") && veh_param["delta_straight_length_depart"].IsInt()) {
            param.delta_straight_length_depart = veh_param["delta_straight_length_depart"].GetInt();
            std::cout << "param.delta_straight_length_depart: " << param.delta_straight_length_depart << std::endl;
        }
        else {
            param.delta_straight_length_depart = 500;
            std::cerr << "无法找到车参 delta_straight_length_depart ，赋予默认值: " << param.delta_straight_length_depart << std::endl;
        }

        if (veh_param.HasMember("min_straight_length_wait") && veh_param["min_straight_length_wait"].IsInt()) {
            param.min_straight_length_wait = veh_param["min_straight_length_wait"].GetInt();
            std::cout << "param.min_straight_length_wait: " << param.min_straight_length_wait << std::endl;
        }
        else {
            param.min_straight_length_wait = 1000;
            std::cerr << "无法找到车参 min_straight_length_wait ，赋予默认值: " << param.min_straight_length_wait << std::endl;
        }

        if (veh_param.HasMember("max_straight_length_wait") && veh_param["max_straight_length_wait"].IsInt()) {
            param.max_straight_length_wait = veh_param["max_straight_length_wait"].GetInt();
            std::cout << "param.max_straight_length_wait: " << param.max_straight_length_wait << std::endl;
        }
        else {
            param.max_straight_length_wait = 5000;
            std::cerr << "无法找到车参 max_straight_length_wait ，赋予默认值: " << param.max_straight_length_wait << std::endl;
        }

        if (veh_param.HasMember("delta_straight_length_wait") && veh_param["delta_straight_length_wait"].IsInt()) {
            param.delta_straight_length_wait = veh_param["delta_straight_length_wait"].GetInt();
            std::cout << "param.delta_straight_length_wait: " << param.delta_straight_length_wait << std::endl;
        }
        else {
            param.delta_straight_length_wait = 500;
            std::cerr << "无法找到车参 delta_straight_length_wait ，赋予默认值: " << param.delta_straight_length_wait << std::endl;
        }

        if (veh_param.HasMember("min_straight_length_load") && veh_param["min_straight_length_load"].IsInt()) {
            param.min_straight_length_load = veh_param["min_straight_length_load"].GetInt();
            std::cout << "param.min_straight_length_load: " << param.min_straight_length_load << std::endl;
        }
        else {
            param.min_straight_length_load = 1000;
            std::cerr << "无法找到车参 min_straight_length_load ，赋予默认值: " << param.min_straight_length_load << std::endl;
        }

        if (veh_param.HasMember("max_straight_length_load") && veh_param["max_straight_length_load"].IsInt()) {
            param.max_straight_length_load = veh_param["max_straight_length_load"].GetInt();
            std::cout << "param.max_straight_length_load: " << param.max_straight_length_load << std::endl;
        }
        else {
            param.max_straight_length_load = 5000;
            std::cerr << "无法找到车参 max_straight_length_load ，赋予默认值: " << param.max_straight_length_load << std::endl;
        }

        if (veh_param.HasMember("delta_straight_length_load") && veh_param["delta_straight_length_load"].IsInt()) {
            param.delta_straight_length_load = veh_param["delta_straight_length_load"].GetInt();
            std::cout << "param.delta_straight_length_load: " << param.delta_straight_length_load << std::endl;
        }
        else {
            param.delta_straight_length_load = 500;
            std::cerr << "无法找到车参 delta_straight_length_load ，赋予默认值: " << param.delta_straight_length_load << std::endl;
        }
        std::cout << "车辆参数解析完成" << std::endl;
    }

    // 解析规划模式(planning_mode)
    if (doc.HasMember("Planning_Mode") && doc["Planning_Mode"].IsInt()) {
        planning_info.planning_mode = doc["Planning_Mode"].GetInt();
        std::cout << "解析 Planning_Mode: " << planning_info.planning_mode << std::endl;
    }

    if (doc.HasMember("Machine_Borders")) {
        cout << "解析 Machine_Borders 中" << endl;
        Value& val = doc["Machine_Borders"];
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
            planning_info.machine_borders.emplace_back(inner_border);
        }
    }

    if (doc.HasMember("Wall_Borders")) {
        cout << "解析 Wall_Borders 中" << endl;
        Value& val = doc["Wall_Borders"];
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
            planning_info.wall_borders.emplace_back(inner_border);
        }
    }

    return planning_info;
}

string LoadAreaPathVecWaypoint2json(std::tuple<bool, GlobalPlanning::Point, GlobalPlanning::Path, GlobalPlanning::Path, GlobalPlanning::Path>& result) {
    cout << "enter LoadAreaPathVecWaypoint2json" << endl;

    time_t start_time, end_time;
    time(&start_time);
    rapidjson::StringBuffer                    strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);

    std::cout << "开始写json" << std::endl;
    writer.StartObject();
    std::cout << "执行完代码 writer.StartObject();" << std::endl;

    // 写入操作结果状态
    bool success = std::get<0>(result);
    writer.Key("Success");
    writer.Bool(success);
    std::cout << "执行完代码 写入success状态" << std::endl;

    // 写入起始点信息
    GlobalPlanning::Point wait_point = std::get<1>(result);
    writer.Key("Wait_Point");
    writer.StartObject();
    writer.Key("x");
    writer.Double(wait_point.x);
    writer.Key("y");
    writer.Double(wait_point.y);
    writer.Key("z");
    writer.Double(wait_point.z);
    writer.Key("yaw");
    writer.Double(wait_point.yaw);
    writer.EndObject();
    std::cout << "执行完代码 写入Wait_Point" << std::endl;

    // 处理三条路径：成功时写入实际数据，失败时写入空数组
    if (success) {
        // 获取三条路径
        GlobalPlanning::Path path_r1 = std::get<2>(result);
        GlobalPlanning::Path path_r2 = std::get<3>(result);
        GlobalPlanning::Path path_r3 = std::get<4>(result);

        // 写入Path1
        writer.Key("Path1");
        writer.StartArray();
        for (const auto& point : path_r1.points) {
            writer.StartObject();
            writer.Key("x");
            writer.Double(point.x);
            writer.Key("y");
            writer.Double(point.y);
            writer.Key("z");
            writer.Double(point.z);
            writer.Key("yaw");
            writer.Double(point.yaw);
            writer.Key("curvature");
            writer.Double(point.curvature);
            writer.Key("direction");
            writer.Int(point.direction);
            writer.Key("attribute");
            writer.Int(4);
            writer.EndObject();
        }
        writer.EndArray();
        std::cout << "执行完代码 写入Path1路径" << std::endl;

        // 写入Path2
        writer.Key("Path2");
        writer.StartArray();
        for (const auto& point : path_r2.points) {
            writer.StartObject();
            writer.Key("x");
            writer.Double(point.x);
            writer.Key("y");
            writer.Double(point.y);
            writer.Key("z");
            writer.Double(point.z);
            writer.Key("yaw");
            writer.Double(point.yaw);
            writer.Key("curvature");
            writer.Double(point.curvature);
            writer.Key("direction");
            writer.Int(point.direction);
            writer.Key("attribute");
            writer.Int(4);
            writer.EndObject();
        }
        writer.EndArray();
        std::cout << "执行完代码 写入Path2路径" << std::endl;

        // 写入Path3
        writer.Key("Path3");
        writer.StartArray();
        for (const auto& point : path_r3.points) {
            writer.StartObject();
            writer.Key("x");
            writer.Double(point.x);
            writer.Key("y");
            writer.Double(point.y);
            writer.Key("z");
            writer.Double(point.z);
            writer.Key("yaw");
            writer.Double(point.yaw);
            writer.Key("curvature");
            writer.Double(point.curvature);
            writer.Key("direction");
            writer.Int(point.direction);
            writer.Key("attribute");
            writer.Int(4);
            writer.EndObject();
        }
        writer.EndArray();
        std::cout << "执行完代码 写入Path3路径" << std::endl;
    }
    else {
        // 失败时写入空数组
        writer.Key("Path1");
        writer.StartArray();
        writer.EndArray();

        writer.Key("Path2");
        writer.StartArray();
        writer.EndArray();

        writer.Key("Path3");
        writer.StartArray();
        writer.EndArray();


        std::cout << "执行完代码 写入错误信息和空路径数组" << std::endl;
    }

    writer.EndObject();
    std::cout << "执行完代码 writer.EndObject();" << std::endl;

    // 使用全局变量存储JSON字符串
    GlobalVariable::getInstance()->SetGlobalStr(strbuf.GetString());
    std::cout << "执行完代码 SetGlobalStr" << std::endl;

    // 获取当前时间戳
    auto         currentTime = chrono::system_clock::now();
    time_t       timestamp   = chrono::system_clock::to_time_t(currentTime);
    stringstream ss;
    ss << put_time(localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
    string timeStr = ss.str();

    // 构造文件路径并写入
    string   filePath = timeStr + "_load_area_path_output.json";
    ofstream outputFile(filePath);
    std::cout << "执行完代码 ofstream outputFile(filePath);" << std::endl;
    outputFile << GlobalVariable::getInstance()->GetGlobalStr();
    std::cout << "执行完代码 写入文件" << std::endl;
    outputFile.close();

    cout << "加载区域路径JSON生成完成 " << timeStr << endl;
    time(&end_time);

    // 记录操作日志
    {
        unique_lock<shared_mutex> lock(GlobalVariable::getInstance()->record_file_write_lock);
        ofstream                  record;
        std::string               folderPath  = "record_file";
        std::string               logFilePath = folderPath + "/LoadAreaPath_record.txt";
        if (!fs::exists(folderPath)) {
            try {
                fs::create_directory(folderPath);
            } catch (const fs::filesystem_error& e) {
                std::cerr << "创建日志目录失败: " << e.what() << std::endl;
            }
        }
        record.open(logFilePath, ios_base::app);
        record << timeStr << " ，处理完加载区域路径请求"
               << "，成功状态: " << (success ? "成功" : "失败") << " ，库版本号:G_V1.4.0.20250310_beta" << endl;
        record.close();
    }

    // 从全局变量获取并返回JSON字符串
    return GlobalVariable::getInstance()->GetGlobalStr();
}


} // namespace Parser
} // namespace GlobalPlanning

#endif // HELPER_H
