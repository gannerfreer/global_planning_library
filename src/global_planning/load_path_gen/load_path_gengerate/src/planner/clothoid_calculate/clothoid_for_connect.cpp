#include "../../../include/planner/clothoid_calculate/clothoid_for_connect.h"


namespace ClothoidPlanner {
// 默认构造与析构函数实现
ClothoidParamCalculator::~ClothoidParamCalculator() {}
ClothoidParamCalculator::ClothoidParamCalculator(double input_path_dense, double straight_path_cut_max_length, double curvature_changing_rate) {
    input_path_dense_             = input_path_dense;
    straight_path_cut_max_length_ = straight_path_cut_max_length;
    curvature_changing_rate_      = curvature_changing_rate;
}
GlobalPlanning::_ClothoidParam ClothoidParamCalculator::ClothoidParamCalculatorInterface(const vector<GlobalPlanning::_TrajectoryPoint>& straight_path, const vector<GlobalPlanning::_TrajectoryPoint>& arc_path, const GlobalPlanning::_SinglePoint arc_center, const double arc_radius) {
    GlobalPlanning::_ClothoidParam result;
    if (straight_path.empty() or arc_path.empty()) {
        std::cout << "入参为空，直接退出" << endl;
        return result;
    }

    vector<GlobalPlanning::_TrajectoryPoint> straight_line_point_for_trail;
    int                                      straight_point_trail_num = (int)(straight_path_cut_max_length_ / input_path_dense_);
    if (straight_point_trail_num > straight_path.size()) straight_point_trail_num = straight_path.size();
    straight_line_point_for_trail.assign(straight_path.rbegin(), straight_path.rbegin() + straight_point_trail_num);

    double total_length     = 1 / arc_radius / curvature_changing_rate_; // 猜测回旋线的大致长度
    double arc_total_length = (arc_path.size() - 1) * input_path_dense_;

    for (int i = 0; i < straight_line_point_for_trail.size(); i++) {
        auto                         new_arc_center  = TransformCoordinate(arc_center, straight_line_point_for_trail[i].x, straight_line_point_for_trail[i].y, straight_line_point_for_trail[i].yaw); // 先进行坐标转换
        double                       straight_length = input_path_dense_ * i;
        VectorXd                     guess_solution(6, 1);
        GlobalPlanning::_SinglePoint end_point;
        std::cout << "straight_length = " << straight_length << endl;

        if (total_length < straight_length) {
            end_point.x       = arc_path.front().x;
            end_point.y       = arc_path.front().y;
            end_point.yaw     = arc_path.front().yaw;
            guess_solution[2] = straight_length;
        }
        else {
            double arc_length      = total_length - straight_length;
            int    end_point_index = (int)(arc_length / input_path_dense_);
            end_point_index        = std::min(end_point_index, (int)(arc_path.size() - 1));
            end_point.x            = arc_path[end_point_index].x;
            end_point.y            = arc_path[end_point_index].y;
            end_point.yaw          = arc_path[end_point_index].yaw;
            guess_solution[2]      = total_length - straight_length;
        }

        auto new_end_point          = TransformCoordinate(end_point, straight_line_point_for_trail[i].x, straight_line_point_for_trail[i].y, straight_line_point_for_trail[i].yaw);
        guess_solution[0]           = new_end_point.x;
        guess_solution[1]           = new_end_point.y;
        guess_solution[3]           = new_end_point.yaw;
        guess_solution[4]           = curvature_changing_rate_;
        guess_solution[5]           = sqrt(1 / curvature_changing_rate_ * curvature_changing_rate_);
        auto final_suolution        = solve_equations(new_arc_center.x, new_arc_center.y, 1 / arc_radius, guess_solution);
        result.start_x              = straight_line_point_for_trail[i].x;
        result.start_y              = straight_line_point_for_trail[i].y;
        result.start_theta          = straight_line_point_for_trail[i].yaw;
        result.start_curvature      = 0;
        result.curvatrue_derivative = final_suolution[4];
        result.totle_length         = final_suolution[2];
        std::cout << "x,y,yaw,curvature,length,curvature_rate = " << result.start_x << "," << result.start_y << "," << result.start_theta << "," << result.start_curvature << "," << result.totle_length << "," << result.curvatrue_derivative << std::endl;

        if (result.totle_length > 0 and fabs(result.curvatrue_derivative) < 0.04) {
            return result;
        }
    }
}


// 定义方程组残差
VectorXd ClothoidParamCalculator::equations(const VectorXd& vars, double a, double b, double delta) {
    double x     = vars[0];
    double y     = vars[1];
    double L     = vars[2];
    double phi   = vars[3];
    double sigma = vars[4];
    double A     = vars[5];

    VectorXd residuals(7);

    // 圆弧方程
    residuals(0) = pow(x - a, 2) + pow(y - b, 2) - 1.0 / (delta * delta);

    // 角度关系
    residuals(1) = tan(phi) - (x - a) / (b - y);

    // 回旋线方程
    double Cf, Sf;
    fresnel_integral(L / (M_PI * A), Cf, Sf);
    residuals(2) = x - A * sqrt(M_PI) * Cf;
    residuals(3) = y - A * sqrt(M_PI) * Sf;
    residuals(4) = phi - (A * A * delta) / 2.0;

    // 曲率关系
    residuals(5) = delta - L * sigma;
    residuals(6) = A * A - 1.0 / sigma;

    return residuals;
}

void ClothoidParamCalculator::fresnel_integral(double t, double& C, double& S) {
    const int n  = 100; // 积分分段数
    double    dt = t / n;
    C            = 0.0;
    S            = 0.0;

    for (int i = 0; i < n; ++i) {
        double u = (i + 0.5) * dt;
        C += cos(M_PI * u * u / 2) * dt;
        S += sin(M_PI * u * u / 2) * dt;
    }
}

// 牛顿迭代法求解
VectorXd ClothoidParamCalculator::solve_equations(double a, double b, double delta, const VectorXd& initial_guess, double tol, int max_iter) {
    VectorXd vars = initial_guess;

    for (int iter = 0; iter < max_iter; ++iter) {
        VectorXd res = equations(vars, a, b, delta);

        if (res.norm() < tol) {
            std::cout << "Converged after " << iter << " iterations." << std::endl;
            return vars;
        }

        // 数值计算雅可比矩阵
        MatrixXd J(7, 6);
        double   h = 1e-6;

        for (int i = 0; i < 6; ++i) {
            VectorXd vars_plus = vars;
            vars_plus(i) += h;
            VectorXd res_plus = equations(vars_plus, a, b, delta);
            J.col(i)          = (res_plus - res) / h;
        }

        // 最小二乘解
        vars = vars - J.jacobiSvd(ComputeThinU | ComputeThinV).solve(res);
    }

    std::cout << "Warning: Did not converge within " << max_iter << " iterations." << std::endl;
    return vars;
}

GlobalPlanning::_SinglePoint ClothoidParamCalculator::TransformCoordinate(const GlobalPlanning::_SinglePoint& original_pose, double new_origin_x, double new_origin_y, double new_origin_yaw) {
    GlobalPlanning::_SinglePoint transformed_pose;

    // 1. 平移变换：将原点移动到 (new_origin_x, new_origin_y)
    double dx = original_pose.x - new_origin_x;
    double dy = original_pose.y - new_origin_y;

    // 2. 旋转变换：考虑 new_origin_yaw 角度
    double cos_yaw = cos(new_origin_yaw);
    double sin_yaw = sin(new_origin_yaw);

    // 新坐标系下的位置
    transformed_pose.x = dx * cos_yaw + dy * sin_yaw;
    transformed_pose.y = -dx * sin_yaw + dy * cos_yaw;

    // 3. 朝向角转换：减去新坐标系的朝向角
    transformed_pose.yaw = original_pose.yaw - new_origin_yaw;

    // 规范化角度到 [-π, π] 范围内
    while (transformed_pose.yaw > M_PI) transformed_pose.yaw -= 2 * M_PI;
    while (transformed_pose.yaw < -M_PI) transformed_pose.yaw += 2 * M_PI;

    return transformed_pose;
}


} // namespace ClothoidPlanner