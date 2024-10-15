#rules
#如果这个工程没有编译过，那么我们的所有c文件都要编译并被链接。
#如果这个工程的某几个c文件被修改，那么我们只编译被修改的c文件，并链接目标程序。
#如果这个工程的头文件被改变了，那么我们需要编译引用了这几个头文件的c文件，并链接目标程序。
CC = gcc # C 编译器
CXX = g++ # C++ 编译器
CXXFLAGS = -fPIC -shared -std=c++17   -D SKIP_HEADER   -lstdc++fs  -O3  # C++ 编译选项，g 选项表示要将调试信息编译到可执行文件中
# LDFLAGS = -lhiredis 
# STATICLIBS = -lhiredis
# LDFLAGS += -leasylogging++
# LDFLAGS = -shared -Wl,--whole-archive $(STATICLIBS) -Wl,--no-whole-archive  
LDFLAGS = -L/usr/local/lib -ldl -pthread -Wl,-rpath,/usr/local/lib


# TARGET = ./lib/libGlobalPlanning-G_V1.0.0.20240702_RC.so
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
	  planner/pathplanner/hybirdastar/r_s_curve_for_h.cpp\
	  planner/speedplanner/global_speed_planning.cpp\
      smoother/path_opti.cpp\
	  smoother/dynamicvoronoi.cpp\
	  collision_check/collision_check.cpp\
	  planner/pathplanner/spline/spline.cpp

	  
OBJS = $(SRC:.cpp = .o)

$(TARGET): $(OBJS)  
	$(CXX) $(CXXFLAGS)  $^ $(LDFLAGS)  -o $@

	

.PHONY: clean
clean: 
	-rm $(TARGET) $(OBJS)