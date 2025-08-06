/*
 * @Author: WuYa
 * @Date: 2023-04-23 09:58:13
 * @LastEditors: WuYa
 * @LastEditTime: 2023-04-23 10:31:57
 * @FilePath: /kuangka_decision_code/src/nodes/node_vehicle_decision/utilities/collision_check/box2d.cpp
 * @Description:
 *
 * Copyright (c) 2023 by wicri All Rights Reserved.
 */
/******************************************
 > File name:       box2d.cpp
 > Author:          cxp
 > Created Time:    2021/09/01
 > Brief:           调用lattice算法的主函数
 * ****************************************/


#include "box2d.h"
GlobalPlanning::Box2d::Box2d(const float64 x, const float64 y, const float64 heading, const float64 length, const float64 width) {
    Eigen::Matrix<float64, 4, 3> points;
    points << -length / 2, -width / 2, 1, -length / 2, width / 2, 1, length / 2, width / 2, 1, length / 2, -width / 2, 1;

    // Eigen::Matrix3d rotation;
    // rotation << cos(heading), -sin(heading), x, sin(heading), cos(heading), y, 0, 0, 1;
    // points_ = (points * rotation.transpose()).leftCols(2);
    // auto xs = points_.col(0);
    // auto ys = points_.col(1);
    // min_x_  = xs.minCoeff();
    // max_x_  = xs.maxCoeff();
    // min_y_  = ys.minCoeff();
    // max_y_  = ys.maxCoeff();
    // 4 加快创建Box2d的速度
    // 优化项目： 1 取消转置操作（直接创建转置之后的矩阵）；2 减少三次创建新矩阵的操作
    Eigen::Matrix3d transformation;
    transformation << cos(heading), sin(heading), 0, -sin(heading), cos(heading), 0, x, y, 1;
    points_ = (points * transformation).leftCols(2);
    min_x_  = points_.col(0).minCoeff();
    max_x_  = points_.col(0).maxCoeff();
    min_y_  = points_.col(1).minCoeff();
    max_y_  = points_.col(1).maxCoeff();
}


GlobalPlanning::Box2d::Box2d(const float64 x, const float64 y, const float64 heading, const float64 center2front, const float64 center2rear, const float64 center2side) {
    Eigen::Matrix<float64, 4, 3> points;
    points << -center2rear, -center2side, 1, -center2rear, center2side, 1, center2front, center2side, 1, center2front, -center2side, 1;
    // Eigen::Matrix3d rotation;
    // rotation << cos(heading), -sin(heading), x, sin(heading), cos(heading), y, 0, 0, 1;

    // points_ = (points * rotation.transpose()).leftCols(2);
    // auto xs = points_.col(0);
    // auto ys = points_.col(1);
    // min_x_  = xs.minCoeff();
    // max_x_  = xs.maxCoeff();
    // min_y_  = ys.minCoeff();
    // max_y_  = ys.maxCoeff();
    // 4 加快创建Box2d的速度
    // 优化项目： 1 取消转置操作（直接创建转置之后的矩阵）；2 减少三次创建新矩阵的操作
    Eigen::Matrix3d transformation;
    transformation << cos(heading), sin(heading), 0, -sin(heading), cos(heading), 0, x, y, 1;
    points_ = (points * transformation).leftCols(2);
    min_x_  = points_.col(0).minCoeff();
    max_x_  = points_.col(0).maxCoeff();
    min_y_  = points_.col(1).minCoeff();
    max_y_  = points_.col(1).maxCoeff();
}


bool GlobalPlanning::Box2d::IsOverlap(const GlobalPlanning::Box2d& box) const {
    // AABB
    if (box.max_x() < min_x() || box.min_x() > max_x() || box.max_y() < min_y() || box.min_y() > max_y()) {
        return false;
    }
    // OBB
    std::vector<double>         axis = {atan2(points_(1, 1) - points_(0, 1), points_(1, 0) - points_(0, 0)), atan2(points_(2, 1) - points_(1, 1), points_(2, 0) - points_(1, 0)), atan2(box.points_(1, 1) - box.points_(0, 1), box.points_(1, 0) - box.points_(0, 0)), atan2(box.points_(2, 1) - box.points_(1, 1), box.points_(2, 0) - box.points_(1, 0))};
    Eigen::Matrix<double, 2, 1> unit;
    for (auto a : axis) {
        unit << cos(a), sin(a);
        // project all points to corresponding axis
        auto proj1 = points_ * unit;
        auto proj2 = box.points_ * unit;
        // check projection overlap
        if (proj2.maxCoeff() - proj1.minCoeff() < 0 || proj1.maxCoeff() - proj2.minCoeff() < 0) return false;
    }
    return true;
}
