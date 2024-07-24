# Install script for directory: /home/yyf/global_planning_library/src/msgs/msg_lidar_shape

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/yyf/global_planning_library/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/msg_lidar_shape/msg" TYPE FILE FILES
    "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObject.msg"
    "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DetectedObjectArray.msg"
    "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/DTLane.msg"
    "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Lane.msg"
    "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/LaneArray.msg"
    "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/Waypoint.msg"
    "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/msg/WaypointState.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/msg_lidar_shape/cmake" TYPE FILE FILES "/home/yyf/global_planning_library/build/msgs/msg_lidar_shape/catkin_generated/installspace/msg_lidar_shape-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/yyf/global_planning_library/devel/include/msg_lidar_shape")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/yyf/global_planning_library/devel/share/roseus/ros/msg_lidar_shape")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/yyf/global_planning_library/devel/share/common-lisp/ros/msg_lidar_shape")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/yyf/global_planning_library/devel/share/gennodejs/ros/msg_lidar_shape")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/yyf/global_planning_library/devel/lib/python2.7/dist-packages/msg_lidar_shape")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/yyf/global_planning_library/devel/lib/python2.7/dist-packages/msg_lidar_shape")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/yyf/global_planning_library/build/msgs/msg_lidar_shape/catkin_generated/installspace/msg_lidar_shape.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/msg_lidar_shape/cmake" TYPE FILE FILES "/home/yyf/global_planning_library/build/msgs/msg_lidar_shape/catkin_generated/installspace/msg_lidar_shape-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/msg_lidar_shape/cmake" TYPE FILE FILES
    "/home/yyf/global_planning_library/build/msgs/msg_lidar_shape/catkin_generated/installspace/msg_lidar_shapeConfig.cmake"
    "/home/yyf/global_planning_library/build/msgs/msg_lidar_shape/catkin_generated/installspace/msg_lidar_shapeConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/msg_lidar_shape" TYPE FILE FILES "/home/yyf/global_planning_library/src/msgs/msg_lidar_shape/package.xml")
endif()

