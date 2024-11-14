/***************************************************/
/*            Author: cxp                          */
/*            Contact: chenxinpeng_hnu@163.com	   */
/*            Last update: 2020-04-15              */
/***************************************************/
/*
  Description: The header file for C++ class path_opti.
*/

// Syntax: <package name>_<type>_<file name>_H
#ifndef PATH_OPTI_H
#define PATH_OPTI_H

#include <unordered_set>

#include "../collision_check/collision_check.h"
#include "../common/common_struct.h"
#include "../math/helper.h"
#include "../planner/pathplanner/spline/spline.h"
#include "dynamicvoronoi.h"
// #include "../os/os.h"
#include "vector2d.h"

using namespace GlobalPlanning;
using namespace std;

// namespace HybridAStar
//{
/**
 * @brief 二维向量
 */
// struct Vector2D {
//     double x;
//     double y;
// };
/**
 * @brief 路径优化结果枚举
 */
enum class OptiResult {
    Opti_OK     = 1, // 优化成功
    Opti_Failed = 0  // 优化失败
};
/**
 * @brief 路径优化类
 */

class Path_Opti {
  public:
    Path_Opti() {}  // 默认构造函数
    ~Path_Opti() {} // 析构函数
    /**
     * @brief 路径优化类接口函数
     * @param[in] original_path    初始路径
     * @param[out] opti_path  最终的路径
     * @return 返回说明：
     * true:  优化成功
     * false: 优化失败
     */
    void                            OptimizePath(Path& original_path, Path& opti_path, CollisonCheck& collisonCheck, _VehicleParam m_vehicle_param);
    vector<unsigned int>            CurvatureCheck();
    void                            CalCurv(Path& traj);
    void                            CalCurvature(Path& new_path_);
    void                            CalculateCubicSplineCurve(bool flag, const Path& points, Path& cubicspline_path);
    void                            CalculateStation(const std::vector<double>& xs, const std::vector<double>& ys);
    DynamicVoronoi*                 voronoiDiagram;
    float                           obsDMax    = 2;
    float                           vorObsDMax = 282;
    float                           alpha      = 0.1;
    bool                            use_voronoi;
    float                           voronoi_origin_x, voronoi_origin_y;
    std::shared_ptr<spdlog::logger> threadLogger_;

  private:
    /**
     * @brief 尖点延伸函数
     * @param[in] collison_check 碰撞检测类对象
     * @return 返回说明：无
     */
    void CuspPointExtension(CollisonCheck& collison_check);
    /**
     * @brief 尖点索引查找函数
     * @return 返回说明：无
     */
    void GetCuspIndex();
    /**
     * @brief 获取固定点索引函数
     * @return 返回说明：无
     */
    void GetFixPointIndex();
    /**
     * @brief 更新固定点索引函数
     * @param[in] cllision_point 碰撞点索引集
     * @return 返回说明：
     */
    void UpdateFixPointSet(const vector<unsigned int> points);
    /**
     * @brief 路径优化核心函数
     * @return 返回说明：无
     */
    void SmoothPath();
    /**
     * @brief 原路径与平滑后路径的偏差项梯度求解函数
     * @param[in]  xi  新路径的当前点
     * @param[in]  xoi 原路径的当前点
     * @return 返回说明：
     * 返回梯度求解结果
     */
    inline Vector2D ErrorTerm(Vector2D xi, Vector2D xoi);
    /**
     * @brief 曲率项梯度求解函数
     * @param[in]  xim1 当前点前一点
     * @param[in]  xi   当前点
     * @param[in]  xip1 当前点后一点
     * @return 返回说明：
     * 返回梯度求解结果
     */
    inline Vector2D CurvatureTerm(Vector2D xim1, Vector2D xi, Vector2D xip1);
    /**
     * @brief 平滑项梯度求解函数
     * @param[in]  xim2 当前点前两点
     * @param[in]  xim1 当前点前一点
     * @param[in]  xi   当前点
     * @param[in]  xip1 当前点后一点
     * @param[in]  xip2 当前点后两点
     * @return 返回说明：
     * 返回梯度求解结果
     */
    inline Vector2D SmoothnessTerm(Vector2D xim2, Vector2D xim1, Vector2D xi, Vector2D xip1, Vector2D xip2);
    Vector2D        VoronoiTerm(Vector2D xi);
    /**
     * @brief 平滑项梯度求解函数
     * @param[in]  a,b 输入的两个向量
     * @return 返回说明：
     * 返回正交补求解结果
     */
    inline Vector2D OrthogonalComplements(Vector2D a, Vector2D b);
    /**
     * @brief 路径角度计算函数
     * @return 返回说明：无
     */
    void CalculatePathAngle();
    /**
     * @brief 路径插值接口函数
     * @param[in & out]  opti_path 待插值路径
     * @return 返回说明：无
     */
    void InterpolatePath(Path& opti_path);
    /**
     * @brief 三次样条曲线插值函数
     * @param[in]  start_point      插值段起点
     * @param[in]  end_point        插值段终点
     * @param[in]  delta_s          插值间距
     * @param[out] interpolate_path 插值后路径
     * @return 返回说明：无
     */
    void CubicInterpolate2Point(const Point start_point, const Point end_point, const double delta_s, Path& interpolate_path);
    /**
     * @brief 判断当前点是否为尖点函数
     * @param[in]  n 当前点索引值
     * @return 返回说明：是尖点则返回true
     */
    inline bool IsCusp(unsigned int n);
    /**
     * @brief 判断当前点是否为固定点函数
     * @param[in]  m 当前点索引值
     * @return 返回说明：是固定点则返回true
     */
    inline bool IsFixPoint(unsigned int m);

    _VehicleParam m_vehicle_param_;


  private:
    unordered_set<unsigned int> cusp_set_;     // 存放尖点索引
    unordered_set<unsigned int> fixpoint_set_; // 存放固定点索引
    Path                        path_;         // 原路径
    Path                        new_path_;     // 优化后的路径
    std::vector<double>         s_;
    curve::spline               sx_;
    curve::spline               sy_;
    double                      kDeltaS = 0.1;
}; // end class

//} // end namespace

#endif // PATH_OPTI_H
