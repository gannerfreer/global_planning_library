//
// Created by ljn on 20-5-4.
// improved by yanyifeng/chenxinpeng on 25-8-29
//
#include "tension_smoother_2.hpp"

#include <cppad/core/pow.hpp>

#include "OsqpEigen/OsqpEigen.h"

namespace GlobalPlanning {

FgEvalQPSmoothing::FgEvalQPSmoothing(const std::vector<double>& seg_x_list, const std::vector<double>& seg_y_list, const std::vector<double>& seg_s_list, const std::vector<double>& seg_angle_list, const std::vector<double>& seg_k_list, const _VehicleParam& m_vehicle_param) : seg_k_list_(seg_k_list), seg_s_list_(seg_s_list), seg_x_list_(seg_x_list), seg_y_list_(seg_y_list), seg_angle_list_(seg_angle_list), m_vehicle_param_(m_vehicle_param) {}

void FgEvalQPSmoothing::operator()(GlobalPlanning::FgEvalQPSmoothing::ADvector& fg, const GlobalPlanning::FgEvalQPSmoothing::ADvector& vars) {
    size_t point_num       = seg_s_list_.size();
    size_t x_idx_begin     = 0;
    size_t y_idx_begin     = x_idx_begin + point_num;
    size_t theta_idx_begin = y_idx_begin + point_num;
    size_t k_idx_begin     = theta_idx_begin + point_num;

    size_t cons_x_idx_begin              = 1;
    size_t cons_y_idx_begin              = cons_x_idx_begin + point_num - 1;
    size_t cons_theta_idx_begin          = cons_y_idx_begin + point_num - 1;
    size_t cons_curvature_rate_idx_begin = cons_theta_idx_begin + point_num - 1;
    std::cout << "w_curvature_change" << m_vehicle_param_.w_curvature_change << std::endl;
    std::cout << "w_curvature" << m_vehicle_param_.w_curvature << std::endl;
    std::cout << "w_deviation" << m_vehicle_param_.w_deviation << std::endl;
    for (size_t i = 0; i < point_num - 1; ++i) {
        ad cur_x      = vars[x_idx_begin + i];
        ad next_x     = vars[x_idx_begin + i + 1];
        ad ref_x      = seg_x_list_[i];
        ad cur_y      = vars[y_idx_begin + i];
        ad next_y     = vars[y_idx_begin + i + 1];
        ad ref_y      = seg_y_list_[i];
        ad cur_theta  = vars[theta_idx_begin + i];
        ad next_theta = vars[theta_idx_begin + i + 1];
        ad ds         = seg_s_list_[i + 1] - seg_s_list_[i];
        ad cur_k      = vars[k_idx_begin + i];

        // cost
        fg[0] += m_vehicle_param_.w_deviation * (pow(cur_x - ref_x, 2) + pow(cur_y - ref_y, 2)); // 代价函数：xy方向偏差代价
        fg[0] += m_vehicle_param_.w_curvature * pow(cur_k, 2);                                   // 代价函数：曲率代价
        ad next_k = vars[k_idx_begin + i + 1];
        fg[0] += m_vehicle_param_.w_curvature_change * pow(cur_k - next_k, 2); // 代价函数：曲率变化代价

        // cons
        fg[cons_x_idx_begin + i]              = next_x - cur_x - ds * cos(cur_theta);     // 约束xy方向运动学约束
        fg[cons_y_idx_begin + i]              = next_y - cur_y - ds * sin(cur_theta);     // 约束y方向运动学约束
        fg[cons_theta_idx_begin + i]          = sin(next_theta - cur_theta - ds * cur_k); // 角度变化约束,采用sin函数约束,防止角度在0～360度之间跳变
        next_k                                = vars[k_idx_begin + i + 1];
        fg[cons_curvature_rate_idx_begin + i] = pow((cur_k - next_k) / ds, 2); // 曲率变化约束，要求相邻路径点之前的曲率变化不能太大，否则会导致路径不平滑
    }
}

TensionSmoother2::TensionSmoother2(const std::vector<Point>& input_points, _VehicleParam m_vehicle_param) : input_points_(input_points), m_vehicle_param_(m_vehicle_param) {}

bool TensionSmoother2::smooth(std::vector<Point>& result) {
    std::vector<double> x_list, y_list, s_list, angle_list, k_list;
    // 先行打印input_points_
    std::cout << "待优化路径信息: " << input_points_.size() << std::endl;
    for (int i = 0; i < input_points_.size(); i++) {
        std::cout << input_points_.at(i).x << " " << input_points_.at(i).y << " " << input_points_.at(i).distance << " " << input_points_.at(i).angle << " " << input_points_.at(i).curvature << std::endl;
    }
    for (int i = 0; i < input_points_.size(); i++) {
        x_list.push_back(input_points_.at(i).x);
        y_list.push_back(input_points_.at(i).y);
        s_list.push_back(input_points_.at(i).distance);
        angle_list.push_back(input_points_.at(i).angle);
        k_list.push_back(input_points_.at(i).curvature);
    }
    std::vector<double> result_x_list, result_y_list, result_s_list, result_curvature_list, result_angle_list;
    bool                solver_ok{false};
    solver_ok = ipoptSmooth(x_list, y_list, angle_list, k_list, s_list, &result_x_list, &result_y_list, &result_s_list, &result_curvature_list, &result_angle_list);
    // 计算优化耗时
    // auto start_time = std::chrono::high_resolution_clock::now();
    // solver_ok       = osqpSmooth(x_list, y_list, angle_list, k_list, s_list, &result_x_list, &result_y_list, &result_s_list, &result_curvature_list, &result_angle_list);
    // auto end_time   = std::chrono::high_resolution_clock::now();
    // auto duration   = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    // std::cout << "优化耗时: " << duration.count() << "ms" << std::endl;
    if (!solver_ok) {
        std::cout << "Tension smoother failed!" << std::endl;
        return false;
    }

    result.resize(result_x_list.size());
    for (int i = 0; i < result_x_list.size(); i++) {
        result.at(i).x         = result_x_list.at(i);
        result.at(i).y         = result_y_list.at(i);
        result.at(i).distance  = result_s_list.at(i);
        result.at(i).curvature = result_curvature_list.at(i);
        result.at(i).angle     = result_angle_list.at(i);
    }

    return true;
}

bool TensionSmoother2::ipoptSmooth(const std::vector<double>& x_list, const std::vector<double>& y_list, const std::vector<double>& angle_list, const std::vector<double>& k_list, const std::vector<double>& s_list, std::vector<double>* result_x_list, std::vector<double>* result_y_list, std::vector<double>* result_s_list, std::vector<double>* result_curvature_list, std::vector<double>* result_angle_list) {
    typedef CPPAD_TESTVECTOR(double) Dvector;
    int    point_num = x_list.size();
    size_t n_vars    = 4 * point_num;

    size_t  x_idx_begin     = 0;
    size_t  y_idx_begin     = x_idx_begin + point_num;
    size_t  theta_idx_begin = y_idx_begin + point_num;
    size_t  k_idx_begin     = theta_idx_begin + point_num;
    Dvector vars(n_vars);
    for (size_t i = 0; i < point_num; i++) {
        vars[x_idx_begin + i]     = x_list[i];
        vars[y_idx_begin + i]     = y_list[i];
        vars[theta_idx_begin + i] = angle_list[i];
        vars[k_idx_begin + i]     = k_list[i];
    }

    std::cout << "打印 vars[] 初值信息" << std::endl;
    for (int i = 0; i < vars.size(); i++) {
        if ((i % point_num) == 0 && i != 0) {
            cout << endl;
            cout << endl;
        }
        std::cout << vars[i] << " ";
    }
    std::cout << std::endl;

    // bounds of variables
    Dvector vars_lowerbound(n_vars);
    Dvector vars_upperbound(n_vars);
    double  max_offset = m_vehicle_param_.ipopt_max_offset;
    threadLogger_->info("ipopt max_offset: {}", max_offset);
    double curvature_threshold;
    // 根据车辆类型和方向设置曲率阈值
    if (input_points_.front().direction == MotionDirection::Forward) {
        if (m_vehicle_param_.is_light) {
            curvature_threshold = tan(m_vehicle_param_.light_forward_max_steering) / m_vehicle_param_.wheel_base;
            threadLogger_->info("ipopt 前向轻车  curvature_threshold: {}", curvature_threshold);
        }
        else {
            curvature_threshold = tan(m_vehicle_param_.heavy_forward_max_steering) / m_vehicle_param_.wheel_base;
            threadLogger_->info("ipopt 前向重车  curvature_threshold: {}", curvature_threshold);
        }
    }
    else {
        if (m_vehicle_param_.is_light) {
            curvature_threshold = tan(m_vehicle_param_.light_backward_max_steering) / m_vehicle_param_.wheel_base;
            threadLogger_->info("ipopt 后向轻车  curvature_threshold: {}", curvature_threshold);
        }
        else {
            curvature_threshold = tan(m_vehicle_param_.heavy_backward_max_steering) / m_vehicle_param_.wheel_base;
            threadLogger_->info("ipopt 后向重车  curvature_threshold: {}", curvature_threshold);
        }
    }
    for (size_t i = 0; i < point_num; i++) {
        // 起点和终点x y 不优化
        if (i == 0 || i == point_num - 1) {
            vars_lowerbound[x_idx_begin + i] = vars_upperbound[x_idx_begin + i] = x_list[i];
            vars_lowerbound[y_idx_begin + i] = vars_upperbound[y_idx_begin + i] = y_list[i];
        }
        else {
            vars_lowerbound[x_idx_begin + i] = x_list[i] - max_offset;
            vars_upperbound[x_idx_begin + i] = x_list[i] + max_offset;
            vars_lowerbound[y_idx_begin + i] = y_list[i] - max_offset;
            vars_upperbound[y_idx_begin + i] = y_list[i] + max_offset;
        }
        vars_lowerbound[theta_idx_begin + i] = -DBL_MAX; // 角度变化范围不限制
        vars_upperbound[theta_idx_begin + i] = DBL_MAX;  // 角度变化范围不限制

        // 约束曲率变化范围
        vars_lowerbound[k_idx_begin + i] = -curvature_threshold;
        vars_upperbound[k_idx_begin + i] = curvature_threshold;
    }
    // 额外对前a个点的曲率进行约束
    int a = 0;
    for (size_t i = 0; i < a; i++) {
        vars_lowerbound[k_idx_begin + i] = 0;
        vars_upperbound[k_idx_begin + i] = 0;
    }
    // 约束角度
    for (size_t i = 0; i < point_num; i++) {
        // 起点和终点角度不优化
        if (i == 0 || i == point_num - 1) {
            vars_lowerbound[theta_idx_begin + i] = vars_upperbound[theta_idx_begin + i] = angle_list[i];
        }
    }

    std::cout << "打印 vars_lowerbound[] 信息" << std::endl;
    for (int i = 0; i < vars_lowerbound.size(); i++) {
        std::cout << vars_lowerbound[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "打印 vars_upperbound[] 信息" << std::endl;
    for (int i = 0; i < vars_upperbound.size(); i++) {
        std::cout << vars_upperbound[i] << " ";
    }
    std::cout << std::endl;

    // Constraints.
    size_t  n_constraints = (point_num - 1) * 4;
    Dvector constraints_lowerbound(n_constraints);
    Dvector constraints_upperbound(n_constraints);
    // for(int i=0;i<n_constraints;i++){
    //   constraints_lowerbound[i]=constraints_upperbound[i]=0;
    // }
    double Eps = 0;
    // x、y、theta方向运动学约束
    for (int i = 0; i < (point_num - 1); i++) {
        constraints_lowerbound[i]                       = -Eps;
        constraints_upperbound[i]                       = Eps;
        constraints_lowerbound[i + (point_num - 1)]     = -Eps;
        constraints_upperbound[i + (point_num - 1)]     = Eps;
        constraints_lowerbound[i + (point_num - 1) * 2] = -Eps;
        constraints_upperbound[i + (point_num - 1) * 2] = Eps;
    }
    // 曲率约束
    for (int i = (point_num - 1) * 3; i < n_constraints; ++i) {
        constraints_lowerbound[i] = -1;
        constraints_upperbound[i] = 0.00041;
    }

    std::cout << "打印 constraints_lowerbound[] 信息" << std::endl;
    for (int i = 0; i < constraints_lowerbound.size(); i++) {
        std::cout << constraints_lowerbound[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "打印 constraints_upperbound[] 信息" << std::endl;
    for (int i = 0; i < constraints_upperbound.size(); i++) {
        std::cout << constraints_upperbound[i] << " ";
    }
    std::cout << std::endl;
    // options for IPOPT solver
    std::string options;
    options += "Integer print_level  0\n";
    options += "Sparse  true        forward\n";
    options += "Sparse  true        reverse\n";
    options += "Numeric max_cpu_time          1\n";

    // place to return solution
    CppAD::ipopt::solve_result<Dvector> solution;
    // weights of the cost function

    FgEvalQPSmoothing fg_eval_reference_smoothing(x_list, y_list, s_list, angle_list, k_list, m_vehicle_param_);

    // solve the problem
    CppAD::ipopt::solve<Dvector, FgEvalQPSmoothing>(options, vars, vars_lowerbound, vars_upperbound, constraints_lowerbound, constraints_upperbound, fg_eval_reference_smoothing, solution);

    // Check if it works
    bool ok = solution.status == CppAD::ipopt::solve_result<Dvector>::success;
    std::cout << "solution.status: " << solution.status << std::endl;
    if (!ok) {
        // LOG(ERROR) << "Tension smoothing 2 ipopt solver failed!";
        return false;
    }

    // 输出所有优化后的变量
    std::cout << "\n优化后的变量结果：" << std::endl;
    std::cout << "索引\tx\ty\ttheta\tk" << std::endl;
    for (size_t i = 0; i != point_num; ++i) {
        std::cout << i << "\t" << solution.x[x_idx_begin + i] << "\t" << solution.x[y_idx_begin + i] << "\t" << solution.x[theta_idx_begin + i] << "\t";
        std::cout << solution.x[k_idx_begin + i];

        std::cout << std::endl;
    }

    // output
    result_s_list->clear();
    result_x_list->clear();
    result_y_list->clear();
    result_curvature_list->clear();
    result_angle_list->clear();
    double tmp_s = 0;
    for (size_t i = 0; i < point_num; ++i) {
        result_x_list->emplace_back(solution.x[x_idx_begin + i]);
        result_y_list->emplace_back(solution.x[y_idx_begin + i]);
        if (i != 0) tmp_s += sqrt(pow(result_x_list->at(i) - result_x_list->at(i - 1), 2) + pow(result_y_list->at(i) - result_y_list->at(i - 1), 2));
        result_s_list->emplace_back(tmp_s);
        result_angle_list->emplace_back(solution.x[theta_idx_begin + i]);

        result_curvature_list->emplace_back(solution.x[k_idx_begin + i]);
    }
    // LOG(INFO) << "Tension smoothing 2 ipopt solver succeeded!";
    return true;
}

bool TensionSmoother2::osqpSmooth(const std::vector<double>& x_list, const std::vector<double>& y_list, const std::vector<double>& angle_list, const std::vector<double>& k_list, const std::vector<double>& s_list, std::vector<double>* result_x_list, std::vector<double>* result_y_list, std::vector<double>* result_s_list, std::vector<double>* result_curvature_list, std::vector<double>* result_angle_list) {
    auto              point_num = x_list.size();
    OsqpEigen::Solver solver;
    solver.settings()->setVerbosity(true);
    solver.settings()->setWarmStart(true);
    solver.data()->setNumberOfVariables(4 * point_num);
    // 设置收敛容差参数
    // 修改OSQP参数设置
    solver.settings()->setAbsoluteTolerance(1e-8); // 先放宽容差
    solver.settings()->setRelativeTolerance(1e-8);
    solver.settings()->setMaxIteration(5000); // 增加最大迭代次数
    solver.settings()->setAdaptiveRho(true);  // 启用自适应rho
    solver.settings()->setRho(0.1);           // 调整rho值
    solver.settings()->setAlpha(1.4);         // 减小alpha值(1.4-1.8之间)


    solver.data()->setNumberOfConstraints(4 * (point_num - 1) + 4 * point_num);
    // Allocate QP problem matrices and vectors.
    Eigen::SparseMatrix<double> hessian;
    Eigen::VectorXd             gradient;
    Eigen::SparseMatrix<double> linearMatrix;
    Eigen::VectorXd             lowerBound;
    Eigen::VectorXd             upperBound;
    setHessianMatrix(point_num, &hessian);
    setGradient(x_list, y_list, &gradient);
    setConstraintMatrix(x_list, y_list, angle_list, k_list, s_list, &linearMatrix, &lowerBound, &upperBound);


    // Input to solver.
    if (!solver.data()->setHessianMatrix(hessian)) return false;
    if (!solver.data()->setGradient(gradient)) return false;
    if (!solver.data()->setLinearConstraintsMatrix(linearMatrix)) return false;
    if (!solver.data()->setLowerBound(lowerBound)) return false;
    if (!solver.data()->setUpperBound(upperBound)) return false;

    // Solve.
    if (!solver.initSolver()) return false;
    // 设置初始解
    Eigen::VectorXd initialSolution(4 * point_num);
    for (int i = 0; i < point_num; ++i) {
        initialSolution(i)                 = x_list[i];
        initialSolution(point_num + i)     = y_list[i];
        initialSolution(2 * point_num + i) = angle_list[i];
        initialSolution(3 * point_num + i) = k_list[i];
    }
    // 旧版本OsqpEigen设置初始解的方法
    if (!solver.setPrimalVariable(initialSolution)) {
        std::cerr << "设置初始解失败" << std::endl;
        return false;
    }
    else {
        std::cout << "设置初始解成功" << std::endl;
    }
    if (!solver.solve()) return false;

    // // 获取并缩放解
    // Eigen::VectorXd scaled_solution = solver.getSolution();
    // Eigen::VectorXd solution = scaled_solution / scaling_factor;

    // 检查求解状态
    auto status = solver.getStatus();
    // bool is_converged = (status == OsqpEigen::Status::OSQP_SOLVED ||
    //                      status == OsqpEigen::Status::OSQP_SOLVED_INACCURATE);

    std::cout << "优化成功收敛!" << static_cast<int>(status) << std::endl;
    // 计算约束违反程度
    // Eigen::VectorXd constraints_violation = linearMatrix * solution;
    // double max_violation = constraints_violation.cwiseAbs().maxCoeff();
    // std::cout << "Max constraint violation: " << max_violation << std::endl;
    // 获取目标函数值
    double objective_value = solver.getObjValue();
    std::cout << "最终目标函数值: " << objective_value << std::endl;
    const auto& QPSolution{solver.getSolution()};
    // Output.
    result_s_list->clear();
    result_x_list->clear();
    result_y_list->clear();
    double tmp_s = 0;
    for (size_t i = 0; i != point_num; ++i) {
        double tmp_x = QPSolution(i);
        double tmp_y = QPSolution(point_num + i);
        result_x_list->emplace_back(tmp_x);
        result_y_list->emplace_back(tmp_y);
        if (i != 0) tmp_s += sqrt(pow(result_x_list->at(i) - result_x_list->at(i - 1), 2) + pow(result_y_list->at(i) - result_y_list->at(i - 1), 2));
        result_s_list->emplace_back(tmp_s);
        result_angle_list->emplace_back(QPSolution(2 * point_num + i));
        result_curvature_list->emplace_back(QPSolution(3 * point_num + i));
        // 打印 temp_x temp_y temp_s temp_angle temp_curvature
        std::ofstream outfile("/home/yyf/test_ipopt/tension_smoother_2.txt", std::ios::app);
        if (i != point_num - 1) {
            std::cout << tmp_x << " " << tmp_y << " " << tmp_s << " " << QPSolution(2 * point_num + i) << " " << QPSolution(3 * point_num + i) << std::endl;
            // 将上述数据保存为文件
            outfile << tmp_x << " " << tmp_y << " " << tmp_s << " " << QPSolution(2 * point_num + i) << " " << QPSolution(3 * point_num + i) << std::endl;
        }
        outfile.close();
    }
    return true;
}

void TensionSmoother2::setHessianMatrix(size_t size, Eigen::SparseMatrix<double>* matrix_h) const {
    const size_t    x_start_index     = 0;
    const size_t    y_start_index     = x_start_index + size;
    const size_t    theta_start_index = y_start_index + size;
    const size_t    k_start_index     = theta_start_index + size;
    const size_t    matrix_size       = 4 * size;
    Eigen::MatrixXd hessian           = Eigen::MatrixXd::Constant(matrix_size, matrix_size, 0);
    // Deviation and curvature.
    for (int i = 0; i < size; ++i) {
        hessian(x_start_index + i, x_start_index + i) = hessian(y_start_index + i, y_start_index + i) = m_vehicle_param_.w_deviation * 2; // 代价函数第一项（x,y）与原始路径的偏差,乘以2是为了符合qp问题标准形式 1/2*XTQX+bTX
        hessian(k_start_index + i, k_start_index + i)                                                 = m_vehicle_param_.w_curvature * 2; // 代价函数第二项（k）要尽量小,乘以2是为了符合qp问题标准形式 1/2*XTQX+bTX
    }
    // Curvature change.
    Eigen::Vector2d coeff_vec{1, -1};
    Eigen::Matrix2d coeff = coeff_vec * coeff_vec.transpose();
    for (int i = 0; i < size - 1; ++i) {
        hessian.block(k_start_index + i, k_start_index + i, 2, 2) += 2 * m_vehicle_param_.w_curvature_change * coeff; // 代价函数第三项（k的变化率）要尽量小,乘以2是为了符合qp问题标准形式 1/2*XTQX+bTX
    }
    // 打印hessian,按照格式打印,每个数占6位,保留2位小数
    std::cout << "打印hessian   " << hessian.rows() << " " << hessian.cols() << std::endl;
    // for (int i = 0; i != hessian.rows(); ++i) {
    //     for (int j = 0; j != hessian.cols(); ++j) {
    //         std::cout << std::fixed << std::setprecision(2) << hessian(i, j) << " ";
    //     }
    //     std::cout << std::endl;
    // }
    *matrix_h = hessian.sparseView();
}

void TensionSmoother2::setConstraintMatrix(const std::vector<double>& x_list, const std::vector<double>& y_list, const std::vector<double>& angle_list, const std::vector<double>& k_list, const std::vector<double>& s_list, Eigen::SparseMatrix<double>* matrix_constraints, Eigen::VectorXd* lower_bound, Eigen::VectorXd* upper_bound) const {
    // 打印x_list,y_list,angle_list,k_list,s_list
    int point_num = x_list.size();
    std::cout << "打印x_list  " << x_list.size() << std::endl;
    for (int i = 0; i != x_list.size(); ++i) {
        if (i % point_num == 0 && i != 0) {
            cout << endl;
        }
        std::cout << x_list[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "打印y_list  " << y_list.size() << std::endl;
    for (int i = 0; i != y_list.size(); ++i) {
        std::cout << y_list[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "打印angle_list  " << angle_list.size() << std::endl;
    for (int i = 0; i != angle_list.size(); ++i) {
        std::cout << angle_list[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "打印k_list  " << k_list.size() << std::endl;
    for (int i = 0; i != k_list.size(); ++i) {
        std::cout << k_list[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "打印s_list  " << s_list.size() << std::endl;
    for (int i = 0; i != s_list.size(); ++i) {
        std::cout << s_list[i] << " ";
    }
    std::cout << std::endl;
    const size_t size              = x_list.size();
    const size_t x_start_index     = 0;                        // x变量纵向索引
    const size_t y_start_index     = x_start_index + size;     // y变量纵向索引
    const size_t theta_start_index = y_start_index + size;     // theta变量纵向索引
    const size_t k_start_index     = theta_start_index + size; // k变量纵向索引

    const size_t cons_x_update_start_index         = 0;                                        // x方向运动学约束横向索引
    const size_t cons_y_update_start_index         = cons_x_update_start_index + size - 1;     // y方向运动学约束横向索引
    const size_t cons_theta_update_start_index     = cons_y_update_start_index + size - 1;     // 角度运动学约束横向索引
    const size_t cons_curvature_update_start_index = cons_theta_update_start_index + size - 1; // 曲率变化率约束横向索引

    const size_t cons_x_bound_start_index         = cons_curvature_update_start_index + size - 1; // x方向上下界约束横向索引
    const size_t cons_y_bound_start_index         = cons_x_bound_start_index + size;              // y方向上下界约束横向索引
    const size_t cons_theta_bound_start_index     = cons_y_bound_start_index + size;              // theta方向上下界约束横向索引
    const size_t cons_curvature_bound_start_index = cons_theta_bound_start_index + size;          // k方向上下界约束横向索引

    std::cout << "打印cons_x_update_start_index  " << cons_x_update_start_index << std::endl;
    std::cout << "打印cons_y_update_start_index  " << cons_y_update_start_index << std::endl;
    std::cout << "打印cons_theta_update_start_index  " << cons_theta_update_start_index << std::endl;
    std::cout << "打印cons_curvature_update_start_index  " << cons_curvature_update_start_index << std::endl;
    std::cout << "打印cons_x_bound_start_index  " << cons_x_bound_start_index << std::endl;
    std::cout << "打印cons_y_bound_start_index  " << cons_y_bound_start_index << std::endl;
    std::cout << "打印cons_theta_bound_start_index  " << cons_theta_bound_start_index << std::endl;
    std::cout << "打印cons_curvature_bound_start_index  " << cons_curvature_bound_start_index << std::endl;


    const size_t n_constraints = 4 * (size - 1) + 4 * size; // 运动学约束 + 优化变量的边界约束
    const size_t n_vars        = 4 * size;                  // x, y, theta, k 变量

    Eigen::MatrixXd cons = Eigen::MatrixXd::Zero(n_constraints, n_vars);
    *lower_bound         = Eigen::MatrixXd::Zero(n_constraints, 1);
    *upper_bound         = Eigen::MatrixXd::Zero(n_constraints, 1);

    // Cons.
    for (int i = 0; i < size - 1; ++i) {
        const double ds = s_list[i + 1] - s_list[i];
        // 配置x方向运动学约束,泰勒展开式到一阶
        cons(cons_x_update_start_index + i, x_start_index + i)     = -1;
        cons(cons_x_update_start_index + i, x_start_index + i + 1) = 1;
        cons(cons_x_update_start_index + i, theta_start_index + i) = ds * sin(angle_list[i]);

        // 配置y方向运动学约束,泰勒展开式到一阶
        cons(cons_y_update_start_index + i, y_start_index + i)     = -1;
        cons(cons_y_update_start_index + i, y_start_index + i + 1) = 1;
        cons(cons_y_update_start_index + i, theta_start_index + i) = -ds * cos(angle_list[i]);

        // 配置theta方向运动学约束,泰勒展开式到一阶
        cons(cons_theta_update_start_index + i, theta_start_index + i)     = -cos(angle_list[i + 1] - angle_list[i] - ds * k_list[i]);
        cons(cons_theta_update_start_index + i, theta_start_index + i + 1) = cos(angle_list[i + 1] - angle_list[i] - ds * k_list[i]);
        cons(cons_theta_update_start_index + i, k_start_index + i)         = -ds * cos(angle_list[i + 1] - angle_list[i] - ds * k_list[i]);

        // 配置相邻路径点曲率变化率约束,泰勒展开式到一阶
        cons(cons_curvature_update_start_index + i, k_start_index + i)     = -2 * (k_list[i + 1] - k_list[i]);
        cons(cons_curvature_update_start_index + i, k_start_index + i + 1) = 2 * (k_list[i + 1] - k_list[i]);
    }

    // 配置xy的上下界约束
    for (int i = 0; i < size; ++i) {
        cons(cons_x_bound_start_index + i, x_start_index + i)         = 1;
        cons(cons_y_bound_start_index + i, y_start_index + i)         = 1;
        cons(cons_theta_bound_start_index + i, theta_start_index + i) = 1;
        cons(cons_curvature_bound_start_index + i, k_start_index + i) = 1;
    }
    // 打印cons,按照格式打印,每个数占6位,保留2位小数
    std::cout << "打印cons  " << cons.rows() << " " << cons.cols() << std::endl;
    // for (int i = 0; i != cons.rows(); ++i) {
    //     for (int j = 0; j != cons.cols(); ++j) {
    //         std::cout << std::fixed << std::setprecision(4) << cons(i, j) << " ";
    //     }
    //     std::cout << std::endl;
    // }
    *matrix_constraints = cons.sparseView();
    // Bounds.
    double Eps = 0.0;
    for (int i = 0; i < size - 1; ++i) {
        const double ds                               = s_list[i + 1] - s_list[i];
        (*lower_bound)(cons_x_update_start_index + i) = (*upper_bound)(cons_x_update_start_index + i) = -1 * x_list[i] + x_list[i + 1] + ds * sin(angle_list[i]) * angle_list[i] - (x_list[i + 1] - x_list[i] - ds * cos(angle_list[i]));
        (*lower_bound)(cons_y_update_start_index + i) = (*upper_bound)(cons_y_update_start_index + i) = -1 * y_list[i] + y_list[i + 1] - ds * cos(angle_list[i]) * angle_list[i] - (y_list[i + 1] - y_list[i] - ds * sin(angle_list[i]));
        (*lower_bound)(cons_theta_update_start_index + i) = (*upper_bound)(cons_theta_update_start_index + i) = -cos(angle_list[i + 1] - angle_list[i] - ds * k_list[i]) * angle_list[i] + cos(angle_list[i + 1] - angle_list[i] - ds * k_list[i]) * angle_list[i + 1] - ds * cos(angle_list[i + 1] - angle_list[i] - ds * k_list[i]) * k_list[i] - sin(angle_list[i + 1] - angle_list[i] - ds * k_list[i]);
        (*lower_bound)(cons_curvature_update_start_index + i)                                                 = 0;
        (*upper_bound)(cons_curvature_update_start_index + i)                                                 = pow(0.02 * ds, 2);
    }

    const double bound_offset = 10; // 10m的浮动范围
    for (int i = 0; i < size; ++i) {
        if (i == 0 || i == size - 1) {
            // 前两个点和后两个点固定
            (*lower_bound)(cons_x_bound_start_index + i) = (*upper_bound)(cons_x_bound_start_index + i) = x_list[i];
            (*lower_bound)(cons_y_bound_start_index + i) = (*upper_bound)(cons_y_bound_start_index + i) = y_list[i];
        }
        else {
            // 其他点允许±10cm的浮动
            (*lower_bound)(cons_x_bound_start_index + i) = x_list[i] - bound_offset;
            (*upper_bound)(cons_x_bound_start_index + i) = x_list[i] + bound_offset;
            (*lower_bound)(cons_y_bound_start_index + i) = y_list[i] - bound_offset;
            (*upper_bound)(cons_y_bound_start_index + i) = y_list[i] + bound_offset;
        }

        (*lower_bound)(cons_theta_bound_start_index + i)     = -3.14 * 2;
        (*upper_bound)(cons_theta_bound_start_index + i)     = 3.14 * 2;
        (*lower_bound)(cons_curvature_bound_start_index + 1) = -0.1;
        (*upper_bound)(cons_curvature_bound_start_index + 1) = 0.1;
    }


    // 打印lower_bound,按照格式打印,每个数占6位,保留4位小数
    std::cout << "打印lower_bound  " << lower_bound->size() << std::endl;
    for (int i = 0; i != lower_bound->size(); ++i) {
        std::cout << std::fixed << std::setprecision(4) << (*lower_bound)(i) << " ";
    }
    std::cout << std::endl;
    // 打印upper_bound,按照格式打印,每个数占6位,保留2位小数
    std::cout << "打印upper_bound  " << upper_bound->size() << std::endl;
    for (int i = 0; i != upper_bound->size(); ++i) {
        std::cout << std::fixed << std::setprecision(4) << (*upper_bound)(i) << " ";
    }
    std::cout << std::endl;
}

void TensionSmoother2::setGradient(const std::vector<double>& x_list, const std::vector<double>& y_list, Eigen::VectorXd* gradient) {
    const auto   size          = x_list.size();
    const size_t x_start_index = 0;
    const size_t y_start_index = x_start_index + size;
    *gradient                  = Eigen::VectorXd::Constant(4 * size, 0);
    for (int i = 0; i != size; ++i) {
        (*gradient)(x_start_index + i) = -2 * m_vehicle_param_.w_deviation * x_list[i];
        (*gradient)(y_start_index + i) = -2 * m_vehicle_param_.w_deviation * y_list[i];
    }
    // 打印gradient,按照格式打印,每个数占6位,保留2位小数
    std::cout << "打印gradient  " << gradient->size() << std::endl;
    for (int i = 0; i != gradient->size(); ++i) {
        std::cout << std::fixed << std::setprecision(3) << (*gradient)(i) << " ";
    }
    std::cout << std::endl;
}
} // namespace GlobalPlanning