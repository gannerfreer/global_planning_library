#ifndef GLOBAL_PLANNING_PLANNING_H
#define GLOBAL_PLANNING_PLANNING_H
#include <random>

#include "../collision_check/collision_check.h"
#include "../common/common_struct.h"
#include "../globalvariable.h"
#include "../planner/pathplanner/dijkstra/dijkstra.h"
#include "../planner/pathplanner/hybirdastar/optimal_path.h"
#include "../planner/speedplanner/global_speed_planning.h"
#ifdef SKIP_HEADER
#else
#include "../map/c_map_analysis.h"
#include "../show/c_rviz_path.h"
#endif
#include <algorithm>

#include "../planner/pathplanner/dubins/dubins.h"
#include "../planner/pathplanner/dubins/point.h"
#include "../planner/pathplanner/spline/spline.h"
using namespace GlobalPlanning;
// using namespace HybridAStar;
using namespace rapidjson;
class Planning {
  public:
    Planning();
    ~Planning();

    /**
     * @brief 类初始化函数，进行地图文件读取，相关参数初始化
     * @param [in] 无
     * @param [return] true：初始化成功，false：初始化失败
     */
    bool InitialFunction();


    /**
     * @brief 调用hibrid A star算法进行路径规划的接口函数
     * @param [in] s_point：起始点坐标，e_point：目标点坐标，区域id, 返回路径，规划规则
     * @param [return] true：成功；false：失败
     */
    bool ApplyHibridAStar(_SinglePoint s_point, _SinglePoint e_point, vector<_TrajectoryPoint>& traj, int plan_rule_id);


    PlanResult ProgressiveHybirdAStar(_SinglePoint& input_point, int& search_index, vector<_TrajectoryPoint>& result_trajectory, const PlanRule& rule_id, int max_search_index, double start_point_offset_distance, vector<_TrajectoryPoint>& input_path);
    /**
     * @brief
     *
     * @param s_point 起点
     * @param e_point 终点
     * @param temp_zone_id 搜索区域
     * @param traj 输出轨迹
     * @param plan_rule_id 规划规则
     * @param time_threshold 搜索允许最大时间
     * @return true 规划成功
     * @return false 失败
     */
    PlanResult ApplyHibridAStarWithTime(_SinglePoint s_point, _SinglePoint e_point, vector<_TrajectoryPoint>& traj, const PlanRule& plan_rule_id, long long time_threshold);


    /**
     * @brief 均匀碾压，每个路径点偏移权重
     *
     * @param k 待偏移路径点索引
     * @param sum 待偏移路径点所在路径路径点总数
     * @return float 该路径点权重偏移系数
     */
    float WeightFunction(int k, int sum);
    /**
     * @brief 均匀碾压，计算每个点的偏移量
     *
     * @param index 输入点在路径上的索引
     * @param sum 输入点所在路径路径点总数
     * @param weight 偏移权重
     * @return float 偏移量
     */
    float CalculateOffSetWithoutCuravture(int index, int sum, float weight);


    /**
     * @brief 供本地rivz仿真使用，读取本地地图
     *
     * @return true
     * @return false
     */
    bool ReadAllMapFile();


    /**
     * @brief
     *
     * @param path 封装在全局函数中的规划库接口函数
     */
    void GlobalPathPlanningInterface(vector<_TrajectoryPoint>& path);
    /**
     * @brief
     *
     * @param start
     * @param end
     * @return true
     * @return false
     */
    bool IsConnect(int start, int end);


    /**
     * @brief
     *
     */
    PlanResult PathPlanning();

    /**
     * @brief
     *
     */
    PlanResult           HybirdAStarFitting();
    void                 StartEndPointProcess();
    bool                 PathOffset();
    PlanResult           NotFollowReferencelinePlanning();
    PlanResult           FollowReferencelinePlanning();
    void                 PathClipAndSplice();
    bool                 JudgeFittingDirection(vector<_TrajectoryPoint>& input_path);
    bool                 IsShortDistance();
    bool                 HasSearched(int start, int end);
    bool                 PoseVerificationInterface(const _SinglePoint& start_pose, const _SinglePoint& end_pose, const bool flag, const int L, std::vector<curve::Point>& output_path);
    void                 CurvatureCal(vector<_TrajectoryPoint>& input_path);
    void                 SmoothPath(vector<_TrajectoryPoint>& input_path);
    void                 FillErrorCode(PlanResult result);
    vector<unsigned int> CurvatureCheck(vector<_TrajectoryPoint>& input_path);
    PlanResult           IsPath3Success(vector<_TrajectoryPoint>& input_path);
    PlanResult           IsPath2Success(vector<_TrajectoryPoint>& input_path);
    PlanResult           IsPath1Success(vector<_TrajectoryPoint>& input_path);
    PlanResult           IsPath4Success(vector<_TrajectoryPoint>& input_path);
    bool                 IsForwardAndBackwardReferencePath();
    // 检查全局路径是否与所有地图边界发生碰撞
    bool IsGlobalPathCollision();
    PlanResult CheckStartPointAndEndPoint();
  public:
    _SinglePoint start_point_,
        end_point_;                                                                                                                                                        // 起、终点坐标
    int    start_key_, end_key_, start_index_, end_index_;                                                                                                                 // 起点、终点匹配上的参考路径id以及在在参考路径上的具体索引
    double start_lat_dis_ = 0, start_lon_dis_ = 0, start_distance_ = 0, start_angle_diff_ = 0, end_lat_dis_ = 0, end_lon_dis_ = 0, end_distance_ = 0, end_angle_diff_ = 0; // 起点、终点与匹配上的参考路径的横纵向距离

    vector<vector<double>>       road_directed_graph_; // 路段有向图
    vector<_BorderPoint>         map_border_;          // 地图外边界
    vector<vector<_BorderPoint>> machine_borders_;     // 挖掘机边界
    vector<vector<_BorderPoint>> wall_borders_;        // 动态挡墙边界
    map<int, _SingleTraj>        all_referencelines_;  // 所有可供无人车行使的参考路段
    vector<_TrajectoryPoint>     global_path_;         // 全局路径
    vector<vector<_TrajectoryPoint>> all_possible_global_paths_; // 合理的全局路径
    vector<int>                  road_sequence_;       // 路段拓扑结果
    vector<int>                  sequence_mapping_;    // 序列映射关系

    Dijkstra               dijkstra_;        // dijkstra对象
    OptimalPath            my_optimal_path_; // hibrid A star类的实例对象
    GlobalSpeedPlanning    my_speed_planning_;
    CollisonCheck          collison_check_;
    _VehicleParam          vehicle_param_; // 传入的车辆参数以及算法参数
    TaskType               task_type_;     // 任务类型 用于终点处规划，规划方案选型
    unsigned char          light_or_heavy_;
    vector<pair<int, int>> v_has_calculate_pair_;

    ErrorType                        error_type_ = ErrorType::SUCCESS;
    shared_ptr<spdlog::logger>       threadLogger_;
    string                           vehicle_code_;
    string                           key_;
    double                           hybridAstar_path_length_ = 0;
    vector<vector<_TrajectoryPoint>> reference_paths_; // 后台下发的要求拟合的参考路径
    Timer                            planning_timer_;

#ifdef SKIP_HEADER
#else
  private:
    CConfigureIO configio_;

  public:
    rviz_path ::CRvizPath c_rviz_; // for 显示
    tarRviz               m_tar_rviz_data_;
#endif
};
#endif // GLOBAL_PLANNING_PLANNING_H
