#ifndef LOAD_AREA_PLANNING
#define LOAD_AREA_PLANNING
#include "../fitting_path_generate/fitting_path_generate.h"
#include "../wait_point_generate/wait_point_generate.h"
#include "../../common/common_struct.h"
namespace LoadAreaPlanning {
class LoadAreaPlanning {
  private:
    double max_curve_length_;                 // 圆弧直线倒车最大曲线长度
    double min_curve_length_;                 // 圆弧直线倒车最小曲线长度
    double delta_curve_length_;               // 圆弧直线倒车曲线长度采样间距
    double wheel_base_length_;                // 车辆轴距
    double center2side_;                      // 车辆宽度
    double max_straight_length_;              // 圆弧直线倒车最大直线长度
    double min_straight_length_;              // 圆弧直线倒车最小直线长度
    double delta_straight_length_;            // 圆弧直线倒车直线采样间距
    double max_steering_angle_;               // 圆弧直线倒车最大转向角
    double min_steering_angle_;               // 圆弧直线倒车最小转向角
    double delta_steering_angle_;             // 圆弧直线倒车转角采样间距
    double standard_steering_angle_;          // 标准倒车转角
    double weight_length_;                    // 圆弧直线倒车长度评分权重
    double weight_curve_;                     // 圆弧直线倒车转角评分权重
    double load_path_straight_length_weight_; // 前往装载点路径直线长度权重
    double load_path_curvature_weight_;       // 前往装载点路径曲率权重
    double out_put_path_dense_;               // 输出路径密度
    double search_range_;                     // 寻找周围路径范围
    double jump_dense_;                       // 在目标路径上取点的密度
    double length_weight_;                    // 前进路径直线长度权重
    double critical_length_;                  // 前进路径长度标准值
    double curvature_weight_;                 // 前进路径曲率权重
    double min_straight_length_depart_;       // 驶离路径最短直线长度
    double max_straight_length_depart_;       // 驶离路径最长直线长度
    double delta_straight_length_depart_;     // 驶离路径长度采样间距
    double min_straight_length_wait_;         // 前往等待点路径直线长度最大值
    double max_straight_length_wait_;         // 前往等待点路径直线长度最小值
    double delta_straight_length_wait_;       // 前往等待点路径直线长度采样间距
    double min_straight_length_load_;         // 前往装载点路径直线长度最小值
    double max_straight_length_load_;         // 前往装载点路径直线长度最大值
    double delta_straight_length_load_;       // 前往装载点路径直线长度采样间距

  public:
    ~LoadAreaPlanning();
    shared_ptr<spdlog::logger> threadLogger_;
    std::tuple<bool, GlobalPlanning::Point, GlobalPlanning::Path, GlobalPlanning::Path, GlobalPlanning::Path> LoadAreaPlanningInterface(int planning_mode, const GlobalPlanning::Point& wait_point, const GlobalPlanning::Point& load_poit, const GlobalPlanning::Path& in_path, GlobalPlanning::Path out_path, GlobalPlanning::CollisonCheck& collision_checker);
};
} // namespace LoadAreaPlanning

#endif