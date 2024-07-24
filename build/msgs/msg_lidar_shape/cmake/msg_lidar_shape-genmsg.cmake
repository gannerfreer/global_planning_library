# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "msg_lidar_shape: 7 messages, 0 services")

set(MSG_I_FLAGS "-Imsg_lidar_shape:/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/melodic/share/geometry_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/melodic/share/sensor_msgs/cmake/../msg;-Ivisualization_msgs:/opt/ros/melodic/share/visualization_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(msg_lidar_shape_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg" NAME_WE)
add_custom_target(_msg_lidar_shape_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msg_lidar_shape" "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg" "geometry_msgs/PoseStamped:visualization_msgs/Marker:sensor_msgs/PointField:msg_lidar_shape/DTLane:msg_lidar_shape/LaneArray:sensor_msgs/PointCloud2:msg_lidar_shape/WaypointState:std_msgs/Header:geometry_msgs/Twist:msg_lidar_shape/Waypoint:geometry_msgs/Vector3:sensor_msgs/Image:geometry_msgs/Pose:geometry_msgs/PolygonStamped:msg_lidar_shape/Lane:geometry_msgs/Point32:geometry_msgs/TwistStamped:std_msgs/ColorRGBA:geometry_msgs/Quaternion:geometry_msgs/Polygon:geometry_msgs/Point"
)

get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg" NAME_WE)
add_custom_target(_msg_lidar_shape_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msg_lidar_shape" "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg" ""
)

get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg" NAME_WE)
add_custom_target(_msg_lidar_shape_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msg_lidar_shape" "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg" "geometry_msgs/Pose:geometry_msgs/TwistStamped:msg_lidar_shape/WaypointState:msg_lidar_shape/DTLane:geometry_msgs/Twist:geometry_msgs/Vector3:msg_lidar_shape/Waypoint:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/PoseStamped:geometry_msgs/Point"
)

get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg" NAME_WE)
add_custom_target(_msg_lidar_shape_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msg_lidar_shape" "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg" ""
)

get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObjectArray.msg" NAME_WE)
add_custom_target(_msg_lidar_shape_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msg_lidar_shape" "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObjectArray.msg" "sensor_msgs/Image:msg_lidar_shape/DTLane:msg_lidar_shape/DetectedObject:std_msgs/Header:geometry_msgs/Vector3:geometry_msgs/Point32:geometry_msgs/PoseStamped:geometry_msgs/Point:sensor_msgs/PointField:sensor_msgs/PointCloud2:geometry_msgs/Quaternion:visualization_msgs/Marker:geometry_msgs/TwistStamped:std_msgs/ColorRGBA:msg_lidar_shape/Waypoint:msg_lidar_shape/WaypointState:geometry_msgs/Pose:geometry_msgs/Twist:msg_lidar_shape/LaneArray:geometry_msgs/Polygon:geometry_msgs/PolygonStamped:msg_lidar_shape/Lane"
)

get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg" NAME_WE)
add_custom_target(_msg_lidar_shape_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msg_lidar_shape" "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg" "geometry_msgs/TwistStamped:msg_lidar_shape/WaypointState:msg_lidar_shape/DTLane:geometry_msgs/Twist:geometry_msgs/Vector3:geometry_msgs/Pose:std_msgs/Header:geometry_msgs/Point:geometry_msgs/PoseStamped:geometry_msgs/Quaternion"
)

get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg" NAME_WE)
add_custom_target(_msg_lidar_shape_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msg_lidar_shape" "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg" "geometry_msgs/Pose:geometry_msgs/TwistStamped:msg_lidar_shape/WaypointState:msg_lidar_shape/DTLane:geometry_msgs/Twist:geometry_msgs/Vector3:msg_lidar_shape/Waypoint:geometry_msgs/Quaternion:std_msgs/Header:msg_lidar_shape/Lane:geometry_msgs/PoseStamped:geometry_msgs/Point"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_cpp(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_cpp(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_cpp(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_cpp(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_cpp(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_cpp(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_shape
)

### Generating Services

### Generating Module File
_generate_module_cpp(msg_lidar_shape
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_shape
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(msg_lidar_shape_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(msg_lidar_shape_generate_messages msg_lidar_shape_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_cpp _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_cpp _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_cpp _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_cpp _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObjectArray.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_cpp _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_cpp _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_cpp _msg_lidar_shape_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_lidar_shape_gencpp)
add_dependencies(msg_lidar_shape_gencpp msg_lidar_shape_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_lidar_shape_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_eus(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_eus(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_eus(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_eus(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_eus(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_eus(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_shape
)

### Generating Services

### Generating Module File
_generate_module_eus(msg_lidar_shape
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_shape
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(msg_lidar_shape_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(msg_lidar_shape_generate_messages msg_lidar_shape_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_eus _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_eus _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_eus _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_eus _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObjectArray.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_eus _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_eus _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_eus _msg_lidar_shape_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_lidar_shape_geneus)
add_dependencies(msg_lidar_shape_geneus msg_lidar_shape_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_lidar_shape_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_lisp(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_lisp(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_lisp(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_lisp(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_lisp(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_lisp(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_shape
)

### Generating Services

### Generating Module File
_generate_module_lisp(msg_lidar_shape
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_shape
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(msg_lidar_shape_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(msg_lidar_shape_generate_messages msg_lidar_shape_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_lisp _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_lisp _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_lisp _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_lisp _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObjectArray.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_lisp _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_lisp _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_lisp _msg_lidar_shape_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_lidar_shape_genlisp)
add_dependencies(msg_lidar_shape_genlisp msg_lidar_shape_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_lidar_shape_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_nodejs(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_nodejs(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_nodejs(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_nodejs(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_nodejs(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_nodejs(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_shape
)

### Generating Services

### Generating Module File
_generate_module_nodejs(msg_lidar_shape
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_shape
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(msg_lidar_shape_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(msg_lidar_shape_generate_messages msg_lidar_shape_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_nodejs _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_nodejs _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_nodejs _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_nodejs _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObjectArray.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_nodejs _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_nodejs _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_nodejs _msg_lidar_shape_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_lidar_shape_gennodejs)
add_dependencies(msg_lidar_shape_gennodejs msg_lidar_shape_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_lidar_shape_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_py(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_py(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_py(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/melodic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_py(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_py(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_shape
)
_generate_msg_py(msg_lidar_shape
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/TwistStamped.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_shape
)

### Generating Services

### Generating Module File
_generate_module_py(msg_lidar_shape
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_shape
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(msg_lidar_shape_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(msg_lidar_shape_generate_messages msg_lidar_shape_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_py _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_py _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_py _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_py _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObjectArray.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_py _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_py _msg_lidar_shape_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg" NAME_WE)
add_dependencies(msg_lidar_shape_generate_messages_py _msg_lidar_shape_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_lidar_shape_genpy)
add_dependencies(msg_lidar_shape_genpy msg_lidar_shape_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_lidar_shape_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_shape)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_shape
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(msg_lidar_shape_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(msg_lidar_shape_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(msg_lidar_shape_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET visualization_msgs_generate_messages_cpp)
  add_dependencies(msg_lidar_shape_generate_messages_cpp visualization_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_shape)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_shape
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(msg_lidar_shape_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(msg_lidar_shape_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(msg_lidar_shape_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()
if(TARGET visualization_msgs_generate_messages_eus)
  add_dependencies(msg_lidar_shape_generate_messages_eus visualization_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_shape)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_shape
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(msg_lidar_shape_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(msg_lidar_shape_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(msg_lidar_shape_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET visualization_msgs_generate_messages_lisp)
  add_dependencies(msg_lidar_shape_generate_messages_lisp visualization_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_shape)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_shape
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(msg_lidar_shape_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(msg_lidar_shape_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(msg_lidar_shape_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()
if(TARGET visualization_msgs_generate_messages_nodejs)
  add_dependencies(msg_lidar_shape_generate_messages_nodejs visualization_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_shape)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_shape\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_shape
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(msg_lidar_shape_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(msg_lidar_shape_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(msg_lidar_shape_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET visualization_msgs_generate_messages_py)
  add_dependencies(msg_lidar_shape_generate_messages_py visualization_msgs_generate_messages_py)
endif()
