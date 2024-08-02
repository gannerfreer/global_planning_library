/******************************************
 > Copyright(C):    湖南大学
 > File name:       main.cpp
 > Author:          cxp
 > Created Time:    2021/08/24
 * ****************************************/
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <ros/ros.h>
#include <tf/transform_datatypes.h>

#include <cmath>
#include <ctime>
#include <iostream>
#include <random>

#include "c_obstacle.h"


msg_obj::Obj add_dynamic_obs2;
bool         is_create_new2;
bool         simulate_start;

/**
 * @brief 根据Rviz发布信息，确定障碍物位置
 *
 * @param msg
 */
// void get_dynamic_obs2_position(const geometry_msgs::PoseStamped::ConstPtr& msg) {
//     add_dynamic_obs2.x        = msg->pose.position.x;
//     add_dynamic_obs2.y        = msg->pose.position.y;
//     add_dynamic_obs2.bbox_yaw = tf::getYaw(msg->pose.orientation) * 180 / M_PI;
//     count                     = count % 5;
//     count++;
//     is_create_new2 = true;
// }

// void create_dynamic_obs2() {
//     if (count == 1) {
//         add_dynamic_obs2.vx = 0;
//         add_dynamic_obs2.vy = 0;
//     }
//     if (count == 2) {
//         add_dynamic_obs2.vx = 0;
//         add_dynamic_obs2.vy = 0;
//     }
//     if (count == 3) {
//         add_dynamic_obs2.vx = 0;
//         add_dynamic_obs2.vy = 0;
//     }
//     if (count == 4) {
//         add_dynamic_obs2.vx = 0;
//         add_dynamic_obs2.vy = 0;
//     }
//     if (count == 5) {
//         add_dynamic_obs2.vx = 0;
//         add_dynamic_obs2.vy = 0;
//     }
//     add_dynamic_obs2.length = 5;
//     add_dynamic_obs2.width  = 1.8;
// }

// void update_dynamic2_obs(msg_obj::Obj& obj) {
//     obj.x += obj.vx * 0.02;
//     obj.y += obj.vy * 0.02;
//     obj.contour_point.clear();
//     msg_common::GridPoint grid_point;
//     // 车辆中心坐标
//     grid_point.x = obj.x;
//     grid_point.y = obj.y;
//     obj.contour_point.push_back(grid_point);
//     // 车辆安全包络左前角坐标
//     grid_point.x = obj.x + (obj.length / 2) * cos(obj.orientation * M_PI / 180.0) -
//                    (obj.width / 2) * sin(obj.orientation * M_PI / 180.0);
//     grid_point.y = obj.y + (obj.length / 2) * sin(obj.orientation * M_PI / 180.0) +
//                    (obj.width / 2) * cos(obj.orientation * M_PI / 180.0);
//     obj.contour_point.push_back(grid_point);
//     // 车辆安全包络右前角坐标
//     grid_point.x = obj.x + (obj.length / 2) * cos(obj.orientation * M_PI / 180.0) +
//                    (obj.width / 2) * sin(obj.orientation * M_PI / 180.0);
//     grid_point.y = obj.y + (obj.length / 2) * sin(obj.orientation * M_PI / 180.0) -
//                    (obj.width / 2) * cos(obj.orientation * M_PI / 180.0);
//     obj.contour_point.push_back(grid_point);
//     // 车辆安全包络左后角坐标
//     grid_point.x = obj.x + -(obj.length / 2) * cos(obj.orientation * M_PI / 180.0) -
//                    (obj.width / 2) * sin(obj.orientation * M_PI / 180.0);
//     grid_point.y = obj.y + -(obj.length / 2) * sin(obj.orientation * M_PI / 180.0) +
//                    (obj.width / 2) * cos(obj.orientation * M_PI / 180.0);
//     obj.contour_point.push_back(grid_point);
//     // 车辆安全包络右后角坐标
//     grid_point.x = obj.x + -(obj.length / 2) * cos(obj.orientation * M_PI / 180.0) +
//                    (obj.width / 2) * sin(obj.orientation * M_PI / 180.0);
//     grid_point.y = obj.y + -(obj.length / 2) * sin(obj.orientation * M_PI / 180.0) -
//                    (obj.width / 2) * cos(obj.orientation * M_PI / 180.0);
//     obj.contour_point.push_back(grid_point);
// }


void callbackStart(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& start) {
    cout << "simulate start!" << endl;
}

int main(int argc, char** argv) {
    ObstacleSet statistic_obstacle_set;
    ObstacleSet dynamic_obstacle_set;
    ObstacleSet dynamic_obstacle2_set;
    ros::init(argc, argv, "n_obstatcle");
    ros::NodeHandle nh;
    ros::Publisher  pub_obstacle_set        = nh.advertise<msg_obj_fuse::msg_obj_fuse>("msg_obj_fuse", 1);
    ros::Subscriber subscriber_start_point_ = nh.subscribe("/initialpose", 10, callbackStart);


    ObstatcleManager obstatcle_manager;

    /*添加障碍物*/
    // obstatcle_manager.AddObstacle(70.0, 0.0, 3.0, 5.2, 1.8, 3.0, 120.0 / 3.6, 4.0, 2, 2);
    // obstatcle_manager.AddDynamicObstacle(60.0, 0.0, /* 5.0 */ 0.0, 5.2, 1.8, 3.0, /* 60.0 / 3.6 */ 0.0, 4.0, 2, 2, 1);

    /*主循环*/
    ros::Rate loop_rate(50);
    while (ros::ok()) {
        ros::spinOnce();
        // obstatcle_manager.update_obs_position();
        msg_obj_fuse::msg_obj_fuse obs_2_show = obstatcle_manager.obs_transfer();
        pub_obstacle_set.publish(obs_2_show);
    }
    loop_rate.sleep();

    return 0;
}
