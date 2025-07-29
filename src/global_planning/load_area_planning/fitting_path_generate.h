#ifndef FITTING_PATH_GENERATE
#define FITTING_PATH_GENERATE

#include <algorithm>
#include <cmath>
#include <string>
#include <tuple>

#include "../collision_check/collision_check.h"
#include "../common/common_struct.h"
#include "../planner/pathplanner/dubins/dubins.h"

namespace FittingPathGenerate {
class FittingPathGenerator {
  private:
    double                                               load_path_straight_length_weight_;
    double                                               load_path_curvature_weight_;
    double                                               out_put_path_dense_;
    double                                               search_range_;
    double                                               jump_dense_;
    double                                               length_weight_;
    double                                               critical_length_;
    double                                               curvature_weight_;
    double                                               min_straight_length_depart_;
    double                                               max_straight_length_depart_;
    double                                               delta_straight_length_depart_;
    double                                               min_straight_length_wait_;
    double                                               max_straight_length_wait_;
    double                                               delta_straight_length_wait_;
    double                                               min_straight_length_load_;
    double                                               max_straight_length_load_;
    double                                               delta_straight_length_load_;
    std::vector<std::pair<GlobalPlanning::Path, double>> depart_path_candidates_;
    std::vector<std::pair<GlobalPlanning::Path, double>> wait_path_candidates_;
    std::vector<std::pair<GlobalPlanning::Path, double>> load_path_candidates_;
    GlobalPlanning::Path                                 PathTransFormer(const std::vector<curve::Point> curve_path);
    double                                               CalPathQuality(const GlobalPlanning::Path& path, double length_weight = 1.0, double curvature_weight = 1.0, double critical_length = 25.0);
    void                                                 PathRateAndSort(std::vector<std::pair<GlobalPlanning::Path, double>>& candi_pathes);
    void                                                 CalCurvature(GlobalPlanning::Path& path, int check_dense);
    std::vector<GlobalPlanning::Point>                   SamplePathSegment(const GlobalPlanning::Path& target_path, const GlobalPlanning::Point& load_point);
    GlobalPlanning::Path                                 GenerateStraitLine(const GlobalPlanning::Point& start, const GlobalPlanning::Point& end);
    GlobalPlanning::Path                                 final_depart_path_;
    GlobalPlanning::Path                                 final_wait_path_;
    GlobalPlanning::Path                                 PathCuttoEnd(const GlobalPlanning::Point& point, const GlobalPlanning::Path& path);
    GlobalPlanning::Path                                 PathCuttoStart(const GlobalPlanning::Point& point, const GlobalPlanning::Path& path);


  public:
    FittingPathGenerator(double out_put_path_dense, double search_range, double jump_dense, double length_weight, double curvature_weight, double critical_length, double min_straight_line_length, double max_straight_line_length, double delta_straight_line_length, double min_straight_length_wait, double max_straight_length_wait, double delta_straight_length_wait, double min_straight_length_load, double max_straight_length_load, double delta_straight_length_load, double straight_length_weight, double load_path_curvature_weight);
    ~FittingPathGenerator();
    std::pair<GlobalPlanning::Path, double>              DepartPathGenerateInterface(const GlobalPlanning::Path& target_path, const GlobalPlanning::Point& load_point, GlobalPlanning::CollisonCheck& collision_checker);
    std::pair<GlobalPlanning::Path, double>              WaitPathGenerateInterface(const GlobalPlanning::Path& origin_path, const GlobalPlanning::Point& wait_point, GlobalPlanning::CollisonCheck& collision_checker);
    std::pair<GlobalPlanning::Path, double>              WaitPathGenerateInterface(const GlobalPlanning::Path& origin_path, const GlobalPlanning::Point& wait_point);
    std::pair<GlobalPlanning::Path, double>              LoadPathGenerateInterface(const GlobalPlanning::Point& load_point, const GlobalPlanning::Point& wait_point, GlobalPlanning::CollisonCheck& collision_checker);
    std::vector<std::pair<GlobalPlanning::Path, double>> GetWaitPathCandis() {
        return wait_path_candidates_;
    }
    std::vector<std::pair<GlobalPlanning::Path, double>> GetDepartPathCandis() {
        return depart_path_candidates_;
    }
    std::vector<std::pair<GlobalPlanning::Path, double>> GetLoadPathCandis() {
        return load_path_candidates_;
    }
};
} // namespace FittingPathGenerate
#endif