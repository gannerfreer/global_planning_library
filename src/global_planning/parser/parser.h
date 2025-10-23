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
#include <tuple>

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
            if (val.HasMember("yaw")) {
                veh_start_end.start_point.yaw = val["yaw"].GetFloat();
                if (veh_start_end.start_point.yaw < 0) {
                    veh_start_end.start_point.yaw += 360.0;
                }
                else if (veh_start_end.start_point.yaw > 360.0) {
                    veh_start_end.start_point.yaw -= 360.0;
                }
            }
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

            if (val.HasMember("wheel_base") && val["wheel_base"].IsNumber()) {
                veh_start_end.veh_param.wheel_base = val["wheel_base"].GetDouble();
                cout << "veh_start_end.veh_param.wheel_base " << veh_start_end.veh_param.wheel_base << endl;
            }
            else {
                veh_start_end.veh_param.wheel_base = 5.15;
                cout << "无法找到车参 wheel_base ，即将赋予默认值 5.15" << endl;
            }

            if (val.HasMember("heavy_forward_max_steering")) {
                veh_start_end.veh_param.heavy_forward_max_steering = val["heavy_forward_max_steering"].GetDouble() * M_PI / 180.0;
            }
            else {
                veh_start_end.veh_param.heavy_forward_max_steering = 27.24 * M_PI / 180.0;
                cout << "无法找到车参 heavy_forward_max_steering ，即将赋予默认值 27.24 * M_PI / 180.0" << endl;
            }

            if (val.HasMember("heavy_backward_max_steering")) {
                veh_start_end.veh_param.heavy_backward_max_steering = val["heavy_backward_max_steering"].GetDouble() * M_PI / 180.0;
            }
            else {
                veh_start_end.veh_param.heavy_backward_max_steering = 22.39 * M_PI / 180.0;
                cout << "无法找到车参 heavy_backward_max_steering ，即将赋予默认值 22.39 * M_PI / 180.0" << endl;
            }

            if (val.HasMember("light_backward_max_steering")) {
                veh_start_end.veh_param.light_backward_max_steering = val["light_backward_max_steering"].GetDouble() * M_PI / 180.0;
            }
            else {
                veh_start_end.veh_param.light_backward_max_steering = 27.24 * M_PI / 180.0;
                cout << "无法找到车参 light_backward_max_steering ，即将赋予默认值 27.24 * M_PI / 180.0" << endl;
            }

            if (val.HasMember("light_forward_max_steering")) {
                veh_start_end.veh_param.light_forward_max_steering = val["light_forward_max_steering"].GetDouble() * M_PI / 180.0;
            }
            else {
                veh_start_end.veh_param.light_forward_max_steering = 30.63 * M_PI / 180.0;
                cout << "无法找到车参 light_forward_max_steering ，即将赋予默认值 30.63 * M_PI / 180.0" << endl;
            }

            if (val.HasMember("safe_margin_bound") && val["safe_margin_bound"].IsNumber()) {
                veh_start_end.veh_param.safe_margin_bound = val["safe_margin_bound"].GetDouble();
                cout << "veh_start_end.veh_param.safe_margin_bound " << veh_start_end.veh_param.safe_margin_bound << endl;
            }
            else {
                veh_start_end.veh_param.safe_margin_bound = 0.0;
                cout << "无法找到车参 safe_margin_bound ，即将赋予默认值 0" << endl;
            }

            if (val.HasMember("safe_margin_wall") && val["safe_margin_wall"].IsNumber()) {
                veh_start_end.veh_param.safe_margin_wall = val["safe_margin_wall"].GetDouble();
                cout << "veh_start_end.veh_param.safe_margin_wall " << veh_start_end.veh_param.safe_margin_wall << endl;
            }
            else {
                veh_start_end.veh_param.safe_margin_wall = 0.5;
                cout << "无法找到车参 safe_margin_wall ，即将赋予默认值 0.5" << endl;
            }


            if (val.HasMember("veh_center_2_side") && val["veh_center_2_side"].IsNumber()) {
                veh_start_end.veh_param.veh_center_2_side = val["veh_center_2_side"].GetDouble();
                cout << "veh_start_end.veh_param.veh_center_2_side " << veh_start_end.veh_param.veh_center_2_side << endl;
            }
            else {
                veh_start_end.veh_param.veh_center_2_side = 1.90;
                cout << "无法找到车参 veh_center_2_side ，即将赋予默认值 1.90" << endl;
            }

            if (val.HasMember("veh_center_2_front") && val["veh_center_2_front"].IsNumber()) {
                veh_start_end.veh_param.veh_center_2_front = val["veh_center_2_front"].GetDouble();
                cout << "veh_start_end.veh_param.veh_center_2_front " << veh_start_end.veh_param.veh_center_2_front << endl;
            }
            else {
                veh_start_end.veh_param.veh_center_2_front = 7.10;
                cout << "无法找到车参 veh_center_2_front ，即将赋予默认值 7.10" << endl;
            }

            if (val.HasMember("safe_margin_obstacle") && val["safe_margin_obstacle"].IsNumber()) {
                veh_start_end.veh_param.safe_margin_obstacle = val["safe_margin_obstacle"].GetDouble();
                cout << "veh_start_end.veh_param.safe_margin_obstacle " << veh_start_end.veh_param.safe_margin_obstacle << endl;
            }
            else {
                veh_start_end.veh_param.safe_margin_obstacle = 1.0;
                cout << "无法找到车参 safe_margin_obstacle ，即将赋予默认值 2.0" << endl;
            }

            if (val.HasMember("veh_center_2_rear_bound") && val["veh_center_2_rear_bound"].IsNumber()) {
                veh_start_end.veh_param.veh_center_2_rear_bound = val["veh_center_2_rear_bound"].GetDouble();
                cout << "veh_start_end.veh_param.veh_center_2_rear_bound " << veh_start_end.veh_param.veh_center_2_rear_bound << endl;
            }
            else {
                veh_start_end.veh_param.veh_center_2_rear_bound = 2.65;
                cout << "无法找到车参 veh_center_2_rear_bound ，即将赋予默认值 2.65" << endl;
            }


            if (val.HasMember("delta_dist") && val["delta_dist"].IsNumber()) {
                veh_start_end.veh_param.delta_dist = val["delta_dist"].GetDouble();
                cout << "veh_start_end.veh_param.delta_dist " << veh_start_end.veh_param.delta_dist << endl;
            }
            else {
                veh_start_end.veh_param.delta_dist = 1.0;
                cout << "无法找到车参 delta_dist ，即将赋予默认值 1.0" << endl;
            }

            if (val.HasMember("grid_dist") && val["grid_dist"].IsNumber()) {
                veh_start_end.veh_param.grid_dist = val["grid_dist"].GetDouble();
                cout << "veh_start_end.veh_param.grid_dist " << veh_start_end.veh_param.grid_dist << endl;
            }
            else {
                veh_start_end.veh_param.grid_dist = 0.7;
                cout << "无法找到车参 grid_dist ，即将赋予默认值 0.7" << endl;
            }


            if (val.HasMember("path_error_term") && val["path_error_term"].IsNumber()) {
                veh_start_end.veh_param.path_error_term = val["path_error_term"].GetDouble();
                cout << "veh_start_end.veh_param.path_error_term " << veh_start_end.veh_param.path_error_term << endl;
            }
            else {
                veh_start_end.veh_param.path_error_term = 0.0;
                cout << "无法找到车参 path_error_term ，即将赋予默认值 0.0" << endl;
            }

            if (val.HasMember("grid_angle") && val["grid_angle"].IsNumber()) {
                veh_start_end.veh_param.grid_angle = val["grid_angle"].GetDouble() * M_PI / 180.0;
                cout << "veh_start_end.veh_param.grid_angle " << veh_start_end.veh_param.grid_angle << endl;
            }
            else {
                veh_start_end.veh_param.grid_angle = 1.0 * M_PI / 180.0;
                cout << "无法找到车参 grid_angle ，即将赋予默认值 1.0 * M_PI / 180.0" << endl;
            }

            if (val.HasMember("hybridastar_step_length") && val["hybridastar_step_length"].IsNumber()) {
                veh_start_end.veh_param.hybridastar_step_length = val["hybridastar_step_length"].GetDouble();
                cout << "veh_start_end.veh_param.hybridastar_step_length " << veh_start_end.veh_param.hybridastar_step_length << endl;
            }
            else {
                veh_start_end.veh_param.hybridastar_step_length = 1.0;
                cout << "无法找到车参 hybridastar_step_length ，即将赋予默认值 1.0" << endl;
            }

            if (val.HasMember("path_curvature_term") && val["path_curvature_term"].IsNumber()) {
                veh_start_end.veh_param.path_curvature_term = val["path_curvature_term"].GetDouble();
                cout << "veh_start_end.veh_param.path_curvature_term " << veh_start_end.veh_param.path_curvature_term << endl;
            }
            else {
                veh_start_end.veh_param.path_curvature_term = 0.0;
                cout << "无法找到车参 path_curvature_term ，即将赋予默认值 0.0" << endl;
            }

            if (val.HasMember("switch_penalty") && val["switch_penalty"].IsNumber()) {
                veh_start_end.veh_param.switch_penalty = val["switch_penalty"].GetDouble();
                cout << "veh_start_end.veh_param.switch_penalty " << veh_start_end.veh_param.switch_penalty << endl;
            }
            else {
                veh_start_end.veh_param.switch_penalty = 10;
                cout << "无法找到车参 switch_penalty ，即将赋予默认值 10" << endl;
            }

            if (val.HasMember("forward_penalty") && val["forward_penalty"].IsNumber()) {
                veh_start_end.veh_param.forward_penalty = val["forward_penalty"].GetDouble();
                cout << "veh_start_end.veh_param.forward_penalty " << veh_start_end.veh_param.forward_penalty << endl;
            }
            else {
                veh_start_end.veh_param.forward_penalty = 1.0;
                cout << "无法找到车参 forward_penalty ，即将赋予默认值 1.0" << endl;
            }


            if (val.HasMember("path_smoothness_term") && val["path_smoothness_term"].IsNumber()) {
                veh_start_end.veh_param.path_smoothness_term = val["path_smoothness_term"].GetDouble();
                cout << "veh_start_end.veh_param.path_smoothness_term " << veh_start_end.veh_param.path_smoothness_term << endl;
            }
            else {
                veh_start_end.veh_param.path_smoothness_term = 0.2;
                cout << "无法找到车参 path_smoothness_term ，即将赋予默认值 0.2" << endl;
            }

            if (val.HasMember("backward_penalty") && val["backward_penalty"].IsNumber()) {
                veh_start_end.veh_param.backward_penalty = val["backward_penalty"].GetDouble();
                cout << "veh_start_end.veh_param.backward_penalty " << veh_start_end.veh_param.backward_penalty << endl;
            }
            else {
                veh_start_end.veh_param.backward_penalty = 5.5;
                cout << "无法找到车参 backward_penalty ，即将赋予默认值 5.5" << endl;
            }

            if (val.HasMember("turnning_penalty") && val["turnning_penalty"].IsNumber()) {
                veh_start_end.veh_param.turnning_penalty = val["turnning_penalty"].GetDouble();
                cout << "veh_start_end.veh_param.turnning_penalty " << veh_start_end.veh_param.turnning_penalty << endl;
            }
            else {
                veh_start_end.veh_param.turnning_penalty = 2.468;
                cout << "无法找到车参 turnning_penalty ，即将赋予默认值 2.468" << endl;
            }

            if (val.HasMember("angle_discrete_num") && val["angle_discrete_num"].IsNumber()) {
                veh_start_end.veh_param.angle_discrete_num = val["angle_discrete_num"].GetUint();
                cout << "veh_start_end.veh_param.angle_discrete_num " << veh_start_end.veh_param.angle_discrete_num << endl;
            }
            else {
                veh_start_end.veh_param.angle_discrete_num = 3;
                cout << "无法找到车参 angle_discrete_num ，即将赋予默认值 3" << endl;
            }

            if (val.HasMember("max_fitting_radius") && val["max_fitting_radius"].IsNumber()) {
                veh_start_end.veh_param.max_fitting_radius = val["max_fitting_radius"].GetDouble();
                cout << "veh_start_end.veh_param.max_fitting_radius " << veh_start_end.veh_param.max_fitting_radius << endl;
            }
            else {
                veh_start_end.veh_param.max_fitting_radius = 100;
                cout << "无法找到车参 max_fitting_radius ，即将赋予默认值 100" << endl;
            }

            if (val.HasMember("max_iterations_opti") && val["max_iterations_opti"].IsNumber()) {
                veh_start_end.veh_param.max_iterations_opti = val["max_iterations_opti"].GetDouble();
                cout << "veh_start_end.veh_param.max_iterations_opti " << veh_start_end.veh_param.max_iterations_opti << endl;
            }
            else {
                veh_start_end.veh_param.max_iterations_opti = 1000;
                cout << "无法找到车参 max_iterations_opti ，即将赋予默认值 1000" << endl;
            }


            if (val.HasMember("cusp_extension_distance") && val["cusp_extension_distance"].IsNumber()) {
                veh_start_end.veh_param.cusp_extension_distance = val["cusp_extension_distance"].GetFloat();
                cout << "veh_start_end.veh_param.cusp_extension_distance " << veh_start_end.veh_param.cusp_extension_distance << endl;
            }
            else {
                veh_start_end.veh_param.cusp_extension_distance = 3.0;
                cout << "无法找到车参 cusp_extension_distance ，即将赋予默认值 3.0" << endl;
            }

            if (val.HasMember("linear_preferred_distance") && val["linear_preferred_distance"].IsNumber()) {
                veh_start_end.veh_param.linear_preferred_distance = val["linear_preferred_distance"].GetDouble();
                cout << "veh_start_end.veh_param.linear_preferred_distance " << veh_start_end.veh_param.linear_preferred_distance << endl;
            }
            else {
                veh_start_end.veh_param.linear_preferred_distance = 3.0;
                cout << "无法找到车参 linear_preferred_distance ，即将赋予默认值 3.0" << endl;
            }

            if (val.HasMember("safe_margin_error") && val["safe_margin_error"].IsNumber()) {
                veh_start_end.veh_param.safe_margin_error = val["safe_margin_error"].GetDouble();
                cout << "veh_start_end.veh_param.safe_margin_error " << veh_start_end.veh_param.safe_margin_error << endl;
            }
            else {
                veh_start_end.veh_param.safe_margin_error = 0.0;
                cout << "无法找到车参 safe_margin_error ，即将赋予默认值 0.0" << endl;
            }

            if (val.HasMember("speed_error_term") && val["speed_error_term"].IsNumber()) {
                veh_start_end.veh_param.speed_error_term = val["speed_error_term"].GetFloat();
                cout << "veh_start_end.veh_param.speed_error_term " << veh_start_end.veh_param.speed_error_term << endl;
            }
            else {
                veh_start_end.veh_param.speed_error_term = 0.01;
                cout << "无法找到车参 speed_error_term ，即将赋予默认值 0.01" << endl;
            }


            if (val.HasMember("speed_smooth_term") && val["speed_smooth_term"].IsNumber()) {
                veh_start_end.veh_param.speed_smooth_term = val["speed_smooth_term"].GetFloat();
                cout << "veh_start_end.veh_param.speed_smooth_term " << veh_start_end.veh_param.speed_smooth_term << endl;
            }
            else {
                veh_start_end.veh_param.speed_smooth_term = 0.2;
                cout << "无法找到车参 speed_smooth_term ，即将赋予默认值 0.2" << endl;
            }

            if (val.HasMember("max_acceleration") && val["max_acceleration"].IsNumber()) {
                veh_start_end.veh_param.max_acceleration = val["max_acceleration"].GetFloat();
                cout << "veh_start_end.veh_param.max_acceleration " << veh_start_end.veh_param.max_acceleration << endl;
            }
            else {
                veh_start_end.veh_param.max_acceleration = 0.3;
                cout << "无法找到车参 max_acceleration ，即将赋予默认值 0.3" << endl;
            }

            if (val.HasMember("min_acceleration") && val["min_acceleration"].IsNumber()) {
                veh_start_end.veh_param.min_acceleration = val["min_acceleration"].GetFloat();
                cout << "veh_start_end.veh_param.min_acceleration " << veh_start_end.veh_param.min_acceleration << endl;
            }
            else {
                veh_start_end.veh_param.min_acceleration = -0.4;
                cout << "无法找到车参 min_acceleration ，即将赋予默认值 -0.4" << endl;
            }

            if (val.HasMember("light_reverse_speed") && val["light_reverse_speed"].IsNumber()) {
                veh_start_end.veh_param.light_reverse_speed = val["light_reverse_speed"].GetFloat();
                cout << "veh_start_end.veh_param.light_reverse_speed " << veh_start_end.veh_param.light_reverse_speed << endl;
            }
            else {
                veh_start_end.veh_param.light_reverse_speed = 1.5;
                cout << "无法找到车参 light_reverse_speed ，即将赋予默认值 1.5" << endl;
            }

            if (val.HasMember("heavy_reverse_speed") && val["heavy_reverse_speed"].IsNumber()) {
                veh_start_end.veh_param.heavy_reverse_speed = val["heavy_reverse_speed"].GetFloat();
                cout << "veh_start_end.veh_param.heavy_reverse_speed " << veh_start_end.veh_param.heavy_reverse_speed << endl;
            }
            else {
                veh_start_end.veh_param.heavy_reverse_speed = 0.5;
                cout << "无法找到车参 heavy_reverse_speed ，即将赋予默认值 0.5" << endl;
            }


            if (val.HasMember("narrow_road_speed_limit") && val["narrow_road_speed_limit"].IsNumber()) {
                veh_start_end.veh_param.narrow_road_speed_limit = val["narrow_road_speed_limit"].GetFloat();
                cout << "veh_start_end.veh_param.narrow_road_speed_limit " << veh_start_end.veh_param.narrow_road_speed_limit << endl;
            }
            else {
                cout << "无法找到车参 narrow_road_speed_limit ，即将赋予默认值 3" << endl;
                veh_start_end.veh_param.narrow_road_speed_limit = 3;
            }

            if (val.HasMember("slope_road_speed_limit") && val["slope_road_speed_limit"].IsNumber()) {
                veh_start_end.veh_param.slope_road_speed_limit = val["slope_road_speed_limit"].GetFloat();
                cout << "veh_start_end.veh_param.slope_road_speed_limit " << veh_start_end.veh_param.slope_road_speed_limit << endl;
            }
            else {
                cout << "无法找到车参 slope_road_speed_limit ，即将赋予默认值 3.0" << endl;
                veh_start_end.veh_param.slope_road_speed_limit = 3.0;
            }

            if (val.HasMember("intersection_road_speed_limit") && val["intersection_road_speed_limit"].IsNumber()) {
                veh_start_end.veh_param.intersection_road_speed_limit = val["intersection_road_speed_limit"].GetFloat();
                cout << "veh_start_end.veh_param.intersection_road_speed_limit " << veh_start_end.veh_param.intersection_road_speed_limit << endl;
            }
            else {
                cout << "无法找到车参 intersection_road_speed_limit ，即将赋予默认值 3.0" << endl;
                veh_start_end.veh_param.intersection_road_speed_limit = 3.0;
            }

            if (val.HasMember("bumpy_road_speed_limit") && val["bumpy_road_speed_limit"].IsNumber()) {
                veh_start_end.veh_param.bumpy_road_speed_limit = val["bumpy_road_speed_limit"].GetFloat();
                cout << "veh_start_end.veh_param.bumpy_road_speed_limit " << veh_start_end.veh_param.bumpy_road_speed_limit << endl;
            }
            else {
                cout << "无法找到车参 bumpy_road_speed_limit ，即将赋予默认值 3.0" << endl;
                veh_start_end.veh_param.bumpy_road_speed_limit = 3.0;
            }

            if (val.HasMember("regular_road_speed_limit") && val["regular_road_speed_limit"].IsNumber()) {
                veh_start_end.veh_param.regular_road_speed_limit = val["regular_road_speed_limit"].GetFloat();
                cout << "veh_start_end.veh_param.regular_road_speed_limit " << veh_start_end.veh_param.regular_road_speed_limit << endl;
            }
            else {
                cout << "无法找到车参 regular_road_speed_limit ，即将赋予默认值 3.0" << endl;
                veh_start_end.veh_param.regular_road_speed_limit = 3.0;
            }


            if (val.HasMember("vehicle_code") && val["vehicle_code"].IsNumber()) {
                veh_start_end.veh_param.vehicle_code = val["vehicle_code"].GetUint();
                cout << "veh_start_end.veh_param.vehicle_code " << veh_start_end.veh_param.vehicle_code << endl;
            }
            else {
                cout << "无法找到车参 vehicle_code ，即将赋予默认值 9999" << endl;
                veh_start_end.veh_param.vehicle_code = 9999;
            }

            if (val.HasMember("uniform_compaction_enable") && val["uniform_compaction_enable"].IsBool()) {
                veh_start_end.veh_param.uniform_compaction_enable = val["uniform_compaction_enable"].GetBool();
                cout << "veh_start_end.veh_param.uniform_compaction_enable " << veh_start_end.veh_param.uniform_compaction_enable << endl;
            }
            else {
                cout << "无法找到车参 uniform_compaction_enable ，即将赋予默认值 true" << endl;
                veh_start_end.veh_param.uniform_compaction_enable = true;
            }


            if (val.HasMember("is_light") && val["is_light"].IsBool()) {
                veh_start_end.veh_param.is_light = val["is_light"].GetBool();
                cout << "veh_start_end.veh_param.is_light " << veh_start_end.veh_param.is_light << endl;
            }
            else {
                cout << "无法找到车参 is_light ，即将赋予默认值 false" << endl;
                veh_start_end.veh_param.is_light = false;
            }


            if (val.HasMember("speed_limit_level") && val["speed_limit_level"].IsNumber() && val["speed_limit_level"].GetUint() >= 1 && val["speed_limit_level"].GetUint() <= 3) {
                veh_start_end.veh_param.speed_limit_level = static_cast<SpeedLimitLevel>(val["speed_limit_level"].GetUint());
                cout << "veh_start_end.veh_param.speed_limit_level " << static_cast<int>(veh_start_end.veh_param.speed_limit_level) << endl;
            }
            else {
                cout << "无法找到车参 speed_limit_level ，即将赋予默认值 three" << endl;
                veh_start_end.veh_param.speed_limit_level = SpeedLimitLevel::three;
            }

            if (val.HasMember("L2") && val["L2"].IsNumber()) {
                veh_start_end.veh_param.L2 = val["L2"].GetUint();
            }
            else {
                cout << "无法找到车参 L2 ，即将赋予默认值 8" << endl;
                veh_start_end.veh_param.L2 = 8;
            }

            if (val.HasMember("L3") && val["L3"].IsNumber()) {
                veh_start_end.veh_param.L3 = val["L3"].GetUint();
            }
            else {
                cout << "无法找到车参 L3 ，即将赋予默认值 8" << endl;
                veh_start_end.veh_param.L3 = 8;
            }


            if (val.HasMember("rs_min_length") && val["rs_min_length"].IsNumber()) {
                veh_start_end.veh_param.rs_min_length = val["rs_min_length"].GetFloat();
            }
            else {
                cout << "无法找到车参 rs_min_length ，即将赋予默认值 1" << endl;
                veh_start_end.veh_param.rs_min_length = 1;
            }

            if (val.HasMember("L1") && val["L1"].IsNumber()) {
                veh_start_end.veh_param.L1 = val["L1"].GetFloat();
            }
            else {
                cout << "无法找到车参 L1 ，即将赋予默认值 3" << endl;
                veh_start_end.veh_param.L1 = 3;
            }

            if (val.HasMember("offset_distance") && val["offset_distance"].IsNumber()) {
                veh_start_end.veh_param.offset_distance = val["offset_distance"].GetFloat();
                veh_start_end.veh_param.offset_distance = std::min(std::max(veh_start_end.veh_param.offset_distance, float(0)), float(0.5));
            }
            else {
                cout << "无法找到车参 offset_distance ，即将赋予默认值 0.3" << endl;
                veh_start_end.veh_param.offset_distance = 0.3;
            }

            if (val.HasMember("max_steering_wheel_speed") && val["max_steering_wheel_speed"].IsNumber()) {
                veh_start_end.veh_param.max_steering_wheel_speed = val["max_steering_wheel_speed"].GetFloat();
            }
            else {
                cout << "无法找到车参 max_steering_wheel_speed ，即将赋予默认值 0.1396" << endl;
                veh_start_end.veh_param.max_steering_wheel_speed = 0.1396;
            }


            if (val.HasMember("sample_num") && val["sample_num"].IsNumber()) {
                veh_start_end.veh_param.sample_num = val["sample_num"].GetUint();
            }
            else {
                cout << "无法找到车参 sample_num ，即将赋予默认值 40" << endl;
                veh_start_end.veh_param.sample_num = 40;
            }

            if (val.HasMember("plan_time") && val["plan_time"].IsNumber()) {
                veh_start_end.veh_param.plan_time = val["plan_time"].GetFloat();
            }
            else {
                cout << "无法找到车参 plan_time ，即将赋予默认值 0.2" << endl;
                veh_start_end.veh_param.plan_time = 0.2;
            }

            if (val.HasMember("dis_threshold") && val["dis_threshold"].IsNumber()) {
                veh_start_end.veh_param.dis_threshold = val["dis_threshold"].GetFloat();
            }
            else {
                cout << "无法找到车参 dis_threshold ，即将赋予默认值 2.0" << endl;
                veh_start_end.veh_param.dis_threshold = 2.0;
            }

            if (val.HasMember("w_deviation")) {
                veh_start_end.veh_param.w_deviation = val["w_deviation"].GetFloat();
            }
            else {
                cout << "无法找到车参 w_deviation ，即将赋予默认值 0.00012" << endl;
                veh_start_end.veh_param.w_deviation = 0.00012;
            }

            if (val.HasMember("w_curvature")) {
                veh_start_end.veh_param.w_curvature = val["w_curvature"].GetFloat();
            }
            else {
                cout << "无法找到车参 w_curvature ，即将赋予默认值 100" << endl;
                veh_start_end.veh_param.w_curvature = 100;
            }

            if (val.HasMember("w_curvature_change")) {
                veh_start_end.veh_param.w_curvature_change = val["w_curvature_change"].GetFloat();
            }
            else {
                cout << "无法找到车参 w_curvature_change ，即将赋予默认值 1" << endl;
                veh_start_end.veh_param.w_curvature_change = 1;
            }

            if (val.HasMember("ipopt_max_offset")) {
                veh_start_end.veh_param.ipopt_max_offset = val["ipopt_max_offset"].GetFloat();
            }
            else {
                cout << "无法找到车参 ipopt_max_offset ，即将赋予默认值 3" << endl;
                veh_start_end.veh_param.ipopt_max_offset = 3;
            }

            if (val.HasMember("lat_dis_threshold")) {
                veh_start_end.veh_param.lat_dis_threshold = val["lat_dis_threshold"].GetFloat();
            }
            else {
                cout << "无法找到车参 lat_dis_threshold ，即将赋予默认值 0.2" << endl;
                veh_start_end.veh_param.lat_dis_threshold = 0.2;
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
            veh_start_end.machine_borders.emplace_back(inner_border);
        }
    }

    if (doc.HasMember("dynamic_border") && doc["dynamic_border"].IsArray()) {
        cout << "解析 dynamic_border 中" << endl;
        const Value&         dynamicBorderArray = doc["dynamic_border"];
        vector<_BorderPoint> dynamicBorderPoints;

        for (SizeType i = 0; i < dynamicBorderArray.Size(); i++) {
            const Value& borderPoint = dynamicBorderArray[i];

            // 验证必要的字段是否存在且类型正确
            if (!borderPoint.IsObject() || !borderPoint.HasMember("x") || !borderPoint["x"].IsDouble() || !borderPoint.HasMember("y") || !borderPoint["y"].IsDouble()) {
                cerr << "dynamic_border 点数据不完整或格式错误，索引: " << i << endl;
                continue; // 跳过错误的点，继续解析其他点
            }

            _BorderPoint temp_point;
            temp_point.x = borderPoint["x"].GetDouble();
            temp_point.y = borderPoint["y"].GetDouble();


            // 可以选择处理经纬度信息
            // if (borderPoint.HasMember("longitude") && borderPoint["longitude"].IsDouble()) {
            //     // 处理经度
            // }
            // if (borderPoint.HasMember("latitude") && borderPoint["latitude"].IsDouble()) {
            //     // 处理纬度
            // }

            dynamicBorderPoints.push_back(temp_point);
        }

        // 将解析到的动态边界点添加到planning_info
        veh_start_end.wall_borders.emplace_back(dynamicBorderPoints);
        cout << "解析 dynamic_border 完毕，共 " << dynamicBorderPoints.size() << " 个点" << endl;
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
                pp.x   = pathPointsArray[j]["x"].GetDouble();
                pp.y   = pathPointsArray[j]["y"].GetDouble();
                pp.yaw = pathPointsArray[j]["yaw"].GetDouble() / 180.0 * M_PI;
                if (pp.yaw >= 2 * M_PI) {
                    pp.yaw -= 2 * M_PI;
                }
                else if (pp.yaw < 0) {
                    pp.yaw += 2 * M_PI;
                }
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
        record << timeStr << " ，处理完规划请求，请求号：" << plan_obj.key_ << "，车辆编号：" << plan_obj.vehicle_code_ << "  规划库版本号:G_V1.11.3.20250912" << endl;
        record.close();
    }

    return GlobalVariable::getInstance()->GetGlobalStr();
}


bool GetMap(char* parea) {
    try {
        Document doc;
        // 解析JSON时可能出现异常
        doc.Parse(parea);
        if (doc.HasParseError()) {
            unsigned int error  = doc.GetParseError();
            size_t       offset = doc.GetErrorOffset();
            throw std::runtime_error("JSON解析错误: 错误代码=" + std::to_string(error) + ", 偏移位置=" + std::to_string(offset));
        }

        // 确保有allocator可用
        doc.GetAllocator();

        // 清空所有的地图边界、参考路径、relation等数据
        GlobalVariable::getInstance()->ClearData();

        // 解析border_points
        if (!doc.HasMember("external_border") || !doc["external_border"].IsArray()) {
            throw std::runtime_error("JSON数据中缺少有效的external_border数组");
        }

        const Value&         borderPointsArray = doc["external_border"];
        _BorderPoint         bp;
        vector<_BorderPoint> v_bp;

        for (SizeType i = 0; i < borderPointsArray.Size(); i++) {
            const Value& point = borderPointsArray[i];
            // 检查点数据是否完整
            if (!point.IsObject() || !point.HasMember("x") || !point["x"].IsDouble() || !point.HasMember("y") || !point["y"].IsDouble() || !point.HasMember("z") || !point["z"].IsDouble() || !point.HasMember("type") || !point["type"].IsInt()) {
                throw std::runtime_error("边界点数据不完整或格式错误，索引: " + std::to_string(i));
            }

            bp.x    = point["x"].GetDouble();
            bp.y    = point["y"].GetDouble();
            bp.z    = point["z"].GetDouble();
            bp.type = static_cast<unsigned char>(point["type"].GetInt());

            if (bp.type == 0) {
                v_bp.emplace_back(bp);
            }
        }

        GlobalVariable::getInstance()->SetMapBorder(v_bp);
        std::cout << "解析border_points完毕,边界点数量：" << v_bp.size() << std::endl;

        // 解析reference_trajs
        if (!doc.HasMember("reference_trajs") || !doc["reference_trajs"].IsArray()) {
            throw std::runtime_error("JSON数据中缺少有效的reference_trajs数组");
        }

        const Value&                  trajsArray = doc["reference_trajs"];
        std::map<int, _SingleTraj>    m_traj_self_driving, m_traj_human_driving;
        map<int, vector<_SingleTraj>> input_paths;
        map<int, vector<_SingleTraj>> output_paths;
        _SingleTraj                   traj;
        _TrajectoryPoint              tp;
        int                           traj_type   = -1;
        double                        speed_limit = -1;
        int                           guid_type   = 0;
        int                           area_id   = -1;

        for (SizeType i = 0; i < trajsArray.Size(); i++) {
            const Value& trajObj = trajsArray[i];
            // 检查轨迹对象基本结构
            if (!trajObj.IsObject() || !trajObj.HasMember("id") || !trajObj["id"].IsInt() || !trajObj.HasMember("trajectory") || !trajObj["trajectory"].IsArray()) {
                throw std::runtime_error("轨迹数据不完整或格式错误，索引: " + std::to_string(i));
            }

            traj.trajectory.clear();
            traj.id = trajObj["id"].GetInt();

            // 处理可选字段
            traj_type = trajObj.HasMember("type") && trajObj["type"].IsInt() ? trajObj["type"].GetInt() : 2;

            speed_limit = trajObj.HasMember("speed_limit") && trajObj["speed_limit"].IsDouble() ? trajObj["speed_limit"].GetDouble() : -1;

            guid_type = trajObj.HasMember("guid_type") && trajObj["guid_type"].IsInt() ? trajObj["guid_type"].GetInt() : 0;

            area_id = trajObj.HasMember("area_id") && trajObj["area_id"].IsInt() ? trajObj["area_id"].GetInt() : -1;


            const Value& trajPointsArray = trajObj["trajectory"];
            for (SizeType j = 0; j < trajPointsArray.Size(); j++) {
                const Value& point = trajPointsArray[j];
                // 检查轨迹点数据是否完整
                if (!point.IsObject() || !point.HasMember("x") || !point["x"].IsDouble() || !point.HasMember("y") || !point["y"].IsDouble() || !point.HasMember("z") || !point["z"].IsDouble() || !point.HasMember("yaw") || !point["yaw"].IsDouble() || !point.HasMember("curvature") || !point["curvature"].IsDouble() || !point.HasMember("attribute") || !point["attribute"].IsInt() || !point.HasMember("direction") || !point["direction"].IsInt()) {
                    throw std::runtime_error("轨迹点数据不完整或格式错误，轨迹索引: " + std::to_string(i) + ", 点索引: " + std::to_string(j));
                }

                tp.x           = point["x"].GetDouble();
                tp.y           = point["y"].GetDouble();
                tp.z           = point["z"].GetDouble();
                tp.yaw         = point["yaw"].GetDouble() / 180.0 * M_PI;
                tp.curvature   = point["curvature"].GetDouble();
                tp.attribute   = static_cast<PointAttribute>(point["attribute"].GetInt());
                tp.direction   = static_cast<unsigned char>(point["direction"].GetInt());
                tp.speed_limit = speed_limit;
                traj.trajectory.push_back(tp);
            }

            // 根据轨迹类型分类
            if (traj_type == 2) {
                m_traj_self_driving[traj.id]  = traj;
                m_traj_human_driving[traj.id] = traj;
            }
            else if (traj_type == 0) {
                m_traj_self_driving[traj.id] = traj;
            }
            else if (traj_type == 1) {
                m_traj_human_driving[traj.id] = traj;
            }
            else {
                throw std::runtime_error("未知的轨迹类型: " + std::to_string(traj_type) + ", 轨迹ID: " + std::to_string(traj.id));
            }

            // 根据引导类型分类
            if (guid_type == 1) {
                input_paths[area_id].push_back(traj);
            }
            else if (guid_type == 2) {
                output_paths[area_id].push_back(traj);
            }
        }

        // 保存解析后的轨迹数据
        GlobalVariable::getInstance()->SetAllSelfDrivingReferencelines(m_traj_self_driving);
        GlobalVariable::getInstance()->SetAllHumanDrivingReferencelines(m_traj_human_driving);
        GlobalVariable::getInstance()->SetInGuidingPaths(input_paths);
        GlobalVariable::getInstance()->SetOutGuidingPaths(output_paths);

        // 解析relation
        if (!doc.HasMember("relation") || !doc["relation"].IsObject()) {
            throw std::runtime_error("JSON数据中缺少有效的relation对象");
        }

        const Value&                    relationObj = doc["relation"];
        std::map<int, std::vector<int>> m_relation_self_driving;  // 无人车专用relation
        std::map<int, std::vector<int>> m_relation_human_driving; // 有人车专用relation
        int                             key;
        std::vector<int>                relVec;

        for (Value::ConstMemberIterator itr = relationObj.MemberBegin(); itr != relationObj.MemberEnd(); ++itr) {
            try {
                key = std::stoi(itr->name.GetString());
            } catch (const std::exception& e) {
                throw std::runtime_error("relation键转换为整数失败: " + std::string(itr->name.GetString()) + ", 错误: " + e.what());
            }

            const Value& relArray = itr->value;
            if (!relArray.IsArray()) {
                throw std::runtime_error("relation值不是数组，键: " + std::to_string(key));
            }

            relVec.clear();
            for (SizeType k = 0; k < relArray.Size(); k++) {
                if (!relArray[k].IsInt()) {
                    throw std::runtime_error("relation数组元素不是整数，键: " + std::to_string(key) + ", 索引: " + std::to_string(k));
                }
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

        // 保存解析后的relation数据
        GlobalVariable::getInstance()->SetSelfDrivingReferencelineRelation(m_relation_self_driving);
        GlobalVariable::getInstance()->SetHumanDrivingReferencelineRelation(m_relation_human_driving);

        // 创建映射和有向图
        GlobalVariable::getInstance()->CreateSelfDrivingSequenceMapping(GlobalVariable::getInstance()->GetAllSelfDrivingReferencelines());
        GlobalVariable::getInstance()->CreateSelfDrivingDirectedGraph(GlobalVariable::getInstance()->GetSelfDrivingReferencelineRelation());
        cout << "**********************地图更新完毕***************************" << endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "解析地图数据时发生错误: " << e.what() << std::endl;
        // 发生异常时清理可能的部分数据
        GlobalVariable::getInstance()->ClearData();
        return false;
    } catch (...) {
        std::cerr << "解析地图数据时发生未知错误" << std::endl;
        // 发生未知异常时清理可能的部分数据
        GlobalVariable::getInstance()->ClearData();
        return false;
    }
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
            if (humanVechicleInfo.pos.yaw < 0) {
                humanVechicleInfo.pos.yaw += 360.0;
            }
            else if (humanVechicleInfo.pos.yaw > 360.0) {
                humanVechicleInfo.pos.yaw -= 360.0;
            }
            cout << "humanVechicleInfo.pos.yaw:" << humanVechicleInfo.pos.yaw << endl;
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
        record << timeStr << " ，处理完规划请求，请求号：" << obj.key_ << "  库版本号:G_V1.11.3.20250912" << endl;
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

    // 解析等待点(queue_point) - 兼容字段不存在或为空的情况
    if (doc.HasMember("queue_point") && doc["queue_point"].IsObject()) {
        const rapidjson::Value& queue_point = doc["queue_point"];

        // 解析x坐标，兼容字段不存在或类型错误
        if (queue_point.HasMember("x") && queue_point["x"].IsDouble()) {
            planning_info.wait_point.x = queue_point["x"].GetDouble();
            std::cout << "解析 queue_point.x: " << planning_info.wait_point.x << std::endl;
        }
        else {
            planning_info.wait_point.x = 0.0;
            std::cerr << "wait_point.x 不存在或格式错误，赋予默认值: " << planning_info.wait_point.x << std::endl;
        }

        // 解析y坐标
        if (queue_point.HasMember("y") && queue_point["y"].IsDouble()) {
            planning_info.wait_point.y = queue_point["y"].GetDouble();
            std::cout << "解析 queue_point.y: " << planning_info.wait_point.y << std::endl;
        }
        else {
            planning_info.wait_point.y = 0.0;
            std::cerr << "queue_point.y 不存在或格式错误，赋予默认值: " << planning_info.wait_point.y << std::endl;
        }

        // 解析z坐标
        if (queue_point.HasMember("z") && queue_point["z"].IsDouble()) {
            planning_info.wait_point.z = queue_point["z"].GetDouble();
            std::cout << "解析 queue_point.z: " << planning_info.wait_point.z << std::endl;
        }
        else {
            planning_info.wait_point.z = 0.0;
            std::cerr << "queue_point.z 不存在或格式错误，赋予默认值: " << planning_info.wait_point.z << std::endl;
        }

        // 解析yaw角度
        if (queue_point.HasMember("yaw") && queue_point["yaw"].IsDouble()) {
            planning_info.wait_point.yaw = queue_point["yaw"].GetDouble();
            if (planning_info.wait_point.yaw < 0) {
                planning_info.wait_point.yaw += 360.0;
            }
            else if (planning_info.wait_point.yaw > 360.0) {
                planning_info.wait_point.yaw -= 360.0;
            }
            std::cout << "解析 queue_point.yaw: " << planning_info.wait_point.yaw << std::endl;
        }
        else {
            planning_info.wait_point.yaw = 0.0;
            std::cerr << "queue_point.yaw 不存在或格式错误，赋予默认值: " << planning_info.wait_point.yaw << std::endl;
        }
    }
    else {
        std::cout << "queue_point 为空" << std::endl;
    }

    // 解析加载点(load_point)
    if (doc.HasMember("load_point") && doc["load_point"].IsObject()) {
        const rapidjson::Value& load_point = doc["load_point"];

        if (load_point.HasMember("x") && load_point["x"].IsDouble()) {
            planning_info.load_point.x = load_point["x"].GetDouble();
            std::cout << "解析 load_point.x: " << planning_info.load_point.x << std::endl;
        }
        else {
            planning_info.load_point.x = 0.0;
            std::cerr << "load_point.x 不存在或格式错误，赋予默认值: " << planning_info.load_point.x << std::endl;
        }

        if (load_point.HasMember("y") && load_point["y"].IsDouble()) {
            planning_info.load_point.y = load_point["y"].GetDouble();
            std::cout << "解析 load_point.y: " << planning_info.load_point.y << std::endl;
        }
        else {
            planning_info.load_point.y = 0.0;
            std::cerr << "load_point.y 不存在或格式错误，赋予默认值: " << planning_info.load_point.y << std::endl;
        }

        if (load_point.HasMember("z") && load_point["z"].IsDouble()) {
            planning_info.load_point.z = load_point["z"].GetDouble();
            std::cout << "解析 load_point.z: " << planning_info.load_point.z << std::endl;
        }
        else {
            planning_info.load_point.z = 0.0;
            std::cerr << "load_point.z 不存在或格式错误，赋予默认值: " << planning_info.load_point.z << std::endl;
        }

        if (load_point.HasMember("yaw") && load_point["yaw"].IsDouble()) {
            planning_info.load_point.yaw = load_point["yaw"].GetDouble();
            if (planning_info.load_point.yaw < 0) {
                planning_info.load_point.yaw += 360.0;
            }
            else if (planning_info.load_point.yaw > 360.0) {
                planning_info.load_point.yaw -= 360.0;
            }
            std::cout << "解析 load_point.yaw: " << planning_info.load_point.yaw << std::endl;
        }
        else {
            planning_info.load_point.yaw = 0.0;
            std::cerr << "load_point.yaw 不存在或格式错误，赋予默认值: " << planning_info.load_point.yaw << std::endl;
        }
    }


    if (doc.HasMember("m_Veh_Param")) {
        cout << "解析 m_Veh_Param 中" << endl;
        Value& val = doc["m_Veh_Param"];
        if (val.IsObject()) {
            // 装载排队点自动生成算法参数


            if (val.HasMember("remove_dis") && val["remove_dis"].IsNumber()) {
                planning_info.remove_dis = val["remove_dis"].GetDouble();
                cout << "planning_info.remove_dis " << planning_info.remove_dis << endl;
            }
            else {
                planning_info.remove_dis = 5.0;
                cout << "无法找到车参 remove_dis ，即将赋予默认值 5.0" << endl;
            }

            if (val.HasMember("safe_margin_front") && val["safe_margin_front"].IsNumber()) {
                planning_info.safe_margin_front = val["safe_margin_front"].GetDouble();
                cout << "planning_info.safe_margin_front " << planning_info.safe_margin_front << endl;
            }
            else {
                planning_info.safe_margin_front = 2.0;
                cout << "无法找到车参 safe_margin_front ，即将赋予默认值 2.0" << endl;
            }

            if (val.HasMember("safe_margin_rear") && val["safe_margin_rear"].IsNumber()) {
                planning_info.safe_margin_rear = val["safe_margin_rear"].GetDouble();
                cout << "planning_info.safe_margin_rear " << planning_info.safe_margin_rear << endl;
            }
            else {
                planning_info.safe_margin_rear = 2.0;
                cout << "无法找到车参 safe_margin_rear ，即将赋予默认值 2.0" << endl;
            }

            if (val.HasMember("safe_margin_side") && val["safe_margin_side"].IsNumber()) {
                planning_info.safe_margin_side = val["safe_margin_side"].GetDouble();
                cout << "planning_info.safe_margin_side " << planning_info.safe_margin_side << endl;
            }
            else {
                planning_info.safe_margin_side = 1.3;
                cout << "无法找到车参 safe_margin_side ，即将赋予默认值 1.3" << endl;
            }


            // 曲线长度参数
            if (val.HasMember("max_curve_length") && val["max_curve_length"].IsInt()) {
                planning_info.max_curve_length = val["max_curve_length"].GetInt();
                std::cout << "planning_info.max_curve_length: " << planning_info.max_curve_length << std::endl;
            }
            else {
                planning_info.max_curve_length = 80.0;
                std::cerr << "无法找到车参 max_curve_length ，赋予默认值: " << planning_info.max_curve_length << std::endl;
            }

            if (val.HasMember("min_curve_length") && val["min_curve_length"].IsInt()) {
                planning_info.min_curve_length = val["min_curve_length"].GetInt();
                std::cout << "planning_info.min_curve_length: " << planning_info.min_curve_length << std::endl;
            }
            else {
                planning_info.min_curve_length = 15;
                std::cerr << "无法找到车参 min_curve_length ，赋予默认值: " << planning_info.min_curve_length << std::endl;
            }

            if (val.HasMember("delta_curve_length") && val["delta_curve_length"].IsInt()) {
                planning_info.delta_curve_length = val["delta_curve_length"].GetInt();
                std::cout << "planning_info.delta_curve_length: " << planning_info.delta_curve_length << std::endl;
            }
            else {
                planning_info.delta_curve_length = 5;
                std::cerr << "无法找到车参 delta_curve_length ，赋予默认值: " << planning_info.delta_curve_length << std::endl;
            }

            // 车辆基础参数
            if (val.HasMember("wheel_base_length") && val["wheel_base_length"].IsDouble()) {
                planning_info.wheel_base_length = val["wheel_base_length"].GetDouble();
                std::cout << "planning_info.wheel_base_length: " << planning_info.wheel_base_length << std::endl;
            }
            else {
                planning_info.wheel_base_length = 5.15; // 典型轴距默认值(mm)
                std::cerr << "无法找到车参 wheel_base_length ，赋予默认值: " << planning_info.wheel_base_length << std::endl;
            }

            if (val.HasMember("center2side") && val["center2side"].IsDouble()) {
                planning_info.center2side = val["center2side"].GetDouble();
                std::cout << "planning_info.center2side: " << planning_info.center2side << std::endl;
            }
            else {
                planning_info.center2side = 1.885; // 典型轮距默认值(mm)
                std::cerr << "无法找到车参 center2side ，赋予默认值: " << planning_info.center2side << std::endl;
            }

            // 直线长度参数
            if (val.HasMember("max_straight_length") && val["max_straight_length"].IsInt()) {
                planning_info.max_straight_length = val["max_straight_length"].GetInt();
                std::cout << "planning_info.max_straight_length: " << planning_info.max_straight_length << std::endl;
            }
            else {
                planning_info.max_straight_length = 8;
                std::cerr << "无法找到车参 max_straight_length ，赋予默认值: " << planning_info.max_straight_length << std::endl;
            }

            if (val.HasMember("min_straight_length") && val["min_straight_length"].IsInt()) {
                planning_info.min_straight_length = val["min_straight_length"].GetInt();
                std::cout << "planning_info.min_straight_length: " << planning_info.min_straight_length << std::endl;
            }
            else {
                planning_info.min_straight_length = 2;
                std::cerr << "无法找到车参 min_straight_length ，赋予默认值: " << planning_info.min_straight_length << std::endl;
            }

            if (val.HasMember("delta_straight_length") && val["delta_straight_length"].IsInt()) {
                planning_info.delta_straight_length = val["delta_straight_length"].GetInt();
                std::cout << "planning_info.delta_straight_length: " << planning_info.delta_straight_length << std::endl;
            }
            else {
                planning_info.delta_straight_length = 2;
                std::cerr << "无法找到车参 delta_straight_length ，赋予默认值: " << planning_info.delta_straight_length << std::endl;
            }

            // 转向角参数
            if (val.HasMember("max_steering_angle") && val["max_steering_angle"].IsInt()) {
                planning_info.max_steering_angle = val["max_steering_angle"].GetInt();
                std::cout << "planning_info.max_steering_angle: " << planning_info.max_steering_angle << std::endl;
            }
            else {
                planning_info.max_steering_angle = 28; // 典型最大转向角(度)
                std::cerr << "无法找到车参 max_steering_angle ，赋予默认值: " << planning_info.max_steering_angle << std::endl;
            }

            if (val.HasMember("min_steering_angle") && val["min_steering_angle"].IsInt()) {
                planning_info.min_steering_angle = val["min_steering_angle"].GetInt();
                std::cout << "planning_info.min_steering_angle: " << planning_info.min_steering_angle << std::endl;
            }
            else {
                planning_info.min_steering_angle = -28; // 典型最小转向角(度)
                std::cerr << "无法找到车参 min_steering_angle ，赋予默认值: " << planning_info.min_steering_angle << std::endl;
            }

            if (val.HasMember("delta_steering_angle") && val["delta_steering_angle"].IsInt()) {
                planning_info.delta_steering_angle = val["delta_steering_angle"].GetInt();
                std::cout << "planning_info.delta_steering_angle: " << planning_info.delta_steering_angle << std::endl;
            }
            else {
                planning_info.delta_steering_angle = 4;
                std::cerr << "无法找到车参 delta_steering_angle ，赋予默认值: " << planning_info.delta_steering_angle << std::endl;
            }

            if (val.HasMember("standard_steering_angle") && val["standard_steering_angle"].IsInt()) {
                planning_info.standard_steering_angle = val["standard_steering_angle"].GetInt();
                std::cout << "planning_info.standard_steering_angle: " << planning_info.standard_steering_angle << std::endl;
            }
            else {
                planning_info.standard_steering_angle = 14; // 标准转向角(直行)
                std::cerr << "无法找到车参 standard_steering_angle ，赋予默认值: " << planning_info.standard_steering_angle << std::endl;
            }

            // 权重参数
            if (val.HasMember("weight_length") && val["weight_length"].IsInt()) {
                planning_info.weight_length = val["weight_length"].GetInt();
                std::cout << "planning_info.weight_length: " << planning_info.weight_length << std::endl;
            }
            else {
                planning_info.weight_length = 2;
                std::cerr << "无法找到车参 weight_length ，赋予默认值: " << planning_info.weight_length << std::endl;
            }

            if (val.HasMember("weight_curve") && val["weight_curve"].IsInt()) {
                planning_info.weight_curve = val["weight_curve"].GetInt();
                std::cout << "planning_info.weight_curve: " << planning_info.weight_curve << std::endl;
            }
            else {
                planning_info.weight_curve = 1.5;
                std::cerr << "无法找到车参 weight_curve ，赋予默认值: " << planning_info.weight_curve << std::endl;
            }

            if (val.HasMember("load_path_straight_length_weight") && val["load_path_straight_length_weight"].IsInt()) {
                planning_info.load_path_straight_length_weight = val["load_path_straight_length_weight"].GetInt();
                std::cout << "planning_info.load_path_straight_length_weight: " << planning_info.load_path_straight_length_weight << std::endl;
            }
            else {
                planning_info.load_path_straight_length_weight = 1;
                std::cerr << "无法找到车参 load_path_straight_length_weight ，赋予默认值: " << planning_info.load_path_straight_length_weight << std::endl;
            }

            if (val.HasMember("load_path_curvature_weight") && val["load_path_curvature_weight"].IsInt()) {
                planning_info.load_path_curvature_weight = val["load_path_curvature_weight"].GetInt();
                std::cout << "planning_info.load_path_curvature_weight: " << planning_info.load_path_curvature_weight << std::endl;
            }
            else {
                planning_info.load_path_curvature_weight = 1;
                std::cerr << "无法找到车参 load_path_curvature_weight ，赋予默认值: " << planning_info.load_path_curvature_weight << std::endl;
            }

            if (val.HasMember("collision_weight") && val["collision_weight"].IsInt()) {
                planning_info.collision_weight = val["collision_weight"].GetInt();
                std::cout << "planning_info.collision_weight: " << planning_info.collision_weight << std::endl;
            }
            else {
                planning_info.collision_weight = 0.75;
                std::cerr << "无法找到车参 collision_weight ，赋予默认值: " << planning_info.collision_weight << std::endl;
            }

            // 路径规划参数
            if (val.HasMember("out_put_path_dense") && val["out_put_path_dense"].IsInt()) {
                planning_info.out_put_path_dense = val["out_put_path_dense"].GetInt();
                std::cout << "planning_info.out_put_path_dense: " << planning_info.out_put_path_dense << std::endl;
            }
            else {
                planning_info.out_put_path_dense = 1; // 路径点密度默认值(mm)
                std::cerr << "无法找到车参 out_put_path_dense ，赋予默认值: " << planning_info.out_put_path_dense << std::endl;
            }

            if (val.HasMember("search_range") && val["search_range"].IsInt()) {
                planning_info.search_range = val["search_range"].GetInt();
                std::cout << "planning_info.search_range: " << planning_info.search_range << std::endl;
            }
            else {
                planning_info.search_range = 80; // 搜索范围默认值(mm)
                std::cerr << "无法找到车参 search_range ，赋予默认值: " << planning_info.search_range << std::endl;
            }

            if (val.HasMember("jump_dense") && val["jump_dense"].IsInt()) {
                planning_info.jump_dense = val["jump_dense"].GetInt();
                std::cout << "planning_info.jump_dense: " << planning_info.jump_dense << std::endl;
            }
            else {
                planning_info.jump_dense = 1;
                std::cerr << "无法找到车参 jump_dense ，赋予默认值: " << planning_info.jump_dense << std::endl;
            }

            if (val.HasMember("length_weight") && val["length_weight"].IsInt()) {
                planning_info.length_weight = val["length_weight"].GetInt();
                std::cout << "planning_info.length_weight: " << planning_info.length_weight << std::endl;
            }
            else {
                planning_info.length_weight = 1;
                std::cerr << "无法找到车参 length_weight ，赋予默认值: " << planning_info.length_weight << std::endl;
            }

            if (val.HasMember("critical_length") && val["critical_length"].IsInt()) {
                planning_info.critical_length = val["critical_length"].GetInt();
                std::cout << "planning_info.critical_length: " << planning_info.critical_length << std::endl;
            }
            else {
                planning_info.critical_length = 30;
                std::cerr << "无法找到车参 critical_length ，赋予默认值: " << planning_info.critical_length << std::endl;
            }

            if (val.HasMember("curvature_weight") && val["curvature_weight"].IsInt()) {
                planning_info.curvature_weight = val["curvature_weight"].GetInt();
                std::cout << "planning_info.curvature_weight: " << planning_info.curvature_weight << std::endl;
            }
            else {
                planning_info.curvature_weight = 1;
                std::cerr << "无法找到车参 curvature_weight ，赋予默认值: " << planning_info.curvature_weight << std::endl;
            }

            // 场景特定直线长度参数
            if (val.HasMember("min_straight_length_depart") && val["min_straight_length_depart"].IsInt()) {
                planning_info.min_straight_length_depart = val["min_straight_length_depart"].GetInt();
                std::cout << "planning_info.min_straight_length_depart: " << planning_info.min_straight_length_depart << std::endl;
            }
            else {
                planning_info.min_straight_length_depart = 2;
                std::cerr << "无法找到车参 min_straight_length_depart ，赋予默认值: " << planning_info.min_straight_length_depart << std::endl;
            }

            if (val.HasMember("max_straight_length_depart") && val["max_straight_length_depart"].IsInt()) {
                planning_info.max_straight_length_depart = val["max_straight_length_depart"].GetInt();
                std::cout << "planning_info.max_straight_length_depart: " << planning_info.max_straight_length_depart << std::endl;
            }
            else {
                planning_info.max_straight_length_depart = 10;
                std::cerr << "无法找到车参 max_straight_length_depart ，赋予默认值: " << planning_info.max_straight_length_depart << std::endl;
            }

            if (val.HasMember("delta_straight_length_depart") && val["delta_straight_length_depart"].IsInt()) {
                planning_info.delta_straight_length_depart = val["delta_straight_length_depart"].GetInt();
                std::cout << "planning_info.delta_straight_length_depart: " << planning_info.delta_straight_length_depart << std::endl;
            }
            else {
                planning_info.delta_straight_length_depart = 2;
                std::cerr << "无法找到车参 delta_straight_length_depart ，赋予默认值: " << planning_info.delta_straight_length_depart << std::endl;
            }

            if (val.HasMember("min_straight_length_wait") && val["min_straight_length_wait"].IsInt()) {
                planning_info.min_straight_length_wait = val["min_straight_length_wait"].GetInt();
                std::cout << "planning_info.min_straight_length_wait: " << planning_info.min_straight_length_wait << std::endl;
            }
            else {
                planning_info.min_straight_length_wait = 2;
                std::cerr << "无法找到车参 min_straight_length_wait ，赋予默认值: " << planning_info.min_straight_length_wait << std::endl;
            }

            if (val.HasMember("max_straight_length_wait") && val["max_straight_length_wait"].IsInt()) {
                planning_info.max_straight_length_wait = val["max_straight_length_wait"].GetInt();
                std::cout << "planning_info.max_straight_length_wait: " << planning_info.max_straight_length_wait << std::endl;
            }
            else {
                planning_info.max_straight_length_wait = 6;
                std::cerr << "无法找到车参 max_straight_length_wait ，赋予默认值: " << planning_info.max_straight_length_wait << std::endl;
            }

            if (val.HasMember("delta_straight_length_wait") && val["delta_straight_length_wait"].IsInt()) {
                planning_info.delta_straight_length_wait = val["delta_straight_length_wait"].GetInt();
                std::cout << "planning_info.delta_straight_length_wait: " << planning_info.delta_straight_length_wait << std::endl;
            }
            else {
                planning_info.delta_straight_length_wait = 2;
                std::cerr << "无法找到车参 delta_straight_length_wait ，赋予默认值: " << planning_info.delta_straight_length_wait << std::endl;
            }

            if (val.HasMember("min_straight_length_load") && val["min_straight_length_load"].IsInt()) {
                planning_info.min_straight_length_load = val["min_straight_length_load"].GetInt();
                std::cout << "planning_info.min_straight_length_load: " << planning_info.min_straight_length_load << std::endl;
            }
            else {
                planning_info.min_straight_length_load = 2;
                std::cerr << "无法找到车参 min_straight_length_load ，赋予默认值: " << planning_info.min_straight_length_load << std::endl;
            }

            if (val.HasMember("max_straight_length_load") && val["max_straight_length_load"].IsInt()) {
                planning_info.max_straight_length_load = val["max_straight_length_load"].GetInt();
                std::cout << "planning_info.max_straight_length_load: " << planning_info.max_straight_length_load << std::endl;
            }
            else {
                planning_info.max_straight_length_load = 10;
                std::cerr << "无法找到车参 max_straight_length_load ，赋予默认值: " << planning_info.max_straight_length_load << std::endl;
            }

            if (val.HasMember("delta_straight_length_load") && val["delta_straight_length_load"].IsInt()) {
                planning_info.delta_straight_length_load = val["delta_straight_length_load"].GetInt();
                std::cout << "planning_info.delta_straight_length_load: " << planning_info.delta_straight_length_load << std::endl;
            }
            else {
                planning_info.delta_straight_length_load = 2;
                std::cerr << "无法找到车参 delta_straight_length_load ，赋予默认值: " << planning_info.delta_straight_length_load << std::endl;
            }


            // 车辆hybridA*规划参数
            if (val.HasMember("wheel_base") && val["wheel_base"].IsNumber()) {
                planning_info.veh_param.wheel_base = val["wheel_base"].GetDouble();
                std::cout << "planning_info.veh_param.wheel_base " << planning_info.veh_param.wheel_base << std::endl;
            }
            else {
                planning_info.veh_param.wheel_base = 5.15;
                cout << "无法找到车参 wheel_base ，即将赋予默认值 5.15" << endl;
            }

            if (val.HasMember("heavy_forward_max_steering")) {
                planning_info.veh_param.heavy_forward_max_steering = val["heavy_forward_max_steering"].GetDouble() * M_PI / 180.0;
            }
            else {
                planning_info.veh_param.heavy_forward_max_steering = 27.24 * M_PI / 180.0;
                cout << "无法找到车参 heavy_forward_max_steering ，即将赋予默认值 27.24 * M_PI / 180.0" << endl;
            }

            if (val.HasMember("heavy_backward_max_steering")) {
                planning_info.veh_param.heavy_backward_max_steering = val["heavy_backward_max_steering"].GetDouble() * M_PI / 180.0;
            }
            else {
                planning_info.veh_param.heavy_backward_max_steering = 22.39 * M_PI / 180.0;
                cout << "无法找到车参 heavy_backward_max_steering ，即将赋予默认值 22.39 * M_PI / 180.0" << endl;
            }

            if (val.HasMember("light_backward_max_steering")) {
                planning_info.veh_param.light_backward_max_steering = val["light_backward_max_steering"].GetDouble() * M_PI / 180.0;
            }
            else {
                planning_info.veh_param.light_backward_max_steering = 27.24 * M_PI / 180.0;
                cout << "无法找到车参 light_backward_max_steering ，即将赋予默认值 27.24 * M_PI / 180.0" << endl;
            }

            if (val.HasMember("light_forward_max_steering")) {
                planning_info.veh_param.light_forward_max_steering = val["light_forward_max_steering"].GetDouble() * M_PI / 180.0;
            }
            else {
                planning_info.veh_param.light_forward_max_steering = 30.63 * M_PI / 180.0;
                cout << "无法找到车参 light_forward_max_steering ，即将赋予默认值 30.63 * M_PI / 180.0" << endl;
            }

            if (val.HasMember("safe_margin_bound") && val["safe_margin_bound"].IsNumber()) {
                planning_info.veh_param.safe_margin_bound = val["safe_margin_bound"].GetDouble();
                std::cout << "planning_info.veh_param.safe_margin_bound " << planning_info.veh_param.safe_margin_bound << std::endl;
            }
            else {
                planning_info.veh_param.safe_margin_bound = 0.0;
                cout << "无法找到车参 safe_margin_bound ，即将赋予默认值 0.0" << endl;
            }

            if (val.HasMember("safe_margin_wall") && val["safe_margin_wall"].IsNumber()) {
                planning_info.veh_param.safe_margin_wall = val["safe_margin_wall"].GetDouble();
                std::cout << "planning_info.veh_param.safe_margin_wall " << planning_info.veh_param.safe_margin_wall << std::endl;
            }
            else {
                planning_info.veh_param.safe_margin_wall = 0.5;
                cout << "无法找到车参 safe_margin_wall ，即将赋予默认值 0.5" << endl;
            }


            if (val.HasMember("veh_center_2_side") && val["veh_center_2_side"].IsNumber()) {
                planning_info.veh_param.veh_center_2_side = val["veh_center_2_side"].GetDouble();
                std::cout << "planning_info.veh_param.veh_center_2_side " << planning_info.veh_param.veh_center_2_side << std::endl;
            }
            else {
                planning_info.veh_param.veh_center_2_side = 1.90;
                cout << "无法找到车参 veh_center_2_side ，即将赋予默认值 1.90" << endl;
            }

            if (val.HasMember("veh_center_2_front") && val["veh_center_2_front"].IsNumber()) {
                planning_info.veh_param.veh_center_2_front = val["veh_center_2_front"].GetDouble();
                std::cout << "planning_info.veh_param.veh_center_2_front " << planning_info.veh_param.veh_center_2_front << std::endl;
            }
            else {
                planning_info.veh_param.veh_center_2_front = 7.10;
                cout << "无法找到车参 veh_center_2_front ，即将赋予默认值 7.10" << endl;
            }

            if (val.HasMember("safe_margin_obstacle") && val["safe_margin_obstacle"].IsNumber()) {
                planning_info.veh_param.safe_margin_obstacle = val["safe_margin_obstacle"].GetDouble();
                std::cout << "planning_info.veh_param.safe_margin_obstacle " << planning_info.veh_param.safe_margin_obstacle << std::endl;
            }
            else {
                planning_info.veh_param.safe_margin_obstacle = 1.0;
                cout << "无法找到车参 safe_margin_obstacle ，即将赋予默认值 1.0" << endl;
            }

            if (val.HasMember("veh_center_2_rear_bound") && val["veh_center_2_rear_bound"].IsNumber()) {
                planning_info.veh_param.veh_center_2_rear_bound = val["veh_center_2_rear_bound"].GetDouble();
                std::cout << "planning_info.veh_param.veh_center_2_rear_bound " << planning_info.veh_param.veh_center_2_rear_bound << std::endl;
            }
            else {
                planning_info.veh_param.veh_center_2_rear_bound = 2.65;
                cout << "无法找到车参 veh_center_2_rear_bound ，即将赋予默认值 2.65  " << endl;
            }


            if (val.HasMember("delta_dist") && val["delta_dist"].IsNumber()) {
                planning_info.veh_param.delta_dist = val["delta_dist"].GetDouble();
                std::cout << "planning_info.veh_param.delta_dist " << planning_info.veh_param.delta_dist << std::endl;
            }
            else {
                planning_info.veh_param.delta_dist = 1.0;
                cout << "无法找到车参 delta_dist ，即将赋予默认值 1.0" << endl;
            }

            if (val.HasMember("grid_dist") && val["grid_dist"].IsNumber()) {
                planning_info.veh_param.grid_dist = val["grid_dist"].GetDouble();
                std::cout << "planning_info.veh_param.grid_dist " << planning_info.veh_param.grid_dist << std::endl;
            }
            else {
                planning_info.veh_param.grid_dist = 0.7;
                cout << "无法找到车参 grid_dist ，即将赋予默认值 0.7" << endl;
            }


            if (val.HasMember("path_error_term") && val["path_error_term"].IsNumber()) {
                planning_info.veh_param.path_error_term = val["path_error_term"].GetDouble();
                std::cout << "planning_info.veh_param.path_error_term " << planning_info.veh_param.path_error_term << std::endl;
            }
            else {
                planning_info.veh_param.path_error_term = 0.0;
                cout << "无法找到车参 path_error_term ，即将赋予默认值 0.0" << endl;
            }

            if (val.HasMember("grid_angle") && val["grid_angle"].IsNumber()) {
                planning_info.veh_param.grid_angle = val["grid_angle"].GetDouble() * M_PI / 180.0;
                std::cout << "planning_info.veh_param.grid_angle " << planning_info.veh_param.grid_angle << std::endl;
            }
            else {
                planning_info.veh_param.grid_angle = 1.0 * M_PI / 180.0;
                cout << "无法找到车参 grid_angle ，即将赋予默认值 1.0* M_PI / 180.0" << endl;
            }

            if (val.HasMember("hybridastar_step_length") && val["hybridastar_step_length"].IsNumber()) {
                planning_info.veh_param.hybridastar_step_length = val["hybridastar_step_length"].GetDouble();
                std::cout << "planning_info.veh_param.hybridastar_step_length " << planning_info.veh_param.hybridastar_step_length << std::endl;
            }
            else {
                planning_info.veh_param.hybridastar_step_length = 1.0;
                cout << "无法找到车参 hybridastar_step_length ，即将赋予默认值 1.0" << endl;
            }

            if (val.HasMember("path_curvature_term") && val["path_curvature_term"].IsNumber()) {
                planning_info.veh_param.path_curvature_term = val["path_curvature_term"].GetDouble();
                std::cout << "planning_info.veh_param.path_curvature_term " << planning_info.veh_param.path_curvature_term << std::endl;
            }
            else {
                planning_info.veh_param.path_curvature_term = 0.0;
                cout << "无法找到车参 path_curvature_term ，即将赋予默认值 0.0" << endl;
            }

            if (val.HasMember("switch_penalty") && val["switch_penalty"].IsNumber()) {
                planning_info.veh_param.switch_penalty = val["switch_penalty"].GetDouble();
                std::cout << "planning_info.veh_param.switch_penalty " << planning_info.veh_param.switch_penalty << std::endl;
            }
            else {
                planning_info.veh_param.switch_penalty = 10;
                cout << "无法找到车参 switch_penalty ，即将赋予默认值 10" << endl;
            }

            if (val.HasMember("forward_penalty") && val["forward_penalty"].IsNumber()) {
                planning_info.veh_param.forward_penalty = val["forward_penalty"].GetDouble();
                std::cout << "planning_info.veh_param.forward_penalty " << planning_info.veh_param.forward_penalty << std::endl;
            }
            else {
                planning_info.veh_param.forward_penalty = 1.0;
                cout << "无法找到车参 forward_penalty ，即将赋予默认值 1.0" << endl;
            }


            if (val.HasMember("path_smoothness_term") && val["path_smoothness_term"].IsNumber()) {
                planning_info.veh_param.path_smoothness_term = val["path_smoothness_term"].GetDouble();
                std::cout << "planning_info.veh_param.path_smoothness_term " << planning_info.veh_param.path_smoothness_term << std::endl;
            }
            else {
                planning_info.veh_param.path_smoothness_term = 0.2;
                cout << "无法找到车参 path_smoothness_term ，即将赋予默认值 0.2" << endl;
            }

            if (val.HasMember("backward_penalty") && val["backward_penalty"].IsNumber()) {
                planning_info.veh_param.backward_penalty = val["backward_penalty"].GetDouble();
                std::cout << "planning_info.veh_param.backward_penalty " << planning_info.veh_param.backward_penalty << std::endl;
            }
            else {
                planning_info.veh_param.backward_penalty = 5.5;
                cout << "无法找到车参 backward_penalty ，即将赋予默认值 5.5" << endl;
            }

            if (val.HasMember("turnning_penalty") && val["turnning_penalty"].IsNumber()) {
                planning_info.veh_param.turnning_penalty = val["turnning_penalty"].GetDouble();
                std::cout << "planning_info.veh_param.turnning_penalty " << planning_info.veh_param.turnning_penalty << std::endl;
            }
            else {
                planning_info.veh_param.turnning_penalty = 2.468;
                cout << "无法找到车参 turnning_penalty ，即将赋予默认值 2.468" << endl;
            }

            if (val.HasMember("angle_discrete_num") && val["angle_discrete_num"].IsNumber()) {
                planning_info.veh_param.angle_discrete_num = val["angle_discrete_num"].GetUint();
                std::cout << "planning_info.veh_param.angle_discrete_num " << planning_info.veh_param.angle_discrete_num << std::endl;
            }
            else {
                planning_info.veh_param.angle_discrete_num = 3;
                cout << "无法找到车参 angle_discrete_num ，即将赋予默认值 3" << endl;
            }

            if (val.HasMember("max_fitting_radius") && val["max_fitting_radius"].IsNumber()) {
                planning_info.veh_param.max_fitting_radius = val["max_fitting_radius"].GetDouble();
                std::cout << "planning_info.veh_param.max_fitting_radius " << planning_info.veh_param.max_fitting_radius << std::endl;
            }
            else {
                planning_info.veh_param.max_fitting_radius = 100;
                cout << "无法找到车参 max_fitting_radius ，即将赋予默认值 100" << endl;
            }

            if (val.HasMember("max_iterations_opti") && val["max_iterations_opti"].IsNumber()) {
                planning_info.veh_param.max_iterations_opti = val["max_iterations_opti"].GetDouble();
                std::cout << "planning_info.veh_param.max_iterations_opti " << planning_info.veh_param.max_iterations_opti << std::endl;
            }
            else {
                planning_info.veh_param.max_iterations_opti = 1000;
                cout << "无法找到车参 max_iterations_opti ，即将赋予默认值 1000" << endl;
            }


            if (val.HasMember("cusp_extension_distance") && val["cusp_extension_distance"].IsNumber()) {
                planning_info.veh_param.cusp_extension_distance = val["cusp_extension_distance"].GetFloat();
                std::cout << "planning_info.veh_param.cusp_extension_distance " << planning_info.veh_param.cusp_extension_distance << std::endl;
            }
            else {
                planning_info.veh_param.cusp_extension_distance = 3.0;
                cout << "无法找到车参 cusp_extension_distance ，即将赋予默认值 3.0" << endl;
            }

            if (val.HasMember("linear_preferred_distance") && val["linear_preferred_distance"].IsNumber()) {
                planning_info.veh_param.linear_preferred_distance = val["linear_preferred_distance"].GetDouble();
                std::cout << "planning_info.veh_param.linear_preferred_distance " << planning_info.veh_param.linear_preferred_distance << std::endl;
            }
            else {
                planning_info.veh_param.linear_preferred_distance = 3.0;
                cout << "无法找到车参 linear_preferred_distance ，即将赋予默认值 3.0" << endl;
            }

            if (val.HasMember("safe_margin_error") && val["safe_margin_error"].IsNumber()) {
                planning_info.veh_param.safe_margin_error = val["safe_margin_error"].GetDouble();
                std::cout << "planning_info.veh_param.safe_margin_error " << planning_info.veh_param.safe_margin_error << std::endl;
            }
            else {
                planning_info.veh_param.safe_margin_error = 0.0;
                cout << "无法找到车参 safe_margin_error ，即将赋予默认值 0.0" << endl;
            }


            if (val.HasMember("is_light") && val["is_light"].IsBool()) {
                planning_info.veh_param.is_light = val["is_light"].GetBool();
                cout << "planning_info.veh_param.is_light " << planning_info.veh_param.is_light << endl;
            }
            else {
                cout << "无法找到车参 is_light ，即将赋予默认值 false" << endl;
                planning_info.veh_param.is_light = false;
            }


            if (val.HasMember("rs_min_length") && val["rs_min_length"].IsNumber()) {
                planning_info.veh_param.rs_min_length = val["rs_min_length"].GetFloat();
            }
            else {
                cout << "无法找到车参 rs_min_length ，即将赋予默认值 1" << endl;
                planning_info.veh_param.rs_min_length = 1;
            }


            if (val.HasMember("plan_time") && val["plan_time"].IsNumber()) {
                planning_info.veh_param.plan_time = val["plan_time"].GetFloat();
            }
            else {
                cout << "无法找到车参 plan_time ，即将赋予默认值 0.2" << endl;
                planning_info.veh_param.plan_time = 0.2;
            }

            if (val.HasMember("dis_threshold") && val["dis_threshold"].IsNumber()) {
                planning_info.veh_param.dis_threshold = val["dis_threshold"].GetFloat();
            }
            else {
                cout << "无法找到车参 dis_threshold ，即将赋予默认值 2.0" << endl;
                planning_info.veh_param.dis_threshold = 2.0;
            }

            if (val.HasMember("w_deviation")) {
                planning_info.veh_param.w_deviation = val["w_deviation"].GetFloat();
            }
            else {
                cout << "无法找到车参 w_deviation ，即将赋予默认值 0.00012" << endl;
                planning_info.veh_param.w_deviation = 0.00012;
            }
            if (val.HasMember("w_curvature")) {
                planning_info.veh_param.w_curvature = val["w_curvature"].GetFloat();
            }
            else {
                cout << "无法找到车参 w_curvature ，即将赋予默认值 100" << endl;
                planning_info.veh_param.w_curvature = 100;
            }
            if (val.HasMember("w_curvature_change")) {
                planning_info.veh_param.w_curvature_change = val["w_curvature_change"].GetFloat();
            }
            else {
                cout << "无法找到车参 w_curvature_change ，即将赋予默认值 1" << endl;
                planning_info.veh_param.w_curvature_change = 1;
            }

            std::cout << "车辆参数解析完成" << std::endl;

            if (val.HasMember("ipopt_max_offset")) {
                planning_info.veh_param.ipopt_max_offset = val["ipopt_max_offset"].GetFloat();
            }
            else {
                planning_info.veh_param.ipopt_max_offset = 3;
                cout << "无法找到车参 ipopt_max_offset ，即将赋予默认值 3" << endl;
            }
        }
    }

    // 解析规划模式(planning_mode)
    if (doc.HasMember("execute_mode") && doc["execute_mode"].IsInt()) {
        planning_info.planning_mode = doc["execute_mode"].GetInt();
        std::cout << "解析 execute_mode: " << planning_info.planning_mode << std::endl;
    }

    if (doc.HasMember("excavator_border")) {
        cout << "解析 excavator_border 中" << endl;
        Value& val = doc["excavator_border"];
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

    if (doc.HasMember("dynamic_border") && doc["dynamic_border"].IsArray()) {
        cout << "解析 dynamic_border 中" << endl;
        const Value&         dynamicBorderArray = doc["dynamic_border"];
        vector<_BorderPoint> dynamicBorderPoints;
        cout << "dynamicBorderArray.Size() = " << dynamicBorderArray.Size() << endl;

        for (SizeType i = 0; i < dynamicBorderArray.Size(); i++) {
            const Value& borderPoint = dynamicBorderArray[i];

            // 验证必要的字段是否存在且类型正确
            if (!borderPoint.IsObject() || !borderPoint.HasMember("x") || !borderPoint["x"].IsDouble() || !borderPoint.HasMember("y") || !borderPoint["y"].IsDouble()) {
                cout << "dynamic_border 点数据不完整或格式错误，索引: " << i << endl;
                continue; // 跳过错误的点，继续解析其他点
            }

            _BorderPoint temp_point;
            temp_point.x = borderPoint["x"].GetDouble();
            temp_point.y = borderPoint["y"].GetDouble();
            // temp_point.z    = static_cast<float>(borderPoint["z"].GetDouble()); // 从double转换为float
            // temp_point.type = borderPoint["type"].GetUint();

            // 可以选择处理经纬度信息
            // if (borderPoint.HasMember("longitude") && borderPoint["longitude"].IsDouble()) {
            //     // 处理经度
            // }
            // if (borderPoint.HasMember("latitude") && borderPoint["latitude"].IsDouble()) {
            //     // 处理纬度
            // }

            dynamicBorderPoints.push_back(temp_point);
        }

        // 将解析到的动态边界点添加到planning_info
        planning_info.wall_borders.emplace_back(dynamicBorderPoints);
        cout << "解析 dynamic_border 完毕，共 " << dynamicBorderPoints.size() << " 个点" << endl;
    }

    if (doc.HasMember("area_id") && doc["area_id"].IsInt()) {
        planning_info.area_id = doc["area_id"].GetInt();
        std::cout << "解析 area_id: " << planning_info.area_id << std::endl;
    }
    else {
        planning_info.area_id = -1;
        cout << "无法找到 area_id ，即将赋予默认值 -1" << endl;
    }

    return planning_info;
}

string LoadAreaPathVecWaypoint2json(std::tuple<int, GlobalPlanning::Point, GlobalPlanning::Path, GlobalPlanning::Path, GlobalPlanning::Path>& result) {
    cout << "enter LoadAreaPathVecWaypoint2json" << endl;

    time_t start_time, end_time;
    time(&start_time);
    rapidjson::StringBuffer                    strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);

    std::cout << "开始写json" << std::endl;
    writer.StartObject();
    std::cout << "执行完代码 writer.StartObject();" << std::endl;

    // 写入操作结果状态
    int success = std::get<0>(result);
    if (success == 1) {
        success = 0;
    }
    else {
        success = 1;
    }
    writer.Key("result");
    writer.Int(success);
    std::cout << "执行完代码 写入success状态" << std::endl;

    // 写入起始点信息
    GlobalPlanning::Point wait_point = std::get<1>(result);
    writer.Key("queue_point");
    writer.StartObject();
    writer.Key("x");
    writer.Double(wait_point.x);
    writer.Key("y");
    writer.Double(wait_point.y);
    writer.Key("z");
    writer.Double(wait_point.z);
    writer.Key("yaw");
    writer.Double(wait_point.angle);
    writer.EndObject();
    std::cout << "执行完代码 写入Wait_Point" << std::endl;

    // 处理三条路径：成功时写入实际数据，失败时写入空数组
    if (!success) {
        // 获取三条路径
        GlobalPlanning::Path path_r1 = std::get<2>(result);
        GlobalPlanning::Path path_r2 = std::get<3>(result);
        GlobalPlanning::Path path_r3 = std::get<4>(result);

        // 写入entrance_queue_path
        writer.Key("entrance_queue_path");
        writer.StartArray();
        for (const auto& point : path_r1) {
            writer.StartObject();
            writer.Key("x");
            writer.Double(point.x);
            writer.Key("y");
            writer.Double(point.y);
            writer.Key("z");
            writer.Double(point.z);
            writer.Key("yaw");
            writer.Double(point.angle);
            writer.Key("curvature");
            writer.Double(point.curvature);
            writer.Key("speed_limit");
            writer.Double(100);
            writer.Key("speed");
            writer.Double(0);
            writer.Key("distance");
            writer.Double(0);
            writer.Key("direction");
            writer.Int(point.direction);
            writer.Key("attribute");
            writer.Int(4);
            writer.EndObject();
        }
        writer.EndArray();
        std::cout << "执行完代码 写入Path1路径" << std::endl;

        // 写入entrance_load_path
        writer.Key("entrance_load_path");
        writer.StartArray();
        for (const auto& point : path_r2) {
            writer.StartObject();
            writer.Key("x");
            writer.Double(point.x);
            writer.Key("y");
            writer.Double(point.y);
            writer.Key("z");
            writer.Double(point.z);
            writer.Key("yaw");
            writer.Double(point.angle);
            writer.Key("curvature");
            writer.Double(point.curvature);
            writer.Key("speed_limit");
            writer.Double(100);
            writer.Key("speed");
            writer.Double(0);
            writer.Key("distance");
            writer.Double(0);
            writer.Key("direction");
            writer.Int(point.direction);
            writer.Key("attribute");
            writer.Int(4);
            writer.EndObject();
        }
        writer.EndArray();
        std::cout << "执行完代码 写入Path2路径" << std::endl;

        // 写入exit_queue_path
        writer.Key("exit_queue_path");
        writer.StartArray();
        for (const auto& point : path_r3) {
            writer.StartObject();
            writer.Key("x");
            writer.Double(point.x);
            writer.Key("y");
            writer.Double(point.y);
            writer.Key("z");
            writer.Double(point.z);
            writer.Key("yaw");
            writer.Double(point.angle);
            writer.Key("curvature");
            writer.Double(point.curvature);
            writer.Key("speed_limit");
            writer.Double(100);
            writer.Key("speed");
            writer.Double(0);
            writer.Key("distance");
            writer.Double(0);
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
        writer.Key("entrance_queue_path");
        writer.StartArray();
        writer.EndArray();

        writer.Key("entrance_load_path");
        writer.StartArray();
        writer.EndArray();

        writer.Key("exit_queue_path");
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
               << "，成功状态: " << (success ? "成功" : "失败") << " ，库版本号:G_V1.11.3.20250912" << endl;
        record.close();
    }

    // 从全局变量获取并返回JSON字符串
    return GlobalVariable::getInstance()->GetGlobalStr();
}


} // namespace Parser
} // namespace GlobalPlanning

#endif // HELPER_H
