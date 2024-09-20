#ifndef GLOBAL_PLANNING_COMMON_STRUCT_H
#define GLOBAL_PLANNING_COMMON_STRUCT_H

#ifdef SKIP_HEADER

#else
#include <geometry_msgs/Point.h>
#endif

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

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
enum struct ErrorType : unsigned int {
    SUCCESS,
    POINT_UNREASONABLE,  // 作业点不合理
    ROAD_GRAPH_ERROR,    // 路网权重图存在问题
    SPEED_PLANNING_FAIL, // 速度规划失败
    ALGORITHM_ERROR,     // 规划算法崩溃，拿出日志，并联系开发人员
    OFFSET_FAIL,         // 均匀碾压失败
    NO_MAP,              // 规划库无地图，可能是容器被重启了，需要重新加载地图
};

struct _TrajectoryPoint {
    double        x;         // x坐标(单位：m)
    double        y;         // y坐标(单位：m)
    double        z;         // z坐标(单位：m)
    double        yaw;       // 朝向(单位：0~360deg)
    double        curvature; // 轨迹的曲率(单位：rad/s)
    double        speed;
    double        distance;
    unsigned char attribute; // 路点属性(根据具体场景定义)
    double        speed_limit;
    unsigned char direction; // 路点方向(0:前进，1:倒退)
    double        acc;
    bool          offset_flag;
    double        t; // 到达改点的时间

    inline void Clear() {
        x = y = z = yaw = curvature = speed = distance = attribute = speed_limit = direction = acc = t = 0;
    }
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
    double       linear_preferred_distance_square;
    unsigned int offset_enable;
    unsigned int multi_section_speed_limit_enable;
    float        light_regular_road_speed_limit;
    float        light_bumpy_road_speed_limit;
    float        light_slope_road_speed_limit;
    float        light_narrow_road_speed_limit;
    float        light_intersection_road_speed_limit;

    float        heavy_regular_road_speed_limit;
    float        heavy_bumpy_road_speed_limit;
    float        heavy_slope_road_speed_limit;
    float        heavy_narrow_road_speed_limit;
    float        heavy_intersection_road_speed_limit;
    unsigned int weather;
    unsigned int task_type;
    unsigned int vehicle_code;
    unsigned int s_curve_speed_limit;
    unsigned int border_change_range;
    unsigned int border_sample_inter;
    float        max_l;
    float        sita;
    float        base;

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
    double end_offset_distance   = 0.0;
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
    bool  is_light;
    bool  hybrid_h_use_rs;
    bool  hybrid_h_use_a_star;
    bool  hybrid_h_use_max;
    float vonoroi_grid_dist;
    float kVoronoiTerm;
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

typedef struct {
    double d_Max_Acc;
    double d_Min_Acc;
    double d_Max_Deceleration;
} tar_Speed, *ptar_Speed;
enum struct PlanRule : int {
    Normal_Planning = 0, // 正常规划,无特殊限制
    // START_BACK_END_IN   = 1, // 起点倒退，终点前进
    // START_BACK_END_BACK = 2, // 起点倒退，终点倒退
    // START_IN_END_IN     = 3, // 起点前进，终点前进
    // START_IN_END_BACK   = 4, // 起点前进，终点倒退
    NO_Backward_In_Start = 1, // 不能倒车起步
    Backward_To_End      = 2, // 必须倒车进入终点，且前进后退只切换一次
    Forward_To_End       = 3, // RS曲线必须前进拟合到终点
    Backward_All_Time    = 4, // 只后退
    Forward_All_Time     = 5, // 只前进
    Entry_loading_point  = 6, // 进入装载点
    U_Turn               = 7  // U行转弯(掉头)
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

enum class PlanResult {
    Plan_OK               = 0,    // 规划成功
    Plan_Overtime         = -301, // 规划超时
    Plan_Infeasible       = -302, // 无可行路径
    StartPoint_Infeasible = -303, // 起点不可行
    EndPoint_Infeasible   = -304, // 终点不可行
    Map_Infeasible        = -305  // 地图不可行
};

} // namespace GlobalPlanning

#endif // GLOBAL_PLANNING_COMMON_STRUCT_H
