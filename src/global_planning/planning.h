#ifndef GLOBAL_PLANNING_PLANNING_H
#define GLOBAL_PLANNING_PLANNING_H
#include "interface/interface.h"

using namespace GlobalPlanning;
class Planning
{
public:
    Planning();
    ~Planning();

    // /**
    //  * @brief 类初始化函数，进行地图文件读取，相关参数初始化
    //  * @param [in] 无
    //  * @param [return] true：初始化成功，false：初始化失败
    //  */
    // bool InitialFunction();
    // /**
    //  * @brief 读取所有的地图文件，将对应的内容存到all_zones_、road_Directed_Graph中
    //  * @param [in] 无
    //  * @param [return] bool true：读取成功；false：读取失败；
    //  */

    // /**
    //  * @brief 找到几个路径中离点point最近的参考路径
    //  * @param [in] 点坐标，路径的容器，最近点id(引用)，路径id(引用)
    //  * @param [return] true：成功；false：失败
    //  */
    // ErrorType FindReferencePath(Single_Point point, std ::vector<Single_Trajectory> &trajs, int32 &nearest_id, int &path_id, bool flag, map<int, double> &v_id, double search_distance);
    // /**
    //  * @brief 找到最近点id
    //  * @param [in] 点坐标，路径，最近距离(引用)，最近点id(引用)
    //  * @param [return] true：成功；false：失败
    //  */
    // bool FindNearestPoint(Single_Point point, Single_Trajectory traj, float32 &distance, int32 &nearest_id);

    // /**
    //  * @brief 计算路径的位移信息
    //  * @param [in]  temp_path
    //  * 返回 temp_path 中的位移信息
    //  */
    // void CalDistance(vector<Trajectory_Point> &temp_path);

    // /**
    //  * @brief 计算路径的曲率信息
    //  * @param [in]  temp_path
    //  * 返回 temp_path 中的曲率信息
    //  */
    // void CalCurv(vector<Trajectory_Point> &temp_path);

    // /**
    //  * @brief 设置非结构化得到路径的限速（设置为区域限速），倒车的限速设置在全局速度规划模块有处理
    //  * @param [in] temp_path：需设置的路径； max_speed：最大速度
    //  * @param [return]
    //  */
    // void SetMaxSpeed(vector<Trajectory_Point> &temp_path, float32 max_speed);

    // /**
    //  * @brief: 将角度换算成-pi~pi
    //  * @param angle:传入角度值
    //  * @return 无
    //  */
    // inline void Mod2Pi(float32 &angle)
    // {
    //     double angle_t = fmod(angle, 2. * M_PI);
    //     if (angle_t < -M_PI)
    //         angle_t += 2. * M_PI;
    //     else if (angle_t > M_PI)
    //         angle_t -= 2. * M_PI;
    //     angle = angle_t;
    // }

    // /**
    //  * @brief: 实现matlab-mod函数 取余
    //  * @param x:传入除数
    //  * @param y:传入被除数
    //  * @return 实现结果
    //  */
    // inline double mod(double x, double y)
    // {
    //     int32 c = floor(x / y);
    //     double d = x - c * y;
    //     return d;
    // }

    // /**
    //  * @brief 调用hibrid A star算法进行路径规划的接口函数
    //  * @param [in] s_point：起始点坐标，e_point：目标点坐标，区域id, 返回路径，规划规则
    //  * @param [return] true：成功；false：失败
    //  */
    // bool ApplyHibridAStar(Single_Point s_point,
    //                       Single_Point e_point,
    //                       int temp_zone_id,
    //                       std ::vector<Trajectory_Point> &traj,
    //                       int plan_rule_id);
    // /**
    //  * @brief
    //  *
    //  * @param s_point  起点坐标
    //  * @param e_point  目标点坐标
    //  * @param all_area  起点到终点的拓扑区域联通
    //  * @param traj 返回路径
    //  * @param plan_rule_id 规划规则
    //  * @return true
    //  * @return false
    //  */
    // bool ApplyHibridAStar(Single_Point s_point,
    //                       Single_Point e_point,
    //                       vector<int> all_area,
    //                       std ::vector<Trajectory_Point> &traj,
    //                       int plan_rule_id);

    /**
     *@brief: 解析传入的全局规划起终点位姿信息
     *@param
     *return
     */
    _TarStartEnd ParseInputInfo(char *str);

    /**
     *@brief: 传出规划完成的全局轨迹json格式信息
     *@param
     *return
     */
    string VecWaypoint2json(vector<_TrajectoryPoint> &vec_wp);

    // /**
    //  * @brief: 弧度转角度
    //  * @param {vector <Trajectory_Point>} &temp_path
    //  * @return {*}
    //  */
    // void Calrad2deg(vector<Trajectory_Point> &temp_path);
    // /**
    //  * @brief: 对路点进行重新限速
    //  * @param {vector <Trajectory_Point>} &temp_path
    //  * @return {*}
    //  */
    // void ReplanPointMaxSpeed(vector<Trajectory_Point> &temp_path);

    // /**
    //  *@brief: 将装卸载点附近边界属性转换(是否可跨越)
    //  *@param [msg_obj_fuse] obj_fuse
    //  *return
    //  */
    // void ChangeBorderType(Single_Point &point);
    // /**
    //  *@brief: 计算当前点距离区域边界点的最近距离
    //  *@param [Single_Point] point, [Single_Border] border_points
    //  *return
    //  */
    // float32 CalNearestDistance(Single_Point point, Single_Border border_points);

    // /**
    //  * @brief
    //  *
    //  * @param input_point 起始点
    //  * @param input_node 起始点所在的区域ID
    //  * @param search_direction 搜索方向[1:正向搜索   0：反向搜索]
    //  * @param input_trajectory 待采样的轨迹
    //  * @param search_start input_point匹配点索引
    //  * @param search_index HybirdA*成功拟合处索引
    //  * @param result_trajectory HybirdA*输出轨迹
    //  * @param rule_id HybirdA*搜索规则
    //  * @return true
    //  * @return false
    //  */
    // bool ProgressiveHybirdAStar(Single_Point &input_point, int input_node, bool search_direction, vector<Trajectory_Point> &input_trajectory, int32 search_start, int32 &search_index, vector<Trajectory_Point> &result_trajectory, int rule_id);
    // /**
    //  * @brief
    //  *
    //  * @param s_point 起点
    //  * @param e_point 终点
    //  * @param temp_zone_id 搜索区域
    //  * @param traj 输出轨迹
    //  * @param plan_rule_id 规划规则
    //  * @param time_threshold 搜索允许最大时间
    //  * @return true 规划成功
    //  * @return false 失败
    //  */
    // bool ApplyHibridAStarWithTime(Single_Point s_point,
    //                               Single_Point e_point,
    //                               int temp_zone_id,
    //                               std ::vector<Trajectory_Point> &traj,
    //                               int plan_rule_id,
    //                               int64 time_threshold);
    // /**
    //  * @brief  判断输入点是否需要进行hybirdA*拟合
    //  *
    //  * @param input_point 待判断点
    //  * @param traj 待拟合参考路径
    //  * @param nearest_point_index 最近点索引
    //  * @param lat_distance_ 输入点与最近点横向距离
    //  * @return true 需要进行拟合
    //  * @return false 不需要进行拟合
    //  */
    // bool DetermineIfOrNoHybirdAStar(Single_Point &input_point, vector<Trajectory_Point> &traj, int32 nearest_point_index, float &lat_distance_);
    // /**
    //  * @brief  去除轨迹中重复点
    //  *
    //  * @param input 输入轨迹
    //  * @param result 删除重复点后的输出轨迹
    //  * @return true
    //  * @return false
    //  */
    // bool removeDuplicates(std ::vector<Trajectory_Point> &input, vector<Trajectory_Point> &result);
    // /**
    //  * @brief 均匀碾压，每个路径点偏移权重
    //  *
    //  * @param k 待偏移路径点索引
    //  * @param sum 待偏移路径点所在路径路径点总数
    //  * @return float 该路径点权重偏移系数
    //  */
    // float WeightFunction(int k, int sum);
    // /**
    //  * @brief 均匀碾压，计算每个点的偏移量
    //  *
    //  * @param index 输入点在路径上的索引
    //  * @param sum 输入点所在路径路径点总数
    //  * @param weight 偏移权重
    //  * @return float 偏移量
    //  */
    // float CalculateOffSetWithoutCuravture(int index, int sum, float weight);
    // /**
    //  * @brief 均匀碾压
    //  *
    //  * @param path 输入路径
    //  * @return 偏移后的输出路径
    //  */
    // std ::vector<Trajectory_Point> RandomOffsetWithoutCuravture(std ::vector<Trajectory_Point> &path);
    // /**
    //  * @brief 基于车辆几何尺寸，检查Path是否碰撞
    //  *
    //  * @param Path 待检测路径
    //  * @return true 碰撞
    //  * @return false 不碰撞
    //  */
    // bool PathCollisionCheck(vector<Trajectory_Point> Path);
    // /**
    //  * @brief 三次多项式差值功能内部子函数，基于xs和ys算累计距离s
    //  *
    //  * @param xs
    //  * @param ys
    //  */
    // void CalculateStation(const vector<double> &xs, const vector<double> &ys);
    // /**
    //  * @brief 基于三次样条差值函数
    //  *
    //  * @param points 离散插值点
    //  * @param cubicspline_path 插值后的路径，默认10cm
    //  */
    // void CalculateCubicSplineCurve(const vector<Trajectory_Point> points, vector<Trajectory_Point> &cubicspline_path);
    // /**
    //  * @brief 均匀碾压子功能 对偏移后的路径曲率进行校验
    //  *
    //  * @param tra 待校验路径
    //  * @return true 校验通过
    //  * @return false
    //  */
    // bool CheckCurvature(vector<Trajectory_Point> &tra);
    // /**
    //  * @brief 供本地rivz仿真使用，读取本地地图
    //  *
    //  * @return true
    //  * @return false
    //  */
    // bool ReadAllMapFile();
    // /**
    //  * @brief 计算轨迹每个轨迹点加速度
    //  *
    //  * @param temp_path
    //  */
    // void CalAcc(vector<Trajectory_Point> &temp_path);
    // /**
    //  * @brief 判断轨迹是否绕圈
    //  *
    //  * @param path
    //  * @return true 绕圈
    //  * @return false 不绕圈
    //  */
    // bool doesTrajectorySelfIntersect(Path &path);
    // /**
    //  * @brief 核查轨迹是否断裂
    //  *
    //  * @param input_path
    //  * @return true 断裂
    //  * @return false
    //  */
    // bool checkPathFracture(vector<Trajectory_Point> &input_path);
    // /**
    //  * @brief 给定point，判断traj是否处于search_distance范围内
    //  *
    //  * @param point
    //  * @param traj
    //  * @param search_distance
    //  * @param lat_dis point与traj最近点横向距离
    //  * @return true 位于
    //  * @return false 不位于
    //  */
    // bool FindSuitableReferenceLine(Single_Point point, Single_Trajectory traj, double search_distance, double lat_dis);
    // /**
    //  * @brief 超速检测
    //  *
    //  * @param input_path
    //  * @return true
    //  * @return false
    //  */
    // bool OverSpeedCheck(vector<Trajectory_Point> &input_path);

    /**
     * @brief
     *
     * @param path 封装在全局函数中的规划库接口函数
     */
    void GlobalPathPlanningIntface(vector<_TrajectoryPoint> &path);

public:
    _SinglePoint start_point_, end_point_; // 起、终点坐标

    vector<vector<double>> road_directed_graph_; // 路段有向图
    vector<_BorderPoint> map_border_;            // 地图外边界
    vector<vector<_BorderPoint>> inner_borders_; // 内边界
    vector<_SingleTraj> all_referencelines_;     // 所有路段
    std ::vector<_TrajectoryPoint> global_path_; // 全局路径

    // Dijkstra dijkstra_;                          // dijkstra对象
    // HybridAStar::OptimalPath my_optimal_path_;   // hibrid A star类的实例对象
    // GlobalSpeedPlanning my_speed_planning_;
    // std ::vector<int> zone_sequence_;          // dijkstra 算法得到的全局路径依次经过的区域id
    _VehicleParam vehicle_param_; // 传入的车辆参数以及算法参数
    // double vehicle_commander_;                  // 车长
    int task_type_; // 任务类型 用于终点处规划，规划方案选型
    // bool end_point_out_border_;                  // 终点是否在边界外
    // int last_task_type_;                        // 上一次任务类型
    // bool start_point_out_border_;                // 终点是否在边界外
    // CollisonCheck collison_check_;
    // vector<double> s_;
    // spline sx_;
    // spline sy_;
    // double kDeltaS_ = 0.1;
    int error_type_ = 0;
    shared_ptr<spdlog::logger> threadLogger_;
    // vector<int> vec_path_;
    string vehicle_code_;
    string key_;
    // bool reverse_flag_;
#ifdef SKIP_HEADER
#else
private:
    CConfigureIO configio_;

public:
    rviz_path ::CRvizPath c_rviz_; // for 显示
    tarRviz m_tar_rviz_data_;
#endif
};
#endif // GLOBAL_PLANNING_PLANNING_H
