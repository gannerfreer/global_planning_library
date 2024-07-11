/***************************************************/
/*            Author: Biao Xu                      */
/*            Contact: dr_xubiao@163.com           */
/*            Last update: 2020-04-15              */
/***************************************************/
/*
Description: The header file for some general struct.
*/

// Syntax: <package name>_<type>_<file name>_H

#ifndef GENERAL_CLASS_H
#define GENERAL_CLASS_H

#include "../os/os.h"
namespace HybridAStar
{

    /**
    * @brief 规划结果枚举
    */
    enum class PlanResult
    {
        Plan_OK               = 0,     //规划成功
        Plan_Overtime         = -301,  //规划超时
        Plan_Infeasible       = -302,  //无可行路径
        StartPoint_Infeasible = -303,  //起点不可行
        EndPoint_Infeasible   = -304,  //终点不可行
        Map_Infeasible        = -305   //地图不可行
    };
    /**
    * @brief 规划规则枚举
    */
    enum struct PlanRule : int32
    {
        Normal_Planning        = 0,  //正常规划,无特殊限制
        NO_Backward_In_Start   = 1,  //不能倒车起步
        Backward_To_End        = 2,  //必须倒车进入终点，且前进后退只切换一次
        Forward_To_End         = 3,  //RS曲线必须前进拟合到终点
        Backward_All_Time      = 4,  //只后退
        Forward_All_Time       = 5,  //只前进
        Entry_loading_point    = 6,  //进入装载点
        U_Turn                 = 7   //U行转弯(掉头)
    };
    /**
    * @brief 车辆运动方向枚举
    */
    enum MotionDirection
    {
        Forward   = 0,  //前进
        Backward  = 1   //后退
    };

    /**
    * @brief 坐标结构体（用于碰撞检测）
    */
    struct Coordinate
    {
        Coordinate() {
            this->x = 0.0;
            this->y = 0.0;
            this->z = 0.0;
        }
        Coordinate(float64 x_, float64 y_, float64 z_)
        {
            this->x = x_;
            this->y = y_;
            this->z = z_;
        }
        float64 x;  // x坐标, 单位：m
        float64 y;  // y坐标, 单位：m
        float64 z;  // z坐标, 单位：m
    };

    /**
    * @brief 整形坐标结构体（用于2-D启发值计算）
    */
    struct IntCoordinate
    {
        IntCoordinate() {
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }
        IntCoordinate(int16 x_, int16 y_, int16 z_)
        {
            this->x = x_;
            this->y = y_;
            this->z = z_;
        }
        int16 x;  // x坐标, 单位：m
        int16 y;  // y坐标, 单位：m
        int16 z;  // z坐标，单位：m
    };


    /**
    * @brief 路点结构体(车辆构型)
    */
    struct Point
    {
        Point() {
            this->x = 0.0;
            this->y = 0.0;
            this->z = 0.0;
            this->angle = 0.0;
            this->left = 0.0;
            this->right = 0.0;
            this->direction = MotionDirection::Forward;
        }
        Point(float64 x, float64 y, float64 z, float64 angle, MotionDirection direction)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->angle = angle;
            this->direction = direction;
        }
        float64 x;  // x坐标, 单位：m
        float64 y;  // y坐标, 单位：m
        float64 z;  // z坐标, 单位：m
        float64 left; // 距左边界值 单位：m
        float64 right; // 距右边界值 单位：m
        float64 angle;  // 方向, 单位：rad
        float64 curvature;
        MotionDirection direction; //0表示前进，1表示后退(尖点属性随后)
    };
    /**
    * @brief 用于在open集和close集查找的取整point
    */
    struct IntPoint
    {
        int32 x;          // x坐标
        int32 y;          // y坐标
        int32 angle;      // 角度,rad
        MotionDirection direction;   // 行驶方向,0为前进，1为后退
    };

    struct Line {
        float64 x1;
        float64 y1;
        float64 x2;
        float64 y2;
    };


    // 障碍物与地图边界
    typedef vector<vector<Coordinate>> Bound;
    // 带前进后退信息的路径
    typedef std::vector<Point> Path;

}// end namespace

#endif // GENERAL_CLASS_H
