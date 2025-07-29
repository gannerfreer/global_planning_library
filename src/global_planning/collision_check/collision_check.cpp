/***************************************************/
/*            Author: Biao Xu                      */
/*            Contact: dr_xubiao@163.com           */
/*            Last update: 2020-04-17              */
/***************************************************/
/*
  Description: The header file for C++ class collision_check.
*/
#include "collision_check.h"

using namespace GlobalPlanning;

void CollisonCheck::InitParam(_VehicleParam m__VehicleParam) {
    m__VehicleParam_ = m__VehicleParam;
}

/**
 *@brief: 初始化地图边界区域
 *@param
 *return
 */
void CollisonCheck::InitBoundMap(const Bound road_bound) {
    road_bound_map_.clear();
    //    std::cout << " 111m__VehicleParam_.grid_dist = " <<  m__VehicleParam_.grid_dist <<"\n";
    // 将所有地图边界点存入对应栅格中
    for (unsigned int i = 0; i < road_bound.size(); ++i) {
        for (auto iter = road_bound.at(i).begin(); iter != road_bound.at(i).end(); ++iter) {
            IntCoordinate temp_int_point;
            temp_int_point.x      = static_cast<int>(floor(iter->x / m__VehicleParam_.grid_dist));
            temp_int_point.y      = static_cast<int>(floor(iter->y / m__VehicleParam_.grid_dist));
            unsigned int hash     = Coordinate2Hash(temp_int_point);
            auto         iter_vec = road_bound_map_.find(hash);
            if (iter_vec == road_bound_map_.end()) // 若当前栅格点没在road_bound_map_中
            {
                road_bound_map_[hash] = vector<Coordinate>();
                iter_vec              = road_bound_map_.find(hash);
            }
            iter_vec->second.push_back(*iter);
        }
    }
    // std::ofstream file_out;
    // file_out.open("collision_border.txt");
    // for (auto i : road_bound_map_) {
    //     for (auto j : i.second) {
    //         file_out << j.x << " " << j.y << endl;
    //     }
    // }
    // file_out.close();


    cout << "InitBoundMap--road_bound_map_.size():" << road_bound_map_.size() << endl;
}

/**
 *@brief: 初始化障碍物边界区域
 *@param
 *return
 */
void CollisonCheck::InitObstacleMap(const Bound obstacle_bound) {
    obstacle_bound_map_.clear();
    //    std::cout << " 222m__VehicleParam_.grid_dist = " <<  m__VehicleParam_.grid_dist <<"\n";
    // 将所有障碍物边界点存入对应栅格中
    for (unsigned int i = 0; i < obstacle_bound.size(); ++i) {
        for (auto iter = obstacle_bound.at(i).begin(); iter != obstacle_bound.at(i).end(); ++iter) {
            IntCoordinate temp_int_point;
            temp_int_point.x      = static_cast<int>(floor(iter->x / m__VehicleParam_.grid_dist));
            temp_int_point.y      = static_cast<int>(floor(iter->y / m__VehicleParam_.grid_dist));
            unsigned int hash     = Coordinate2Hash(temp_int_point);
            auto         iter_vec = obstacle_bound_map_.find(hash);
            if (iter_vec == obstacle_bound_map_.end()) // 若当前栅格点没在road_bound_map_中
            {
                obstacle_bound_map_[hash] = vector<Coordinate>();
                iter_vec                  = obstacle_bound_map_.find(hash);
            }
            iter_vec->second.push_back(*iter);
        }
    }
    cout << "obstacle_bound_map_.size():" << obstacle_bound_map_.size() << endl;
}

void CollisonCheck::InitWallBoundMap(const Bound wall_bound) {
    wall_bound_map_.clear();
    if (wall_bound.empty()) return;
    //    std::cout << " 111m__VehicleParam_.grid_dist = " <<  m__VehicleParam_.grid_dist <<"\n";
    // 将所有地图边界点存入对应栅格中
    for (unsigned int i = 0; i < wall_bound.size(); ++i) {
        for (auto iter = wall_bound.at(i).begin(); iter != wall_bound.at(i).end(); ++iter) {
            IntCoordinate temp_int_point;
            temp_int_point.x      = static_cast<int>(floor(iter->x / m__VehicleParam_.grid_dist));
            temp_int_point.y      = static_cast<int>(floor(iter->y / m__VehicleParam_.grid_dist));
            unsigned int hash     = Coordinate2Hash(temp_int_point);
            auto         iter_vec = wall_bound_map_.find(hash);
            if (iter_vec == wall_bound_map_.end()) // 若当前栅格点没在wall_bound_map_中
            {
                wall_bound_map_[hash] = vector<Coordinate>();
                iter_vec              = wall_bound_map_.find(hash);
            }
            iter_vec->second.push_back(*iter);
        }
    }
    cout << "InitWallBoundMap--wall_bound_map_.size():" << wall_bound.front().size() << endl;
}


/**
 *@brief: 初始化挡墙边界区域
 *@param
 *return
 */
void CollisonCheck::InitWallMap(const Bound wall_bound) {
    wall_bound_map_.clear();
    //    std::cout << " 222m__VehicleParam_.grid_dist = " <<  m__VehicleParam_.grid_dist <<"\n";
    // 将所有障碍物边界点存入对应栅格中
    for (unsigned int i = 0; i < wall_bound.size(); ++i) {
        for (auto iter = wall_bound.at(i).begin(); iter != wall_bound.at(i).end(); ++iter) {
            IntCoordinate temp_int_point;
            temp_int_point.x      = static_cast<int>(floor(iter->x / m__VehicleParam_.grid_dist));
            temp_int_point.y      = static_cast<int>(floor(iter->y / m__VehicleParam_.grid_dist));
            unsigned int hash     = Coordinate2Hash(temp_int_point);
            auto         iter_vec = wall_bound_map_.find(hash);
            if (iter_vec == wall_bound_map_.end()) // 若当前栅格点没在road_bound_map_中
            {
                wall_bound_map_[hash] = vector<Coordinate>();
                iter_vec              = wall_bound_map_.find(hash);
            }
            iter_vec->second.push_back(*iter);
        }
    }
    cout << "wall_bound_map_.size():" << wall_bound_map_.size() << endl;
}


/**
 *@brief: 判断路径是否跟边界碰撞函数
 *@param
 *return
 */
bool CollisonCheck::IsRSPathCollision(const Path& my_rspath) {
    for (int i = 0; i < my_rspath.size(); ++i) {
        if (true == IsVehicleCollision(my_rspath.at(i)))
            return true;
        else
            ;
    }
    return false;
}

/**
 *@brief: 判断优化路径是否跟边界碰撞函数
 *@param
 *return
 */
vector<unsigned int> CollisonCheck::OptiPathCollisionCheck(const Path& my_optipath) {
    vector<unsigned int> collision_point;
    for (int i = 0; i < my_optipath.size(); ++i) {
        if (!IsVehicleCollisionRoadBound(my_optipath.at(i), m__VehicleParam_.safe_margin_bound - m__VehicleParam_.safe_margin_error)) {
            if (obstacle_bound_map_.empty() || !IsVehicleCollisionObstacleBound(my_optipath.at(i), m__VehicleParam_.safe_margin_obstacle - m__VehicleParam_.safe_margin_error)) {
                continue;
            }
        }
        collision_point.push_back(i);
    }
    return collision_point;
}

/**
 *@brief: 判断优化路径是否跟所有障碍物碰撞
 *@param
 *return
 */
vector<unsigned int> CollisonCheck::OptiPathCollisionCheckWithAll(const Path& my_optipath) {
    vector<unsigned int> collision_point;
    for (int i = 0; i < my_optipath.size(); ++i) {
        if (!IsVehicleCollisionRoadBound(my_optipath.at(i), m__VehicleParam_.safe_margin_bound - m__VehicleParam_.safe_margin_error)) {
            // std::cout << "与静态边界不撞" << endl;
            if (obstacle_bound_map_.empty() || !IsVehicleCollisionObstacleBound(my_optipath.at(i), m__VehicleParam_.safe_margin_obstacle - m__VehicleParam_.safe_margin_error)) {
                // std::cout << "与挖机不撞" << endl;
                if (wall_bound_map_.empty() || !IsVehicleCollisionWallBound(my_optipath.at(i), m__VehicleParam_.safe_margin_wall - m__VehicleParam_.safe_margin_error)) {
                    // std::cout << "与挡墙不撞" << endl;
                    continue;
                }
            }
        }
        collision_point.push_back(i);
    }
    return collision_point;
}

/**
 *@brief: 判断路径是否与装载区动态边界和挖机碰撞
 *@param
 *return
 */
vector<unsigned int> CollisonCheck::DepartPathCollisionCheck(const Path& my_optipath) {
    vector<unsigned int> collision_point;
    for (int i = 0; i < my_optipath.size(); ++i) {
        if (!IsVehicleCollisionWallBound(my_optipath.at(i), m__VehicleParam_.safe_margin_bound - m__VehicleParam_.safe_margin_error)) {
            if (obstacle_bound_map_.empty() || !IsVehicleCollisionObstacleBound(my_optipath.at(i), m__VehicleParam_.safe_margin_obstacle - m__VehicleParam_.safe_margin_error)) {
                continue;
            }
        }
        collision_point.push_back(i);
    }
    return collision_point;
}

/**
 *@brief: 判断车辆位置是否跟边界碰撞函数
 *@param
 *return
 */
bool CollisonCheck::IsVehicleCollision(const Point& my_point) {
    utility::CTimeCounterTool time_tool(&time_couter_);
    if (!IsVehicleCollisionRoadBound(my_point, m__VehicleParam_.safe_margin_bound)) {
        if (obstacle_bound_map_.empty()) {
            return false;
        }

        return IsVehicleCollisionObstacleBound(my_point, m__VehicleParam_.safe_margin_obstacle);
    }
    return true;
}

/**
 *@brief: 计算两向量叉乘函数
 *@param
 *return
 */
double CollisonCheck::GetCross(Coordinate& p1, Coordinate& p2, Coordinate& p) {
    // 计算|p1 p2| x |p1 p|
    return (p2.x - p1.x) * (p.y - p1.y) - (p.x - p1.x) * (p2.y - p1.y);
}

/**
 *@brief: 判断点是否在矩形内函数
 *@param
 *return
 */
bool CollisonCheck::IsPointInMatrix(Coordinate& p, Coordinate& p1, Coordinate& p2, Coordinate& p3, Coordinate& p4) {
    return GetCross(p1, p2, p) * GetCross(p3, p4, p) >= 0 && GetCross(p2, p3, p) * GetCross(p4, p1, p) >= 0;
}

/**
 *@brief: 判断车辆位置是否跟地图边界碰撞函数
 *@param
 *return
 */
bool CollisonCheck::IsVehicleCollisionRoadBound(const Point& my_point, const double& safe_distance) {
    double cosa = cos(my_point.angle);
    double sina = sin(my_point.angle);

    // 计算车辆安全包络左前角坐标
    double     x_lf = my_point.x + (m__VehicleParam_.veh_center_2_front + safe_distance) * cosa - (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
    double     y_lf = my_point.y + (m__VehicleParam_.veh_center_2_front + safe_distance) * sina + (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
    Coordinate point_lf(x_lf, y_lf, my_point.z);

    // 计算车辆安全包络右前角坐标
    double     x_rf = my_point.x + (m__VehicleParam_.veh_center_2_front + safe_distance) * cosa + (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
    double     y_rf = my_point.y + (m__VehicleParam_.veh_center_2_front + safe_distance) * sina - (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
    Coordinate point_rf(x_rf, y_rf, my_point.z);

    // 计算车辆安全包络左后角坐标
    double     x_lr = my_point.x + -(m__VehicleParam_.veh_center_2_rear_bound + safe_distance) * cosa - (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
    double     y_lr = my_point.y + -(m__VehicleParam_.veh_center_2_rear_bound + safe_distance) * sina + (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
    Coordinate point_lr(x_lr, y_lr, my_point.z);

    // 计算车辆安全包络右后角坐标
    double     x_rr = my_point.x + -(m__VehicleParam_.veh_center_2_rear_bound + safe_distance) * cosa + (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
    double     y_rr = my_point.y + -(m__VehicleParam_.veh_center_2_rear_bound + safe_distance) * sina - (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
    Coordinate point_rr(x_rr, y_rr, my_point.z);

    // 使用轴对齐包围盒AABB包络车辆安全包络
    double x_aabb_min = x_lf < x_rf ? x_lf : x_rf;
    x_aabb_min        = x_aabb_min < x_lr ? x_aabb_min : x_lr;
    x_aabb_min        = x_aabb_min < x_rr ? x_aabb_min : x_rr;

    double x_aabb_max = x_lf > x_rf ? x_lf : x_rf;
    x_aabb_max        = x_aabb_max > x_lr ? x_aabb_max : x_lr;
    x_aabb_max        = x_aabb_max > x_rr ? x_aabb_max : x_rr;

    double y_aabb_min = y_lf < y_rf ? y_lf : y_rf;
    y_aabb_min        = y_aabb_min < y_lr ? y_aabb_min : y_lr;
    y_aabb_min        = y_aabb_min < y_rr ? y_aabb_min : y_rr;

    double y_aabb_max = y_lf > y_rf ? y_lf : y_rf;
    y_aabb_max        = y_aabb_max > y_lr ? y_aabb_max : y_lr;
    y_aabb_max        = y_aabb_max > y_rr ? y_aabb_max : y_rr;

    // 计算方向包络盒占据的网格上下限
    int x_int_aabb_min = static_cast<int>(floor(x_aabb_min / m__VehicleParam_.grid_dist));
    int x_int_aabb_max = static_cast<int>(ceil(x_aabb_max / m__VehicleParam_.grid_dist));
    int y_int_aabb_min = static_cast<int>(floor(y_aabb_min / m__VehicleParam_.grid_dist));
    int y_int_aabb_max = static_cast<int>(ceil(y_aabb_max / m__VehicleParam_.grid_dist));

    // 遍历每个栅格点进行碰撞检测
    IntCoordinate temp_int_point;
    for (int i = x_int_aabb_min; i <= x_int_aabb_max; ++i) {
        for (int j = y_int_aabb_min; j <= y_int_aabb_max; ++j) {
            temp_int_point.x      = i;
            temp_int_point.y      = j;
            unsigned int hash     = Coordinate2Hash(temp_int_point);
            auto         iter_vec = road_bound_map_.find(hash);
            if (iter_vec != road_bound_map_.end()) {
                for (auto iter = iter_vec->second.begin(); iter != iter_vec->second.end(); ++iter) {
                    if (IsPointInMatrix(*iter, point_lf, point_lr, point_rr, point_rf) == true) {
                        // cout << "点坐标：(" << iter->x << " ," << iter->y << ")" << endl;
                        // cout << "车坐标：(" << point_lf.x << "," << point_lf.y << "),(" << point_lr.x << "," << point_lr.y << "),(" << point_rr.x << "," << point_rr.y << "),(" << point_rf.x << "," << point_rf.y << ")" << endl;
                        return true;
                    }
                    else
                        ;
                }
            }
        }
    }
    return false;
}

/**
 *@brief: 判断车辆位置是否跟障碍物边界碰撞函数
 *@param
 *return
 */
bool CollisonCheck::IsVehicleCollisionObstacleBound(const Point& my_point, const double& safe_distance) {
    double cosa = cos(my_point.angle);
    double sina = sin(my_point.angle);

    if (my_point.direction == MotionDirection::Forward) {
        // 计算车辆安全包络左前角坐标
        double     x_lf = my_point.x + (m__VehicleParam_.veh_center_2_front + safe_distance) * cosa - (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
        double     y_lf = my_point.y + (m__VehicleParam_.veh_center_2_front + safe_distance) * sina + (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
        Coordinate point_lf(x_lf, y_lf, my_point.z);

        // 计算车辆安全包络右前角坐标
        double     x_rf = my_point.x + (m__VehicleParam_.veh_center_2_front + safe_distance) * cosa + (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
        double     y_rf = my_point.y + (m__VehicleParam_.veh_center_2_front + safe_distance) * sina - (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
        Coordinate point_rf(x_rf, y_rf, my_point.z);

        // 计算车辆安全包络左后角坐标
        double     x_lr = my_point.x + -(m__VehicleParam_.veh_center_2_rear_bound) * cosa - (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
        double     y_lr = my_point.y + -(m__VehicleParam_.veh_center_2_rear_bound) * sina + (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
        Coordinate point_lr(x_lr, y_lr, my_point.z);

        // 计算车辆安全包络右后角坐标
        double     x_rr = my_point.x + -(m__VehicleParam_.veh_center_2_rear_bound) * cosa + (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
        double     y_rr = my_point.y + -(m__VehicleParam_.veh_center_2_rear_bound) * sina - (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
        Coordinate point_rr(x_rr, y_rr, my_point.z);

        // 使用轴对齐包围盒AABB包络车辆安全包络
        double x_aabb_min = x_lf < x_rf ? x_lf : x_rf;
        x_aabb_min        = x_aabb_min < x_lr ? x_aabb_min : x_lr;
        x_aabb_min        = x_aabb_min < x_rr ? x_aabb_min : x_rr;

        double x_aabb_max = x_lf > x_rf ? x_lf : x_rf;
        x_aabb_max        = x_aabb_max > x_lr ? x_aabb_max : x_lr;
        x_aabb_max        = x_aabb_max > x_rr ? x_aabb_max : x_rr;

        double y_aabb_min = y_lf < y_rf ? y_lf : y_rf;
        y_aabb_min        = y_aabb_min < y_lr ? y_aabb_min : y_lr;
        y_aabb_min        = y_aabb_min < y_rr ? y_aabb_min : y_rr;

        double y_aabb_max = y_lf > y_rf ? y_lf : y_rf;
        y_aabb_max        = y_aabb_max > y_lr ? y_aabb_max : y_lr;
        y_aabb_max        = y_aabb_max > y_rr ? y_aabb_max : y_rr;

        // 计算方向包络盒占据的网格上下限
        int x_int_aabb_min = static_cast<int>(floor(x_aabb_min / m__VehicleParam_.grid_dist));
        int x_int_aabb_max = static_cast<int>(ceil(x_aabb_max / m__VehicleParam_.grid_dist));
        int y_int_aabb_min = static_cast<int>(floor(y_aabb_min / m__VehicleParam_.grid_dist));
        int y_int_aabb_max = static_cast<int>(ceil(y_aabb_max / m__VehicleParam_.grid_dist));

        // 遍历每个栅格点进行碰撞检测
        IntCoordinate temp_int_point;
        for (int i = x_int_aabb_min; i <= x_int_aabb_max; ++i) {
            for (int j = y_int_aabb_min; j <= y_int_aabb_max; ++j) {
                temp_int_point.x      = i;
                temp_int_point.y      = j;
                unsigned int hash     = Coordinate2Hash(temp_int_point);
                auto         iter_vec = obstacle_bound_map_.find(hash);
                if (iter_vec != obstacle_bound_map_.end()) {
                    for (auto iter = iter_vec->second.begin(); iter != iter_vec->second.end(); ++iter) {
                        if (IsPointInMatrix(*iter, point_lf, point_lr, point_rr, point_rf) == true) // 存在一个点发生碰撞
                            return true;
                        else
                            ;
                    }
                }
            }
        }
    }
    else {
        // 计算车辆安全包络左前角坐标
        double     x_lf = my_point.x + (m__VehicleParam_.veh_center_2_front) * cosa - (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
        double     y_lf = my_point.y + (m__VehicleParam_.veh_center_2_front) * sina + (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
        Coordinate point_lf(x_lf, y_lf, my_point.z);

        // 计算车辆安全包络右前角坐标
        double     x_rf = my_point.x + (m__VehicleParam_.veh_center_2_front) * cosa + (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
        double     y_rf = my_point.y + (m__VehicleParam_.veh_center_2_front) * sina - (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
        Coordinate point_rf(x_rf, y_rf, my_point.z);

        // 计算车辆安全包络左后角坐标
        double     x_lr = my_point.x + -(m__VehicleParam_.veh_center_2_rear_bound + safe_distance) * cosa - (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
        double     y_lr = my_point.y + -(m__VehicleParam_.veh_center_2_rear_bound + safe_distance) * sina + (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
        Coordinate point_lr(x_lr, y_lr, my_point.z);

        // 计算车辆安全包络右后角坐标
        double     x_rr = my_point.x + -(m__VehicleParam_.veh_center_2_rear_bound + safe_distance) * cosa + (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
        double     y_rr = my_point.y + -(m__VehicleParam_.veh_center_2_rear_bound + safe_distance) * sina - (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
        Coordinate point_rr(x_rr, y_rr, my_point.z);

        // 使用轴对齐包围盒AABB包络车辆安全包络
        double x_aabb_min = x_lf < x_rf ? x_lf : x_rf;
        x_aabb_min        = x_aabb_min < x_lr ? x_aabb_min : x_lr;
        x_aabb_min        = x_aabb_min < x_rr ? x_aabb_min : x_rr;

        double x_aabb_max = x_lf > x_rf ? x_lf : x_rf;
        x_aabb_max        = x_aabb_max > x_lr ? x_aabb_max : x_lr;
        x_aabb_max        = x_aabb_max > x_rr ? x_aabb_max : x_rr;

        double y_aabb_min = y_lf < y_rf ? y_lf : y_rf;
        y_aabb_min        = y_aabb_min < y_lr ? y_aabb_min : y_lr;
        y_aabb_min        = y_aabb_min < y_rr ? y_aabb_min : y_rr;

        double y_aabb_max = y_lf > y_rf ? y_lf : y_rf;
        y_aabb_max        = y_aabb_max > y_lr ? y_aabb_max : y_lr;
        y_aabb_max        = y_aabb_max > y_rr ? y_aabb_max : y_rr;

        // 计算方向包络盒占据的网格上下限
        int x_int_aabb_min = static_cast<int>(floor(x_aabb_min / m__VehicleParam_.grid_dist));
        int x_int_aabb_max = static_cast<int>(ceil(x_aabb_max / m__VehicleParam_.grid_dist));
        int y_int_aabb_min = static_cast<int>(floor(y_aabb_min / m__VehicleParam_.grid_dist));
        int y_int_aabb_max = static_cast<int>(ceil(y_aabb_max / m__VehicleParam_.grid_dist));

        // 遍历每个栅格点进行碰撞检测
        IntCoordinate temp_int_point;
        for (int i = x_int_aabb_min; i <= x_int_aabb_max; ++i) {
            for (int j = y_int_aabb_min; j <= y_int_aabb_max; ++j) {
                temp_int_point.x      = i;
                temp_int_point.y      = j;
                unsigned int hash     = Coordinate2Hash(temp_int_point);
                auto         iter_vec = obstacle_bound_map_.find(hash);
                if (iter_vec != obstacle_bound_map_.end()) {
                    for (auto iter = iter_vec->second.begin(); iter != iter_vec->second.end(); ++iter) {
                        if (IsPointInMatrix(*iter, point_lf, point_lr, point_rr, point_rf) == true) // 存在一个点发生碰撞
                            return true;
                        else
                            ;
                    }
                }
            }
        }
    }
    return false;
}

/**
 *@brief: 判断车辆位置是否跟挡墙碰撞函数
 *@param
 *return
 */
bool CollisonCheck::IsVehicleCollisionWallBound(const Point& my_point, const double& safe_distance) {
    double cosa = cos(my_point.angle);
    double sina = sin(my_point.angle);

    // 计算车辆安全包络左前角坐标
    double     x_lf = my_point.x + (m__VehicleParam_.veh_center_2_front + safe_distance) * cosa - (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
    double     y_lf = my_point.y + (m__VehicleParam_.veh_center_2_front + safe_distance) * sina + (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
    Coordinate point_lf(x_lf, y_lf, my_point.z);

    // 计算车辆安全包络右前角坐标
    double     x_rf = my_point.x + (m__VehicleParam_.veh_center_2_front + safe_distance) * cosa + (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
    double     y_rf = my_point.y + (m__VehicleParam_.veh_center_2_front + safe_distance) * sina - (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
    Coordinate point_rf(x_rf, y_rf, my_point.z);

    // 计算车辆安全包络左后角坐标
    double     x_lr = my_point.x + -(m__VehicleParam_.veh_center_2_rear_bound + safe_distance) * cosa - (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
    double     y_lr = my_point.y + -(m__VehicleParam_.veh_center_2_rear_bound + safe_distance) * sina + (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
    Coordinate point_lr(x_lr, y_lr, my_point.z);

    // 计算车辆安全包络右后角坐标
    double     x_rr = my_point.x + -(m__VehicleParam_.veh_center_2_rear_bound + safe_distance) * cosa + (m__VehicleParam_.veh_center_2_side + safe_distance) * sina;
    double     y_rr = my_point.y + -(m__VehicleParam_.veh_center_2_rear_bound + safe_distance) * sina - (m__VehicleParam_.veh_center_2_side + safe_distance) * cosa;
    Coordinate point_rr(x_rr, y_rr, my_point.z);

    // 使用轴对齐包围盒AABB包络车辆安全包络
    double x_aabb_min = x_lf < x_rf ? x_lf : x_rf;
    x_aabb_min        = x_aabb_min < x_lr ? x_aabb_min : x_lr;
    x_aabb_min        = x_aabb_min < x_rr ? x_aabb_min : x_rr;

    double x_aabb_max = x_lf > x_rf ? x_lf : x_rf;
    x_aabb_max        = x_aabb_max > x_lr ? x_aabb_max : x_lr;
    x_aabb_max        = x_aabb_max > x_rr ? x_aabb_max : x_rr;

    double y_aabb_min = y_lf < y_rf ? y_lf : y_rf;
    y_aabb_min        = y_aabb_min < y_lr ? y_aabb_min : y_lr;
    y_aabb_min        = y_aabb_min < y_rr ? y_aabb_min : y_rr;

    double y_aabb_max = y_lf > y_rf ? y_lf : y_rf;
    y_aabb_max        = y_aabb_max > y_lr ? y_aabb_max : y_lr;
    y_aabb_max        = y_aabb_max > y_rr ? y_aabb_max : y_rr;

    // 计算方向包络盒占据的网格上下限
    int x_int_aabb_min = static_cast<int>(floor(x_aabb_min / m__VehicleParam_.grid_dist));
    int x_int_aabb_max = static_cast<int>(ceil(x_aabb_max / m__VehicleParam_.grid_dist));
    int y_int_aabb_min = static_cast<int>(floor(y_aabb_min / m__VehicleParam_.grid_dist));
    int y_int_aabb_max = static_cast<int>(ceil(y_aabb_max / m__VehicleParam_.grid_dist));


    // 遍历每个栅格点进行碰撞检测
    IntCoordinate temp_int_point;
    for (int i = x_int_aabb_min; i <= x_int_aabb_max; ++i) {
        for (int j = y_int_aabb_min; j <= y_int_aabb_max; ++j) {
            temp_int_point.x      = i;
            temp_int_point.y      = j;
            unsigned int hash     = Coordinate2Hash(temp_int_point);
            auto         iter_vec = wall_bound_map_.find(hash);
            if (iter_vec != wall_bound_map_.end()) {
                for (auto iter = iter_vec->second.begin(); iter != iter_vec->second.end(); ++iter) {
                    if (IsPointInMatrix(*iter, point_lf, point_lr, point_rr, point_rf) == true) {
                        // cout << "点坐标：(" << iter->x << " ," << iter->y << ")" << endl;
                        // cout << "车坐标：(" << point_lf.x << "," << point_lf.y << "),(" << point_lr.x << "," << point_lr.y << "),(" << point_rr.x << "," << point_rr.y << "),(" << point_rf.x << "," << point_rf.y << ")" << endl;
                        return true;
                    }
                    else
                        ;
                }
            }
        }
    }
    return false;
}


/**
 *@brief: 将坐标形式转为哈希值
 *@param
 *return
 */
unsigned int CollisonCheck::Coordinate2Hash(const IntCoordinate& point) {
    unsigned int hash = 0;
    short        x    = static_cast<short>(point.x);
    short        y    = static_cast<short>(point.y);

    hash |= (x & 0xFFFF) << 16;
    hash |= (y & 0xFFFF);

    return hash;
}
// end namespace
