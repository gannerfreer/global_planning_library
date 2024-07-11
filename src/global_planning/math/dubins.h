#ifndef DUBINS_H
#define DUBINS_H

#include"../os/os.h"
#include"general_class.h"
#include "constants.h"

#define M_PI       3.14159265358979323846

const float64 twopi = 2 * M_PI;


namespace HybridAStar
{
using std :: vector;
using namespace Constants;

class Dubins
{
public:
    Dubins(){}
    ~Dubins(){}
    vehicle_param m_vehicle_prarm_;

    void SetParam(float64 radius, Point end,PlanRule plan_rule)
    {
        radius_ = radius;
        if(PlanRule :: Backward_All_Time == plan_rule)
        {
            start_ = end;
            flag_back_ = true;
        }
        else
        {
            end_ = end;
            flag_back_ = false;
        }
    }
    /**
    * @brief 获取dubins路径代价接口函数
    * @param[in] start　起点
    * @return 返回说明：　dubins路径长度
    */
    float64 GetDubinsCost(const Point start);
private:
    /**
    * @brief 左转－直行－左转
    * @return 返回说明：　无
    */
    void LSL();
    /**
    * @brief 左转－直行－右转
    * @return 返回说明：　无
    */
    void LSR();
    /**
    * @brief 右转－直行－左转
    * @return 返回说明：　无
    */
    void RSL();
    /**
    * @brief 右转－直行－右转
    * @return 返回说明：　无
    */
    void RSR();
    /**
    * @brief 右转－左转－右转
    * @return 返回说明：　无
    */
    void RLR();
    /**
    * @brief 左转－右转－左转
    * @return 返回说明：　无
    */
    void LRL();
    /**
    * @brief 取模运算函数
    * @return 返回说明：　无
    */
    inline float64 mod(float64 a, float64 b)
    {
        return a - b * static_cast<int>(floor(a / b));
    }

private:
    bool flag_back_;
    Point start_,end_;
    float64 radius_;
    float64 alpha_,beta_,d_;
    vector<float64> path_len_;
    float64 sin_alpha_,sin_beta_,cos_alpha_,cos_beta_,cos_alpha_m_beta_;

    };

}// end namespace

#endif // DUBINS_H
