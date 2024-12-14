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
        publisher_global_path_  = n.advertise<visualization_msgs::Marker>("path_global", 1);
        publisher_expand_point_ = n.advertise<visualization_msgs::Marker>("point_expand", 1);
        m_Publisher_road_node_  = n.advertise<sensor_msgs ::PointCloud>("road_node", 1);

        pub_area_path   = n.advertise<sensor_msgs ::PointCloud>("area_points", 1);
        pub_start       = n.advertise<visualization_msgs::Marker>("start", 1);
        pub_end         = n.advertise<visualization_msgs::Marker>("end", 1);
        pub_h_value_map = n.advertise<visualization_msgs::MarkerArray>("/h_value_map", 1);
        pub_obstacle_   = n.advertise<sensor_msgs ::PointCloud>("obstacle_points", 1);


        global_path_now_.header.frame_id = "map";
        global_path_now_.ns              = "my_namespace";
        global_path_now_.type            = visualization_msgs::Marker ::POINTS;
        global_path_now_.action          = visualization_msgs::Marker ::ADD;
        global_path_now_.scale.x         = 0.5;
        global_path_now_.scale.y         = 0.5;
        global_path_now_.scale.z         = 0.5;
        global_path_now_.id              = 20;
        global_path_now_.color.a         = 1.0;
        global_path_now_.color.r         = 1.0;
        global_path_now_.color.g         = 0.0;
        global_path_now_.color.b         = 1.0;

        expand_point_now_.header.frame_id = "map";
        expand_point_now_.ns              = "my_namespace";
        expand_point_now_.type            = visualization_msgs::Marker ::POINTS;
        expand_point_now_.action          = visualization_msgs::Marker ::ADD;
        expand_point_now_.scale.x         = 0.5;
        expand_point_now_.scale.y         = 0.5;
        expand_point_now_.scale.z         = 0.5;
        expand_point_now_.id              = 21;
        expand_point_now_.color.a         = 1.0;
        expand_point_now_.color.r         = 1.0;
        expand_point_now_.color.g         = 1.0;
        expand_point_now_.color.b         = 0.0;


        road_nodes_.header.frame_id      = "map";
        area_points.header.frame_id      = "map";
        obstacle_points_.header.frame_id = "map";

        start.header.frame_id = "map";
        start.ns              = "my_namespace";
        start.type            = visualization_msgs::Marker::ARROW;
        start.action          = visualization_msgs::Marker::ADD;

        end.header.frame_id = "map";
        end.ns              = "my_namespace";
        end.type            = visualization_msgs::Marker::ARROW;
        end.action          = visualization_msgs::Marker::ADD;
    };
    void Pub2DCostMap(const unordered_map<unsigned int, double>& cost_map, Point midpoint_);


    void PubMapborderAndReferenceline(vector<geometry_msgs::Point>& vec_msga);


    void PubGlobalPath(std::vector<_TrajectoryPoint>& path);
    void PubRoadNode(vector<geometry_msgs::Point>& path);

    void PubStartPosition(double x, double y, double yaw_angle);
    void PubEndPosition(double x, double y, double yaw_angle);

    void PubExpandPoint(std::vector<Point>& path, Point mid_point);
    void PubObstacles(vector<geometry_msgs::Point>& vec_msga);

  public:
    const double x_o_ = -94; // 园区偏移参数
    const double y_o_ = 173; // 园区偏移参数
  private:
    ros::NodeHandle                 n;
    ros::Publisher                  pub_obstacle_, pub_area_path, publisher_global_path_, publisher_expand_point_, m_Publisher_road_node_, pub_end, pub_h_value_map, pub_start;
    sensor_msgs::PointCloud         area_points, road_nodes_, obstacle_points_;
    visualization_msgs::Marker      global_path_now_, start, end, expand_point_now_;
    visualization_msgs::MarkerArray h_value_map;
};
} // namespace rviz_path
#endif // PATH_TEST_IPOPT_C_RVIZ_PATH_H