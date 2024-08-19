/***************************************************/
/*            Author: cxp                          */
/*            Contact: chenxinpeng_hnu@163.com     */
/*            Last update: 2020-04-15              */
/***************************************************/

// #include "../include/glog/logging.h"
#include "path_opti.h"


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

    if (original_path.size() < 5) {
        return;
    }

    // 将传入路径插值成间距step_length的路点
    for (unsigned int i = 0; i < original_path.size() - 1; ++i) {
        double dis_square = pow(original_path.at(i).x - original_path.at(i + 1).x, 2) + pow(original_path.at(i).y - original_path.at(i + 1).y, 2);

        if (dis_square > pow(1.5 * m_vehicle_param_.step_length, 2)) {
            Path tem_path;
            CubicInterpolate2Point(original_path.at(i), original_path.at(i + 1), m_vehicle_param_.step_length, tem_path);
            path_.insert(path_.end(), tem_path.begin(), tem_path.begin() + 2);
        }
        else {
            path_.push_back(original_path.at(i));
        }
    }
    path_.push_back(original_path.back());

    // 如果有尖点，则尝试在尖点处补偿直线
    CuspPointExtension(collison_check);

    // 得到节点和固定点索引
    GetCuspIndex();     // 得到尖点索引查询表cuspLookup
    GetFixPointIndex(); // 得到固定点索引查询表fixpLookup

    unsigned int opti_num     = 0;
    unsigned int max_opti_num = 10;

    // 迭代优化
    while (opti_num++ < max_opti_num) {
        // cout << "第" << opti_num << "次" << endl;
        SmoothPath();
        CalculatePathAngle();
        auto collision_point = collison_check.OptiPathCollisionCheck(new_path_); // 判断优化路径是否碰撞
        if (true == collision_point.empty())                                     // 若无碰撞直接输出
        {
            break;
        }
        else // 否则固定碰撞点，继续优化
        {
            UpdateFixPointSet(collision_point);
        }
    }

    // std::ofstream file_out;
    // file_out.open("control_point.txt");
    // for (size_t index = 0; index < new_path_.size(); index++)
    // {
    //     file_out << 0.0 << " " << new_path_.at(index).x << " " << new_path_.at(index).y << endl;
    // }
    // file_out.close();
    // for (int i = 0; i < new_path_.size(); i++)
    // {
    //     cout << "i: " << new_path_.at(i).x << " " << new_path_.at(i).y << endl;
    // }
    // cout << "开始插值" << endl;

    InterpolatePath(opti_path); // 插值
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
            cusp_set_.insert(i);
        }
    }
    // std::cout << "cusp_set_.size() :" << cusp_set_.size() << std::endl;
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

        // for(unsigned int index = *it; index < path_.size()-1; index++)
        // {
        //     if(fabs(path_.at(index+1)angle - path_.at(index).angle) < 1e-3)
        //     {
        //         continue;
        //     }
        //     else
        //     {
        //         fixpoint_set_.insert(index+1);
        //     }
        // }

        fixpoint_set_.insert(*it + 1);
    }
}

/**
 *@brief: 更新固定点查找表函数
 *@param
 *return
 */
void Path_Opti::UpdateFixPointSet(const vector<unsigned int> cllision_point) {
    // 将所有碰撞点变为固定点
    for (unsigned int i = 0; i < cllision_point.size(); i++) {
        unsigned int index = cllision_point.at(i);
        fixpoint_set_.insert(index);
    }
}

/**
 *@brief: 路径优化核心函数
 *@param
 *return
 */
void Path_Opti::SmoothPath() {
    int            L     = path_.size();
    double         x_sat = 6;
    vector<double> coeff;
    for (int i = 0; i < L; i++) {
        double x    = (i < L / 2) ? i : (L - 1.0 - i);
        double temp = 1 / (1 + exp(-x + x_sat));
        coeff.push_back(temp);
    }

    unsigned int iterations = 0;
    Vector2D     xim2, xim1, xi, xip1, xip2, xoi;
    Vector2D     gradient_error_term;
    Vector2D     gradient_curvature_term;
    Vector2D     gradient_smoothness_term;
    new_path_ = path_;

    // 梯度下降法迭代优化
    while (iterations++ < m_vehicle_param_.max_iterations_opti) {
        for (unsigned int i = 2; i < new_path_.size() - 2; i++) {
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
            new_path_.at(i).x -= coeff.at(i) * gradient_error_term.x;
            new_path_.at(i).y -= coeff.at(i) * gradient_error_term.y;

            // 曲率项
            gradient_curvature_term = CurvatureTerm(xim1, xi, xip1);
            new_path_.at(i).x -= coeff.at(i) * gradient_curvature_term.x;
            new_path_.at(i).y -= coeff.at(i) * gradient_curvature_term.y;

            // 平滑项
            gradient_smoothness_term = SmoothnessTerm(xim2, xim1, xi, xip1, xip2);
            new_path_.at(i).x -= coeff.at(i) * gradient_smoothness_term.x;
            new_path_.at(i).y -= coeff.at(i) * gradient_smoothness_term.y;
        }
    }
    //     for (int i = 0; i < new_path_.size(); i++)
    // {
    //     cout << "i: " << new_path_.at(i).x << " " << new_path_.at(i).y << endl;
    // }
}

/**
 * @brief 求解新路径与原路径偏差项梯度
 * @param[out] gradient  返回梯度
 */
inline Vector2D Path_Opti::ErrorTerm(Vector2D xi, Vector2D xoi) {
    Vector2D gradient;
    gradient.x = m_vehicle_param_.error_term * (xi.x - xoi.x);
    gradient.y = m_vehicle_param_.error_term * (xi.y - xoi.y);
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

    if (kappa >= m_vehicle_param_.max_kappa) {
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

        gradient.x = m_vehicle_param_.curvature_term * (0.25 * k0.x + 0.5 * k1.x + 0.25 * k2.x);
        gradient.y = m_vehicle_param_.curvature_term * (0.25 * k0.y + 0.5 * k1.y + 0.25 * k2.y);
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
    gradient.x = m_vehicle_param_.smoothness_term * (xip2.x - 4 * xip1.x + 6 * xi.x - 4 * xim1.x + xim2.x);
    gradient.y = m_vehicle_param_.smoothness_term * (xip2.y - 4 * xip1.y + 6 * xi.y - 4 * xim1.y + xim2.y);
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
    temp_path.push_back(path_.at(0));
    for (unsigned int i = 1; i < path_.size(); i++) {
        // 如果方向不变，则直接存储
        if (path_.at(i).direction == path_.at(i - 1).direction) {
            temp_path.push_back(path_.at(i));
        }
        else {
            // 尖点处两点距离较近，则舍去一个点
            double dis_square = pow(path_.at(i).x - path_.at(i - 1).x, 2) + pow(path_.at(i).y - path_.at(i - 1).y, 2);
            if (dis_square < pow(0.5 * m_vehicle_param_.step_length, 2)) {
                temp_path.pop_back();
            }
            double       flag_pos_neg = (path_.at(i).direction == Forward) ? -1.0 : 1.0;
            unsigned int num          = 0;
            Point        temp_point;

            // 尖点前直线延伸，最大延伸距离为cusp_extension_distance
            for (int j = 0; j <= m_vehicle_param_.cusp_extension_distance; j++) {
                // std::cout<<" J = " << j << std::endl;
                temp_point.angle     = path_.at(i).angle;
                temp_point.x         = path_.at(i).x + flag_pos_neg * j * cos(temp_point.angle);
                temp_point.y         = path_.at(i).y + flag_pos_neg * j * sin(temp_point.angle);
                temp_point.direction = (path_.at(i).direction == Forward) ? Backward : Forward;
                num                  = j - 1;
                if (false == collison_check.IsVehicleCollision(temp_point)) // 如果碰撞，则放弃继续延伸
                {
                    temp_path.push_back(temp_point);
                }
                else {
                    break;
                }
            }
            temp_path.back().direction = (temp_path.back().direction == Forward) ? Backward : Forward;

            // 尖点后直线延伸
            for (int k = num - 1; k >= 0; k--) {
                // std::cout << "k = " << k << "\n";
                temp_point.angle     = path_.at(i).angle;
                temp_point.x         = path_.at(i).x + flag_pos_neg * k * cos(temp_point.angle);
                temp_point.y         = path_.at(i).y + flag_pos_neg * k * sin(temp_point.angle);
                temp_point.direction = path_.at(i).direction;
                temp_path.push_back(temp_point);
            }
        }
    }
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
        double dx    = (new_path_.at(i + 1).x - new_path_.at(i - 1).x);
        double dy    = (new_path_.at(i + 1).y - new_path_.at(i - 1).y);
        double angle = atan(dy / dx);
        if (dx < 0)
            angle = angle + M_PI;
        else if (dx >= 0 && dy < 0)
            angle = angle + 2 * M_PI;
        else
            ;
        if (new_path_.at(i).direction == Backward) // 表示后退
            new_path_.at(i).angle = Helper::NormalizeAngleRad(angle + M_PI);
        else
            new_path_.at(i).angle = Helper::NormalizeAngleRad(angle);
    }
}

/**
 *@brief: 插值接口函数
 *@param
 *return
 */
// void Path_Opti::InterpolatePath(Path &opti_path)
// {
//     // 两两之间调用CubicInterpolate2Point函数进行插值
//     Path tem_interpolatepath;
//     // for (int i = 0; i < new_path_.size(); i++)
//     // {
//     //     cout << "i: " << new_path_.at(i).x << " " << new_path_.at(i).y << endl;
//     // }

//     for (unsigned int i = 0; i < new_path_.size() - 1; i++)
//     {
//         CubicInterpolate2Point(new_path_.at(i),
//                                new_path_.at(i + 1),
//                                m_vehicle_param_.delta_s,
//                                tem_interpolatepath);
//         opti_path.insert(opti_path.end(), tem_interpolatepath.begin(), tem_interpolatepath.end());
//         Path().swap(tem_interpolatepath);
//         // cout << "*" << endl;
//     }
//     // 存入最后一点
//     Point last_point;
//     int index = new_path_.size() - 1;
//     last_point.x = new_path_.at(index).x;
//     last_point.y = new_path_.at(index).y;
//     last_point.z = 0;
//     last_point.angle = new_path_.at(index).angle;
//     last_point.direction = new_path_.at(index).direction;
//     opti_path.push_back(last_point);
// }

void Path_Opti::InterpolatePath(Path& opti_path) {
    // 先对opti_path进行分段，根据其方向
    // cout << "对路径进行分段" << endl;
    unsigned int start = 0, end = 0;
    vector<Path> vec_path;
    Path         temp_path;
    for (unsigned int i = 0; i < new_path_.size() - 1; i++) {
        if (new_path_.at(i).direction != new_path_.at(i + 1).direction) {
            end = i;
            temp_path.assign(new_path_.begin() + start, new_path_.begin() + end + 1);
            start = end + 1;
            vec_path.push_back(temp_path);
        }
    }
    temp_path.assign(new_path_.begin() + start, new_path_.end());
    vec_path.push_back(temp_path);
    // cout << "路径分段完毕" << endl;
    // cout << "vec_path.size():" << vec_path.size() << endl;

    // 对每个分段的点进行三次B样条拟合，插值间距0.1m
    // vector<Path> vec_path_;
    // temp_path.clear();
    // Path copy_temp_path;
    // bool flag = true;
    // for (unsigned int i = 0; i < vec_path.size(); i++)
    // {
    //     if (vec_path.at(i).front().direction == 0) // 正向 here
    //     {
    //         flag = true;
    //         // 调用三次B样条进行拟合
    //         CalculateCubicSplineCurve(flag, vec_path.at(i), temp_path);
    //         vec_path_.push_back(temp_path);
    //         temp_path.clear();
    //     }
    //     else
    //     {
    //         flag = false;
    //         // 先对整条路进行逆向，再调用三次B样条进行拟合，之后再进行逆向
    //         reverse(vec_path.at(i).begin(), vec_path.at(i).end());
    //         copy_temp_path = vec_path.at(i);
    //         // reverse_copy(vec_path.at(i).begin(), vec_path.at(i).end(), copy_temp_path.begin());
    //         CalculateCubicSplineCurve(flag, copy_temp_path, temp_path);
    //         reverse(temp_path.begin(), temp_path.end());
    //         vec_path_.push_back(temp_path);
    //         temp_path.clear();
    //     }
    // }
    // cout << "jjjj" << endl;

    // 规范一下vec_path的angel，统一约束到【0，2π】
    for (unsigned int i = 0; i < vec_path.size(); i++) {
        for (unsigned int j = 0; j < vec_path.at(i).size(); j++) {
            if (vec_path.at(i).at(j).angle < 0) {
                vec_path.at(i).at(j).angle += 2 * M_PI;
            }
            opti_path.push_back(vec_path.at(i).at(j));
        }
    }


    // cout << "插值结束" << endl;
}

// void Path_Opti::CalculateCubicSplineCurve(bool flag, const Path& points, Path& cubicspline_path) {
//     // cout << "line511" << endl;
//     std::vector<double> x_set;
//     std::vector<double> y_set;
//     x_set.reserve(points.size());
//     y_set.reserve(points.size());
//     for (const auto& pt : points) {
//         // cout<<"pt.x:"<<pt.x<<" pt.y:"<<pt.y<<endl;
//         x_set.push_back(pt.x);
//         y_set.push_back(pt.y);
//     }
//     // cout << "x_set.size()" << x_set.size() << endl;
//     // cout << "x_set.back():" << x_set.back() << endl;
//     // cout << "y_set.size()" << y_set.size() << endl;
//     // cout << "y_set.back():" << y_set.back() << endl;
//     CalculateStation(x_set, y_set);
//     sx_.set_points(s_, x_set);
//     sy_.set_points(s_, y_set);
//     // cout << "line10758  s_.size():" << s_.size() << endl;
//     kDeltaS = 0.1;
//     // cout << "s_.back():" << s_.back() << endl;

//     float epsilon = 0.0001; // 容差值
//     for (double s = 0.0; s <= s_.back(); s += kDeltaS) {
//         double dx = sx_.deriv(1, s);
//         double dy = sy_.deriv(1, s);

//         double ddx = sx_.deriv(2, s);
//         double ddy = sy_.deriv(2, s);

//         float angle = atan(dy / dx);
//         if (dx < 0)
//             angle = angle + M_PI;
//         else if (dx >= 0 && dy < 0)
//             angle = angle + 2 * M_PI;
//         //  cout << "angle = " << angle << endl;
//         double cur = (ddy * dx - ddx * dy) / pow(dx * dx + dy * dy, 3.0 / 2);

//         Point temp_point;
//         temp_point.x         = sx_(s);
//         temp_point.y         = sy_(s);
//         temp_point.angle     = angle;
//         temp_point.curvature = cur;
//         if (flag == true)
//             temp_point.direction = MotionDirection::Forward;
//         else
//             temp_point.direction = MotionDirection::Backward;
//         ;
//         cubicspline_path.emplace_back(temp_point);
//     }
//     // cout << "cubicspline_path.size():" << cubicspline_path.size() << endl;
// }

// void Path_Opti::CalculateStation(const std::vector<double>& xs, const std::vector<double>& ys) {
//     double cum = 0.0;
//     s_.clear();
//     s_.push_back(cum);
//     // cout << "here" << endl;
//     // cout<<"xs.size():"<<xs.size()<<endl;
//     // cout<<"ys.size():"<<ys.size()<<endl;
//     for (unsigned int i = 1; i < xs.size(); i++) {
//         double dx = xs.at(i) - xs.at(i - 1);
//         double dy = ys.at(i) - ys.at(i - 1);
//         cum += std::hypot(dx, dy);
//         // cout<<"cun:"<<cum<<endl;
//         s_.push_back(cum);
//     }
//     // cout << "****s_.back():" << s_.back() << endl;
// }

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
        while ((k * delta_s <= x1_t_r) && (std::fabs(k * delta_s - x1_t_r) > 1e-3)) {
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
            tem_point.direction = start_point.direction;
            cout << tem_point.angle << endl;
            interpolate_path.push_back(tem_point);

            k++;
        }
    }
    else {
        // cout << "<" << endl;
        while (-k * delta_s >= x1_t_r && (std::fabs(-k * delta_s - x1_t_r) > 1e-3)) {
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
            tem_point.direction = start_point.direction;

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
