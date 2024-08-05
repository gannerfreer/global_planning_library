/******************************************
 > Copyright(C):    湖南大学
 > File name:       c_obstacle.cpp
 > Author:          cxp
 > Created Time:    2021/08/24
 * ****************************************/
#include "c_obstacle.h"

#include <math.h>

#include <climits>
#include <iomanip>
#include <iterator>

ObstatcleManager::ObstatcleManager() : server_("n_obstacle") {
    // ReadRoadFile();
}
ObstatcleManager::~ObstatcleManager() {}

/**
 * @brief 读取全局路径函数
 */
bool ObstatcleManager::ReadRoadFile(Obstacle& some_obs) {
    std::string   path = ros::package::getPath("n_obstacle");
    std::ifstream path_file;
    string        path_name = "/temp_data/task";
    char          ch        = '0' + some_obs.task_id;
    path_name += std::string{ch};
    path_name += "/global_path.txt";
    std::cout << path + "/../../.." + path_name << std::endl;
    path_file.open(path + "/../../.." + path_name);
    if (!path_file.is_open()) {
        std::cout << "open path file fail!!!" << std::endl;
    }
    else {
        vector<Point> temp_path;
        Point         point;
        while (!path_file.eof()) {
            path_file >> point.x >> point.y >> point.z >> point.heading_angle >> point.speed >> point.curvature >> point.direction >> point.distance >> point.left >> point.right;
            temp_path.push_back(point);
        }
        some_obs.reference_path = temp_path;
        if (some_obs.lane_id == 2) {
            reverse(some_obs.reference_path.begin(), some_obs.reference_path.end());
        }
    }
    path_file.close();
    std::cout << "reference_path.size()" << some_obs.reference_path.size() << std::endl;
    return true;
}

void ObstatcleManager::calculate_s(vector<Point>& some_path) {
    if (some_path.empty()) {
        return;
    }
    double temp_s         = 0;
    some_path[0].distance = 0;
    for (int i = 1; i < some_path.size(); i++) {
        temp_s                = temp_s + sqrt(pow(some_path[i].x - some_path[i - 1].x, 2) + pow(some_path[i].y - some_path[i - 1].y, 2));
        some_path[i].distance = temp_s;
    }
}

void ObstatcleManager::AddDynamicObstacle(const double s, const double l, const double speed, const double length, const double width, const double a_max, const double expect_speed, const double acc_coe, const int lane_id, const int id, const int task_id) {
    Obstacle obstacle;
    obstacle.id           = id;
    obstacle.task_id      = task_id;
    obstacle.s            = s;
    obstacle.l            = l;
    obstacle.speed        = speed;
    obstacle.length       = length;
    obstacle.width        = width;
    obstacle.a_max        = a_max;
    obstacle.expect_speed = expect_speed;
    obstacle.acc_coe      = acc_coe;
    obstacle.min_dis      = 2.0 + length;
    obstacle.lane_id      = lane_id;
    obstacle.a_start      = 1.0;
    obstacle.a_deacc      = 2.0;
    obstacle.expect_t     = 3.0;
    obstacle.a            = 0.0;

    bool read_file = ReadRoadFile(obstacle);
    if (read_file) {
        calculate_s(obstacle.reference_path);
    }

    for (int i = 0; i < obstacle.reference_path.size(); i++) {
        if (obstacle.s <= obstacle.reference_path[i].distance) {
            double delta_s = obstacle.s - obstacle.reference_path[i - 1].distance;
            double ratio   = delta_s / (obstacle.reference_path[i].distance - obstacle.reference_path[i - 1].distance);
            obstacle.x     = obstacle.reference_path[i - 1].x + ratio * (obstacle.reference_path[i].x - obstacle.reference_path[i - 1].x);
            obstacle.y     = obstacle.reference_path[i - 1].y + ratio * (obstacle.reference_path[i].y - obstacle.reference_path[i - 1].y);
            obstacle.angle = obstacle.reference_path[i - 1].heading_angle + ratio * (obstacle.reference_path[i].heading_angle - obstacle.reference_path[i - 1].heading_angle);
            break;
        }
    }
    obstacle_set_.emplace_back(obstacle);
}

void ObstatcleManager::AddStaticObstacle(const double x, const double y, const double heading_angle, const double length, const double width) {
    Obstacle obstacle;
    obstacle.speed  = 0;
    obstacle.length = length;
    obstacle.width  = width;
    obstacle.x      = x;
    obstacle.y      = y;
    obstacle.angle  = heading_angle;
    obstacle_set_.emplace_back(obstacle);
}

void ObstatcleManager::AddMovableObstacle(int id, double x, double y, double heading_angle, double length, double width) {
    visualization_msgs::InteractiveMarker int_marker;
    int_marker.header.frame_id  = "map";
    int_marker.name             = "o" + std::string{id};
    int_marker.pose.position.x  = x;
    int_marker.pose.position.y  = y;
    int_marker.pose.position.z  = 10.0;
    int_marker.pose.orientation = tf::createQuaternionMsgFromYaw(heading_angle * M_PI / 180);
    int_marker.scale            = 1.0;

    visualization_msgs::Marker marker;
    marker.type    = visualization_msgs::Marker::CUBE;
    marker.scale.x = length;
    marker.scale.y = width;
    marker.scale.z = 0.25;
    marker.color.r = 1.0;
    marker.color.g = 0.8;
    marker.color.b = 0.0;
    marker.color.a = 0.2;

    visualization_msgs::InteractiveMarkerControl control;
    control.markers.push_back(marker);

    control.orientation.w    = 1;
    control.orientation.x    = 0;
    control.orientation.y    = 1;
    control.orientation.z    = 0;
    control.always_visible   = true;
    control.interaction_mode = visualization_msgs::InteractiveMarkerControl::MOVE_PLANE;
    int_marker.controls.push_back(control);

    visualization_msgs::Marker marker2;
    marker2.type    = visualization_msgs::Marker::CUBE;
    marker2.scale.x = (length) * 1.5;
    marker2.scale.y = width * 1.5;
    marker2.scale.z = 0.20;
    marker2.color.r = 0.5;
    marker2.color.g = 0.8;
    marker2.color.b = 0.0;
    marker2.color.a = 0.0;

    visualization_msgs::InteractiveMarkerControl control2;
    control2.markers.push_back(marker2);

    control2.orientation.w  = 1;
    control2.orientation.x  = 0;
    control2.orientation.y  = 1;
    control2.orientation.z  = 0;
    control2.always_visible = true;

    control2.interaction_mode = visualization_msgs::InteractiveMarkerControl::ROTATE_AXIS;
    int_marker.controls.push_back(control2);

    server_.insert(int_marker, boost::bind(&ObstatcleManager::ObstacleMoveCallback, this, _1, id));
    server_.applyChanges();
}

void ObstatcleManager::ObstacleMoveCallback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr& feedback, int id) {
    obstacle_set_[id].x     = feedback->pose.position.x;
    obstacle_set_[id].y     = feedback->pose.position.y;
    obstacle_set_[id].angle = tf::getYaw(feedback->pose.orientation) * 180 / M_PI;
}

void ObstatcleManager::update_obs_position() {
    for (int i = 0; i < obstacle_set_.size(); i++) {
        double   min_dis = DBL_MAX;
        Obstacle front_obs;
        front_obs.speed = DBL_MAX;
        front_obs.s     = DBL_MAX;
        for (int j = 0; j < obstacle_set_.size(); j++) {
            if (obstacle_set_[j].lane_id == obstacle_set_[i].lane_id) {
                double temp_dis_2_front = obstacle_set_[j].s - obstacle_set_[i].s;
                if (temp_dis_2_front > 0 && temp_dis_2_front < min_dis) {
                    min_dis   = temp_dis_2_front;
                    front_obs = obstacle_set_[j];
                }
            }
        }
        double expect_dis  = cal_expect_dis(obstacle_set_[i].min_dis, obstacle_set_[i].expect_t, obstacle_set_[i].speed, front_obs.speed, obstacle_set_[i].a_start, obstacle_set_[i].a_deacc);
        obstacle_set_[i].a = cal_IDM_a(obstacle_set_[i].a_max, obstacle_set_[i].speed, obstacle_set_[i].expect_speed, obstacle_set_[i].acc_coe, front_obs.s, obstacle_set_[i].s, obstacle_set_[i].min_dis, expect_dis);

        obstacle_set_[i].s = obstacle_set_[i].s + obstacle_set_[i].speed * delta_t;
        for (int k = 0; k < obstacle_set_[i].reference_path.size(); k++) {
            if (obstacle_set_[i].s <= obstacle_set_[i].reference_path[k].distance) {
                double delta_s         = obstacle_set_[i].reference_path[k].distance - obstacle_set_[i].s;
                double ratio           = delta_s / (obstacle_set_[i].reference_path[k].distance - obstacle_set_[i].reference_path[k - 1].distance);
                obstacle_set_[i].x     = obstacle_set_[i].reference_path[k - 1].x + ratio * (obstacle_set_[i].reference_path[k].x - obstacle_set_[i].reference_path[k - 1].x);
                obstacle_set_[i].y     = obstacle_set_[i].reference_path[k - 1].y + ratio * (obstacle_set_[i].reference_path[k].y - obstacle_set_[i].reference_path[k - 1].y);
                obstacle_set_[i].angle = obstacle_set_[i].reference_path[k - 1].heading_angle + ratio * (obstacle_set_[i].reference_path[k].heading_angle - obstacle_set_[i].reference_path[k - 1].heading_angle);
                break;
            }
        }
        obstacle_set_[i].speed = max(0.0, obstacle_set_[i].speed + obstacle_set_[i].a * delta_t);
    }
}

double ObstatcleManager::cal_expect_dis(double static_s, double expect_t, double ego_speed, double front_speed, double start_acc, double deacc_a) {
    return static_s + max(0.0, (expect_t * ego_speed + ego_speed * (ego_speed - front_speed)) / (2.0 * sqrt(start_acc * deacc_a)));
}

double ObstatcleManager::cal_IDM_a(double a_max, double ego_speed, double expect_speed, double acc_coe, double front_s, double ego_s, double static_dis, double expect_dis) {
    return a_max * (1.0 - pow((ego_speed / expect_speed), acc_coe) - pow(expect_dis / (front_s - ego_s - static_dis), 2));
}

msg_obj_fuse::msg_obj_fuse ObstatcleManager::obs_transfer() {
    msg_obj_fuse::msg_obj_fuse obs_set;
    for (int i = 0; i < obstacle_set_.size(); i++) {
        msg_obj::Obj temp_obj;
        temp_obj.id       = obstacle_set_[i].id;
        temp_obj.x        = obstacle_set_[i].x;
        temp_obj.y        = obstacle_set_[i].y;
        temp_obj.bbox_yaw = obstacle_set_[i].angle;
        cout << "temp_obj.bbox_yaw = " << temp_obj.bbox_yaw << endl;
        temp_obj.width  = obstacle_set_[i].width;
        temp_obj.length = obstacle_set_[i].length;
        temp_obj.vx     = obstacle_set_[i].speed * cos(obstacle_set_[i].angle * M_PI / 180.0);
        temp_obj.vy     = obstacle_set_[i].speed * sin(obstacle_set_[i].angle * M_PI / 180.0);
        temp_obj.ax     = obstacle_set_[i].a * cos(obstacle_set_[i].angle * M_PI / 180.0);
        temp_obj.ay     = obstacle_set_[i].a * sin(obstacle_set_[i].angle * M_PI / 180.0);

        temp_obj.contour_point.clear();
        msg_common::GridPoint grid_point;
        grid_point.x = temp_obj.x;
        grid_point.y = temp_obj.y;
        temp_obj.contour_point.push_back(grid_point);

        // 车辆安全包络左前角坐标
        grid_point.x = temp_obj.x + (temp_obj.length / 2) * cos(temp_obj.bbox_yaw * M_PI / 180.0) - (temp_obj.width / 2) * sin(temp_obj.bbox_yaw * M_PI / 180.0);
        grid_point.y = temp_obj.y + (temp_obj.length / 2) * sin(temp_obj.bbox_yaw * M_PI / 180.0) + (temp_obj.width / 2) * cos(temp_obj.bbox_yaw * M_PI / 180.0);
        temp_obj.contour_point.push_back(grid_point);
        // 车辆安全包络右前角坐标
        grid_point.x = temp_obj.x + (temp_obj.length / 2) * cos(temp_obj.bbox_yaw * M_PI / 180.0) + (temp_obj.width / 2) * sin(temp_obj.bbox_yaw * M_PI / 180.0);
        grid_point.y = temp_obj.y + (temp_obj.length / 2) * sin(temp_obj.bbox_yaw * M_PI / 180.0) - (temp_obj.width / 2) * cos(temp_obj.bbox_yaw * M_PI / 180.0);
        temp_obj.contour_point.push_back(grid_point);
        // 车辆安全包络左后角坐标
        grid_point.x = temp_obj.x + -(temp_obj.length / 2) * cos(temp_obj.bbox_yaw * M_PI / 180.0) - (temp_obj.width / 2) * sin(temp_obj.bbox_yaw * M_PI / 180.0);
        grid_point.y = temp_obj.y + -(temp_obj.length / 2) * sin(temp_obj.bbox_yaw * M_PI / 180.0) + (temp_obj.width / 2) * cos(temp_obj.bbox_yaw * M_PI / 180.0);
        temp_obj.contour_point.push_back(grid_point);
        // 车辆安全包络右后角坐标
        grid_point.x = temp_obj.x + -(temp_obj.length / 2) * cos(temp_obj.bbox_yaw * M_PI / 180.0) + (temp_obj.width / 2) * sin(temp_obj.bbox_yaw * M_PI / 180.0);
        grid_point.y = temp_obj.y + -(temp_obj.length / 2) * sin(temp_obj.bbox_yaw * M_PI / 180.0) - (temp_obj.width / 2) * cos(temp_obj.bbox_yaw * M_PI / 180.0);
        temp_obj.contour_point.push_back(grid_point);
        temp_obj.type = 0;
        obs_set.obj_fuse.emplace_back(temp_obj);
    }
    return obs_set;
}


ros::Publisher pub_grid_point; // for obstalce grid position
ros::Publisher pub_obs;        // for obstacle position
pub_obs          = nh.advertise<visualization_msgs::MarkerArray>("obstacle_position", 1);
pub_grids_points = nh.advertise<sensor_msgs::PointCloud>("grids_position", 1);

sensor_msgs::PointCloud         pc;
visualization_msgs::MarkerArray obstacle_markerarray_;

void datavisualizaton::Visualizaton::SetObstaclePosition() {
    visualization_msgs::Marker obstacle_marker;
    obstacle_marker.header.frame_id = "map";
    obstacle_marker.ns              = "my_namespace";
    obstacle_marker.type            = visualization_msgs::Marker::CUBE;
    obstacle_marker.action          = visualization_msgs::Marker::ADD;
    // obstacle_marker.lifetime        = ros::Duration(0.02);
    obstacle_marker.header.stamp = ros::Time();
    obstacle_marker.color.a      = 0.2;
    obstacle_marker.color.r      = 0.0;
    obstacle_marker.color.g      = 1.0;
    obstacle_marker.color.b      = 1.0;
    obstacle_markerarray_.markers.clear();
    int                        id = 0;
    visualization_msgs::Marker text_marker;
    text_marker.header.frame_id = "map";
    text_marker.ns              = "my_namespace";
    text_marker.type            = visualization_msgs::Marker::TEXT_VIEW_FACING;
    text_marker.ns              = "basic_shapes";
    text_marker.action          = visualization_msgs::Marker::ADD;
    // text_marker.lifetime        = ros::Duration(0.1);
    text_marker.header.stamp = ros::Time();
    text_marker.color.a      = 1.0;
    text_marker.color.r      = 0.0;
    text_marker.color.g      = 0.0;
    text_marker.color.b      = 0.0;
    for (auto& pt : obstacle_set_) {
        if (pt.contour_point.empty()) continue;
        obstacle_marker.id               = id++;
        obstacle_marker.pose.position.x  = pt.x;
        obstacle_marker.pose.position.y  = pt.y;
        obstacle_marker.pose.position.z  = pt.z;
        obstacle_marker.pose.orientation = tf::createQuaternionMsgFromYaw(pt.bbox_yaw * M_PI / 180);
        obstacle_marker.scale.x          = pt.length;
        obstacle_marker.scale.y          = pt.width;
        obstacle_marker.scale.z          = pt.height;
        text_marker.id                   = id++;
        text_marker.pose.position.x      = pt.x;
        text_marker.pose.position.y      = pt.y;
        text_marker.pose.position.z      = 3.5;
        text_marker.scale.x              = 0.0;
        text_marker.scale.y              = 0.0;
        text_marker.scale.z              = 0.2;
        text_marker.pose.orientation     = tf::createQuaternionMsgFromYaw(pt.bbox_yaw * M_PI / 180);
        ostringstream str;
        string        id = to_string(pt.id);
        str << id;
        text_marker.text = str.str(); // 文字内容
        obstacle_markerarray_.markers.push_back(text_marker);
        obstacle_markerarray_.markers.push_back(obstacle_marker);
    }
}

void datavisualizaton::Visualizaton::SetCountourPointsPosition() {
    pc.header.stamp    = ros::Time::now();
    pc.header.frame_id = "map";
    pc.points.clear();
    // pc.lifetime = ros::Duration(0.02);
    for (int i = 0; i < obstacle_set_.size(); i++) {
        // if (obstacle_set_.at(i).type != 6) continue;
        double farest_dis = std::sqrt(obstacle_set_.at(i).length * obstacle_set_.at(i).length + obstacle_set_.at(i).width * obstacle_set_.at(i).width + obstacle_set_.at(i).height * obstacle_set_.at(i).height) / 2.0;
        double count      = 0;
        for (int j = 0; j < obstacle_set_.at(i).contour_point.size(); j++) {
            double dis = std::sqrt(pow(obstacle_set_.at(i).contour_point.at(j).x - obstacle_set_.at(i).x, 2) + pow(obstacle_set_.at(i).contour_point.at(j).y - obstacle_set_.at(i).y, 2) + pow(obstacle_set_.at(i).contour_point.at(j).z - obstacle_set_.at(i).z, 2));
            if (dis > farest_dis) {
                count += 1.0;
                std::cout << "dis - farest_dis = " << dis - farest_dis << std::endl;
            }
            geometry_msgs::Point32 ros_pt;
            ros_pt.x = obstacle_set_.at(i).contour_point.at(j).x;
            ros_pt.y = obstacle_set_.at(i).contour_point.at(j).y;
            ros_pt.z = obstacle_set_.at(i).contour_point.at(j).z;
            pc.points.push_back(ros_pt);
        }
        if (!obstacle_set_.at(i).contour_point.empty()) {
            double ratio = count / obstacle_set_.at(i).contour_point.size();
            std::cout << "ratio = " << ratio << std::endl;
        }
    }
}


pub_obs.publish(obstacle_markerarray_);
pub_grids_points.publish(pc);