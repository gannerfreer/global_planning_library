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

    threadLogger_->info("平滑内部--相邻点进行一米的插值");
    // 将传入路径插值成间距step_length的路点
    for (unsigned int i = 0; i < original_path.size() - 1; ++i) {
        double dis_square = pow(original_path.at(i).x - original_path.at(i + 1).x, 2) + pow(original_path.at(i).y - original_path.at(i + 1).y, 2);

        if (dis_square > pow(1.5 * m_vehicle_param_.step_length, 2)) {
            Path tem_path;
            CubicInterpolate2Point(original_path.at(i), original_path.at(i + 1), m_vehicle_param_.step_length, tem_path);
            path_.insert(path_.end(), tem_path.begin(), tem_path.end());
            path_.push_back(original_path.at(i + 1));
        }
        else {
            path_.push_back(original_path.at(i));
        }
    }
    path_.push_back(original_path.back());
    // 如果有尖点，则尝试在尖点处补偿直线
    threadLogger_->info("1m插值后，未删除重复点，每个路径点的信息");
    for (auto i : path_) {
        threadLogger_->info("x:{}  y:{}  angle:{}  direction:{}", i.x, i.y, i.angle / M_PI * 180, i.direction);
    }

    // 需要对点进行去重,去掉后面的重复点
    if (path_.size() > 2) {
        // 应用类似的快慢指针逻辑，但这次保留的是从最后一个点开始不重复的点
        int slow = 0, fast = 0;
        while (fast < path_.size()) {
            if (slow == 0 || hypot(path_.at(fast).x - path_.at(slow - 1).x, path_.at(fast).y - path_.at(slow - 1).y) > 0.1) {
                path_.at(slow) = path_.at(fast);
                slow++;
            }
            fast++;
        }

        // 保留不重复的部分
        path_.resize(slow);
    }

    // path_ = original_path;

    // 如果有尖点，则尝试在尖点处补偿直线
    threadLogger_->info("1m插值后,删除重复点，每个路径点的信息");
    for (auto i : path_) {
        threadLogger_->info("x:{}  y:{}  angle:{}  direction:{}", i.x, i.y, i.angle / M_PI * 180, i.direction);
    }

    CuspPointExtension(collison_check);

    CalCurvature(path_);
    CalCurvature(path_);

    Path         path_with_curvature;
    vector<Path> multipath;
    Path         temp_path;

    for (int i = 0; i < path_.size() - 1; i++) {
        if (path_.at(i).direction == path_.at(i + 1).direction) {
            temp_path.push_back(path_.at(i));
        }
        else {
            temp_path.push_back(path_.at(i));
            multipath.push_back(temp_path);
            temp_path.clear();
        }
    }
    multipath.push_back(temp_path);


    threadLogger_->info("三次样条插值环节，一共分出 {} 段路", multipath.size());
    Path final_path;
    for (int i = 0; i < multipath.size(); i++) {
        temp_path.clear();
        CalculateCubicSplineCurve(false, multipath.at(i), temp_path);
        threadLogger_->info("待插值的点信息,数量：{}", multipath.at(i).size());
        for (int j = 0; j < multipath.at(i).size(); j++) {
            threadLogger_->info("x:{}  y:{}  angle:{}  curvature:{}  direction:{}", multipath.at(i).at(j).x, multipath.at(i).at(j).y, multipath.at(i).at(j).angle / M_PI * 180, multipath.at(i).at(j).curvature, multipath.at(i).at(j).direction);
        }
        threadLogger_->info("插值后的点信息，数量：{}", temp_path.size());
        for (int j = 0; j < temp_path.size(); j++) {
            threadLogger_->info("x:{}  y:{}  angle:{}  curvature:{}  direction:{}", temp_path.at(j).x, temp_path.at(j).y, temp_path.at(j).angle / M_PI * 180, temp_path.at(j).curvature, temp_path.at(j).direction);
        }

        final_path.insert(final_path.end(), temp_path.begin(), temp_path.end());
    }

    threadLogger_->info("执行三次样条插值后，每个轨迹点的信息，final_path.size():{}", final_path.size());
    for (int i = 0; i < final_path.size() - 1; i++) {
        threadLogger_->info("x:{}  y:{}  angle:{}  curvature:{}  direction:{}", final_path.at(i).x, final_path.at(i).y, final_path.at(i).angle / M_PI * 180, final_path.at(i).curvature, final_path.at(i).direction);
        threadLogger_->info("相邻点间距 dis: {}", hypot(final_path.at(i).x - final_path.at(i + 1).x, final_path.at(i).y - final_path.at(i + 1).y));
    }

    threadLogger_->info("执行尖点延伸逻辑后，每个轨迹点的信息,path_.size():{}", path_.size());
    for (int i = 0; i < path_.size() - 1; i++) {
        threadLogger_->info("x:{}  y:{}  angle:{}  curvature:{}  direction:{}", path_.at(i).x, path_.at(i).y, path_.at(i).angle / M_PI * 180, path_.at(i).curvature, path_.at(i).direction);
        threadLogger_->info("相邻点间距 dis: {}", hypot(path_.at(i).x - path_.at(i + 1).x, path_.at(i).y - path_.at(i + 1).y));
    }

    std::ofstream file_out;
    file_out.open("youhuaqian.txt");
    for (size_t index = 0; index < path_.size(); index++) {
        file_out << path_.at(index).x << " " << path_.at(index).y << " " << path_.at(index).angle / M_PI * 180 << " " << path_.at(index).direction << endl;
    }
    file_out.close();

    // 得到节点和固定点索引
    GetCuspIndex();     // 得到尖点索引查询表cuspLookup
    GetFixPointIndex(); // 得到固定点索引查询表fixpLookup

    unsigned int opti_num     = 0;
    unsigned int max_opti_num = 10;


    while (opti_num++ < max_opti_num) {
        threadLogger_->info("第 {} 次优化,fixpoint_set_.size():{}", opti_num, fixpoint_set_.size());
        SmoothPath();
        CalculatePathAngle();
        auto collision_point  = collison_check.OptiPathCollisionCheck(new_path_); // 判断优化路径是否碰撞
        bool curvature_exceed = CurvatureCheck();
        if (true == collision_point.empty()) // 若无碰撞且曲率不超标
        {
            break;
        }
        else // 否则固定碰撞点，继续优化
        {
            UpdateFixPointSet(collision_point);
        }
    }


    InterpolatePath(opti_path); // 插值
    // std::ofstream file_out;
    file_out.open("youhuahou.txt");
    for (size_t index = 0; index < opti_path.size(); index++) {
        file_out << opti_path.at(index).x << " " << opti_path.at(index).y << " " << opti_path.at(index).angle / M_PI * 180 << " " << opti_path.at(index).direction << endl;
    }
    file_out.close();
}
bool Path_Opti::CurvatureCheck() {
    CalCurvature(new_path_);
    for (unsigned int i = 0; i < new_path_.size(); i++) {
        double curvature = new_path_.at(i).curvature;
        if (curvature > 0.1) {
            threadLogger_->info("i:{}  curvature:{}  优化过程中曲率超标", i, curvature);
            return true;
        }
    }
    threadLogger_->info("本次优化曲率达标");
    return false;
}
void Path_Opti::CalCurvature(Path& path_) {
    Point  delta_xi;   // Δxi
    Point  delta_xip1; // Δxi+1
    double norm_delta_xi, norm_delta_xip1, d, dphi, kappa;
    if (path_.size() > 2) {
        for (int i = 1; i < path_.size() - 1; i++) {
            if (path_.at(i).direction == path_.at(i + 1).direction) {
                delta_xi.x      = path_.at(i).x - path_.at(i - 1).x;
                delta_xi.y      = path_.at(i).y - path_.at(i - 1).y;
                delta_xip1.x    = path_.at(i + 1).x - path_.at(i).x;
                delta_xip1.y    = path_.at(i + 1).y - path_.at(i).y;
                norm_delta_xi   = sqrt(pow(delta_xi.x, 2) + pow(delta_xi.y, 2));     // |Δxi|
                norm_delta_xip1 = sqrt(pow(delta_xip1.x, 2) + pow(delta_xip1.y, 2)); // |Δxi+1|
                d               = norm_delta_xi * norm_delta_xip1;
                double temp     = (delta_xi.x * delta_xip1.x + delta_xi.y * delta_xip1.y) / d;
                if (temp > 1.0) {
                    temp = 1.0;
                }
                if (temp < -1.0) {
                    temp = -1.0;
                }
                dphi  = acos(temp); // 通过向量积求出两向量之间夹角
                kappa = dphi / norm_delta_xi;
                // threadLogger_->info("delta_xi.x :{} delta_xip1.x:{}  delta_xi.y :{}  delta_xip1.y:{}  d:{}  acos({})", delta_xi.x, delta_xip1.x, delta_xi.y, delta_xip1.y, d, (delta_xi.x * delta_xip1.x + delta_xi.y * delta_xip1.y) / d);
                // threadLogger_->info("kappa :{} dphi:{}  norm_delta_xi:{} ", kappa, dphi, norm_delta_xi);
                path_.at(i).curvature = kappa;
            }

            else {
                if (i - 1 > 0) {
                    path_.at(i).curvature = path_.at(i - 1).curvature;
                }
                else {
                    path_.at(i).curvature = 0;
                }
            }
        }
        path_.front().curvature = path_.at(1).curvature;
        path_.back().curvature  = path_.at(path_.size() - 2).curvature;
    }
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
            cusp_set_.insert(i - 1);
        }
    }
    if (path_.size() > 10) {
        // 将前5个路径点加入固定点
        for (int i = 1; i < 4; i++) {
            cusp_set_.insert(i);
        }

        // 将后5个路径点加入固定点
        for (int i = path_.size() - 2; i >= path_.size() - 4; i--) {
            cusp_set_.insert(i);
        }
    }
    //   cout << "cusp_set_.size() :" << cusp_set_.size() <<   endl;
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
    Vector2D     gradient_vonoroi_term;
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

            // Vonoroi项
            // 需要满足两个条件才会利用voronoi项进行平滑，1、需要使用voronoi图，2、当前传入的路径坐标xi位于voronoi图范围内
            if (use_voronoi) {
                bool in_x_range = false;
                bool in_y_range = false;
                if (static_cast<int>(floor((xi.getX() - voronoi_origin_x) / m_vehicle_param_.vonoroi_grid_dist)) >= 0 && static_cast<int>(floor((xi.getX() - voronoi_origin_x) / m_vehicle_param_.vonoroi_grid_dist)) <= voronoiDiagram->getSizeX()) {
                    in_x_range = true;
                }
                if (static_cast<int>(floor((xi.getY() - voronoi_origin_y) / m_vehicle_param_.vonoroi_grid_dist)) >= 0 && static_cast<int>(floor((xi.getY() - voronoi_origin_y) / m_vehicle_param_.vonoroi_grid_dist)) <= voronoiDiagram->getSizeY()) {
                    in_y_range = true;
                }
                if (use_voronoi && in_x_range && in_y_range) {
                    cout << "计算voronoiterm" << endl;
                    gradient_vonoroi_term = VoronoiTerm(xi);
                    // cout << "算出的梯度为：" << gradient_vonoroi_term.getX() << " " << gradient_vonoroi_term.getY() << endl;
                    if (!isnan(gradient_vonoroi_term.x)) new_path_.at(i).x -= coeff.at(i) * gradient_vonoroi_term.x;
                    if (!isnan(gradient_vonoroi_term.y)) new_path_.at(i).y -= coeff.at(i) * gradient_vonoroi_term.y;
                    cout << "delta_x:" << coeff.at(i) * gradient_vonoroi_term.x << " delta_y:" << coeff.at(i) * gradient_vonoroi_term.y << endl;
                }
                else {
                    // cout << "跳过voronoiterm" << endl;
                }
            }
        }
    }
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


Vector2D Path_Opti::VoronoiTerm(Vector2D xi) {
    Vector2D gradient(0, 0);

    //    alpha > 0 = falloff rate
    //    dObs(x,y) = distance to nearest obstacle
    //    dEge(x,y) = distance to nearest edge of the GVD
    //    dObsMax   = maximum distance for the cost to be applicable
    // distance to the closest obstacle
    // 最近障碍物
    int   index_x = static_cast<int>(floor((xi.getX() - voronoi_origin_x) / m_vehicle_param_.vonoroi_grid_dist));
    int   index_y = static_cast<int>(floor((xi.getY() - voronoi_origin_y) / m_vehicle_param_.vonoroi_grid_dist));
    float obsDst  = voronoiDiagram->getDistance(index_x, index_y);
    // distance to the closest voronoiDiagram edge
    // 最近边
    // wsl-add11
    float edgDst          = 0; // todo
    Vec2i closest_edge_pt = voronoiDiagram->GetClosestVoronoiEdgePoint({index_x, index_y}, edgDst);
    // the vector determining where the obstacle is
    Vector2D obsVct(index_x - voronoiDiagram->getData()[index_x][index_y].obstX, index_y - voronoiDiagram->getData()[index_x][index_y].obstY);
    // the vector determining where the voronoiDiagram edge is
    // wsl-add12
    Vector2D edgVct(index_x - closest_edge_pt.x(), index_y - closest_edge_pt.y()); // todo
                                                                                   // Vec2d edgVct(xi.x() - closest_edge_pt.x(), xi.y() - closest_edge_pt.y());
                                                                                   //  calculate the distance to the closest obstacle from the current node
                                                                                   //  obsDist =  voronoiDiagram.getDistance(node->getX(),node->getY())
                                                                                   //  调试输出

    cout << "节点{" << index_x << "," << index_y << "}距离最近障碍物的距离 obsDst: " << obsDst * m_vehicle_param_.vonoroi_grid_dist << "m" << endl;
    edgDst = hypot(edgVct.getX(), edgVct.getY());
    cout << "节点{" << index_x << "," << index_y << "}距离最近voronoi边的距离 edgDst: " << edgDst * m_vehicle_param_.vonoroi_grid_dist << "m" << endl;

    if (obsDst < vorObsDMax) {
        // calculate the distance to the closest GVD edge from the current node
        //  the node is away from the optimal free space area
        if (edgDst > 0) {
            cout << "edgDst>0" << endl;
            // float PobsDst_Pxi; // todo = obsVct / obsDst;
            // float PedgDst_Pxi; // todo = edgVct / edgDst;
            Vector2D PobsDst_Pxi     = obsVct / obsDst;
            Vector2D PedgDst_Pxi     = edgVct / edgDst;
            float    PvorPtn_PedgDst = alpha * obsDst * pow(obsDst - vorObsDMax, 2) / (pow(vorObsDMax, 2) * (obsDst + alpha) * pow(edgDst + obsDst, 2));

            float PvorPtn_PobsDst = (alpha * edgDst * (obsDst - vorObsDMax) * ((edgDst + 2 * vorObsDMax + alpha) * obsDst + (vorObsDMax + 2 * alpha) * edgDst + alpha * vorObsDMax)) / (pow(vorObsDMax, 2) * pow(obsDst + alpha, 2) * pow(obsDst + edgDst, 2));
            gradient              = m_vehicle_param_.kVoronoiTerm * PvorPtn_PobsDst * PobsDst_Pxi + PvorPtn_PedgDst * PedgDst_Pxi;

            return gradient;
        }
        return gradient;
    }
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
            double       flag_pos_neg = (path_.at(i).direction == Forward) ? -1.0 : 1.0;
            unsigned int num          = 0;
            Point        temp_point;

            // 尖点前直线延伸，最大延伸距离为cusp_extension_distance
            threadLogger_->info("尖点延伸距离：{}", m_vehicle_param_.cusp_extension_distance);
            threadLogger_->info("尖点前延伸");
            for (int j = 2; j <= m_vehicle_param_.cusp_extension_distance + 1; j++) {
                //   cout<<" J = " << j <<   endl;
                temp_point.angle     = path_.at(i).angle;
                temp_point.x         = path_.at(i).x + flag_pos_neg * j * cos(temp_point.angle);
                temp_point.y         = path_.at(i).y + flag_pos_neg * j * sin(temp_point.angle);
                temp_point.direction = (path_.at(i).direction == Forward) ? Backward : Forward;
                threadLogger_->info("延伸的点坐标({},{},{})", temp_point.x, temp_point.y, temp_point.direction);

                num = j - 1;
                if (false == collison_check.IsVehicleCollision(temp_point)) // 如果碰撞，则放弃继续延伸
                {
                    threadLogger_->info("该点碰撞检测通过");
                    temp_path.push_back(temp_point);
                }
                else {
                    threadLogger_->info("该点碰撞检测不通过");
                    break;
                }
            }
            // temp_path.back().direction = (temp_path.back().direction == Forward) ? Backward : Forward;

            // 尖点后直线延伸
            threadLogger_->info("尖点后延伸");

            for (int k = num - 1; k >= 0; k--) {
                //   cout << "k = " << k << "\n";
                temp_point.angle     = path_.at(i).angle;
                temp_point.x         = path_.at(i).x + flag_pos_neg * k * cos(temp_point.angle);
                temp_point.y         = path_.at(i).y + flag_pos_neg * k * sin(temp_point.angle);
                temp_point.direction = path_.at(i).direction;
                temp_path.push_back(temp_point);
                threadLogger_->info("延伸的点坐标({},{},{})", temp_point.x, temp_point.y, temp_point.direction);
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
        double dx = (new_path_.at(i + 1).x - new_path_.at(i - 1).x);

        double dy = (new_path_.at(i + 1).y - new_path_.at(i - 1).y);

        double angle = atan(dy / dx);
        cout << "dx:" << dx << "dy:" << dy << "angle:" << angle << endl;
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
    kDeltaS = 1;

    float epsilon = 0.0001; // 容差值
    for (double s = 0.0; s <= s_.back(); s += kDeltaS) {
        double dx = sx_.deriv(1, s);
        double dy = sy_.deriv(1, s);

        double ddx = sx_.deriv(2, s);
        double ddy = sy_.deriv(2, s);

        float angle = atan(dy / dx);
        if (dx < 0)
            angle = angle + M_PI;
        else if (dx >= 0 && dy < 0)
            angle = angle + 2 * M_PI;
        double cur = (ddy * dx - ddx * dy) / pow(dx * dx + dy * dy, 3.0 / 2);

        Point temp_point;
        temp_point.x         = sx_(s);
        temp_point.y         = sy_(s);
        temp_point.angle     = angle;
        temp_point.curvature = cur;
        if (flag == true)
            temp_point.direction = MotionDirection::Forward;
        else
            temp_point.direction = MotionDirection::Backward;
        ;
        cubicspline_path.emplace_back(temp_point);
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
            cout << tem_point.angle << endl;
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

void Path_Opti::CalCurv(Path& traj) {
    vector<double> vec_x, vec_y, vec_angle;
    int            delta_length = 4, halflengthmark = 0;
    double         distance_halflength = 0;
    int            s                   = traj.size();
    for (int i = 0; i < s; i++) {
        vec_x.push_back(traj.at(i).x);
        vec_y.push_back(traj.at(i).y);
        vec_angle.push_back(traj.at(i).angle);
    }
    // 计算前2m的点的位置halflengthmark
    int j = 0;
    while (j < s - 1) {
        distance_halflength = distance_halflength + hypot(vec_x.at(j + 1) - vec_x.at(j), vec_y.at(j + 1) - vec_y.at(j));
        if (distance_halflength >= delta_length / 2) {
            halflengthmark = j + 1;
            break;
        }
        j++;
    }

    // 计算前1.0m点的曲率
    for (int i = 0; i <= halflengthmark; i++) {
        double distance_front = 0, distance_back = 0;
        int    k = i;
        // 计算当前点距离第一个点的距离
        while (k > 0) {
            distance_back = distance_back + sqrt(pow(vec_x.at(k) - vec_x.at(k - 1), 2) + pow(vec_y.at(k) - vec_y.at(k - 1), 2));
            k--;
        }
        k = i;
        while (k < s - 1) {
            distance_front = distance_front + sqrt(pow(vec_x.at(k + 1) - vec_x.at(k), 2) + pow(vec_y.at(k + 1) - vec_y.at(k), 2));
            if (distance_front >= (delta_length - distance_back)) {
                double anglew_front  = vec_angle.at(k + 1); // 当前点0.5后的点角度
                double delta_anglew  = anglew_front - vec_angle.at(0);
                delta_anglew         = fmod((delta_anglew + 3 * M_PI), (2 * M_PI)) - M_PI; // 角度插值转化，避免 - 180和180处出问题
                traj.at(i).curvature = delta_anglew / delta_length;
                break;
            }
            k++;
        }
    }

    // 计算末尾前0.5m点的位置
    double distance_last_halflength = 0;
    int    lasthalflengthmark       = 0;
    j                               = s - 1;
    while (j > 0) {
        distance_last_halflength = distance_last_halflength + sqrt(pow(vec_x.at(j) - vec_x.at(j - 1), 2) + pow(vec_y.at(j) - vec_y.at(j - 1), 2));
        if (distance_last_halflength >= (delta_length / 2)) {
            lasthalflengthmark = j - 1;
            break;
        }
        j--;
    }

    //%计算末尾0.5米曲率
    for (int i = lasthalflengthmark; i <= s - 1; i++) {
        double distance_back  = 0;
        double distance_front = 0;
        int    k              = i;
        while (k < s - 1) {
            distance_back = distance_back + sqrt(pow(vec_x.at(k + 1) - vec_x.at(k), 2) + pow(vec_y.at(k + 1) - vec_y.at(k), 2));
            k++;
        }
        k = i;
        while (k > 0) {
            distance_front = distance_front + sqrt(pow(vec_x.at(k) - vec_x.at(k - 1), 2) + pow(vec_y.at(k) - vec_y.at(k - 1), 2));
            if (distance_front >= (delta_length - distance_back)) {
                double anglew_back   = vec_angle.at(k - 1);
                double delta_anglew  = vec_angle.at(traj.size() - 1) - anglew_back;
                delta_anglew         = fmod((delta_anglew + 3 * M_PI), (2 * M_PI)) - M_PI;
                traj.at(i).curvature = delta_anglew / delta_length;
                break;
            }
            k--;
        }
    }

    // 计算中间曲率
    for (int i = halflengthmark + 1; i <= lasthalflengthmark - 1; i++) {
        double distance_back  = 0;
        double distance_front = 0;
        double anglew_front   = 0;
        double anglew_back    = 0;
        int    k              = i;
        while (k < s - 1) {
            distance_front = distance_front + sqrt(pow(vec_x.at(k + 1) - vec_x.at(k), 2) + pow(vec_y.at(k + 1) - vec_y.at(k), 2));
            if (distance_front >= delta_length / 2) {
                anglew_front = vec_angle.at(k + 1); // 当前点0.5后的点角度
                break;
            }
            k++;
        }
        k = i;
        while (k > 0) {
            distance_back = distance_back + sqrt(pow(vec_x.at(k) - vec_x.at(k - 1), 2) + pow(vec_y.at(k) - vec_y.at(k - 1), 2));
            if (distance_back >= delta_length / 2) {
                anglew_back = vec_angle.at(k - 1);
                break;
            }
            k--;
        }
        double delta_anglew  = anglew_front - anglew_back;
        delta_anglew         = fmod((delta_anglew + 3 * M_PI), (2 * M_PI)) - M_PI;
        traj.at(i).curvature = delta_anglew / delta_length;
    }
}
