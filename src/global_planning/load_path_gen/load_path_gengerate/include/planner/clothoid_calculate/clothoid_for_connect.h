#ifndef CLOTHOID_FOR_CONNECT
#define CLOTHOID_FOR_CONNECT

#include <Eigen/Dense>
#include <algorithm>
#include <cmath>
#include <string>

#include "../../common/common_struct.h"
using namespace Eigen;
namespace ClothoidPlanner {
class ClothoidParamCalculator {
  private:
    double input_path_dense_             = 0.1;
    double straight_path_cut_max_length_ = 5.0;
    double curvature_changing_rate_      = 0.04;

    VectorXd                     equations(const VectorXd& vars, double a, double b, double delta);
    void                         fresnel_integral(double t, double& C, double& S);
    VectorXd                     solve_equations(double a, double b, double delta, const VectorXd& initial_guess, double tol = 1e-6, int max_iter = 100);
    GlobalPlanning::_SinglePoint TransformCoordinate(const GlobalPlanning::_SinglePoint& original_pose, double new_origin_x, double new_origin_y, double new_origin_yaw);

  public:
    ClothoidParamCalculator(double input_path_dense, double straight_path_cut_max_length, double curvature_changing_rate);
    ~ClothoidParamCalculator();
    GlobalPlanning::_ClothoidParam ClothoidParamCalculatorInterface(const vector<GlobalPlanning::_TrajectoryPoint>& straight_path, const vector<GlobalPlanning::_TrajectoryPoint>& arc_path, const GlobalPlanning::_SinglePoint arc_center, const double arc_radius);
};
} // namespace ClothoidPlanner
#endif