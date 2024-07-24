# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "msg_safety_diagn: 2 messages, 0 services")

set(MSG_I_FLAGS "-Imsg_safety_diagn:/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg;-Imsg_obj:/home/yyf/global_planning_library/src/msgs/msg_obj/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg;-Imsg_common:/home/yyf/global_planning_library/src/msgs/msg_common/msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(msg_safety_diagn_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/msg_safety_diagn.msg" NAME_WE)
add_custom_target(_msg_safety_diagn_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msg_safety_diagn" "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/msg_safety_diagn.msg" "msg_common/Covariance:msg_obj/Obj:msg_common/GridPoint:msg_safety_diagn/DiagnDataStruct"
)

get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg" NAME_WE)
add_custom_target(_msg_safety_diagn_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msg_safety_diagn" "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg" "msg_common/Covariance:msg_common/GridPoint:msg_obj/Obj"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(msg_safety_diagn
  "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/msg_safety_diagn.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_safety_diagn
)
_generate_msg_cpp(msg_safety_diagn
  "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_safety_diagn
)

### Generating Services

### Generating Module File
_generate_module_cpp(msg_safety_diagn
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_safety_diagn
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(msg_safety_diagn_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(msg_safety_diagn_generate_messages msg_safety_diagn_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/msg_safety_diagn.msg" NAME_WE)
add_dependencies(msg_safety_diagn_generate_messages_cpp _msg_safety_diagn_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg" NAME_WE)
add_dependencies(msg_safety_diagn_generate_messages_cpp _msg_safety_diagn_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_safety_diagn_gencpp)
add_dependencies(msg_safety_diagn_gencpp msg_safety_diagn_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_safety_diagn_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(msg_safety_diagn
  "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/msg_safety_diagn.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_safety_diagn
)
_generate_msg_eus(msg_safety_diagn
  "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_safety_diagn
)

### Generating Services

### Generating Module File
_generate_module_eus(msg_safety_diagn
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_safety_diagn
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(msg_safety_diagn_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(msg_safety_diagn_generate_messages msg_safety_diagn_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/msg_safety_diagn.msg" NAME_WE)
add_dependencies(msg_safety_diagn_generate_messages_eus _msg_safety_diagn_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg" NAME_WE)
add_dependencies(msg_safety_diagn_generate_messages_eus _msg_safety_diagn_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_safety_diagn_geneus)
add_dependencies(msg_safety_diagn_geneus msg_safety_diagn_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_safety_diagn_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(msg_safety_diagn
  "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/msg_safety_diagn.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_safety_diagn
)
_generate_msg_lisp(msg_safety_diagn
  "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_safety_diagn
)

### Generating Services

### Generating Module File
_generate_module_lisp(msg_safety_diagn
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_safety_diagn
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(msg_safety_diagn_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(msg_safety_diagn_generate_messages msg_safety_diagn_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/msg_safety_diagn.msg" NAME_WE)
add_dependencies(msg_safety_diagn_generate_messages_lisp _msg_safety_diagn_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg" NAME_WE)
add_dependencies(msg_safety_diagn_generate_messages_lisp _msg_safety_diagn_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_safety_diagn_genlisp)
add_dependencies(msg_safety_diagn_genlisp msg_safety_diagn_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_safety_diagn_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(msg_safety_diagn
  "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/msg_safety_diagn.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_safety_diagn
)
_generate_msg_nodejs(msg_safety_diagn
  "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_safety_diagn
)

### Generating Services

### Generating Module File
_generate_module_nodejs(msg_safety_diagn
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_safety_diagn
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(msg_safety_diagn_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(msg_safety_diagn_generate_messages msg_safety_diagn_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/msg_safety_diagn.msg" NAME_WE)
add_dependencies(msg_safety_diagn_generate_messages_nodejs _msg_safety_diagn_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg" NAME_WE)
add_dependencies(msg_safety_diagn_generate_messages_nodejs _msg_safety_diagn_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_safety_diagn_gennodejs)
add_dependencies(msg_safety_diagn_gennodejs msg_safety_diagn_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_safety_diagn_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(msg_safety_diagn
  "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/msg_safety_diagn.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_safety_diagn
)
_generate_msg_py(msg_safety_diagn
  "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg"
  "${MSG_I_FLAGS}"
  "/home/yyf/global_planning_library/src/msgs/msg_common/msg/Covariance.msg;/home/yyf/global_planning_library/src/msgs/msg_common/msg/GridPoint.msg;/home/yyf/global_planning_library/src/msgs/msg_obj/msg/Obj.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_safety_diagn
)

### Generating Services

### Generating Module File
_generate_module_py(msg_safety_diagn
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_safety_diagn
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(msg_safety_diagn_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(msg_safety_diagn_generate_messages msg_safety_diagn_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/msg_safety_diagn.msg" NAME_WE)
add_dependencies(msg_safety_diagn_generate_messages_py _msg_safety_diagn_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yyf/global_planning_library/src/msgs/msg_safety_diagn/msg/DiagnDataStruct.msg" NAME_WE)
add_dependencies(msg_safety_diagn_generate_messages_py _msg_safety_diagn_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msg_safety_diagn_genpy)
add_dependencies(msg_safety_diagn_genpy msg_safety_diagn_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msg_safety_diagn_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_safety_diagn)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msg_safety_diagn
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET msg_obj_generate_messages_cpp)
  add_dependencies(msg_safety_diagn_generate_messages_cpp msg_obj_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_safety_diagn)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msg_safety_diagn
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET msg_obj_generate_messages_eus)
  add_dependencies(msg_safety_diagn_generate_messages_eus msg_obj_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_safety_diagn)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msg_safety_diagn
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET msg_obj_generate_messages_lisp)
  add_dependencies(msg_safety_diagn_generate_messages_lisp msg_obj_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_safety_diagn)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msg_safety_diagn
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET msg_obj_generate_messages_nodejs)
  add_dependencies(msg_safety_diagn_generate_messages_nodejs msg_obj_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_safety_diagn)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_safety_diagn\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msg_safety_diagn
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET msg_obj_generate_messages_py)
  add_dependencies(msg_safety_diagn_generate_messages_py msg_obj_generate_messages_py)
endif()
