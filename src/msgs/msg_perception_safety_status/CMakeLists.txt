cmake_minimum_required(VERSION 2.8.3)
project(msg_perception_safety_status)

find_package(catkin REQUIRED
  roscpp
  std_msgs
  message_generation
)

add_message_files(
  FILES
  SensorErrorInfo.msg
  msg_perception_safety_status.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS message_runtime
)
