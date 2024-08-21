/***************************************************/
/*            Author: Fan Yang                     */
/*            Contact: allenyangfan@163.com           */
/*            Last update: 2020-04-22              */
/***************************************************/
/*
  Description: The header file for C++ class r_s_curve.
*/

// Syntax: <package name>_<type>_<file name>_H
#ifndef R_S_CURVE_FOR_H_H
#define R_S_CURVE_FOR_H_H

#include <cfloat>

#include "../../../common/common_struct.h"
#include "r_s_curve.h"
// #include "../../../os/os.h"

namespace GlobalPlanning {

using std::vector;


/**
 * @brief RS曲线规划类
 */
class RSCurve_H {
  public:
    RSCurve_H();  // 默认构造函数
    ~RSCurve_H(); // 析构函数
    void Init(_VehicleParam& vehicleparam);

    /**
     * @brief RS曲线规划类接口函数
     * @param[in] start　RS曲线起始点
     * @param[in] end　　RS曲线目标点
     * @param[in] plan_rule　　0：正常规划，没有特殊限制；1：不能倒车起步；2：必须倒车进入; 3:全程前进
     * @param[out] rs_path　规划的得到的RS曲线
     * @return 返回说明：无
     */
    bool PlanRSPath(const Point start, const Point end);

    /**
     * @brief 坐标系转换和归一化函数
     * @param[in] start　RS曲线起始点
     * @param[in] end　　RS曲线目标点
     * @param[in] radious　　车辆后轴最小转弯半径
     * @return 返回说明：无
     */
    void CoordinateTransformation(Point start, Point end, double radious);

    /**
     * @brief 生成最优RS曲线路段
     * @return 返回说明：无
     */
    bool ReedsSheppGeneration();


    /**
     * @brief CSC、CCC、CCCC、CCSC、CCSCC五种类型的Reeds-Shepp路段
     */
    inline void CSC();
    inline void CCC();
    inline void CCCC();
    inline void CCSC();
    inline void CCSCC();

    /**
     * @brief 计算辅助函数
     */
    inline double Mod2pi(double x);                                    // 使用2*pi取模
    inline void   Polar(double x, double y, double& r, double& theta); // 将笛卡尔坐标系下的点转换至极坐标下
    inline bool   Valid(double theta);                                 // 验证角度是否有效条件
    // inline bool   LengthValid();                                       // 判断生成的最优RS路径各段是否满足最小长度要求
    /**
     * @brief RS曲线各类型计算公式
     */
    inline bool                     LpSpLp(double x, double y, double phi, double& t, double& u, double& v);
    inline bool                     LpSpRp(double x, double y, double phi, double& t, double& u, double& v);
    inline bool                     LpRnLp(double x, double y, double phi, double& t, double& u, double& v);
    inline bool                     LpRnLn(double x, double y, double phi, double& t, double& u, double& v);
    inline bool                     LpRpLn(double x, double y, double phi, double& t, double& u, double& v);
    inline bool                     LpRupLumRm(double x, double y, double phi, double& t, double& u, double& v);
    inline bool                     LpRumLumRp(double x, double y, double phi, double& t, double& u, double& v);
    inline bool                     LpRmSmLm(double x, double y, double phi, double& t, double& u, double& v);
    inline bool                     LpRmSmLmBack(double x, double y, double phi, double& t, double& u, double& v);
    inline bool                     LpRmSmRmBack(double x, double y, double phi, double& t, double& u, double& v);
    inline bool                     LpRmSmRm(double x, double y, double phi, double& t, double& u, double& v);
    inline bool                     LpRmSLmRp(double x, double y, double phi, double& t, double& u, double& v);
    _VehicleParam                   m_vehicle_prarm_;
    ReedsSheppPath                  opti_rs_path; // 最优RS曲线路段
    std::shared_ptr<spdlog::logger> threadLogger_;

  private:
    Point                                     new_end; // 旋转坐标系下的终点坐标
    vector<vector<ReedsSheppPathSegmentType>> reeds_shepp_path_type_v;


    // apollo
    // const double kStepLength = 1.5;//最终rs路径点之间的间距(单位：m)
    // const double kRadious    = 2.63;//车辆后轴最小转弯半径(单位：m)
    // const double kMinimumLength = 2;//最短rs路段长度

    // 矿卡
    // const double kStepLength = 2;//最终RS路径点之间的间距(单位：m)
    // const double kRadious    = 15;//车辆后轴最小转弯半径(单位：m)
    // const double kMinimumLength = 3;//最短RS路段长度

    // 林肯车
    //  const double kStepLength = 1.5;//最终RS路径点之间的间距(单位：m)
    //  const double kRadious    = 5;//车辆后轴最小转弯半径(单位：m)
    // const double kMinimumLength = 2;//最短RS路段长度

}; // end class


} // namespace GlobalPlanning


#endif // R_S_CURVE_FOR_H_H
