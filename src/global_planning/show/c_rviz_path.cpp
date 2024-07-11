/*******************************************************************/
/*                      Author: xubiao                             */
/*                     Contact: xubiao@hnu.edu.cn                  */
/*                 Last update: 2019-05-30                         */
/*******************************************************************/

/*
  Description: The header file for C++ class CRvizPath
  The class includes all the necessary vars and funcs for showing path and obstacle in rviz.
*/

#include "../include/c_rviz_path.h"
#include "../include/color.h"
#include "../include/general_class.h"
#include "string.h"

namespace rviz_path
{
#if 0
  void CRvizPath::SetGlobalPath1(vector<msg_v_trajectory :: Trajectory> path_)
  {
    geometry_msgs::PoseStamped this_pose_stamped; 
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id="path1"; 
    global_path1.poses.clear();
    for(int32 i =0; i<path_.size(); i++)
    {
      if (i%10 == 0)
      {
        this_pose_stamped.pose.position.x = path_.at(i).x; 
        this_pose_stamped.pose.position.y = path_.at(i).y; 
        global_path1.poses.push_back(this_pose_stamped);
      }
    }
    global_path1.header.stamp = ros::Time::now();
    //std :: cout << "global_path1.size() is :"<< path_.size()<<"\n";
    pub_global_path1.publish(global_path1);
  }

    void CRvizPath::SetGlobalPath2(vector<msg_v_trajectory :: Trajectory> path_)
  {
    geometry_msgs::PoseStamped this_pose_stamped; 
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id="path2"; 
    global_path2.poses.clear();
    for(int32 i =0; i<path_.size(); i++)
    {
      if (i%10 == 0)
      {
        this_pose_stamped.pose.position.x = path_.at(i).x; 
        this_pose_stamped.pose.position.y = path_.at(i).y; 
        global_path2.poses.push_back(this_pose_stamped);
      }
    }
    global_path2.header.stamp = ros::Time::now();
    //std :: cout << "global_path2.size() is :"<< path_.size()<<"\n";
    pub_global_path2.publish(global_path2);
  }

    void CRvizPath::SetGlobalPath3(vector<msg_v_trajectory :: Trajectory> path_)
  {
    geometry_msgs::PoseStamped this_pose_stamped; 
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id="path3"; 
    global_path3.poses.clear();
    for(int32 i =0; i<path_.size(); i++)
    {
      if (i%10 == 0)
      {
        this_pose_stamped.pose.position.x = path_.at(i).x; 
        this_pose_stamped.pose.position.y = path_.at(i).y; 
        global_path3.poses.push_back(this_pose_stamped);
      }
    }
    global_path3.header.stamp = ros::Time::now();
    //std :: cout << "global_path3.size() is :"<< path_.size()<<"\n";
    pub_global_path3.publish(global_path3);
  }

    void CRvizPath::SetGlobalPath4(vector<msg_v_trajectory :: Trajectory> path_)
  {
    geometry_msgs::PoseStamped this_pose_stamped; 
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id="path4"; 
    global_path4.poses.clear();
    for(int32 i =0; i<path_.size(); i++)
    {
      if (i%10 == 0)
      {
        this_pose_stamped.pose.position.x = path_.at(i).x; 
        this_pose_stamped.pose.position.y = path_.at(i).y; 
        global_path4.poses.push_back(this_pose_stamped);
      }
    }
    global_path4.header.stamp = ros::Time::now();
    //std :: cout << "global_path4.size() is :"<< path_.size()<<"\n";
    pub_global_path4.publish(global_path4);
  }

    void CRvizPath::SetGlobalPath5(vector<msg_v_trajectory :: Trajectory> path_)
  {
    geometry_msgs::PoseStamped this_pose_stamped; 
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id="path5"; 
    global_path5.poses.clear();
    for(int32 i =0; i<path_.size(); i++)
    {
      if (i%10 == 0)
      {
        this_pose_stamped.pose.position.x = path_.at(i).x; 
        this_pose_stamped.pose.position.y = path_.at(i).y; 
        global_path5.poses.push_back(this_pose_stamped);
      }
    }
    global_path5.header.stamp = ros::Time::now();
    //std :: cout << "global_path5.size() is :"<< path_.size()<<"\n";
    pub_global_path5.publish(global_path5);
  }

    void CRvizPath::SetGlobalPath6(vector<msg_v_trajectory :: Trajectory> path_)
  {
    geometry_msgs::PoseStamped this_pose_stamped; 
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id="path6"; 
    global_path6.poses.clear();
    for(int32 i =0; i<path_.size(); i++)
    {
      if (i%10 == 0)
      {
        this_pose_stamped.pose.position.x = path_.at(i).x; 
        this_pose_stamped.pose.position.y = path_.at(i).y; 
        global_path6.poses.push_back(this_pose_stamped);
      }
    }
    global_path6.header.stamp = ros::Time::now();
    //std :: cout << "global_path6.size() is :"<< path_.size()<<"\n";
    pub_global_path6.publish(global_path6);
  }

    void CRvizPath::SetGlobalPath7(vector<msg_v_trajectory :: Trajectory> path_)
  {
    geometry_msgs::PoseStamped this_pose_stamped; 
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id="path7"; 
    global_path7.poses.clear();
    for(int32 i =0; i<path_.size(); i++)
    {
      if (i%10 == 0)
      {
        this_pose_stamped.pose.position.x = path_.at(i).x; 
        this_pose_stamped.pose.position.y = path_.at(i).y; 
        global_path7.poses.push_back(this_pose_stamped);
      }
    }
    global_path7.header.stamp = ros::Time::now();
    //std :: cout << "global_path7.size() is :"<< path_.size()<<"\n";
    pub_global_path7.publish(global_path7);
  }

    void CRvizPath::SetGlobalPath8(vector<msg_v_trajectory :: Trajectory> path_)
  {
    geometry_msgs::PoseStamped this_pose_stamped; 
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id="path8"; 
    global_path8.poses.clear();
    for(int32 i =0; i<path_.size(); i++)
    {
      if (i%10 == 0)
      {
        this_pose_stamped.pose.position.x = path_.at(i).x; 
        this_pose_stamped.pose.position.y = path_.at(i).y; 
        global_path8.poses.push_back(this_pose_stamped);
      }
    }
    global_path8.header.stamp = ros::Time::now();
    //std :: cout << "global_path8.size() is :"<< path_.size()<<"\n";
    pub_global_path8.publish(global_path8);
  }

    void CRvizPath::SetGlobalPath9(vector<msg_v_trajectory :: Trajectory> path_)
  {
    geometry_msgs::PoseStamped this_pose_stamped; 
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id="path9"; 
    global_path9.poses.clear();
    for(int32 i =0; i<path_.size(); i++)
    {
      if (i%10 == 0)
      {
        this_pose_stamped.pose.position.x = path_.at(i).x; 
        this_pose_stamped.pose.position.y = path_.at(i).y; 
        global_path9.poses.push_back(this_pose_stamped);
      }
    }
    global_path9.header.stamp = ros::Time::now();
    //std :: cout << "global_path9.size() is :"<< path_.size()<<"\n";
    pub_global_path9.publish(global_path9);
  }

    void CRvizPath::SetGlobalPath10(vector<msg_v_trajectory :: Trajectory> path_)
  {
    geometry_msgs::PoseStamped this_pose_stamped; 
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id="path10"; 
    global_path10.poses.clear();
    for(int32 i =0; i<path_.size(); i++)
    {
      if (i%10 == 0)
      {
        this_pose_stamped.pose.position.x = path_.at(i).x; 
        this_pose_stamped.pose.position.y = path_.at(i).y; 
        global_path10.poses.push_back(this_pose_stamped);
      }
    }
    global_path10.header.stamp = ros::Time::now();
    //std :: cout << "global_path10.size() is :"<< path_.size()<<"\n";
    pub_global_path10.publish(global_path10);
  }

    void CRvizPath::SetGlobalPath11(vector<msg_v_trajectory :: Trajectory> path_)
  {
    geometry_msgs::PoseStamped this_pose_stamped; 
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id="path11"; 
    global_path11.poses.clear();
    for(int32 i =0; i<path_.size(); i++)
    {
      if (i%10 == 0)
      {
        this_pose_stamped.pose.position.x = path_.at(i).x; 
        this_pose_stamped.pose.position.y = path_.at(i).y; 
        global_path11.poses.push_back(this_pose_stamped);
      }
    }
    global_path11.header.stamp = ros::Time::now();
    //std :: cout << "global_path11.size() is :"<< path_.size()<<"\n";
    pub_global_path11.publish(global_path11);
  }

    void CRvizPath::SetGlobalPath12(vector<msg_v_trajectory :: Trajectory> path_)
  {
    geometry_msgs::PoseStamped this_pose_stamped; 
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id="path12"; 
    global_path12.poses.clear();
    for(int32 i =0; i<path_.size(); i++)
    {
      if (i%10 == 0)
      {
        this_pose_stamped.pose.position.x = path_.at(i).x;
        this_pose_stamped.pose.position.y = path_.at(i).y;
        global_path12.poses.push_back(this_pose_stamped);
      }
    }
    global_path12.header.stamp = ros::Time::now();
    //std :: cout << "global_path12.size() is :"<< path_.size()<<"\n";
    pub_global_path12.publish(global_path12);
  }


  void CRvizPath::SetLocalPath(vector<msg_v_trajectory :: Trajectory> path_)
  {
    std :: cout << "path_.size = " << path_.size() << std :: endl;

    geometry_msgs::PoseStamped this_pose_stamped; 
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id="path_l"; 
    local_path.poses.clear();
    for(int32 i =0; i<path_.size(); i++)
    {
      this_pose_stamped.pose.position.x = path_.at(i).x; 
      this_pose_stamped.pose.position.y = path_.at(i).y; 

      //std :: cout << "this_pose_stamped.pose.position.x = " << this_pose_stamped.pose.position.x << std :: endl;
      //std :: cout << "this_pose_stamped.pose.position.y = " << this_pose_stamped.pose.position.y << std :: endl;


      local_path.poses.push_back(this_pose_stamped);
    }
    local_path.header.stamp = ros::Time::now();
    pub_local_path.publish(local_path);

  }
#endif

  void CRvizPath::SetGlobalPath1(vector<GlobalPlanning::Trajectory_Point> path_)
  {
    geometry_msgs::PoseStamped this_pose_stamped;
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id = "my_frame";
    global_path1.poses.clear();
    for (int32 i = 0; i < path_.size(); i++)
    {
      // if (i%10 == 0)
      {
        this_pose_stamped.pose.position.x = path_.at(i).x;
        this_pose_stamped.pose.position.y = path_.at(i).y;
        global_path1.poses.push_back(this_pose_stamped);
      }
    }
    global_path1.header.stamp = ros::Time::now();
    std ::cout << "global_path1.size() is :" << path_.size() << "\n";
    // pub_global_path1.publish(global_path1);
  }

  void CRvizPath::SetHistoryPath(float64 x, float64 y)
  {
    static uint8 index = 0;
    geometry_msgs::PoseStamped this_pose_stamped;
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id = "my_frame";
    this_pose_stamped.pose.position.x = x;
    this_pose_stamped.pose.position.y = y;
    if (index == 10)
    {
      history_path.poses.push_back(this_pose_stamped);
      index = 0;
    }
    index++;
    pub_history_path.publish(history_path);
  }

  void CRvizPath::SetVehiclePosition(float64 x, float64 y, float64 yaw_angle)
  {
    yaw_angle = yaw_angle * M_PI / 180;
    vehicle_marker.pose.position.x = x - cos(yaw_angle);
    vehicle_marker.pose.position.y = y - sin(yaw_angle);
    vehicle_marker.pose.position.z = 0;
    vehicle_marker.pose.orientation.x = cos(yaw_angle / 2);
    vehicle_marker.pose.orientation.y = sin(yaw_angle / 2) * 1;
    vehicle_marker.pose.orientation.z = sin(yaw_angle / 2) * 0;
    vehicle_marker.pose.orientation.w = sin(yaw_angle / 2) * 0;
    vehicle_marker.header.stamp = ros::Time();
    pub_veh.publish(vehicle_marker);
  }

  void CRvizPath::SetPreviewMarker(float64 x, float64 y, float64 yaw_angle)
  {
    yaw_angle = yaw_angle * M_PI / 180;
    preview_marker.header.stamp = ros::Time();
    preview_marker.pose.position.x = x;
    preview_marker.pose.position.y = y;
    preview_marker.pose.position.z = 0;
    preview_marker.pose.orientation.x = cos(yaw_angle / 2);
    preview_marker.pose.orientation.y = sin(yaw_angle / 2) * 1;
    preview_marker.pose.orientation.z = sin(yaw_angle / 2) * 0;
    preview_marker.pose.orientation.w = sin(yaw_angle / 2) * 0;
    pub_veh.publish(preview_marker);
  }

  void CRvizPath ::PeripheryPark(int id, vector<geometry_msgs ::Point> &vec_msga)
  {
    // rviz
    m_rviz_point.id = id;
    m_rviz_point.points = vec_msga;
    m_Publisher_rviz.publish(m_rviz_point);
    // for (int i = 0; i < 6; ++i)
    // {
    // m_Publisher_rviz.publish(m_rviz_point);
    // sleep(1);
    // }
  }

  void CRvizPath ::SetAreaPath(vector<geometry_msgs ::Point> &vec_msga)
  {
    area_points.header.stamp = ros::Time::now();
    area_points.points.clear();
    // std::cout << "vec_msga = " << vec_msga.size() << std::endl;
    for (uint32 i = 0; i < vec_msga.size(); i += 1)
    {
      geometry_msgs ::Point32 ros_pt;
      ros_pt.x = vec_msga.at(i).x - x_o_;
      ros_pt.y = vec_msga.at(i).y - y_o_;
      area_points.points.push_back(ros_pt);
    }
    pub_area_path.publish(area_points);
  }

  void CRvizPath ::SetGlobalPath_All(vector<geometry_msgs ::Point> &path_)
  {
    // global_MarkerArrat.markers.clear();
    global_ve_marker.points.clear();
    // cout << " void CRvizPath :: SetGlobalPath_All(vector <geometry_msgs :: Point> path_) = " << path_.size() << endl;
    // global_ve_marker.points = path_;
    // cout << "global_ve_marker.points.size = " << global_ve_marker.points.size() << endl;
    // m_Publisher_global.publish(global_ve_marker);
    // sleep(1);

    global_ve_marker.points = path_;
    global_MarkerArrat.markers.emplace_back(global_ve_marker);

    // for(int in dex = 0; index < path_.size(); index++)
    // {
    //   global_ve_marker.points = path_.at(index);

    //   cout << "global_ve_marker.points.size = " << global_ve_marker.points.size() << endl;
    //   m_Publisher_global.publish(global_ve_marker);
    //   sleep(1);
    // }
  }
  void CRvizPath ::PubGlobalPath(std::vector<Trajectory_Point> &path)
  {
    // std::cout << "aapath.size = " << path.size() << std::endl;
    global_path_now.points.clear();
    global_path_now.header.stamp = ros ::Time ::now();
    geometry_msgs ::Point temp_point;
    for (int32 i = 0; i < path.size(); i++)
    {
      temp_point.x = path.at(i).x - x_o_;
      temp_point.y = path.at(i).y - y_o_;
      temp_point.z = 0; // info_router.path_point.at(i).z;
      global_path_now.points.push_back(temp_point);
    }
    // std::cout << "global_path_now.points.size = " << global_path_now.points.size() << std::endl;
    m_Publisher_global.publish(global_path_now);

#if 0
    for(int index = 0; index < global_MarkerArrat.markers.size(); ++index)
    {
      global_MarkerArrat.markers.at(index).header.frame_id = "map";
      global_MarkerArrat.markers.at(index).ns = "my_namespace";
      global_MarkerArrat.markers.at(index).type = visualization_msgs :: Marker :: POINTS;
      global_MarkerArrat.markers.at(index).action = visualization_msgs :: Marker :: ADD;
      global_MarkerArrat.markers.at(index).scale.x = 0.2;
      global_MarkerArrat.markers.at(index).scale.y = 0.2;
      global_MarkerArrat.markers.at(index).scale.z = 0.2;
      global_MarkerArrat.markers.at(index).color.a = 321;
      global_MarkerArrat.markers.at(index).color.r = 120;
      global_MarkerArrat.markers.at(index).color.g = 0;
      global_MarkerArrat.markers.at(index).color.b = 301;
      global_MarkerArrat.markers.at(index).id = index + 1;
    }
    m_Publisher_global.publish(global_MarkerArrat); 
    // pub_global_path1.publish(global_path1);
#endif
  }

  void CRvizPath ::PubTurningPathParagraph(std::vector<Trajectory_Point> &path)
  {
    // std::cout << "aapath.size = " << path.size() << std::endl;
    turn_path_paragraph_now.points.clear();
    turn_path_paragraph_now.header.stamp = ros ::Time ::now();
    geometry_msgs ::Point temp_point;
    for (int32 i = 0; i < path.size(); i++)
    {
      temp_point.x = path.at(i).x - x_o_;
      temp_point.y = path.at(i).y - y_o_;
      temp_point.z = 0; // info_router.path_point.at(i).z;
      turn_path_paragraph_now.points.push_back(temp_point);
    }
    // std::cout << "global_path_now.points.size = " << global_path_now.points.size() << std::endl;
    m_Publisher_turn_path_paragraph.publish(turn_path_paragraph_now);

#if 0
    for(int index = 0; index < global_MarkerArrat.markers.size(); ++index)
    {
      global_MarkerArrat.markers.at(index).header.frame_id = "map";
      global_MarkerArrat.markers.at(index).ns = "my_namespace";
      global_MarkerArrat.markers.at(index).type = visualization_msgs :: Marker :: POINTS;
      global_MarkerArrat.markers.at(index).action = visualization_msgs :: Marker :: ADD;
      global_MarkerArrat.markers.at(index).scale.x = 0.2;
      global_MarkerArrat.markers.at(index).scale.y = 0.2;
      global_MarkerArrat.markers.at(index).scale.z = 0.2;
      global_MarkerArrat.markers.at(index).color.a = 321;
      global_MarkerArrat.markers.at(index).color.r = 120;
      global_MarkerArrat.markers.at(index).color.g = 0;
      global_MarkerArrat.markers.at(index).color.b = 301;
      global_MarkerArrat.markers.at(index).id = index + 1;
    }
    m_Publisher_global.publish(global_MarkerArrat); 
    // pub_global_path1.publish(global_path1);
#endif
  }

void CRvizPath ::PubTurningPathParagraphAnother(std::vector<Trajectory_Point> &path)
  {
    // std::cout << "aapath_an.size = " << path.size() << std::endl;
    turn_path_paragraph_another.points.clear();
    turn_path_paragraph_another.header.stamp = ros ::Time ::now();
    geometry_msgs ::Point temp_point;
    for (int32 i = 0; i < path.size(); i++)
    {
      temp_point.x = path.at(i).x - x_o_;
      temp_point.y = path.at(i).y - y_o_;
      temp_point.z = 0; // info_router.path_point.at(i).z;
      turn_path_paragraph_another.points.push_back(temp_point);
    }
    // std::cout << "global_path_now.points.size = " << global_path_now.points.size() << std::endl;
    m_Publisher_turn_path_paragraph_another.publish(turn_path_paragraph_another);

#if 0
    for(int index = 0; index < global_MarkerArrat.markers.size(); ++index)
    {
      global_MarkerArrat.markers.at(index).header.frame_id = "map";
      global_MarkerArrat.markers.at(index).ns = "my_namespace";
      global_MarkerArrat.markers.at(index).type = visualization_msgs :: Marker :: POINTS;
      global_MarkerArrat.markers.at(index).action = visualization_msgs :: Marker :: ADD;
      global_MarkerArrat.markers.at(index).scale.x = 0.2;
      global_MarkerArrat.markers.at(index).scale.y = 0.2;
      global_MarkerArrat.markers.at(index).scale.z = 0.2;
      global_MarkerArrat.markers.at(index).color.a = 321;
      global_MarkerArrat.markers.at(index).color.r = 120;
      global_MarkerArrat.markers.at(index).color.g = 0;
      global_MarkerArrat.markers.at(index).color.b = 301;
      global_MarkerArrat.markers.at(index).id = index + 1;
    }
    m_Publisher_global.publish(global_MarkerArrat); 
    // pub_global_path1.publish(global_path1);
#endif
  }


  void CRvizPath ::SetStartPosition(float64 x, float64 y, float64 yaw_angle)
  {
    start.header.stamp = ros::Time();
    start.color.a = 0.5;
    start.color.r = 1.0;
    start.color.g = 0.0;
    start.color.b = 0.0;
    start.pose.position.x = x;
    start.pose.position.y = y;
    start.pose.position.z = 0;
    start.pose.orientation.x = cos(yaw_angle / 2);
    start.pose.orientation.y = sin(yaw_angle / 2) * 1;
    start.pose.orientation.z = sin(yaw_angle / 2) * 0;
    start.pose.orientation.w = sin(yaw_angle / 2) * 0;
    start.scale.x = 5.22;
    start.scale.y = 1;
    start.scale.z = 1;
  }

  void CRvizPath ::SetEndPosition(float64 x, float64 y, float64 yaw_angle)
  {
    end.header.stamp = ros::Time();
    end.color.a = 0.5;
    end.color.r = 1.0;
    end.color.g = 0.0;
    end.color.b = 1.0;
    end.pose.position.x = x;
    end.pose.position.y = y;
    end.pose.position.z = 0;
    end.pose.orientation.x = cos(yaw_angle / 2);
    end.pose.orientation.y = sin(yaw_angle / 2) * 1;
    end.pose.orientation.z = sin(yaw_angle / 2) * 0;
    end.pose.orientation.w = sin(yaw_angle / 2) * 0;
    end.scale.x = 5.22;
    end.scale.y = 1;
    end.scale.z = 1;
  }

  void CRvizPath ::PublishStart()
  {
    pub_start.publish(start);
  }

  void CRvizPath ::PublishEnd()
  {
    pub_end.publish(end);
  }
  void CRvizPath::Set2DCostMap(const unordered_map<uint32, float64> cost_map, Point midpoint_)
  {
    float64 max_value = 0;
    float64 min_value = 1000;
    // const unordered_map<uint64, float64>::iterator it;

    for (auto it = cost_map.begin(); it != cost_map.end(); ++it)
    {
      if (it->second > max_value)
      {
        max_value = it->second;
      }
      if (it->second < min_value)
      {
        min_value = it->second;
      }
    }
    //      cout << "max_value = " << max_value << endl;
    //      cout << "min_value = " << min_value << endl;

    h_value_map.markers.clear();
    ColorGradient heatMapGradient;
    heatMapGradient.createDefaultHeatMapGradient();
    float32 red, green, blue;
    uint32 num = 0;
    bool once = true;
    IntCoordinate point;
    for (auto it = cost_map.begin(); it != cost_map.end(); ++it)
    {
      //          if(Constants::bfs_search)
      //          {
      //              point.x = it->first >> 32;
      //              point.y = it->first & 0xFFFFFFFF;
      //          }
      //          else
      {
        point.x = it->first >> 16;
        point.y = it->first & 0xFFFF;
      }

      visualization_msgs::Marker cost_cube;
      cost_cube.header.frame_id = "map";
      cost_cube.header.stamp = ros::Time::now();
      cost_cube.id = num++;
      cost_cube.type = visualization_msgs::Marker::CUBE;
      if (once)
      {
        cost_cube.action = 3;
        once = false;
      }
      else
        cost_cube.action = 0;
      cost_cube.scale.x = Constants::grid_dist;
      cost_cube.scale.y = Constants::grid_dist;
      cost_cube.scale.z = 0.1;
      cost_cube.color.a = 0.5;

      float64 value = (it->second - min_value) / (max_value - min_value);
      heatMapGradient.getColorAtValue(value, red, green, blue); // 转化成颜色

      cost_cube.color.r = red;
      cost_cube.color.g = green;
      cost_cube.color.b = blue;
      // center in cell +0.5
      cost_cube.pose.position.x = point.x + midpoint_.x;
      cost_cube.pose.position.y = point.y + midpoint_.y;
      h_value_map.markers.push_back(cost_cube);
      //          //显示文字
      //          visualization_msgs::Marker text_marker;
      //          text_marker.header.frame_id = "map";
      //          text_marker.header.stamp = ros::Time::now();
      //          text_marker.id = num++;
      //          text_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
      //          if(once)
      //          {
      //              text_marker.action = 3;
      //              once = false;
      //          }
      //          else
      //              text_marker.action = 0;
      //          text_marker.scale.x = Constants::grid_dist;
      //          text_marker.scale.y = Constants::grid_dist;
      //          text_marker.scale.z = 0.1;
      //          text_marker.color.a = 0.5;
      //          text_marker.text = std::to_string(it->second);

      //          text_marker.color.r = 255;
      //          text_marker.color.g = 0;
      //          text_marker.color.b = 0;

      //            // center in cell +0.5
      //          text_marker.pose.position.x = point.x;
      //          text_marker.pose.position.y = point.y;
      //          h_value_map.markers.push_back(text_marker);
    }
    pub_h_value_map.publish(h_value_map);
  }
}
