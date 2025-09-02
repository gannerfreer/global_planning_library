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

#include "mine_global_planning/planning.h"
#include "mine_global_planning/predicting.h"
#include "msg_global_planning/msg_global_planning.h"

using namespace GlobalPlanning;
namespace fs = filesystem;
_SinglePoint                 start_point;
_SinglePoint                 end_point;
vector<geometry_msgs::Point> obstacle_v;
bool                         is_receive_start = false;
bool                         is_receive_end   = false;


const double x_o_ = 0; // 园区偏移参数
const double y_o_ = 0; // 园区偏移参数

vector<_TrajectoryPoint>         auto_vehicle_global_path, road_nodes;
vector<vector<_TrajectoryPoint>> human_vehicle_global_path;
vector<Point>                    expand_point;







void StartPositionCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg) {
    start_point.x   = msg->pose.pose.position.x;
    start_point.y   = msg->pose.pose.position.y;
    start_point.yaw = tf::getYaw(msg->pose.pose.orientation);
    // start_point.x   = -20.182964324951172 - x_o_;
    // start_point.y   = -56.12870788574219 - y_o_;
    // start_point.yaw = 38.89308130400649/ 180.0 * M_PI;

    is_receive_start = true;
}


void EndPositionCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
    end_point.x   = msg->pose.position.x;
    end_point.y   = msg->pose.position.y;
    end_point.yaw = tf::getYaw(msg->pose.orientation);
    // end_point.x   = 46.263710021972656 - x_o_;
    // end_point.y   = -34.0452995300293 - y_o_;
    // end_point.yaw = 56.257860551712604 / 180.0 * M_PI;


    is_receive_end = true;
}
void clickedPointCallback(const geometry_msgs::PointStamped::ConstPtr& msg) {
    cout << "clickedPointCallback" << endl;
    float                radius = 5.0; // 实际上，我们使用半径的两倍作为正方形的边长
    geometry_msgs::Point bp;
    for (int i = 0; i < 360; i++) {
        bp.x = msg->point.x + radius * cos(i / 180.0 * M_PI) + x_o_;
        bp.y = msg->point.y + radius * sin(i / 180.0 * M_PI) + y_o_;
        bp.z = 0;
        obstacle_v.push_back(bp);
    }
    cout << "obstacle_v.size():" << obstacle_v.size() << endl;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "n_global_planning");
    ros::NodeHandle nh;

    ros::Subscriber sub_start_point = nh.subscribe("/initialpose", 1000, StartPositionCallback);
    ros::Subscriber sub_end_point   = nh.subscribe("/move_base_simple/goal", 1000, EndPositionCallback);
    ros::Subscriber sub             = nh.subscribe("/clicked_point", 10, clickedPointCallback);
    ros::Publisher  pub_speed_curve = nh.advertise<std_msgs::Float64MultiArray>("speed_curve", 1);
    ros::Publisher  pub_global_path = nh.advertise<msg_global_planning::msg_global_planning>("global_path", 1);

    Planning   planning;
    Predicting predicting;
    string     logger_id  = "planning";
    string     logger_id2 = "predicting";

    // 创建 log 目录
    string dirPath                  = "src/global_planning/simulation_log/";
    string path_predicting_dir_path = "src/global_planning/path_predicting_log/";
    fs::create_directories(dirPath);
    fs::create_directories(path_predicting_dir_path);
    // 构造文件路径
    auto         currentTime = chrono::system_clock::now();
    time_t       timestamp   = chrono::system_clock::to_time_t(currentTime);
    stringstream ss;
    ss << put_time(localtime(&timestamp), "%Y-%m-%d-%H-%M-%S");
    string timeStr         = ss.str();
    string filePath        = dirPath + "/log_" + timeStr + ".log";
    planning.threadLogger_ = spdlog::rotating_logger_mt(logger_id, filePath, 10 * 1024 * 1024, 15, true);
    planning.threadLogger_->flush_on(spdlog::level::info);
    planning.threadLogger_->info("本地仿真环境日志");

    string path_predicting_filePath = path_predicting_dir_path + "/log_" + timeStr + ".log";
    predicting.threadLogger_        = spdlog::rotating_logger_mt(logger_id2, path_predicting_filePath, 10 * 1024 * 1024, 15, true);
    predicting.threadLogger_->flush_on(spdlog::level::info);
    predicting.threadLogger_->info("本地仿真环境日志");

    cout << "task_type:" << (int)planning.task_type_ << endl;
    ros::Rate            rate(10);
    vector<_BorderPoint> v_bp;
    _BorderPoint         bp;
    while (ros::ok()) {
        ros::spinOnce();
        // 将rviz输入的障碍物进行可视化
        planning.m_tar_rviz_data_.obstacle_v = obstacle_v;
        planning.c_rviz_.PubObstacles(planning.m_tar_rviz_data_.obstacle_v);
        // 将地图边界和参考路径发给rviz显示
        planning.c_rviz_.PubMapborderAndReferenceline(planning.m_tar_rviz_data_.vec_point);
        planning.c_rviz_.PubRoadNode(planning.m_tar_rviz_data_.road_node);
        // if (is_receive_start == true) {
        //     cout << "enter Predicting interface函数" << endl;
        //     is_receive_start          = false;
        //     predicting.start_point_.x = start_point.x + x_o_;
        //     predicting.start_point_.y = start_point.y + y_o_;
        //     if (start_point.yaw < 0) {
        //         start_point.yaw += 2 * M_PI;
        //     }
        //     predicting.start_point_.yaw = start_point.yaw / M_PI * 180;
        //     predicting.c_rviz_.PubStartPosition(start_point.x, start_point.y, start_point.yaw);
        //     cout << setprecision(11) << "m_start_point.x = " << predicting.start_point_.x << endl;
        //     cout << setprecision(11) << "m_start_point.y = " << predicting.start_point_.y << endl;
        //     predicting.threadLogger_->info("start_point.x ={}", predicting.start_point_.x);
        //     predicting.threadLogger_->info("start_point.y ={}", predicting.start_point_.y);
        //     predicting.threadLogger_->info("start_point.yaw ={}", predicting.start_point_.yaw);
        //     predicting.PredictingInterface(human_vehicle_global_path, 100);

        //     cout << "main-human_vehicle_global_path.size():" << human_vehicle_global_path.size() << endl;
        // }
        if (is_receive_start == false || is_receive_end == false) {}
        else {
            is_receive_start = false;
            is_receive_end   = false;

            planning.start_point_.x = start_point.x + x_o_;
            planning.start_point_.y = start_point.y + y_o_;
            if (start_point.yaw < 0) {
                start_point.yaw += 2 * M_PI;
            }
            planning.start_point_.yaw = start_point.yaw / M_PI * 180;

            planning.end_point_.x = end_point.x + x_o_;
            planning.end_point_.y = end_point.y + y_o_;
            if (end_point.yaw < 0) {
                end_point.yaw += 2 * M_PI;
            }
            planning.end_point_.yaw = end_point.yaw / M_PI * 180;

            //  cout << " planning.start_point.x = " <<  planning.start_point.x << "\n";


            // 将obstacle_v存入planning的inner_borders中
            if (!obstacle_v.empty()) {
                v_bp.clear();
                planning.machine_borders_.clear();
                for (int i = 0; i < obstacle_v.size(); i++) {
                    bp.x    = obstacle_v.at(i).x;
                    bp.y    = obstacle_v.at(i).y;
                    bp.z    = 0;
                    bp.type = 0;
                    v_bp.push_back(bp);
                }
                planning.machine_borders_.push_back(v_bp);
            }

            planning.c_rviz_.PubStartPosition(start_point.x, start_point.y, start_point.yaw);

            planning.c_rviz_.PubEndPosition(end_point.x, end_point.y, end_point.yaw);

            cout << setprecision(11) << "m_start_point.x = " << planning.start_point_.x << endl;
            cout << setprecision(11) << "m_start_point.y = " << planning.start_point_.y << endl;

            cout << setprecision(11) << "m_End_Point.x = " << planning.end_point_.x << endl;
            cout << setprecision(11) << "m_End_Point.y = " << planning.end_point_.y << endl;

            planning.threadLogger_->info("start_point.x ={}", planning.start_point_.x);
            planning.threadLogger_->info("start_point.y ={}", planning.start_point_.y);
            planning.threadLogger_->info("start_point.yaw ={}", planning.start_point_.yaw);
            planning.threadLogger_->info("end_point.x ={}", planning.end_point_.x);
            planning.threadLogger_->info("end_point.y ={}", planning.end_point_.y);
            planning.threadLogger_->info("end_point.yaw ={}", planning.end_point_.yaw);

            planning.GlobalPathPlanningInterface(auto_vehicle_global_path);
            cout << "error_code:" << static_cast<int>(planning.error_type_) << std::endl;

            cout << "main-auto_vehicle_global_path.size():" << auto_vehicle_global_path.size() << endl;

msg_global_planning::msg_global_planning temp_path;
            temp_path.way_point.clear();
            for (size_t jndex = 0; jndex < auto_vehicle_global_path.size(); jndex++) {
                msg_common::WayPoint temp_point;
                // temp_point.x             = auto_vehicle_global_path.at(jndex).x;
                // temp_point.y             = auto_vehicle_global_path.at(jndex).y;
                // temp_point.z             = auto_vehicle_global_path.at(jndex).z;
                // temp_point.heading_angle = auto_vehicle_global_path.at(jndex).yaw;
                temp_point.speed       = auto_vehicle_global_path.at(jndex).speed;
                temp_point.speed_limit = auto_vehicle_global_path.at(jndex).speed_limit;
                // temp_point.distance      = auto_vehicle_global_path.at(jndex).distance;
                // temp_point.direction     = auto_vehicle_global_path.at(jndex).direction;
                temp_path.way_point.emplace_back(temp_point);
            }
            pub_global_path.publish(temp_path);

          


            ofstream file_out;
            file_out.open("global_path.txt", ios::out);
            for (size_t i = 0; i < auto_vehicle_global_path.size(); i++) {
                // file_out << setprecision(11) << auto_vehicle_global_path.at(i).speed << " " << auto_vehicle_global_path.at(i).speed_limit << endl;
                file_out << auto_vehicle_global_path.at(i).x << " " << auto_vehicle_global_path.at(i).y << " " << 0 << " " << 0 << " " << auto_vehicle_global_path.at(i).yaw << " " << auto_vehicle_global_path.at(i).curvature << " " << auto_vehicle_global_path.at(i).speed << " " << auto_vehicle_global_path.at(i).distance << " " << 0 << " " << auto_vehicle_global_path.at(i).speed_limit << " " << static_cast<int>(auto_vehicle_global_path.at(i).direction) << " " << static_cast<int>(auto_vehicle_global_path.at(i).attribute) << endl;
            } //  x y left right angle curvature speed distance slope speed_limit direction attribute
            file_out.close();
            std_msgs::Float64MultiArray speed_curve;
            speed_curve.data.clear();
            for (size_t index = 0; index < auto_vehicle_global_path.size(); index++) {
                speed_curve.data.emplace_back(auto_vehicle_global_path.at(index).speed);
            }
            pub_speed_curve.publish(speed_curve);
            // spdlog::drop("example");
            auto cost_map = planning.my_optimal_path_.GetHCostMap();
            // cout << "midpoint_.x" << planning.my_optimal_path_.midpoint_.x << " midpoint_.y:" << planning.my_optimal_path_.midpoint_.y << endl;
            // cout << "cost_map.size():" << cost_map.size() << endl;
            planning.c_rviz_.Pub2DCostMap(cost_map, planning.my_optimal_path_.midpoint_);
        }


        //  cout << "aaglobal_path.size = " << auto_vehicle_global_path.size() <<  endl;
        planning.c_rviz_.PubGlobalPath(auto_vehicle_global_path);
        // predicting.c_rviz_.PubHumanVehGlobalPath(human_vehicle_global_path);

        expand_point.clear();
        expand_point = planning.my_optimal_path_.GetExpandPoint();
        // cout << "expand_point.size():" << expand_point.size() << endl;
        planning.c_rviz_.PubExpandPoint(expand_point, planning.my_optimal_path_.midpoint_);

        rate.sleep();
    }

    return 0;
}
