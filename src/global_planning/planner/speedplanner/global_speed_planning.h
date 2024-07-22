/* ****************************************
 * 作者: cxp(chenxinpeng_hnu@163.com)、jh、yzy(yangzeyu@wicri.org)
 * 日期: 2020/08/21
 * 内容: 完成函数功能实现,完善修改程序逻辑
 * 功能：考虑到达时间、速度平滑性以及加速度限制，
 *       对一条不同路段赋有不同最高限速的路径
 *       (可能包含多段前进、后退路段)规划全局速度
 * ****************************************/
#ifndef GLOBAL_SPEED_PLANNING_TEST_H
#define GLOBAL_SPEED_PLANNING_TEST_H

#include <cmath>
#include <iostream>
#include <vector>

#include "../../common/common_struct.h"
// #include "../../os/os.h"

using namespace GlobalPlanning;

// namespace GlobalPlanning
//{

/**
 *@brief: 关键点结构体
 */
struct KeyPoint {
    unsigned int  index;             // 关键点所在位置索引
    float         distance;          // 路点与轨迹起点沿轨迹的距离
    unsigned char direction;         // 路点方向(0:前进，1:倒退)
    float         speed_limit_left;  // 速度上限
    float         speed_limit_right; // 速度上限
    inline void   Clear() {
        index = distance = speed_limit_left = speed_limit_right = 0;
    }
    KeyPoint() {
        this->index             = 0;
        this->distance          = 0;
        this->direction         = 0;
        this->speed_limit_left  = 0;
        this->speed_limit_right = 0;
    }
    inline void Set(unsigned int index_, float distance_, unsigned char direction_, float speed_limit_left_,
                    float speed_limit_right_) {
        index             = index_;
        distance          = distance_;
        direction         = direction_;
        speed_limit_left  = speed_limit_left_;
        speed_limit_right = speed_limit_right_;
    }
    inline void SetSpeedLimitRight(float speed_limit_right_) {
        speed_limit_right = speed_limit_right_;
    }
};

/*
 * @brief 稀疏速度点结构体
 */
struct SparseSpeedPoint {
    unsigned int index; // 该点所在位置索引
    float        speed; // 该点速度
};

/*
 * @brief 规划规则枚举
 */
enum struct SpeedPlanRule : unsigned char {
    Shortest_Time = 0, // 贴着最高速度进行规划，时间最短规则
    Set_Time      = 1, // 贴着给定的时间进行规划，准点到达
};

class GlobalSpeedPlanning {
  public:
    /**
     * @brief: 构造函数
     * @return 无
     */

    GlobalSpeedPlanning(){};
    /**
     * @brief: 析构函数
     * @return 无
     */
    ~GlobalSpeedPlanning() noexcept = default;

  private:
    /**
     * @brief: 路径划分，将全局路径按照前进、后退切换的点划分为不同的片段，分别进行速度规划
     * @return 无
     */
    bool SplitPath();

    /**
     * @brief: 获取关键点
     * @return 无
     */
    bool GetKeypoint();

    /**
     * @brief: 模式0 Shortest_Time 速度规划的主流程函数
     * @param  departure_time：出发时间
     * @return true: 规划成功；false：规划失败
     */
    bool PlanCase0(const int departure_time = 0);

    /**
     * @brief: 模式1 Set_Time 速度规划的主流程函数
     * @param  total_time：总时间需求；departure_time：出发时间
     * @return true: 规划成功；false：规划失败
     */
    bool PlanCase1(const int total_time = 0, const int departure_time = 0);

    /**
     * @brief: 梯形速度规划函数
     * @param  num：trajectory_fragments中的第num条
     * @return 无
     */
    bool TrapezoidalSpeedPlanning(unsigned char num);

    /**
     * @brief: 速度曲线平滑函数
     * @param  num：trajectory_fragments中的第num条
     * @return 无
     */
    void SpeedCurveSmooth(unsigned char num);

    /**
     * @brief: 计算当前速度曲线总用时函数
     * @return 无
     */
    float GetCurrentTotalTime();

    /**
     * @brief: 速度曲线插值函数
     * @param  num：trajectory_fragments中的第num条
     * @return 无
     */
    void SpeedCurveInterpolation(unsigned char num);

    /**
     * @brief: 获取时间信息函数
     * @param  start_time 开始发车时间
     * @return 每个路点对应时间
     */
    void AddTimeInformation(const int& start_time);

    /**
     * @brief 按比例减小各段限速大小
     * @param [in] delta_speed：每次减小的量
     * @param [return]
     */
    void ReducedMaximumSpeedAve(float delta_speed);

    /**
     * @brief 减小速度最大的一段的限速
     * @param [in]
     * @param [return]
     */
    void ReducedMaximumSpeed();

    /**
     * @brief 对不合理的key_points进行调整，主要是针对一些减速都无法达到末端速度要求的路段
     * @param [in]
     * @param [return]
     */
    bool AdpKeyPoints();
    bool KeyPointsDecelerationCheck();

    /**
     * @brief 对单个路段进行速度规划
     * @param [in]
     * num：trajectory_fragments中的第num条；keypoint1、keypoint2：该路段的两个关键点；temp_sparsespeedpoints：规划后的速度点；last_speed：规划后的末速度
     * @param [return]
     */
    bool PlanForSingleSegment(unsigned char num, KeyPoint keypoint1, KeyPoint keypoint2,
                              vector<SparseSpeedPoint>& temp_sparsespeedpoints, float& last_speed);

    /**
     *@brief: 初始化速度规划参数
     *@param [in] m_veh_param 车辆参数
     *return
     */
    void InitSpeedParam(_VehicleParam m_veh_param);
    /**
     * @brief: 删除左右速度一样的关键点
     * @param [in]    vector<KeyPoint> m_keypoints
     * @return {*}
     */
    void Deletekeypoints(vector<KeyPoint>& m_keypoints);

    /* 需规划速度的全局路径 */
    vector<_TrajectoryPoint> trajectory_points;
    /*根据前进、后退截断后的全局路径*/
    vector<vector<_TrajectoryPoint>> trajectory_fragments;
    /* 关键点 */
    vector<vector<KeyPoint>> key_points;
    /* 梯形规划出的速度 */
    vector<vector<SparseSpeedPoint>> global_speeds;
    /* 优化后的速度 */
    vector<vector<SparseSpeedPoint>> opti_global_speeds;
    /* 规划速度之后的全局路径 */
    vector<_TrajectoryPoint> final_trajectory_points;
    /* 最大速度、初始速度、最终速度 */
    float max_speed_, initial_speed_, final_speed_;
    //        /* 最大加速度 单位(m/s^2) */
    //        const float  kMaxAcceleration;
    //        /* 最小加速度 单位(m/s^2) */
    //        const float  kMinAcceleration;
    //        /* 速度增量   单位(m/s) */
    //        const float  kDeltaSpeed;
    //        /* 误差项权重 */
    //        const float  kErrorTerm;
    //        /* 平滑项权重 */
    //        const float  kSmoothnessTerm;
    //        /* 离散点间隔数量 */
    //        const float  kDiscreteNumber;
    //        /* 倒车速度 */
    //        const float reverse_speed;
    /* 最大加速度 单位(m/s^2) */
    float kMaxAcceleration;
    /* 最小加速度 单位(m/s^2) */
    float kMinAcceleration;
    /* 速度增量   单位(m/s) */
    float kDeltaSpeed;
    /* 误差项权重 */
    float kErrorTerm;
    /* 平滑项权重 */
    float kSmoothnessTerm;
    /* 离散点间隔数量 */
    float kDiscreteNumber;
    /* 倒车速度 */
    float reverse_speed;
    /*插值间隔*/
    float         delta_s;
    _VehicleParam vehicle_param;

  public:
    /**
     * @brief: 速度规划接口函数
     * @param  total_time：总时间需求；departure_time：出发时间；trajectory：规划后的路径；mode：规划模式：
     * 0：最短时间策略；1：准点策略
     * @return true：规划成功；false：规划失败
     */
    bool SpeedPlanning(vector<_TrajectoryPoint>& trajectory, const _VehicleParam m_veh_param, const int total_time = 0,
                       const int departure_time = 0, unsigned char mode = 0);


    void ReplanPointMaxSpeed();

  public:
    shared_ptr<spdlog::logger> threadLogger_;
};

//}

#endif // GLOBAL_SPEED_PLANNING_H
