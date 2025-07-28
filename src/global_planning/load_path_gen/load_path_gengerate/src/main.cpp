#include <cmath>
#include <iostream>
#define _USE_MATH_DEFINES // 启用M_PI常量

#include <chrono>

#include "../include/planner/clothoid_calculate/clothoid_for_connect.h"
#include "../include/planner/clothoid_calculate/test.h"
#include "../include/planner/collision_check/collision_check.h"
#include "../include/planner/dubins/dubins.h"
#include "../include/planner/fitting_path_generate/fitting_path_generate.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

void VisualizeTrajectory(const std::vector<GlobalPlanning::_TrajectoryPoint>& line, const std::vector<GlobalPlanning::_TrajectoryPoint>& arc, const GlobalPlanning::_SinglePoint& arc_center) {
    // 提取坐标
    std::vector<double> line_x, line_y, arc_x, arc_y;
    for (const auto& p : line) {
        line_x.push_back(p.x);
        line_y.push_back(p.y);
    }
    for (const auto& p : arc) {
        arc_x.push_back(p.x);
        arc_y.push_back(p.y);
    }

    // 创建属性map（正确格式）
    std::map<std::string, std::string> line_style = {
        {"label", "Line"},
        {"color", "b"   }
    };
    std::map<std::string, std::string> arc_style = {
        {"label", "Arc"},
        {"color", "r"  }
    };

    // 绘制
    plt::plot(line_x, line_y, line_style);
    plt::plot(arc_x, arc_y, arc_style);

    plt::title("Line + Arc Trajectory");
    plt::xlabel("X (m)");
    plt::ylabel("Y (m)");
    plt::legend();
    plt::grid(true);
    plt::axis("equal");
    plt::show();
}

GlobalPlanning::Bound readBorderFile(const std::string& filename) {
    GlobalPlanning::Bound points;
    std::ifstream         inFile(filename);

    if (!inFile) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return points;
    }

    std::string                             line;
    int                                     lineNum = 0;
    GlobalPlanning::Coordinate              temp_bound_point;
    std::vector<GlobalPlanning::Coordinate> temp_points_line;
    while (std::getline(inFile, line)) {
        lineNum++;
        // 移除前后空白字符
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (line.empty()) continue; // 跳过空行

        // 检查格式
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) {
            std::cerr << "格式错误(行 " << lineNum << "): 缺少逗号分隔符 -> " << line << std::endl;
            continue;
        }

        try {
            temp_bound_point.x = std::stof(line.substr(0, commaPos));
            temp_bound_point.y = std::stof(line.substr(commaPos + 1));
            temp_points_line.emplace_back(temp_bound_point);
        } catch (const std::exception& e) {
            std::cerr << "数值转换错误(行 " << lineNum << "): " << line << " (" << e.what() << ")" << std::endl;
        }
    }
    points.emplace_back(temp_points_line);

    std::cout << "从 " << filename << " 成功读取 " << points.front().size() << " 个点" << std::endl;
    return points;
}

void VisualizeDepartCandidates(const std::vector<std::pair<GlobalPlanning::Path, double>>& depart_candi_pathes) {
    // 设置颜色循环，使每条路径有不同的颜色
    std::vector<std::string> colors = {"b", "g", "r", "c", "m", "y", "k"};

    // 创建图形
    plt::figure_size(1200, 800);

    // 绘制每条候选路径
    for (size_t i = 0; i < depart_candi_pathes.size(); ++i) {
        if (i > 0) {
            break;
        }
        const auto&         path = depart_candi_pathes[i].first;
        std::vector<double> x_vals, y_vals;

        for (const auto& point : path) {
            x_vals.push_back(point.x);
            y_vals.push_back(point.y);
        }

        // 使用循环颜色，如果路径数多于颜色数则循环使用
        std::string color = colors[i % colors.size()];
        std::string label = "Path " + std::to_string(i + 1) + " (cost: " + std::to_string(depart_candi_pathes[i].second) + ")";

        plt::plot(x_vals, y_vals,
                  {
                      {"color",     color},
                      {"label",     label},
                      {"linewidth", "1.5"}
        });

        // 标记起点和终点
        if (!path.empty()) {
            plt::plot(
                {
                    path.front().x
            },
                {path.front().y}, {{"marker", "o"}, {"color", color}, {"markersize", "5"}});
            plt::plot(
                {
                    path.back().x
            },
                {path.back().y}, {{"marker", "s"}, {"color", color}, {"markersize", "5"}});
        }
    }

    // 设置图形属性
    plt::title("Departure Candidate Paths");
    plt::xlabel("X (m)");
    plt::ylabel("Y (m)");
    plt::legend({
        {"loc", "upper right"}
    });
    plt::grid(true);
    plt::axis("equal");

    // 显示图形
    plt::show();
}
std::string to_hex(int value) {
    value                  = std::clamp(value, 0, 255); // 确保值在有效范围
    const char hex_chars[] = "0123456789ABCDEF";
    return {
        hex_chars[(value >> 4) & 0xF], // 高4位
        hex_chars[value & 0xF]         // 低4位
    };
}

void VisualizeCombined(const GlobalPlanning::Bound& static_border, const GlobalPlanning::Bound& wall_border, const GlobalPlanning::Bound& obs_border, const GlobalPlanning::Path& unload_path, const std::vector<std::pair<GlobalPlanning::Path, double>>& depart_candi_pathes, const GlobalPlanning::Path& depart_path) {
    // 创建图形
    plt::figure_size(1200, 800);

    // 1. 绘制环境部分 ---------------------------------------------------

    // 绘制静态边界(蓝色)
    if (!static_border.empty()) {
        std::vector<double> static_x, static_y;
        for (const auto& point : static_border[0]) {
            static_x.push_back(point.x);
            static_y.push_back(point.y);
        }
        // 闭合多边形
        // static_x.push_back(static_border[0][0].x);
        // static_y.push_back(static_border[0][0].y);

        plt::scatter(static_x, static_y);
    }

    // 绘制墙边界(红色)
    if (!wall_border.empty()) {
        std::vector<double> wall_x, wall_y;
        for (const auto& point : wall_border[0]) {
            wall_x.push_back(point.x);
            wall_y.push_back(point.y);
        }
        // 闭合多边形
        wall_x.push_back(wall_border[0][0].x);
        wall_y.push_back(wall_border[0][0].y);

        plt::scatter(wall_x, wall_y);
    }

    // 绘制障碍物边界(绿色)
    if (!obs_border.empty()) {
        std::vector<double> obs_x, obs_y;
        for (const auto& point : obs_border[0]) {
            obs_x.push_back(point.x);
            obs_y.push_back(point.y);
        }
        // 闭合多边形
        obs_x.push_back(obs_border[0][0].x);
        obs_y.push_back(obs_border[0][0].y);

        plt::scatter(obs_x, obs_y);
    }

    // 绘制卸载路径(黑色带箭头)
    if (!unload_path.empty()) {
        std::vector<double> unload_x, unload_y;
        for (const auto& point : unload_path) {
            unload_x.push_back(point.x);
            unload_y.push_back(point.y);
        }

        plt::plot(unload_x, unload_y,
                  {
                      {"label",     "Unload Path"},
                      {"color",     "k"          },
                      {"linestyle", "-"          },
                      {"linewidth", "2.0"        }
        });
    }

    // 2. 绘制候选路径部分 -----------------------------------------------
    const std::vector<std::string> color_palette = {
        "#00FF00", // 绿
        "#80FF00",
        "#FFFF00", // 黄
        "#FF8000",
        "#FF0000" // 红
    };

    double max_cost = 0;
    for (const auto& p : depart_candi_pathes) {
        max_cost = std::max(max_cost, p.second);
    }

    // 绘制每条候选路径
    for (size_t i = 0; i < depart_candi_pathes.size(); ++i) {
        const auto& path = depart_candi_pathes[i].first;
        if (path.empty()) continue;
        // if (i > 0) break;
        std::vector<double> x_vals, y_vals;
        for (const auto& point : path) {
            x_vals.push_back(point.x);
            y_vals.push_back(point.y);
        }

        double normalized_cost = depart_candi_pathes[i].second / (max_cost + 1e-6);

        // 在循环内部使用
        int         color_index = static_cast<int>(normalized_cost * (color_palette.size() - 1));
        std::string color       = color_palette[color_index];

        plt::scatter(x_vals, y_vals, 2.0);
    }

    std::vector<double> x_vals, y_vals;
    for (const auto& point : depart_path) {
        x_vals.push_back(point.x);
        y_vals.push_back(point.y);
    }
    plt::scatter(x_vals, y_vals, 20);
    // 3. 设置图形属性 ---------------------------------------------------
    plt::title("Combined Environment and Candidate Paths Visualization");
    plt::xlabel("X (m)");
    plt::ylabel("Y (m)");
    plt::legend({
        {"loc",      "upper right"},
        {"fontsize", "8"          }
    }); // 调整图例字体大小
    plt::grid(true);
    plt::axis("equal");

    // 显示图形
    plt::show();
}

int main() {
    auto                          static_border = readBorderFile("../border.txt");
    auto                          wall_border   = readBorderFile("../wall.txt");
    auto                          obs_border    = readBorderFile("../obs.txt");
    GlobalPlanning::_VehicleParam vehicle_param;
    vehicle_param.veh_center_2_front      = 7.1;
    vehicle_param.veh_center_2_rear_bound = 2.65;
    vehicle_param.veh_center_2_side       = 1.885;
    vehicle_param.grid_dist               = 0.5;
    vehicle_param.safe_margin_bound       = 0.0;
    vehicle_param.safe_margin_error       = 0.0;
    vehicle_param.safe_margin_obstacle    = 0.0;
    vehicle_param.safe_margin_wall        = 0.0;


    GlobalPlanning::CollisonCheck collision_checker;
    collision_checker.InitParam(vehicle_param);
    collision_checker.InitBoundMap(static_border);
    collision_checker.InitWallBoundMap(wall_border);
    collision_checker.InitObstacleMap(obs_border);

    GlobalPlanning::Point load_point;
    load_point.x     = 157.00;
    load_point.y     = 318.00;
    load_point.angle = 0.0;

    GlobalPlanning::Point temp_point;
    GlobalPlanning::Path  unload_path;
    GlobalPlanning::Path  load_path;
    GlobalPlanning::Point wait_point;
    wait_point.x     = 250.0;
    wait_point.y     = 360.0;
    wait_point.angle = 90;


    for (double y = 396.0; y > 224.0; y -= 1.0) {
        temp_point.x         = 224;
        temp_point.y         = y;
        temp_point.angle     = -90.0;
        temp_point.curvature = 0.0;
        temp_point.direction = GlobalPlanning::MotionDirection::Forward;
        unload_path.emplace_back(temp_point);
    }

    for (double y = 224.0; y < 396.0; y += 1.0) {
        temp_point.x         = 234;
        temp_point.y         = y;
        temp_point.angle     = 90.0;
        temp_point.curvature = 0.0;
        temp_point.direction = GlobalPlanning::MotionDirection::Forward;
        load_path.emplace_back(temp_point);
    }
    auto                                      start = std::chrono::high_resolution_clock::now();
    FittingPathGenerate::FittingPathGenerator depart_path_planner(1.0, 70, 10, 1.0, 1.0, 20.0, 5, 10, 2.5, 2.0, 8.0, 2.0, 2.0, 10.0, 1.0, 1.0, 1.0);
    auto                                      depart_path_info = depart_path_planner.DepartPathGenerateInterface(unload_path, load_point, collision_checker);
    auto                                      wait_path_info   = depart_path_planner.WaitPathGenerateInterface(load_path, wait_point, collision_checker);
    auto                                      load_path_info   = depart_path_planner.LoadPathGenerateInterface(load_point, wait_point, collision_checker);
    auto                                      end              = std::chrono::high_resolution_clock::now();
    auto                                      duration         = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "代码执行耗时: " << duration.count() << " 毫秒" << std::endl;
    std::vector<std::pair<GlobalPlanning::Path, double>> depart_candi_pathes;
    auto                                                 best_depart_path = depart_path_info.first;
    std::vector<std::pair<GlobalPlanning::Path, double>> wait_candi_pathes;
    auto                                                 best_wait_path    = wait_path_info.first;
    std::vector<std::pair<GlobalPlanning::Path, double>> load_candi_pathes = depart_path_planner.GetLoadPathCandis();
    auto                                                 best_load_path    = load_path_info.first;
    // 记录结束时间点
    // 计算耗时（以毫秒为单位）
    // std::cout << "depart_candi_pathes.size() = " << depart_candi_pathes.size() << std::endl;
    // std::cout << "wait_candi_pathes.size() = " << wait_candi_pathes.size() << std::endl;
    std::cout << "load_candi_pathes.size() = " << load_candi_pathes.size() << std::endl;
    VisualizeCombined(static_border, wall_border, obs_border, load_path, wait_candi_pathes, best_wait_path);
    VisualizeCombined(static_border, wall_border, obs_border, unload_path, depart_candi_pathes, best_depart_path);
    VisualizeCombined(static_border, wall_border, obs_border, unload_path, load_candi_pathes, best_load_path);
    return 0;
}