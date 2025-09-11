#include "predicting.h"


Predicting::Predicting() {
    InitialFunction();
}
Predicting::~Predicting() {
    threadLogger_->info("析构函数已被调用");
    cout << "析构函数已被调用" << endl;
}


bool Predicting::InitialFunction() {
    all_referencelines_.clear();
#ifdef SKIP_HEADER
#else
    if (ReadAllMapFile()) {
        printf(" The map file is readed \n");
        return true;
    }
    else {
        printf(" Failed to read the map file \n");
        return false;
    }
#endif
    return true;
}
bool Predicting::ReadAllMapFile() {
#ifdef SKIP_HEADER
#else
    memset(&m_tar_rviz_data_, 0, sizeof(tarRviz));
    m_tar_rviz_data_.minx = std::numeric_limits<double>::infinity();
    m_tar_rviz_data_.miny = std::numeric_limits<double>::infinity();
    // 读取地图信息
    if (!configio_.GetMap_PathPredicting(all_referencelines_, referenceline_relation_, m_tar_rviz_data_)) {
        return false;
    }
    else {
        return true;
    }

#endif
}
void Predicting::PredictingInterface(vector<vector<_TrajectoryPoint>>& path, int predicting_distance) {
    predicting_distance_ = predicting_distance;
    threadLogger_->info("Enter PredictingIntface,预测距离{}m", predicting_distance_);
    cout << "Enter PredictingIntface,预测距离" << predicting_distance_ << "m" << endl;
    path.clear();
    PlanResult result = PlanResult::Plan_OK;
    error_type_       = ErrorType::SUCCESS;


    threadLogger_->info("referenceline_relation_.size():{}", referenceline_relation_.size());
    threadLogger_->info("all_referencelines_.size():{}", all_referencelines_.size());
    cout << "referenceline_relation_.size():" << referenceline_relation_.size() << endl;
    cout << "all_referencelines_.size():" << all_referencelines_.size() << endl;
    std::vector<std::vector<_TrajectoryPoint>> final_result = predictPath(start_point_.x, start_point_.y, start_point_.yaw / 180.0 * M_PI, 20);

    // 对final_result进行100m准确裁减
    std::vector<_TrajectoryPoint> temp_traj;
    double                        total_dis     = 0;
    int                           nearest_index = -1;
    for (int i = 0; i < final_result.size(); i++) {
        total_dis          = 0;
        double minDistance = std::numeric_limits<double>::max();
        for (int j = 0; j < final_result.at(i).size(); j++) {
            double dist = calculateDistance(final_result.at(i).at(j), _TrajectoryPoint(start_point_.x, start_point_.y, start_point_.yaw));
            if (dist < minDistance) {
                minDistance   = dist;
                nearest_index = j;
            }
        }
        threadLogger_->info("nearest_index:{}", nearest_index);
        cout << "nearest_index:" << nearest_index << endl;
        temp_traj.clear();
        for (int k = nearest_index; k < final_result.at(i).size(); k++) {
            // 裁减final_result.at(i)的前${predicting_distance_}m，如果不够，则裁减到尽头

            if (k != final_result.at(i).size() - 1) {
                total_dis += hypot(final_result.at(i).at(k + 1).x - final_result.at(i).at(k).x, final_result.at(i).at(k + 1).y - final_result.at(i).at(k).y);
            }
            if (total_dis < predicting_distance_) {
                temp_traj.push_back(final_result.at(i).at(k));
            }
            else {
                break;
            }
        }
        if (temp_traj.size()) {
            path.push_back(temp_traj);
        }
        threadLogger_->info("当前推入的路径大小:{} path.size():{}", temp_traj.size(), path.size());
        cout << "当前推入的路径大小:" << temp_traj.size() << " path.size():" << path.size() << endl;
    }


    temp_traj.clear();
}


// 查找车辆一定阈值范围内的所有路径
std::vector<_SingleTraj> Predicting::findCurrentRoad(double x, double y, double yaw, double distance_threshold) {
    threadLogger_->info("进入 findCurrentRoad 函数");
    cout << "进入 findCurrentRoad 函数" << endl;
    std::vector<_SingleTraj> validRoads;
    for (const auto& road : all_referencelines_) {
        double           minDistance = std::numeric_limits<double>::max();
        _TrajectoryPoint nearestPoint;

        // 找到道路中距离车辆最近的点
        for (const auto& point : road.second.trajectory) {
            double distance = calculateDistance(_TrajectoryPoint(x, y, yaw), point);
            if (distance < minDistance) {
                minDistance  = distance;
                nearestPoint = point;
            }
        }
        double yawDiff           = calculateYawDifference(yaw, nearestPoint.yaw);
        double longitudinalError = std::abs((x - nearestPoint.x) * std::cos(nearestPoint.yaw) + (y - nearestPoint.y) * std::sin(nearestPoint.yaw));
        threadLogger_->info("当前路径id:{} 最近距离：{} 角度差：{} 最近点纵向距离：{}", road.first, minDistance, yawDiff / M_PI * 180.0, longitudinalError);
        if (minDistance < distance_threshold && yawDiff < M_PI / 4 && longitudinalError < 1) {
            int         id = road.first;
            _SingleTraj single_traj;
            single_traj.id         = id;
            single_traj.trajectory = road.second.trajectory;
            validRoads.push_back(single_traj);
        }
    }
    threadLogger_->info("validRoads.size():{}", validRoads.size());
    cout << "validRoads.size():" << validRoads.size() << endl;
    return validRoads;
}
double Predicting::calculateDistance(const _TrajectoryPoint& p1, const _TrajectoryPoint& p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}
double Predicting::calculateYawDifference(double yaw1, double yaw2) {
    double diff = std::fmod(yaw1 - yaw2 + M_PI, 2 * M_PI) - M_PI;
    return std::abs(diff);
}
// 预测车辆接下来 ${predicting_distance_} m 的路径
std::vector<std::vector<_TrajectoryPoint>> Predicting::predictPath(double x, double y, double yaw, double distance_threshold) {
    threadLogger_->info("进入 PreddictPath 函数");
    cout << "进入 PreddictPath 函数" << endl;
    std::vector<_SingleTraj> currentRoads = findCurrentRoad(x, y, yaw, distance_threshold);
    threadLogger_->info("currentRoads.size():{} ", currentRoads.size());
    cout << "currentRoads.size():" << currentRoads.size() << endl;
    double totalDistance = 0;

    // 基于relation来构建所有节点信息
    road_map_ = buildRoadLists();
    threadLogger_->info("road_map_.size():{} ", road_map_.size());
    cout << "road_map_.size():" << road_map_.size() << endl;
    // 更新road_map_信息
    for (const auto currentRoad : currentRoads) {
        std::vector<_TrajectoryPoint> path          = currentRoad.trajectory;
        double                        totalDistance = 0; // 找到最近的点

        double minDist   = std::numeric_limits<double>::max();
        auto   nearestIt = path.begin();
        for (auto it = path.begin(); it != path.end(); ++it) {
            double dist = calculateDistance(*it, _TrajectoryPoint(x, y, yaw));
            if (dist < minDist) {
                minDist   = dist;
                nearestIt = it;
            }
        }
        int currentIndex                     = std::distance(path.begin(), nearestIt);
        totalDistance                        = path.size() - currentIndex;
        road_map_.at(currentRoad.id)->length = totalDistance;
        threadLogger_->info("更新road_map_信息,id:{},截断的位置：{} 路段总长：{} 更新后的路径:{}", currentRoad.id, currentIndex, path.size(), totalDistance);
        cout << "更新road_map_信息,id:" << currentRoad.id << ",截断的位置：" << currentIndex << " 路段总长：" << path.size() << " 更新后的路径:" << totalDistance << endl;
    }
    threadLogger_->info("更新road_map_信息完毕");
    cout << "更新road_map_信息完毕" << endl;
    std::vector<std::vector<Road*>>            temp_road_nodes;
    std::vector<_TrajectoryPoint>              temp_single_traj;
    std::vector<std::vector<_TrajectoryPoint>> final_result;
    int                                        threshold = predicting_distance_;
    for (const auto currentRoad : currentRoads) {
        temp_road_nodes = findPathsToLeafRoads(road_map_.at(currentRoad.id), threshold);
        // 将 temp_road_nodes转化为
        threadLogger_->info("temp_road_nodes.size():{}", temp_road_nodes.size());
        cout << "temp_road_nodes.size():" << temp_road_nodes.size() << endl;
        for (const auto& path : temp_road_nodes) {
            temp_single_traj.clear();
            for (const auto& part_path : path) {
                temp_single_traj.insert(temp_single_traj.end(), all_referencelines_.at(part_path->id).trajectory.begin(), all_referencelines_.at(part_path->id).trajectory.end());
            }

            final_result.push_back(temp_single_traj);
        }
    }
    threadLogger_->info("final_result.size():{}", final_result.size());
    cout << "final_result.size():" << final_result.size() << endl;
    return final_result;
}
std::vector<std::vector<Road*>> Predicting::findPathsToLeafRoads(Road* startRoad, int threshold) {
    threadLogger_->info("进入 findPathsToLeafRoads 函数");
    cout << "进入 findPathsToLeafRoads 函数" << endl;
    std::vector<std::vector<Road*>> allPaths;
    std::vector<Road*>              currentPath;
    dfs(startRoad, 0, threshold, currentPath, allPaths);
    return allPaths;
}
void Predicting::dfs(Road* Current_Road, int currentWeight, int threshold, std::vector<Road*>& currentPath, std::vector<std::vector<Road*>>& allPaths) {
    if (Current_Road == nullptr) {
        return;
    }
    // 将当前节点加入路径
    currentPath.push_back(Current_Road);
    threadLogger_->info("dfs函数内部，当前push_back的路段id:{}", Current_Road->id);
    cout << "dfs函数内部，当前push_back的路段id:" << Current_Road->id << endl;
    // 更新当前权重
    currentWeight += Current_Road->length;

    // 如果当前权重达到或超过阈值，不再继续向下探索
    if (currentWeight >= threshold) {
        allPaths.push_back(currentPath);
        currentPath.pop_back();
        threadLogger_->info("dfs函数内部，当前探索到的路id为 {},已经满足 {} 阈值", Current_Road->id, threshold);
        cout << "dfs函数内部，当前探索到的路id为 " << Current_Road->id << ",已经满足 " << threshold << " 阈值" << endl;
        return;
    }

    // 如果当前节点是叶节点，记录当前路径
    if (Current_Road->following_nodes.empty()) {
        allPaths.push_back(currentPath);
    }
    else {
        // 递归遍历所有子节点
        for (Road* child : Current_Road->following_nodes) {
            dfs(child, currentWeight, threshold, currentPath, allPaths);
        }
    }
    // 回溯，移除当前节点，以便尝试其他路径
    currentPath.pop_back();
}
// 计算轨迹长度
double Predicting::calculateTrajectoryLength(const std::vector<_TrajectoryPoint>& trajectory) {
    double length = 0.0;
    for (size_t i = 1; i < trajectory.size(); ++i) {
        const _TrajectoryPoint& prev = trajectory[i - 1];
        const _TrajectoryPoint& curr = trajectory[i];
        length += std::sqrt(std::pow(curr.x - prev.x, 2) + std::pow(curr.y - prev.y, 2));
    }
    return length;
}

// 构建 road_lists_
std::map<int, Road*> Predicting::buildRoadLists() {
    std::map<int, Road*> roadMap;

    // 第一步：为每个 _SingleTraj 创建对应的 Road 对象，并计算长度
    for (const auto& roadPair : all_referencelines_) {
        int                roadId     = roadPair.first;
        const _SingleTraj& singleTraj = roadPair.second;
        double             length     = calculateTrajectoryLength(singleTraj.trajectory);
        Road*              newRoad    = new Road(roadId, length);
        roadMap[roadId]               = newRoad;
    }
    threadLogger_->info("roadMap.size():{}", roadMap.size());
    cout << "roadMap.size():" << roadMap.size() << endl;

    // 第二步：根据 relation 为每个 Road 对象设置 following_nodes
    for (const auto& relationPair : referenceline_relation_) {
        int  currentRoadId = relationPair.first;
        auto it            = roadMap.find(currentRoadId);
        if (it != roadMap.end()) {
            Road*                   currentRoad  = it->second;
            const std::vector<int>& followingIds = relationPair.second;
            for (int followingId : followingIds) {
                auto followingIt = roadMap.find(followingId);
                if (followingIt != roadMap.end()) {
                    currentRoad->following_nodes.push_back(followingIt->second);
                }
            }
            threadLogger_->info("id:{} following_road.size():{}", currentRoadId, currentRoad->following_nodes.size());
            cout << "id:" << currentRoadId << " following_road.size():" << currentRoad->following_nodes.size() << endl;
        }
    }
    threadLogger_->info("roadMap.size():{}", roadMap.size());
    cout << "roadMap.size():" << roadMap.size() << endl;

    return roadMap;
}
// 释放 Road 对象的内存
void Predicting::freeRoadLists(std::vector<Road*>& road_lists_) {
    for (Road* road : road_lists_) {
        delete road;
    }
    road_lists_.clear();
}
