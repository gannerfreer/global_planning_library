# Install script for directory: /home/yyf/global_planning_library/src

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
  
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
        file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
      endif()
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin")
        file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin" "")
      endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/yyf/global_planning_library/install/_setup_util.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/yyf/global_planning_library/install" TYPE PROGRAM FILES "/home/yyf/global_planning_library/build/catkin_generated/installspace/_setup_util.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/yyf/global_planning_library/install/env.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/yyf/global_planning_library/install" TYPE PROGRAM FILES "/home/yyf/global_planning_library/build/catkin_generated/installspace/env.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/yyf/global_planning_library/install/setup.bash;/home/yyf/global_planning_library/install/local_setup.bash")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/yyf/global_planning_library/install" TYPE FILE FILES
    "/home/yyf/global_planning_library/build/catkin_generated/installspace/setup.bash"
    "/home/yyf/global_planning_library/build/catkin_generated/installspace/local_setup.bash"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/yyf/global_planning_library/install/setup.sh;/home/yyf/global_planning_library/install/local_setup.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/yyf/global_planning_library/install" TYPE FILE FILES
    "/home/yyf/global_planning_library/build/catkin_generated/installspace/setup.sh"
    "/home/yyf/global_planning_library/build/catkin_generated/installspace/local_setup.sh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/yyf/global_planning_library/install/setup.zsh;/home/yyf/global_planning_library/install/local_setup.zsh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/yyf/global_planning_library/install" TYPE FILE FILES
    "/home/yyf/global_planning_library/build/catkin_generated/installspace/setup.zsh"
    "/home/yyf/global_planning_library/build/catkin_generated/installspace/local_setup.zsh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/yyf/global_planning_library/install/.rosinstall")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/yyf/global_planning_library/install" TYPE FILE FILES "/home/yyf/global_planning_library/build/catkin_generated/installspace/.rosinstall")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/yyf/global_planning_library/build/gtest/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_common/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_perception_safety_status/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_obj/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_safety_diagn/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_global_planning/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_gnss_prep/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_hd_map/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_imu_prep/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_info_router/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_lidar_odom/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_lidar_prep/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_local_planning/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_map_collect/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_obj_fuse/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_radar_obj/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_radar_prep/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_safety_record/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/ms_update_map/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_v_control/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_v_decision/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_v_prep/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_v_state/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/msgs/msg_lidar_shape/cmake_install.cmake")
  include("/home/yyf/global_planning_library/build/global_planning/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/yyf/global_planning_library/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
