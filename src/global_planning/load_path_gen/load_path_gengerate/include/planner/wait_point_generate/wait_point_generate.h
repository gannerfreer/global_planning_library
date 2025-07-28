#ifndef WAIT_POINT_GENERATE
#define WAIT_POINT_GENERATE
#include "../fitting_path_generate/fitting_path_generate.h"
namespace WaitPointGenerate {
class WaitPointGenerator {
  private:
    double               max_curve_length_;
    double               min_curve_length_;
    double               delta_curve_length_;
    double               wheel_base_length_;
    double               center2side_;
    double               max_straight_length_;
    double               min_straight_length_;
    double               delta_straight_length_;
    double               max_steering_angle_;
    double               min_steering_angle_;
    double               delta_steering_angle_;
    double               standard_steering_angle_;
    double               weight_length_;
    double               weight_curve_;
    GlobalPlanning::Path CalArcPath(double steer, const GlobalPlanning::Point& parking_pose, double straight_length, double wheelbase, double arc_total_length);

  public:
    GlobalPlanning::Path GenerateWaitPointInterface(const GlobalPlanning::Point& load_point, const GlobalPlanning::Path& depart_path, GlobalPlanning::CollisonCheck& collision_checker);
    WaitPointGenerator(double max_curve_length, double min_curve_length, double delta_curve_length, double wheel_base_length, double center2side, double max_straight_length, double min_straight_length, double delta_straight_length, double max_steering_angle, double min_steering_angle, double delta_steering_angle, double standard_steering_angle, double weight_length, double weight_curve);
    ~WaitPointGenerator();
};
} // namespace WaitPointGenerate

#endif