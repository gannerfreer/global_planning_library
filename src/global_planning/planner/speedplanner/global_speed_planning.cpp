/* ****************************************
 * 作者: yyf(yanyifeng@wicri.org)
 * 日期: 2025/03/03
 * 内容: 完成函数功能实现,完善修改程序逻辑
 * 功能：考虑限速的(可能包含多段前进、后退路段)全局速度规划
 * ****************************************/
#include "global_speed_planning.h"

#include <cctype>
#include <cmath>
#include <type_traits>


#define eps 1e-4

using namespace GlobalPlanning;

/**
 *@brief: 初始化速度规划参数
 *@param [in] m_veh_param 车辆参数
 *return
 */
void GlobalSpeedPlanning::InitSpeedParam(_VehicleParam m_veh_param) {
    max_acceleration_   = m_veh_param.max_acceleration;
    min_acceleration_   = m_veh_param.min_acceleration;
    speed_error_term    = m_veh_param.speed_error_term;
    speed_smooth_term   = m_veh_param.speed_smooth_term;
    light_reverse_speed = m_veh_param.light_reverse_speed;
    heavy_reverse_speed = m_veh_param.heavy_reverse_speed;
    threadLogger_->info("max_acceleration_ ={} ", max_acceleration_);
    threadLogger_->info("min_acceleration_ ={} ", min_acceleration_);
    threadLogger_->info("speed_error_term ={} ", speed_error_term);
    threadLogger_->info("speed_smooth_term ={} ", speed_smooth_term);
    threadLogger_->info("light_reverse_speed ={} ", light_reverse_speed);
    threadLogger_->info("heavy_reverse_speed ={} ", heavy_reverse_speed);
    vehicle_param = m_veh_param;
}


/*
 * 速度规划接口函数
 * @param  trajectory：规划后的路径
 * @param  m_veh_param：车辆参数
 * @return true：规划成功；false：规划失败
 */
void GlobalSpeedPlanning::SpeedPlanning(vector<_TrajectoryPoint>& trajectory, const _VehicleParam m_veh_param) {
    // // 先对trajectory进行加密
    // vector<_TrajectoryPoint> copy_trajectory;
    // copy_trajectory=trajectory;
    // //保存copy_trajectory
    // std::ofstream file;
    // file.open("copy_trajectory.txt");
    // for (const auto& point : copy_trajectory) {
    //     file << point.x << " " << point.y << " " << point.yaw <<" "<< point.curvature << std::endl;
    // }
    // file.close();
    // CalculateCubicSplineCurve(copy_trajectory,trajectory);
    // //保存trajectory
    // file.open("trajectory.txt");
    // for (const auto& point : trajectory) {
    //     file << point.x << " " << point.y << " " << point.yaw <<" "<< point.curvature << std::endl;
    // }
    // file.close();

    InitSpeedParam(m_veh_param);
    /*限速设置*/
    ReplanPointMaxSpeed(trajectory);


    // 对trajectory中的每个点进行速度规划
    planSpeed(trajectory);
    Helper::calculateAcceleration(trajectory);

    // std::ofstream file;
    // // 保存平滑前的速度
    // file.open("speed_before_smooth.txt");
    // for (const auto& point : trajectory) {
    //     file << point.distance << " " << point.speed << " " << point.acc << " " << point.speed_limit << std::endl;
    // }
    // file.close();

    // 速度曲线平滑
    // Smooth(trajectory);

    threadLogger_->info("进入FixLocalMininum");
    FixLocalMininum(trajectory);
    Helper::calculateAcceleration(trajectory);
    

    // file.open("speed_after_smooth.txt");
    // for (const auto& point : trajectory) {
    //     file << point.distance << " " << point.speed << " " << point.acc << " " << point.speed_limit << std::endl;
    // }
    // file.close();
    threadLogger_->info("进入Smooth");
    Smooth(trajectory);
    Helper::calculateAcceleration(trajectory);
    // threadLogger_->info("进入FixLocalMaxnum");
    // FixLocalMaxnum(trajectory);
    // file.open("speed_after_smooth2.txt");
    // for (const auto& point : trajectory) {
    //     file << point.distance << " " << point.speed << " " << point.acc << " " << point.speed_limit << std::endl;
    // }
    // file.close();


    // 恢复倒车速度
    for (auto& point : trajectory) {
        if (point.direction == 1) {
            point.speed *= -1;
        }
    }
    // 保存平滑后的速度
}


void GlobalSpeedPlanning::ReplanPointMaxSpeed(vector<_TrajectoryPoint>& trajectory) {
    double regular_road_speed_limit      = 1;    // 常规路面限速
    double narrow_road_speed_limit       = 1;    // 会车道路限速
    double intersection_road_speed_limit = 1;    // 路口限速
    double slope_road_speed_limit        = 1;    // 坡路限速
    double bumpy_road_speed_limit        = 1;    // 颠簸路段限速
    double reverse_speed                 = 1;    // 本次规划倒车限速
    double a                             = 0.9;  // a表示一级限速到二级限速之间的缩放比例
    double b                             = 0.85; // b表示一级限速到三级限速之间的缩放比例
    double c                             = 0.9;  // c表示轻载到重载之间的缩放比例


    if (vehicle_param.speed_limit_level == SpeedLimitLevel::three) { // 晴天+白天【三级限速】
        threadLogger_->info("晴天+白天【三级限速】");
        regular_road_speed_limit      = vehicle_param.regular_road_speed_limit;
        narrow_road_speed_limit       = vehicle_param.narrow_road_speed_limit;
        intersection_road_speed_limit = vehicle_param.intersection_road_speed_limit;
        slope_road_speed_limit        = vehicle_param.slope_road_speed_limit;
        bumpy_road_speed_limit        = vehicle_param.bumpy_road_speed_limit;
    }
    else if (vehicle_param.speed_limit_level == SpeedLimitLevel::two) { // 晴天+晚上      雨天+白天 【二级限速】
        threadLogger_->info("晴天+晚上      雨天+白天 【二级限速】");
        regular_road_speed_limit      = a * vehicle_param.regular_road_speed_limit;
        narrow_road_speed_limit       = a * vehicle_param.narrow_road_speed_limit;
        intersection_road_speed_limit = a * vehicle_param.intersection_road_speed_limit;
        slope_road_speed_limit        = a * vehicle_param.slope_road_speed_limit;
        bumpy_road_speed_limit        = a * vehicle_param.bumpy_road_speed_limit;
    }
    else { // 雨天+晚上 【一级限速】
        threadLogger_->info("雨天+晚上 【一级限速】");
        regular_road_speed_limit      = b * vehicle_param.regular_road_speed_limit;
        narrow_road_speed_limit       = b * vehicle_param.narrow_road_speed_limit;
        intersection_road_speed_limit = b * vehicle_param.intersection_road_speed_limit;
        slope_road_speed_limit        = b * vehicle_param.slope_road_speed_limit;
        bumpy_road_speed_limit        = b * vehicle_param.bumpy_road_speed_limit;
    }

    reverse_speed = vehicle_param.light_reverse_speed;
    if (vehicle_param.is_light == false) {
        threadLogger_->info("重载");
        regular_road_speed_limit      = c * regular_road_speed_limit;
        narrow_road_speed_limit       = c * narrow_road_speed_limit;
        intersection_road_speed_limit = c * intersection_road_speed_limit;
        slope_road_speed_limit        = c * slope_road_speed_limit;
        bumpy_road_speed_limit        = c * bumpy_road_speed_limit;
        reverse_speed                 = vehicle_param.heavy_reverse_speed;
    }


    // 先通过direction属性，将前进后退轨迹进行区分(direction 0:前进 1:后退),后退轨迹限速均为1m/s
    vector<_TrajectoryPoint>::iterator iter = trajectory.begin();
    threadLogger_->info("trajectory.back().speed_limit:{}", trajectory.back().speed_limit);
    if (trajectory.back().speed_limit == -1) {
        // speed_limit=-1表示没有设置限速，说明地图中没有提供限速信息，说明这是矿区版本的地图
        threadLogger_->info("地图中没有提供限速信息，说明这是矿区版本的地图");
        double last_speed_limit = 0;
        for (; iter != trajectory.end(); iter++) {
            if (iter->direction == 0) {
                if (iter->attribute == PointAttribute::regular_road) // 正常路
                {
                    iter->speed_limit = regular_road_speed_limit;
                }
                else if (iter->attribute == PointAttribute::narrow_road) // 会车路
                {
                    iter->speed_limit = narrow_road_speed_limit;
                }
                else if (iter->attribute == PointAttribute::intersection_road) // 路口
                {
                    iter->speed_limit = intersection_road_speed_limit;
                }
                else if (iter->attribute == PointAttribute::slope_road) // 坡路
                {
                    iter->speed_limit = slope_road_speed_limit;
                }
                else if (iter->attribute == PointAttribute::dump_road) // 颠簸路
                {
                    iter->speed_limit = bumpy_road_speed_limit;
                }
                else if (iter->attribute == PointAttribute::queue_point) // 装载排队点
                {
                    // 排队点限速为上一个点的限速
                    iter->speed_limit = last_speed_limit;
                }
                else // 其他特殊点一律限速为0
                {
                    iter->speed_limit = 0;
                }
                last_speed_limit = iter->speed_limit;
            }
            else {
                iter->speed_limit = reverse_speed;
            }
        }
    }
    else {
        // 如果speed_limit!=-1，说明地图中提供了限速信息，说明这是光伏/园区版本的地图
        // 对hybrid*astar规划的路径进行限速
        threadLogger_->info("地图中提供了限速信息，hybridAstar_path_length_：{}", hybridAstar_path_length_);
        for (int i = 0; i < hybridAstar_path_length_; i++) {
            trajectory.at(i).speed_limit = 10;
        }
        for (int i = 0; i < trajectory.size(); i++) {
            if (trajectory.at(i).direction == 1) {
                trajectory.at(i).speed_limit = reverse_speed;
            }
        }
    }
    // std::ofstream file_out;
    // file_out.open("speed_limit0.txt");
    // for (size_t index = 0; index < trajectory.size(); index++) {
    //     file_out << 0 << " " << trajectory.at(index).speed_limit << " " << trajectory.at(index).curvature << endl;
    // }
    // file_out.close();

    // 计算trajectory前hybridAstar_path_length_个路径点的曲率变化率,如果曲率变化率大于0.06，则将对应路径点的限速设置为1
    threadLogger_->info("速度规划，hybridAstar_path_length_：{}", hybridAstar_path_length_);
    vector<double> curvature_change_rate;
    for (int i = 1; i < hybridAstar_path_length_; i++) {
        curvature_change_rate.push_back(fabs(trajectory.at(i).curvature - trajectory.at(i - 1).curvature));
    }
    for (int i = 0; i < curvature_change_rate.size(); i++) {
        if (curvature_change_rate.at(i) > 0.06) {
            trajectory.at(i).speed_limit = 1;
        }
    }

    // 遍历整个trajectory，检核每个点的限速是否合理；根据方向盘最大转速以及每个点的瞬时曲率来确定每个点的合理限速
    float L_vehicle                = vehicle_param.wheel_base;
    float max_Steering_wheel_speed = vehicle_param.max_steering_wheel_speed;
    threadLogger_->info("速度规划，max_Steering_wheel_speed：{}", max_Steering_wheel_speed);
    float         temp_max_speed;
    float         wheel_delta_angle, wheel_angle1, wheel_angle2;
    float         sampling_distance = 1;
    vector<float> vec_temp_max_speed; // 记录全局路径上基于曲率变化算出限速信息


    for (int i = 1; i < trajectory.size(); i++) //
    {
        wheel_angle1   = atan(L_vehicle * trajectory.at(i).curvature);
        wheel_angle2   = atan(L_vehicle * trajectory.at(i - 1).curvature);
        temp_max_speed = sampling_distance * max_Steering_wheel_speed / (fabs(wheel_angle1 - wheel_angle2) + eps); // 根据控制给的方向盘最高转速和预定的采样距离算出的每个点的最大限速
        if (temp_max_speed >= 10) temp_max_speed = 10;
        vec_temp_max_speed.push_back(temp_max_speed);
    }

    for (int i = 1; i < vec_temp_max_speed.size(); i++) {
        if (vec_temp_max_speed.at(i) < trajectory.at(i).speed_limit) {
            trajectory.at(i).speed_limit = vec_temp_max_speed.at(i);
            // 为了便于控制跟踪，将附近路径点限速也降低为vec_temp_max_speed.at(i)
            for (int j = i - 1; j < i + 1; j++) {
                if (j >= 0 && j < trajectory.size()) {
                    if (trajectory.at(j).speed_limit > vec_temp_max_speed.at(i)) {
                        trajectory.at(j).speed_limit = vec_temp_max_speed.at(i);
                    }
                }
            }
        }
    }

    // file_out.open("speed_limit1.txt");
    // for (size_t index = 0; index < trajectory.size(); index++) {
    //     file_out << 0 << " " << trajectory.at(index).speed_limit << endl;
    // }
    // file_out.close();


    double coff = 0.4;
    if (vehicle_param.is_light == false) {
        coff = 0.2;
    }
    // 曲率限速
    iter = trajectory.begin();
    for (; iter != trajectory.end(); iter++) {
        if (iter->speed_limit > sqrt(coff / fabs(iter->curvature))) {
            iter->speed_limit = sqrt(coff / fabs(iter->curvature));
        }
    }

    // threadLogger_->info("限速设置--在这里打印路径点限速信息");
    for (size_t index = 0; index < trajectory.size(); index++) {
        // threadLogger_->info("index:{}  speed_limit:{}", index, trajectory.at(index).speed_limit);
    }
    // file_out.open("speed_limit2.txt");
    // for (size_t index = 0; index < trajectory.size(); index++) {
    //     file_out << 0 << " " << trajectory.at(index).speed_limit << endl;
    // }
    // file_out.close();
}

void GlobalSpeedPlanning::Smooth(vector<_TrajectoryPoint>& trajectory) {
    vector<_TrajectoryPoint> trajectory_copy = trajectory;
    unsigned int             iterations      = 0;
    // 最大遍历次数为100次
    while (iterations++ < 100) {
        // 遍历稀疏速度曲线，分别计算出目标函数中每一项的梯度值，采用梯度下降法对速度曲线优化。
        for (unsigned int i = 1; i < trajectory.size() - 1; i++) {
            float v0     = trajectory.at(i - 1).speed;
            float v1     = trajectory.at(i).speed;
            float v2     = trajectory.at(i + 1).speed;
            float v_init = trajectory_copy.at(i).speed;

            float gradient_smooth = speed_smooth_term * (v0 + v2 - 2 * v1);
            float error_smooth    = speed_error_term * (v_init - v1);


            trajectory.at(i).speed += gradient_smooth + error_smooth;

            // 确保速度不超过原始限速
            if (trajectory_copy.at(i).speed < trajectory.at(i).speed) {
                trajectory.at(i).speed = trajectory_copy.at(i).speed;
            }
        }
    }
}
void GlobalSpeedPlanning::FixLocalMininum(vector<_TrajectoryPoint>& trajectory) {
    const double JERK = 0.01; // 基准jerk值 (m/s³/m)

    // 找出所有极小值点的索引（不包括起点和终点）
    vector<size_t> minima_indices;
    for (size_t i = 1; i < trajectory.size() - 1; i++) {
        if ((trajectory[i].speed <= trajectory[i - 1].speed && trajectory[i].speed < trajectory[i + 1].speed) || (trajectory[i].speed < trajectory[i - 1].speed && trajectory[i].speed <= trajectory[i + 1].speed)) {
            minima_indices.push_back(i);
        }
    }

    // 添加起点和终点
    minima_indices.insert(minima_indices.begin(), 0);
    minima_indices.push_back(trajectory.size() - 1);

    // 打印minima_indices
    for (size_t i = 0; i < minima_indices.size(); i++) {
        threadLogger_->info("minima_indices:{}", minima_indices[i]);
    }

    // 对每对相邻极小值之间的区间进行处理
    for (size_t i = 0; i < minima_indices.size() - 1; i++) {
        size_t start_idx = minima_indices[i];
        size_t end_idx   = minima_indices[i + 1];

        // 判断此区间是否有效，通过判断这个区间速度是否相等来识别
        if (fabs(trajectory[start_idx].speed - trajectory[end_idx].speed) < 0.01 && trajectory[end_idx].speed > eps && fabs(trajectory[start_idx].speed - trajectory[start_idx + 1].speed) < 0.01) {
            continue;
        }
        // 打印调试信息
        threadLogger_->info("start_idx:{}, end_idx:{} 左侧速度：{} 右侧速度：{}", start_idx, end_idx, trajectory[start_idx].speed, trajectory[end_idx].speed);

        // 从极小值向两边扩展
        double current_jerk           = JERK;
        bool   valid_profile          = false;
        bool   has_run_special_case   = false;
        bool   has_run_special_case_2 = false;
        while (!valid_profile) {
            threadLogger_->info("current_jerk:{}", current_jerk);

            vector<double> forward_speeds;  // 从start向前推演的速度
            vector<double> backward_speeds; // 从end向后推演的速度

            // 从start_idx开始向前推演
            double v = trajectory[start_idx].speed;
            double a = 0.0; // 假设极小值处加速度为0

            if (!has_run_special_case && fabs(trajectory[start_idx].speed) < 0.01) {
                current_jerk = 1.5 * JERK;
                threadLogger_->info("特殊段落，current_jerk:{}", current_jerk);
                has_run_special_case = true;
            }
            threadLogger_->info("开始向前推演");
            for (size_t j = start_idx; j <= end_idx; j++) {
                forward_speeds.push_back(v);

                if (j < end_idx) {
                    // threadLogger_->info("a:{} v:{} current_jerk:{}", a, v, current_jerk);
                    double ds = trajectory[j + 1].distance - trajectory[j].distance;
                    double k1, k2, k3, k4;
                    k1                   = 1.0 / (6 * current_jerk * current_jerk);
                    k2                   = a / (2.0 * current_jerk * current_jerk);
                    k3                   = v / current_jerk;
                    k4                   = -ds;
                    vector<double> roots = solveCubic(k1, k2, k3, k4);
                    // threadLogger_->info("前向推演 roots:{}", roots.size());
                    // for (size_t k = 0; k < roots.size(); k++) {
                    //     threadLogger_->info("roots[{}]:{}", k, roots[k]);
                    // }
                    double next_a = 0.0;
                    // next_a取最大的根
                    double max_root = -1e10;
                    for (int i = 0; i < roots.size(); i++) {
                        if (roots[i] >= max_root) {
                            max_root = roots[i];
                        }
                    }
                    next_a = max_root + a;

                    next_a = std::min(float(next_a), max_acceleration_);
                    // double v_next = v + (next_a - a) * a / current_jerk + pow((next_a - a), 2) / current_jerk / 2;
                    double v_next = sqrt(v * v + 2 * next_a * ds);

                    a = next_a;
                    if (fabs(v_next) > fabs(trajectory[j + 1].speed)) {
                        v = fabs(trajectory[j + 1].speed);
                    }
                    else {
                        v = v_next;
                    }
                    threadLogger_->info("第{}个点前向推演 v:{} a:{}  ds:{}", j + 1, v, a, ds);
                }
            }
            threadLogger_->info("开始向后推演");
            // 从end_idx开始向后推演
            v = trajectory[end_idx].speed;
            if (!has_run_special_case_2 && fabs(trajectory[end_idx].speed) < 0.01) {
                current_jerk = 1.5 * JERK;
                threadLogger_->info("特殊段落，current_jerk:{}", current_jerk);
                has_run_special_case_2 = true;
            }
            a = 0.0;

            for (size_t j = end_idx; j >= start_idx; j--) {
                backward_speeds.insert(backward_speeds.begin(), v);

                if (j > start_idx) {
                    double ds = trajectory[j].distance - trajectory[j - 1].distance;
                    double k1, k2, k3, k4;
                    k1                      = 1.0 / (6 * current_jerk * current_jerk);
                    k2                      = a / (2.0 * current_jerk * current_jerk);
                    k3                      = v / current_jerk;
                    k4                      = -ds;
                    vector<double> roots    = solveCubic(k1, k2, k3, k4);
                    double         next_a   = 0.0;
                    double         max_root = -1e10;
                    for (int i = 0; i < roots.size(); i++) {
                        if (roots[i] >= max_root) {
                            max_root = roots[i];
                        }
                    }
                    next_a        = max_root + a;
                    next_a        = std::min(float(next_a), -min_acceleration_);
                    double v_prev = sqrt(v * v + 2 * next_a * ds);
                    a             = next_a;

                    if (fabs(v_prev) > fabs(trajectory[j - 1].speed)) {
                        v = fabs(trajectory[j - 1].speed);
                    }
                    else {
                        v = v_prev;
                    }
                    threadLogger_->info("第{}个点后向推演 a:{} v:{}", j - 1, a, v);
                }

                if (j == start_idx) break;
            }
            // 打印forward_speeds和backward_speeds
            threadLogger_->info("forward_speeds:{}", forward_speeds.size());
            for (size_t j = 0; j < forward_speeds.size(); j++) {
                threadLogger_->info("forward_speeds[{}]:{}", j, forward_speeds[j]);
            }
            threadLogger_->info("backward_speeds:{}", backward_speeds.size());
            for (size_t j = 0; j < backward_speeds.size(); j++) {
                threadLogger_->info("backward_speeds[{}]:{}", j, backward_speeds[j]);
            }

            // 找出forward和backward的交点，选择较小的速度作为最终速度
            vector<double> temp_speeds(end_idx - start_idx + 1);
            for (size_t j = 0; j <= end_idx - start_idx; j++) {
                if (j == 0) {
                    temp_speeds[j] = forward_speeds[j];
                }
                else if (j == end_idx - start_idx) {
                    temp_speeds[j] = backward_speeds[j];
                }
                else {
                    temp_speeds[j] = (fabs(forward_speeds[j]) <= fabs(backward_speeds[j])) ? forward_speeds[j] : backward_speeds[j];
                }
            }
            threadLogger_->info("当前轮推演结束，current_jerk:{}", current_jerk);

            // 打印temp_speeds
            threadLogger_->info("temp_speeds:{}", temp_speeds.size());
            for (size_t j = 0; j < temp_speeds.size(); j++) {
                threadLogger_->info("temp_speeds[{}]:{}", j, temp_speeds[j]);
            }

            // 检查加速度约束
            valid_profile = true;
            for (size_t j = 1; j <= end_idx - start_idx; j++) {
                double ds  = trajectory[start_idx + j].distance - trajectory[start_idx + j - 1].distance;
                double acc = (temp_speeds[j] * temp_speeds[j] - temp_speeds[j - 1] * temp_speeds[j - 1]) / (2 * ds);

                if (acc > max_acceleration_ + eps || acc < min_acceleration_ - eps) {
                    threadLogger_->info("第{}个点acc:{} 超出加速度约束,ds:{},temp_speeds[j]:{} temp_speeds[j-1]:{}", j + start_idx, acc, ds, backward_speeds[j], backward_speeds[j - 1]);
                    valid_profile = false;
                    break;
                }
            }

            if (valid_profile) {
                // 如果满足加速度约束，更新速度
                for (size_t j = 0; j <= end_idx - start_idx; j++) {
                    trajectory[start_idx + j].speed = temp_speeds[j];
                }
            }
            else {
                // 如果不满足约束，增加jerk值继续尝试

                current_jerk *= 1.2;
                threadLogger_->info("不满足约束，增加jerk值继续尝试，current_jerk:{}", current_jerk);
            }
        }
    }
}


void GlobalSpeedPlanning::planSpeed(vector<_TrajectoryPoint>& trajectory) {
    vector<_TrajectoryPoint> trajectory_copy = trajectory;
    // 确保起始和终止速度为0
    trajectory_copy.front().speed_limit = 0.0;
    trajectory_copy.back().speed_limit  = 0.0;
    trajectory_copy.front().speed       = 0.0;
    trajectory_copy.back().speed        = 0.0;

    // 在方向改变的点设置速度限制为0（换档点）
    for (size_t i = 1; i < trajectory_copy.size(); ++i) {
        if (trajectory_copy[i].direction != trajectory_copy[i - 1].direction) {
            threadLogger_->info("planSpeed-换档点");
            trajectory_copy[i - 1].speed_limit = 0.0;
        }
    }

    // 前向扫描：考虑加速度限制和速度限制
    for (size_t i = 1; i < trajectory_copy.size(); ++i) {
        double ds = trajectory_copy[i].distance - trajectory_copy[i - 1].distance;
        // 根据方向选择加速度限制
        double current_max_acc    = trajectory_copy[i].direction == 0 ? max_acceleration_ : max_acceleration_;
        double max_possible_speed = std::sqrt(trajectory_copy[i - 1].speed * trajectory_copy[i - 1].speed + 2 * current_max_acc * ds);
        trajectory_copy[i].speed  = std::min(max_possible_speed, trajectory_copy[i].speed_limit);
        // threadLogger_->info("i:{} speed:{}", i, trajectory_copy[i].speed);
    }

    // 后向扫描：确保能够及时减速到0
    for (size_t i = trajectory_copy.size() - 2; i > 0; --i) {
        double ds = trajectory_copy[i + 1].distance - trajectory_copy[i].distance;
        // 根据方向选择减速度限制
        double current_min_acc    = trajectory_copy[i].direction == 0 ? min_acceleration_ : min_acceleration_;
        double max_possible_speed = std::sqrt(trajectory_copy[i + 1].speed * trajectory_copy[i + 1].speed + 2 * std::abs(current_min_acc) * ds);
        trajectory_copy[i].speed  = std::min(trajectory_copy[i].speed, max_possible_speed);
        // threadLogger_->info("i:{} speed:{}", i, trajectory_copy[i].speed);
    }

    for (int i = 0; i < trajectory_copy.size(); i++) {
        trajectory.at(i).speed = trajectory_copy.at(i).speed;
    }
}


void GlobalSpeedPlanning::FixLocalMaxnum(vector<_TrajectoryPoint>& trajectory) {
    // 找出所有极大值点的索引（不包括起点和终点）
    vector<size_t> maxima_indices;
    for (size_t i = 1; i < trajectory.size() - 1; i++) {
        if ((trajectory[i].speed >= trajectory[i - 1].speed && trajectory[i].speed > trajectory[i + 1].speed) || (trajectory[i].speed > trajectory[i - 1].speed && trajectory[i].speed >= trajectory[i + 1].speed)) {
            maxima_indices.push_back(i);
        }
    }
    // 打印maxima_indices
    threadLogger_->info("打印所有极大值");
    for (size_t i = 0; i < maxima_indices.size(); i++) {
        threadLogger_->info("maxima_indices:{}", maxima_indices[i]);
    }
    // 找出所有极小值点
    vector<size_t> minima_indices;
    for (size_t i = 1; i < trajectory.size() - 1; i++) {
        if ((trajectory[i].speed <= trajectory[i - 1].speed && trajectory[i].speed < trajectory[i + 1].speed) || (trajectory[i].speed < trajectory[i - 1].speed && trajectory[i].speed <= trajectory[i + 1].speed)) {
            minima_indices.push_back(i);
        }
    }

    // 添加起点和终点
    minima_indices.insert(minima_indices.begin(), 0);
    minima_indices.push_back(trajectory.size() - 1);
    // 打印minima_indices
    threadLogger_->info("打印所有极小值，包括起点终点");
    for (size_t i = 0; i < minima_indices.size(); i++) {
        threadLogger_->info("minima_indices:{}", minima_indices[i]);
    }

    // 构建vector<tuple<int,int,int>>，每个tuple包含一个极大值点索引，及该极大值索引左侧的极小值点索引和右侧的极小值点索引
    vector<int> total_record;
    total_record.insert(total_record.end(), minima_indices.begin(), minima_indices.end());
    total_record.insert(total_record.end(), maxima_indices.begin(), maxima_indices.end());
    sort(total_record.begin(), total_record.end());
    vector<tuple<int, int, int>> maxima_minima_indices;
    for (size_t i = 0; i < maxima_indices.size(); i++) {
        int index = BinarySearch(maxima_indices.at(i), total_record);
        maxima_minima_indices.push_back(make_tuple(maxima_indices[i], total_record[index - 1], total_record[index + 1]));
    }

    // 打印maxima_minima_indices

    threadLogger_->info("打印所有极大值区间");
    for (size_t i = 0; i < maxima_minima_indices.size(); i++) {
        threadLogger_->info("maxima_minima_indices:{}  {}  {}", get<0>(maxima_minima_indices[i]), get<1>(maxima_minima_indices[i]), get<2>(maxima_minima_indices[i]));
    }


    double min_delta_jerk = -0.1;
    int    pre_end_index  = -1;
    for (int i = 0; i < maxima_minima_indices.size(); i++) {
        int maxima_idx      = get<0>(maxima_minima_indices[i]);
        int left_minima_idx = get<1>(maxima_minima_indices[i]);
        if (left_minima_idx < pre_end_index) {
            left_minima_idx = pre_end_index;
        }
        int right_minima_idx = get<2>(maxima_minima_indices[i]);
        int reasonable_idx   = -1;

        threadLogger_->info("第 {} 对区间 [{},{}],极大值{},上一次的end_index:{} 最右侧端点的速度 {}，加速度 {}", i, left_minima_idx, right_minima_idx, maxima_idx, pre_end_index, trajectory[right_minima_idx].speed, trajectory[right_minima_idx].acc);
        // 从maxima_idx开始，往前遍历，直到遍历到left_minima_idx

        for (int j = maxima_idx - 1; j >= left_minima_idx; j--) {
            bool   flag  = false;
            double cur_a = trajectory.at(j).acc;
            double cur_v = trajectory.at(j).speed;
            for (int k = j; k < right_minima_idx; k++) {
                double ds = trajectory[k + 1].distance - trajectory[k].distance;
                threadLogger_->info("index:{} cur_a:{} cur_v:{} ds:{}", k, cur_a, cur_v, ds);
                double k1, k2, k3, k4;
                k1 = 1.0 / (6 * min_delta_jerk * min_delta_jerk);
                k2 = cur_a / (2.0 * min_delta_jerk * min_delta_jerk);
                k3 = cur_v / min_delta_jerk;
                k4 = -ds;
                // threadLogger_->info("k1:{} k2:{} k3:{} k4:{}", k1, k2, k3, k4);


                vector<double> roots = solveCubic(k1, k2, k3, k4);
                for (int i = 0; i < roots.size(); i++) {
                    roots[i] = roots[i] + cur_a;
                    threadLogger_->info("roots:{}", roots[i]);
                }

                double next_a = 0.0;
                // 从roots中选择比cur_a小且距离cur_a最近的值
                double min_root         = 1e10;
                int    reasonable_index = -1;

                for (int i = 0; i < roots.size(); i++) {
                    if (roots[i] <= cur_a) {
                        if (fabs(roots[i] - cur_a) < min_root) {
                            min_root         = fabs(roots[i] - cur_a);
                            reasonable_index = i;
                        }
                    }
                }

                if (reasonable_index == -1) {
                    next_a = cur_a;
                }
                else {
                    next_a = roots[reasonable_index];
                }


                if (next_a < min_acceleration_) next_a = min_acceleration_;
                double next_v = sqrt(max(0.0, cur_v * cur_v + 2 * next_a * ds));
                cur_v         = next_v;
                cur_a         = next_a;
                threadLogger_->info("index:{} min_delta_jerk:{} v:{} acc:{} target_v:{} target_acc:{}", k, min_delta_jerk, cur_v, cur_a, trajectory.at(k + 1).speed, trajectory.at(k + 1).acc);
                if (cur_v > trajectory.at(k + 1).speed) {
                    flag = true;
                    break;
                }

                cout << "第" << i << "区间,第" << k << "个索引点" << " ds:" << ds << " a:" << cur_a << " v:" << cur_v << endl;
            }
            if (flag) {
                threadLogger_->info("候选点 {} 以最大减速度推演出现超速情况，pass,重新找下一个候选点", j);
                threadLogger_->info(" ");
                continue;
            }
            threadLogger_->info("候选点 {} ,起始速度：{}  起始加速度：{} 最终推导结果如下 cur_v:{} cur_a:{}", j, trajectory.at(j).speed, trajectory.at(j).acc, cur_v, cur_a);
            // 循环结束，判断推演出的最后一个点的速度、加速度是否满足要求
            if ((cur_v <= trajectory[right_minima_idx].speed) && (cur_a <= trajectory.at(right_minima_idx).acc)) {
                threadLogger_->info("第 {} 对区间，找到合理的衔接点{}", i, j);
                reasonable_idx = j;
                break;
            }
            else {
                threadLogger_->info("不达标，继续推演");
            }
            cout << endl;
        }

        if (reasonable_idx == -1) {
            // 这个区间，极大值左侧找不到合理的衔接点,跳过后续所有代码
            threadLogger_->info("第 {} 对区间，没有找到合理的衔接点", i);
            continue;
        }
        // 从reasonable_idx处开始推理，找到最合理的delta_jerk
        threadLogger_->info("开始对第 {} 对区间进行试验，找出合理的delta_jerk", i);
        double                        cur_delta_jerk = min_delta_jerk;
        vector<tuple<double, double>> v_t;

        bool success_flag = false;
        while (cur_delta_jerk < 0) {
            double cur_a = trajectory.at(reasonable_idx).acc;
            double cur_v = trajectory.at(reasonable_idx).speed;
            v_t.clear();
            for (int k = reasonable_idx; k < right_minima_idx; k++) {
                threadLogger_->info("index:{} cur_a:{} cur_v:{}", k, cur_a, cur_v);
                double ds = trajectory[k + 1].distance - trajectory[k].distance;
                double k1, k2, k3, k4;
                k1                   = 1.0 / (6 * cur_delta_jerk * cur_delta_jerk);
                k2                   = cur_a / (2.0 * cur_delta_jerk * cur_delta_jerk);
                k3                   = cur_v / cur_delta_jerk;
                k4                   = -ds;
                vector<double> roots = solveCubic(k1, k2, k3, k4);
                for (int i = 0; i < roots.size(); i++) {
                    roots[i] = roots[i] + cur_a;
                    threadLogger_->info("roots:{}", roots[i]);
                }
                double next_a           = 0.0;
                double min_root         = 1e10;
                int    reasonable_index = -1;
                for (int i = 0; i < roots.size(); i++) {
                    if (roots[i] <= cur_a) {
                        if (fabs(roots[i] - cur_a) < min_root) {
                            min_root         = fabs(roots[i] - cur_a);
                            reasonable_index = i;
                        }
                    }
                }
                threadLogger_->info("reasonable_index:{}", reasonable_index);
                if (reasonable_index == -1) {
                    next_a = cur_a;
                }
                else {
                    next_a = roots[reasonable_index];
                }

                double next_v = sqrt(max(0.0, cur_v * cur_v + 2 * next_a * ds));
                cur_a         = next_a;
                cur_v         = next_v;
                v_t.push_back(make_tuple(cur_a, cur_v));
                threadLogger_->info("推演一步 index:{} cur_delta_jerk:{} v:{} a:{} target_v:{} target_a:{}", k, cur_delta_jerk, cur_v, cur_a, trajectory.at(k + 1).speed, trajectory.at(k + 1).acc);
                if (fabs(next_v) < 1e-2) {
                    threadLogger_->info("next_v:{} 已经降低为0，跳过", next_v);
                    if (k != right_minima_idx - 1) {
                        threadLogger_->info("未成功对接");
                        break;
                    }
                }

                if (k + 1 > maxima_idx && fabs(cur_v - trajectory.at(k + 1).speed) < 0.01 && fabs(cur_a - trajectory.at(k + 1).acc) < 1e-2) {
                    threadLogger_->info("成功对接，对接处的索引{},speed:{} acc:{}", k + 1, cur_v, cur_a);
                    success_flag  = true;
                    pre_end_index = k + 1;
                    threadLogger_->info("有 {} 个点需要调整速度 加速度", v_t.size());
                    for (int m = 0; m < v_t.size(); m++) {
                        reasonable_idx++;
                        threadLogger_->info("m:{} 副值索引:{}", m, reasonable_idx);
                        trajectory.at(reasonable_idx).acc   = get<0>(v_t.at(m));
                        trajectory.at(reasonable_idx).speed = get<1>(v_t.at(m));
                    }
                    break;
                }
                else {
                    threadLogger_->info("未成功对接");
                }
            }
            if (cur_a > 0.001) {
                threadLogger_->info("当前jerk:{} 不达标，后续jerk也都不会达标，保持原有速度分布，提前结束", cur_delta_jerk);
                break;
            }
            if (success_flag) {
                break;
            }

            // 循环结束，判断推演出的最后一个点的速度、加速度是否满足要求

            threadLogger_->info("cur_delta_jerk:{}无法顺利接轨", cur_delta_jerk);
            cur_delta_jerk += 0.0001;
            threadLogger_->info("换成 {} 尝试", cur_delta_jerk);
        }
        threadLogger_->info("line603");
    }
}

int GlobalSpeedPlanning::BinarySearch(int a, vector<int>& vec) {
    int size = vec.size();
    int left = 0, right = size;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a < vec.at(mid)) {
            right = mid - 1;
        }
        else if (a > vec.at(mid)) {
            left = mid + 1;
        }
        else {
            return mid;
        }
    }
    return -1;
}

void GlobalSpeedPlanning::CalculateCubicSplineCurve(vector<_TrajectoryPoint>& points, vector<_TrajectoryPoint>& cubicspline_path) {
    vector<double> x_set;
    vector<double> y_set;
    x_set.reserve(points.size());
    y_set.reserve(points.size());
    for (const auto& pt : points) {
        x_set.push_back(pt.x);
        y_set.push_back(pt.y);
    }

    CalculateStation(x_set, y_set);
    sx_.set_points(s_, x_set);
    sy_.set_points(s_, y_set);
    kDeltaS = 0.1;

    float  epsilon = 0.0001; // 容差值
    double s       = 0.0;
    for (s = 0.0; s <= s_.back(); s += kDeltaS) {
        double dx = sx_.deriv(1, s);
        double dy = sy_.deriv(1, s);

        double ddx = sx_.deriv(2, s);
        double ddy = sy_.deriv(2, s);

        // float angle = atan(dy / dx);
        // if (dx < 0)
        //     angle = angle + M_PI;
        // else if (dx >= 0 && dy < 0)
        //     angle = angle + 2 * M_PI;
        float angle = atan2(dy, dx);
        if (angle < 0) {
            angle += 2 * M_PI;
        }
        double cur = (ddy * dx - ddx * dy) / pow(dx * dx + dy * dy, 3.0 / 2);
        // if (fabs(cur) > 0.1) kDeltaS = 0.4;
        _TrajectoryPoint temp_point;
        temp_point.x         = sx_(s);
        temp_point.y         = sy_(s);
        temp_point.z         = 0;
        temp_point.yaw       = angle;
        temp_point.curvature = cur;
        temp_point.attribute = PointAttribute::dump_road;
        temp_point.direction = MotionDirection::Forward;
        cubicspline_path.emplace_back(temp_point);
    }
    s        = s_.back();
    float dx = sx_.deriv(1, s);
    float dy = sy_.deriv(1, s);

    float ddx   = sx_.deriv(2, s);
    float ddy   = sy_.deriv(2, s);
    float angle = atan2(dy, dx);
    if (angle < 0) {
        angle += 2 * M_PI;
    }
    float            cur = (ddy * dx - ddx * dy) / pow(dx * dx + dy * dy, 3.0 / 2);
    _TrajectoryPoint temp_point;
    temp_point.x         = sx_(s);
    temp_point.y         = sy_(s);
    temp_point.z         = 0;
    temp_point.yaw       = angle;
    temp_point.curvature = cur;
    temp_point.direction = MotionDirection::Forward;
    temp_point.attribute = PointAttribute::dump_road;
    cubicspline_path.emplace_back(temp_point);
}

void GlobalSpeedPlanning::CalculateStation(const vector<double>& xs, const vector<double>& ys) {
    double cum = 0.0;
    s_.clear();
    s_.push_back(cum);

    for (unsigned int i = 1; i < xs.size(); i++) {
        double dx = xs.at(i) - xs.at(i - 1);
        double dy = ys.at(i) - ys.at(i - 1);
        cum += hypot(dx, dy);
        s_.push_back(cum);
    }
}

// 求解三次方程 ax³ + bx² + cx + d = 0 的实根
vector<double> GlobalSpeedPlanning::solveCubic(double a, double b, double c, double d) {
    vector<double> roots;

    // 确保首项系数不为零
    if (fabs(a) < 1e-10) {
        cerr << "不是三次方程（a不能为0）" << endl;
        return roots;
    }

    // 归一化方程：x³ + px² + qx + r = 0
    double p = b / a;
    double q = c / a;
    double r = d / a;

    // 消去二次项，转换为 y³ + ay + b = 0 形式
    double delta = p / 3.0;
    double a1    = (3.0 * q - p * p) / 3.0;
    double b1    = (2.0 * p * p * p - 9.0 * p * q + 27.0 * r) / 27.0;

    // 计算判别式
    double discriminant = (b1 / 2.0) * (b1 / 2.0) + (a1 / 3.0) * (a1 / 3.0) * (a1 / 3.0);

    const double PI = acos(-1.0);

    if (discriminant > 1e-10) {
        // 一个实根，两个复根
        double sqrtD = sqrt(discriminant);
        double u     = cbrt(-b1 / 2.0 + sqrtD);
        double v     = cbrt(-b1 / 2.0 - sqrtD);
        double y     = u + v;
        roots.push_back(y - delta);
    }
    else if (fabs(discriminant) <= 1e-10) {
        // 三个实根，其中至少有两个相等
        double u = cbrt(-b1 / 2.0);
        roots.push_back(2 * u - delta);
        roots.push_back(-u - delta);
        roots.push_back(-u - delta);
    }
    else {
        // 三个不同的实根
        double sqrtD = sqrt(-discriminant);
        double rho   = sqrt((b1 / 2.0) * (b1 / 2.0) - discriminant);
        double theta = acos(-b1 / (2.0 * rho));

        double y1 = 2.0 * cbrt(rho) * cos(theta / 3.0);
        double y2 = 2.0 * cbrt(rho) * cos((theta + 2.0 * PI) / 3.0);
        double y3 = 2.0 * cbrt(rho) * cos((theta - 2.0 * PI) / 3.0);

        roots.push_back(y1 - delta);
        roots.push_back(y2 - delta);
        roots.push_back(y3 - delta);
    }

    // 排序根
    sort(roots.begin(), roots.end());

    // 去除可能的重复根（由于浮点数计算误差）
    auto last = unique(roots.begin(), roots.end(), [](double a, double b) { return fabs(a - b) < 1e-10; });
    roots.erase(last, roots.end());

    return roots;
}
