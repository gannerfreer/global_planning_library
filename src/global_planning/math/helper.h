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

#include <math.h>

#include "../common/common_struct.h"
// #include "../os/os.h"

#define M_PI 3.14159265358979323846

namespace GlobalPlanning {

namespace Helper {

/**
 * @brief 将角度转换到0~2pi
 * @param [in] angle 输入角度值(rad)
 * @return 返回说明：
 * 返回转换后的角度值
 */
inline double NormalizeAngleRad(double angle) {
    if (angle < 0) {
        angle = angle - 2.0 * M_PI * (int)(angle / (2.0 * M_PI));
        return static_cast<double>(2.0 * M_PI + angle);
    }
    else {
        return static_cast<double>(angle - 2.0 * M_PI * (int)(angle / (2.0 * M_PI)));
    }
}

/**
 * @brief 将角度转换到0~360°
 * @param [in] angle 输入角度值(deg)
 * @return 返回说明：
 * 返回转换后的角度值
 */
inline double NormalizeAngleDeg(double angle) {
    if (angle < 0) {
        angle = angle - 360.0 * (int)(angle / 360.0);
        return static_cast<double>(360.0 + angle);
    }
    else {
        return static_cast<double>(angle - 360.0 * (int)(angle / 360.0));
    }
}

/**
 * @brief 弧度转角度
 * @param [in] angle 输入角度值(rad)
 * @return 返回说明：
 * 返回转换后的角度值
 */
inline double ToDeg(double t) {
    return NormalizeAngleRad(t) * 180.f / M_PI;
}

/**
 * @brief 角度转弧度
 * @param [in] angle 输入角度值(deg)
 * @return 返回说明：
 * 返回转换后的角度值
 */
inline double ToRad(double t) {
    return NormalizeAngleRad(t / 180.f * M_PI);
}


inline int GetNearestReferencelines(_SinglePoint point, const map<int, _SingleTraj>& trajs, double& lat_dis, double& lon_dis) {
    cout << "Coming GetNearestReferencelines" << endl;
    _TrajectoryPoint nearest_point;
    cout << "Point.x:   " << point.x << "point.y:    " << point.y << endl;
    if (!trajs.size()) {
        cout << "轨迹个数为0" << endl;
        lat_dis = numeric_limits<double>::max();
        lon_dis = numeric_limits<double>::max();
        return -1;
    }
    bool temp_bool = false;

    double nearest_dis = numeric_limits<double>::max();
    double temp_dis;
    int    index = -1;
    for (const auto pair : trajs) {
        for (unsigned int i = 0; i < pair.second.trajectory.size(); i++) {
            temp_dis = sqrt(pow(point.x - pair.second.trajectory.at(i).x, 2) + pow(point.y - pair.second.trajectory.at(i).y, 2));
            if (temp_dis < nearest_dis) {
                nearest_dis   = temp_dis;
                index         = i;
                nearest_point = pair.second.trajectory.at(index);
            }
        }
    }
    lat_dis = fabs((point.y - nearest_point.y) * cos(nearest_point.yaw) - (point.x - nearest_point.x) * sin(nearest_point.yaw)); // 横向距离先不区分左正右负
    lon_dis = (point.x - nearest_point.x) * cos(nearest_point.yaw) + (point.y - nearest_point.y) * sin(nearest_point.yaw);
    cout << "找到的终点最近点距离：" << hypot(point.x - nearest_point.x, point.y - nearest_point.y) << endl;
    return index;
    // angle_diff = fabs(point.yaw - nearest_point.yaw) > M_PI ? 2 * M_PI - fabs(point.yaw - nearest_point.yaw) : fabs(point.yaw - nearest_point.yaw);
}

inline double calculateAngleDifference(double a, double b) {
    // 计算差值
    double diff = std::fmod(std::abs(a - b), 2 * M_PI);

    // 将差值限制在[0, π]范围内
    if (diff > M_PI) {
        diff = 2 * M_PI - diff;
    }

    return diff;
}
inline bool GetReferencelinesWithRadius(_SinglePoint point, const map<int, _SingleTraj>& trajs, double radius, vector<int>& vec) {
    cout << "Coming GetReferencelinesWithRadius" << endl;
    vec.clear();
    cout << "Point.x" << point.x << "   point.y:" << point.y << endl;
    cout << "radius:" << radius << endl;
    if (!trajs.size()) {
        cout << "轨迹个数为0" << endl;
        return false;
    }
    bool temp_bool = false;

    double nearest_dis = numeric_limits<double>::max();
    double temp_dis;
    int    index = -1;
    for (const auto pair : trajs) {
        nearest_dis = numeric_limits<double>::max();
        // cout << "轨迹id：" << pair.first << "轨迹点数量：" << pair.second.trajectory.size() << endl;
        for (unsigned int i = 0; i < pair.second.trajectory.size(); i++) {
            // if (calculateAngleDifference(point.yaw, pair.second.trajectory.at(i).yaw) < 1.58) {
            temp_dis = sqrt(pow(point.x - pair.second.trajectory.at(i).x, 2) + pow(point.y - pair.second.trajectory.at(i).y, 2));
            if (temp_dis < nearest_dis) {
                nearest_dis = temp_dis;
                index       = i;
            }
            // }
        }
        // cout << "nearest_dis:" << nearest_dis << "            id:" << pair.first << endl;
        if (nearest_dis < radius) {
            vec.push_back(pair.first);
            cout << "index:" << index << endl;
            temp_bool = true;
        }
    }
    if (temp_bool)
        return true;
    else
        return false;
}

inline bool GetReferencelinesWithRadiusAndAngle(_SinglePoint point, const map<int, _SingleTraj>& trajs, double radius, vector<int>& vec) {
    cout << "Coming GetReferencelinesWithRadiusAndAngle" << endl;
    vec.clear();

    if (!trajs.size()) {
        cout << "轨迹个数为0" << endl;
        return false;
    }
    bool temp_bool = false;

    double nearest_dis = numeric_limits<double>::max();
    double temp_dis;
    int    index = -1;
    for (const auto pair : trajs) {
        nearest_dis = numeric_limits<double>::max();
        for (unsigned int i = 0; i < pair.second.trajectory.size(); i++) {
            temp_dis = sqrt(pow(point.x - pair.second.trajectory.at(i).x, 2) + pow(point.y - pair.second.trajectory.at(i).y, 2));
            if (temp_dis < nearest_dis) {
                nearest_dis = temp_dis;
                index       = i;
            }
        }
        if (nearest_dis < radius && (fabs(point.yaw - pair.second.trajectory.at(index).yaw) / M_PI * 180.0 < 5 || fabs(point.yaw - pair.second.trajectory.at(index).yaw) / M_PI * 180.0 > 355)) {
            cout << "tell me the angle:" << point.yaw << "  " << pair.second.trajectory.at(index).yaw << endl;
            vec.push_back(pair.first);
            cout << "index:" << index << endl;
            temp_bool = true;
        }
        else {
            cout << "id: " << pair.first << " nearest_dis: " << nearest_dis << " 此时搜索半径： " << radius << " 最近点角度差： " << fabs(point.yaw - pair.second.trajectory.at(index).yaw) / M_PI * 180.0 << endl;
        }
    }
    if (temp_bool)
        return true;
    else
        return false;
}

inline void CalNearestIndex(_SinglePoint& point, _SingleTraj& traj, int& nearest_index, double& lat_dis, double& lon_dis, double& distance, double& angle_diff) {
    double           temp_dis;
    double           min_distance = numeric_limits<double>::max();
    _TrajectoryPoint nearest_point;
    for (int i = 0; i < traj.trajectory.size(); i++) {
        _TrajectoryPoint temp_point;
        temp_point = traj.trajectory.at(i);
        // if (calculateAngleDifference(point.yaw, temp_point.yaw) < 1.58) {
        temp_dis = sqrt(pow(point.x - temp_point.x, 2) + pow(point.y - temp_point.y, 2));
        if (temp_dis < min_distance) {
            min_distance  = temp_dis;
            nearest_index = i;
            // }
        }
    }
    nearest_point = traj.trajectory.at(nearest_index);

    lat_dis    = fabs((point.y - nearest_point.y) * cos(nearest_point.yaw) - (point.x - nearest_point.x) * sin(nearest_point.yaw)); // 横向距离先不区分左正右负
    lon_dis    = (point.x - nearest_point.x) * cos(nearest_point.yaw) + (point.y - nearest_point.y) * sin(nearest_point.yaw);
    distance   = hypot(point.x - nearest_point.x, point.y - nearest_point.y);
    angle_diff = fabs(point.yaw - nearest_point.yaw) > M_PI ? 2 * M_PI - fabs(point.yaw - nearest_point.yaw) : fabs(point.yaw - nearest_point.yaw);
    // cout << "计算纵向距离" << endl;
    // cout << "x偏差： " << point.x - nearest_point.x << "   y偏差： " << point.y - nearest_point.y << "最近点角度："
    //      << nearest_point.yaw << endl;
    // cout << "lon_dis:" << lon_dis << endl;
}

inline bool OverSpeedCheck(vector<_TrajectoryPoint>& traj, float L) {
    bool flag = false;
    for (int i = 0; i < traj.size() - 1; i++) {
        // cout << "index:" << i << "speed_limit:" << traj.at(i).speed_limit << endl;
        if (traj.at(i).speed > traj.at(i).speed_limit + 0.5 + eps) {
            cout << "超速类型1" << endl;
            flag = true;
        }
        if (traj.at(i).speed > sqrt(0.5 / traj.at(i).curvature) + eps) {
            cout << "超速类型2" << "index:" << i << "real_speed:" << traj.at(i).speed << "  ideal_speed_limit:" << sqrt(0.5 / traj.at(i).curvature) << endl;
            flag = true;
        }
        if (traj.at(i).speed > 1.0 * 0.175 * 1.5 / (fabs(atan(L * traj.at(i).curvature) - atan(L * traj.at(i + 1).curvature)) + eps) + eps) {
            cout << "超速类型3" << "index:" << i << "real_speed:" << traj.at(i).speed << "  ideal_speed_limit:" << 1.0 * 0.175 * 1.5 / (fabs(atan(L * traj.at(i).curvature) - atan(L * traj.at(i + 1).curvature)) + eps) << endl;
            flag = true;
        }
    }
    if (flag == true) return false;
    return true;
}


inline bool doesTrajectorySelfIntersect(Path& path) {
    // 通过判断yaw的变化了分析是否画圈
    // 判断方法，设置36个if else，36个标志位，如果超过24个标志为被置为true，即被判定为绕圈
    cout << "进入检测绕圈函数" << endl;
    vector<int> vec(36, 0);
    int         index = 0;
    for (int i = 0; i < path.size(); i++) {
        index = floor(path.at(i).angle * 18.0 / M_PI);
        if (index > 35) index = 35;
        if (index < 0) index = 0;
        vec.at(floor(index)) = 1;
    }
    // cout << "成功的经过这里" << endl;
    int sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (vec.at(i) == 1) {
            sum++;
        }
    }
    double percent = sum / 36.0;
    cout << "percent" << percent << endl;
    if (percent < 0.7) {
        cout << "路径未构成圈" << endl;
        return false;
    }
    else {
        cout << "路径构成圈圈" << endl;
        return true;
    }
}
inline void CalDistance(vector<_TrajectoryPoint>& traj) {
    traj.at(0).distance = 0;
    double s            = 0;
    for (unsigned int i = 1; i < traj.size(); i++) {
        double dx = traj.at(i).x - traj.at(i - 1).x;
        double dy = traj.at(i).y - traj.at(i - 1).y;
        s += sqrt(dx * dx + dy * dy);
        traj.at(i).distance = s;
    }
}
inline void CalDistance(vector<Point>& path) {
    path.at(0).distance = 0;
    double s            = 0;
    for (unsigned int i = 1; i < path.size(); i++) {
        double dx = path.at(i).x - path.at(i - 1).x;
        double dy = path.at(i).y - path.at(i - 1).y;
        s += sqrt(dx * dx + dy * dy);
        path.at(i).distance = s;
    }
}
// inline void CalCurv(vector<_TrajectoryPoint>& traj) {
//     Point  delta_xi;   // Δxi
//     Point  delta_xip1; // Δxi+1
//     double norm_delta_xi, norm_delta_xip1, d, dphi, kappa;
//     if (traj.size() > 2) {
//         for (int i = 1; i < traj.size() - 1; i++) {
//             if (traj.at(i).direction == traj.at(i + 1).direction) {
//                 delta_xi.x      = traj.at(i).x - traj.at(i - 1).x;
//                 delta_xi.y      = traj.at(i).y - traj.at(i - 1).y;
//                 delta_xip1.x    = traj.at(i + 1).x - traj.at(i).x;
//                 delta_xip1.y    = traj.at(i + 1).y - traj.at(i).y;
//                 norm_delta_xi   = sqrt(pow(delta_xi.x, 2) + pow(delta_xi.y, 2));     // |Δxi|
//                 norm_delta_xip1 = sqrt(pow(delta_xip1.x, 2) + pow(delta_xip1.y, 2)); // |Δxi+1|
//                 d               = norm_delta_xi * norm_delta_xip1;
//                 double temp     = (delta_xi.x * delta_xip1.x + delta_xi.y * delta_xip1.y) / d;
//                 if (temp > 1.0) {
//                     temp = 1.0;
//                 }
//                 if (temp < -1.0) {
//                     temp = -1.0;
//                 }
//                 dphi = acos(temp); // 通过向量积求出两向量之间夹角
//                 // cout << "(" << traj.at(i - 1).x << "," << traj.at(i - 1).y << ")  ->(" << traj.at(i).x << "," << traj.at(i).y << ")之间的角度变化 ：" << dphi / M_PI * 180.0 << "两者之间距离：" << norm_delta_xi << endl;
//                 double cross_product = delta_xi.x * delta_xip1.y - delta_xi.y * delta_xip1.x;
//                 if (cross_product > 0)
//                     kappa = dphi / norm_delta_xi;
//                 else
//                     kappa = -dphi / norm_delta_xi;
//                 // threadLogger_->info("delta_xi.x :{} delta_xip1.x:{}  delta_xi.y :{}  delta_xip1.y:{}  d:{}  acos({})", delta_xi.x, delta_xip1.x, delta_xi.y, delta_xip1.y, d, (delta_xi.x * delta_xip1.x + delta_xi.y * delta_xip1.y) / d);
//                 // threadLogger_->info("kappa :{} dphi:{}  norm_delta_xi:{} ", kappa, dphi, norm_delta_xi);
//                 traj.at(i).curvature = kappa;
//             }
//             else {
//                 if (i - 1 > 0) {
//                     traj.at(i).curvature = traj.at(i - 1).curvature;
//                 }
//                 else {
//                     traj.at(i).curvature = 0;
//                 }
//             }
//         }
//         traj.front().curvature = traj.at(1).curvature;
//         traj.back().curvature  = traj.at(traj.size() - 2).curvature;
//     }
// }


// inline void CalCurv(vector<Point>& traj) {
//     Point  delta_xi;   // Δxi
//     Point  delta_xip1; // Δxi+1
//     double norm_delta_xi, norm_delta_xip1, d, dphi, kappa;
//     if (traj.size() > 2) {
//         for (int i = 1; i < traj.size() - 1; i++) {
//             if (traj.at(i).direction == traj.at(i + 1).direction) {
//                 delta_xi.x      = traj.at(i).x - traj.at(i - 1).x;
//                 delta_xi.y      = traj.at(i).y - traj.at(i - 1).y;
//                 delta_xip1.x    = traj.at(i + 1).x - traj.at(i).x;
//                 delta_xip1.y    = traj.at(i + 1).y - traj.at(i).y;
//                 norm_delta_xi   = sqrt(pow(delta_xi.x, 2) + pow(delta_xi.y, 2));     // |Δxi|
//                 norm_delta_xip1 = sqrt(pow(delta_xip1.x, 2) + pow(delta_xip1.y, 2)); // |Δxi+1|
//                 d               = norm_delta_xi * norm_delta_xip1;
//                 double temp     = (delta_xi.x * delta_xip1.x + delta_xi.y * delta_xip1.y) / d;
//                 if (temp > 1.0) {
//                     temp = 1.0;
//                 }
//                 if (temp < -1.0) {
//                     temp = -1.0;
//                 }
//                 dphi = acos(temp); // 通过向量积求出两向量之间夹角
//                 // cout << "(" << traj.at(i - 1).x << "," << traj.at(i - 1).y << ")  ->(" << traj.at(i).x << "," << traj.at(i).y << ")之间的角度变化 ：" << dphi / M_PI * 180.0 << "两者之间距离：" << norm_delta_xi << endl;
//                 double cross_product = delta_xi.x * delta_xip1.y - delta_xi.y * delta_xip1.x;
//                 if (cross_product > 0)
//                     kappa = dphi / norm_delta_xi;
//                 else
//                     kappa = -dphi / norm_delta_xi;
//                 // threadLogger_->info("delta_xi.x :{} delta_xip1.x:{}  delta_xi.y :{}  delta_xip1.y:{}  d:{}  acos({})", delta_xi.x, delta_xip1.x, delta_xi.y, delta_xip1.y, d, (delta_xi.x * delta_xip1.x + delta_xi.y * delta_xip1.y) / d);
//                 // threadLogger_->info("kappa :{} dphi:{}  norm_delta_xi:{} ", kappa, dphi, norm_delta_xi);
//                 traj.at(i).curvature = kappa;
//             }
//             else {
//                 if (i - 1 > 0) {
//                     traj.at(i).curvature = traj.at(i - 1).curvature;
//                 }
//                 else {
//                     traj.at(i).curvature = 0;
//                 }
//             }
//         }
//         traj.front().curvature = traj.at(1).curvature;
//         traj.back().curvature  = traj.at(traj.size() - 2).curvature;
//     }
// }


inline void SmoothFilter(vector<_TrajectoryPoint>& traj, int opt_num) {
    unsigned int iterations = 0;
    // 最大遍历次数为30次
    if (opt_num > 50) opt_num = 50;
    while (iterations++ < opt_num) {
        // 遍历稀疏速度曲线，分别计算出目标函数中每一项的梯度值，采用梯度下降法对速度曲线优化。
        for (unsigned int i = 1; i < traj.size() - 1; i++) {
            float pre_curvature  = traj.at(i - 1).curvature;
            float cur_curvature  = traj.at(i).curvature;
            float next_curvature = traj.at(i + 1).curvature;
            // float origin_curvature = traj.at(i).curvature;

            // float gradient_error  = speed_error_term * (vo - v1);
            float gradient_smooth = 0.01 * (pre_curvature + next_curvature - 2 * cur_curvature);


            traj.at(i).curvature += gradient_smooth;
        }
    }
}


inline void Calrad2deg(vector<_TrajectoryPoint>& traj) {
    for (size_t index = 0; index < traj.size(); index++) {
        float temp_angle   = traj.at(index).yaw;
        traj.at(index).yaw = temp_angle / M_PI * 180.0;
    }
}

inline void RemoveBeforeSamePoint(std::vector<_TrajectoryPoint>& traj) {
    if (traj.size() < 2) return; // 如果轨迹点少于2个，则无需处理

    // 反转轨迹
    std::reverse(traj.begin(), traj.end());

    // 应用类似的快慢指针逻辑，但这次保留的是从最后一个点开始不重复的点
    int slow = 0, fast = 0;
    while (fast < traj.size()) {
        if (slow == 0 || hypot(traj.at(fast).x - traj.at(slow - 1).x, traj.at(fast).y - traj.at(slow - 1).y) > 0.3) {
            traj.at(slow) = traj.at(fast);
            slow++;
        }
        fast++;
    }

    // 保留不重复的部分
    traj.resize(slow);

    // 再次反转以恢复原始顺序
    std::reverse(traj.begin(), traj.end());
}
inline void RemoveAfterSamePoint(std::vector<_TrajectoryPoint>& traj) {
    if (traj.size() < 2) return; // 如果轨迹点少于2个，则无需处理

    // 反转轨迹
    // std::reverse(traj.begin(), traj.end());

    // 应用类似的快慢指针逻辑，但这次保留的是从最后一个点开始不重复的点
    int slow = 0, fast = 0;
    while (fast < traj.size()) {
        if (slow == 0 || hypot(traj.at(fast).x - traj.at(slow - 1).x, traj.at(fast).y - traj.at(slow - 1).y) > 0.2) {
            traj.at(slow) = traj.at(fast);
            slow++;
        }
        fast++;
    }

    // 保留不重复的部分
    traj.resize(slow);

    // 再次反转以恢复原始顺序
    // std::reverse(traj.begin(), traj.end());
}

inline bool SequenceAndDirectionCheck(std::vector<_TrajectoryPoint>& traj) {
    if (traj.size() < 2) return false; // 如果轨迹点少于2个，则无需处理
    double temp_angle = (atan2(traj.at(1).y - traj.at(0).y, traj.at(1).x - traj.at(0).x)) / M_PI * 180.0;
    double last_angle = temp_angle < 0 ? temp_angle + 360 : temp_angle;
    int    angle_diff = 0.0;
    for (int i = 1; i < traj.size() - 1; i++) {
        temp_angle = (atan2(traj.at(i + 1).y - traj.at(i).y, traj.at(i + 1).x - traj.at(i).x)) / M_PI * 180.0;
        temp_angle = temp_angle < 0 ? temp_angle + 360 : temp_angle;
        angle_diff = fabs(temp_angle - last_angle) > 180.0 ? 360 - fabs(temp_angle - last_angle) : fabs(temp_angle - last_angle);

        if (angle_diff > 90) {
            if (traj.at(i + 1).direction == traj.at(i).direction) {
                cout << "检测到角度突变，但是direction却没有变,索引：" << i + 1 << "角度突变：" << angle_diff << endl;
                // return false;
            }
        }
        last_angle = temp_angle;
    }
    return true;
}

inline bool CheckPathFracture(vector<_TrajectoryPoint>& traj) {
    double dis = 0.0, angle_diff = 0.0;
    cout << "开始进行轨迹断裂校验，一共 " << traj.size() << " 个点" << endl;
    for (int i = 0; i < traj.size() - 1; i++) {
        dis        = hypot(traj.at(i).x - traj.at(i + 1).x, traj.at(i).y - traj.at(i + 1).y);
        angle_diff = fabs(traj.at(i + 1).yaw - traj.at(i).yaw) > 180.0 ? 360 - fabs(traj.at(i + 1).yaw - traj.at(i).yaw) : fabs(traj.at(i + 1).yaw - traj.at(i).yaw);
        if (angle_diff > 20) { // 角度偏差不允许超过20度
            cout << "轨迹连续性检测，角度有跳变，跳变" << angle_diff << " 度,索引：" << i + 1 << "坐标：(" << traj.at(i).x << "," << traj.at(i).y << ")  和   (" << traj.at(i + 1).x << "," << traj.at(i + 1).y << ")" << endl;
            return false;
        }

        if (dis > 10) { // 相邻点间隔不允许超过
            cout << "traj.at(i).x" << traj.at(i).x << "traj.at(i).y " << traj.at(i).y << endl;
            return false; // 如果相邻点间距大于3m，说明路径产生断裂
        }
    }
    return true;
}


inline bool CheckCurvature(vector<_TrajectoryPoint>& tra, float threshold) {
    for (int i = 0; i < tra.size(); i++) {
        if (fabs(tra.at(i).curvature) > threshold) {
            cout << "曲率超标" << endl;
            return false;
        }
    }
    return true;
}
/**
 * @brief: 将角度换算成-pi~pi
 * @param angle:传入角度值
 * @return 无
 */
inline void Mod2Pi(float& angle) {
    double angle_t = fmod(angle, 2. * M_PI);
    if (angle_t < -M_PI)
        angle_t += 2. * M_PI;
    else if (angle_t > M_PI)
        angle_t -= 2. * M_PI;
    angle = angle_t;
}
/**
 * @brief: 实现matlab-mod函数 取余
 * @param x:传入除数
 * @param y:传入被除数
 * @return 实现结果
 */
inline double mod(double x, double y) {
    int    c = floor(x / y);
    double d = x - c * y;
    return d;
}


// 计算加速度的函数
inline void calculateAcceleration(const std::vector<_TrajectoryPoint>& v_points) {
    if (v_points.size() < 2) {
        std::cout << "至少需要两个点才能计算加速度" << std::endl;
        return;
    }

    for (size_t i = 1; i < v_points.size(); ++i) {
        const _TrajectoryPoint& prevPoint        = v_points[i - 1];
        const _TrajectoryPoint& currentPoint     = v_points[i];
        double                  distance         = hypot(prevPoint.x - currentPoint.x, prevPoint.y - currentPoint.y);
        double                  speedSquaredDiff = currentPoint.speed * currentPoint.speed - prevPoint.speed * prevPoint.speed;

        double acceleration = speedSquaredDiff / 2 * distance;

        // std::cout << "点(" << currentPoint.x << ", " << currentPoint.y << ") 的加速度为: " << acceleration << std::endl;
    }
}

static inline float clamp(float n, float lower, float upper) {
    return std::max(lower, std::min(n, upper));
}


} // namespace Helper
} // namespace GlobalPlanning

#endif // HELPER_H
