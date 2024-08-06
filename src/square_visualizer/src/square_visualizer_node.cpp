#include <geometry_msgs/PointStamped.h>
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>

#include "iostream"
using namespace std;
visualization_msgs::Marker marker;
// 回调函数，处理从/clicked_point接收到的点
void clickedPointCallback(const geometry_msgs::PointStamped::ConstPtr& msg) {
    cout << "clickedPointCallback" << endl;
    // // 初始化ROS节点句柄和TF监听器
    // // ros::NodeHandle       nh;
    // tf::TransformListener listener;

    // // 等待TF变换数据变得可用
    // try {
    //     listener.waitForTransform("/map", msg->header.frame_id, msg->header.stamp, ros::Duration(1.0));
    // } catch (tf::TransformException& ex) {
    //     ROS_ERROR("%s", ex.what());
    //     return;
    // }

    // 计算正方形的四个顶点
    // tf::StampedTransform transform;
    // listener.lookupTransform("/map", msg->header.frame_id, msg->header.stamp, transform);

    float radius    = 10.0; // 实际上，我们使用半径的两倍作为正方形的边长
    float half_side = radius * 2.0;

    // 创建四个点的Marker
    marker.points.clear();
    marker.header.frame_id    = "/map";
    marker.header.stamp       = ros::Time::now();
    marker.ns                 = "square_markers";
    marker.id                 = 0;
    marker.type               = visualization_msgs::Marker::POINTS;
    marker.action             = visualization_msgs::Marker::ADD;
    marker.pose.orientation.w = 1.0;
    marker.scale.x            = 1.0;
    marker.scale.y            = 1.0;
    marker.scale.z            = 1.0;
    marker.color.r            = 1.0; // 红色
    marker.color.g            = 0.0; // 绿色
    marker.color.b            = 0.0; // 蓝色
    marker.color.a            = 1.0; // 透明度（完全不透明）

    // 添加四个顶点到marker的points数组
    geometry_msgs::Point point;
    point.x = msg->point.x + radius;
    point.y = msg->point.y + radius;
    point.z = 0.0;
    marker.points.push_back(point);

    point.x = msg->point.x + radius;
    point.y = msg->point.y - radius;
    marker.points.push_back(point);

    point.x = msg->point.x - radius;
    point.y = msg->point.y + radius;
    marker.points.push_back(point);

    point.x = msg->point.x - radius;
    point.y = msg->point.y - radius;
    marker.points.push_back(point);
    cout << "marker.points.size():" << marker.points.size() << endl;
    // for (int i = 0; i <)

    // 发布Marker
}
int main(int argc, char** argv) {
    ros::init(argc, argv, "square_visualizer");
    ros::NodeHandle nh;

    // 订阅/clicked_point话题
    ros::Subscriber sub = nh.subscribe("/clicked_point", 10, clickedPointCallback);

    ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    ros::Rate      loop_rate(10);
    while (ros::ok()) {
        marker_pub.publish(marker);
        ros::spinOnce();
        loop_rate.sleep();
    }


    return 0;
}
