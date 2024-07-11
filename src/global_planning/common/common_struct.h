#ifndef GLOBAL_PLANNING_COMMON_STRUCT_H
#define GLOBAL_PLANNING_COMMON_STRUCT_H

#ifdef SKIP_HEADER

#else
#include <geometry_msgs/Point.h>
#endif

#include <iostream>
#include <vector>
#include <map>
#include <shared_mutex>
#include <iomanip>
#include <fstream>
#include <filesystem>

#include "../third_lib/rapidjson/document.h"
#include "../third_lib/rapidjson/writer.h"
#include "../third_lib/rapidjson/stringbuffer.h"
#include "../third_lib/rapidjson/filewritestream.h"
#include "../third_lib/rapidjson/prettywriter.h"
#include "../third_lib/rapidjson/filereadstream.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

using namespace std;

namespace GlobalPlanning
{
    // 当前车辆任务类型
    enum struct TaskType : unsigned int
    {
        RESERVED = 0,                     // 保留
        GO_LOAD_POINT = 1,                // 前往装载点
        GO_LOADAREA_WAITAREA = 2,         // 前往装载区候车区
        GO_UNLOAD_POINT = 3,              // 前往卸载点
        GO_UNLOADAREA_WAITAREA = 4,       // 前往卸载区候车区
        GO_PARKLOT_POINT = 5,             // 前往停车场停车点
        GO_PARK_AREA = 6,                 // 前往停车候车区
        TASK_CANCLE = 7,                  // 任务取消
        TEMP_MOVE_CAR = 8,                // 临时挪车
        GO_TO_CHARGING_WAITAREA = 9,      // 前往充电候车区
        GO_TO_CHARGING_POINT = 10,        // 前往充电电
        GO_LOAD_TRANSITIONS_POINT = 11,   // 前往装载区过渡点
        GO_APART_LOADING_POINT = 12,      // 驶离装载点
        GO_UNLOAD_TRANSITIONS_POINT = 13, // 前往卸载过渡点
    };
    enum struct ErrorType : unsigned int
    {
        SUCCESS,
        START_OUT_OF_MAP,             // 当前任务起点坐标超出地图区域范围
        END_OUT_OF_MAP,               // 当前任务终点坐标超出地图区域范围
        START_POINT_UNREASONABLE,     // 起点位置不合理，调整车辆位置
        END_POINT_UNREASONABLE,       // 终点位置不合理，调整车辆位置
        PLANNING_FAIL,                // 规划算法无法规划出路径，拿出日志，并联系开发人员
        DIRECTION_MAP_ERROR,          // mapjson中传入的有向图异常
        SPEED_PLANNING_FAIL,          // 速度规划失败
        END_POINT_ERROR,              // 当前任务的终点不严格意义上位于参考路径上
        NO_REFERENCELINE,             // 地图中缺少行车参考路径
        TOO_CLOSE_TO_LOADING_POINT,   // 电铲位置相对驶离装载点位置不合理
        ALGORITHM_ERROR,              // 规划算法崩溃，拿出日志，并联系开发人员
        NO_LONG_DISTANCE_BACK,        // 需要长距离倒车，超过20m，不予以处理
        OFFSET_FAIL,                  // 均匀碾压失败
        NO_MAP,                       // 规划库无地图，可能是容器被重启了，需要重新加载地图
        ERROR_LOADING_WAITTING_POINT, // 装载等待点与装载点不属于同一区域，诊断为错误的装载等待点，请核验
        PATH_FRACTURE,                // 路径出现断裂，请检查map.json中的参考路径
        REFERENCELINE_LOSS            // 卸载区参考路径存在丢失
    };

    struct _TrajectoryPoint
    {
        double x;         // x坐标(单位：m)
        double y;         // y坐标(单位：m)
        double z;         // z坐标(单位：m)
        double yaw;       // 朝向(单位：0~360deg)
        double curvature; // 轨迹的曲率(单位：rad/s)
        double speed;
        double distance;
        unsigned char attribute; // 路点属性(根据具体场景定义)
        double speed_limit;
        unsigned char direction; // 路点方向(0:前进，1:倒退)

        inline void Clear()
        {
            x = y = z = yaw = curvature = speed = distance = attribute = speed_limit = direction = 0;
        }
    };

    struct _SingleTraj
    {
        unsigned int id; // 路径的编号
        vector<_TrajectoryPoint> trajectory;
    };

    struct _BorderPoint
    {
        double x;
        double y;
        double z;
        unsigned char type;
    };

    struct _SinglePoint
    {
        double x;   // x坐标(单位:m)
        double y;   // y坐标(单位:m)
        double z;   // z坐标(单位:m)
        double yaw; // 朝向(单位:deg)
        inline void Clear()
        {
            x = y = z = yaw = 0;
        }
    };

    struct _VehicleParam
    {
        // 后轴中心到车头距离
        double veh_center_2_front;
        // 后轴中心到车尾距离（地图边界）
        double veh_center_2_rear_bound;
        // 后轴中心到车尾距离（障碍物）
        double veh_center_2_rear_obstacle;
        // 后轴中心到两侧距离
        double veh_center_2_side;
        // 轴距
        double wheel_base;
        // 前后左右的安全距离（地图边界）
        double safe_margin_bound;
        // 前后左右的安全距离（障碍物）
        double safe_margin_obstacle;
        // 最小车轮转角
        double min_steering;
        // 最大车轮转角
        double max_steering;
        // 车辆后轴最小转弯半径(用于RS曲线拟合)
        double radious;

        // 混合A星+RS算法参数
        // 是否使用BFS提前遍历地图得到H值查询表
        bool bfs_search;
        // 最大迭代次数
        unsigned int max_iterations_astar;
        // 前轮转角离散数量(奇数)
        unsigned int angle_discrete_num;
        // 拓展步长
        double delta_dist;
        // xy网格大小
        double grid_dist;
        // 角度网格大小
        double grid_angle;
        // RS拟合的距终点最大距离
        double max_fitting_radius;
        // RS单段路径最小距离
        double min_path_Length;
        // 路径平滑前路点距离
        double step_length;
        // 前进惩罚
        double forward_penalty;
        // 倒退惩罚
        double backward_penalty;
        // 转向惩罚
        double turnning_penalty;
        // 方向切换惩罚
        double switch_penalty;
        // 倒车搜索范围（距起点距离）
        double backward_search_range;
        // 起始处线性搜索优先的范围
        double linear_preferred_distance_square;
        unsigned int offset_enable;
        unsigned int multi_section_speed_limit_enable;
        float light_regular_road_speed_limit;
        float light_bumpy_road_speed_limit;
        float light_slope_road_speed_limit;
        float light_narrow_road_speed_limit;
        float light_intersection_road_speed_limit;

        float heavy_regular_road_speed_limit;
        float heavy_bumpy_road_speed_limit;
        float heavy_slope_road_speed_limit;
        float heavy_narrow_road_speed_limit;
        float heavy_intersection_road_speed_limit;
        unsigned int weather;
        unsigned int task_type;
        unsigned int vehicle_code;
        unsigned int s_curve_speed_limit;
        unsigned int border_change_range;
        unsigned int border_sample_inter;
        float max_l;
        float sita;
        float base;

        // _________________
        // 路径后处理算法参数（平滑+插值）
        // 误差项权重
        double error_term;
        // 曲率项权重
        double curvature_term;
        // 平滑项权重
        double smoothness_term;
        // 最大曲率
        double max_kappa;
        // 最大优化迭代次数
        double max_iterations_opti;
        // 插值距离
        double delta_s;
        // 安全距离允许浮动偏差
        double safe_margin_error; // safe_margin_bound / 2;

        // _________________
        // 特殊处理参数
        // 终点添加直线段距离
        double end_offset_distance = 0.0;
        double start_offset_distance = 0.0;
        // 尖点延伸距离
        unsigned int cusp_extension_distance;
        // _________________
        // 限速处理
        float min_speed_limit; // 4
        float mid_speed_limit; // 6
        float max_speed_limit; // 8

        // _________________
        // 曲率划分
        float min_curvature;
        float max_curvature;

        // 终点选择判断阈值
        double min_distance;
        double lat_min_distance;
        double lon_min_distance;

        // 横纵向偏差值影响因子
        double lat_term;
        double lon_term;

        double lat_min_distance_struct;

        // ________________
        // 速度规划参数
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
    };

    // 调用全局规划时，需要传入的参数
    struct _TarStartEnd
    {
        _SinglePoint start_point;                   // 起点
        _SinglePoint end_point;                     // 终点
        _VehicleParam veh_param;                    // 车辆参数
        unsigned int task_type;                     // 当前车辆任务类型
        vector<vector<_BorderPoint>> inner_borders; // 区域内边界
        string my_key;
    };

    struct GridPoint
    {
        GridPoint()
            : x(0.0), y(0.0), z(0.0), length(0.0), width(0.0), height(0.0)
        {
        }
        double x;
        double y;
        double z;
        float length;
        float width;
        float height;
    };

#ifdef SKIP_HEADER
#else
    struct tarRviz
    {
        // vector<Point_3d> vec_point;
        vector<geometry_msgs::Point> vec_point;
        double minx;
        double miny;
    };
#endif

#if 1
    typedef struct
    {
        double x;
        double y;
        double z;
    } Point_3d;
#endif

    typedef struct
    {
        double d_Max_Acc;
        double d_Min_Acc;
        double d_Max_Deceleration;
    } tar_Speed, *ptar_Speed;

}

#endif // GLOBAL_PLANNING_COMMON_STRUCT_H
