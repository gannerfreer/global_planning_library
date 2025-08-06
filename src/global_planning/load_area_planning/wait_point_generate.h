#ifndef WAIT_POINT_GENERATE
#define WAIT_POINT_GENERATE
#include "fitting_path_generate.h"
namespace WaitPointGenerate {
struct arc_sample_point {
    GlobalPlanning::Point path_point;
    double                steering;
    double                arc_length;
    double                grade;
};

class WaitPointGenerator {
  private:
    double                   center2front_;
    double                   center2side_;
    double                   center2rear_;
    double                   safe_margin_front_;
    double                   safe_margin_2side_;
    double                   safe_margin_rear_;
    double                   max_curve_length_;
    double                   min_curve_length_;
    double                   delta_curve_length_;
    double                   wheel_base_length_;
    double                   max_straight_length_;
    double                   min_straight_length_;
    double                   delta_straight_length_;
    double                   max_steering_angle_;
    double                   min_steering_angle_;
    double                   delta_steering_angle_;
    double                   standard_steering_angle_;
    double                   weight_length_;
    double                   weight_curve_;
    double                   out_put_path_dense_;
    double                   collision_weight_;
    GlobalPlanning::Path     CalArcPath(double steer, double wheelbase, double arc_total_length, const GlobalPlanning::Point& straight_end);
    double                   DeterminateStraightLength(const GlobalPlanning::Point& load_point, GlobalPlanning::CollisonCheck& collision_checker);
    vector<arc_sample_point> SampleCandiPoints(GlobalPlanning::CollisonCheck& collision_checker, double max_steering, double min_steering, const GlobalPlanning::Point& start_point, const GlobalPlanning::Path& depart_path);
    double                   distanceSquared(const GlobalPlanning::Point& point, const GlobalPlanning::Point& other) const;
    bool                     doSegmentsIntersect(const GlobalPlanning::Point& p1, const GlobalPlanning::Point& p2, const GlobalPlanning::Point& q1, const GlobalPlanning::Point& q2);
    bool                     arePathsCrossing(const std::vector<GlobalPlanning::Point>& path1, const std::vector<GlobalPlanning::Point>& path2, double distanceThreshold = 5.0);
    GlobalPlanning::Path     GenerateStraitLine(const GlobalPlanning::Point& start, const GlobalPlanning::Point& end);
    void                     CalculateWaitPointGrade(const GlobalPlanning::Path& load_path, const GlobalPlanning::Point& load_point);
    GlobalPlanning::Point    FindNearestPoint(double x, double y, const GlobalPlanning::Path& path);
    double                   CalculateGradeAboutLoadPath(const arc_sample_point& sample_point, const GlobalPlanning::Point& closest_point);
    double                   NormalizeAngle(double angle);
    double                   LinearScore(double diff, double target_diff, double tolerance);
    double                   CalculateGradeAboutLoadPoint(const arc_sample_point& sample_point, const GlobalPlanning::Point& load_point, const GlobalPlanning::Point& closest_point);
    double                   normalizeAngle360(double angle);
    double                   calculateAcuteBisector(double angle1, double angle2);
    bool                     IsPathCollision(const GlobalPlanning::Path& wait_path, const GlobalPlanning::Path& depart_path, double center2front, double center2rear, double center2side, double safe_margin_front, double safe_margin_rear, double safe_margin_side);

  public:
    GlobalPlanning::Path GenerateWaitPointInterface(const GlobalPlanning::Point& load_point, const GlobalPlanning::Path& depart_path, GlobalPlanning::CollisonCheck& collision_checker, FittingPathGenerate::FittingPathGenerator& fitting_path_generator, const GlobalPlanning::Path& in_path);
    WaitPointGenerator(double max_curve_length, double min_curve_length, double delta_curve_length, double wheel_base_length, double max_straight_length, double min_straight_length, double delta_straight_length, double max_steering_angle, double min_steering_angle, double delta_steering_angle, double standard_steering_angle, double weight_length, double weight_curve, double out_put_path_dense, double center2front, double center2side, double center2rear, double safe_margin_front, double safe_margin_2side, double safe_margin_rear, double collision_weight);
    vector<arc_sample_point> wait_point_sample_;


    ~WaitPointGenerator();
}; // namespace WaitPointGenerate
} // namespace WaitPointGenerate
#endif