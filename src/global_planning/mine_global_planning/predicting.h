#ifndef HUMAN_PATH_PREDICTING_H
#define HUMAN_PATH_PREDICTING_H
#include <random>

#include "../common/common_struct.h"
#include "../globalvariable.h"

#ifdef SKIP_HEADER
#else
#include "../map/c_map_analysis.h"
#include "../show/c_rviz_path.h"
#endif
#include <algorithm>
#include <cmath>


using namespace GlobalPlanning;
using namespace rapidjson;
struct Road {
    int                id;
    int                length; // 节点的权重
    std::vector<Road*> following_nodes;
    Road(int id, int length) : id(id), length(length) {}
};
class Predicting {
  public:
    Predicting();
    ~Predicting();
    bool                                       InitialFunction();
    bool                                       ReadAllMapFile();
    void                                       PredictingInterface(vector<vector<_TrajectoryPoint>>& path, int predicting_distance);
    PlanResult                                 PathPlanning();
    void                                       FillErrorCode(PlanResult result);
    std::vector<_SingleTraj>                   findCurrentRoad(double x, double y, double yaw, double distance_threshold);
    double                                     calculateDistance(const _TrajectoryPoint& p1, const _TrajectoryPoint& p2);
    double                                     calculateYawDifference(double yaw1, double yaw2);
    std::vector<std::vector<_TrajectoryPoint>> predictPath(double x, double y, double yaw, double distance_threshold);
    std::vector<std::vector<Road*>>            findPathsToLeafRoads(Road* startRoad, int threshold);
    void                                       dfs(Road* Current_Road, int currentWeight, int threshold, std::vector<Road*>& currentPath, std::vector<std::vector<Road*>>& allPaths);
    double                                     calculateTrajectoryLength(const std::vector<_TrajectoryPoint>& trajectory);
    std::map<int, Road*>                       buildRoadLists();
    void                                       freeRoadLists(std::vector<Road*>& road_lists_);

  public:
    _SinglePoint               start_point_;                                                                       // 起点坐标
    int                        start_key_, start_index_;                                                           // 起点匹配上的参考路径id以及在在参考路径上的具体索引
    double                     start_lat_dis_ = 0, start_lon_dis_ = 0, start_distance_ = 0, start_angle_diff_ = 0; // 起点匹配上的参考路径的横纵向距离
    map<int, _SingleTraj>      all_referencelines_;
    map<int, vector<int>>      referenceline_relation_; // 所有可供有人车行驶的参考路段
    ErrorType                  error_type_ = ErrorType::SUCCESS;
    shared_ptr<spdlog::logger> threadLogger_;
    string                     vehicle_code_;
    std::map<int, Road*>       road_map_;
    int                        predicting_distance_ = 100;
    string                     key_                 = "human_veh_predicting";


#ifdef SKIP_HEADER
#else
  private:
    CConfigureIO configio_;

  public:
    rviz_path ::CRvizPath c_rviz_; // for 显示
    tarRviz               m_tar_rviz_data_;
#endif
};
#endif // HUMAN_PATH_PREDICTING_H
