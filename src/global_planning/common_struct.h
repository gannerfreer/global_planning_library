#ifndef COMMON_STRUCT_H
#define COMMON_STRUCT_H

#include <string>
#include <vector>
#include <map>
#include "constants.h"
#include "../os/os.h"
#ifdef SKIP_HEADER

#else
#include <geometry_msgs/Point.h>
#endif
using std ::map;
using std ::string;
using std ::vector;
using namespace HybridAStar::Constants;
using namespace std;

namespace GlobalPlanning
{
    // 当前车辆任务类型
    enum struct TaskType : uint
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
    enum struct ErrorType : uint
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
    // 区域属性
    enum struct ZoneAttribute : uint8
    {
        LOAD_AREA = 0,     // 装载区
        UNLOAD_AREA = 1,   // 卸载区
        PARK_AREA = 2,     // 停车场
        CORSSING_AREA = 3, // 交叉路口
        NORMAL_ROAD = 4,   // 正常道路
        SINGLE_ROAD = 5,   // 单车道
    };

    typedef struct
    {
        int unreceived_obs;     // 80001
        int no_response;        // 80002
        int ids_avoid_obs_over; // 80003
        int standby;            // 80004
        int path_follow;        // 80005
        int veh_follow;         // 80006
    } Interactive_instruction;

    struct Trajectory_Point
    {
        float64 x;           // x坐标(单位：m)
        float64 y;           // y坐标(单位：m)
        float32 z;           // z坐标(单位：m)
        float32 yaw;         // 朝向(单位：0~360deg)
        float32 speed_limit; // 该路点的限速
        float64 left;        // 距左边界值
        float64 right;       // 距右边界值
        // float64 reversing;
        float32 speed;     // 轨迹的速度(单位：m/s)
        float32 curvature; // 轨迹的曲率(单位：rad/s)
        float32 slope;     // 道路坡道(单位：deg)
        float32 distance;  // 路点与轨迹起点沿轨迹的距离(单位：m)
        float32 acc;
        uint8 attribute; // 路点属性(根据具体场景定义)
        bool offset_flag = true;
        uint8 direction; // 路点方向(0:前进，1:倒退)
        uint8 areaid;    // 路点所在区域
        float64 t;       // 到达改点的时间

        inline void Clear()
        {
            x = y = z = yaw = speed = curvature = distance = acc = attribute = direction = slope = 0;
            left = right = 0;
        }
    };

    using ReferenceTrajectory = std ::vector<Trajectory_Point>;

    typedef struct
    {
        uint8 start_zone_id;                       // 路径起始区域ID
        uint8 current_zone_id;                     // 路径经过区域ID
        uint8 end_zone_id;                         // 路径到达区域ID
        uint8 id;                                  // 同方向路径的编号
        uint32 traj_point_num;                     // 路径的路点数量
        std ::vector<Trajectory_Point> trajectory; // 路径点容器,读取文件的时候，把对应区域的最大速度赋值给路径的最大速度！！！！！！！！！！！！！
    } Single_Trajectory;

    typedef struct
    {
        float64 x;   // x坐标(单位:m)
        float64 y;   // y坐标(单位:m)
        float32 z;   // z坐标(单位:m)
        float32 yaw; // 朝向(单位:deg)
        inline void Clear()
        {
            x = y = z = yaw = 0;
        }
    } Single_Point;

    typedef struct
    {
        float64 x;  // x坐标(单位：m)
        float64 y;  // y坐标(单位：m)
        float32 z;  // z坐标(单位：m)
        uint8 type; // 边界点类型(0:不可跨越，1:可跨越)
    } Single_Border_Point;

    typedef struct
    {
        uint32 point_num;                                // 边界点数量
        std ::vector<Single_Border_Point> border_points; // 边界点集
    } Single_Border;

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

    // 后台绕障传入障碍物
    struct Obj
    {
        Obj()
            : x(0.0), y(0.0), z(0.0), vx(0.0), vy(0.0), vz(0.0), width(0.0), length(0.0), height(0.0), track_state(0), predict_length(0), type(0), orientation(0.0), absolute_motion(0), id(0), contour_point()
        {
        }

        double x;
        double y;
        double z;
        float vx;
        float vy;
        float vz;
        float width;
        float length;
        float height;
        uint8_t track_state;
        uint8_t predict_length;
        int32_t type;
        float orientation;
        uint8_t absolute_motion;              // 绝对的运动状态 0:位置 1:静止 2:运动
        uint32_t id;                          // 跟踪之后给出的最感兴趣obj的id
        std::vector<GridPoint> contour_point; // 为障碍物的包络点
    };
    using Obstacles = std::vector<Obj>;

    typedef struct
    {
        uint8 zone_id; // 区域ID，1~255   str_area_Id

        uint8 zone_type;                                 // 区域类型(1:结构化道路，0:非结构化道路) str_area_type
        uint8 zone_attribute;                            // 区域属性(根据实际问题定义) str_area_name
        float32 max_speed;                               // 最大速度 n_max_speed
        std ::vector<Single_Point> parking_points;       // 区域内的停车点集
        std ::vector<Single_Point> load_points;          // 区域内的装载点集
        std ::vector<Single_Point> unload_points;        // 区域内的卸载点集
        Single_Border external_border;                   // 区域外边界
        std ::vector<Single_Border> inner_borders;       // 区域内边界，当做障碍物处理
        std ::vector<Single_Trajectory> reference_trajs; // 区域内的参考路径
        inline void Clear()
        {
            zone_id = zone_attribute = max_speed = 0;
            zone_type = 0;
            parking_points.clear();
            load_points.clear();
            unload_points.clear();
            external_border.border_points.clear();
            external_border.point_num = 0;
            inner_borders.clear();
            reference_trajs.clear();
        }
    } Single_Zone;
    using All_Zones = std ::vector<Single_Zone>; // 储存所有区域信息的容器，//区域id从小到大排列，区域i放在第i-1位，对应id无区域的位置零

    typedef struct
    {
        uint8 node_num;                           // 有向图节点数量
        std ::vector<std ::vector<double>> graph; // 有向图矩阵
        inline void Clear()
        {
            node_num = 0;
            graph.clear();
        }
    } Directed_Graph, *pDirected_Graph;
#ifdef SKIP_HEADER
#else
    struct tarRviz
    {
        // vector<Point_3d> vec_point;
        std::vector<geometry_msgs::Point> vec_point;
        float64 minx;
        float64 miny;
    };
#endif
    typedef struct
    {
        Directed_Graph Road_Directed_Graph; // 有向图
        All_Zones all_zone_atr;             // 所有区域属性
    } zones;

#if 1
    typedef struct
    {
        float64 x;
        float64 y;
        float64 z;
    } Point_3d;
#endif

    typedef struct
    {
        Single_Point current_veh_location; // 车辆当前位置
        float32 current_speed;             // 车辆当前速度
    } vehicle_state;

    typedef struct
    {
        double d_Max_Acc;
        double d_Min_Acc;
        double d_Max_Deceleration;
    } tar_Speed, *ptar_Speed;

    struct zone_inner_border
    {
        uint8 zone_id;
        std::vector<Single_Border> inner_border;
    };

    // 调用全局规划时，需要传入的参数
    typedef struct
    {
        Single_Point m_Start_Point;                   // 起点
        Single_Point m_End_Point;                     // 终点
        vehicle_param m_Veh_Param;                    // 车辆参数
        uint m_task_type;                             // 当前车辆任务类型
        Directed_Graph Road_Directed_Graph;           // 有向图
        std::vector<zone_inner_border> inner_borders; // 区域内边界
        string my_key;
    } tar_start_end;

    // 调用后台绕障接口时，传入的参数
    typedef struct
    {
        vehicle_state m_cur_vehicle;                   // 当前车辆状态，包括车辆位置，朝向，速度
        Obstacles m_current_obs;                       // 当前车辆周围障碍物
        vehicle_param m_Veh_Param;                     // 当前车辆的车身参数、算法参数
        tar_Speed acc_dec_speed;                       // 车辆的加速度、减速度
        std::vector<Trajectory_Point> cur_global_path; // 当前车辆的所执行任务的全局轨迹
    } tar_local_planning_parm;

}

#endif // COMMON_STRUCT_H
