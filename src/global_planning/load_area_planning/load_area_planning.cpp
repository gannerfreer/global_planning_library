#include "load_area_planning.h"
namespace LoadAreaPlanning {
std::tuple<int, GlobalPlanning::Point, GlobalPlanning::Path, GlobalPlanning::Path, GlobalPlanning::Path> LoadAreaPlanning::LoadAreaPlanningInterface(int planning_mode, const GlobalPlanning::Point& wait_point, const GlobalPlanning::Point& load_point, const GlobalPlanning::Path& in_path, GlobalPlanning::Path out_path, GlobalPlanning::CollisonCheck collision_checker) {
    FittingPathGenerate::FittingPathGenerator fit_path_planner(out_put_path_dense_, search_range_, jump_dense_, length_weight_, curvature_weight_, critical_length_, min_straight_length_depart_, max_straight_length_depart_, delta_straight_length_depart_, min_straight_length_wait_, max_straight_length_wait_, delta_straight_length_wait_, min_straight_length_load_, max_straight_length_load_, delta_straight_length_load_, load_path_straight_length_weight_, load_path_curvature_weight_);
    GlobalPlanning::Path                      wait_path;
    GlobalPlanning::Path                      load_path;
    GlobalPlanning::Path                      depart_path;
    GlobalPlanning::Point                     queue_point;
    depart_path = fit_path_planner.DepartPathGenerateInterface(out_path, load_point, collision_checker).first;
    cout << "DepartPathGenerateInterface完成" << endl;
    cout << "depart_path.size() = " << depart_path.size() << endl;
    CalCurvature(depart_path, 1);

    if (depart_path.empty()) {
        cout << "驶出路径规划失败！" << endl;
        return std::make_tuple(0, queue_point, wait_path, load_path, depart_path);
    }
    else {
        auto temp_depart_path = depart_path;
        veh_param.is_light    = false;
        // 将temp_depart_path中的x y yaw curvature direction 保存为txt文件
        ofstream file;
        file.open("depart_path_before.txt");
        for (auto& point : temp_depart_path) {
            file << point.x << " " << point.y << " " << point.angle << " " << point.curvature << " " << point.direction << endl;
        }
        file.close();
        if (PathSmoother(temp_depart_path, veh_param)) {
            cout << "line28 depart_path ipopt优化完成" << endl;
            depart_path = temp_depart_path;
            // 将temp_depart_path中的x y yaw curvature direction 保存为txt文件
            file.open("depart_path_after.txt");
            for (auto& point : temp_depart_path) {
                file << point.x << " " << point.y << " " << point.angle << " " << point.curvature << " " << point.direction << endl;
            }
            file.close();
        }
        else {
            cout << "line37 depart_path ipopt优化失败" << endl;
        }
    }
    veh_param.is_light = true;

    if (planning_mode == 1) { // 尝试人工指定排队点
        cout << "人工指定排队点模式----------------------------" << endl;
        wait_path = fit_path_planner.WaitPathGenerateInterface(in_path, wait_point, collision_checker).first;
        CalCurvature(wait_path, 1);
        if (wait_path.empty()) {
            cout << "排队点驶入路径规划失败！" << endl;
            return std::make_tuple(0, queue_point, wait_path, load_path, depart_path);
        }
        wait_path_candidates = fit_path_planner.GetWaitPathCandis();
        load_path            = fit_path_planner.LoadPathGenerateInterface(load_point, wait_point, collision_checker).first;
        CalCurvature(load_path, 1);
        if (load_path.empty()) {
            cout << "装载倒车路径规划失败！" << endl;
            return std::make_tuple(0, queue_point, wait_path, load_path, depart_path);
        }
        auto temp_wait_path = wait_path;
        // 将temp_wait_path中的x y yaw curvature direction 保存为txt文件
        ofstream file;
        file.open("wait_path_before.txt");
        for (auto& point : temp_wait_path) {
            file << point.x << " " << point.y << " " << point.angle << " " << point.curvature << " " << point.direction << endl;
        }
        file.close();
        if (PathSmoother(temp_wait_path, veh_param)) {
            cout << "line62 wait_path ipopt优化完成" << endl;
            wait_path = temp_wait_path;
            // 将temp_wait_path中的x y yaw curvature direction 保存为txt文件
            file.open("wait_path_after.txt");
            for (auto& point : temp_wait_path) {
                file << point.x << " " << point.y << " " << point.angle << " " << point.curvature << " " << point.direction << endl;
            }
            file.close();
        }
        else {
            cout << "line74 wait_path ipopt优化失败" << endl;
        }

        auto temp_load_path = load_path;
        // 将temp_load_path中的x y yaw curvature direction 保存为txt文件
        file.open("load_path_before.txt");
        for (auto& point : temp_load_path) {
            file << point.x << " " << point.y << " " << point.angle << " " << point.curvature << " " << point.direction << endl;
        }
        file.close();
        if (PathSmoother(temp_load_path, veh_param)) {
            cout << "line79 load_path ipopt优化完成" << endl;
            load_path = temp_load_path;
            // 将temp_load_path中的x y yaw curvature direction 保存为txt文件
            file.open("load_path_after.txt");
            for (auto& point : temp_load_path) {
                file << point.x << " " << point.y << " " << point.angle << " " << point.curvature << " " << point.direction << endl;
            }
            file.close();
        }
        else {
            cout << "line95 load_path ipopt优化失败" << endl;
        }
        return std::make_tuple(1, wait_point, wait_path, load_path, depart_path);
    }
    if (planning_mode == 2) {
        cout << "复用排队点模式-----------------------------------" << endl;
        load_path = fit_path_planner.LoadPathGenerateInterface(load_point, wait_point, collision_checker).first;
        CalCurvature(load_path, 1);
        if (load_path.empty()) {
            cout << "装载路径生成失败,转生成排队点模式" << endl;
            planning_mode = 0;
        }
        else {
            auto temp_load_path = load_path;
            // 将temp_load_path中的x y yaw curvature direction 保存为txt文件
            ofstream file;
            file.open("load_path_before.txt");
            for (auto& point : temp_load_path) {
                file << point.x << " " << point.y << " " << point.angle << " " << point.curvature << " " << point.direction << endl;
            }
            file.close();
            if (PathSmoother(temp_load_path, veh_param)) {
                cout << "line108 load_path ipopt优化完成" << endl;
                load_path = temp_load_path;
                // 将temp_load_path中的x y yaw curvature direction 保存为txt文件
                file.open("load_path_after.txt");
                for (auto& point : temp_load_path) {
                    file << point.x << " " << point.y << " " << point.angle << " " << point.curvature << " " << point.direction << endl;
                }
                file.close();
            }
            else {
                cout << "line126 load_path ipopt优化失败" << endl;
            }
            return std::make_tuple(1, wait_point, wait_path, load_path, depart_path);
        }
    }
    if (planning_mode == 0) {
        cout << "自动生成排队点模式-----------------------------------" << endl;
        WaitPointGenerate::WaitPointGenerator wait_point_planner(max_curve_length_, min_curve_length_, delta_curve_length_, wheel_base_length_, max_straight_length_, min_straight_length_, delta_straight_length_, max_steering_angle_, min_steering_angle_, delta_steering_angle_, standard_steering_angle_, weight_length_, weight_curve_, out_put_path_dense_, center2front_, center2side_, center2rear_, safe_margin_front_, safe_margin_side_, safe_margin_rear_, collision_weight_);
        load_path = wait_point_planner.GenerateWaitPointInterface(load_point, depart_path, collision_checker, fit_path_planner, in_path);
        CalCurvature(load_path, 1);
        sample_points = wait_point_planner.wait_point_sample_;
        if (load_path.empty()) {
            cout << "驶入等待点路径生成失败" << endl;
            return std::make_tuple(0, queue_point, wait_path, load_path, depart_path);
        }
        cout << "load_path.size() = " << load_path.size() << endl;
        queue_point = load_path.front();
        cout << "最后一边调用：queue_point：x,y,angle = " << queue_point.x << "," << queue_point.y << "," << queue_point.angle << endl;
        wait_path = fit_path_planner.WaitPathGenerateInterface(in_path, queue_point, collision_checker).first;
        CalCurvature(wait_path, 1);
        if (wait_path.empty()) {
            cout << "驶入排队点路径生成失败" << endl;
            return std::make_tuple(0, queue_point, wait_path, load_path, depart_path);
        }
        auto temp_wait_path = wait_path;
        // 将temp_wait_path中的x y yaw curvature direction 保存为txt文件
        ofstream file;
        file.open("wait_path_before.txt");
        for (auto& point : temp_wait_path) {
            file << point.x << " " << point.y << " " << point.angle << " " << point.curvature << " " << point.direction << endl;
        }
        file.close();
        if (PathSmoother(temp_wait_path, veh_param)) {
            cout << "line146 wait_path ipopt优化完成" << endl;
            wait_path = temp_wait_path;
            // 将temp_wait_path中的x y yaw curvature direction 保存为txt文件
            file.open("wait_path_after.txt");
            for (auto& point : temp_wait_path) {
                file << point.x << " " << point.y << " " << point.angle << " " << point.curvature << " " << point.direction << endl;
            }
            file.close();
        }
        else {
            cout << "line152 wait_path ipopt优化失败" << endl;
        }
        auto temp_load_path = load_path;
        // 将temp_load_path中的x y yaw curvature direction 保存为txt文件
        file.open("load_path_before.txt");
        for (auto& point : temp_load_path) {
            file << point.x << " " << point.y << " " << point.angle << " " << point.curvature << " " << point.direction << endl;
        }
        file.close();
        if (PathSmoother(temp_load_path, veh_param)) {
            cout << "line163 load_path ipopt优化完成" << endl;
            load_path = temp_load_path;
            // 将temp_load_path中的x y yaw curvature direction 保存为txt文件
            file.open("load_path_after.txt");
            for (auto& point : temp_load_path) {
                file << point.x << " " << point.y << " " << point.angle << " " << point.curvature << " " << point.direction << endl;
            }
            file.close();
        }
        else {
            cout << "line172 load_path ipopt优化失败" << endl;
        }
        return std::make_tuple(1, queue_point, wait_path, load_path, depart_path);
    }
}

void LoadAreaPlanning::CalculatePathDistance(GlobalPlanning::Path& input_path) {
    if (input_path.size() < 2) {
        return;
    }
    input_path.front().distance = 0;
    for (int i = 1; i < input_path.size(); i++) {
        input_path[i].distance = input_path[i - 1].distance + sqrt(pow(input_path[i].x - input_path[i - 1].x, 2) + pow(input_path[i].y - input_path[i - 1].y, 2));
    }
}

bool LoadAreaPlanning::PathSmoother(GlobalPlanning::Path& input_path, const GlobalPlanning::_VehicleParam& veh_param) {
    for (auto& point : input_path) {
        // 帮我将angle从度数转化为弧度，并约束到[0,2_PI]
        point.angle = point.angle * M_PI / 180.0;
        if (point.angle < 0) {
            point.angle += 2 * M_PI;
        }
        if (point.angle > 2 * M_PI) {
            point.angle -= 2 * M_PI;
        }
    }
    CalculatePathDistance(input_path);
    GlobalPlanning::TensionSmoother2 smoother(input_path, veh_param);
    if (smoother.smooth(input_path)) {

        for (auto& point : input_path) {
            point.angle = point.angle * 180.0 / M_PI;
        }
        for (int i = 0; i < input_path.size() - 1; i++) {
            input_path[i].angle = atan2(input_path[i + 1].y - input_path[i].y, input_path[i + 1].x - input_path[i].x) * 180.0 / M_PI;
        }
        input_path.back().angle = input_path[input_path.size() - 2].angle;
        CalCurvature(input_path, 1);
        return true;
    }
    else {
        return false;
    }
}

void LoadAreaPlanning::CalCurvature(GlobalPlanning::Path& path, int check_dense) {
    if (path.size() < 2) {
        cout << "路径过短无法计算曲率" << endl;
        return;
    }
    for (int i = 0; i < path.size() - 2 * check_dense; i++) {
        double x1 = path[i].x;
        double x2 = path[i + check_dense].x;
        double x3 = path[i + 2 * check_dense].x;
        double y1 = path[i].y;
        double y2 = path[i + check_dense].y;
        double y3 = path[i + 2 * check_dense].y;

        // 计算三角形的边长
        double a = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        double b = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
        double c = sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2));

        // 计算三角形面积（带符号）
        double signed_S = (x1 * y2 + x2 * y3 + x3 * y1 - y1 * x2 - y2 * x3 - y3 * x1) / 2;

        // 计算曲率（带符号）
        if (a == 0 || b == 0 || c == 0) {
            path[i].curvature = 0;
        }
        else {
            // 4 * |S| / (a * b * c) 并赋予符号
            path[i].curvature = 4 * signed_S / (a * b * c);
        }
    }

    // 处理最后两个点（保持与倒数第三个点相同的曲率）
    path[path.size() - 2].curvature = path[path.size() - 3].curvature;
    path[path.size() - 1].curvature = path[path.size() - 3].curvature;
}

LoadAreaPlanning::~LoadAreaPlanning() {}

} // namespace LoadAreaPlanning
