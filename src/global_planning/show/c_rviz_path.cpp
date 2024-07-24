/*******************************************************************/
/*                      Author: xubiao                             */
/*                     Contact: xubiao@hnu.edu.cn                  */
/*                 Last update: 2019-05-30                         */
/*******************************************************************/

/*
  Description: The header file for C++ class CRvizPath
  The class includes all the necessary vars and funcs for showing path and obstacle in rviz.
*/

#include "c_rviz_path.h"

#include "../common/color.h"
#include "string.h"

namespace rviz_path {


void CRvizPath::SetGlobalPath1(vector<_TrajectoryPoint> path_) {
    geometry_msgs::PoseStamped this_pose_stamped;
    this_pose_stamped.header.stamp    = ros::Time::now();
    this_pose_stamped.header.frame_id = "my_frame";
    global_path1.poses.clear();
    for (int i = 0; i < path_.size(); i++) {
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

void CRvizPath::SetHistoryPath(double x, double y) {
    static unsigned char       index = 0;
    geometry_msgs::PoseStamped this_pose_stamped;
    this_pose_stamped.header.stamp    = ros::Time::now();
    this_pose_stamped.header.frame_id = "my_frame";
    this_pose_stamped.pose.position.x = x;
    this_pose_stamped.pose.position.y = y;
    if (index == 10) {
        history_path.poses.push_back(this_pose_stamped);
        index = 0;
    }
    index++;
    pub_history_path.publish(history_path);
}

void CRvizPath::SetVehiclePosition(double x, double y, double yaw_angle) {
    yaw_angle                         = yaw_angle * M_PI / 180;
    vehicle_marker.pose.position.x    = x - cos(yaw_angle);
    vehicle_marker.pose.position.y    = y - sin(yaw_angle);
    vehicle_marker.pose.position.z    = 0;
    vehicle_marker.pose.orientation.x = cos(yaw_angle / 2);
    vehicle_marker.pose.orientation.y = sin(yaw_angle / 2) * 1;
    vehicle_marker.pose.orientation.z = sin(yaw_angle / 2) * 0;
    vehicle_marker.pose.orientation.w = sin(yaw_angle / 2) * 0;
    vehicle_marker.header.stamp       = ros::Time();
    pub_veh.publish(vehicle_marker);
}

void CRvizPath::SetPreviewMarker(double x, double y, double yaw_angle) {
    yaw_angle                         = yaw_angle * M_PI / 180;
    preview_marker.header.stamp       = ros::Time();
    preview_marker.pose.position.x    = x;
    preview_marker.pose.position.y    = y;
    preview_marker.pose.position.z    = 0;
    preview_marker.pose.orientation.x = cos(yaw_angle / 2);
    preview_marker.pose.orientation.y = sin(yaw_angle / 2) * 1;
    preview_marker.pose.orientation.z = sin(yaw_angle / 2) * 0;
    preview_marker.pose.orientation.w = sin(yaw_angle / 2) * 0;
    pub_veh.publish(preview_marker);
}

void CRvizPath ::PeripheryPark(int id, vector<geometry_msgs ::Point>& vec_msga) {
    // rviz
    m_rviz_point.id     = id;
    m_rviz_point.points = vec_msga;
    m_Publisher_rviz.publish(m_rviz_point);
    // for (int i = 0; i < 6; ++i)
    // {
    // m_Publisher_rviz.publish(m_rviz_point);
    // sleep(1);
    // }
}

void CRvizPath ::SetAreaPath(vector<geometry_msgs ::Point>& vec_msga) {
    area_points.header.stamp = ros::Time::now();
    area_points.points.clear();
    // std::cout << "vec_msga = " << vec_msga.size() << std::endl;
    for (unsigned int i = 0; i < vec_msga.size(); i += 1) {
        geometry_msgs ::Point32 ros_pt;
        ros_pt.x = vec_msga.at(i).x - x_o_;
        ros_pt.y = vec_msga.at(i).y - y_o_;
        area_points.points.push_back(ros_pt);
    }
    pub_area_path.publish(area_points);
}

void CRvizPath ::SetGlobalPath_All(vector<geometry_msgs ::Point>& path_) {
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
void CRvizPath ::PubGlobalPath(std::vector<_TrajectoryPoint>& path) {
    // std::cout << "aapath.size = " << path.size() << std::endl;
    global_path_now.points.clear();
    global_path_now.header.stamp = ros ::Time ::now();
    geometry_msgs ::Point temp_point;
    for (int i = 0; i < path.size(); i++) {
        temp_point.x = path.at(i).x - x_o_;
        temp_point.y = path.at(i).y - y_o_;
        temp_point.z = 0; // info_router.path_point.at(i).z;
        global_path_now.points.push_back(temp_point);
    }
    // std::cout << "global_path_now.points.size = " << global_path_now.points.size() << std::endl;
    m_Publisher_global.publish(global_path_now);
}

void CRvizPath ::PubTurningPathParagraph(std::vector<_TrajectoryPoint>& path) {
    // std::cout << "aapath.size = " << path.size() << std::endl;
    turn_path_paragraph_now.points.clear();
    turn_path_paragraph_now.header.stamp = ros ::Time ::now();
    geometry_msgs ::Point temp_point;
    for (int i = 0; i < path.size(); i++) {
        temp_point.x = path.at(i).x - x_o_;
        temp_point.y = path.at(i).y - y_o_;
        temp_point.z = 0; // info_router.path_point.at(i).z;
        turn_path_paragraph_now.points.push_back(temp_point);
    }
    // std::cout << "global_path_now.points.size = " << global_path_now.points.size() << std::endl;
    m_Publisher_turn_path_paragraph.publish(turn_path_paragraph_now);
}

void CRvizPath ::PubTurningPathParagraphAnother(std::vector<_TrajectoryPoint>& path) {
    // std::cout << "aapath_an.size = " << path.size() << std::endl;
    turn_path_paragraph_another.points.clear();
    turn_path_paragraph_another.header.stamp = ros ::Time ::now();
    geometry_msgs ::Point temp_point;
    for (int i = 0; i < path.size(); i++) {
        temp_point.x = path.at(i).x - x_o_;
        temp_point.y = path.at(i).y - y_o_;
        temp_point.z = 0; // info_router.path_point.at(i).z;
        turn_path_paragraph_another.points.push_back(temp_point);
    }
    // std::cout << "global_path_now.points.size = " << global_path_now.points.size() << std::endl;
    m_Publisher_turn_path_paragraph_another.publish(turn_path_paragraph_another);
}


void CRvizPath ::SetStartPosition(double x, double y, double yaw_angle) {
    start.header.stamp       = ros::Time();
    start.color.a            = 0.5;
    start.color.r            = 1.0;
    start.color.g            = 0.0;
    start.color.b            = 0.0;
    start.pose.position.x    = x;
    start.pose.position.y    = y;
    start.pose.position.z    = 0;
    start.pose.orientation.x = cos(yaw_angle / 2);
    start.pose.orientation.y = sin(yaw_angle / 2) * 1;
    start.pose.orientation.z = sin(yaw_angle / 2) * 0;
    start.pose.orientation.w = sin(yaw_angle / 2) * 0;
    start.scale.x            = 5.22;
    start.scale.y            = 1;
    start.scale.z            = 1;
}

void CRvizPath ::SetEndPosition(double x, double y, double yaw_angle) {
    end.header.stamp       = ros::Time();
    end.color.a            = 0.5;
    end.color.r            = 1.0;
    end.color.g            = 0.0;
    end.color.b            = 1.0;
    end.pose.position.x    = x;
    end.pose.position.y    = y;
    end.pose.position.z    = 0;
    end.pose.orientation.x = cos(yaw_angle / 2);
    end.pose.orientation.y = sin(yaw_angle / 2) * 1;
    end.pose.orientation.z = sin(yaw_angle / 2) * 0;
    end.pose.orientation.w = sin(yaw_angle / 2) * 0;
    end.scale.x            = 5.22;
    end.scale.y            = 1;
    end.scale.z            = 1;
}

void CRvizPath ::PublishStart() {
    pub_start.publish(start);
}

void CRvizPath ::PublishEnd() {
    pub_end.publish(end);
}
void CRvizPath::Set2DCostMap(const unordered_map<unsigned int, double> cost_map, Point midpoint_) {
    double max_value = 0;
    double min_value = 1000;
    // const unordered_map<uint64, double>::iterator it;

    for (auto it = cost_map.begin(); it != cost_map.end(); ++it) {
        if (it->second > max_value) {
            max_value = it->second;
        }
        if (it->second < min_value) {
            min_value = it->second;
        }
    }
    //      cout << "max_value = " << max_value << endl;
    //      cout << "min_value = " << min_value << endl;

    h_value_map.markers.clear();
    ColorGradient heatMapGradient;
    heatMapGradient.createDefaultHeatMapGradient();
    float         red, green, blue;
    unsigned int  num  = 0;
    bool          once = true;
    IntCoordinate point;
    for (auto it = cost_map.begin(); it != cost_map.end(); ++it) {
        point.x = it->first >> 16;
        point.y = it->first & 0xFFFF;


        visualization_msgs::Marker cost_cube;
        cost_cube.header.frame_id = "map";
        cost_cube.header.stamp    = ros::Time::now();
        cost_cube.id              = num++;
        cost_cube.type            = visualization_msgs::Marker::CUBE;
        if (once) {
            cost_cube.action = 3;
            once             = false;
        }
        else
            cost_cube.action = 0;
        cost_cube.scale.x = 1;
        cost_cube.scale.y = 1;
        cost_cube.scale.z = 0.1;
        cost_cube.color.a = 0.5;

        double value = (it->second - min_value) / (max_value - min_value);
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
} // namespace rviz_path
