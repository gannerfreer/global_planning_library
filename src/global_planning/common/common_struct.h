#ifndef GLOBAL_PLANNING_COMMON_STRUCT_H
#define GLOBAL_PLANNING_COMMON_STRUCT_H

#ifdef SKIP_HEADER

#else
#include <geometry_msgs/Point.h>
#endif

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <shared_mutex>
#include <vector>

#include "../third_lib/rapidjson/document.h"
#include "../third_lib/rapidjson/filereadstream.h"
#include "../third_lib/rapidjson/filewritestream.h"
#include "../third_lib/rapidjson/prettywriter.h"
#include "../third_lib/rapidjson/stringbuffer.h"
#include "../third_lib/rapidjson/writer.h"

using namespace std;

namespace GlobalPlanning {
const double eps = 1e-8;
// 当前车辆任务类型
enum struct TaskType : unsigned int {
    RESERVED      = 0,
    TEMP_MOVE_CAR = 1, // 临时挪车
    DISPATCH      = 2, // 常规调度
    LOAD          = 3, // 装载
    UNLOAD        = 4  // 卸载
};

enum class PlanResult {
    Plan_OK                         = 0,  // 规划成功
    Plan_Infeasible                 = 1,  // 无可行路径
    Plan_Overtime                   = 2,  // 规划超时
    StartPoint_Collision            = 3,  // 起点碰撞
    StartPoint_Unreasonable         = 4,  // 当前车辆位置不合理
    EndPoint_Deviation              = 5,  // 终点不可行
    EndPoint_Collision              = 6,  // 终点不可行
    EndPoint_Infeasible             = 7,  // 终点不可达
    Map_Infeasible                  = 8,  // 地图不可行
    Leaving_Load_Point_Too_Close    = 9,  // 驶离装载点距离装载点太近
    Load_Queue_Point_Unreasonable   = 10, // 装载点角度不合理
    Unload_Queue_Point_Unreasonable = 11,
    Start_Point_Too_Far             = 12
};
enum struct ErrorType : unsigned int {
    SUCCESS                                           = 0,
    Plan_Infeasible                                   = 1,  // Plan_Infeasible 起点距离地图边界太近，请挪动车辆
    UnReasonable_Task                                 = 2,  // Plan_Overtime  当前车辆位置前、后方区域太窄，请将车挪至空旷地带
    StartPoint_Collision                              = 3,  // StartPoint_Collision 当前车辆位置与地图边界干涉，请挪车至地图区域内
    StartPoint_Unreasonable                           = 4,  // StartPoint_Unreasonable 当前车辆位置不合理，请调整车辆位置
    EndPoint_Deviation                                = 5,  // EndPoint_Deviation 当前任务终点不位于参考路径上，请后台系统人员排查问题
    EndPoint_Collision                                = 6,  // EndPoint_Collision  当前任务终点与地图边界干涉，请调整任务终点
    EndPoint_Infeasible                               = 7,  // EndPoint_Infeasible 当前任务终点距离边界太近，无法成功规划到此位置的轨迹，请调整目标点角度或位置
    ROAD_GRAPH_ERROR                                  = 8,  // Map_Infeasible 地图文件中，参考路径联通关系数据异常，请后台人员排查问题
    Leaving_Load_Point_Too_Close                      = 9,  // Leaving_Load_Point_Too_Close 驶离装载点距离装载点太近
    Load_Queue_Point_Unreasonable                     = 10, // Load_Queue_Point_Unreasonable 装载点角度不合理
    Unload_Queue_Point_Unreasonable                   = 11, // Unload_Queue_Point_Unreasonable 卸载排队点不合理，距离卸载点太近且无调整空间
    NO_MAP                                            = 12, // 规划库所在容器未加载地图
    ALGORITHM_ERROR_PARAS_PARSE_FAIL                  = 13, // 全局规划算法运行异常-入参解析功能异常
    ALGORITHM_ERROR_UNIFORM_COMPACTION                = 14, // 全局规划算法运行异常-均匀碾压功能异常
    ALGORITHM_ERROR_TRAJECTORY_VERIFY_PATH_BREAK      = 15, // 全局规划算法运行异常-路径校验异常，路径断裂
    ALGORITHM_ERROR_TRAJECTORY_VERIFY_SPEED_OVER      = 16, // 全局规划算法运行异常-路径校验异常,轨迹超速
    ALGORITHM_ERROR_TRAJECTORY_VERIFY_DIRECTION_ERROR = 17, // 全局规划算法运行异常-路径校验异常,倒车路段direction错误
    ALGORITHM_ERROR_TRY_CATCH_ERROR                   = 18, // try_catch捕获异常
    Start_Point_Too_Far                               = 19  // Start_Point_Too_Far 任务起点远离所有参考路径，目前支持最大范围100m
};

enum struct PointAttribute : unsigned int {
    regular_road      = 0, // 常规道路
    narrow_road       = 1, // 会车道路
    intersection_road = 2, // 交叉路口
    slope_road        = 3, // 坡路
    dump_road         = 4, // 颠簸路
    weight_point      = 6, // 过磅
    clean_point       = 7, // 洗车
    queue_point       = 8  // 排队点
};

enum struct SpeedLimitLevel : unsigned int {
    reserve = 0,
    one     = 1, // 一级限速
    two     = 2, // 二级限速
    three   = 3  // 三级限速
};

struct _TrajectoryPoint {
    double         x;         // x坐标(单位：m)
    double         y;         // y坐标(单位：m)
    double         z;         // z坐标(单位：m)
    double         yaw;       // 朝向(单位：0~360deg)
    double         curvature; // 轨迹的曲率(单位：rad/s)
    double         speed;
    double         distance;
    PointAttribute attribute; // 路点属性(根据具体场景定义)
    double         speed_limit;
    unsigned char  direction; // 路点方向(0:前进，1:倒退)
    double         acc;
    bool           offset_flag;
    double         t; // 到达改点的时间

    inline void Clear() {
        x = y = z = yaw = curvature = speed = distance = speed_limit = direction = acc = t = 0;
    }
    _TrajectoryPoint() : x(0), y(0), z(0), yaw(0), curvature(0), speed(0), distance(0), attribute(PointAttribute::regular_road), speed_limit(0), direction(0), acc(0), offset_flag(false), t(0) {}
    _TrajectoryPoint(double x_val, double y_val, double yaw_val) : x(x_val), y(y_val), z(0), yaw(yaw_val), curvature(0), speed(0), distance(0), attribute(PointAttribute::regular_road), speed_limit(0), direction(0), acc(0), offset_flag(false), t(0) {}
};

struct _SingleTraj {
    unsigned int             id; // 路径的编号
    vector<_TrajectoryPoint> trajectory;
};

struct _BorderPoint {
    double        x;
    double        y;
    double        z;
    unsigned char type;
};

struct _SinglePoint {
    double      x;   // x坐标(单位:m)
    double      y;   // y坐标(单位:m)
    double      z;   // z坐标(单位:m)
    double      yaw; // 朝向(单位:deg)
    inline void Clear() {
        x = y = z = yaw = 0;
    }
};

struct _VehicleParam {
    // 后轴中心到车头距离
    double veh_center_2_front;
    // 后轴中心到车尾距离
    double veh_center_2_rear_bound;
    // 后轴中心到两侧距离
    double veh_center_2_side;
    // 轴距
    double wheel_base;
    // 前后左右的安全距离（地图边界）
    double safe_margin_bound;
    // 前后左右的安全距离（障碍物）
    double safe_margin_obstacle;
    // 重载向后开最大车轮转角
    double heavy_backward_max_steering;
    // 重载向前开最大车轮转角
    double heavy_forward_max_steering;
    // 轻载向前开最大车轮转角
    double light_forward_max_steering;
    // 轻载向后开最大车轮转角
    double light_backward_max_steering;
    // 车辆后轴最小转弯半径(用于RS曲线拟合)
    double radious;
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

    // 路径平滑前路点距离
    double hybridastar_step_length;
    // 前进惩罚
    double forward_penalty;
    // 倒退惩罚
    double backward_penalty;
    // 转向惩罚
    double turnning_penalty;
    // 方向切换惩罚
    double switch_penalty;

    // 起始处线性搜索优先的范围
    double       linear_preferred_distance;
    bool         uniform_compaction_enable;
    float        regular_road_speed_limit;
    float        bumpy_road_speed_limit;
    float        slope_road_speed_limit;
    float        narrow_road_speed_limit;
    float        intersection_road_speed_limit;
    unsigned int task_type;
    unsigned int vehicle_code;

    double path_error_term;
    // 曲率项权重
    double path_curvature_term;
    // 平滑项权重
    double path_smoothness_term;
    // 最大曲率
    double max_kappa;
    // 最大优化迭代次数
    double max_iterations_opti;

    // 安全距离允许浮动偏差
    double safe_margin_error; // safe_margin_bound / 2;

    // 尖点延伸距离
    float cusp_extension_distance;


    // 速度规划参数
    /* 最大加速度 单位(m/s^2) */
    float max_acceleration;
    /* 最小加速度 单位(m/s^2) */
    float min_acceleration;

    /* 误差项权重 */
    float speed_error_term;
    /* 平滑项权重 */
    float speed_smooth_term;
    /* 倒车速度 */
    float reverse_speed;


    /*曲率校验阈值*/
    float curvature_threshold;
    bool  is_light;

    SpeedLimitLevel speed_limit_level        = SpeedLimitLevel::three;
    int             L2                       = 8;
    int             L3                       = 4;
    float           rs_min_length            = 2;
    float           L1                       = 1.0;
    float           offset_distance          = 0.3;
    float           max_steering_wheel_speed = 0.1396;
    int             sample_num               = 40;
    float           plan_time                = 0.2;
    float           w_curvature              = 1.0;
    float           w_length                 = 0.0;
    float           dis_threshold            = 2.0;
};

// 调用全局规划时，需要传入的参数
struct _TarStartEnd {
    _SinglePoint                 start_point;   // 起点
    _SinglePoint                 end_point;     // 终点
    _VehicleParam                veh_param;     // 车辆参数
    TaskType                     task_type;     // 当前车辆任务类型
    vector<vector<_BorderPoint>> inner_borders; // 区域内边界
    string                       my_key;
};

struct _HumanVechicleInfo {
    _SinglePoint pos; // 起点
    string       id;
};
// 调用有人车未来路径预测时，需要传入的参数
struct _AllHumanVechicleInfos {
    vector<_HumanVechicleInfo> human_vechicle_infos; // 有人车路位姿信息
    string                     my_key              = "human_test";
    int                        predicting_distance = 100;
};

struct GridPoint {
    GridPoint() : x(0.0), y(0.0), z(0.0), length(0.0), width(0.0), height(0.0) {}
    double x;
    double y;
    double z;
    float  length;
    float  width;
    float  height;
};

#ifdef SKIP_HEADER
#else
struct tarRviz {
    // vector<Point_3d> vec_point;
    vector<geometry_msgs::Point> vec_point, road_node, obstacle_v;
    double                       minx;
    double                       miny;
};
#endif

#if 1
typedef struct {
    double x;
    double y;
    double z;
} Point_3d;
#endif


enum struct PlanRule : int {
    Normal_Planning      = 0, // 正常规划,无特殊限制
    Start_Back_End_Front = 1, // 起点倒退，然后前进到终点
    Start_Front_End_Back = 2, // 起点前进，然后倒车到终点
    Backward_All_Time    = 3, // 只后退
    Forward_All_Time     = 4, // 只前进
};
enum MotionDirection {
    Forward  = 0, // 前进
    Backward = 1  // 后退
};
struct Coordinate {
    Coordinate() {
        this->x = 0.0;
        this->y = 0.0;
        this->z = 0.0;
    }
    Coordinate(double x_, double y_, double z_) {
        this->x = x_;
        this->y = y_;
        this->z = z_;
    }
    double x; // x坐标, 单位：m
    double y; // y坐标, 单位：m
    double z; // z坐标, 单位：m
};
struct IntCoordinate {
    IntCoordinate() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    IntCoordinate(int x_, int y_, int z_) {
        this->x = x_;
        this->y = y_;
        this->z = z_;
    }
    int x; // x坐标, 单位：m
    int y; // y坐标, 单位：m
    int z; // z坐标，单位：m
};
/**
 * @brief 路点结构体(车辆构型)
 */
struct Point {
    Point() {
        this->x         = 0.0;
        this->y         = 0.0;
        this->z         = 0.0;
        this->angle     = 0.0;
        this->direction = MotionDirection::Forward;
    }
    Point(double x, double y, double z, double angle, MotionDirection direction) {
        this->x         = x;
        this->y         = y;
        this->z         = z;
        this->angle     = angle;
        this->direction = direction;
    }
    double x; // x坐标, 单位：m
    double y; // y坐标, 单位：m
    double z; // z坐标, 单位：m

    double          angle; // 方向, 单位：rad
    double          curvature;
    MotionDirection direction; // 0表示前进，1表示后退(尖点属性随后)
};
/**
 * @brief 用于在open集和close集查找的取整point
 */
struct IntPoint_ {
    int             x;         // x坐标
    int             y;         // y坐标
    int             angle;     // 角度,rad
    MotionDirection direction; // 行驶方向,0为前进，1为后退
};

struct Line {
    double x1;
    double y1;
    double x2;
    double y2;
};


// 障碍物与地图边界
typedef vector<vector<Coordinate>> Bound;
// 带前进后退信息的路径
typedef std::vector<Point> Path;


} // namespace GlobalPlanning

#endif // GLOBAL_PLANNING_COMMON_STRUCT_H
