#include "wait_point_generate.h"
namespace WaitPointGenerate {

// 计算两点间距离的平方（避免开方提高性能）
double WaitPointGenerator::distanceSquared(const GlobalPlanning::Point& point, const GlobalPlanning::Point& other) const {
    double dx = point.x - other.x;
    double dy = point.y - other.y;
    return dx * dx + dy * dy;
}

bool WaitPointGenerator::arePathsCrossing(const std::vector<GlobalPlanning::Point>& path1, const std::vector<GlobalPlanning::Point>& path2, double distanceThreshold) {
    // 如果任一路径点数小于2，无法形成线段，直接返回false
    if (path1.size() < 2 || path2.size() < 2) {
        return false;
    }

    // 预先计算距离阈值平方（避免开方）
    double thresholdSq = distanceThreshold * distanceThreshold;

    // 记录可能相交的线段对
    std::unordered_map<size_t, std::vector<size_t>> candidatePairs;

    // 第一步：粗略筛选 - 找出距离较近的线段对
    for (size_t i = 0; i < path1.size() - 1; ++i) {
        const auto& p1_start = path1[i];
        const auto& p1_end   = path1[i + 1];

        for (size_t j = 0; j < path2.size() - 1; ++j) {
            const auto& p2_start = path2[j];
            const auto& p2_end   = path2[j + 1];

            // 计算两个线段的最小距离（近似）
            double minDistSq = std::numeric_limits<double>::max();

            // 检查线段端点间的距离
            minDistSq = std::min(minDistSq, distanceSquared(p1_start, p2_start));
            minDistSq = std::min(minDistSq, distanceSquared(p1_start, p2_end));
            minDistSq = std::min(minDistSq, distanceSquared(p1_end, p2_start));
            minDistSq = std::min(minDistSq, distanceSquared(p1_end, p2_end));

            // 如果最小距离小于阈值，加入候选对
            if (minDistSq <= thresholdSq) {
                candidatePairs[i].push_back(j);
            }
        }
    }

    // 第二步：精确检测 - 只检查候选线段对
    for (const auto& pair : candidatePairs) {
        size_t      i        = pair.first;
        const auto& p1_start = path1[i];
        const auto& p1_end   = path1[i + 1];

        for (size_t j : pair.second) {
            const auto& p2_start = path2[j];
            const auto& p2_end   = path2[j + 1];

            if (doSegmentsIntersect(p1_start, p1_end, p2_start, p2_end)) {
                return true;
            }
        }
    }

    return false;
}

bool WaitPointGenerator::doSegmentsIntersect(const GlobalPlanning::Point& p1, const GlobalPlanning::Point& p2, const GlobalPlanning::Point& q1, const GlobalPlanning::Point& q2) {
    // 计算方向向量的叉积
    auto cross = [](const GlobalPlanning::Point& a, const GlobalPlanning::Point& b, const GlobalPlanning::Point& c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); };

    // 计算四个方向
    double d1 = cross(p1, p2, q1);
    double d2 = cross(p1, p2, q2);
    double d3 = cross(q1, q2, p1);
    double d4 = cross(q1, q2, p2);

    // 检查线段是否跨立
    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
        return true;
    }

    // 检查共线情况下的重叠
    if (std::abs(d1) < std::numeric_limits<double>::epsilon() && ((q1.x >= std::min(p1.x, p2.x) && q1.x <= std::max(p1.x, p2.x)) && (q1.y >= std::min(p1.y, p2.y) && q1.y <= std::max(p1.y, p2.y)))) {
        return true;
    }

    if (std::abs(d2) < std::numeric_limits<double>::epsilon() && ((q2.x >= std::min(p1.x, p2.x) && q2.x <= std::max(p1.x, p2.x)) && (q2.y >= std::min(p1.y, p2.y) && q2.y <= std::max(p1.y, p2.y)))) {
        return true;
    }

    if (std::abs(d3) < std::numeric_limits<double>::epsilon() && ((p1.x >= std::min(q1.x, q2.x) && p1.x <= std::max(q1.x, q2.x)) && (p1.y >= std::min(q1.y, q2.y) && p1.y <= std::max(q1.y, q2.y)))) {
        return true;
    }

    if (std::abs(d4) < std::numeric_limits<double>::epsilon() && ((p2.x >= std::min(q1.x, q2.x) && p2.x <= std::max(q1.x, q2.x)) && (p2.y >= std::min(q1.y, q2.y) && p2.y <= std::max(q1.y, q2.y)))) {
        return true;
    }

    return false;
}

GlobalPlanning::Path WaitPointGenerator::GenerateStraitLine(const GlobalPlanning::Point& start, const GlobalPlanning::Point& end) {
    GlobalPlanning::Path result;
    double               length = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
    for (int i = 0; i * out_put_path_dense_ < length - 0.1; i++) {
        GlobalPlanning::Point temp_point;
        temp_point.x         = start.x + i * out_put_path_dense_ * cos(start.angle * M_PI / 180.0);
        temp_point.y         = start.y + i * out_put_path_dense_ * sin(start.angle * M_PI / 180.0);
        temp_point.angle     = start.angle;
        temp_point.curvature = 0;
        result.emplace_back(temp_point);
    }
    return result;
}

double WaitPointGenerator::DeterminateStraightLength(const GlobalPlanning::Point& load_point, GlobalPlanning::CollisonCheck& collision_checker) {
    double result = min_straight_length_;
    for (double i = 0.0; i * delta_straight_length_ + max_straight_length_ >= min_straight_length_; i -= 1.0) {
        double                temp_length   = i * delta_curve_length_ + max_straight_length_ >= min_straight_length_;
        double                succeed_count = 0;
        GlobalPlanning::Point start_end;
        start_end.x         = load_point.x + temp_length * cos(load_point.angle * M_PI / 180.0);
        start_end.y         = load_point.y + temp_length * sin(load_point.angle * M_PI / 180.0);
        start_end.angle     = load_point.angle;
        start_end.curvature = 0.0;

        for (double j = 0; j + delta_steering_angle_ + min_steering_angle_ <= max_steering_angle_; j += 1.0) {
            double steering_angle = j + delta_steering_angle_ + min_steering_angle_;
            auto   arc_path       = CalArcPath(steering_angle, wheel_base_length_, max_curve_length_, start_end);
            if (collision_checker.DepartPathCollisionCheck(arc_path).empty()) {
                succeed_count += 1.0;
            }
        }
        if ((succeed_count / (double)(max_steering_angle_ - min_steering_angle_ + 1)) > 0.6) {
            result = temp_length;
            break;
        }
    }
    return result;
}

vector<arc_sample_point> WaitPointGenerator::SampleCandiPoints(GlobalPlanning::CollisonCheck& collision_checker, double max_steering, double min_steering, const GlobalPlanning::Point& start_point) {
    vector<arc_sample_point> candi_points;
    for (double i = 0.0; i * delta_steering_angle_ + min_steering <= max_steering; i += 1.0) {
        double steer = i * delta_steering_angle_ + min_steering;
        double R;
        if (abs(steer) < 1e-5) {
            R = numeric_limits<double>::infinity(); // Straight driving
        }
        else {
            R = -abs(wheel_base_length_ / tan(steer * M_PI / 180.0));
        }
        if (isinf(R)) {
            arc_sample_point temp_point;
            for (double i = min_curve_length_; i <= max_curve_length_; i += delta_curve_length_) {
                temp_point.path_point.x     = start_point.x + i * cos(start_point.angle * M_PI / 180.0);
                temp_point.path_point.y     = start_point.y + i * sin(start_point.angle * M_PI / 180.0);
                temp_point.path_point.angle = start_point.angle;
                if (collision_checker.IsVehicleCollisionWithAll(temp_point.path_point)) {
                    break;
                }
                temp_point.path_point.curvature = 0.0;
                temp_point.steering             = steer;
                temp_point.arc_length           = i;
                // temp_point.grade                = (weight_length_ * (min_curve_length_ / i) + weight_curve_ * 1.0 / fabs(steer - standard_steering_angle_)) / (weight_length_ + weight_curve_);
                candi_points.emplace_back(temp_point);
            }
        }
        else {
            double               direction   = (steer > 0) ? 1.0 : -1.0; // Left turn (+) or right turn (-)
            pair<double, double> center      = {start_point.x + direction * R * sin(start_point.angle * M_PI / 180.0), start_point.y - direction * R * cos(start_point.angle * M_PI / 180.0)};
            double               theta_start = start_point.angle - direction * 90.0;
            double               theta_range = max_curve_length_ / abs(R) / M_PI * 180.0;
            for (double i = min_curve_length_; i <= max_curve_length_; i += delta_curve_length_) {
                double           t     = static_cast<double>(i) / max_curve_length_;
                double           theta = theta_start + direction * t * theta_range;
                arc_sample_point temp_point;
                temp_point.path_point.x         = center.first + abs(R) * cos(theta * M_PI / 180.0);
                temp_point.path_point.y         = center.second + abs(R) * sin(theta * M_PI / 180.0);
                temp_point.path_point.angle     = theta + direction * 90.0;
                temp_point.path_point.curvature = fabs(1 / R);
                if (collision_checker.IsVehicleCollisionWithAll(temp_point.path_point)) {
                    break;
                }
                temp_point.arc_length = i;
                temp_point.steering   = steer;
                // temp_point.grade      = (weight_length_ * (min_curve_length_ / i) + weight_curve_ * (1.0 - fabs(fabs(steer) - standard_steering_angle_) / standard_steering_angle_)) / (weight_length_ + weight_curve_);
                candi_points.emplace_back(temp_point);
            }
        }
    }
    return candi_points;
}

double WaitPointGenerator::LinearScore(double diff, double target_diff, double tolerance) {
    double error = std::abs(diff - target_diff);
    if (error <= tolerance) {
        return 1.0 - (error / tolerance); // 线性递减
    }
    else {
        return 0.0; // 超出容忍范围，评分为 0
    }
}

double WaitPointGenerator::CalculateGradeAboutLoadPath(const arc_sample_point& sample_point, const GlobalPlanning::Point& closest_point) {
    double dx        = sample_point.path_point.x - closest_point.x;
    double dy        = sample_point.path_point.y - closest_point.y;
    double dist_diff = std::sqrt(dx * dx + dy * dy);

    // 2. 计算角度差（单位：弧度，可调整）
    double angle_diff = std::abs(sample_point.path_point.angle - closest_point.angle);
    angle_diff        = NormalizeAngle(angle_diff);

    // 3. 计算距离评分（越接近 target_dist_diff 越高）
    double dist_score = LinearScore(dist_diff, 15.0, 15.0);

    // 4. 计算角度评分（越接近 target_angle_diff 越高）
    double angle_score = LinearScore(angle_diff, 20.0, 20.0);

    cout << "dist_diff = " << dist_diff << ",angle_diff = " << angle_diff << ",dist_score = " << dist_score << ",angle_score = " << angle_score << ",score = " << (weight_length_ * dist_score + weight_curve_ * angle_score) / (weight_length_ + weight_curve_) << endl;

    // 5. 综合评分（加权平均）
    return (weight_length_ * dist_score + weight_curve_ * angle_score) / (weight_length_ + weight_curve_);
}

double WaitPointGenerator::NormalizeAngle(double angle) {
    angle = fmod(angle + 180.0, 360.0); // 转换到 [0, 360)
    if (angle < 0) angle += 360.0;      // 处理负数情况
    return angle - 180.0;               // 转换到 [-180, 180]
}

void WaitPointGenerator::CalculateWaitPointGrade(const GlobalPlanning::Path& load_path) {
    for (int i = 0; i < wait_point_sample_.size(); i++) {
        auto closest_point = FindNearestPoint(wait_point_sample_[i].path_point.x, wait_point_sample_[i].path_point.y, load_path);
        wait_point_sample_[i].grade += CalculateGradeAboutLoadPath(wait_point_sample_[i], closest_point);
    }
}

GlobalPlanning::Point WaitPointGenerator::FindNearestPoint(double x, double y, const GlobalPlanning::Path& path) {
    // 1. 寻找距离load_point最近的点
    double min_dist    = std::numeric_limits<double>::max();
    int    closest_idx = -1;

    for (int i = 0; i < path.size() - 1; ++i) {
        double dx   = path[i].x - x;
        double dy   = path[i].y - y;
        double dist = std::sqrt(dx * dx + dy * dy);
        if (dist < min_dist) {
            min_dist    = dist;
            closest_idx = i;
        }
    }
    return path[closest_idx];
}

GlobalPlanning::Path WaitPointGenerator::GenerateWaitPointInterface(const GlobalPlanning::Point& load_point, const GlobalPlanning::Path& depart_path, GlobalPlanning::CollisonCheck& collision_checker, FittingPathGenerate::FittingPathGenerator& fitting_path_generator, const GlobalPlanning::Path& in_path) {
    cout << "进入！！！" << endl;
    double expect_straight_length = DeterminateStraightLength(load_point, collision_checker);
    cout << "expect_straight_length = " << expect_straight_length << endl;
    GlobalPlanning::Point straight_end;
    straight_end.x         = load_point.x + expect_straight_length * cos(load_point.angle * M_PI / 180.0);
    straight_end.y         = load_point.y + expect_straight_length * sin(load_point.angle * M_PI / 180.0);
    straight_end.angle     = load_point.angle;
    straight_end.curvature = 0.0;
    auto straight_path     = GenerateStraitLine(load_point, straight_end);
    reverse(straight_path.begin(), straight_path.begin());

    wait_point_sample_ = SampleCandiPoints(collision_checker, max_steering_angle_, min_steering_angle_, straight_end);
    cout << "生成采样点完毕" << endl;
    cout << "wait_point_sample_.size() = " << wait_point_sample_.size() << endl;
    CalculateWaitPointGrade(in_path);
    cout << "代价计算完毕" << endl;
    std::sort(wait_point_sample_.begin(), wait_point_sample_.end(), [](const arc_sample_point& a, const arc_sample_point& b) {
        return a.grade > b.grade; // 按 double 值降序
    });
    cout << "排序完毕" << endl;
    cout << "wait_point_sample_.size() = " << wait_point_sample_.size() << endl;
    for (const auto& point : wait_point_sample_) {
        cout << "point.path_point.x = " << point.path_point.x << endl;
        cout << "point.path_point.y = " << point.path_point.y << endl;
        cout << "point.path_point.angle = " << point.path_point.angle << endl;

        auto wait_path = fitting_path_generator.WaitPathGenerateInterface(in_path, point.path_point, collision_checker);
        if (!wait_path.first.empty()) {
            cout << "驶入规划成功" << endl;
            auto load_path = CalArcPath(point.steering, wheel_base_length_, point.arc_length, straight_end);
            reverse(load_path.begin(), load_path.end());
            load_path.insert(load_path.end(), straight_path.begin(), straight_path.end());
            cout << "load_path.size()=" << load_path.size() << endl;
            if (collision_checker.OptiPathCollisionCheckWithAll(load_path).empty()) {
                cout << "没碰撞load_path.size()=" << load_path.size() << endl;
                return load_path;
            }
        }
    }
    GlobalPlanning::Path empty_path;
    return empty_path;
    // auto standard_path_left = CalArcPath(standard_steering_angle_, wheel_base_length_, max_curve_length_, straight_end);
    // cout << "standard_path_left.size() = " << standard_path_left.size() << endl;
    // if (!standard_path_left.empty()) {
    //     cout << "!standard_path_left.empty()" << endl;
    //     // 左边标准点驶入路径不为空
    //     cout << "standard_path_left.front().x = " << standard_path_left.front().x << endl;
    //     cout << "standard_path_left.front().y = " << standard_path_left.front().y << endl;


    //     auto wait_path = fitting_path_generator.WaitPathGenerateInterface(in_path, standard_path_left.front()); // 生成标准驶入等待点路径
    //     cout << "WaitPathGenerateInterface" << endl;
    //     if (!wait_path.first.empty()) {
    //         cout << "!wait_path.first.empty()" << endl;            // 标准驶入等待点路径不为空
    //         if (!arePathsCrossing(wait_path.first, depart_path)) { // 标准驶入等待点路径不与驶出路径交叉
    //             cout << "!arePathsCrossing(wait_path.first, depart_path)" << endl;
    //             auto candi_points = SampleCandiPointsandSort(collision_checker, load_point, max_steering_angle_, 0.0, straight_end);
    //             cout << "SampleCandiPointsandSort" << endl;
    //             if (!candi_points.empty()) {
    //                 for (auto& point : candi_points) {
    //                     auto load_path = CalArcPath(point.steering, wheel_base_length_, point.arc_length, straight_end);
    //                     load_path.insert(load_path.end(), straight_path.begin(), straight_path.end());
    //                     if (collision_checker.OptiPathCollisionCheckWithAll(load_path).empty()) {
    //                         auto wait_path = fitting_path_generator.WaitPathGenerateInterface(in_path, load_path.front(), collision_checker);
    //                         if (!wait_path.first.empty()) {
    //                             return load_path;
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    // auto candi_points = SampleCandiPointsandSort(collision_checker, load_point, 0.0, min_steering_angle_, straight_end);
    // if (!candi_points.empty()) {
    //     cout << "candi_points.size = " << candi_points.size() << endl;
    //     for (auto& point : candi_points) {
    //         cout << "point.x、y、grade=" << point.path_point.x << "," << point.path_point.y << "," << point.grade << endl;
    //         auto load_path = CalArcPath(point.steering, wheel_base_length_, point.arc_length, straight_end);
    //         reverse(load_path.begin(), load_path.end());
    //         load_path.insert(load_path.end(), straight_path.begin(), straight_path.end());
    //         if (collision_checker.OptiPathCollisionCheckWithAll(load_path).empty()) {
    //             cout << "装载无碰撞" << endl;
    //             cout << "load_path.front().x=" << load_path.front().x << endl;
    //             cout << "load_path.front().y=" << load_path.front().y << endl;
    //             auto wait_path = fitting_path_generator.WaitPathGenerateInterface(in_path, load_path.front(), collision_checker);
    //             cout << "wait_path.size" << wait_path.first.size() << endl;
    //             if (!wait_path.first.empty()) {
    //                 cout << "驶入无碰撞" << endl;
    //                 return load_path;
    //             }
    //         }
    //     }
    // }
}

GlobalPlanning::Path WaitPointGenerator::CalArcPath(double steer, double wheelbase, double arc_total_length, const GlobalPlanning::Point& straight_end) {
    GlobalPlanning::Path path;
    cout << "steer = " << steer << endl;
    cout << "wheelbase = " << wheelbase << endl;
    cout << "arc_total_length = " << arc_total_length << endl;
    cout << "straight_end.angle = " << straight_end.angle << endl;
    cout << "straight_end.X = " << straight_end.x << endl;
    cout << "straight_end.Y = " << straight_end.y << endl;


    // 2. Calculate turning radius R (avoid division by zero)
    double R;
    if (abs(steer) < 1e-5) {
        R = numeric_limits<double>::infinity(); // Straight driving
    }
    else {
        R = -abs(wheelbase / tan(steer * M_PI / 180.0));
    }
    cout << "R = " << R << endl;


    // 3. Generate arc segment
    if (isinf(R)) {
        GlobalPlanning::Point temp_point;
        for (double i = 1; i < max_curve_length_; i += 1.0) {
            temp_point.x         = straight_end.x + i * cos(straight_end.angle * M_PI / 180.0);
            temp_point.y         = straight_end.y + i * sin(straight_end.angle * M_PI / 180.0);
            temp_point.angle     = straight_end.angle;
            temp_point.curvature = 0.0;
            path.emplace_back(temp_point);
        }
    }
    else {
        // Calculate arc center
        double               direction = (steer > 0) ? 1.0 : -1.0; // Left turn (+) or right turn (-)
        pair<double, double> center    = {straight_end.x + direction * R * sin(straight_end.angle * M_PI / 180.0), straight_end.y - direction * R * cos(straight_end.angle * M_PI / 180.0)};
        cout << "center.x = " << center.first << endl;
        cout << "center.y = " << center.second << endl;

        // Arc starting angle (from the end of straight segment)
        double theta_start = straight_end.angle - direction * 90.0;
        cout << "theta_start = " << theta_start << endl;

        // Arc angle range (calculated based on total length)
        double theta_range = arc_total_length / abs(R) / M_PI * 180.0;
        cout << "theta_range = " << theta_range << endl;


        // Generate arc coordinates
        for (int i = 1; i < arc_total_length; ++i) {
            double                t     = static_cast<double>(i) / arc_total_length;
            double                theta = theta_start + direction * t * theta_range;
            GlobalPlanning::Point temp_point;
            temp_point.x         = center.first + abs(R) * cos(theta * M_PI / 180.0);
            temp_point.y         = center.second + abs(R) * sin(theta * M_PI / 180.0);
            temp_point.angle     = theta + direction * 90.0;
            temp_point.curvature = fabs(1 / R);
            path.emplace_back(temp_point);
        }
    }
    return path;
}

WaitPointGenerator::WaitPointGenerator(double max_curve_length, double min_curve_length, double delta_curve_length, double wheel_base_length, double max_straight_length, double min_straight_length, double delta_straight_length, double max_steering_angle, double min_steering_angle, double delta_steering_angle, double standard_steering_angle, double weight_length, double weight_curve, double out_put_path_dense) {
    max_curve_length_        = max_curve_length;
    min_curve_length_        = min_curve_length;
    delta_curve_length_      = delta_curve_length;
    wheel_base_length_       = wheel_base_length;
    max_straight_length_     = max_straight_length;
    min_straight_length_     = min_straight_length;
    delta_straight_length_   = delta_straight_length;
    max_steering_angle_      = max_steering_angle;
    min_steering_angle_      = min_steering_angle;
    delta_steering_angle_    = delta_steering_angle;
    standard_steering_angle_ = standard_steering_angle;
    weight_length_           = weight_length;
    weight_curve_            = weight_curve;
    out_put_path_dense_      = out_put_path_dense;
}

WaitPointGenerator::~WaitPointGenerator() {}

} // namespace WaitPointGenerate
