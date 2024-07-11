/***************************************************/
/*            Author: cxp                          */
/*            Contact: chenxinpeng_hnu@163.com     */
/*            Last update: 2021-07-27              */
/***************************************************/
/*
Description: This is a collection of helper functions that are used throughout the project.
*/
#ifndef HELPER_H
#define HELPER_H

#include "../os/os.h"
#include <math.h>

#define M_PI       3.14159265358979323846

namespace HybridAStar {

namespace Helper {


/**
* @brief 将角度转换到0~2pi
* @param [in] angle 输入角度值(rad)
* @return 返回说明：
* 返回转换后的角度值
*/
static inline float32 NormalizeAngleRad(float32 angle)
{
    if (angle < 0)
    {
        angle = angle - 2.0 * M_PI * (int32)(angle / (2.0 * M_PI));
        return static_cast<float32>(2.0 * M_PI + angle);
    }
    else
    {
        return static_cast<float32>(angle - 2.0 * M_PI * (int32)(angle / (2.0 * M_PI)));
    }
}

/**
* @brief 将角度转换到0~360°
* @param [in] angle 输入角度值(deg)
* @return 返回说明：
* 返回转换后的角度值
*/
static inline float32 NormalizeAngleDeg(float32 angle)
{
    if (angle < 0)
    {
        angle = angle - 360.0 * (int32)(angle / 360.0);
        return static_cast<float32>(360.0 + angle);
    }
    else
    {
        return static_cast<float32>(angle - 360.0 * (int32)(angle / 360.0));
    }
}

/**
* @brief 弧度转角度
* @param [in] angle 输入角度值(rad)
* @return 返回说明：
* 返回转换后的角度值
*/
static inline float32 ToDeg(float32 t) {
  return NormalizeAngleRad(t) * 180.f / M_PI ;
}

/**
* @brief 角度转弧度
* @param [in] angle 输入角度值(deg)
* @return 返回说明：
* 返回转换后的角度值
*/
static inline float32 ToRad(float32 t) {
  return NormalizeAngleRad(t / 180.f * M_PI);
}
}
}

#endif // HELPER_H
