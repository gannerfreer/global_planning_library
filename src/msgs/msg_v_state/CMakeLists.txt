cmake_minimum_required(VERSION 2.8.3)
project(msg_v_state)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED 
  roscpp
  msg_safety_diagn
  message_generation)

 add_message_files(
   FILES
   msg_diagn_v_state.msg
   msg_v_state.msg
#   Message2.msg
 )


## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   msg_safety_diagn
#   std_msgs  # Or other packages containing msgs
 )

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES msg_v_state
  CATKIN_DEPENDS message_runtime
#  DEPENDS system_lib
)

include_directories(
# include
# ${catkin_INCLUDE_DIRS}
)