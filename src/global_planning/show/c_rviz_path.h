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
        m_Publisher_global     = n.advertise<visualization_msgs::Marker>("path_global", 1);
        m_Publisher_road_node_ = n.advertise<sensor_msgs ::PointCloud>("road_node", 1);

        pub_area_path   = n.advertise<sensor_msgs ::PointCloud>("area_points", 1);
        pub_start       = n.advertise<visualization_msgs::Marker>("start", 1);
        pub_end         = n.advertise<visualization_msgs::Marker>("end", 1);
        pub_h_value_map = n.advertise<visualization_msgs::MarkerArray>("/h_value_map", 1);


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


        road_nodes_.header.frame_id = "map";
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
    void Pub2DCostMap(const unordered_map<unsigned int, double> cost_map, Point midpoint_);


    void PubMapborderAndReferenceline(vector<geometry_msgs::Point>& vec_msga);


    void PubGlobalPath(std::vector<_TrajectoryPoint>& path);
    void PubRoadNode(vector<geometry_msgs::Point>& path);

    void PubStartPosition(double x, double y, double yaw_angle);
    void PubEndPosition(double x, double y, double yaw_angle);

  public:
    // const double x_o_ = -321737.4857;     // 舒兰
    // const double y_o_ = 534463.584699999; // 舒兰

    const double x_o_ = -299; // 鲁南
    const double y_o_ = 920;  // 鲁南

  private:
    ros::NodeHandle n;
    ros::Publisher  pub_area_path, m_Publisher_global, m_Publisher_road_node_, pub_end, pub_h_value_map, pub_start;
    sensor_msgs::PointCloud         area_points, road_nodes_;
    visualization_msgs::Marker      global_path_now, start, end;
    visualization_msgs::MarkerArray h_value_map;
};
} // namespace rviz_path
#endif // PATH_TEST_IPOPT_C_RVIZ_PATH_H