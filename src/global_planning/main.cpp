#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <ros/ros.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/String.h>
#include <tf/transform_datatypes.h>

#include <filesystem>
#include <fstream>

#include "../include/shenyan.h"
#include "msg_global_planning/msg_global_planning.h"

using namespace GlobalPlanning;
namespace fs = std::filesystem;
_SinglePoint start_point;
_SinglePoint end_point;
bool         is_receive_start = false;
bool         is_receive_end   = false;

// const double x_o_ = -1171.654151; // 玖智偏移参数
// const double y_o_ = 6205.765819;  // 玖智偏移参数

// const double x_o_ = -321737.4857;     // 舒兰偏移参数
// const double y_o_ = 534463.584699999; // 舒兰偏移参数

const double x_o_ = 0; // 鲁南偏移参数
const double y_o_ = 0; // 鲁南偏移参数

// const double x_o_ = -205293.9231; // 致富偏移参数
// const double y_o_ = 7973.5012;    // 致富偏移参数

std::vector<Trajectory_Point> global_path;

void StartPositionCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg) {
    start_point.x   = msg->pose.pose.position.x;
    start_point.y   = msg->pose.pose.position.y;
    start_point.yaw = tf::getYaw(msg->pose.pose.orientation);
    // start_point.x = -80.36298370361328 - x_o_;
    // start_point.y = -7.795932769775391 - y_o_;
    // start_point.yaw = 353.44797 / 180.0 * M_PI;

    is_receive_start = true;
}

void EndPositionCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
    end_point.x   = msg->pose.position.x;
    end_point.y   = msg->pose.position.y;
    end_point.yaw = tf::getYaw(msg->pose.orientation);
    // end_point.x = 178.6564483642578 - x_o_;
    // end_point.y = 37.87535095214844 - y_o_;
    // end_point.yaw = 15.316479 / 180.0 * M_PI;

    is_receive_end = true;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "n_global_planning");
    ros::NodeHandle nh;

    ros::Subscriber sub_start_point = nh.subscribe("/initialpose", 1000, StartPositionCallback);
    ros::Subscriber sub_end_point   = nh.subscribe("/move_base_simple/goal", 1000, EndPositionCallback);
    ros::Publisher  pub_speed_curve = nh.advertise<std_msgs::Float64MultiArray>("speed_curve", 1);
    ros::Publisher  pub_global_path = nh.advertise<msg_global_planning::msg_global_planning>("global_path", 1);

    Shenyan shenyan;
    string  logger_id = "example";

    // 创建 log 目录
    std::string dirPath = "src/global_planning/simulation_log/";
    fs::create_directories(dirPath);
    // 构造文件路径
    auto              currentTime = std::chrono::system_clock::now();
    std::time_t       timestamp   = std::chrono::system_clock::to_time_t(currentTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
    std::string timeStr  = ss.str();
    std::string filePath = dirPath + "/log_" + timeStr + ".txt";
    // spdlog::flush_on(spdlog::level::info);
    shenyan.threadLogger_ = spdlog::rotating_logger_mt(logger_id, filePath, 3 * 1024 * 1024, 1, true);
    shenyan.threadLogger_->flush_on(spdlog::level::info);
    shenyan.threadLogger_->info("本地仿真环境日志");
    cout << "task_type:" << (int)shenyan.task_type_ << endl;
    ros::Rate rate(10);

    while (ros::ok()) {
        ros::spinOnce();
        // shenyan.c_rviz_.PeripheryPark(1,shenyan.m_tar_rviz_data.vec_point);
        shenyan.c_rviz_.SetAreaPath(shenyan.m_tar_rviz_data_.vec_point);
        // std::cout<< "1111111111111" << std::endl;

        if (is_receive_start == false || is_receive_end == false) {
            // rate.sleep();
            // continue;
        }
        else {
            is_receive_start = false;
            is_receive_end   = false;

            shenyan.start_point_.x = start_point.x + x_o_;
            shenyan.start_point_.y = start_point.y + y_o_;
            if (start_point.yaw < 0) {
                start_point.yaw += 2 * M_PI;
            }
            shenyan.start_point_.yaw = start_point.yaw / M_PI * 180;

            shenyan.end_point_.x = end_point.x + x_o_;
            shenyan.end_point_.y = end_point.y + y_o_;
            if (end_point.yaw < 0) {
                end_point.yaw += 2 * M_PI;
            }
            shenyan.end_point_.yaw = end_point.yaw / M_PI * 180;

            // std::cout << "shenyan.start_point.x = " << shenyan.start_point.x << "\n";

            shenyan.c_rviz_.SetStartPosition(start_point.x, start_point.y, start_point.yaw);
            shenyan.c_rviz_.SetEndPosition(end_point.x, end_point.y, end_point.yaw);
            shenyan.c_rviz_.PublishStart();
            shenyan.c_rviz_.PublishEnd();

            std::cout << setprecision(11) << "m_start_point.x = " << shenyan.start_point_.x << std::endl;
            std::cout << setprecision(11) << "m_start_point.y = " << shenyan.start_point_.y << std::endl;

            std::cout << setprecision(11) << "m_End_Point.x = " << shenyan.end_point_.x << std::endl;
            std::cout << setprecision(11) << "m_End_Point.y = " << shenyan.end_point_.y << std::endl;

            shenyan.threadLogger_->info("start_point.x ={}", shenyan.start_point_.x);
            shenyan.threadLogger_->info("start_point.y ={}", shenyan.start_point_.y);
            shenyan.threadLogger_->info("start_point.yaw ={}", shenyan.start_point_.yaw);
            shenyan.threadLogger_->info("end_point.x ={}", shenyan.end_point_.x);
            shenyan.threadLogger_->info("end_point.y ={}", shenyan.end_point_.y);
            shenyan.threadLogger_->info("end_point.yaw ={}", shenyan.end_point_.yaw);

            shenyan.GlobalPathPlanningIntface(global_path);

            cout << "global_path.size():" << global_path.size() << endl;

            msg_global_planning::msg_global_planning temp_path;
            temp_path.way_point.clear();
            for (size_t jndex = 0; jndex < global_path.size(); jndex++) {
                msg_common::WayPoint temp_point;
                temp_point.x             = global_path.at(jndex).x;
                temp_point.y             = global_path.at(jndex).y;
                temp_point.z             = global_path.at(jndex).z;
                temp_point.heading_angle = global_path.at(jndex).yaw;
                temp_point.left          = global_path.at(jndex).left;
                temp_point.right         = global_path.at(jndex).right;
                temp_point.speed         = global_path.at(jndex).speed;
                temp_point.speed_limit   = global_path.at(jndex).speed_limit;
                temp_point.slope         = global_path.at(jndex).slope;
                temp_point.distance      = global_path.at(jndex).distance;
                temp_point.direction     = global_path.at(jndex).direction;
                temp_path.way_point.emplace_back(temp_point);
            }
            pub_global_path.publish(temp_path);

            cout << "line171" << endl;
            std::ofstream file_out;
            file_out.open("global_path.txt", std::ios::out);
            for (size_t i = 0; i < global_path.size(); i++) {
                // file_out << std::setprecision(11)
                //          << global_path.at(i).x << " "
                //          << global_path.at(i).y << " "
                //          << global_path.at(i).z << " "
                //          << global_path.at(i).yaw << " "
                //          << global_path.at(i).left << " "
                //          << global_path.at(i).right << " "
                //          << global_path.at(i).speed << " "
                //          << global_path.at(i).speed_limit << " "
                //          << global_path.at(i).curvature << " "
                //          << global_path.at(i).distance << " "
                //          << static_cast<int>(global_path.at(i).attribute) << " "
                //          << static_cast<int>(global_path.at(i).direction) << std::endl;
                file_out << std::setprecision(11) << global_path.at(i).x << " " << global_path.at(i).y << " "
                         << global_path.at(i).z << " " << global_path.at(i).yaw << " " << global_path.at(i).speed << " "
                         << global_path.at(i).speed_limit << " " << global_path.at(i).curvature << " "
                         << static_cast<int>(global_path.at(i).direction) << " "
                         << static_cast<int>(global_path.at(i).attribute) << " " << global_path.at(i).distance
                         << std::endl;
            }
            file_out.close();
            cout << "line202" << endl;
            std_msgs::Float64MultiArray speed_curve;
            speed_curve.data.clear();
            for (size_t index = 0; index < global_path.size(); index++) {
                speed_curve.data.emplace_back(global_path.at(index).speed);
            }
            pub_speed_curve.publish(speed_curve);
            cout << "line210" << endl;
            // rate.sleep();
        }

        // std::cout << "aaglobal_path.size = " << global_path.size() << std::endl;
        shenyan.c_rviz_.PubGlobalPath(global_path);
        // shenyan.c_rviz_.PubTurningPathParagraph(turning_path_paragraph);
        // shenyan.c_rviz_.PubTurningPathParagraphAnother(turning_path_paragraph_another);

        auto cost_map = shenyan.my_optimal_path_.GetHCostMap();
        shenyan.c_rviz_.Set2DCostMap(cost_map, shenyan.my_optimal_path_.midpoint_);
        rate.sleep();
        cout << "line222" << endl;
    }
    // spdlog::drop("example");

    return 0;
}
