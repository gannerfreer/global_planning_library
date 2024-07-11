#ifndef SHENYAN_H
#define SHENYAN_H

// #include "shenyan_global.h"

#include <random>
#include <ctime>
// Include system lib.
// #include <iostream>
// #include <fstream>
// #include <cmath>
// #include <vector>
// #include <map>
// #include <string>
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include "../rapidjson/rapidjson.h"

// Include personal lib.
#include "../include/my_typedef.h"
#include "../include/dijkstra.h"
// #include "common_struct.h"
// #include "global_speed_planning.h"
// #include "general_class.h"
// #include "optimal_path.h"
#include "../include/c_conf_struct.h"
#include "../include/collision_check.h"
#include "../include/spline.h"
// #include <boost/filesystem.hpp>
#include <filesystem>
#include <thread>
// #include "../common/c_common.h"
#include "common_struct.h"
#include "optimal_path.h"
#include "global_speed_planning_test.h"
#ifdef SKIP_HEADER
#else
#include "c_rviz_path.h"
#include "c_map_analysis.h"
#endif

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

using rapidjson::Value;
using namespace GlobalPlanning;
using namespace HybridAStar;
using namespace curve;
using namespace std;

#define INF 0x7fffffff
extern "C"
{
    class Shenyan
    {

    public:
        Shenyan();
        ~Shenyan();

        /**
         * @brief 类初始化函数，进行地图文件读取，相关参数初始化
         * @param [in] 无
         * @param [return] true：初始化成功，false：初始化失败
         */
        bool InitialFunction();
        /**
         * @brief 读取所有的地图文件，将对应的内容存到all_zones_、road_Directed_Graph中
         * @param [in] 无
         * @param [return] bool true：读取成功；false：读取失败；
         */

        /**
         * @brief 起始点和终止点在同一区域，且该区域为结构化道路
         * @param [in] 无
         * @param [return] true: 规划成功；false：规划失败
         */
        ErrorType PlanningCase1();

        /**
         * @brief 起始点和终止点在同一区域，且该区域为非结构化道路
         * @param [in] 无
         * @param [return] true: 规划成功；false：规划失败
         */
        ErrorType PlanningCase2();

        /**
         * @brief 起始点和终止点不在同一区域，且起点、终点为结构化道路
         * @param [in] 无
         * @param [return] true: 规划成功；false：规划失败
         */
        ErrorType PlanningCase3();

        /**
         * @brief 起始点和终止点不在同一区域，且起点为结构化道路、终点为非结构化道路
         * @param [in] 无
         * @param [return] true: 规划成功；false：规划失败
         */
        ErrorType PlanningCase4();

        /**
         * @brief 起始点和终止点不在同一区域，且起点为非结构化道路、终点为结构化道路
         * @param [in] 无
         * @param [return] true: 规划成功；false：规划失败
         */
        ErrorType PlanningCase5();

        /**
         * @brief 起始点和终止点不在同一区域，且起点、终点为非结构化道路
         * @param [in] 无
         * @param [return] true: 规划成功；false：规划失败
         */
        ErrorType PlanningCase6();

        /**
         * @brief 找到点所在的区域的id号，并获取区域类型
         * @param [in] point：起始点/目标点；zone_type：区域类型
         * @param [return] 点所在区域id号
         */
        uint8 FindZoneId(Single_Point point, uint8 &zone_type);

        /**
         * @brief 判断点是否在给定的区域边界
         * @param [in] 点，区域边界点集
         * @param [return] true：在该边界内部；false：在该边界外部
         */
        bool PointInZone(Single_Point point, Single_Border border);

        /**
         * @brief 找到几个路径中离点point最近的参考路径
         * @param [in] 点坐标，路径的容器，最近点id(引用)，路径id(引用)
         * @param [return] true：成功；false：失败
         */
        ErrorType FindReferencePath(Single_Point point, std ::vector<Single_Trajectory> &trajs, uint32 &nearest_id, uint8 &path_id, bool flag, map<uint8, double> &v_id, double search_distance);
        /**
         * @brief 找到最近点id
         * @param [in] 点坐标，路径，最近距离(引用)，最近点id(引用)
         * @param [return] true：成功；false：失败
         */
        bool FindNearestPoint(Single_Point point, Single_Trajectory traj, float32 &distance, uint32 &nearest_id);

        /**
         * @brief 根据起始区域、经过区域、到达区域找到路径id
         * @param [in] 起始区域id，经过区域id，到达区域id，路径的容器，路径id(引用)
         * @param [return] true：成功；false：失败
         */
        bool FindPathId(uint8 s_id, uint8 c_id, uint8 e_id, std ::vector<Single_Trajectory> &trajs, uint8 &path_id);

        /**
         * @brief 路径的线性插值
         * @param [in]  temp_path
         * 返回
         */
        void Path_Interpolation_Linear(std::vector<Trajectory_Point> global_path, std::vector<Trajectory_Point> &temp_path);

        /**
         * @brief 路径的三次曲线插值
         * @param [in]  temp_path
         * 返回 无
         */
        void Path_Interpolation(std::vector<Trajectory_Point> global_path, std::vector<Trajectory_Point> &temp_path);

        /**
         * @brief 计算路径的位移信息
         * @param [in]  temp_path
         * 返回 temp_path 中的位移信息
         */
        void CalDistance(std::vector<Trajectory_Point> &temp_path);

        /**
         * @brief 计算路径的曲率信息
         * @param [in]  temp_path
         * 返回 temp_path 中的曲率信息
         */
        void CalCurv(std::vector<Trajectory_Point> &temp_path);

        /**
         * @brief 两个点之间的三次样条曲线插值
         * @param [in] 无
         * @param [return] 无
         */
        void Interpolate(float64 x0, float64 y0, float32 theta0,
                         float64 x1, float64 y1, float32 theta1,
                         std::vector<Trajectory_Point> &path);

        /**
         * @brief 设置非结构化得到路径的限速（设置为区域限速），倒车的限速设置在全局速度规划模块有处理
         * @param [in] temp_path：需设置的路径； max_speed：最大速度
         * @param [return]
         */
        void SetMaxSpeed(std::vector<Trajectory_Point> &temp_path, float32 max_speed);

        /**
         * @brief: 实现符号函数sign
         * @param x:传入值
         * @return 返回结果
         */
        inline int32 siG(float64 x)
        {
            if (x < 0)
                return -1;
            else if (x == 0)
                return 0;
            else
                return 1;
        }

        /**
         * @brief: 将角度换算成-pi~pi
         * @param angle:传入角度值
         * @return 无
         */
        inline void Mod2Pi(float32 &angle)
        {
            float64 angle_t = fmod(angle, 2. * M_PI);
            if (angle_t < -M_PI)
                angle_t += 2. * M_PI;
            else if (angle_t > M_PI)
                angle_t -= 2. * M_PI;
            angle = angle_t;
        }

        /**
         * @brief: 实现matlab-mod函数 取余
         * @param x:传入除数
         * @param y:传入被除数
         * @return 实现结果
         */
        inline float64 mod(float64 x, float64 y)
        {
            int32 c = floor(x / y);
            float64 d = x - c * y;
            return d;
        }

        /**
         * @brief 调用hibrid A star算法进行路径规划的接口函数
         * @param [in] s_point：起始点坐标，e_point：目标点坐标，区域id, 返回路径，规划规则
         * @param [return] true：成功；false：失败
         */
        bool ApplyHibridAStar(Single_Point s_point,
                              Single_Point e_point,
                              uint8 temp_zone_id,
                              std ::vector<Trajectory_Point> &traj,
                              uint8 plan_rule_id);
        /**
         * @brief
         *
         * @param s_point  起点坐标
         * @param e_point  目标点坐标
         * @param all_area  起点到终点的拓扑区域联通
         * @param traj 返回路径
         * @param plan_rule_id 规划规则
         * @return true
         * @return false
         */
        bool ApplyHibridAStar(Single_Point s_point,
                              Single_Point e_point,
                              vector<uint8> all_area,
                              std ::vector<Trajectory_Point> &traj,
                              uint8 plan_rule_id);

        /**
         *@brief: 解析传入的全局规划起终点位姿信息
         *@param
         *return
         */
        tar_start_end ParseInputInfo(char *str);

        /**
         *@brief: 传出规划完成的全局轨迹json格式信息
         *@param
         *return
         */
        string VecWaypoint2json(ReferenceTrajectory &vec_wp);

        /**
         * @brief: 弧度转角度
         * @param {vector <Trajectory_Point>} &temp_path
         * @return {*}
         */
        void Calrad2deg(std::vector<Trajectory_Point> &temp_path);
        /**
         * @brief: 对路点进行重新限速
         * @param {vector <Trajectory_Point>} &temp_path
         * @return {*}
         */
        void ReplanPointMaxSpeed(std::vector<Trajectory_Point> &temp_path);

        /**
         *@brief: 将装卸载点附近边界属性转换(是否可跨越)
         *@param [msg_obj_fuse] obj_fuse
         *return
         */
        void ChangeBorderType(Single_Point &point);
        /**
         *@brief: 计算当前点距离区域边界点的最近距离
         *@param [Single_Point] point, [Single_Border] border_points
         *return
         */
        float32 CalNearestDistance(Single_Point point, Single_Border border_points);

        /**
         * @brief
         *
         * @param input_point 起始点
         * @param input_node 起始点所在的区域ID
         * @param search_direction 搜索方向[1:正向搜索   0：反向搜索]
         * @param input_trajectory 待采样的轨迹
         * @param search_start input_point匹配点索引
         * @param search_index HybirdA*成功拟合处索引
         * @param result_trajectory HybirdA*输出轨迹
         * @param rule_id HybirdA*搜索规则
         * @return true
         * @return false
         */
        bool ProgressiveHybirdAStar(Single_Point &input_point, uint8 input_node, bool search_direction, std::vector<Trajectory_Point> &input_trajectory, uint32 search_start, int32 &search_index, std::vector<Trajectory_Point> &result_trajectory, uint8 rule_id);
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
        bool ApplyHibridAStarWithTime(Single_Point s_point,
                                      Single_Point e_point,
                                      uint8 temp_zone_id,
                                      std ::vector<Trajectory_Point> &traj,
                                      uint8 plan_rule_id,
                                      int64 time_threshold);
        /**
         * @brief  判断输入点是否需要进行hybirdA*拟合
         *
         * @param input_point 待判断点
         * @param traj 待拟合参考路径
         * @param nearest_point_index 最近点索引
         * @param lat_distance_ 输入点与最近点横向距离
         * @return true 需要进行拟合
         * @return false 不需要进行拟合
         */
        bool DetermineIfOrNoHybirdAStar(Single_Point &input_point, std::vector<Trajectory_Point> &traj, uint32 nearest_point_index, float &lat_distance_);
        /**
         * @brief  去除轨迹中重复点
         *
         * @param input 输入轨迹
         * @param result 删除重复点后的输出轨迹
         * @return true
         * @return false
         */
        bool removeDuplicates(std ::vector<Trajectory_Point> &input, std::vector<Trajectory_Point> &result);
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
         * @brief 均匀碾压
         *
         * @param path 输入路径
         * @return 偏移后的输出路径
         */
        std ::vector<Trajectory_Point> RandomOffsetWithoutCuravture(std ::vector<Trajectory_Point> &path);
        /**
         * @brief 基于车辆几何尺寸，检查Path是否碰撞
         *
         * @param Path 待检测路径
         * @return true 碰撞
         * @return false 不碰撞
         */
        bool PathCollisionCheck(std::vector<Trajectory_Point> Path);
        /**
         * @brief 三次多项式差值功能内部子函数，基于xs和ys算累计距离s
         *
         * @param xs
         * @param ys
         */
        void CalculateStation(const std::vector<float64> &xs, const std::vector<float64> &ys);
        /**
         * @brief 基于三次样条差值函数
         *
         * @param points 离散插值点
         * @param cubicspline_path 插值后的路径，默认10cm
         */
        void CalculateCubicSplineCurve(const std::vector<Trajectory_Point> points, std::vector<Trajectory_Point> &cubicspline_path);
        /**
         * @brief 均匀碾压子功能 对偏移后的路径曲率进行校验
         *
         * @param tra 待校验路径
         * @return true 校验通过
         * @return false
         */
        bool CheckCurvature(std::vector<Trajectory_Point> &tra);
        /**
         * @brief 供本地rivz仿真使用，读取本地地图
         *
         * @return true
         * @return false
         */
        bool ReadAllMapFile();
        /**
         * @brief 计算轨迹每个轨迹点加速度
         *
         * @param temp_path
         */
        void CalAcc(std::vector<Trajectory_Point> &temp_path);
        /**
         * @brief 判断轨迹是否绕圈
         *
         * @param path
         * @return true 绕圈
         * @return false 不绕圈
         */
        bool doesTrajectorySelfIntersect(Path &path);
        /**
         * @brief 核查轨迹是否断裂
         *
         * @param input_path
         * @return true 断裂
         * @return false
         */
        bool checkPathFracture(std::vector<Trajectory_Point> &input_path);
        /**
         * @brief 给定point，判断traj是否处于search_distance范围内
         *
         * @param point
         * @param traj
         * @param search_distance
         * @param lat_dis point与traj最近点横向距离
         * @return true 位于
         * @return false 不位于
         */
        bool FindSuitableReferenceLine(Single_Point point, Single_Trajectory traj, double search_distance, double lat_dis);
        /**
         * @brief 超速检测
         *
         * @param input_path
         * @return true
         * @return false
         */
        bool OverSpeedCheck(std::vector<Trajectory_Point> &input_path);
        /**
         * @brief 跨区域挪车
         *
         * @return ErrorType
         */
        ErrorType PlanningCase8();
        /**
         * @brief 区域内部挪车
         *
         * @return ErrorType
         */
        ErrorType PlanningCase7();
        /**
         * @brief 由装载等待点前往装载点规划
         *
         * @return ErrorType
         */
        ErrorType PlanningCase9();
        /**
         * @brief 由装载点前往驶离装载点规划
         *
         * @return ErrorType
         */
        ErrorType PlanningCase10();

        /**
         * @brief
         *
         * @param path 封装在全局函数中的规划库接口函数
         */
        void GlobalPathPlanningIntface(std::vector<Trajectory_Point> &path);

    public:
        Single_Point start_point_;                 // 起始点坐标
        Single_Point end_point_;                   // 目标点坐标
        uint8 start_node_;                         // 起始点所在区域
        uint8 end_node_;                           // 目标点所在区域
        uint8 start_zone_type_;                    // 起始区域属性
        uint8 end_zone_type_;                      // 目标区域属性
        std ::vector<Single_Zone> all_zones_;      // 储存所有地图信息
        Directed_Graph road_directed_graph_;       // 区域连通关系有向图
        Dijkstra dijkstra_;                        // dijkstra对象
        HybridAStar::OptimalPath my_optimal_path_; // hibrid A star类的实例对象
        GlobalSpeedPlanning my_speed_planning_;
        std ::vector<uint8> zone_sequence_;          // dijkstra 算法得到的全局路径依次经过的区域id
        std ::vector<Trajectory_Point> global_path_; // 全局路径
        vehicle_param m_vehicle_param_;              // 传入的车辆参数以及算法参数
        float64 vehicle_commander_;                  // 车长
        uint task_type_;                             // 任务类型 用于终点处规划，规划方案选型
        bool end_point_out_border_;                  // 终点是否在边界外
        uint last_task_type_;                        // 上一次任务类型
        bool start_point_out_border_;                // 终点是否在边界外

        CollisonCheck collison_check_;
        std::vector<float64> s_;
        spline sx_;
        spline sy_;
        float64 kDeltaS_ = 0.1;
        uint error_type_ = 0;
        std::shared_ptr<spdlog::logger> threadLogger_;
        std::vector<uint8> vec_path_;
        string Vehicle_code_;
        string key_;
        bool reverse_flag_;
#ifdef SKIP_HEADER
#else
    private:
        CConfigureIO configio_;

    public:
        rviz_path ::CRvizPath c_rviz_; // for 显示
        tarRviz m_tar_rviz_data_;
#endif
    };

    // 后台调用global_dll.dll函数的接口 传入参数均为json格式
    char *GlobalPathPlanning(char *point_veh_start_end); // 全局轨迹规划
    void GetMap(char *parea);                            // 初始化自动获取地图信息
}

#endif // SHENYAN_H
