//
// Created by ljn on 20-5-4.
//

#ifndef PATH_OPTIMIZER_INCLUDE_PATH_OPTIMIZER_REFERENCE_PATH_SMOOTHER_TENSION_SMOOTHER_2_HPP_
#define PATH_OPTIMIZER_INCLUDE_PATH_OPTIMIZER_REFERENCE_PATH_SMOOTHER_TENSION_SMOOTHER_2_HPP_
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <cfloat>
#include <cppad/cppad.hpp>
#include <cppad/ipopt/solve.hpp>
#include <vector>

#include "../common/common_struct.h"
#include "OsqpEigen/OsqpEigen.h"

namespace GlobalPlanning {

using CppAD::AD;
// class FgEvalReferenceSmoothing {
//   public:
//     FgEvalReferenceSmoothing(const std::vector<double>& seg_x_list, const
//     std::vector<double>& seg_y_list, const std::vector<double>& seg_s_list,
//     const std::vector<double>& seg_angle_list) : seg_s_list_(seg_s_list),
//     seg_x_list_(seg_x_list), seg_y_list_(seg_y_list),
//     seg_angle_list_(seg_angle_list) {} virtual ~FgEvalReferenceSmoothing() =
//     default; typedef CPPAD_TESTVECTOR(AD<double>) ADvector; typedef
//     AD<double> ad; virtual void       operator()(ADvector& fg, const
//     ADvector& vars);

//   protected:
//     const std::vector<double>& seg_s_list_;
//     const std::vector<double>& seg_x_list_;
//     const std::vector<double>& seg_y_list_;
//     const std::vector<double>& seg_angle_list_;
// };
// class FgEvalQPSmoothing : public FgEvalReferenceSmoothing {

// struct _TrajectoryPoint {
//   double x;         // x坐标(单位：m)
//   double y;         // y坐标(单位：m)
//   double z;         // z坐标(单位：m)
//   double yaw;       // 朝向(单位：0~360deg)
//   double curvature; // 轨迹的曲率(单位：rad/s)
//   double distance;

//   inline void Clear() { x = y = z = yaw = curvature = distance = 0; }
//   _TrajectoryPoint() : x(0), y(0), z(0), yaw(0), curvature(0), distance(0) {}
//   _TrajectoryPoint(double x_val, double y_val, double yaw_val)
//       : x(x_val), y(y_val), z(0), yaw(yaw_val), curvature(0), distance(0) {}
// };

class FgEvalQPSmoothing {
  public:
    FgEvalQPSmoothing(const std::vector<double>& seg_x_list, const std::vector<double>& seg_y_list, const std::vector<double>& seg_s_list, const std::vector<double>& seg_angle_list, const std::vector<double>& seg_k_list, const _VehicleParam& m_vehicle_param);
    ~FgEvalQPSmoothing() = default;
    typedef CPPAD_TESTVECTOR(AD<double>) ADvector;
    typedef AD<double> ad;
    void               operator()(ADvector& fg, const ADvector& vars);

  private:
    const std::vector<double>& seg_k_list_;
    const std::vector<double>& seg_s_list_;
    const std::vector<double>& seg_x_list_;
    const std::vector<double>& seg_y_list_;
    const std::vector<double>& seg_angle_list_;
    const _VehicleParam&       m_vehicle_param_;
};

class TensionSmoother2 {
  public:
    TensionSmoother2() = delete;
    TensionSmoother2(const std::vector<Point>& input_points, _VehicleParam m_vehicle_param);
    ~TensionSmoother2() = default;

  public:
    bool                            smooth(std::vector<Point>& result);
    bool                            ipoptSmooth(const std::vector<double>& x_list, const std::vector<double>& y_list, const std::vector<double>& angle_list, const std::vector<double>& k_list, const std::vector<double>& s_list, std::vector<double>* result_x_list, std::vector<double>* result_y_list, std::vector<double>* result_s_list, std::vector<double>* result_curvature_list, std::vector<double>* result_angle_list);
    bool                            osqpSmooth(const std::vector<double>& x_list, const std::vector<double>& y_list, const std::vector<double>& angle_list, const std::vector<double>& k_list, const std::vector<double>& s_list, std::vector<double>* result_x_list, std::vector<double>* result_y_list, std::vector<double>* result_s_list, std::vector<double>* result_curvature_list, std::vector<double>* result_angle_list);
    void                            setHessianMatrix(size_t size, Eigen::SparseMatrix<double>* matrix_h) const;
    void                            setConstraintMatrix(const std::vector<double>& x_list, const std::vector<double>& y_list, const std::vector<double>& angle_list, const std::vector<double>& k_list, const std::vector<double>& s_list, Eigen::SparseMatrix<double>* matrix_constraints, Eigen::VectorXd* lower_bound, Eigen::VectorXd* upper_bound) const;
    void                            setGradient(const std::vector<double>& x_list, const std::vector<double>& y_list, Eigen::VectorXd* gradient);
    std::vector<Point>   input_points_;
    _VehicleParam                   m_vehicle_param_;
    std::shared_ptr<spdlog::logger> threadLogger_;
};
} // namespace GlobalPlanning
#endif // PATH_OPTIMIZER_INCLUDE_PATH_OPTIMIZER_REFERENCE_PATH_SMOOTHER_TENSION_SMOOTHER_2_HPP_
