/***************************************************/
/*            Author: Xinpeng Chen                 */
/*            Contact: *********@163.com           */
/*            Last update: 2020-11-02              */
/***************************************************/
/*
Description: The header file for C++ class collision_check.
*/

#include "dubins.h"
using namespace curve;
/**
 * @brief 获取dubins路径代价接口函数实现
 */
bool Dubins ::GetDubinsPath(const Point start_pose, const Point end_pose, std::vector<Point>& path) {
    // threadLogger_->info("采用Dubins曲线预校验 ");
    // threadLogger_->info("start_pose.x = {},start_pose.y = {},start_pose.angle = {}", start_pose.GetX(), start_pose.GetY(), start_pose.GetAngle());
    // threadLogger_->info("end_pose.x = {},end_pose.y = {},end_pose.angle = {}", end_pose.GetX(), end_pose.GetY(), end_pose.GetAngle());
    float dx    = end_pose.GetX() - start_pose.GetX();
    float dy    = end_pose.GetY() - start_pose.GetY();
    float theta = mod(std ::atan2(dy, dx), twopi);

    alpha_            = mod(start_pose.GetAngle() * M_PI / 180 - theta, twopi);
    beta_             = mod(end_pose.GetAngle() * M_PI / 180 - theta, twopi);
    d_                = sqrt(dx * dx + dy * dy) / radius_;
    sin_alpha_        = sin(alpha_);
    cos_alpha_        = cos(alpha_);
    sin_beta_         = sin(beta_);
    cos_beta_         = cos(beta_);
    cos_alpha_m_beta_ = cos(alpha_ - beta_);
    std::vector<std::tuple<float, float, float>> C;
    C.emplace_back(LSL());
    C.emplace_back(LSR());
    C.emplace_back(RSL());
    C.emplace_back(RSR());
    C.emplace_back(RLR());
    C.emplace_back(LRL());
    float min_length       = DBL_MAX;
    int   min_length_index = 0;
    for (int i = 0; i < C.size(); i++) {
        auto len = std::get<0>(C[i]) + std::get<1>(C[i]) + std::get<2>(C[i]);
        if (len < min_length) {
            min_length       = len;
            min_length_index = i;
        }
    }
    auto opt_path = C[min_length_index];
    auto type     = dubins_path_type_[min_length_index];

    if (min_length_index == 1 || min_length_index == 2) {
        // threadLogger_->info("dubins lsl lsr rsl rsr {},{},{}", std::get<0>(opt_path) * radius_, std::get<1>(opt_path) * radius_, std::get<2>(opt_path) * radius_);
        if ((std::get<1>(opt_path) * radius_ < 2 * max_steering_angle_ / 10 * 1.414 && std::get<0>(opt_path) * radius_ > 2 * max_steering_angle_ / 10 * 1.414) || (std::get<1>(opt_path) * radius_ < 2 * max_steering_angle_ / 10 * 1.414 && std::get<2>(opt_path) * radius_ > 2 * max_steering_angle_ / 10 * 1.414)) {
            threadLogger_->info("路径长度小于{}m，不合理", 2 * max_steering_angle_ / 10 * 1.414);
            return false;
        }
        // threadLogger_->info("达标");
    }
    else if (min_length_index == 4 || min_length_index == 5) {
        threadLogger_->info("构型不合理");
        return false;
    }

    std::vector<Point> cp;
    cp.emplace_back(0, 0, start_pose.GetAngle());
    cp.emplace_back(CalNextPoint(std::get<0>(opt_path), cp[0].GetX(), cp[0].GetY(), cp[0].GetAngle(), type[0]));
    cp.emplace_back(CalNextPoint(std::get<1>(opt_path), cp[1].GetX(), cp[1].GetY(), cp[1].GetAngle(), type[1]));
    // for (const auto pt : cp) {
    //     std::cout << "x = " << pt.GetX() << "   y = " << pt.GetY() << "   theta = " << pt.GetAngle() << std::endl;
    // }


    for (float v = 0; v < min_length; v += delta_s_ / radius_) {
        Point pt;
        if (v < std::get<0>(opt_path)) {
            pt = CalNextPoint(v, cp[0].GetX(), cp[0].GetY(), cp[0].GetAngle(), type[0]);
        }
        else if (v < std::get<0>(opt_path) + std::get<1>(opt_path)) {
            pt = CalNextPoint(v - std::get<0>(opt_path), cp[1].GetX(), cp[1].GetY(), cp[1].GetAngle(), type[1]);
        }
        else {
            pt = CalNextPoint(v - std::get<0>(opt_path) - std::get<1>(opt_path), cp[2].GetX(), cp[2].GetY(), cp[2].GetAngle(), type[2]);
        }
        pt = pt * radius_ + start_pose;
        pt.SetAngle(mod(pt.GetAngle(), 360.0));
        path.emplace_back(pt);
    }


    if (DubinsPathSelfIntersectCheck(path)) {
        threadLogger_->info("路径绕圈，不合理");
        return false;
    }

    // for (int i = 0; i < 3; i++) {
    //     if (type[i] == DubinsPathSegmentType::L || type[i] == DubinsPathSegmentType::R) {
    //         if ((i == 0 && std::get<0>(opt_path) > M_PI) || (i == 1 && std::get<1>(opt_path) > M_PI) || (i == 2 && std::get<2>(opt_path) > M_PI)) {
    //             return false;
    //         }
    //     }
    // }
    // cout << "path.size():" << path.size() << endl;
    return true;
}
/**
 * @brief 左转－直行－左转
 */
std::tuple<float, float, float> Dubins ::LSL() {
    float p_squared = 2.0 + (d_ * d_) - (2 * cos_alpha_m_beta_) + (2 * d_ * (sin_alpha_ - sin_beta_));
    if (p_squared < 0)
        return std::make_tuple(DBL_MAX, DBL_MAX, DBL_MAX);
    else {
        float temp0 = d_ + sin_alpha_ - sin_beta_;
        float temp1 = atan2((cos_beta_ - cos_alpha_), temp0);
        float t     = mod((-alpha_ + temp1), twopi);
        float p     = sqrt(p_squared);
        float q     = mod((beta_ - temp1), twopi);
        return std::make_tuple(t, p, q);
    }
}
/**
 * @brief 左转－直行－右转
 */
std::tuple<float, float, float> Dubins ::LSR() {
    float p_squared = -2.0 + (d_ * d_) + (2.0 * cos_alpha_m_beta_) + (2 * d_ * (sin_alpha_ + sin_beta_));
    if (p_squared < 0)
        return std::make_tuple(DBL_MAX, DBL_MAX, DBL_MAX);
    else {
        float p     = sqrt(p_squared);
        float temp0 = atan2((-cos_alpha_ - cos_beta_), (d_ + sin_alpha_ + sin_beta_)) - atan2(-2.0, p);
        float t     = mod((-alpha_ + temp0), twopi);
        float q     = mod(-mod(beta_, twopi) + temp0, twopi);
        return std::make_tuple(t, p, q);
    }
}
/**
 * @brief 右转－直行－左转
 */
std::tuple<float, float, float> Dubins ::RSL() {
    float p_squared = -2.0 + (d_ * d_) + (2.0 * cos_alpha_m_beta_) - (2 * d_ * (sin_alpha_ + sin_beta_));
    if (p_squared < 0)
        return std::make_tuple(DBL_MAX, DBL_MAX, DBL_MAX);
    else {
        float p     = sqrt(p_squared);
        float temp0 = atan2((cos_alpha_ + cos_beta_), (d_ - sin_alpha_ - sin_beta_)) - atan2(2.0, p);
        float t     = mod((alpha_ - temp0), twopi);
        float q     = mod((beta_ - temp0), twopi);
        return std::make_tuple(t, p, q);
    }
}
/**
 * @brief 右转－直行－右转
 */
std::tuple<float, float, float> Dubins ::RSR() {
    float p_squared = 2.0 + (d_ * d_) - (2.0 * cos_alpha_m_beta_) + (2 * d_ * (sin_beta_ - sin_alpha_));
    if (p_squared < 0)
        return std::make_tuple(DBL_MAX, DBL_MAX, DBL_MAX);
    else {
        float temp0 = d_ - sin_alpha_ + sin_beta_;
        float temp1 = atan2((cos_alpha_ - cos_beta_), temp0);
        float t     = mod((alpha_ - temp1), twopi);
        float p     = sqrt(p_squared);
        float q     = mod((-beta_ + temp1), twopi);
        return std::make_tuple(t, p, q);
    }
}
/**
 * @brief 右转－左转－右转
 */
std::tuple<float, float, float> Dubins ::RLR() {
    float tmp_rlr = (6.0 - (d_ * d_) + (2.0 * cos_alpha_m_beta_) + (2 * d_ * (sin_alpha_ - sin_beta_))) / 8.0;
    if (abs(tmp_rlr) > 1.0)
        return std::make_tuple(DBL_MAX, DBL_MAX, DBL_MAX);
    else {
        float p = mod((twopi - acos(tmp_rlr)), twopi);
        float t = mod((alpha_ - atan2(cos_alpha_ - cos_beta_, d_ - sin_alpha_ + sin_beta_) + mod(p / 2.0, twopi)), twopi);
        float q = mod((alpha_ - beta_ - t + mod(p, twopi)), twopi);
        return std::make_tuple(t, p, q);
    }
}
/**
 * @brief 左转－右转－左转
 */
std::tuple<float, float, float> Dubins ::LRL() {
    float tmp_lrl = (6.0 - (d_ * d_) + (2.0 * cos_alpha_m_beta_) + (2 * d_ * (-sin_alpha_ + sin_beta_))) / 8.0;
    if (abs(tmp_lrl) > 1.0)
        return std::make_tuple(DBL_MAX, DBL_MAX, DBL_MAX);
    else {
        float p = mod((twopi - acos(tmp_lrl)), twopi);
        float t = mod((-alpha_ - atan2(cos_alpha_ - cos_beta_, d_ + sin_alpha_ - sin_beta_) + p / 2.0), twopi);
        float q = mod((mod(beta_, twopi) - alpha_ - t + mod(p, twopi)), twopi);
        return std::make_tuple(t, p, q);
    }
}

Point Dubins ::CalNextPoint(float v, float x, float y, float theta, DubinsPathSegmentType type) {
    float x_value, y_value, theta_value;
    float temp_theta = theta * M_PI / 180;
    switch (type) {
        case DubinsPathSegmentType::L:
            x_value     = x + std::sin(temp_theta + v) - std::sin(temp_theta);
            y_value     = y - std::cos(temp_theta + v) + std::cos(temp_theta);
            theta_value = temp_theta + v;
            break;
        case DubinsPathSegmentType::S:
            x_value     = x + v * std::cos(temp_theta);
            y_value     = y + v * std::sin(temp_theta);
            theta_value = temp_theta;
            break;
        case DubinsPathSegmentType::R:
            x_value     = x - std::sin(temp_theta - v) + std::sin(temp_theta);
            y_value     = y + std::cos(temp_theta - v) - std::cos(temp_theta);
            theta_value = temp_theta - v;
            break;
        default:
            break;
    }
    return Point(x_value, y_value, theta_value * 180 / M_PI);
}
bool Dubins::DubinsPathSelfIntersectCheck(std::vector<Point>& path) {
    // 通过判断yaw的变化了分析是否画圈
    // 判断方法，设置36个if else，36个标志位，如果超过24个标志为被置为true，即被判定为绕圈
    // cout << "进入检测绕圈函数" << endl;

    vector<int> vec(36, 0);
    int         index = 0;
    for (int i = 0; i < path.size(); i++) {
        index = floor(path.at(i).GetAngle() / 10.0);
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
    // cout << "percent: " << percent << endl;
    if (percent < 0.5) {
        // cout << "路径未构成圈" << endl;
        return false;
    }
    else {
        // cout << "路径构成圈圈" << endl;
        return true;
    }
}
