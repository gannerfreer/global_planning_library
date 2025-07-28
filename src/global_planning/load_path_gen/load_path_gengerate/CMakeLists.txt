cmake_minimum_required(VERSION 3.10)
project(LoadPathGenerationProject)

# 设置C++标准（单独set命令）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 强制要求C++17

# 设置Python路径（单独set命令）
set(Python3_ROOT_DIR "/usr/bin/python3.8")

# 查找依赖库（分开find_package）
find_package(Eigen3 REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Development)
find_package(Python3 COMPONENTS Development REQUIRED)


# 包含头文件目录
include_directories(
    include
    ${EIGEN3_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/matplotlib-cpp
)

# 添加可执行文件
add_executable(LoadPathGeneration 
    src/main.cpp
    src/planner/clothoid_calculate/clothoid_for_connect.cpp
    src/planner/dubins/dubins.cpp
    src/planner/collision_check/collision_check.cpp
    src/planner/fitting_path_generate/fitting_path_generate.cpp
    src/planner/wait_point_generate/wait_point_generate.cpp
    src/planner/load_area_planning/load_area_planning.cpp
)

# 链接库（使用现代CMake目标）
target_link_libraries(LoadPathGeneration 
    PRIVATE
    Eigen3::Eigen
    Python3::Python  # 使用导入目标而非${Python3_LIBRARIES}
    PRIVATE Python3::Python
)

