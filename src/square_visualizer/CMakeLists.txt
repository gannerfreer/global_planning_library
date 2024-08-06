cmake_minimum_required(VERSION 2.8.3)  
project(square_visualizer)  
  
find_package(catkin REQUIRED COMPONENTS  
  roscpp  
  geometry_msgs  
  visualization_msgs  
  tf  
)  
  
catkin_package()  
  
include_directories(  
# include  
  ${catkin_INCLUDE_DIRS}  
)  
  
add_executable(square_visualizer_node src/square_visualizer_node.cpp)  
target_link_libraries(square_visualizer_node ${catkin_LIBRARIES})  
  
add_dependencies(square_visualizer_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})