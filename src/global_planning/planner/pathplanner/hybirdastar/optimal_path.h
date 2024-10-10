/***************************************************/
/*            Author: Biao Xu                      */
/*            Contact: dr_xubiao@163.com           */
/*            Last update: 2020-04-15              */
/***************************************************/
/*
Description: The header file for C++ class OptimalPath.
*/

// Syntax: <package name>_<type>_<file name>_H
#ifndef OPTIMAL_PATH_H
#define OPTIMAL_PATH_H

#include "../../../collision_check/collision_check.h"
#include "../../../common/common_struct.h"
#include "../../../math/helper.h"
#include "../../../smoother/path_opti.h"
// #include "../../../os/os.h" //包含所有所需标准头文件
#include <set>

#include "../../../smoother/dynamicvoronoi.h"
#include "../../../time/StringHelper.h"
#include "../../../time/TimeHelper.h"
#include "../dubins/dubins.h"
#include "node2d.h"
#include "r_s_curve.h"
#include "r_s_curve_for_h.h"

namespace GlobalPlanning {
/**
 * @brief Hybrid A*算法中节点
 */
struct Vertex3D {
    unsigned long long id;        // id信息
    unsigned long long parent_id; // 父节点id
    double             x;         // x坐标
    double             y;         // y坐标
    double             z;         // z坐标
    double             angle;     // 角度,rad
    MotionDirection    direction; // 行驶方向,0为前进，1为后退
    double             h;         // 与终点估计代价
    double             g;         // 与起点代价
    double             f;         // 总代价
    //
};

/**
 * @brief BFS算法中节点
 */
struct Vertex2D {
    int    x; // x坐标
    int    y; // y坐标
    int    z; // z坐标
    double g; // 与起点代价
};

/**
 * @brief 终点RS拟合方向枚举
 */
enum class FittingDirection {
    Forword_Fitting  = 0, // 前进拟合
    Backward_Fitting = 1, // 后退回合
    Both_Fitting     = 2, // 前进后退皆可
};

/**
 * @brief 全局路径规划主类
 */
class OptimalPath {
  public:
    OptimalPath() {}  // 默认构造函数
    ~OptimalPath() {} // 析构函数
    /**
     * @brief 全局路径规划类接口函数
     * @param [in] start            起始构型(x,y,theta)
     * @param [in] end              终止构型(x,y,theta)
     * @param [in] road_bound       道路边界
     * @param [in] obstacle_bound   障碍物边界
     * @param [in] plan_path_rule   规划规则(默认为无规则)
     * @param [in & out] final_path 规划的路径
     * @return 返回说明：
     * 返回规划结果
     */
    PlanResult    SearchGlobalPath(const Point start, const Point end, const _VehicleParam m_vehicle_param, Path& final_path, long long time_threshold, const PlanRule plan_path_rule = PlanRule ::Normal_Planning);
    void          InitVoronoiAndBound(const _SinglePoint start_point, const vector<_BorderPoint>& map_border, const vector<vector<_BorderPoint>>& inner_borders, const _VehicleParam& m_vehicle_param, bool enable_voronoi);
    void          DeleteVoronoiSpace(bool enable_voronoi);
    _VehicleParam m_vehicle_param_;

  private:
    /**
     * @brief 数据初始化函数，将数值减小，防止精度丢失
     * @param [in] start          起始构型
     * @param [in] end            终止构型
     * @param [in] road_bound     道路边界
     * @param [in] obstacle_bound 障碍物边界
     */
    void InitData(Point start, Point end);

    /**
     * @brief 混合A*搜索主函数
     * @param [out] path  规划的路径
     * @return 返回说明：
     * 返回规划结果
     */
    PlanResult AStarPath(Path& path, long long timeThreshold);

    /**
     * @brief 初始化CLOSE集与OPEN集函数
     * @return 返回说明：无
     */
    void InitOpenClose();

    /**
     * @brief 判断是否退出混合A*搜索函数
     * @param [in] point  混合A星搜索的当前点
     * @return 返回说明：
     * true：退出A*
     * false:继续A*
     */
    bool IfExitAStar(const Vertex3D& point);

    /**
     * @brief 寻找所有拓展节点函数
     * @param [in] current_point 混合A星搜索的当前点
     * @return 返回说明：无
     */
    void FindExpandVertex(const Vertex3D& current_point, unsigned long long& time_dy, unsigned long long& time_collision, unsigned long long& time_expand_other);

    /**
     * @brief 路径回溯函数
     * @param [in] final_point 路径终点哈希值
     * @return 返回说明：无
     */
    void TracePath(const Vertex3D final_point);
    /**
     * @brief 路径整合函数
     * @return 返回说明：无
     */
    void PathIntegration();
    /**
     * @brief 路径点数据还原函数
     * @param [in] path 最终还原的路径
     * @return 返回说明：无
     */

    void removeDuplicates(Path& input, Path& result);
    void RestoreData(Path& path);
    /**
     * @brief 基于车辆运动学模型的节点拓展函数
     * @param [in] start     起始点
     * @param [in] direction 行驶方向，0为前进，1为后退
     * @param [in] steering  转向角度,左转为正，右转为负
     * @param [out] end      下一步的点
     * @return 返回说明：无
     */
    void VehDynam(const Vertex3D& start, const MotionDirection direction, const double steering, Vertex3D& end);
    /**
     * @brief 计算g值函数
     * @param [in] start_point     起点
     * @param [in & out] end_point 终点
     * @return 返回说明：无
     */
    inline void CalGValue(const Vertex3D& start_point, Vertex3D& end_point);

    /**
     * @brief 计算h值(与终点代价的估计值)函数
     * @param [in & out] point 目前的点
     * @return 返回说明：无
     */
    void CalHValue(Vertex3D& point);

    /**
     * @brief 采用广度优先算法遍历计算与终点距离
     * @return 返回说明：计算是否成功
     */
    bool BFSSearch2D();

    /**
     * @brief 采用A*搜索算法计算启发值
     * @return 返回说明：计算计算得到的启发值
     */
    float AStarSearch2D(Node2D& start, Node2D& goal, int& num);

    /**
     * @brief 判断柵格点是否在边界上函数
     * @param [in] point 所需判断的柵格点
     * @return 返回说明：
     * 若位于边界上,返回是,若不在边界上,返回否
     */
    bool IsBoundGrid(IntCoordinate point);

    /**
     * @brief 生成柵格边界集函数
     * @return 返回说明：无
     */
    void GenerateBoundSet();

    /**
     * @brief 生成左右边界值
     * @return 返回说明：无
     */
    // void GetLeftAndRightDistance(Path& final_path);

    /**
     * @brief 判断两线段是否相交
     */
    bool IsIntersection(const Line& l1, const Line& l2);

    /**
     * @brief 将2D柵格坐标转换为哈希值函数
     * @param [in] 柵格坐标
     * @return 返回说明：对应哈希值
     */
    inline unsigned int Coordinate2Hash(const IntCoordinate point) {
        unsigned int hash = 0;
        hash |= (point.x) << 16;
        hash |= (point.y & 0x0000FFFF);
        return hash;
    }
    /**
     * @brief 将哈希值转换为函数2D柵格坐标
     * @param [in] hash 哈希值
     * @return 返回说明：对应2D柵格坐标
     */
    inline IntCoordinate Hash2Coordinate(unsigned long long hash) {
        IntCoordinate point;
        point.x = hash >> 16;
        point.y = hash & 0xFFFF;
        return point;
    }
    /**
     * @brief 将混合A*搜索3D点转换为哈希值函数
     * @param [in] v 混合A*搜索节点
     * @return 返回说明：对应哈希值
     */
    inline unsigned long long Vertex2Hash(Vertex3D v) {
        IntPoint_ int_vertex;
        int_vertex.x         = static_cast<int>(floor(v.x / m_vehicle_param_.grid_dist));
        int_vertex.y         = static_cast<int>(floor(v.y / m_vehicle_param_.grid_dist));
        int_vertex.angle     = static_cast<int>(floor(v.angle / m_vehicle_param_.grid_angle));
        int_vertex.direction = v.direction;
        return Point2Hash(int_vertex);
    }
    /**
     * @brief 3D柵格点转换为哈希值函数
     * @param [in] p 3D柵格点
     * @return 返回说明：对应哈希值
     */
    inline unsigned long long Point2Hash(IntPoint_ p) {
        unsigned long long hash = 0;
        unsigned long long tmp;
        if (p.direction == MotionDirection::Backward) {
            hash |= 0x8000000000000000;
        }
        if (p.angle < 0) {
            hash |= 0x4000000000000000;
            p.angle = -p.angle;
        }
        if (p.x < 0) {
            hash |= 0x2000000000000000;
            p.x = -p.x;
        }
        if (p.y < 0) {
            hash |= 0x1000000000000000;
            p.y = -p.y;
        }
        tmp = p.angle & 0xFFF;
        hash |= (tmp << 48);
        tmp = p.x & 0xFFFFFF;
        hash |= (tmp << 24);
        hash |= (p.y & 0xFFFFFF);
        return hash;
    }

    void   CalCurv(Path& temp_path);
    double computeCurvature(const Point& p1, const Point& p2, const Point& p3);

  public:
    /**
     * @brief 设置地图AABB包围盒函数
     * @return 返回说明：无
     */
    inline void SetBoxBoundSet(std ::vector<int> box_index) {
        box_index_ = box_index;
    }
    /**
     * @brief 取出混合A*搜索路径点函数
     * @return 返回说明：
     * 返回混合A*搜索路径点
     */
    Path GetPathAStar() {
        for (auto& pt : path_a_star_) {
            pt.x += midpoint_.x;
            pt.y += midpoint_.y;
        }
        return path_a_star_;
    }
    /**
     * @brief 获取拓展点函数
     * @return 返回说明：
     * 返回所有拓展点
     */
    Path GetExpandPoint() {
        Path  expandpoint;
        Point temp_point;
        for (auto iter = open_map_.begin(); iter != open_map_.end(); iter++) {
            temp_point.x         = iter->second.x;
            temp_point.y         = iter->second.y;
            temp_point.z         = iter->second.z;
            temp_point.angle     = iter->second.angle;
            temp_point.direction = (iter->second.direction == Backward) ? Forward : Backward;
            expandpoint.push_back(temp_point);
        }
        for (auto iter = close_map_.begin(); iter != close_map_.end(); iter++) {
            temp_point.x         = iter->second.x;
            temp_point.y         = iter->second.y;
            temp_point.z         = iter->second.z;
            temp_point.angle     = iter->second.angle;
            temp_point.direction = (iter->second.direction == Backward) ? Forward : Backward;
            expandpoint.push_back(temp_point);
        }
        // cout << "GetExpandPoint--expandpoint.size():" << expandpoint.size() << endl;

        return expandpoint;
    }
    /**
     * @brief 取出H值查询表函数
     * @return 返回说明：
     * 返回H值查询表
     */
    inline unordered_map<unsigned int, double> GetHCostMap() {
        for (auto iter = nodes2D_map_.begin(); iter != nodes2D_map_.end(); iter++) {
            // if(iter->second.isClosed())
            h_cost_map_[iter->first] = iter->second.getG();
        }

        return h_cost_map_;
    }
    /**
     * @brief 打印版本号
     */
    static void PrintVersion() {
        std::cout << "Path Version：2.1" << std::endl;
    }
    Point midpoint_;

  public:
    std::shared_ptr<spdlog::logger> threadLogger_;
    bool**                          binMap = nullptr;
    int                             width;
    int                             height;
    bool                            use_voronoi = false;


  private:
    RSCurve   my_r_s_curve;
    RSCurve_H my_r_s_curve_h;
    Dubins    dubins_;

    double           voronoi_origin_x, voronoi_origin_y; // 记录voronoi图的原点
    Path_Opti        my_path_opti;
    CollisonCheck    collison_check_;
    PlanRule         plan_path_rule_;
    FittingDirection fitting_direction_;
    bool             flag_dubins_; // 采用dubins曲线计算启发值标志

    Point start_, actual_start_;
    Point end_, end_f_, end_r_;

    Path path_a_star_, path_r_s_;

    vector<Coordinate> v_road_outer_bound_, v_road_inner_bound_; // hybridA*规划框定的地图外边界和内边界
    Bound              init_road_bound_, init_obstacle_bound_;
    Bound              offset_road_bound_, offset_obstacle_bound_;
    Bound              voronoi_bound_;
    DynamicVoronoi*    voronoiDiagram;

    MotionDirection start_d_, end_d_; // 结束拓展方向

    /// Hybrid A*
    unordered_map<unsigned long long, Vertex3D> close_map_;  // 混合A星算法的close集
    unordered_map<unsigned long long, Vertex3D> open_map_;   // 混合A星算法的open集
    multimap<double, Vertex3D>                  open_map_f_; // 基于f值升序排列的open集优先队列
    unordered_map<unsigned int, double>         h_cost_map_; // 地图网格的位置和h值的映射关系

    /// A*
    unordered_map<unsigned long long, Node2D> nodes2D_map_; // 存儲所有搜索得到的节点
    set<unsigned long long>                   nodes2D_set_; // open集

    unordered_set<unsigned int> bound_set_, bound_set_for_Astar_; // 边界的整数坐标形式

    vector<int> box_index_;
    int         All;

}; // end class optimal_path

} // namespace GlobalPlanning

#endif // OPTIMAL_PATH_H
