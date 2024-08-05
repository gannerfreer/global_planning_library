# global_planning_library
## 开始
### 本地仿真
1、编译
> 进入src所在目录

> catkin_make

2、运行
> cd src所在目录

> ./run_all_nodes.sh  //日志位于/src/global_planning/simulation_log下
### 部署
1、编译
> cd src/global_planning/

> make //生成的动态库会放到lib目录下,名称为libGlobalPlanning.so
```
TARGET = lib/libGlobalPlanning.so
# SRC = src/shenyan.cpp \
#       src/collision_check.cpp \
#       src/path_opti.cpp \
# 	  src/optimal_path.cpp \
# 	  src/dubins.cpp \
# 	  src/r_s_curve.cpp \
# 	  src/c_global_speed_planning_test.cpp \
# 	  src/node2d.cpp \
# 	  src/spline.cpp\
# 	  src/dijkstra.cpp
SRC = interface.cpp \
      mine_global_planning/planning.cpp\
	  globalvariable.cpp \
      planner/pathplanner/dijkstra/dijkstra.cpp\
	  planner/pathplanner/hybirdastar/node2d.cpp\
	  planner/pathplanner/hybirdastar/optimal_path.cpp\
	  planner/pathplanner/hybirdastar/r_s_curve.cpp\
	  planner/speedplanner/global_speed_planning.cpp\
      math/opti/path_opti.cpp\
	  collision_check/collision_check.cpp\
	  planner/pathplanner/spline/spline.cpp
```
### 本地复现
> 更新src/global_planning/test下的test_input.json文件

> 更新src/global_planning/map下的map.json文件

>  cd src/global_planning/test/

> g++ -g  -std=c++11 test_so.cpp  -o test -ldl -pthread -lhiredis -D SKIP_HEADER //如果修改了test_so.cpp，需要重新编译生成新的test可执行文件

> ./test  //执行test脚本，日志位于当前log目录下，轨迹输出位于当前目录下
