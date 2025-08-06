/*
 * @Author: WuYa
 * @Date: 2023-04-23 09:58:13
 * @LastEditors: WuYa
 * @LastEditTime: 2023-04-23 10:11:53
 * @FilePath: /kuangka_decision_code/src/nodes/node_vehicle_decision/utilities/collision_check/box2d.h
 * @Description:
 *
 * Copyright (c) 2023 by wicri All Rights Reserved.
 */
/******************************************
 > File name:       box2d.h
 > Author:          cxp
 > Created Time:    2021/09/01
 > Brief:           The class of Box2d.
 * ****************************************/
#ifndef BOX_2D_H
#define BOX_2D_H
// Include system lib.
#include <Eigen/Dense> //矩阵库
#include <iostream>
#include <limits>
#include <vector>

typedef double float64;

namespace GlobalPlanning {

typedef Eigen::Matrix<double, 4, 2> FootprintPoints;

class Box2d {
  public:
    Box2d() = default;
    /**
     * @brief Constructor which takes the center, heading, length and width.
     * @param center:  The center of the rectangular bounding box.
     * @param heading: The angle between the x-axis and the heading-axis,measured counter-clockwise(0~2π).
     * @param length:  The size of the heading-axis.
     * @param width:   The size of the axis perpendicular to the heading-axis.
     */
    Box2d(const float64 x, const float64 y, const float64 heading, const float64 length = 0.1, const float64 width = 0.1);

    /**
     * @brief 以后轴中心构造包围盒的构造函数.
     * @param x:  后轴中心横坐标
     * @param heading: 后轴中心航向角
     * @param center2front:  后轴中心到车头距离
     * @param center2rear:   后轴中心到车尾距离
     * @param center2side:   后轴中心到两侧距离
     */
    Box2d(const float64 x, const float64 y, const float64 heading, const float64 center2front, const float64 center2rear, const float64 center2side);


    /**
     * @brief Determines whether these two boxes overlap.
     * @param box: The other box
     * @return True if they overlap
     */
    bool IsOverlap(const Box2d& box) const;


    inline float64 max_x() const {
        return max_x_;
    }
    inline float64 min_x() const {
        return min_x_;
    }
    inline float64 max_y() const {
        return max_y_;
    }
    inline float64 min_y() const {
        return min_y_;
    }
    inline FootprintPoints GetBoxPoint() const {
        return points_;
    }


  private:
    FootprintPoints points_;
    float64         min_x_ = std::numeric_limits<double>::max();
    float64         min_y_ = std::numeric_limits<double>::max();
    float64         max_x_ = std::numeric_limits<double>::lowest();
    float64         max_y_ = std::numeric_limits<double>::lowest();
};

} // namespace GlobalPlanning

#endif //  BOX_2D_H