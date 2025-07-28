#ifndef GENERATE_TEST_DATA
#define GENERATE_TEST_DATA

#include "../../common/common_struct.h"
namespace GenTestData {
#include <cmath>
#include <vector>

#include "../../common/common_struct.h"

constexpr double PI = 3.14159265358979323846;

// 生成直线+圆弧轨迹
void GenerateLineArcTrajectory(double                                         start_x,         // 直线起点x坐标
                               double                                         start_y,         // 直线起点y坐标
                               double                                         start_yaw,       // 直线起点朝向角(弧度)
                               double                                         line_length,     // 直线长度(m)
                               double                                         arc_length,      // 圆弧长度(m)
                               double                                         arc_radius,      // 圆弧半径(m)
                               double                                         point_interval,  // 点间距(m)
                               std::vector<GlobalPlanning::_TrajectoryPoint>& line_points,     // 输出：直线点集
                               std::vector<GlobalPlanning::_TrajectoryPoint>& arc_points,      // 输出：圆弧点集
                               GlobalPlanning::_SinglePoint&                  arc_center,      // 输出：圆弧圆心
                               double&                                        final_arc_radius // 输出：圆弧半径(可能与输入不同)
) {
    // 清空输出容器
    line_points.clear();
    arc_points.clear();

    // ========== 1. 生成直线部分 ==========
    int    line_point_num = static_cast<int>(line_length / point_interval) + 1;
    double delta_s        = line_length / (line_point_num - 1);

    for (int i = 0; i < line_point_num; ++i) {
        double                           s = i * delta_s;
        GlobalPlanning::_TrajectoryPoint point;
        point.x         = start_x + s * cos(start_yaw);
        point.y         = start_y + s * sin(start_yaw);
        point.yaw       = start_yaw;
        point.curvature = 0.0; // 直线曲率为0
        line_points.push_back(point);
    }

    // ========== 2. 计算圆弧参数 ==========
    // 直线终点（也是圆弧起点）
    double line_end_x = start_x + line_length * cos(start_yaw);
    double line_end_y = start_y + line_length * sin(start_yaw);

    // 计算圆弧圆心位置（保证与直线相切）
    // 根据转向方向确定圆心位置（假设direction=0为前进，1为后退）
    // 这里假设左转（圆心在直线左侧）
    arc_center.x   = line_end_x - arc_radius * sin(start_yaw);
    arc_center.y   = line_end_y + arc_radius * cos(start_yaw);
    arc_center.yaw = 0.0; // 圆心朝向无意义

    // 调整实际圆弧半径（可能与输入不同）
    final_arc_radius         = std::abs(arc_radius);
    double actual_arc_length = arc_length;

    // ========== 3. 生成圆弧部分 ==========
    int    arc_point_num = static_cast<int>(arc_length / point_interval) + 1;
    double delta_theta   = -arc_length / final_arc_radius / (arc_point_num - 1);

    // 圆弧起始角度（直线方向的垂直方向）
    double start_angle = start_yaw + (arc_radius > 0 ? -PI / 2.0 : PI / 2.0);

    for (int i = 0; i < arc_point_num; ++i) {
        double                           theta = i * delta_theta;
        GlobalPlanning::_TrajectoryPoint point;

        // 圆弧上的点坐标
        point.x = arc_center.x + final_arc_radius * cos(start_angle + (arc_radius > 0 ? -theta : theta));
        point.y = arc_center.y + final_arc_radius * sin(start_angle + (arc_radius > 0 ? -theta : theta));

        // 朝向角（切线方向）
        point.yaw = start_yaw + (arc_radius > 0 ? -theta : theta);
        // 规范化角度到[0, 2π]
        while (point.yaw < 0) point.yaw += 2 * PI;
        while (point.yaw > 2 * PI) point.yaw -= 2 * PI;

        point.curvature = 1.0 / final_arc_radius; // 曲率为半径倒数
        arc_points.push_back(point);
    }
}
} // namespace GenTestData

#endif
