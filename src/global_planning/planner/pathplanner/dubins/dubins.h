/***************************************************/
/*            Author: Xinpeng Chen                 */
/*            Contact: *********@163.com           */
/*            Last update: 2020-11-02              */
/***************************************************/
/*
Description: The header file for C++ class Dubis.
*/

#ifndef DUBINS_H
#define DUBINS_H
#include <float.h>

#include <tuple>

#include "../../../common/common_struct.h"
#include "point.h"

const float twopi = 2 * M_PI;
namespace curve {
using std ::vector;
class Dubins {
  public:
    Dubins() {}
    ~Dubins() {}
    /**
     * @brief 获取dubins路径函数
     * @param[in] start_pose 起始位姿
     * @param[in] end_pose 目标位姿
     * @param[in] path 目标位姿
     * @return 返回说明：路径是否可行
     */
    bool GetDubinsPath(const Point start_pose, const Point end_pose, std::vector<Point>& path);

  private:
    enum DubinsPathSegmentType : unsigned char {
        L = 1,
        S = 2,
        R = 3,
    }; // 枚举路段类型
    /**
     * @brief 左转－直行－左转
     * @return 返回说明：　无
     */
    std::tuple<float, float, float> LSL();
    /**
     * @brief 左转－直行－右转
     * @return 返回说明：　无
     */
    std::tuple<float, float, float> LSR();
    /**
     * @brief 右转－直行－左转
     * @return 返回说明：　无
     */
    std::tuple<float, float, float> RSL();
    /**
     * @brief 右转－直行－右转
     * @return 返回说明：　无
     */
    std::tuple<float, float, float> RSR();
    /**
     * @brief 右转－左转－右转
     * @return 返回说明：　无
     */
    std::tuple<float, float, float> RLR();
    /**
     * @brief 左转－右转－左转
     * @return 返回说明：　无
     */
    std::tuple<float, float, float> LRL();
    /**
     * @brief 取模运算函数
     * @return 返回说明：　无
     */
    inline float mod(float a, float b) {
        return a - b * static_cast<int>(floor(a / b));
    }
    /**
     * @brief 计算下一个点函数
     * @return 返回说明：　点信息
     */
    Point CalNextPoint(float v, float x, float y, float theta, DubinsPathSegmentType type);

  private:
    const DubinsPathSegmentType dubins_path_type_[6][3] = {
        {L, S, L},
        {L, S, R},
        {R, S, L},
        {R, S, R},
        {R, L, R},
        {L, R, L}
    }; // dubins曲线的6种组成类型

    const float radius_  = 15;
    const float delta_s_ = 0.1;
    float       alpha_, beta_, d_;
    float       sin_alpha_, sin_beta_, cos_alpha_, cos_beta_, cos_alpha_m_beta_;
};

} // namespace curve

#endif
