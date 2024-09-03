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


inline bool GetReferencelinesWithRadius(_SinglePoint point, const map<int, _SingleTraj>& trajs, double radius, vector<int>& vec) {
    cout << "Coming GetReferencelinesWithRadius" << endl;
    vec.clear();
    cout << "Point.x" << point.x << "point.y:" << point.y << endl;
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
        cout << "轨迹id：" << pair.first << "轨迹点数量：" << pair.second.trajectory.size() << endl;
        for (unsigned int i = 0; i < pair.second.trajectory.size(); i++) {
            temp_dis = sqrt(pow(point.x - pair.second.trajectory.at(i).x, 2) + pow(point.y - pair.second.trajectory.at(i).y, 2));
            if (temp_dis < nearest_dis) {
                nearest_dis = temp_dis;
                index       = i;
            }
        }
        cout << "nearest_dis:" << nearest_dis << "            id:" << pair.first << endl;
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
        if (nearest_dis < radius && (fabs(point.yaw - pair.second.trajectory.at(index).yaw) / M_PI * 180.0 < 90 || fabs(point.yaw - pair.second.trajectory.at(index).yaw) / M_PI * 180.0 > 270)) {
            cout << "tell me the angle:" << point.yaw << "  " << pair.second.trajectory.at(index).yaw << endl;
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

inline void CalNearestIndex(_SinglePoint& point, _SingleTraj& traj, int& nearest_index, double& lat_dis, double& lon_dis, double& distance, double& angle_diff) {
    double           temp_dis;
    double           min_distance = numeric_limits<double>::max();
    _TrajectoryPoint nearest_point;
    for (int i = 0; i < traj.trajectory.size(); i++) {
        _TrajectoryPoint temp_point;
        temp_point = traj.trajectory.at(i);
        temp_dis   = sqrt(pow(point.x - temp_point.x, 2) + pow(point.y - temp_point.y, 2));
        if (temp_dis < min_distance) {
            min_distance  = temp_dis;
            nearest_index = i;
        }
    }
    nearest_point = traj.trajectory.at(nearest_index);

    lat_dis    = fabs((point.y - nearest_point.y) * cos(nearest_point.yaw) - (point.x - nearest_point.x) * sin(nearest_point.yaw)); // 横向距离先不区分左正右负
    lon_dis    = (point.x - nearest_point.x) * cos(nearest_point.yaw) + (point.y - nearest_point.y) * sin(nearest_point.yaw);
    distance   = hypot(point.x - nearest_point.x, point.y - nearest_point.y);
    angle_diff = fabs(point.yaw - nearest_point.yaw) > M_PI ? fabs(point.yaw - nearest_point.yaw) - M_PI : fabs(point.yaw - nearest_point.yaw);
    // cout << "计算纵向距离" << endl;
    // cout << "x偏差： " << point.x - nearest_point.x << "   y偏差： " << point.y - nearest_point.y << "最近点角度："
    //      << nearest_point.yaw << endl;
    // cout << "lon_dis:" << lon_dis << endl;
}

inline bool OverSpeedCheck(vector<_TrajectoryPoint>& traj) {
    bool flag = false;
    for (int i = 0; i < traj.size() - 1; i++) {
        if (traj.at(i).speed > traj.at(i).speed_limit + 0.5) {
            flag = true;
        }
    }
    if (flag == true) return true;
    return false;
}

inline bool CheckPathFracture(vector<_TrajectoryPoint>& traj) {
    double dis = 0;
    for (int i = 0; i < traj.size() - 1; i++) {
        dis = pow(traj.at(i).x - traj.at(i + 1).x, 2) + pow(traj.at(i).y - traj.at(i + 1).y, 2);

        if (dis > 100) {
            cout << "traj.at(i).x" << traj.at(i).x << "traj.at(i).y " << traj.at(i).y << endl;
            return false; // 如果相邻点间距大于3m，说明路径产生断裂
        }
    }
    return true;
}

inline bool doesTrajectorySelfIntersect(Path& path) {
    // 通过判断yaw的变化了分析是否画圈
    // 判断方法，设置36个if else，36个标志位，如果超过24个标志为被置为true，即被判定为绕圈
    // cout << "进入检测绕圈函数" << endl;

    vector<int> vec(36, 0);
    cout << "检查角度" << endl;
    // for (int i = 0; i < path.size(); i++) {
    //     cout << path.at(i).angle << endl;
    // }
    cout << "准备经过这里" << endl;
    for (int i = 0; i < path.size(); i++) {
        vec.at(floor(path.at(i).angle * 18.0 / M_PI)) = 1;
    }
    cout << "成功的经过这里" << endl;
    int sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (vec.at(i) == 1) {
            sum++;
        }
    }
    double percent = sum / 36.0;
    if (percent < 0.9) {
        return false;
    }
    else {
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
inline void CalCurv(vector<_TrajectoryPoint>& traj) {
    vector<double> vec_x, vec_y, vec_angle;
    int            delta_length        = 4;
    int            halflengthmark      = 0;
    double         distance_halflength = 0;
    int            s                   = traj.size();
    for (int i = 0; i < s; i++) {
        vec_x.push_back(traj.at(i).x);
        vec_y.push_back(traj.at(i).y);
        vec_angle.push_back(traj.at(i).yaw);
    }
    // 计算前0.5m的点的位置halflengthmark
    int j = 0;
    while (j < s - 1) {
        distance_halflength = distance_halflength + sqrt(pow(vec_x.at(j + 1) - vec_x.at(j), 2) + pow(vec_y.at(j + 1) - vec_y.at(j), 2));
        if (distance_halflength >= delta_length / 2) {
            halflengthmark = j + 1;
            break;
        }
        j++;
    }

    // 计算前1.0m点的曲率
    for (int i = 0; i <= halflengthmark; i++) {
        double distance_front = 0, distance_back = 0;
        int    k = i;
        // 计算当前点距离第一个点的距离
        while (k > 0) {
            distance_back = distance_back + sqrt(pow(vec_x.at(k) - vec_x.at(k - 1), 2) + pow(vec_y.at(k) - vec_y.at(k - 1), 2));
            k--;
        }
        k = i;
        while (k < s - 1) {
            distance_front = distance_front + sqrt(pow(vec_x.at(k + 1) - vec_x.at(k), 2) + pow(vec_y.at(k + 1) - vec_y.at(k), 2));
            if (distance_front >= (delta_length - distance_back)) {
                double anglew_front  = vec_angle.at(k + 1); // 当前点0.5后的点角度
                double delta_anglew  = anglew_front - vec_angle.at(0);
                delta_anglew         = fmod((delta_anglew + 3 * M_PI), (2 * M_PI)) - M_PI; // 角度插值转化，避免 - 180和180处出问题
                traj.at(i).curvature = delta_anglew / delta_length;
                break;
            }
            k++;
        }
    }

    // 计算末尾前0.5m点的位置
    double distance_last_halflength = 0;
    int    lasthalflengthmark       = 0;
    j                               = s - 1;
    while (j > 0) {
        distance_last_halflength = distance_last_halflength + sqrt(pow(vec_x.at(j) - vec_x.at(j - 1), 2) + pow(vec_y.at(j) - vec_y.at(j - 1), 2));
        if (distance_last_halflength >= (delta_length / 2)) {
            lasthalflengthmark = j - 1;
            break;
        }
        j--;
    }

    //%计算末尾0.5米曲率
    for (int i = lasthalflengthmark; i <= s - 1; i++) {
        double distance_back  = 0;
        double distance_front = 0;
        int    k              = i;
        while (k < s - 1) {
            distance_back = distance_back + sqrt(pow(vec_x.at(k + 1) - vec_x.at(k), 2) + pow(vec_y.at(k + 1) - vec_y.at(k), 2));
            k++;
        }
        k = i;
        while (k > 0) {
            distance_front = distance_front + sqrt(pow(vec_x.at(k) - vec_x.at(k - 1), 2) + pow(vec_y.at(k) - vec_y.at(k - 1), 2));
            if (distance_front >= (delta_length - distance_back)) {
                double anglew_back   = vec_angle.at(k - 1);
                double delta_anglew  = vec_angle.at(traj.size() - 1) - anglew_back;
                delta_anglew         = fmod((delta_anglew + 3 * M_PI), (2 * M_PI)) - M_PI;
                traj.at(i).curvature = delta_anglew / delta_length;
                break;
            }
            k--;
        }
    }

    // 计算中间曲率
    for (int i = halflengthmark + 1; i <= lasthalflengthmark - 1; i++) {
        double distance_back  = 0;
        double distance_front = 0;
        double anglew_front   = 0;
        double anglew_back    = 0;
        int    k              = i;
        while (k < s - 1) {
            distance_front = distance_front + sqrt(pow(vec_x.at(k + 1) - vec_x.at(k), 2) + pow(vec_y.at(k + 1) - vec_y.at(k), 2));
            if (distance_front >= delta_length / 2) {
                anglew_front = vec_angle.at(k + 1); // 当前点0.5后的点角度
                break;
            }
            k++;
        }
        k = i;
        while (k > 0) {
            distance_back = distance_back + sqrt(pow(vec_x.at(k) - vec_x.at(k - 1), 2) + pow(vec_y.at(k) - vec_y.at(k - 1), 2));
            if (distance_back >= delta_length / 2) {
                anglew_back = vec_angle.at(k - 1);
                break;
            }
            k--;
        }
        double delta_anglew  = anglew_front - anglew_back;
        delta_anglew         = fmod((delta_anglew + 3 * M_PI), (2 * M_PI)) - M_PI;
        traj.at(i).curvature = delta_anglew / delta_length;
    }
}
// inline void CalAcc(vector<_TrajectoryPoint>& traj) {
//     float last_acc;
//     float delta_length = 1.0;
//     for (int i = 0; i < traj.size() - 10; i++) {
//         double delta_speed_square = pow(traj.at(i + 10).speed, 2) - pow(traj.at(i).speed, 2);
//         traj.at(i).acc            = delta_speed_square / (2 * delta_length);
//         last_acc                  = delta_speed_square / (2 * delta_length);
//     }
//     for (int i = traj.size() - 10; i < traj.size(); i++) {
//         traj.at(i).acc = last_acc;
//     }
// }

inline void Calrad2deg(vector<_TrajectoryPoint>& traj) {
    for (size_t index = 0; index < traj.size(); index++) {
        float temp_angle   = traj.at(index).yaw;
        traj.at(index).yaw = temp_angle / M_PI * 180;
    }
}

inline void RemoveSamePoint(std::vector<_TrajectoryPoint>& traj) {
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

inline bool CheckCurvature(vector<_TrajectoryPoint>& tra) {
    float threshold = 0.15;
    for (int i = 0; i < tra.size(); i++) {
        if (fabs(tra.at(i).curvature) > threshold) {
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


} // namespace Helper
} // namespace GlobalPlanning

#endif // HELPER_H
