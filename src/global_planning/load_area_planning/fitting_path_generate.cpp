#include "fitting_path_generate.h"
namespace FittingPathGenerate {

FittingPathGenerator::FittingPathGenerator(double out_put_path_dense, double search_range, double jump_dense, double length_weight, double curvature_weight, double critical_length, double min_straight_line_length, double max_straight_line_length, double delta_straight_line_length, double min_straight_length_wait, double max_straight_length_wait, double delta_straight_length_wait, double min_straight_length_load, double max_straight_length_load, double delta_straight_length_load, double straight_length_weight, double load_path_curvature_weight) {
    out_put_path_dense_               = out_put_path_dense;
    search_range_                     = search_range;
    jump_dense_                       = jump_dense;
    length_weight_                    = length_weight;
    curvature_weight_                 = curvature_weight;
    critical_length_                  = critical_length;
    min_straight_length_depart_       = min_straight_line_length;
    max_straight_length_depart_       = max_straight_line_length;
    delta_straight_length_depart_     = delta_straight_line_length;
    min_straight_length_wait_         = min_straight_length_wait;
    max_straight_length_wait_         = max_straight_length_wait;
    delta_straight_length_wait_       = delta_straight_length_wait;
    min_straight_length_load_         = min_straight_length_load;
    max_straight_length_load_         = max_straight_length_load;
    delta_straight_length_load_       = delta_straight_length_load;
    load_path_straight_length_weight_ = straight_length_weight;
    load_path_curvature_weight_       = load_path_curvature_weight;
}

FittingPathGenerator::~FittingPathGenerator() {}

std::pair<GlobalPlanning::Path, double> FittingPathGenerator::LoadPathGenerateInterface(const GlobalPlanning::Point& load_point, const GlobalPlanning::Point& wait_point, GlobalPlanning::CollisonCheck& collision_checker) {
    std::cout << "进入" << endl;
    GlobalPlanning::Path      result;
    double                    result_grade;
    curve::Point              temp_wait_point(wait_point.x, wait_point.y, wait_point.angle, 0.0);
    curve::Dubins             dubins_planner;
    std::vector<curve::Point> dubins_path;
    std::cout << "delta_straight_length_load_ = " << delta_straight_length_load_ << endl;
    std::cout << "max_straight_length_load_ = " << max_straight_length_load_ << endl;
    std::cout << "min_straight_length_load_ = " << min_straight_length_load_ << endl;

    for (double i = 0.0; i * delta_straight_length_load_ + max_straight_length_load_ >= min_straight_length_load_; i -= 1.0) {
        double length = i * delta_straight_length_load_ + max_straight_length_load_;
        std::cout << "length = " << length << endl;
        GlobalPlanning::Point straight_line_start;
        straight_line_start.x         = load_point.x + length * cos(load_point.angle * M_PI / 180.0);
        straight_line_start.y         = load_point.y + length * sin(load_point.angle * M_PI / 180.0);
        straight_line_start.angle     = load_point.angle;
        straight_line_start.curvature = 0.0;
        curve::Point temp_straight_line_start(straight_line_start.x, straight_line_start.y, straight_line_start.angle, 0.0);
        dubins_planner.GetDubinsPath(temp_straight_line_start, temp_wait_point, dubins_path);
        reverse(dubins_path.begin(), dubins_path.end());
        auto load_curve_path = PathTransFormer(dubins_path);
        CalCurvature(load_curve_path, 1);
        double total_curvature;
        for (const auto& point : load_curve_path) {
            total_curvature += fabs(point.curvature);
        }
        double aver_curvature = total_curvature / (double)(load_curve_path.size() - 1);
        auto   stitch_path    = GenerateStraitLine(load_point, straight_line_start);
        reverse(stitch_path.begin(), stitch_path.end());
        stitch_path.emplace_back(straight_line_start);
        load_curve_path.insert(load_curve_path.end(), stitch_path.begin() + 1, stitch_path.end());
        double grade = (load_path_straight_length_weight_ * length / max_straight_length_load_ + load_path_curvature_weight_ * aver_curvature) / (load_path_straight_length_weight_ + load_path_curvature_weight_);
        load_path_candidates_.emplace_back(std::make_pair(load_curve_path, grade));
    }
    std::sort(load_path_candidates_.begin(), load_path_candidates_.end(), [](const std::pair<GlobalPlanning::Path, double>& a, const std::pair<GlobalPlanning::Path, double>& b) {
        return a.second > b.second; // 按 double 值降序
    });
    for (auto& path_info : load_path_candidates_) {
        if (collision_checker.OptiPathCollisionCheckWithAll(path_info.first).empty()) {
            std::cout << "成功了" << std::endl;
            for (int i = 0; i < path_info.first.size(); i++) {
                path_info.first[i].direction = GlobalPlanning::MotionDirection::Backward;
            }
            return std::make_pair(path_info.first, path_info.second);
        }
        else {
            std::cout << "失败了" << std::endl;
        }
    }
    return std::make_pair(result, result_grade);
}

std::pair<GlobalPlanning::Path, double> FittingPathGenerator::WaitPathGenerateInterface(const GlobalPlanning::Path& origin_path, const GlobalPlanning::Point& wait_point) {
    GlobalPlanning::Path result;
    double               grade = 0.0;

    curve::Dubins                                        dubins_planner;
    std::vector<GlobalPlanning::Point>                   start_point_sample = SamplePathSegment(origin_path, wait_point);
    std::vector<std::pair<GlobalPlanning::Path, double>> wait_path_candidates;
    if (start_point_sample.empty()) {
        std::cout << "该排队点离主路径太远，不满足要求" << std::endl;
        return std::make_pair(result, 0.0);
    }
    std::cout << "SamplePathSegment" << std::endl;

    curve::Point end_point(wait_point.x, wait_point.y, wait_point.angle, 0.0);
    for (const auto& start_point : start_point_sample) {
        curve::Point              temp_start_point(start_point.x, start_point.y, start_point.angle, 0.0);
        std::vector<curve::Point> temp_wait_path;
        dubins_planner.GetDubinsPath(temp_start_point, end_point, temp_wait_path);
        auto wait_path = PathTransFormer(temp_wait_path);
        wait_path_candidates.emplace_back(std::make_pair(wait_path, 0.0));
    }

    PathRateAndSort(wait_path_candidates);
    wait_path_candidates_ = wait_path_candidates;
    for (int i = 0; i < wait_path_candidates.size(); i++) {
        result = wait_path_candidates_[i].first;
        grade  = wait_path_candidates_[i].second;
    }

    auto stitch_path = PathCuttoStart(result.front(), origin_path);
    std::cout << "stitch_path .size()=" << stitch_path.size() << endl;
    result.insert(result.begin(), stitch_path.begin(), stitch_path.end());
    for (int i = 0; i < result.size(); i++) {
        result[i].direction = GlobalPlanning::MotionDirection::Forward;
    }
    return std::make_pair(result, grade);
}

std::pair<GlobalPlanning::Path, double> FittingPathGenerator::WaitPathGenerateInterface(const GlobalPlanning::Path& origin_path, const GlobalPlanning::Point& wait_point, GlobalPlanning::CollisonCheck& collision_checker) {
    GlobalPlanning::Path result;
    double               grade = 0.0;
    if (collision_checker.IsVehicleCollision(wait_point)) {
        std::cout << "该排队点有碰撞，无法使用" << endl;
        return std::make_pair(result, 0.0);
    }

    GlobalPlanning::Path straight_path_with_wait_point;
    // std::cout << "max_straight_length_wait_ = " << max_straight_length_wait_ << std::endl;
    // std::cout << "min_straight_length_wait_ = " << min_straight_length_wait_ << std::endl;
    // std::cout << "delta_straight_length_wait_ = " << delta_straight_length_wait_ << std::endl;

    for (double i = 0.0; i * delta_straight_length_wait_ + max_straight_length_wait_ >= min_straight_length_wait_; i -= 1.0) {
        GlobalPlanning::Point straight_start_point;
        double                length = i * delta_straight_length_wait_ + max_straight_length_wait_;
        // std::cout << "length = " << length << std::endl;
        straight_start_point.x         = wait_point.x - length * cos(wait_point.angle * M_PI / 180.0);
        straight_start_point.y         = wait_point.y - length * cos(wait_point.angle * M_PI / 180.0);
        straight_start_point.angle     = wait_point.angle;
        straight_start_point.curvature = 0;
        auto straight_path             = GenerateStraitLine(straight_start_point, wait_point);
        if (collision_checker.OptiPathCollisionCheckWithAll(straight_path).empty()) {
            straight_path.emplace_back(wait_point);
            straight_path_with_wait_point = straight_path;
            break;
        }
    }

    if (straight_path_with_wait_point.empty()) {
        std::cout << "该排队点距离障碍物过近，无法使用" << endl;
        return std::make_pair(result, 0.0);
    }

    curve::Dubins                      dubins_planner;
    std::vector<GlobalPlanning::Point> start_point_sample = SamplePathSegment(origin_path, straight_path_with_wait_point.front());
    // cout << "驶出点寻找完毕" << endl;
    std::vector<std::pair<GlobalPlanning::Path, double>> wait_path_candidates;
    if (start_point_sample.empty()) {
        std::cout << "该排队点离主路径太远，不满足要求" << std::endl;
        return std::make_pair(result, 0.0);
    }

    curve::Point end_point(straight_path_with_wait_point.front().x, straight_path_with_wait_point.front().y, straight_path_with_wait_point.front().angle, 0.0);
    for (const auto& start_point : start_point_sample) {
        curve::Point              temp_start_point(start_point.x, start_point.y, start_point.angle, 0.0);
        std::vector<curve::Point> temp_wait_path;
        if (dubins_planner.GetDubinsPath(temp_start_point, end_point, temp_wait_path)) {
            auto wait_path = PathTransFormer(temp_wait_path);
            wait_path_candidates.emplace_back(std::make_pair(wait_path, 0.0));
        }
    }
    // cout << "候选路径生成完毕" << wait_path_candidates.size() << endl;

    PathRateAndSort(wait_path_candidates);
    // cout << "候选路径评分完毕完毕" << endl;

    wait_path_candidates_ = wait_path_candidates;
    for (int i = 0; i < wait_path_candidates.size(); i++) {
        if (collision_checker.OptiPathCollisionCheckWithAll(wait_path_candidates_[i].first).empty()) {
            result = wait_path_candidates_[i].first;
            grade  = wait_path_candidates_[i].second;
        }
    }

    if (result.empty()) {
        // std::cout << "因边界或障碍物无法生成" << endl;
        return std::make_pair(result, 0.0);
    }

    auto stitch_path = PathCuttoStart(result.front(), origin_path);
    // std::cout << "stitch_path .size()=" << stitch_path.size() << endl;
    result.insert(result.begin(), stitch_path.begin(), stitch_path.end());
    // std::cout << "straight_path_with_wait_point .size()=" << straight_path_with_wait_point.size() << endl;

    result.insert(result.end(), straight_path_with_wait_point.begin() + 1, straight_path_with_wait_point.end());
    for (int i = 0; i < result.size(); i++) {
        result[i].direction = GlobalPlanning::MotionDirection::Forward;
    }
    return std::make_pair(result, grade);
}

std::pair<GlobalPlanning::Path, double> FittingPathGenerator::DepartPathGenerateInterface(const GlobalPlanning::Path& target_path, const GlobalPlanning::Point& load_point, GlobalPlanning::CollisonCheck& collision_checker) {
    GlobalPlanning::Path                                 result;
    double                                               grade;
    curve::Dubins                                        dubins_planner;
    std::vector<GlobalPlanning::Point>                   end_point_sample = SamplePathSegment(target_path, load_point);
    std::vector<std::pair<GlobalPlanning::Path, double>> depart_path_candidates;
    std::vector<std::pair<GlobalPlanning::Path, double>> temp_depart_path_candidates;
    std::vector<curve::Point>                            temp_candi_path;
    if (end_point_sample.empty()) {
        std::cout << "驶出引导路径不满足要求" << std::endl;
        return std::make_pair(result, 0.0);
    }
    double straight_line_length;

    for (double i = 0; min_straight_length_depart_ + i * delta_straight_length_depart_ <= max_straight_length_depart_; i += 1.0) {
        straight_line_length = min_straight_length_depart_ + i * delta_straight_length_depart_;
        curve::Point start_point(load_point.x + straight_line_length * cos(load_point.angle * M_PI / 180.0), load_point.y + straight_line_length * sin(load_point.angle * M_PI / 180.0), load_point.angle, 0.0);
        std::cout << "直线段采样长度：" << straight_line_length << std::endl;

        for (int j = 0; j < end_point_sample.size(); j++) {
            temp_candi_path.clear();
            curve::Point end_point(end_point_sample[j].x, end_point_sample[j].y, end_point_sample[j].angle, end_point_sample[j].curvature);
            std::cout << "取得终点：" << end_point_sample[j].x << "," << end_point_sample[j].y << std::endl;
            if (dubins_planner.GetDubinsPath(start_point, end_point, temp_candi_path)) {
                auto temp_path = PathTransFormer(temp_candi_path);
                // if (j == end_point_sample.size() - 1) {
                //     for (auto& point : temp_path) {
                //         std::cout << "x,y,yaw = " << point.x << "," << point.y << "," << point.angle * 180 / M_PI << endl;
                //     }
                // }
                auto collision_info = collision_checker.DepartPathCollisionCheck(temp_path);
                if (collision_info.empty()) { // 你没有引用返回，严一峰
                    std::cout << "碰撞检测成功" << std::endl;
                    depart_path_candidates.emplace_back(std::make_pair(temp_path, 0.0));
                    temp_depart_path_candidates.emplace_back(std::make_pair(temp_path, 0.0));
                }
                else {
                    std::cout << "碰撞检测失败" << std::endl;
                }
            }
        }
        if (!end_point_sample.empty() && static_cast<float>(depart_path_candidates.size()) / end_point_sample.size() > 0.6f) {
            std::cout << "驶出成功率超60%" << std::endl;
            break;
        }
        else {
            depart_path_candidates.clear();
        }
    }

    if (depart_path_candidates.empty()) {
        if (temp_depart_path_candidates.empty()) {
            std::cout << "装载位或挖机位置不满足要求" << std::endl;
            return std::make_pair(result, 0.0);
        }
        else {
            depart_path_candidates = temp_depart_path_candidates;
        }
    }
    PathRateAndSort(depart_path_candidates);
    depart_path_candidates_ = depart_path_candidates;
    for (int i = 0; i < depart_path_candidates_.size(); i++) {
        result             = depart_path_candidates_.front().first;
        grade              = depart_path_candidates_.front().second;
        auto straight_line = GenerateStraitLine(load_point, result.front());
        result.insert(result.begin(), straight_line.begin(), straight_line.end());
        if (collision_checker.OptiPathCollisionCheckWithAll(result).empty()) {
            break;
        }
        else {
            result.clear();
        }
    }
    auto stitch_path = PathCuttoEnd(result.back(), target_path);
    std::cout << "stitch_path .size()=" << stitch_path.size() << endl;
    result.insert(result.end(), stitch_path.begin(), stitch_path.end());
    for (int i = 0; i < result.size(); i++) {
        result[i].direction = GlobalPlanning::MotionDirection::Forward;
    }
    return std::make_pair(result, grade);
}

GlobalPlanning::Path FittingPathGenerator::GenerateStraitLine(const GlobalPlanning::Point& start, const GlobalPlanning::Point& end) {
    GlobalPlanning::Path result;
    double               length = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
    for (int i = 0; i * out_put_path_dense_ < length - 0.1; i++) {
        GlobalPlanning::Point temp_point;
        temp_point.x         = start.x + i * out_put_path_dense_ * cos(start.angle * M_PI / 180.0);
        temp_point.y         = start.y + i * out_put_path_dense_ * sin(start.angle * M_PI / 180.0);
        temp_point.angle     = start.angle;
        temp_point.curvature = 0;
        result.emplace_back(temp_point);
    }
    return result;
}

GlobalPlanning::Path FittingPathGenerator::PathCuttoEnd(const GlobalPlanning::Point& point, const GlobalPlanning::Path& path) {
    GlobalPlanning::Path result;
    double               dis_square = DBL_MAX;
    int                  index      = 0;
    for (int i = 0; i < path.size(); i++) {
        double temp_dis = pow(point.x - path[i].x, 2) + pow(point.y - path[i].y, 2);
        if (temp_dis < dis_square) {
            dis_square = temp_dis;
            index      = i;
        }
    }
    std::cout << "index = " << index << endl;
    std::cout << "path.size() - 1 = " << path.size() - 1;
    if (index != path.size() - 1) {
        for (int j = index + 1; j < path.size() - 1; j++) {
            result.emplace_back(path[j]);
        }
    }
    return result;
}

GlobalPlanning::Path FittingPathGenerator::PathCuttoStart(const GlobalPlanning::Point& point, const GlobalPlanning::Path& path) {
    GlobalPlanning::Path result;
    double               dis_square = DBL_MAX;
    int                  index      = 0;
    for (int i = 0; i < path.size(); i++) {
        double temp_dis = pow(point.x - path[i].x, 2) + pow(point.y - path[i].y, 2);
        if (temp_dis < dis_square) {
            dis_square = temp_dis;
            index      = i;
        }
    }
    // std::cout << "index = " << index << endl;
    // std::cout << "path.size() - 1 = " << path.size() - 1;
    if (index != 0) {
        for (int j = 0; j <= index - 1; j++) {
            result.emplace_back(path[j]);
        }
    }
    return result;
}

void FittingPathGenerator::PathRateAndSort(std::vector<std::pair<GlobalPlanning::Path, double>>& candi_pathes) {
    // cout << "candi_pathes.size()=" << candi_pathes.size() << endl;
    for (int i = 0; i < candi_pathes.size(); i++) {
        // cout << "对i路径进行评分:" << i << endl;
        // cout << "candi_pathes[i].first.size = " << candi_pathes[i].first.size() << endl;
        CalCurvature(candi_pathes[i].first, 1);
        candi_pathes[i].second = CalPathQuality(candi_pathes[i].first, length_weight_, curvature_weight_, critical_length_);
    }
    std::sort(candi_pathes.begin(), candi_pathes.end(), [](const std::pair<GlobalPlanning::Path, double>& a, const std::pair<GlobalPlanning::Path, double>& b) {
        return a.second > b.second; // 按 double 值降序
    });
}


double FittingPathGenerator::CalPathQuality(const GlobalPlanning::Path& path, double length_weight, double curvature_weight, double critical_length) {
    // 1. 计算路径总长度
    if (path.empty()) return 0.0;
    double total_length = 0.0;
    for (int i = 1; i < path.size(); ++i) {
        double dx = path[i].x - path[i - 1].x;
        double dy = path[i].y - path[i - 1].y;
        total_length += std::hypot(dx, dy);
    }
    // 2. 计算平均曲率
    double total_curvature = 0.0;
    for (int i = 1; i < path.size() - 1; ++i) {
        total_curvature += fabs(path[i].curvature);
    }
    double avg_curvature = total_curvature / (path.size() - 1);


    // 3. 计算长度评分 (长度超过critical_length后评分降低)
    double length_score = 1.0;
    if (total_length > critical_length) {
        length_score = critical_length / total_length;
    }


    // 4. 计算曲率评分 (曲率越大评分越低)
    double curvature_score = 1.0 / (1.0 + avg_curvature);


    // 5. 综合评分 (应用权重因子)
    double final_score = (length_weight * length_score + curvature_weight * curvature_score) / (length_weight + curvature_weight);


    return final_score;
}


void FittingPathGenerator::CalCurvature(GlobalPlanning::Path& path, int check_dense) {
    if (path.size() < 2) {
        cout << "路径过短无法计算曲率" << endl;
        return;
    }
    for (int i = 0; i < path.size() - 2 * check_dense; i++) {
        double x1         = path[i].x;
        double x2         = path[i + check_dense].x;
        double x3         = path[i + 2 * check_dense].x;
        double y1         = path[i].y;
        double y2         = path[i + check_dense].y;
        double y3         = path[i + 2 * check_dense].y;
        double a          = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        double b          = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
        double c          = sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2));
        double S          = abs((x1 * y2 + x2 * y3 + x3 * y1 - y1 * x2 - y2 * x3 - y3 * x1) / 2);
        path[i].curvature = 4 * S / a / b / c;
        if (a == 0 or b == 0 or c == 0) {
            path[i].curvature = 0;
        }
    }
    path[path.size() - 2].curvature = path[path.size() - 3].curvature;
    path[path.size() - 1].curvature = path[path.size() - 3].curvature;
}

std::vector<GlobalPlanning::Point> FittingPathGenerator::SamplePathSegment(const GlobalPlanning::Path& target_path, const GlobalPlanning::Point& load_point) {
    std::vector<GlobalPlanning::Point> end_point_sample;

    if (target_path.empty()) {
        std::cout << "引出路径为空" << std::endl;
        return end_point_sample;
    }

    // 1. 寻找距离load_point最近的点
    double min_dist    = std::numeric_limits<double>::max();
    int    closest_idx = -1;

    for (int i = 0; i < target_path.size() - 1; ++i) {
        double dx   = target_path[i].x - load_point.x;
        double dy   = target_path[i].y - load_point.y;
        double dist = std::sqrt(dx * dx + dy * dy);
        if (dist < min_dist) {
            min_dist    = dist;
            closest_idx = i;
        }
    }
    // std::cout << "寻找距离load_point最近的点" << std::endl;

    // 检查最近点是否在50m范围内
    // std::cout << "路径上最近点离装载点的距离" << min_dist << std::endl;
    if (min_dist > search_range_) {
        return end_point_sample; // 返回空vector
    }

    // 2. 确定连续50m范围内的轨迹段
    int start_idx = closest_idx;
    int end_idx   = closest_idx;

    // 向前搜索起点
    for (int i = closest_idx; i >= 0; --i) {
        double dx   = target_path[i].x - load_point.x;
        double dy   = target_path[i].y - load_point.y;
        double dist = std::sqrt(dx * dx + dy * dy);

        if (dist <= search_range_) {
            start_idx = i;
        }
        else {
            break; // 超出范围时停止
        }
    }

    // 向后搜索终点
    for (int i = closest_idx; i < target_path.size(); ++i) {
        double dx   = target_path[i].x - load_point.x;
        double dy   = target_path[i].y - load_point.y;
        double dist = std::sqrt(dx * dx + dy * dy);

        if (dist <= search_range_) {
            end_idx = i;
        }
        else {
            break; // 超出范围时停止
        }
    }

    // 3. 计算轨迹段累计距离
    std::vector<double> cumulative_dist;
    double              total_dist = 0.0;
    cumulative_dist.push_back(total_dist);

    for (int i = start_idx + 1; i <= end_idx; ++i) {
        double dx       = target_path[i].x - target_path[i - 1].x;
        double dy       = target_path[i].y - target_path[i - 1].y;
        double seg_dist = std::sqrt(dx * dx + dy * dy);
        total_dist += seg_dist;
        cumulative_dist.push_back(total_dist);
    }

    // 4. 每隔5米采样点
    double sample_interval = jump_dense_; // 5米采样间隔
    double current_dist    = 0.0;

    while (current_dist <= total_dist) {
        // 找到大于等于current_dist的第一个点
        auto it = std::lower_bound(cumulative_dist.begin(), cumulative_dist.end(), current_dist);

        if (it == cumulative_dist.end()) {
            break; // 超出范围
        }

        int idx        = std::distance(cumulative_dist.begin(), it);
        int actual_idx = start_idx + idx;

        // 添加到结果
        end_point_sample.push_back(target_path[actual_idx]);

        // 移动到下一个采样点
        current_dist += sample_interval;
    }
    // std::cout << "驶出路径上的采样点" << end_point_sample.size() << std::endl;
    return end_point_sample;
}

GlobalPlanning::Path FittingPathGenerator::PathTransFormer(const std::vector<curve::Point> curve_path) {
    GlobalPlanning::Path  result;
    GlobalPlanning::Point temp_point;
    for (const auto& point : curve_path) {
        temp_point.x         = point.GetX();
        temp_point.y         = point.GetY();
        temp_point.angle     = point.GetAngle() * M_PI / 180.0;
        temp_point.curvature = point.GetCurvature();
        result.emplace_back(temp_point);
    }
    return result;
}

} // namespace FittingPathGenerate
