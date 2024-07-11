/***************************************************/
/*            Author: Xinpeng Chen                 */
/*            Contact: *********@163.com           */
/*            Last update: 2020-11-02              */
/***************************************************/
/*
Description: The header file for C++ class collision_check.
*/

#include "../include/dubins.h"
using namespace HybridAStar;

/**
* @brief 获取dubins路径代价接口函数实现
*/
float64 Dubins :: GetDubinsCost(const Point start)
{
    vector<float64>().swap(path_len_);
    if(flag_back_)
      end_ = start;
    else
      start_ = start;
    float64 dx = end_.x - start_.x;
    float64 dy = end_.y - start_.y;
    float64 theta = mod(std :: atan2(dy,dx), twopi);

    alpha_ = mod(start_.angle - theta, twopi);
    beta_ = mod(end_.angle - theta, twopi);
    d_ = sqrt(dx * dx + dy * dy) / radius_;
    sin_alpha_ = sin(alpha_);
    cos_alpha_ = cos(alpha_);
    sin_beta_ = sin(beta_);
    cos_beta_ = cos(beta_);
    cos_alpha_m_beta_ = cos(alpha_ - beta_);
    LSL();
    LSR();
    RSL();
    RSR();
    RLR();
    LRL();
    auto min_length = *std ::min_element(path_len_.begin(),path_len_.end());
    return min_length * radius_;
}
/**
* @brief 左转－直行－左转
*/
void Dubins :: LSL()
{
    float64 p_squared = 2.0 + (d_ * d_) - (2 * cos_alpha_m_beta_) + (2 * d_ * (sin_alpha_ - sin_beta_));
    if(p_squared < 0)
        return;
    else
    {
        float64 temp0 = d_ + sin_alpha_ - sin_beta_;
        float64 temp1 = atan2((cos_beta_ - cos_alpha_), temp0);
        float64 t = mod((-alpha_ + temp1), twopi);
        float64 p = sqrt(p_squared);
        float64 q = mod((beta_ - temp1), twopi);
        float64 L = t + p + q;
        path_len_.push_back(L);
    }
}
/**
* @brief 左转－直行－右转
*/
void Dubins :: LSR()
{
    float64 p_squared = -2.0 + (d_ * d_) + (2.0 * cos_alpha_m_beta_) + (2 * d_ * (sin_alpha_ + sin_beta_));
    if(p_squared < 0)
        return;
    else
    {

        float64 p = sqrt(p_squared);
        float64 temp0 = atan2((-cos_alpha_ - cos_beta_), (d_ + sin_alpha_ + sin_beta_)) - atan2(-2.0,p);
        float64 t = mod((-alpha_ + temp0), twopi);
        float64 q = mod(-mod(beta_ , twopi) + temp0, twopi);
        float64 L = t + p + q;
        path_len_.push_back(L);
    }
}
/**
* @brief 右转－直行－左转
*/
void Dubins :: RSL()
{
    float64 p_squared = -2.0 + (d_ * d_) + (2.0 * cos_alpha_m_beta_) - (2 * d_ * (sin_alpha_ + sin_beta_));
    if(p_squared < 0)
        return;
    else
    {

        float64 p = sqrt(p_squared);
        float64 temp0 = atan2((cos_alpha_ + cos_beta_), (d_ - sin_alpha_ - sin_beta_)) - atan2(2.0,p);
        float64 t = mod((alpha_ - temp0), twopi);
        float64 q = mod((beta_ - temp0), twopi);
        float64 L = t + p + q;
        path_len_.push_back(L);
    }
}
/**
* @brief 右转－直行－右转
*/
void Dubins :: RSR()
{
    float64 p_squared = 2.0 + (d_ * d_) - (2.0 * cos_alpha_m_beta_) + (2 * d_ * (sin_beta_ - sin_alpha_));
    if(p_squared < 0)
        return;
    else
    {
        float64 temp0 = d_ - sin_alpha_ + sin_beta_;
        float64 temp1 = atan2((cos_alpha_ - cos_beta_), temp0);
        float64 t = mod((alpha_ - temp1), twopi);
        float64 p = sqrt(p_squared);
        float64 q = mod((-beta_ + temp1), twopi);
        float64 L = t + p + q;
        path_len_.push_back(L);
    }
}
/**
* @brief 右转－左转－右转
*/
void Dubins :: RLR()
{
    float64 tmp_rlr = (6.0 - (d_ * d_) + (2.0 * cos_alpha_m_beta_) + (2 * d_ * (sin_alpha_ - sin_beta_))) / 8.0;
    if(abs(tmp_rlr) > 1.0)
        return;
    else
    {
        float64 p = mod((twopi - acos(tmp_rlr)),twopi);
        float64 t = mod((alpha_ - atan2(cos_alpha_ - cos_beta_, d_ - sin_alpha_ + sin_beta_) + mod(p / 2.0, twopi)), twopi);
        float64 q = mod((alpha_ - beta_ - t + mod(p, twopi)), twopi);
        float64 L = t + p + q;
        path_len_.push_back(L);
    }
}
/**
* @brief 左转－右转－左转
*/
void Dubins :: LRL()
{
    float64 tmp_lrl = (6.0 - (d_ * d_) + (2.0 * cos_alpha_m_beta_) + (2 * d_ * (-sin_alpha_ + sin_beta_))) / 8.0;
    if(abs(tmp_lrl) > 1.0)
        return;
    else
    {
        float64 p = mod((twopi - acos(tmp_lrl)), twopi);
        float64 t = mod((-alpha_ - atan2(cos_alpha_ - cos_beta_, d_ + sin_alpha_ - sin_beta_) + p / 2.0), twopi);
        float64 q = mod((mod(beta_, twopi) - alpha_ - t + mod(p, twopi)), twopi);
        float64 L = t + p + q;
        path_len_.push_back(L);
    }
}
