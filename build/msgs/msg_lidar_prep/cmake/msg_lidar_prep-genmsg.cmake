# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "msg_lidar_prep: 4 messages, 0 services")

set(MSG_I_FLAGS "-Imsg_lidar_prep:/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg;-Imsg_common:/home/yyf/global_planning_library/src/msgs/msg_common/msg;-Imsg_safety_diagn:/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg;-Imsg_obj:/home/yyf/global_planning_library/src/msgs/msg_obj/msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(msg_lidar_prep_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_diagn_lidar_prep.msg" NAME_WE)
add_custom_target(_msg_lidar_prep_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msg_lidar_prep" "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_diagn_lidar_prep.msg" "msg_common/Covariance:msg_obj/Obj:msg_common/GridPoint:msg_safety_diagn/DiagnDataStruct"
)

get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg" NAME_WE)
add_custom_target(_msg_lidar_prep_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msg_lidar_prep" "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg" ""
)

get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prepare.msg" NAME_WE)
add_custom_target(_msg_lidar_prep_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msg_lidar_prep" "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prepare.msg" "msg_lidar_prep/LidarPoints:msg_common/Time"
)

get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prep.msg" NAME_WE)
add_custom_target(_msg_lidar_prep_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msg_lidar_prep" "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prep.msg" "msg_lidar_prep/LidarPoints"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_diagn_lidar_prep.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_cpp(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_cpp(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prepare.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/Time.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_cpp(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prep.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_prep
)

### Generating Services

### Generating Module File
_generate_module_cpp(msg_lidar_prep
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_prep
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(msg_lidar_prep_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(msg_lidar_prep_generate_messages msg_lidar_prep_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_diagn_lidar_prep.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_cpp _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_cpp _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prepare.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_cpp _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prep.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_cpp _msg_lidar_prep_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_lidar_prep_gencpp)
add_dependencies(msg_lidar_prep_gencpp msg_lidar_prep_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_lidar_prep_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_diagn_lidar_prep.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_eus(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_eus(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prepare.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/Time.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_eus(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prep.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_prep
)

### Generating Services

### Generating Module File
_generate_module_eus(msg_lidar_prep
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_prep
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(msg_lidar_prep_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(msg_lidar_prep_generate_messages msg_lidar_prep_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_diagn_lidar_prep.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_eus _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_eus _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prepare.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_eus _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prep.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_eus _msg_lidar_prep_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_lidar_prep_geneus)
add_dependencies(msg_lidar_prep_geneus msg_lidar_prep_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_lidar_prep_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_diagn_lidar_prep.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_lisp(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_lisp(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prepare.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/Time.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_lisp(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prep.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_prep
)

### Generating Services

### Generating Module File
_generate_module_lisp(msg_lidar_prep
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_prep
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(msg_lidar_prep_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(msg_lidar_prep_generate_messages msg_lidar_prep_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_diagn_lidar_prep.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_lisp _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_lisp _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prepare.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_lisp _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prep.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_lisp _msg_lidar_prep_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_lidar_prep_genlisp)
add_dependencies(msg_lidar_prep_genlisp msg_lidar_prep_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_lidar_prep_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_diagn_lidar_prep.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_nodejs(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_nodejs(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prepare.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/Time.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_nodejs(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prep.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_prep
)

### Generating Services

### Generating Module File
_generate_module_nodejs(msg_lidar_prep
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_prep
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(msg_lidar_prep_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(msg_lidar_prep_generate_messages msg_lidar_prep_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_diagn_lidar_prep.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_nodejs _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_nodejs _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prepare.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_nodejs _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prep.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_nodejs _msg_lidar_prep_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_lidar_prep_gennodejs)
add_dependencies(msg_lidar_prep_gennodejs msg_lidar_prep_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_lidar_prep_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_diagn_lidar_prep.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_py(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_py(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prepare.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/Time.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_prep
)
_generate_msg_py(msg_lidar_prep
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prep.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_prep
)

### Generating Services

### Generating Module File
_generate_module_py(msg_lidar_prep
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_prep
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(msg_lidar_prep_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(msg_lidar_prep_generate_messages msg_lidar_prep_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_diagn_lidar_prep.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_py _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/LidarPoints.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_py _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prepare.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_py _msg_lidar_prep_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_lidar_prep/msg/msg_lidar_prep.msg" NAME_WE)
add_dependencies(msg_lidar_prep_generate_messages_py _msg_lidar_prep_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_lidar_prep_genpy)
add_dependencies(msg_lidar_prep_genpy msg_lidar_prep_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_lidar_prep_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_prep)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_lidar_prep
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET msg_common_generate_messages_cpp)
  add_dependencies(msg_lidar_prep_generate_messages_cpp msg_common_generate_messages_cpp)
endif()
if(TARGET msg_safety_diagn_generate_messages_cpp)
  add_dependencies(msg_lidar_prep_generate_messages_cpp msg_safety_diagn_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_prep)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_lidar_prep
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET msg_common_generate_messages_eus)
  add_dependencies(msg_lidar_prep_generate_messages_eus msg_common_generate_messages_eus)
endif()
if(TARGET msg_safety_diagn_generate_messages_eus)
  add_dependencies(msg_lidar_prep_generate_messages_eus msg_safety_diagn_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_prep)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_lidar_prep
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET msg_common_generate_messages_lisp)
  add_dependencies(msg_lidar_prep_generate_messages_lisp msg_common_generate_messages_lisp)
endif()
if(TARGET msg_safety_diagn_generate_messages_lisp)
  add_dependencies(msg_lidar_prep_generate_messages_lisp msg_safety_diagn_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_prep)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_lidar_prep
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET msg_common_generate_messages_nodejs)
  add_dependencies(msg_lidar_prep_generate_messages_nodejs msg_common_generate_messages_nodejs)
endif()
if(TARGET msg_safety_diagn_generate_messages_nodejs)
  add_dependencies(msg_lidar_prep_generate_messages_nodejs msg_safety_diagn_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_prep)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_prep\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_lidar_prep
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET msg_common_generate_messages_py)
  add_dependencies(msg_lidar_prep_generate_messages_py msg_common_generate_messages_py)
endif()
if(TARGET msg_safety_diagn_generate_messages_py)
  add_dependencies(msg_lidar_prep_generate_messages_py msg_safety_diagn_generate_messages_py)
endif()
