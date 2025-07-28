#include "../../../include/planner/wait_point_generate/wait_point_generate.h"
namespace WaitPointGenerate {

GlobalPlanning::Path WaitPointGenerator::GenerateWaitPointInterface(const GlobalPlanning::Point& load_point, const GlobalPlanning::Path& depart_path, GlobalPlanning::CollisonCheck& collision_checker) {
    GlobalPlanning::Path                                 result;
    double                                               straight_length;
    std::vector<std::pair<GlobalPlanning::Path, double>> candi_load_pathes;
    for (double i = 0.0; i * delta_curve_length_ + max_straight_length_ >= min_straight_length_; i -= 1.0) {
        double temp_length = i * delta_curve_length_ + max_straight_length_ >= min_straight_length_;
        for (double j = 0; j + delta_steering_angle_ + min_steering_angle_ <= max_steering_angle_; j += 1.0) {
            double steering_angle = j + delta_steering_angle_ + min_steering_angle_;
            auto   arc_path       = CalArcPath(steering_angle, load_point, temp_length, wheel_base_length_, max_curve_length_);
            if (collision_checker.DepartPathCollisionCheck(arc_path).empty()) {
                candi_load_pathes.emplace_back(std::make_pair(arc_path, steering_angle));
            }
        }
        if (((double)candi_load_pathes.size() / (double)(max_steering_angle_ - min_steering_angle_ + 1)) > 0.6) {
            break;
            straight_length = temp_length;
        }
        else {
            candi_load_pathes.clear();
        }
    }
    if (candi_load_pathes.empty()) {
        return result;
    }
    vector<std::pair<GlobalPlanning::Point, double>> candi_wait_points;
    for (int i = min_curve_length_; i < max_curve_length_; i += delta_curve_length_) {
        for (const auto& path : candi_load_pathes) {
            if (!collision_checker.IsVehicleCollisionWithAll(path.first[i])) {
                double grade = weight_curve_ * fabs(path.second - standard_steering_angle_) / standard_steering_angle_ + min_curve_length_ / i * weight_length_;
                candi_wait_points.emplace_back(std::make_pair(path.first[i], grade));
            }
        }
        if (i == standard_steering_angle_) {}
        if (i == -standard_steering_angle_) {}
    }
    if (candi_wait_points.empty()) {
        return result;
    }
}

GlobalPlanning::Path WaitPointGenerator::CalArcPath(double steer, const GlobalPlanning::Point& parking_pose, double straight_length, double wheelbase, double arc_total_length) {
    GlobalPlanning::Path path;

    // 1. Generate initial straight segment
    GlobalPlanning::Point straight_end;
    straight_end.x         = parking_pose.x + straight_length * cos(parking_pose.angle * M_PI / 180.0);
    straight_end.y         = parking_pose.y + straight_length * sin(parking_pose.angle * M_PI / 180.0);
    straight_end.angle     = parking_pose.angle;
    straight_end.curvature = 0.0;


    // 2. Calculate turning radius R (avoid division by zero)
    double R;
    if (abs(steer) < 1e-5) {
        R = numeric_limits<double>::infinity(); // Straight driving
    }
    else {
        R = -abs(wheelbase / tan(steer));
    }

    // 3. Generate arc segment
    if (isinf(R)) {
        GlobalPlanning::Point temp_point;
        for (double i = 1; i < max_curve_length_; i += 0.1) {
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
        pair<double, double> center    = {straight_end.x + direction * R * sin(parking_pose.angle * M_PI / 180.0), straight_end.y - direction * R * cos(parking_pose.angle * M_PI / 180.0)};

        // Arc starting angle (from the end of straight segment)
        double theta_start = parking_pose.angle - direction * 180.0;

        // Arc angle range (calculated based on total length)
        double theta_range = arc_total_length / abs(R) / M_PI * 180.0;

        // Generate arc coordinates
        for (int i = 1; i < arc_total_length; ++i) {
            double                t     = static_cast<double>(i) / arc_total_length;
            double                theta = theta_start + direction * t * theta_range;
            GlobalPlanning::Point temp_point;
            temp_point.x         = center.first + abs(R) * cos(theta);
            temp_point.y         = center.second + abs(R) * sin(theta);
            temp_point.angle     = theta;
            temp_point.curvature = fabs(1 / R);
            path.emplace_back(temp_point);
        }
    }

    return path;
}
WaitPointGenerator::WaitPointGenerator(double max_curve_length, double min_curve_length, double delta_curve_length, double wheel_base_length, double center2side, double max_straight_length, double min_straight_length, double delta_straight_length, double max_steering_angle, double min_steering_angle, double delta_steering_angle, double standard_steering_angle, double weight_length, double weight_curve) {
    max_curve_length_        = max_curve_length;
    min_curve_length_        = min_curve_length;
    delta_curve_length_      = delta_curve_length;
    wheel_base_length_       = wheel_base_length;
    center2side_             = center2side;
    max_straight_length_     = max_straight_length;
    min_straight_length_     = min_straight_length;
    delta_straight_length_   = delta_straight_length;
    max_steering_angle_      = max_steering_angle;
    min_steering_angle_      = min_steering_angle;
    delta_steering_angle_    = delta_steering_angle;
    standard_steering_angle_ = standard_steering_angle;
    weight_length_           = weight_length;
    weight_curve_            = weight_curve;
}
WaitPointGenerator::~WaitPointGenerator() {}

} // namespace WaitPointGenerate