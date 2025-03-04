/* ****************************************
 * 作者: yyf(yanyifeng@wicri.org)
 * 日期: 2025/03/03
 * 内容: 完成函数功能实现,完善修改程序逻辑
 * 功能：考虑限速的(可能包含多段前进、后退路段)全局速度规划
 * ****************************************/
#include "global_speed_planning.h"

#define eps 1e-4

using namespace GlobalPlanning;

/**
 *@brief: 初始化速度规划参数
 *@param [in] m_veh_param 车辆参数
 *return
 */
void GlobalSpeedPlanning::InitSpeedParam(_VehicleParam m_veh_param) {
    max_acceleration  = m_veh_param.max_acceleration;
    min_acceleration  = m_veh_param.min_acceleration;
    speed_error_term  = m_veh_param.speed_error_term;
    speed_smooth_term = m_veh_param.speed_smooth_term;
    reverse_speed     = m_veh_param.reverse_speed;


    threadLogger_->info("max_acceleration ={} ", max_acceleration);
    threadLogger_->info("min_acceleration ={} ", min_acceleration);
    threadLogger_->info("speed_error_term ={} ", speed_error_term);
    threadLogger_->info("speed_smooth_term ={} ", speed_smooth_term);
    threadLogger_->info("reverse_speed ={} ", reverse_speed);
    vehicle_param = m_veh_param;
}


/*
 * 速度规划接口函数
 * @param  trajectory：规划后的路径
 * @param  m_veh_param：车辆参数
 * @return true：规划成功；false：规划失败
 */
void GlobalSpeedPlanning::SpeedPlanning(vector<_TrajectoryPoint>& trajectory, const _VehicleParam m_veh_param) {
    InitSpeedParam(m_veh_param);
    /*限速设置*/
    ReplanPointMaxSpeed(trajectory);
    // 对trajectory中的每个点进行速度规划
    planSpeed(trajectory);

    // 保存平滑前的速度
    std::ofstream file_before;
    file_before.open("speed_before_smooth.txt");
    for (const auto& point : trajectory) {
        file_before << point.distance << " " << point.speed << std::endl;
    }
    file_before.close();

    // 速度曲线平滑
    SpeedCurveSmooth(trajectory);

    // 保存平滑后的速度
    std::ofstream file_after;
    file_after.open("speed_after_smooth.txt");
    for (const auto& point : trajectory) {
        file_after << point.distance << " " << point.speed << std::endl;
    }
    file_after.close();
}


void GlobalSpeedPlanning::ReplanPointMaxSpeed(vector<_TrajectoryPoint>& trajectory) {
    double regular_road_speed_limit      = 1;    // 常规路面限速
    double narrow_road_speed_limit       = 1;    // 会车道路限速
    double intersection_road_speed_limit = 1;    // 路口限速
    double slope_road_speed_limit        = 1;    // 坡路限速
    double bumpy_road_speed_limit        = 1;    // 颠簸路段限速
    double reverse_speed                 = 1;    // 倒车限速
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


    if (vehicle_param.is_light == 0) {
        threadLogger_->info("重载");
        regular_road_speed_limit      = c * regular_road_speed_limit;
        narrow_road_speed_limit       = c * narrow_road_speed_limit;
        intersection_road_speed_limit = c * intersection_road_speed_limit;
        slope_road_speed_limit        = c * slope_road_speed_limit;
        bumpy_road_speed_limit        = c * bumpy_road_speed_limit;
    }
    reverse_speed = vehicle_param.reverse_speed;

    // 先通过direction属性，将前进后退轨迹进行区分(direction 0:前进 1:后退),后退轨迹限速均为1m/s
    vector<_TrajectoryPoint>::iterator iter             = trajectory.begin();
    double                             last_speed_limit = 0;
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
            // 此时，该点为后退路径上的点,后退轨迹限速均为1m/s
            iter->speed_limit = vehicle_param.reverse_speed;
        }
    }
    std::ofstream file_out;
    file_out.open("speed_limit0.txt");
    for (size_t index = 0; index < trajectory.size(); index++) {
        file_out << 0 << " " << trajectory.at(index).speed_limit << endl;
    }
    file_out.close();

    // 遍历整个trajectory，检核每个点的限速是否合理；根据方向盘最大转速以及每个点的瞬时曲率来确定每个点的合理限速
    float         L_vehicle                = vehicle_param.wheel_base;
    float         max_Steering_wheel_speed = 0.174;
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

    file_out.open("speed_limit1.txt");
    for (size_t index = 0; index < trajectory.size(); index++) {
        file_out << 0 << " " << trajectory.at(index).speed_limit << endl;
    }
    file_out.close();


    // 曲率限速
    iter = trajectory.begin();
    for (; iter != trajectory.end(); iter++) {
        if (iter->speed_limit > sqrt(0.4 / fabs(iter->curvature))) {
            iter->speed_limit = sqrt(0.4 / fabs(iter->curvature));
        }
    }

    threadLogger_->info("限速设置--在这里打印路径点限速信息");
    for (size_t index = 0; index < trajectory.size(); index++) {
        threadLogger_->info("index:{}  speed_limit:{}", index, trajectory.at(index).speed_limit);
    }
    file_out.open("speed_limit2.txt");
    for (size_t index = 0; index < trajectory.size(); index++) {
        file_out << 0 << " " << trajectory.at(index).speed_limit << endl;
    }
    file_out.close();
}


void GlobalSpeedPlanning::SpeedCurveSmooth(vector<_TrajectoryPoint>& trajectory) {
    const double JERK = 0.02; // 基准jerk值 (m/s³/m)

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
        if (fabs(trajectory[start_idx].speed - trajectory[end_idx].speed) < 0.01 && trajectory[end_idx].speed > eps) {
            continue;
        }
        // 打印调试信息
        threadLogger_->info("start_idx:{}, end_idx:{}", start_idx, end_idx);

        // 从极小值向两边扩展
        double current_jerk  = JERK;
        bool   valid_profile = false;

        while (!valid_profile) {
            threadLogger_->info("current_jerk:{}", current_jerk);
            vector<double> forward_speeds;  // 从start向前推演的速度
            vector<double> backward_speeds; // 从end向后推演的速度

            // 从start_idx开始向前推演
            double v = trajectory[start_idx].speed;
            double a = 0.0; // 假设极小值处加速度为0

            for (size_t j = start_idx; j <= end_idx; j++) {
                forward_speeds.push_back(v);

                if (j < end_idx) {
                    double ds = trajectory[j + 1].distance - trajectory[j].distance;
                    a         = std::min(float(a + current_jerk * ds), max_acceleration);
                    threadLogger_->info("a:{}", a);
                    double v_next = sqrt(v * v + 2 * a * ds);

                    if (fabs(v_next) > fabs(trajectory[j + 1].speed)) {
                        v = trajectory[j + 1].speed > 0 ? fabs(trajectory[j + 1].speed) : -fabs(trajectory[j + 1].speed);
                    }
                    else {
                        v = v_next;
                    }
                }
            }
            threadLogger_->info("开始向后推演");
            // 从end_idx开始向后推演
            v = trajectory[end_idx].speed;
            a = 0.0;

            for (size_t j = end_idx; j >= start_idx; j--) {
                backward_speeds.insert(backward_speeds.begin(), v);

                if (j > start_idx) {
                    double ds = trajectory[j].distance - trajectory[j - 1].distance;
                    a         = std::min(float(a + current_jerk * ds), -min_acceleration);
                    threadLogger_->info("a:{}", a);
                    double v_prev = sqrt(v * v + 2 * a * ds);

                    if (fabs(v_prev) > fabs(trajectory[j - 1].speed)) {
                        v = trajectory[j - 1].speed > 0 ? fabs(trajectory[j - 1].speed) : -fabs(trajectory[j - 1].speed);
                    }
                    else {
                        v = v_prev;
                    }
                }

                if (j == start_idx) break;
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

            // 检查加速度约束
            valid_profile = true;
            for (size_t j = 1; j <= end_idx - start_idx; j++) {
                double ds  = trajectory[start_idx + j].distance - trajectory[start_idx + j - 1].distance;
                double acc = (temp_speeds[j] * temp_speeds[j] - temp_speeds[j - 1] * temp_speeds[j - 1]) / (2 * ds);
                threadLogger_->info("acc:{}", acc);
                if (acc > max_acceleration + eps || acc < min_acceleration - eps) {
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
            }
        }
    }
}


void GlobalSpeedPlanning::planSpeed(vector<_TrajectoryPoint>& trajectory) {
    // 确保起始和终止速度为0
    trajectory.front().speed_limit = 0.0;
    trajectory.back().speed_limit  = 0.0;
    trajectory.front().speed       = 0.0;
    trajectory.back().speed        = 0.0;

    // 在方向改变的点设置速度限制为0（换档点）
    for (size_t i = 1; i < trajectory.size(); ++i) {
        if (trajectory[i].direction != trajectory[i - 1].direction) {
            trajectory[i - 1].speed_limit = 0.0;
        }
    }

    // 前向扫描：考虑加速度限制和速度限制
    for (size_t i = 1; i < trajectory.size(); ++i) {
        double ds = trajectory[i].distance - trajectory[i - 1].distance;
        // 根据方向选择加速度限制
        double current_max_acc    = trajectory[i].direction == 0 ? max_acceleration : max_acceleration * 0.5;
        double max_possible_speed = std::sqrt(trajectory[i - 1].speed * trajectory[i - 1].speed + 2 * current_max_acc * ds);
        double speed_limit        = trajectory[i].direction == 0 ? trajectory[i].speed_limit : -trajectory[i].speed_limit;
        trajectory[i].speed       = trajectory[i].direction == 0 ? std::min(max_possible_speed, speed_limit) : std::max(-max_possible_speed, speed_limit);
    }

    // 后向扫描：确保能够及时减速到0
    for (size_t i = trajectory.size() - 2; i > 0; --i) {
        double ds = trajectory[i + 1].distance - trajectory[i].distance;
        // 根据方向选择减速度限制
        double current_min_acc    = trajectory[i].direction == 0 ? min_acceleration : min_acceleration * 0.5;
        double max_possible_speed = std::sqrt(trajectory[i + 1].speed * trajectory[i + 1].speed + 2 * std::abs(current_min_acc) * ds);

        if (trajectory[i].direction == 0) {
            trajectory[i].speed = std::min(trajectory[i].speed, max_possible_speed);
        }
        else {
            trajectory[i].speed = std::max(trajectory[i].speed, -max_possible_speed);
        }
    }
}
