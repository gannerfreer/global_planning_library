/*******************************************************************/
/*                      Author: xubiao                             */
/*                     Contact: xubiao@hnu.edu.cn                  */
/*                 Last update: 2019-07-03                         */
/*******************************************************************/

/*
  Description: The header file for C++ class CRvizPath
  The class includes all the necessary vars and funcs for showing path and obstacle in rviz.
*/

// Syntax: <package name>_<type>_<file name>_H
#ifndef PATH_TEST_IPOPT_C_RVIZ_PATH_H
#define PATH_TEST_IPOPT_C_RVIZ_PATH_H

// Include system lib.
#include <sensor_msgs/PointCloud.h>

#include <vector>

#include "nav_msgs/Path.h"
#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"
// #include "msg_decision_planning/TrajectoryPoint.h"

// Include personal lib.
#include "../common/common_struct.h"
#include "../map/c_map_analysis.h"
using namespace GlobalPlanning;
namespace rviz_path {
using std::vector;

class CRvizPath {
  public:
    CRvizPath() {
        global_path1.header.frame_id = "map";

        history_path.header.frame_id    = "map";
        pub_global_path1                = n.advertise<nav_msgs::Path>("global_path1", 1);
        m_Publisher_rviz                = n.advertise<visualization_msgs::Marker>("visualization_marker", 2);
        pub_history_path                = n.advertise<nav_msgs::Path>("history_path", 1);
        pub_veh                         = n.advertise<visualization_msgs::Marker>("vehicle_marker", 1);
        pub_preview                     = n.advertise<visualization_msgs::Marker>("preview_marker", 1);
        m_Publisher_global              = n.advertise<visualization_msgs::Marker>("path_global", 1);
        m_Publisher_turn_path_paragraph = n.advertise<visualization_msgs::Marker>("path_turn_paragraph", 1);
        m_Publisher_turn_path_paragraph_another =
            n.advertise<visualization_msgs::Marker>("path_turn_paragraph_another", 1);
        pub_area_path   = n.advertise<sensor_msgs ::PointCloud>("area_points", 1);
        pub_start       = n.advertise<visualization_msgs::Marker>("start", 1);
        pub_end         = n.advertise<visualization_msgs::Marker>("end", 1);
        pub_h_value_map = n.advertise<visualization_msgs::MarkerArray>("/h_value_map", 1);


        vehicle_marker.header.frame_id = "map";
        vehicle_marker.ns              = "my_namespace";
        vehicle_marker.id              = 10;
        vehicle_marker.type            = visualization_msgs::Marker::CUBE;
        vehicle_marker.action          = visualization_msgs::Marker::ADD;
        vehicle_marker.color.a         = 0.9;
        vehicle_marker.color.r         = 1.0;
        vehicle_marker.color.g         = 1.0;
        vehicle_marker.color.b         = 0.0;
        vehicle_marker.scale.x         = 2.00;
        vehicle_marker.scale.y         = 1.40;
        vehicle_marker.scale.z         = 1.48;
        vehicle_marker.lifetime        = ros::Duration();


        preview_marker.header.frame_id = "map";
        preview_marker.ns              = "my_namespace";
        preview_marker.id              = 11;
        preview_marker.type            = visualization_msgs::Marker::ARROW;
        preview_marker.action          = visualization_msgs::Marker::ADD;
        preview_marker.color.a         = 1.0;
        preview_marker.color.r         = 0.0;
        preview_marker.color.g         = 0.0;
        preview_marker.color.b         = 1.0;
        preview_marker.scale.x         = 4;
        preview_marker.scale.y         = 0.1;
        preview_marker.scale.z         = 0.1;
        preview_marker.lifetime        = ros::Duration();


        m_rviz_point.header.frame_id    = "map";
        m_rviz_point.header.stamp       = ros::Time::now();
        m_rviz_point.ns                 = "my_namespace";                  // 命名空间
        m_rviz_point.action             = visualization_msgs::Marker::ADD; // 对标记的操作类型
        m_rviz_point.pose.orientation.w = 200.0;
        m_rviz_point.type               = visualization_msgs::Marker::POINTS; // 标记的形状
        m_rviz_point.lifetime           = ros::Duration(0);

        m_rviz_point.scale.x = 1;
        m_rviz_point.scale.y = 1;

        m_rviz_point.color.a = 1;
        m_rviz_point.color.g = 120;


        // m_Publisher_global = n.advertise<visualization_msgs::Marker>("global_marker",2);

        global_path_now.header.frame_id = "map";
        global_path_now.ns              = "my_namespace";
        global_path_now.type            = visualization_msgs::Marker ::POINTS;
        global_path_now.action          = visualization_msgs::Marker ::ADD;
        global_path_now.scale.x         = 0.5;
        global_path_now.scale.y         = 0.5;
        global_path_now.scale.z         = 0.5;
        global_path_now.id              = 20;
        global_path_now.color.a         = 1.0;
        global_path_now.color.r         = 1.0;
        global_path_now.color.g         = 0.0;
        global_path_now.color.b         = 1.0;

        turn_path_paragraph_now.header.frame_id = "map";
        turn_path_paragraph_now.ns              = "my_namespace";
        turn_path_paragraph_now.type            = visualization_msgs::Marker ::POINTS;
        turn_path_paragraph_now.action          = visualization_msgs::Marker ::ADD;
        turn_path_paragraph_now.scale.x         = 1.0;
        turn_path_paragraph_now.scale.y         = 1.0;
        turn_path_paragraph_now.scale.z         = 1.0;
        turn_path_paragraph_now.id              = 21;
        turn_path_paragraph_now.color.a         = 1.0;
        turn_path_paragraph_now.color.r         = 1.0;
        turn_path_paragraph_now.color.g         = 1.0;
        turn_path_paragraph_now.color.b         = 0.0;

        turn_path_paragraph_another.header.frame_id = "map";
        turn_path_paragraph_another.ns              = "my_namespace";
        turn_path_paragraph_another.type            = visualization_msgs::Marker ::POINTS;
        turn_path_paragraph_another.action          = visualization_msgs::Marker ::ADD;
        turn_path_paragraph_another.scale.x         = 1.0;
        turn_path_paragraph_another.scale.y         = 1.0;
        turn_path_paragraph_another.scale.z         = 1.0;
        turn_path_paragraph_another.id              = 22;
        turn_path_paragraph_another.color.a         = 1.0;
        turn_path_paragraph_another.color.r         = 0.0;
        turn_path_paragraph_another.color.g         = 1.0;
        turn_path_paragraph_another.color.b         = 1.0;


        area_points.header.frame_id = "map";

        start.header.frame_id = "map";
        start.ns              = "my_namespace";
        start.type            = visualization_msgs::Marker::ARROW;
        start.action          = visualization_msgs::Marker::ADD;

        end.header.frame_id = "map";
        end.ns              = "my_namespace";
        end.type            = visualization_msgs::Marker::ARROW;
        end.action          = visualization_msgs::Marker::ADD;
    };
    void SetGlobalPath1(vector<_TrajectoryPoint> path_);
    void Set2DCostMap(const unordered_map<unsigned int, double> cost_map, Point midpoint_);


    void SetHistoryPath(double x, double y);
    void SetVehiclePosition(double x, double y, double yaw_angle);
    void SetPreviewMarker(double x_p, double y_p, double yaw_angle_p);
    void SetAreaPath(vector<geometry_msgs ::Point>& vec_msga);

    struct Point2d {
        double x;
        double y;
    };
    void PeripheryPark(int id, vector<geometry_msgs ::Point>& vec_msga);
    void SetGlobalPath_All(vector<geometry_msgs ::Point>& path_);
    void PubGlobalPath(std::vector<_TrajectoryPoint>& path);
    void PubTurningPathParagraph(std::vector<_TrajectoryPoint>& path);
    void PubTurningPathParagraphAnother(std::vector<_TrajectoryPoint>& path);

    void SetStartPosition(double x, double y, double yaw_angle);
    void SetEndPosition(double x, double y, double yaw_angle);
    void PublishStart();
    void PublishEnd();

  public:
    // const double x_o_ = -321737.4857;     // 舒兰
    // const double y_o_ = 534463.584699999; // 舒兰

    const double x_o_ = -299; // 鲁南
    const double y_o_ = 920;  // 鲁南

  private:
    ros::NodeHandle n;
    nav_msgs::Path  history_path, global_path1;
    ros::Publisher  pub_global_path1, m_Publisher_rviz, pub_history_path, pub_veh, pub_area_path, pub_preview,
        m_Publisher_global, m_Publisher_turn_path_paragraph, m_Publisher_turn_path_paragraph_another, pub_end,
        pub_h_value_map, pub_start;
    sensor_msgs::PointCloud    area_points;
    std ::vector<Point2d>      area_path;
    visualization_msgs::Marker global_path_now, turn_path_paragraph_now, turn_path_paragraph_another, vehicle_marker,
        m_rviz_point, global_ve_marker, start, preview_marker, end;
    visualization_msgs::MarkerArray h_value_map, global_MarkerArrat, path_global;
};
} // namespace rviz_path
#endif // PATH_TEST_IPOPT_C_RVIZ_PATH_H