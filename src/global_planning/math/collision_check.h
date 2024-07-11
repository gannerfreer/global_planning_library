#ifndef COLLISION_CHECK_H
#define COLLISION_CHECK_H

#include "general_class.h"
#include "../os/os.h"
#include "../util/TimeHelper.h"
#include "constants.h"

using namespace HybridAStar::Constants;
namespace HybridAStar
{
    /**
     * @brief 路径规划中碰撞检测类
     */
    class CollisonCheck
    {
    public:
        explicit CollisonCheck()
        {
            time_couter_.SetHeader("碰撞检测.");
        } // 默认构造函数
        ~CollisonCheck()
        {
        } // 析构函数
        void InitParam(vehicle_param m_vehicle_param);
        /**
         * @brief 初始化地图边界函数
         * @param[in] road_bound 地图边界点
         * @return 返回说明：无
         */
        void InitBoundMap(const Bound road_bound);
        /**
         * @brief 初始化障碍物边界函数
         * @param[in] obstacle_bound 障碍物边界点
         * @return 返回说明：无
         */
        void InitObstacleMap(const Bound obstacle_bound);
        /**
         * @brief 判断RS拟合路径是否跟边界碰撞函数
         * @param[in] my_rspath  RS路径
         * @return 返回说明：
         * true:  碰撞
         * false: 不碰撞
         */
        bool IsRSPathCollision(const Path my_rspath);
        /**
         * @brief 判断优化路径是否跟边界碰撞函数
         * @param[in] my_optipath  优化路径
         * @return 返回碰撞点索引
         */
        vector<uint32> OptiPathCollisionCheck(const Path my_optipath);
        /**
         * @brief 判断车辆位置是否跟边界碰撞函数
         * @param[in] my_point  路点位置
         * @return 返回说明：
         * true:  碰撞
         * false: 不碰撞
         */
        bool IsVehicleCollision(const Point my_point);

    private:
        /**
         * @brief 判断车辆位置是否跟地图边界碰撞函数
         * @param[in] my_point       路点位置
         * @param[in] safe_distance  车辆安全距离
         * @return 返回说明：
         * true:  碰撞
         * false: 不碰撞
         */
        bool IsVehicleCollisionRoadBound(const Point my_point, const float64 safe_distance);
        /**
         * @brief 判断车辆位置是否跟障碍物边界碰撞函数
         * @param[in] my_point       路点位置
         * @param[in] safe_distance  车辆安全距离
         * @return 返回说明：
         * true:  碰撞
         * false: 不碰撞
         */
        bool IsVehicleCollisionObstacleBound(const Point my_point, const float64 safe_distance);
        /**
         * @brief 判断点是否在矩形内函数
         * @param[in] p   待判断点坐标
         * @param[in] p1  矩形顶点坐标1
         * @param[in] p2  矩形顶点坐标2
         * @param[in] p2  矩形顶点坐标3
         * @param[in] p2  矩形顶点坐标4
         * @return 返回说明：
         * true:  点在矩形内
         * false: 点在矩形外
         */
        bool IsPointInMatrix(Coordinate p, Coordinate p1, Coordinate p2, Coordinate p3, Coordinate p4);
        /**
         * @brief 计算两向量叉乘函数
         * @param[in] p1  矩形边的端点坐标1
         * @param[in] p2  矩形边的端点坐标2
         * @param[in] p2  点坐标
         * @return 返回说明：
         * |p1 p2| X |p1 p|
         */
        float64 GetCross(Coordinate p1, Coordinate p2, Coordinate p);
        /**
         * @brief 将坐标形式转为哈希值函数
         * @param[in] point  点坐标
         * @return 返回说明：
         * 对应哈希值
         */
        inline uint32 Coordinate2Hash(const IntCoordinate point);

        vehicle_param m_vehicle_param_;

    private:
        unordered_map<uint32, vector<Coordinate>> road_bound_map_;     // 地图边界
        unordered_map<uint32, vector<Coordinate>> obstacle_bound_map_; // 障碍物边界
        utility::CTimeCounter time_couter_;                            // 计时对象

    }; // end class
} // end namespace

#endif // COLLISION_CHECK_H
