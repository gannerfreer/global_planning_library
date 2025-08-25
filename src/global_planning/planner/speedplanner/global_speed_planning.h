/* ****************************************
 * 作者: yyf(yanyifeng@wicri.org)
 * 日期: 2025/03/03
 * 内容: 完成函数功能实现,完善修改程序逻辑
 * 功能：考虑限速的(可能包含多段前进、后退路段)全局速度规划
 * ****************************************/
#ifndef GLOBAL_SPEED_PLANNING_TEST_H
#define GLOBAL_SPEED_PLANNING_TEST_H

#include <cmath>
#include <iostream>
#include <vector>

#include "../../common/common_struct.h"
#include "../../math/helper.h"
#include "../pathplanner/spline/spline.h"

using namespace GlobalPlanning;


class GlobalSpeedPlanning {
  public:
    /**
     * @brief: 构造函数
     * @return 无
     */

    GlobalSpeedPlanning() {};
    /**
     * @brief: 析构函数
     * @return 无
     */
    ~GlobalSpeedPlanning() noexcept = default;
    /**
     * @brief: 速度规划接口函数
     * @param  total_time：总时间需求；departure_time：出发时间；trajectory：规划后的路径；mode：规划模式：
     * 0：最短时间策略；1：准点策略
     * @return true：规划成功；false：规划失败
     */
    void SpeedPlanning(vector<_TrajectoryPoint>& trajectory, const _VehicleParam m_veh_param);

    void                       CalculateStation(const vector<double>& xs, const vector<double>& ys);
    void                       CalculateCubicSplineCurve(vector<_TrajectoryPoint>& points, vector<_TrajectoryPoint>& cubicspline_path);
    shared_ptr<spdlog::logger> threadLogger_;
    double                     hybridAstar_path_length_ = 0;


  private:
    /**
     * @brief: 速度曲线平滑函数
     * @param  num：trajectory_fragments中的第num条
     * @return 无
     */
    void Smooth(vector<_TrajectoryPoint>& trajectory);
    void FixLocalMininum(vector<_TrajectoryPoint>& trajectory);
    void FixLocalMaxnum(vector<_TrajectoryPoint>& trajectory);
    int  BinarySearch(int a, vector<int>& input);

    /**
     *@brief: 初始化速度规划参数
     *@param [in] m_veh_param 车辆参数
     *return
     */
    void InitSpeedParam(_VehicleParam m_veh_param);


    /* 最大加速度 单位(m/s^2) */
    float max_acceleration_;
    /* 最小加速度 单位(m/s^2) */
    float min_acceleration_;

    /* 误差项权重 */
    float speed_error_term;
    /* 平滑项权重 */
    float speed_smooth_term;

    /* 倒车速度 */
    float reverse_speed;

    _VehicleParam vehicle_param;


    void planSpeed(vector<_TrajectoryPoint>& trajectory);
    void ReplanPointMaxSpeed(vector<_TrajectoryPoint>& trajectory);

    std::vector<double> s_;
    curve::spline       sx_;
    curve::spline       sy_;
    double              kDeltaS = 0.1;
};

#endif // GLOBAL_SPEED_PLANNING_H
