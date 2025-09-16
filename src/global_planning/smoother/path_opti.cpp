/***************************************************/
/*            Author: cxp                          */
/*            Contact: chenxinpeng_hnu@163.com     */
/*            Last update: 2020-04-15              */
/***************************************************/

// #include "../include/glog/logging.h"
#include "path_opti.h"

#include <thread>


using namespace GlobalPlanning;

/**
 *@brief: 路径优化接口函数实现
 *@param
 *return
 */
void Path_Opti::OptimizePath(Path& original_path, Path& opti_path, CollisonCheck& collison_check, _VehicleParam m_vehicle_param) {
    // 清空相关容器
    path_.clear();
    new_path_.clear();
    cusp_set_.clear();
    fixpoint_set_.clear();
    m_vehicle_param_ = m_vehicle_param;
    path_            = original_path;


    std::ofstream file_out;
    // file_out.open("cusp_path_before.txt");
    // for (size_t index = 0; index < path_.size(); index++) {
    //     file_out << setprecision(4) << path_.at(index).x << " " << path_.at(index).y << " " << path_.at(index).angle / M_PI * 180 << " " << path_.at(index).direction << " " << path_.at(index).curvature << endl;
    // }
    // file_out.close();

    CuspPointExtension(collison_check); // 尖点延伸

    // file_out.open("cusp_path_after.txt");
    // for (size_t index = 0; index < path_.size(); index++) {
    //     file_out << setprecision(4) << path_.at(index).x << " " << path_.at(index).y << " " << path_.at(index).angle / M_PI * 180 << " " << path_.at(index).direction << " " << path_.at(index).curvature << endl;
    // }
    // file_out.close();


    // file_out.open("path_smooth_before.txt");
    // for (size_t index = 0; index < path_.size(); index++) {
    //     file_out << setprecision(4) << path_.at(index).x << " " << path_.at(index).y << " " << path_.at(index).angle / M_PI * 180 << " " << path_.at(index).direction << " " << path_.at(index).curvature << endl;
    // }
    // file_out.close();
    // 采用优化方案失败，则继续采用传统平滑方案
    // 得到节点和固定点索引
    GetCuspIndex();     // 得到尖点索引查询表cuspLookup
    GetFixPointIndex(); // 得到固定点索引查询表fixpLookup

    unsigned int opti_num     = 0;
    unsigned int max_opti_num = 10;

    // 统计时间
    auto start_time = std::chrono::high_resolution_clock::now();

    while (opti_num++ < path_.size() + 1) {
        // threadLogger_->info("第 {} 次优化,fixpoint_set_.size():{}", opti_num, fixpoint_set_.size());
        SmoothPath();
        CalculatePathAngle();
        CurvatureCal(new_path_);

        auto collision_point  = collison_check.OptiPathCollisionCheck(new_path_); // 判断优化路径是否碰撞
        auto curvature_exceed = CurvatureCheck(new_path_);
        // threadLogger_->info("curvature_exceed.size():{}", curvature_exceed.size());
        if (true == collision_point.empty() && curvature_exceed.empty() == true) // 若无碰撞且曲率不超标
        {
            break;
        }
        else // 否则固定碰撞点和曲率超标点，继续优化
        {
            UpdateFixPointSet(collision_point);
            UpdateFixPointSet(curvature_exceed);
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    threadLogger_->info("梯度下降优化耗时: {}ms", duration.count());

    Helper::CalDistance(new_path_);


    // file_out.open("path_smooth_after_tidu.txt");
    // for (size_t index = 0; index < new_path_.size(); index++) {
    //     file_out << setprecision(4) << new_path_.at(index).x << " " << new_path_.at(index).y << " " << new_path_.at(index).angle / M_PI * 180 << " " << new_path_.at(index).direction << " " << new_path_.at(index).curvature << endl;
    // }
    // file_out.close();


    // InterpolationPath(new_path_);
    // CurvatureCal(new_path_);
    // file_out.open("interpolation_path.txt");
    // for (size_t index = 0; index < new_path_.size(); index++) {
    //     file_out << setprecision(4) << new_path_.at(index).x << " " << new_path_.at(index).y << " " << new_path_.at(index).angle / M_PI * 180 << " " << new_path_.at(index).direction << " " << new_path_.at(index).curvature << endl;
    // }
    // file_out.close();


    if (!OsqpSmooth(new_path_, opti_path, collison_check)) {
        threadLogger_->info("osqp优化失败，继续采用传统平滑方案");
        opti_path = new_path_;
    }
    // file_out.open("path_smooth_after_ipopt_new_curvature.txt");
    // for (size_t index = 0; index < opti_path.size(); index++) {
    //     file_out << setprecision(4) << opti_path.at(index).x << " " << opti_path.at(index).y << " " << opti_path.at(index).angle / M_PI * 180 << " " << opti_path.at(index).direction << " " << opti_path.at(index).curvature << endl;
    // }
    // file_out.close();
}

void Path_Opti::SmoothPath() {
    int           L     = path_.size();
    float         x_sat = 6;
    vector<float> coeff;
    for (int i = 0; i < L; i++) {
        float x    = (i < L / 2) ? i : (L - 1.0 - i);
        float temp = 1 / (1 + exp(-x + x_sat));
        coeff.push_back(temp);
    }

    uint     iterations = 0;
    Vector2D xim2, xim1, xi, xip1, xip2, xoi;
    Vector2D gradient_error_term;
    Vector2D gradient_curvature_term;
    Vector2D gradient_smoothness_term;
    new_path_ = path_;

    // 梯度下降法迭代优化
    while (iterations++ < m_vehicle_param_.max_iterations_opti) {
        for (uint i = 2; i < new_path_.size() - 2; i++) {
            if (IsCusp(i) || IsFixPoint(i)) {
                continue;
            }

            // 优化路径的当前点前两点、当前点、当前点后两点及原路径当前点
            xim2.x = new_path_.at(i - 2).x;
            xim2.y = new_path_.at(i - 2).y;
            xim1.x = new_path_.at(i - 1).x;
            xim1.y = new_path_.at(i - 1).y;
            xi.x   = new_path_.at(i).x;
            xi.y   = new_path_.at(i).y;
            xip1.x = new_path_.at(i + 1).x;
            xip1.y = new_path_.at(i + 1).y;
            xip2.x = new_path_.at(i + 2).x;
            xip2.y = new_path_.at(i + 2).y;
            xoi.x  = path_.at(i).x;
            xoi.y  = path_.at(i).y;

            // 与原路径偏差项
            gradient_error_term = ErrorTerm(xi, xoi);
            new_path_.at(i).x -= coeff[i] * gradient_error_term.x;
            new_path_.at(i).y -= coeff[i] * gradient_error_term.y;

            // 曲率项
            gradient_curvature_term = CurvatureTerm(xim1, xi, xip1);
            new_path_.at(i).x -= coeff[i] * gradient_curvature_term.x;
            new_path_.at(i).y -= coeff[i] * gradient_curvature_term.y;

            // 平滑项
            gradient_smoothness_term = SmoothnessTerm(xim2, xim1, xi, xip1, xip2);
            new_path_.at(i).x -= coeff[i] * gradient_smoothness_term.x;
            new_path_.at(i).y -= coeff[i] * gradient_smoothness_term.y;
        }
    }
}


// void Path_Opti::SmoothPath() {
//     int            L     = path_.size();
//     double         x_sat = 6;
//     vector<double> coeff;
//     for (int i = 0; i < L; i++) {
//         double x    = (i < L / 2) ? i : (L - 1.0 - i);
//         double temp = 1 / (1 + exp(-x + x_sat));
//         coeff.push_back(temp);
//     }

//     unsigned int iterations = 0;
//     Vector2D     xim2, xim1, xi, xip1, xip2, xoi;
//     Vector2D     gradient_error_term;
//     Vector2D     gradient_curvature_term;
//     Vector2D     gradient_smoothness_term;
//     Vector2D     gradient_vonoroi_term;
//     new_path_ = path_;

//     // 梯度下降法迭代优化
//     while (iterations++ < m_vehicle_param_.max_iterations_opti) {
//         // cout << "梯度下降，第 " << iterations << " 轮" << endl;
//         for (unsigned int i = 2; i < new_path_.size() - 2; i++) {
//             if (IsCusp(i) || IsFixPoint(i)) {
//                 // cout << "点" << i << "属于anchor点，予以跳过" << endl;
//                 continue;
//             }
//             // 优化路径的当前点前两点、当前点、当前点后两点及原路径当前点
//             xim2.x = new_path_.at(i - 2).x;
//             xim2.y = new_path_.at(i - 2).y;
//             xim1.x = new_path_.at(i - 1).x;
//             xim1.y = new_path_.at(i - 1).y;
//             xi.x   = new_path_.at(i).x;
//             xi.y   = new_path_.at(i).y;
//             xip1.x = new_path_.at(i + 1).x;
//             xip1.y = new_path_.at(i + 1).y;
//             xip2.x = new_path_.at(i + 2).x;
//             xip2.y = new_path_.at(i + 2).y;
//             xoi.x  = path_.at(i).x;
//             xoi.y  = path_.at(i).y;


//             // 与原路径偏差项
//             gradient_error_term = ErrorTerm(xi, xoi);
//             if (!isinf(gradient_error_term.x)) new_path_.at(i).x -= coeff.at(i) * gradient_error_term.x;
//             if (!isinf(gradient_error_term.y)) new_path_.at(i).y -= coeff.at(i) * gradient_error_term.y;


//             // 曲率项
//             gradient_curvature_term = CurvatureTerm(xim1, xi, xip1);
//             // gradient_curvature_term = CurvatureTerm(xim2, xim1, xi, xip1, xip2);
//             if (!isinf(gradient_curvature_term.x)) new_path_.at(i).x -= coeff.at(i) * gradient_curvature_term.x;
//             if (!isinf(gradient_curvature_term.y)) new_path_.at(i).y -= coeff.at(i) * gradient_curvature_term.y;


//             // 平滑项
//             gradient_smoothness_term = SmoothnessTerm(xim2, xim1, xi, xip1, xip2);
//             if (!isinf(gradient_smoothness_term.x)) new_path_.at(i).x -= coeff.at(i) * gradient_smoothness_term.x;
//             if (!isinf(gradient_smoothness_term.y)) new_path_.at(i).y -= coeff.at(i) * gradient_smoothness_term.y;
//         }
//     }
// }


vector<unsigned int> Path_Opti::CurvatureCheck(const Path& input_path) {
    double curvature_threshold = 1.0;
    threadLogger_->info("轻载前进最大曲率:{}", tan(m_vehicle_param_.light_forward_max_steering) / m_vehicle_param_.wheel_base);
    threadLogger_->info("重载前进最大曲率:{}", tan(m_vehicle_param_.heavy_forward_max_steering) / m_vehicle_param_.wheel_base);
    threadLogger_->info("轻载后退最大曲率:{}", tan(m_vehicle_param_.light_backward_max_steering) / m_vehicle_param_.wheel_base);
    threadLogger_->info("重载后退最大曲率:{}", tan(m_vehicle_param_.heavy_backward_max_steering) / m_vehicle_param_.wheel_base);

    vector<unsigned int> curvature_exceed_point;
    curvature_exceed_point.clear();
    for (unsigned int i = 1; i < input_path.size() - 1; i++) {
        double curvature = input_path.at(i).curvature;
        if (input_path.at(i).direction == MotionDirection::Forward) {
            if (m_vehicle_param_.is_light) {
                curvature_threshold = tan(m_vehicle_param_.light_forward_max_steering) / m_vehicle_param_.wheel_base;
            }
            else {
                curvature_threshold = tan(m_vehicle_param_.heavy_forward_max_steering) / m_vehicle_param_.wheel_base;
            }
        }
        else {
            if (m_vehicle_param_.is_light) {
                curvature_threshold = tan(m_vehicle_param_.light_backward_max_steering) / m_vehicle_param_.wheel_base;
            }
            else {
                curvature_threshold = tan(m_vehicle_param_.heavy_backward_max_steering) / m_vehicle_param_.wheel_base;
            }
        }
        if (fabs(curvature) > curvature_threshold + 1e-2) {
            threadLogger_->info("第 {} 个点曲率超标，点坐标为({},{}),曲率为{},此点将被列为anchor点,> {}", i, input_path.at(i).x, input_path.at(i).y, input_path.at(i).curvature, curvature_threshold);
            curvature_exceed_point.push_back(i);
            curvature_exceed_point.push_back(i - 1);
            curvature_exceed_point.push_back(i + 1);
        }
    }
    return curvature_exceed_point;
}


/**
 *@brief: 获取尖点索引函数
 *@param  [out] cusp_set_ 返回尖点索引值查找表
 *return
 */
void Path_Opti::GetCuspIndex() {
    // 方向属性切换的点则为尖点
    for (unsigned int i = 1; i < path_.size(); ++i) {
        if (path_.at(i).direction != path_.at(i - 1).direction) {
            cusp_set_.insert(i - 1); // 之所以放i-1,是因为hybridA*规划的尖点属性是跟随前面的，这里需要严格把控rs曲线采样那里的逻辑
        }
    }
}

/**
 *@brief: 获取固定点索引函数
 *@param  [out] cusp_set_  返回固定点索引值查找表
 */
void Path_Opti::GetFixPointIndex() {
    // 固定尖点前后点

    for (auto it = cusp_set_.begin(); it != cusp_set_.end(); ++it) {
        fixpoint_set_.insert(*it - 1);
        fixpoint_set_.insert(*it);
        fixpoint_set_.insert(*it + 1);
    }
    fixpoint_set_.insert(0);
    fixpoint_set_.insert(path_.size() - 1);
    threadLogger_->info("打印锚点信息");
    for (auto i : fixpoint_set_) {
        threadLogger_->info("{}", i);
    }
}

/**
 *@brief: 更新固定点查找表函数
 *@param
 *return
 */
void Path_Opti::UpdateFixPointSet(const vector<unsigned int> points) {
    // 将所有碰撞点和曲率超标的点变为固定点
    for (unsigned int i = 0; i < points.size(); i++) {
        unsigned int index = points.at(i);
        fixpoint_set_.insert(index);
    }
}

/**
 *@brief: 路径优化核心函数
 *@param
 *return
 */
bool Path_Opti::SmoothSegmentPath(const Path& input_path, Path& output_path, CollisonCheck& collison_check) {
    TensionSmoother2 smoother(input_path, m_vehicle_param_);
    smoother.threadLogger_ = threadLogger_;
    cout << "开始优化" << endl;
    if (!smoother.smooth(output_path)) {
        threadLogger_->info("优化方案优化失败");
        cout << "优化方案优化失败" << endl;
        return false;
    }
    threadLogger_->info("优化方案优化成功");
    cout << "优化方案优化成功" << endl;

    // std::ofstream file_out;
    // file_out.open("path_smooth_after_ipopt.txt");
    // for (size_t index = 0; index < output_path.size(); index++) {
    //     file_out << setprecision(4) << output_path.at(index).x << " " << output_path.at(index).y << " " << output_path.at(index).angle / M_PI * 180 << " " << output_path.at(index).direction << " " << output_path.at(index).curvature << endl;
    // }
    // file_out.close();

    // 计算曲率
    CurvatureCal(output_path);
    // 如果input_path为后退路段，则将output_path反向
    if (input_path.at(0).direction == MotionDirection::Backward) {
        std::reverse(output_path.begin(), output_path.end());
    }
    // 循环结束后，计算角度并保存原始属性
    for (unsigned int i = 0; i < output_path.size() - 1; i++) {
        double dx    = (output_path.at(i + 1).x - output_path.at(i).x);
        double dy    = (output_path.at(i + 1).y - output_path.at(i).y);
        double angle = atan2(dy, dx);

        if (angle < 0) {
            angle += 2 * M_PI;
        }

        if (input_path.at(i).direction == MotionDirection::Backward) {
            output_path.at(i).angle = Helper::NormalizeAngleRad(angle + M_PI);
        }
        else {
            output_path.at(i).angle = Helper::NormalizeAngleRad(angle);
        }

        // 保存原始属性信息
        output_path.at(i).direction = input_path.at(i).direction;
    }
    // 处理最后一个点
    if (!output_path.empty()) {
        output_path.back().angle     = output_path[output_path.size() - 2].angle;
        output_path.back().direction = input_path.back().direction;
    }
    Helper::CalDistance(output_path);

    // 检查碰撞和曲率
    auto collision_points = collison_check.OptiPathCollisionCheck(output_path);
    threadLogger_->info("碰撞点数量: {}", collision_points.size());
    auto curvature_exceed = CurvatureCheck(output_path);
    threadLogger_->info("曲率超标点数量: {}", curvature_exceed.size());
    // 只要存在碰撞点或曲率超标点，均认定优化失败
    if (!collision_points.empty() || !curvature_exceed.empty()) {
        return false;
    }
    return true;
}

bool Path_Opti::OsqpSmooth(const Path& path_, Path& opti_path, CollisonCheck& collison_check) {
    // 清空输出路径
    opti_path.clear();
    // 对路径进行分段
    vector<Path>  segments;
    vector<Point> current_segment;
    for (size_t i = 0; i < path_.size(); ++i) {
        current_segment.push_back(path_[i]);
        if (i == path_.size() - 1 || (i < path_.size() - 1 && path_[i].direction != path_[i + 1].direction)) {
            if (!current_segment.empty()) {
                segments.push_back(current_segment);
                current_segment.clear();
            }
        }
    }
    threadLogger_->info("准备对hybridA*路径进行优化，一共分 {} 段", segments.size());
    cout << "准备对hybridA*路径进行优化，一共分 " << segments.size() << " 段" << endl;
    // 对每一段进行优化
    for (const auto& segment : segments) {
        Path segment_path(segment);
        Path opti_segment;
        // 使用OSQP/ipopt求解器优化当前段
        // 判断segment_path为前进还是后退路段，如果为后退，则将segment_path反向,否则会因为角度反向问题导致优化失败
        if (segment_path.at(0).direction == MotionDirection::Backward) {
            threadLogger_->info("倒车路段");
            cout << "倒车路段" << endl;
            std::reverse(segment_path.begin(), segment_path.end());
        }
        else {
            threadLogger_->info("前进路段");
            cout << "前进路段" << endl;
        }
        // 重新计算segment_path的累积s
        Helper::CalDistance(segment_path);
        threadLogger_->info("开始优化当前段");
        cout << "开始优化当前段" << endl;
        if (!SmoothSegmentPath(segment_path, opti_segment, collison_check)) {
            return false;
        }

        // 将优化后的段添加到最终路径中
        opti_path.insert(opti_path.end(), opti_segment.begin(), opti_segment.end());
    }
    return true;
}

/**
 * @brief 求解新路径与原路径偏差项梯度
 * @param[out] gradient  返回梯度
 */
inline Vector2D Path_Opti::ErrorTerm(Vector2D xi, Vector2D xoi) {
    Vector2D gradient;
    gradient.x = m_vehicle_param_.path_error_term * (xi.x - xoi.x);
    gradient.y = m_vehicle_param_.path_error_term * (xi.y - xoi.y);
    return gradient;
}

/**
 *@brief: 求解曲率项梯度
 *@param  [out] gradient 返回梯度
 *参考：
 * Dolgov D, Thrun S, Montemerlo M, et al. Practical search techniques in path planning for
 * autonomous driving[J]. Ann Arbor, 2008, 1001(48105): 18-80.
 */
inline Vector2D Path_Opti::CurvatureTerm(Vector2D xim1, Vector2D xi, Vector2D xip1) {
    Vector2D gradient;
    Vector2D delta_xi;   // Δxi
    Vector2D delta_xip1; // Δxi+1
    double   norm_delta_xi, norm_delta_xip1, d, dphi, kappa;
    delta_xi.x      = xi.x - xim1.x;
    delta_xi.y      = xi.y - xim1.y;
    delta_xip1.x    = xip1.x - xi.x;
    delta_xip1.y    = xip1.y - xi.y;
    norm_delta_xi   = sqrt(pow(delta_xi.x, 2) + pow(delta_xi.y, 2));     // |Δxi|
    norm_delta_xip1 = sqrt(pow(delta_xip1.x, 2) + pow(delta_xip1.y, 2)); // |Δxi+1|
    d               = norm_delta_xi * norm_delta_xip1;
    dphi            = acos((delta_xi.x * delta_xip1.x + delta_xi.y * delta_xip1.y) / d); // 通过向量积求出两向量之间夹角
    kappa           = dphi / norm_delta_xi;

    if (kappa >= 0.07) {
        double pdphi_pcosdphi = -1 / sqrt(1 - pow(cos(dphi), 2));
        double u              = pdphi_pcosdphi / norm_delta_xi;
        double s              = dphi / pow(norm_delta_xi, 2);

        Vector2D m_delta_xip1; // -Δxi+1
        m_delta_xip1.x = -delta_xip1.x;
        m_delta_xip1.y = -delta_xip1.y;
        Vector2D oc1   = OrthogonalComplements(delta_xi, m_delta_xip1);
        Vector2D oc2   = OrthogonalComplements(m_delta_xip1, delta_xi);

        Vector2D p1, p2, k0, k1, k2;
        p1.x = oc1.x / d;
        p1.y = oc1.y / d;
        p2.x = oc2.x / d;
        p2.y = oc2.y / d;
        k1.x = u * (-p1.x - p2.x) - s * delta_xi.x / norm_delta_xi;
        k1.y = u * (-p1.y - p2.y) - s * delta_xi.y / norm_delta_xi;
        k0.x = u * p2.x + s * delta_xi.x / norm_delta_xi;
        k0.y = u * p2.y + s * delta_xi.y / norm_delta_xi;
        k2.x = u * p1.x;
        k2.y = u * p1.y;

        gradient.x = m_vehicle_param_.path_curvature_term * (0.25 * k0.x + 0.5 * k1.x + 0.25 * k2.x);
        gradient.y = m_vehicle_param_.path_curvature_term * (0.25 * k0.y + 0.5 * k1.y + 0.25 * k2.y);
    }
    else {
        gradient.x = 0;
        gradient.y = 0;
    }
    return gradient;
}


/**
 *@brief: 求解平滑项梯度
 *@param  [out] gradient 返回梯度
 *return
 */
inline Vector2D Path_Opti::SmoothnessTerm(Vector2D xim2, Vector2D xim1, Vector2D xi, Vector2D xip1, Vector2D xip2) {
    Vector2D gradient;
    gradient.x = m_vehicle_param_.path_smoothness_term * (xip2.x - 4 * xip1.x + 6 * xi.x - 4 * xim1.x + xim2.x);
    gradient.y = m_vehicle_param_.path_smoothness_term * (xip2.y - 4 * xip1.y + 6 * xi.y - 4 * xim1.y + xim2.y);
    return gradient;
}


/**
 *@brief: 求解两向量的正交补
 *@param
 *return
 */
inline Vector2D Path_Opti::OrthogonalComplements(Vector2D a, Vector2D b) {
    Vector2D oc;
    double   c = (a.x * b.x + a.y * b.y) / (b.x * b.x + b.y * b.y);
    oc.x       = a.x - c * b.x;
    oc.y       = a.y - c * b.y;
    return oc;
}

/**
 *@brief: 尖点延伸函数
 *@param
 *return
 */
void Path_Opti::CuspPointExtension(CollisonCheck& collison_check) {
    Path temp_path;
    for (unsigned int i = 0; i < path_.size() - 1; i++) {
        temp_path.push_back(path_.at(i));
        // 如果方向不变，则直接存储
        if (path_.at(i).direction != path_.at(i + 1).direction) {
            double flag_pos_neg = (path_.at(i).direction == Forward) ? 1.0 : -1.0;
            int    num          = -1;
            Point  temp_point;
            threadLogger_->info("尖点延伸距离：{}", m_vehicle_param_.cusp_extension_distance);
            threadLogger_->info("尖点向前延伸");
            // float average_angle = CalAverageAngle(path_.at(i).angle, path_.at(i + 1).angle);
            // 尖点延伸，需要考虑：尖点延伸过程中出现障碍物碰撞、正常尖点延伸
            for (int j = 1; j <= m_vehicle_param_.cusp_extension_distance; j++) {
                temp_point.angle     = path_.at(i).angle;
                temp_point.x         = path_.at(i).x + flag_pos_neg * j * cos(temp_point.angle);
                temp_point.y         = path_.at(i).y + flag_pos_neg * j * sin(temp_point.angle);
                temp_point.direction = (path_.at(i).direction == Forward) ? Forward : Backward;
                threadLogger_->info("延伸的点坐标({},{},{})", temp_point.x, temp_point.y, temp_point.direction);
                if (false == collison_check.IsVehicleCollisionWithAll(temp_point)) // 如果碰撞，则放弃继续延伸
                {
                    threadLogger_->info("该点碰撞检测通过");
                    temp_path.push_back(temp_point);
                    num = j - 1;
                }
                else {
                    threadLogger_->info("该点碰撞检测不通过");
                    break;
                }
            }
            // 尖点后直线延伸
            threadLogger_->info("尖点后延伸");
            for (int k = num; k >= 0; k--) {
                temp_point.angle     = path_.at(i).angle;
                temp_point.x         = path_.at(i).x + flag_pos_neg * k * cos(temp_point.angle);
                temp_point.y         = path_.at(i).y + flag_pos_neg * k * sin(temp_point.angle);
                temp_point.direction = (path_.at(i).direction == Forward) ? Backward : Forward;
                temp_path.push_back(temp_point);
                threadLogger_->info("延伸的点坐标({},{},{})", temp_point.x, temp_point.y, temp_point.direction);
            }
        }
    }
    temp_path.push_back(path_.back());
    path_ = temp_path;
}

/**
 *@brief: 更新优化路径的角度
 *@param
 *return
 */
void Path_Opti::CalculatePathAngle() {
    // 起点和终点角度不变，中间点角度为当前点的前一点指向后一点的方向角
    for (unsigned int i = 1; i < new_path_.size() - 1; i++) {
        if (IsCusp(i)) {
            continue;
        }
        double dx = (new_path_.at(i + 1).x - new_path_.at(i - 1).x);

        double dy = (new_path_.at(i + 1).y - new_path_.at(i - 1).y);

        double angle = atan(dy / dx);
        // cout << "dx:" << dx << "dy:" << dy << "angle:" << angle << endl;
        if (dx < 0)
            angle = angle + M_PI;
        else if (dx >= 0 && dy < 0)
            angle = angle + 2 * M_PI;
        else
            ;
        if (new_path_.at(i).direction == Backward) // 表示后退
        {
            new_path_.at(i).angle = Helper::NormalizeAngleRad(angle + M_PI);
        }
        else {
            new_path_.at(i).angle = Helper::NormalizeAngleRad(angle);
        }
    }
}


void Path_Opti::CalculateCubicSplineCurve(bool flag, const Path& points, Path& cubicspline_path) {
    vector<double> x_set;
    vector<double> y_set;
    x_set.reserve(points.size());
    y_set.reserve(points.size());
    for (const auto& pt : points) {
        x_set.push_back(pt.x);
        y_set.push_back(pt.y);
    }

    CalculateStation(x_set, y_set);
    sx_.set_points(s_, x_set);
    sy_.set_points(s_, y_set);
    kDeltaS = 0.4;

    float  epsilon = 0.0001; // 容差值
    double s       = 0.0;
    for (s = 0.0; s <= s_.back(); s += kDeltaS) {
        double dx = sx_.deriv(1, s);
        double dy = sy_.deriv(1, s);

        double ddx = sx_.deriv(2, s);
        double ddy = sy_.deriv(2, s);

        // float angle = atan(dy / dx);
        // if (dx < 0)
        //     angle = angle + M_PI;
        // else if (dx >= 0 && dy < 0)
        //     angle = angle + 2 * M_PI;
        float angle = atan2(dy, dx);
        if (angle < 0) {
            angle += 2 * M_PI;
        }
        double cur = (ddy * dx - ddx * dy) / pow(dx * dx + dy * dy, 3.0 / 2);
        // if (fabs(cur) > 0.1) kDeltaS = 0.4;
        Point temp_point;
        temp_point.x         = sx_(s);
        temp_point.y         = sy_(s);
        temp_point.angle     = angle;
        temp_point.curvature = cur;
        if (flag == true)
            temp_point.direction = MotionDirection::Forward;
        else
            temp_point.direction = MotionDirection::Backward;
        cubicspline_path.emplace_back(temp_point);
    }
    s        = s_.back();
    float dx = sx_.deriv(1, s);
    float dy = sy_.deriv(1, s);

    float ddx   = sx_.deriv(2, s);
    float ddy   = sy_.deriv(2, s);
    float angle = atan2(dy, dx);
    if (angle < 0) {
        angle += 2 * M_PI;
    }
    float cur = (ddy * dx - ddx * dy) / pow(dx * dx + dy * dy, 3.0 / 2);
    Point temp_point;
    temp_point.x         = sx_(s);
    temp_point.y         = sy_(s);
    temp_point.angle     = angle;
    temp_point.curvature = cur;
    if (flag == true)
        temp_point.direction = MotionDirection::Forward;
    else
        temp_point.direction = MotionDirection::Backward;
    cubicspline_path.emplace_back(temp_point);

    if (flag == false) {
        for (auto& i : cubicspline_path) {
            i.angle += M_PI;
            if (i.angle > 2 * M_PI) i.angle -= 2 * M_PI;
        }
    }
}

void Path_Opti::CalculateStation(const vector<double>& xs, const vector<double>& ys) {
    double cum = 0.0;
    s_.clear();
    s_.push_back(cum);

    for (unsigned int i = 1; i < xs.size(); i++) {
        double dx = xs.at(i) - xs.at(i - 1);
        double dy = ys.at(i) - ys.at(i - 1);
        cum += hypot(dx, dy);
        s_.push_back(cum);
    }
}

/**
 *@brief: 三次样条插值函数实现
 *@param
 *return
 */
void Path_Opti::CubicInterpolate2Point(const Point start_point, const Point end_point, const double delta_s, Path& interpolate_path) {
    // cout << "start_point.x:" << start_point.x << " start_point.y:" << start_point.y << " end_point.x:" << end_point.x
    // << " end_point.y:" << end_point.y << endl;
    double x1_t   = end_point.x - start_point.x;
    double y1_t   = end_point.y - start_point.y;
    double x1_t_r = x1_t * cos(start_point.angle) + y1_t * sin(start_point.angle);
    double y1_t_r = -x1_t * sin(start_point.angle) + y1_t * cos(start_point.angle);
    double a      = tan(end_point.angle - start_point.angle) / x1_t_r / x1_t_r - 2 * y1_t_r / x1_t_r / x1_t_r / x1_t_r;
    double b      = 3 * y1_t_r / x1_t_r / x1_t_r - tan(end_point.angle - start_point.angle) / x1_t_r;
    double x_i;
    double y_i;
    double theta_i;
    double x_i_r;
    double y_i_r;
    double theta_i_r;
    double x_i_r_t;
    double y_i_r_t;
    int    k = 0;

    Point tem_point;

    if (x1_t_r > 0) // 下一个点在该点的右边
    {
        // cout << ">" << endl;
        // cout<<"x1_t_r:"<<x1_t_r<<endl;
        while ((k * delta_s <= x1_t_r) && (fabs(k * delta_s - x1_t_r) > 1e-3)) {
            // cout << "x_i:" << x_i << endl;
            x_i       = k * delta_s;
            y_i       = a * x_i * x_i * x_i + b * x_i * x_i;
            theta_i   = atan(3 * a * x_i * x_i + 2 * b * x_i);
            x_i_r     = x_i * cos(start_point.angle) - y_i * sin(start_point.angle);
            y_i_r     = x_i * sin(start_point.angle) + y_i * cos(start_point.angle);
            theta_i_r = fmod(theta_i + start_point.angle + 2 * M_PI, 2 * M_PI);
            x_i_r_t   = x_i_r + start_point.x;
            y_i_r_t   = y_i_r + start_point.y;

            tem_point.x         = x_i_r_t;
            tem_point.y         = y_i_r_t;
            tem_point.z         = 0;
            tem_point.angle     = theta_i_r;
            tem_point.direction = end_point.direction;
            // cout << tem_point.angle << endl;
            interpolate_path.push_back(tem_point);

            k++;
        }
    }
    else {
        // cout << "<" << endl;
        while (-k * delta_s >= x1_t_r && (fabs(-k * delta_s - x1_t_r) > 1e-3)) {
            // cout << "x_i:" << x_i << endl;
            x_i       = -k * delta_s;
            y_i       = a * x_i * x_i * x_i + b * x_i * x_i;
            theta_i   = atan(3 * a * x_i * x_i + 2 * b * x_i);
            x_i_r     = x_i * cos(start_point.angle) - y_i * sin(start_point.angle);
            y_i_r     = x_i * sin(start_point.angle) + y_i * cos(start_point.angle);
            theta_i_r = fmod(theta_i + start_point.angle + 2 * M_PI, 2 * M_PI);
            x_i_r_t   = x_i_r + start_point.x;
            y_i_r_t   = y_i_r + start_point.y;

            tem_point.x     = x_i_r_t;
            tem_point.y     = y_i_r_t;
            tem_point.z     = 0;
            tem_point.angle = theta_i_r;
            // cout << tem_point.angle << endl;
            tem_point.direction = end_point.direction;

            interpolate_path.push_back(tem_point);

            k++;
        }
    }
}

/**
 * @brief 判断当前点是否为尖点函数
 */
inline bool Path_Opti::IsCusp(unsigned int n) {
    if (cusp_set_.count(n) == 0)
        return false;
    else
        return true;
}
/**
 * @brief 判断当前点是否为固定点函数
 */
inline bool Path_Opti::IsFixPoint(unsigned int m) {
    if (fixpoint_set_.count(m) == 0)
        return false;
    else
        return true;
}

float CalAverageAngle(float angle_A, float angle_B) {
    float average_angle = 0;
    float angle_diff    = fabs(angle_A - angle_B) > M_PI ? 2 * M_PI - fabs(angle_A - angle_B) : fabs(angle_A - angle_B);
    float new_angle_1 = 0, new_angle_2 = 0;
    new_angle_1 = angle_A + angle_diff / 2.0;
    if (new_angle_1 > 2 * M_PI) new_angle_1 -= 2 * M_PI;
    if (new_angle_1 < 0) new_angle_1 += 2 * M_PI;
    new_angle_2 = angle_B + angle_diff / 2.0;
    if (new_angle_2 > 2 * M_PI) new_angle_2 -= 2 * M_PI;
    if (new_angle_2 < 0) new_angle_2 += 2 * M_PI;
    Vector2D new_angle_1_v, new_angle_2_v;
    new_angle_1_v.x = cos(new_angle_1);
    new_angle_1_v.y = sin(new_angle_1);
    new_angle_2_v.x = cos(new_angle_2);
    new_angle_2_v.y = sin(new_angle_2);
    Vector2D angle_A_v, angle_b_v;
    angle_A_v.x   = cos(angle_A);
    angle_A_v.y   = sin(angle_A);
    angle_b_v.x   = cos(angle_B);
    angle_b_v.y   = sin(angle_B);
    float result1 = angle_A_v.CrossProd(new_angle_1_v);
    float resule2 = angle_b_v.CrossProd(new_angle_1_v);
    float result3 = angle_A_v.CrossProd(new_angle_2_v);
    float resule4 = angle_b_v.CrossProd(new_angle_2_v);
    average_angle = result1 * resule2 > 0 ? atan2(new_angle_2_v.y, new_angle_2_v.x) : atan2(new_angle_1_v.y, new_angle_1_v.x);
    if (average_angle < 0) average_angle += 2 * M_PI;
    return average_angle;
}

void Path_Opti::CurvatureCal(Path& input_path) {
    Point  p1, p2, p3;
    double crossProduct = 0;
    // 计算三角形外接圆的半径
    if (input_path.size() > 2) {
        for (int i = 1; i < input_path.size() - 1; i++) {
            if (input_path.at(i).direction == input_path.at(i + 1).direction) {
                p1           = input_path.at(i - 1);
                p2           = input_path.at(i);
                p3           = input_path.at(i + 1);
                crossProduct = (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x);
                double a     = hypot(p2.x - p3.x, p2.y - p3.y);
                double b     = hypot(p1.x - p3.x, p1.y - p3.y);
                double c     = hypot(p1.x - p2.x, p1.y - p2.y);
                double s     = (a + b + c) / 2.0;
                double area  = std::sqrt(fabs(s * (s - a) * (s - b) * (s - c)));

                double r = (a * b * c) / (4.0 * area);
                if (r == 0 || area == 0) {
                    input_path.at(i).curvature = 0;
                }
                else {
                    input_path.at(i).curvature = 1.0 / r;
                }
            }
            else {
                if (i - 1 > 0) {
                    input_path.at(i).curvature = input_path.at(i - 1).curvature;
                }
                else {
                    input_path.at(i).curvature = 0;
                }
            }
            if (crossProduct < 0) {
                if (input_path.at(i).curvature > 0) {
                    input_path.at(i).curvature *= -1;
                }
            }
        }
        input_path.front().curvature = input_path.at(1).curvature;
        input_path.back().curvature  = input_path.at(input_path.size() - 2).curvature;
    }
}

void Path_Opti::InterpolationPath(Path& input_path) {
    Path final_path;
    final_path.clear();
    Path temp_input_path, temp_output_path;
    int  start_index = 0, end_index = 0;
    bool forward_or_backward = false; // forward:true，backward:false
    threadLogger_->info("input_path.size()：{}", input_path.size());
    for (int i = 0; i < input_path.size() - 1; i++) {
        if (input_path.at(i).direction != input_path.at(i + 1).direction) {
            if (input_path.at(i).direction == MotionDirection::Forward) {
                forward_or_backward = true;
            }
            else {
                forward_or_backward = false;
            }
            end_index = i;
            threadLogger_->info("start_index:{} end_index：{}", start_index, end_index);

            temp_input_path.insert(temp_input_path.end(), input_path.begin() + start_index, input_path.begin() + end_index + 1);
            threadLogger_->info("temp_input_path信息");
            for (auto i : temp_input_path) {
                threadLogger_->info("x:{} y:{} curvature:{} angle:{} direction:{}", i.x, i.y, i.curvature, i.angle / M_PI * 180, i.direction);
            }
            if (temp_input_path.size() > 2) {
                CalculateCubicSplineCurve(forward_or_backward, temp_input_path, temp_output_path);
            }
            else {
                temp_output_path = temp_input_path;
            }

            final_path.insert(final_path.end(), temp_output_path.begin(), temp_output_path.end());
            threadLogger_->info("temp_output_path信息");
            for (auto i : temp_output_path) {
                threadLogger_->info("x:{} y:{} curvature:{} angle:{} direction:{}", i.x, i.y, i.curvature, i.angle / M_PI * 180, i.direction);
            }

            temp_output_path.clear();
            start_index = i + 1;
            temp_input_path.clear();
        }
    }
    if (input_path.at(start_index).direction == MotionDirection::Forward) {
        forward_or_backward = true;
    }
    else {
        forward_or_backward = false;
    }
    threadLogger_->info("start_index:{} end_index：{}", start_index, input_path.size() - 1);
    temp_input_path.insert(temp_input_path.end(), input_path.begin() + start_index, input_path.end());
    threadLogger_->info("temp_input_path信息");
    for (auto i : temp_input_path) {
        threadLogger_->info("x:{} y:{} curvature:{} angle:{} direction:{}", i.x, i.y, i.curvature, i.angle / M_PI * 180, i.direction);
    }
    if (temp_input_path.size() > 2) {
        CalculateCubicSplineCurve(forward_or_backward, temp_input_path, temp_output_path);
    }
    else {
        temp_output_path = temp_input_path;
    }
    final_path.insert(final_path.end(), temp_output_path.begin(), temp_output_path.end());
    threadLogger_->info("temp_output_path信息");
    for (auto i : temp_output_path) {
        threadLogger_->info("x:{} y:{} curvature:{} angle:{} direction:{}", i.x, i.y, i.curvature, i.angle / M_PI * 180, i.direction);
    }
    input_path.clear();
    input_path = final_path;
}
