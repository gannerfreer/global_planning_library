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


void CRvizPath::PubObstacles(vector<geometry_msgs::Point>& vec_msga) {
    obstacle_points_.header.stamp = ros::Time::now();
    obstacle_points_.points.clear();
    // std::cout << "vec_msga = " << vec_msga.size() << std::endl;
    for (unsigned int i = 0; i < vec_msga.size(); i += 1) {
        geometry_msgs::Point32 ros_pt;
        ros_pt.x = vec_msga.at(i).x - x_o_;
        ros_pt.y = vec_msga.at(i).y - y_o_;
        obstacle_points_.points.push_back(ros_pt);
    }
    // cout << "obstalce_points_.points.size():" << obstacle_points_.points.size() << endl;
    pub_obstacle_.publish(obstacle_points_);
}

void CRvizPath::PubMapborderAndReferenceline(vector<geometry_msgs::Point>& vec_msga) {
    area_points.header.stamp = ros::Time::now();
    area_points.points.clear();
    // std::cout << "vec_msga = " << vec_msga.size() << std::endl;
    for (unsigned int i = 0; i < vec_msga.size(); i += 1) {
        geometry_msgs::Point32 ros_pt;
        ros_pt.x = vec_msga.at(i).x - x_o_;
        ros_pt.y = vec_msga.at(i).y - y_o_;
        area_points.points.push_back(ros_pt);
    }
    pub_area_path.publish(area_points);
}
void CRvizPath::PubRoadNode(vector<geometry_msgs::Point>& path) {
    road_nodes_.header.stamp = ros::Time::now();
    road_nodes_.points.clear();
    // std::cout << "vec_msga = " << vec_msga.size() << std::endl;
    for (unsigned int i = 0; i < path.size(); i += 1) {
        geometry_msgs::Point32 ros_pt;
        ros_pt.x = path.at(i).x - x_o_;
        ros_pt.y = path.at(i).y - y_o_;
        road_nodes_.points.push_back(ros_pt);
    }
    m_Publisher_road_node_.publish(road_nodes_);
}


void CRvizPath::PubGlobalPath(std::vector<_TrajectoryPoint>& path) {
    // std::cout << "aapath.size = " << path.size() << std::endl;
    global_path_now_.points.clear();
    global_path_now_.header.stamp = ros ::Time ::now();
    geometry_msgs::Point temp_point;
    for (int i = 0; i < path.size(); i++) {
        temp_point.x = path.at(i).x - x_o_;
        temp_point.y = path.at(i).y - y_o_;
        temp_point.z = 0; // info_router.path_point.at(i).z;
        global_path_now_.points.push_back(temp_point);
    }
    // std::cout << "global_path_now_.points.size = " << global_path_now_.points.size() << std::endl;
    publisher_global_path_.publish(global_path_now_);
}

void CRvizPath::PubExpandPoint(std::vector<Point>& path, Point midpoint_) {
    // std::cout << "aapath.size = " << path.size() << std::endl;
    expand_point_now_.points.clear();
    expand_point_now_.header.stamp = ros ::Time ::now();
    geometry_msgs::Point temp_point;
    for (int i = 0; i < path.size(); i++) {
        temp_point.x = path.at(i).x - x_o_ + midpoint_.x;
        temp_point.y = path.at(i).y - y_o_ + midpoint_.y;
        temp_point.z = 0; // info_router.path_point.at(i).z;
        expand_point_now_.points.push_back(temp_point);
    }
    // cout << "expand_point_now_.points.sie():" << expand_point_now_.points.size() << endl;
    publisher_expand_point_.publish(expand_point_now_);
}

void CRvizPath::PubStartPosition(double x, double y, double yaw_angle) {
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
    pub_start.publish(start);
}


void CRvizPath::PubEndPosition(double x, double y, double yaw_angle) {
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
    pub_end.publish(end);
}


void CRvizPath::Pub2DCostMap(const unordered_map<unsigned int, double>& cost_map, Point midpoint_) {
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
        cout << "it->first:" << it->first << endl;
        point.x = short(it->first >> 16);
        cout << "point.x:" << point.x << endl;
        point.y = short(it->first & 0x0000FFFF);
        cout << "point.y:" << point.y << endl;


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
        cost_cube.pose.position.x = point.x + midpoint_.x - x_o_;
        cost_cube.pose.position.y = point.y + midpoint_.y - y_o_;
        h_value_map.markers.push_back(cost_cube);
    }
    // cout << "H_value_map.markers.size():" << h_value_map.markers.size() << endl;
    pub_h_value_map.publish(h_value_map);
}
} // namespace rviz_path
