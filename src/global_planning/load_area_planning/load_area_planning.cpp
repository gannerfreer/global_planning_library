#include "load_area_planning.h"
namespace LoadAreaPlanning {
std::tuple<int, GlobalPlanning::Point, GlobalPlanning::Path, GlobalPlanning::Path, GlobalPlanning::Path> LoadAreaPlanning::LoadAreaPlanningInterface(int planning_mode, const GlobalPlanning::Point& wait_point, const GlobalPlanning::Point& load_point, const GlobalPlanning::Path& in_path, GlobalPlanning::Path out_path, GlobalPlanning::CollisonCheck collision_checker) {
    FittingPathGenerate::FittingPathGenerator fit_path_planner(out_put_path_dense_, search_range_, jump_dense_, length_weight_, curvature_weight_, critical_length_, min_straight_length_depart_, max_straight_length_depart_, delta_straight_length_depart_, min_straight_length_wait_, max_straight_length_wait_, delta_straight_length_wait_, min_straight_length_load_, max_straight_length_load_, delta_straight_length_load_, load_path_straight_length_weight_, load_path_curvature_weight_);
    GlobalPlanning::Path                      wait_path;
    GlobalPlanning::Path                      load_path;
    GlobalPlanning::Path                      depart_path;
    GlobalPlanning::Point                     queue_point;
    depart_path = fit_path_planner.DepartPathGenerateInterface(out_path, load_point, collision_checker).first;
    if (depart_path.empty()) {
        return std::make_tuple(0, queue_point, wait_path, load_path, depart_path);
    }
    if (planning_mode == 1) { // 尝试人工指定排队点
        wait_path = fit_path_planner.WaitPathGenerateInterface(in_path, wait_point, collision_checker).first;
        if (wait_path.empty()) {
            return std::make_tuple(0, queue_point, wait_path, load_path, depart_path);
        }
        load_path = fit_path_planner.LoadPathGenerateInterface(load_point, wait_point, collision_checker).first;
        if (load_path.empty()) {
            return std::make_tuple(0, queue_point, wait_path, load_path, depart_path);
        }

        return std::make_tuple(1, wait_point, wait_path, load_path, depart_path);
    }
    if (planning_mode == 2) {
        load_path = fit_path_planner.LoadPathGenerateInterface(load_point, wait_point, collision_checker).first;
        if (load_path.empty()) {
            planning_mode = 0;
        }
        else {
            wait_path = fit_path_planner.WaitPathGenerateInterface(in_path, wait_point, collision_checker).first;
            if (wait_path.empty()) {
                return std::make_tuple(0, queue_point, wait_path, load_path, depart_path);
            }
            return std::make_tuple(1, wait_point, wait_path, load_path, depart_path);
        }
    }
    if (planning_mode == 0) {
        WaitPointGenerate::WaitPointGenerator wait_point_planner(max_curve_length_, min_curve_length_, delta_curve_length_, wheel_base_length_, max_straight_length_, min_straight_length_, delta_straight_length_, max_steering_angle_, min_steering_angle_, delta_steering_angle_, standard_steering_angle_, weight_length_, weight_curve_, out_put_path_dense_);
        load_path = wait_point_planner.GenerateWaitPointInterface(load_point, depart_path, collision_checker, fit_path_planner, in_path);
        if (load_path.empty()) {
            return std::make_tuple(0, queue_point, wait_path, load_path, depart_path);
        }
        queue_point = load_path.front();
        wait_path   = fit_path_planner.WaitPathGenerateInterface(in_path, queue_point).first;
        if (wait_path.empty()) {
            return std::make_tuple(0, queue_point, wait_path, load_path, depart_path);
        }
        return std::make_tuple(1, queue_point, wait_path, load_path, depart_path);
    }
}
LoadAreaPlanning::~LoadAreaPlanning() {}

} // namespace LoadAreaPlanning
