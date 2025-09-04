# 如果工程未编译，编译所有C文件；若文件修改，仅编译修改文件；若头文件修改，编译引用该头文件的C文件
CC = gcc 
CXX = g++
CXXFLAGS = -fPIC -shared -std=c++17 -D SKIP_HEADER -D OSQP_EIGEN_OSQP_IS_V1 -D OSQP_EIGEN_OSQP_IS_V1_FINAL -lstdc++fs -O3 -I/usr/include/eigen3  -I/usr/local/include/osqp -I/usr/local/include/OsqpEigen
LDFLAGS = -L/usr/local/lib -Wl,-rpath,$(CURDIR)/lib/deps -Wl,-rpath,/usr/local/lib -ldl -pthread

TARGET = lib/libGlobalPlanning.so

# 源文件列表
SRC = interface.cpp \
      mine_global_planning/planning.cpp\
      mine_global_planning/predicting.cpp\
      globalvariable.cpp \
      planner/pathplanner/dijkstra/dijkstra.cpp\
      planner/pathplanner/dubins/dubins.cpp\
      planner/pathplanner/hybirdastar/node2d.cpp\
      planner/pathplanner/hybirdastar/optimal_path.cpp\
      planner/pathplanner/hybirdastar/r_s_curve.cpp\
      planner/speedplanner/global_speed_planning.cpp\
      smoother/path_opti.cpp\
      smoother/tension_smoother_2.cpp\
      collision_check/collision_check.cpp\
	  collision_check/box2d.cpp\
      planner/pathplanner/spline/spline.cpp\
	  load_area_planning/load_area_planning.cpp\
	  load_area_planning/wait_point_generate.cpp\
	  load_area_planning/fitting_path_generate.cpp
		  

# 构建目录，用于存放临时文件
BUILD_DIR = build

# 将目标文件和依赖文件放在build目录下，保持与源文件相同的目录结构
OBJS = $(addprefix $(BUILD_DIR)/, $(SRC:.cpp=.o))
DEPS = $(OBJS:.o=.d)

# 确保所需目录存在
$(shell mkdir -p lib lib/deps $(addprefix $(BUILD_DIR)/, $(dir $(SRC))))

# 主目标：链接动态库
$(TARGET): $(OBJS)  
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -lipopt -lcppad_lib -losqp -lOsqpEigen -o $@
	@echo "已生成动态库: $@"

# 通用编译规则：包含依赖检测，将.o文件放入build目录
$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@
	@echo "已编译: $< -> $@"

# 包含依赖文件
-include $(DEPS)

.PHONY: clean package
clean: 
	-rm -f $(TARGET)
	-rm -rf $(BUILD_DIR) lib
	@echo "清理完成"

package: $(TARGET)
	# 打包依赖库
	cp /usr/local/lib/libipopt.so* lib/deps/ || true
	cp /usr/local/lib/libcppad_lib.so lib/deps/ || true
	cp /usr/local/lib/libosqp.so* lib/deps/ || true
	cp /usr/local/lib/libOsqpEigen.so* lib/deps/ || true
	@echo "打包完成，依赖库已复制到lib/deps目录"
