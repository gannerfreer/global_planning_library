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
#include <vector>
#include "ros/ros.h"
#include "nav_msgs/Path.h"
#include <sensor_msgs/PointCloud.h>
#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"
// #include "msg_decision_planning/TrajectoryPoint.h"

// Include personal lib.
#include "my_typedef.h"
#include "common_struct.h"
#include "c_map_analysis.h"
using namespace HybridAStar;
namespace rviz_path
{
  using std::vector;

  class CRvizPath
  {
  public:
    CRvizPath()
    {
      global_path1.header.frame_id = "map";
#if 0
    global_path2.header.frame_id = global_path3.header.frame_id
    = global_path4.header.frame_id = global_path5.header.frame_id = global_path6.header.frame_id
    = global_path7.header.frame_id = global_path8.header.frame_id = global_path9.header.frame_id
    = global_path10.header.frame_id = global_path11.header.frame_id = global_path12.header.frame_id = "map";
    local_path.header.frame_id="map";
#endif
      history_path.header.frame_id = "map";
      pub_global_path1 = n.advertise<nav_msgs::Path>("global_path1", 1);
      m_Publisher_rviz = n.advertise<visualization_msgs::Marker>("visualization_marker", 2);

#if 0
    pub_local_path = n.advertise<nav_msgs::Path>("local_path",1);
    
    pub_global_path2 = n.advertise<nav_msgs::Path>("global_path2",1);
    pub_global_path3 = n.advertise<nav_msgs::Path>("global_path3",1);
    pub_global_path4 = n.advertise<nav_msgs::Path>("global_path4",1);
    pub_global_path5 = n.advertise<nav_msgs::Path>("global_path5",1);
    pub_global_path6 = n.advertise<nav_msgs::Path>("global_path6",1);
    pub_global_path7 = n.advertise<nav_msgs::Path>("global_path7",1);
    pub_global_path8 = n.advertise<nav_msgs::Path>("global_path8",1);
    pub_global_path9 = n.advertise<nav_msgs::Path>("global_path9",1);
    pub_global_path10 = n.advertise<nav_msgs::Path>("global_path10",1);
    pub_global_path11 = n.advertise<nav_msgs::Path>("global_path11",1);
    pub_global_path12 = n.advertise<nav_msgs::Path>("global_path12",1);
#endif

      pub_history_path = n.advertise<nav_msgs::Path>("history_path", 1);

      vehicle_marker.header.frame_id = "map";
      vehicle_marker.ns = "my_namespace";
      vehicle_marker.id = 10;
      vehicle_marker.type = visualization_msgs::Marker::CUBE;
      vehicle_marker.action = visualization_msgs::Marker::ADD;
      vehicle_marker.color.a = 0.9;
      vehicle_marker.color.r = 1.0;
      vehicle_marker.color.g = 1.0;
      vehicle_marker.color.b = 0.0;
      vehicle_marker.scale.x = 2.00;
      vehicle_marker.scale.y = 1.40;
      vehicle_marker.scale.z = 1.48;
      vehicle_marker.lifetime = ros::Duration();
      pub_veh = n.advertise<visualization_msgs::Marker>("vehicle_marker", 1);

      preview_marker.header.frame_id = "map";
      preview_marker.ns = "my_namespace";
      preview_marker.id = 11;
      preview_marker.type = visualization_msgs::Marker::ARROW;
      preview_marker.action = visualization_msgs::Marker::ADD;
      preview_marker.color.a = 1.0;
      preview_marker.color.r = 0.0;
      preview_marker.color.g = 0.0;
      preview_marker.color.b = 1.0;
      preview_marker.scale.x = 4;
      preview_marker.scale.y = 0.1;
      preview_marker.scale.z = 0.1;
      preview_marker.lifetime = ros::Duration();
      pub_preview = n.advertise<visualization_msgs::Marker>("preview_marker", 1);

#if 1
      m_rviz_point.header.frame_id = "map";
      m_rviz_point.header.stamp = ros::Time::now();
      m_rviz_point.ns = "my_namespace";                      // 命名空间
      m_rviz_point.action = visualization_msgs::Marker::ADD; // 对标记的操作类型
      m_rviz_point.pose.orientation.w = 200.0;
      m_rviz_point.type = visualization_msgs::Marker::POINTS; // 标记的形状
      m_rviz_point.lifetime = ros::Duration(0);

      m_rviz_point.scale.x = 1;
      m_rviz_point.scale.y = 1;

      m_rviz_point.color.a = 1;
      m_rviz_point.color.g = 120;

#if 0
    global_ve_marker.header.frame_id = "map";
    global_ve_marker.header.stamp = ros::Time::now();
    global_ve_marker.ns = "my_namespace";        //命名空间
    global_ve_marker.action = visualization_msgs::Marker::ADD;   //对标记的操作类型
    global_ve_marker.pose.orientation.w = 10.0;
    global_ve_marker.type = visualization_msgs::Marker::POINTS; //标记的形状
    global_ve_marker.lifetime = ros::Duration(0);

    global_ve_marker.id = 1;

    global_ve_marker.scale.x = 5;
    global_ve_marker.scale.y = 1;

    global_ve_marker.color.a = 1;
    global_ve_marker.color.r = 120;
#endif
      // m_Publisher_global = n.advertise<visualization_msgs::Marker>("global_marker",2);

      global_path_now.header.frame_id = "map";
      global_path_now.ns = "my_namespace";
      global_path_now.type = visualization_msgs ::Marker ::POINTS;
      global_path_now.action = visualization_msgs ::Marker ::ADD;
      global_path_now.scale.x = 0.5;
      global_path_now.scale.y = 0.5;
      global_path_now.scale.z = 0.5;
      global_path_now.id = 20;
      global_path_now.color.a = 1.0;
      global_path_now.color.r = 1.0;
      global_path_now.color.g = 0.0;
      global_path_now.color.b = 1.0;

      turn_path_paragraph_now.header.frame_id = "map";
      turn_path_paragraph_now.ns = "my_namespace";
      turn_path_paragraph_now.type = visualization_msgs ::Marker ::POINTS;
      turn_path_paragraph_now.action = visualization_msgs ::Marker ::ADD;
      turn_path_paragraph_now.scale.x = 1.0;
      turn_path_paragraph_now.scale.y = 1.0;
      turn_path_paragraph_now.scale.z = 1.0;
      turn_path_paragraph_now.id = 21;
      turn_path_paragraph_now.color.a = 1.0;
      turn_path_paragraph_now.color.r = 1.0;
      turn_path_paragraph_now.color.g = 1.0;
      turn_path_paragraph_now.color.b = 0.0;

      turn_path_paragraph_another.header.frame_id = "map";
      turn_path_paragraph_another.ns = "my_namespace";
      turn_path_paragraph_another.type = visualization_msgs ::Marker ::POINTS;
      turn_path_paragraph_another.action = visualization_msgs ::Marker ::ADD;
      turn_path_paragraph_another.scale.x = 1.0;
      turn_path_paragraph_another.scale.y = 1.0;
      turn_path_paragraph_another.scale.z = 1.0;
      turn_path_paragraph_another.id = 22;
      turn_path_paragraph_another.color.a = 1.0;
      turn_path_paragraph_another.color.r = 0.0;
      turn_path_paragraph_another.color.g = 1.0;
      turn_path_paragraph_another.color.b = 1.0;

      m_Publisher_global = n.advertise<visualization_msgs ::Marker>("path_global", 1);
      m_Publisher_turn_path_paragraph = n.advertise<visualization_msgs ::Marker>("path_turn_paragraph", 1);
      m_Publisher_turn_path_paragraph_another = n.advertise<visualization_msgs ::Marker>("path_turn_paragraph_another", 1);

#endif

      pub_area_path = n.advertise<sensor_msgs ::PointCloud>("area_points", 1);
      area_points.header.frame_id = "map";

      start.header.frame_id = "map";
      start.ns = "my_namespace";
      start.type = visualization_msgs::Marker::ARROW;
      start.action = visualization_msgs::Marker::ADD;

      end.header.frame_id = "map";
      end.ns = "my_namespace";
      end.type = visualization_msgs::Marker::ARROW;
      end.action = visualization_msgs::Marker::ADD;

      pub_start = n.advertise<visualization_msgs::Marker>("start", 1);
      pub_end = n.advertise<visualization_msgs::Marker>("end", 1);
      pub_h_value_map = n.advertise<visualization_msgs::MarkerArray>("/h_value_map", 1);
    };
    void SetGlobalPath1(vector<GlobalPlanning::Trajectory_Point> path_);
    void Set2DCostMap(const unordered_map<uint32, float64> cost_map, Point midpoint_);
#if 0
  
  void SetGlobalPath2(vector<msg_v_trajectory :: Trajectory> path_);
  void SetGlobalPath3(vector<msg_v_trajectory :: Trajectory> path_);
  void SetGlobalPath4(vector<msg_v_trajectory :: Trajectory> path_);
  void SetGlobalPath5(vector<msg_v_trajectory :: Trajectory> path_);
  void SetGlobalPath6(vector<msg_v_trajectory :: Trajectory> path_);
  void SetGlobalPath7(vector<msg_v_trajectory :: Trajectory> path_);
  void SetGlobalPath8(vector<msg_v_trajectory :: Trajectory> path_);
  void SetGlobalPath9(vector<msg_v_trajectory :: Trajectory> path_);
  void SetGlobalPath10(vector<msg_v_trajectory :: Trajectory> path_);
  void SetGlobalPath11(vector<msg_v_trajectory :: Trajectory> path_);
  void SetGlobalPath12(vector<msg_v_trajectory :: Trajectory> path_);

  void SetLocalPath(vector<msg_v_trajectory :: Trajectory> path_);
#endif

    void SetHistoryPath(float64 x, float64 y);
    void SetVehiclePosition(float64 x, float64 y, float64 yaw_angle);
    void SetPreviewMarker(float64 x_p, float64 y_p, float64 yaw_angle_p);
    void SetAreaPath(vector<geometry_msgs ::Point> &vec_msga);

    struct Point2d
    {
      float64 x;
      float64 y;
    };

  private:
    ros::NodeHandle n;               // Main access to ROS system.
    nav_msgs::Path history_path;     // for reference path
    ros::Publisher pub_global_path1; // for publish optimize path
    nav_msgs::Path global_path1;
    sensor_msgs::PointCloud area_points;
    std ::vector<Point2d> area_path;
    visualization_msgs ::Marker global_path_now, turn_path_paragraph_now, turn_path_paragraph_another;
    ros ::Publisher m_Publisher_rviz;
    visualization_msgs::MarkerArray h_value_map;
#if 0
  nav_msgs::Path global_path1,global_path2,global_path3,global_path4,global_path5,global_path6,global_path7,
                 global_path8,global_path9,global_path10,global_path11,global_path12;                  // for optimized path
  nav_msgs::Path local_path;
  
  ros::Publisher pub_global_path2;
  ros::Publisher pub_global_path3;
  ros::Publisher pub_global_path4;
  ros::Publisher pub_global_path5;
  ros::Publisher pub_global_path6;
  ros::Publisher pub_global_path7;
  ros::Publisher pub_global_path8;
  ros::Publisher pub_global_path9;
  ros::Publisher pub_global_path10;
  ros::Publisher pub_global_path11;
  ros::Publisher pub_global_path12;
  ros::Publisher pub_local_path;
#endif
    ros::Publisher pub_history_path;           // for publish left-bound road
    visualization_msgs::Marker vehicle_marker; // for vehicle
    visualization_msgs::Marker preview_marker; // for previewpoint

    ros::Publisher pub_veh;
    ros::Publisher pub_preview;

    // 园区 rviz
  private:
    visualization_msgs ::Marker m_rviz_point;
    ros::Publisher pub_area_path;
    // ros :: Publisher m_Publisher_Global_Plan;

    // vector<geometry_msgs::Point> m_vec_global;
    // vector<geometry_msgs::Point> m_vec_out_border,m_vec_globaltest;

  private:
    // nav_msgs::Path global_path_vec;
    // ros::Publisher pub_global_path_vec;

    // std :: vector<visualization_msgs :: Marker> global_ve_marker;
    visualization_msgs ::Marker global_ve_marker;
    visualization_msgs ::MarkerArray global_MarkerArrat;
    ros ::Publisher m_Publisher_global, m_Publisher_turn_path_paragraph, m_Publisher_turn_path_paragraph_another;
    visualization_msgs ::MarkerArray path_global;

  private:
    visualization_msgs::Marker start; // for start point
    visualization_msgs::Marker end;   // for start point
    ros::Publisher pub_start;
    ros::Publisher pub_end;
    ros::Publisher pub_h_value_map;

  public:
    void PeripheryPark(int id, vector<geometry_msgs ::Point> &vec_msga);
    void SetGlobalPath_All(vector<geometry_msgs ::Point> &path_);
    void PubGlobalPath(std::vector<Trajectory_Point> &path);
    void PubTurningPathParagraph(std::vector<Trajectory_Point> &path);
    void PubTurningPathParagraphAnother(std::vector<Trajectory_Point> &path);

    void SetStartPosition(float64 x, float64 y, float64 yaw_angle);
    void SetEndPosition(float64 x, float64 y, float64 yaw_angle);
    void PublishStart();
    void PublishEnd();

    // const float64 x_o_ = -1171.654151;//玖智
    // const float64 y_o_ = 6205.765819;//

    // const float64 x_o_ = -321737.4857;     // 舒兰
    // const float64 y_o_ = 534463.584699999; // 舒兰

   
    const float64 x_o_ = 0; //鲁南
    const float64 y_o_ = 0; //鲁南

    // const float64 x_o_ = -205293.9231; // 致富
    // const float64 y_o_ = 7973.5012;    // 致富
  };
}
#endif // PATH_TEST_IPOPT_C_RVIZ_PATH_H
