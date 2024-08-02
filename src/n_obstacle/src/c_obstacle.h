/******************************************
 > Copyright(C):    湖南大学
 > File name:       c_obstacle.h
 > Author:          cxp
 > Created Time:    2021/08/24
 * ****************************************/
#ifndef Obstatcle_H
#define Obstatcle_H
// Include system lib.
#include <ros/package.h>
#include <ros/ros.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "interactive_markers/interactive_marker_server.h"
#include "tf/tf.h"
// Include personal lib.
#include "msg_common/GridPoint.h"
#include "msg_common/WayPoint.h"
#include "msg_obj/Obj.h"
#include "msg_obj_fuse/msg_obj_fuse.h"
#include "msg_v_decision/Trajectory.h"
// #include "msg_v_position/msg_v_position.h"
// #include "msg_decision_planning/TrajectoryPoint.h"
#include "my_typedef.h"

using namespace std;

typedef msg_obj_fuse::msg_obj_fuse ObstacleSet;
typedef msg_common::WayPoint       Point;

struct Obstacle {
    double        a;
    double        s;
    double        l;
    double        speed;
    double        length;
    double        width;
    double        x;
    double        y;
    double        angle;
    double        a_max;
    double        expect_speed;
    double        acc_coe;
    double        min_dis;
    double        a_start;
    double        a_deacc;
    int           lane_id;
    double        expect_t;
    int           id;
    int           task_id;
    vector<Point> reference_path;
};

class ObstatcleManager {
  public:
    ObstatcleManager();
    ~ObstatcleManager();

    /*
     * @brief 传入障碍物，车辆将根据障碍物车道信息读取对应的参考路径并存入some_obs的reference_path成员变量
     */
    bool ReadRoadFile(Obstacle& some_obs);

    void calculate_s(vector<Point>& some_path);

    /**
     * @brief
     * 根据输入的lane_id读取全局路径，lane_id为1时，障碍物读取的全局路径与自车同向，lane_id为2时读取的全局路径与自车反向。
     * 障碍物可以避让前方lane_id相同的车，产生跟车行为，跟车行为参数为a_max和acc_coe，默认为1和0.4。
     * 障碍物初始位置在s、l处，初始速度为speed。障碍物保持l不变加速往全局路径方向行驶，直到加速到expect_speed或产生必要的跟车行为时放弃加速。
     * 输入id参数暂时没啥意义，随便输就好
     */
    void AddDynamicObstacle(const double s, const double l, const double speed, const double length, const double width, const double a_max, const double expect_speed, const double acc_coe, const int lane_id, const int id, const int task_id);

    void AddStaticObstacle(const double x, const double y, const double heading_angle, const double length, const double width);
    void AddMovableObstacle(int id, double x, double y, double heading_angle, double length, double width);

    void ObstacleMoveCallback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr& feedback, int id);

    void AddArrowCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg) {
        // if (obs_num == 1) {
        //     AddStaticObstacle(-31, -107, 0, 1.8, 1.8);
        //     AddMovableObstacle(obstacle_set_.size() - 1, -31, -107, 0, 1.8, 1.8);
        //     cout << "add a MovableObstacle : (" << msg->pose.pose.position.x << ", " << msg->pose.pose.position.y << ")"
        //          << endl;
        //     obs_num = 2;
        // }
        // else if (obs_num == 2) {
        //     AddStaticObstacle(-27.3, -107, 0, 1.8, 1.8);
        //     AddMovableObstacle(obstacle_set_.size() - 1, -27.3, -107, 0, 1.8, 1.8);
        //     cout << "add a MovableObstacle : (" << msg->pose.pose.position.x << ", " << msg->pose.pose.position.y << ")"
        //          << endl;
        //     obs_num = 1;
        // }
        AddStaticObstacle(msg->pose.pose.position.x, msg->pose.pose.position.y, 0, 1.8, 1.8);
        AddMovableObstacle(obstacle_set_.size() - 1, msg->pose.pose.position.x, msg->pose.pose.position.y, 0, 1.8, 1.8);
    };

    void update_obs_position();

    double cal_expect_dis(double static_s, double expect_t, double ego_speed, double front_speed, double start_acc, double deacc_a);

    double cal_IDM_a(double a_max, double ego_speed, double expect_speed, double acc_coe, double front_s, double ego_s, double static_dis, double expect_dis);

    msg_obj_fuse::msg_obj_fuse obs_transfer();

  private:
    std::vector<Obstacle>                        obstacle_set_;
    ros::NodeHandle                              nh;
    ros::Subscriber                              add_arrow_sub_ = nh.subscribe<geometry_msgs::PoseWithCovarianceStamped>("/initialpose", 1, &ObstatcleManager::AddArrowCallback, this);
    interactive_markers::InteractiveMarkerServer server_;
    double                                       delta_t = 0.02;
    int                                          obs_num = 1;
};

#endif // Obstatcle_H
