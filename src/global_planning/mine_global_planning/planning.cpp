#include "planning.h"


Planning::Planning() {
    InitialFunction();
}
Planning::~Planning() {
    threadLogger_->info("析构函数已被调用");
}


bool Planning::InitialFunction() {
    road_directed_graph_.clear(); // 储存所有区域信息的容器
    map_border_.clear();
    inner_borders_.clear();
    all_referencelines_.clear();
    global_path_.clear();
    v_has_calculate_pair_.clear();
    task_type_ = TaskType::RESERVED;


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
bool Planning::ReadAllMapFile() {
#ifdef SKIP_HEADER
#else
    memset(&m_tar_rviz_data_, 0, sizeof(tarRviz));
    m_tar_rviz_data_.minx = INF;
    m_tar_rviz_data_.miny = INF;
    // 读取地图信息
    if (!configio_.GetMap(road_directed_graph_, map_border_, all_referencelines_, sequence_mapping_, m_tar_rviz_data_) || !configio_.GetVehicleParam(vehicle_param_)) {
        return false;
    }
    else {
        task_type_ = static_cast<TaskType>(vehicle_param_.task_type);
        return true;
    }

#endif
}


void Planning::GlobalPathPlanningIntface(vector<_TrajectoryPoint>& path) {
    threadLogger_->info("Enter GlobalPathPlanningIntface");
    path.clear();
    global_path_.clear();
    // 路径规划：作业点参考路径匹配及裁剪拼接
    if (!PathPlanning()) {
        return;
    }
    threadLogger_->info("PathPlanning 成功");


    // 只针对DISPATCH任务进行参考路径拼接
    //  HybirdA*拟合：起点、终点需要拟合则拟合，否则跳过
    if (task_type_ == TaskType::DISPATCH) {
        if (!HybirdAStarFitting()) {
            return;
        }
    }
    if (IsShortDistance()) {
        path = global_path_;
        return;
    }
    Helper::RemoveAfterSamePoint(global_path_);

    threadLogger_->info("StartEndPointProcess global_path_.size():{}", global_path_.size());
    // 将起点、终点放入全局路径
    StartEndPointProcess();


    threadLogger_->info("global_path_.size():{}", global_path_.size());

    // 均匀碾压：对除了过磅、洗车和倒车之外的路段进行横向偏移
    if (vehicle_param_.offset_enable == true) {
        if (!PathOffset()) {
            return;
        }
    }


    // 计算累计s
    Helper::CalDistance(global_path_);

    //
    // 计算路径点曲率
    Helper::CalCurv(global_path_);


    // 角度转换
    Helper::Calrad2deg(global_path_);


    // 速度规划：限速设置、梯形速度规划
    if (!SpeedPlanning()) {
        return;
    }
    Helper::RemoveAfterSamePoint(global_path_);


    // 路径断裂检查,涉及相邻点间距和相邻点角度差
    if (!Helper::CheckPathFracture(global_path_)) {
        threadLogger_->info("CheckPathFracture fail");
        return;
    }
    threadLogger_->info("CheckPathFracture");

    // 超速检测
    if (!Helper::OverSpeedCheck(global_path_)) {
        threadLogger_->info("OverSpeedCheck fail");
        return;
    }
    threadLogger_->info("OverSpeedCheck");


    // 路径点顺序和direction校验
    if (!Helper::SequenceAndDirectionCheck(global_path_)) {
        threadLogger_->info("SequenceAndDirectionCheck fail");
        return;
    }


    // // 计算加速度
    // Helper::CalAcc(global_path_);
    // threadLogger_->info("CalAcc");

    path = global_path_;
    threadLogger_->info("final_out global_Path.size():{}", global_path_.size());
    return;
}


bool Planning::ProgressiveHybirdAStar(_SinglePoint& input_point, bool search_direction, int search_start, int& search_index, vector<_TrajectoryPoint>& result_trajectory, unsigned char rule_id, int off_set) {
    long long    time_threshold = 0.8 * 1000 * 1000;
    int          counter        = 0;
    bool         success_flag   = false;
    _SinglePoint temp_start, temp_end;
    int          cal = 0;
    threadLogger_->info("搜索方向  -- 1(顺着参考线)  --0(逆着参考线)：{}", search_start, search_direction);
    int offset = off_set;
    if (search_direction == true) // 顺着参考线进行搜索，这种case为找拼接终点
    {
        cal = 0;

        for (int i = search_start + offset; i < global_path_.size(); i += 5) {
            cal++;
            counter++;
            temp_end.x   = global_path_.at(i).x;
            temp_end.y   = global_path_.at(i).y;
            temp_end.z   = global_path_.at(i).z;
            temp_end.yaw = global_path_.at(i).yaw;
            threadLogger_->info("第 {}个候选点，其索引：{},yaw:{}, rule_id:{}", cal, i, temp_end.yaw, float(rule_id));
            // 到8个点的时候，时间得提升到800ms
            if (counter > 4) time_threshold = 0.8 * 1000 * 1000;
            if (ApplyHibridAStarWithTime(input_point, temp_end, result_trajectory, rule_id,
                                         time_threshold)) // rule_id:5，只前进
            {
                search_index = i;
                success_flag = true;
                break;
            }
            if (counter > 8) {
                threadLogger_->info("最多搜索8个点");
                return false;
            }
        }
    }
    else { // 逆着参考线进行搜索，这种case为找拼接起点
        cal     = 0;
        counter = 0;
        for (int i = search_start - offset; i > 0; i -= 5) {
            cal++;
            counter++;
            temp_start.x   = global_path_.at(i).x;
            temp_start.y   = global_path_.at(i).y;
            temp_start.z   = global_path_.at(i).z;
            temp_start.yaw = global_path_.at(i).yaw;
            threadLogger_->info("第{}个候选点，其索引：{} rule_id:{}", cal, i, float(rule_id));
            if (counter > 4) time_threshold = 0.8 * 1000 * 1000;
            if (ApplyHibridAStarWithTime(temp_start, input_point, result_trajectory, rule_id,
                                         time_threshold)) // rule_id:5，只前进
            {
                search_index = i;
                success_flag = true;
                break;
            }
            if (counter > 8) {
                threadLogger_->info("最多搜索16个点，不搜了");
                return false;
            }
        }
    }
    if (success_flag == true) {
        threadLogger_->info("ProgressiveHybirdAStar success");
        return true;
    }
    else {
        return false;
    }
}

bool Planning::ApplyHibridAStarWithTime(_SinglePoint s_point, _SinglePoint e_point, vector<_TrajectoryPoint>& traj, unsigned char plan_rule_id, long long time_threshold) {
    // 起始点、目标点结构转换
    Point temp_start_point(s_point.x, s_point.y, s_point.z, s_point.yaw, MotionDirection ::Forward);
    Point temp_end_point(e_point.x, e_point.y, e_point.z, e_point.yaw, MotionDirection ::Forward);


    // 搜索获取轨迹
    traj.clear();
    Path     final_path;
    PlanRule planrule = static_cast<PlanRule>(plan_rule_id);


    if (my_optimal_path_.SearchGlobalPath(temp_start_point, temp_end_point, vehicle_param_, final_path, time_threshold, planrule) == PlanResult::Plan_OK) {
        threadLogger_->info("SearchGlobalPath success");
        _TrajectoryPoint temp_point;
        for (int i = 0; i < final_path.size(); i++) {
            temp_point.Clear();
            temp_point.x         = final_path.at(i).x;
            temp_point.y         = final_path.at(i).y;
            temp_point.z         = final_path.at(i).z;
            temp_point.yaw       = final_path.at(i).angle;
            temp_point.direction = final_path.at(i).direction;
            temp_point.attribute = 4;
            temp_point.curvature = final_path.at(i).curvature;
            traj.emplace_back(temp_point);
        }
        // 针对rule:5的情况，进行绕圈检查，检查原理：判断两个点之间的距离进行判断，是否有间距小于0.8m的点

        // if (plan_rule_id == 5 || plan_rule_id == 4) {
        //     threadLogger_->info("开始绕圈检测");
        //     // 针对rule:5的情况，进行绕圈检查，检查原理：判断角度是否产生0~2M_PI的变化
        //     if (Helper::doesTrajectorySelfIntersect(final_path)) {
        //         threadLogger_->info("检测到路径绕圈");
        //         return false;
        //     }
        // }
        // threadLogger_->info("绕圈检测达标");

        return true;
    }
    else {
        threadLogger_->error(" Failed to plan the path by hibrid A star  ");

        return false;
    }
    return true;
}


// 成功：true，失败：false
bool Planning::RandomOffsetWithoutCuravture() {
    vector<_TrajectoryPoint> input_points, temp_path, global_path_copy;
    global_path_copy = global_path_;
    random_device rd;
    mt19937       gen(rd());

    // 定义您想要生成的浮点数的集合
    vector<float> weights = {-1.0, -0.75, -0.5, -0.25, 0, 0.25, 0.5, 0.75, 1.0};

    // 使用uniform_int_distribution从集合中随机选择一个索引
    uniform_int_distribution<size_t> dis(0, weights.size() - 1);
    float                            weight = 0.0;


    int num = 0;
    do {
        global_path_.clear();
        num++;
        threadLogger_->info("num:{}", num);
        if (num > 50) {
            return false;
        }

        temp_path = global_path_copy;
        // 从集合中随机选择一个权重
        weight = weights[dis(gen)];
        vector<pair<int, int>> reverse_section, forward_section;

        int  start = 0, end = 0;
        bool flag1;

        if (temp_path.front().offset_flag == true) // 起步就是需要偏移的路段
        {
            threadLogger_->info("起步就是需要偏移的路段");

            flag1 = true;
            for (int i = 0; i < temp_path.size() - 1; i++) {
                if (temp_path.at(i + 1).offset_flag != temp_path.at(i).offset_flag) {
                    end = i;
                    if (flag1 == true) {
                        forward_section.push_back(make_pair(start, end));
                        flag1 = false;
                    }
                    else {
                        reverse_section.push_back(make_pair(start, end));
                        flag1 = true;
                    }
                    start = i + 1;
                }
            }
        }
        else // 起步就是不需要偏移的路段
        {
            threadLogger_->info("起步就是不需要偏移的路段");

            flag1 = false;
            for (int i = 0; i < temp_path.size() - 1; i++) {
                if (temp_path.at(i + 1).offset_flag != temp_path.at(i).offset_flag) {
                    end = i;
                    if (flag1 == true) {
                        forward_section.push_back(make_pair(start, end));
                        flag1 = false;
                    }
                    else {
                        reverse_section.push_back(make_pair(start, end));
                        flag1 = true;
                    }
                    start = i + 1;
                }
            }
        }
        if (temp_path.back().offset_flag == true) // 最后一段为需要偏移的道路
        {
            forward_section.push_back(make_pair(start, temp_path.size() - 1));
        }
        else {
            reverse_section.push_back(make_pair(start, temp_path.size() - 1));
        }

        threadLogger_->info("规划出的路径包含{}个偏移路段，{}个不偏移路段", forward_section.size(), reverse_section.size());

        for (int i = 0; i < forward_section.size(); i++) {
            threadLogger_->info("偏移路段索引：({},{})", forward_section.at(i).first, forward_section.at(i).second);
        }

        for (int i = 0; i < reverse_section.size(); i++) {
            threadLogger_->info("不偏移路段索引：({},{})", reverse_section.at(i).first, reverse_section.at(i).second);
        }

        float off_set = 0.0;

        // 如果先前
        if (temp_path.front().direction == 0) {
            int j = 0;
            for (int i = 0; i < forward_section.size(); i++) {
                start = forward_section.at(i).first;
                end   = forward_section.at(i).second;
                int a = 0, sum = 0;
                input_points.clear();
                for (int m = start; m <= end; m = m + 1) {
                    sum++;
                }

                int           m;
                vector<float> vec_off_set;
                for (m = start; m <= end; m = m + 1) {
                    a++;
                    if (end - start > 250) {
                        off_set = CalculateOffSetWithoutCuravture(a, sum + 1, weight); //
                    }
                    else // 如果改段路太短，不进行偏移
                    {
                        off_set = 0.0;
                    }

                    temp_path.at(m).x = temp_path.at(m).x + off_set * cos(temp_path.at(m).yaw + M_PI / 2);
                    temp_path.at(m).y = temp_path.at(m).y + off_set * sin(temp_path.at(m).yaw + M_PI / 2);


                    input_points.push_back(temp_path.at(m));
                    vec_off_set.push_back(off_set);
                }


                global_path_.insert(global_path_.end(), input_points.begin(), input_points.end());


                if (j < reverse_section.size()) {
                    global_path_.insert(global_path_.end(), temp_path.begin() + reverse_section.at(j).first, temp_path.begin() + reverse_section.at(j).second + 1);
                    j++;
                }
            }
        }
        else {
            int i = 0;
            for (int j = 0; j < reverse_section.size(); j++) {
                global_path_.insert(global_path_.end(), temp_path.begin() + reverse_section.at(j).first, temp_path.begin() + reverse_section.at(j).second + 1);
                if (i < forward_section.size()) {
                    start = forward_section.at(i).first;
                    end   = forward_section.at(i).second;
                    int a = 0, sum = 0;
                    input_points.clear();
                    for (int m = start; m <= end; m = m + 1) {
                        sum++;
                    }

                    int m;
                    for (m = start; m <= end; m = m + 1) {
                        a++;
                        off_set = CalculateOffSetWithoutCuravture(a, sum + 1, weight);

                        temp_path.at(m).x = temp_path.at(m).x + off_set * cos(temp_path.at(m).yaw + M_PI / 2);
                        temp_path.at(m).y = temp_path.at(m).y + off_set * sin(temp_path.at(m).yaw + M_PI / 2);

                        input_points.push_back(temp_path.at(m));
                    }

                    if (m != end + 1) {
                        input_points.push_back(temp_path.at(end));
                    }
                    threadLogger_->info("输入点的数量：{}", input_points.size());

                    threadLogger_->info("当前偏移的权重：{}", weight);

                    global_path_.insert(global_path_.end(), input_points.begin(), input_points.end());
                    threadLogger_->info("input_points.size():{}", input_points.size());


                    i++;
                }
            }
        }


    } while (!Helper::CheckCurvature(global_path_)); // 碰撞检测通过、曲率校验通过
    threadLogger_->info("找到合适的权重：{}", weight);

    return true;
}

float Planning::CalculateOffSetWithoutCuravture(int index, int sum, float weight) {
    float max_l = vehicle_param_.max_l;
    float L     = max_l * weight; // 控制默认偏移量
    L           = L * WeightFunction(index, sum);
    return L;
}


float Planning::WeightFunction(int k, int sum) {
    // int sita = vehicle_param_.sita;
    int sita = 200;
    int x;
    if (k < sum / 2) {
        x = k;
    }
    else {
        x = sum - 1 - k;
    }
    // return 1.0 / (1 + pow(vehicle_param_.base, (-(x - sita))));
    return 1.0 / (1 + pow(1.1, (-(x - sita))));
}


// 全局轨迹规划--路径规划
bool Planning::PathPlanning() {
    threadLogger_->info("Enter PathPlanning");
    time_t start_time, end_time;
    time(&start_time);
    start_point_.yaw = start_point_.yaw / 180.0 * M_PI;
    end_point_.yaw   = end_point_.yaw / 180.0 * M_PI;
    threadLogger_->info(" task_type_: {}", (int)task_type_);

    if (task_type_ != TaskType::DISPATCH) {
        // 临时挪车不走参考路径
        threadLogger_->error("挪车、装载、卸载");
        if (!NotFollowReferencelinePlanning()) {
            return false;
        }
    }
    else {
        threadLogger_->error("调度");
        if (!FollowReferencelinePlanning()) {
            return false;
        }
    }
    return true;
}
// 非调度规划任务
bool Planning::NotFollowReferencelinePlanning() {
    vector<_TrajectoryPoint> temp_traj;
    long long                time_threshold = 2 * 1000 * 1000;
    unsigned char            rule_id_1 = 4, rule_id_2 = 5, rule_id_3 = 2;
    if (task_type_ == TaskType::TEMP_MOVE_CAR) { // 临时挪车任务，先采用纯倒车的规划，再采用纯往前开的策略
        // 先倒车规划，不行正向规划
        threadLogger_->error("挪车");
        if (!ApplyHibridAStarWithTime(start_point_, end_point_, temp_traj, rule_id_1, time_threshold)) {
            if (!ApplyHibridAStarWithTime(start_point_, end_point_, temp_traj, rule_id_2, time_threshold)) {
                threadLogger_->error("Hybird A*无法规划出当前起点至终点的路径");
                error_type_ = ErrorType::POINT_UNREASONABLE;
                return false;
            }
        }
        global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.end());
        threadLogger_->info("临时挪车,路长:{}", global_path_.size());
    }
    else if (task_type_ == TaskType::LOAD) { // 装载任务，先纯倒车，纯倒车不行再往前开，再倒车
        threadLogger_->error("装载");
        vehicle_param_.end_offset_distance = 8.0; // 装载任务，最后倒车进去的轨迹必须是一条8m的直线
        if (!ApplyHibridAStarWithTime(start_point_, end_point_, temp_traj, rule_id_1, time_threshold)) {
            if (!ApplyHibridAStarWithTime(start_point_, end_point_, temp_traj, rule_id_3, time_threshold)) {
                threadLogger_->error("Hybird A*无法规划出当前起点至终点的路径");
                error_type_ = ErrorType::POINT_UNREASONABLE;
                return false;
            }
        }
        global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.end());
        threadLogger_->info("装载,路长:{}", global_path_.size());
    }
    else if (task_type_ == TaskType::UNLOAD) { // 卸载任务，先前进，后倒退进入卸载点
        threadLogger_->error("卸载");
        if (!ApplyHibridAStarWithTime(start_point_, end_point_, temp_traj, rule_id_3, time_threshold)) {
            threadLogger_->error("Hybird A*无法规划出当前起点至终点的路径");
            error_type_ = ErrorType::POINT_UNREASONABLE;
            return false;
        }
        global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.end());
        threadLogger_->info("卸载,路长:{}", global_path_.size());
    }
    else {
        threadLogger_->info("未定义的任务");
        return false;
    }

    return true;
}


// 沿路网路径规划
bool Planning::FollowReferencelinePlanning() {
    // 起点、终点渐进式扩大搜索
    vector<pair<pair<int, int>, int>> success_pair;
    v_has_calculate_pair_.clear();
    bool           searched_flag = false, is_found = false; // 用于跟踪是否找到了成功的路径对
    double         end_search_radius = 0.5, start_search_radius = 0.5;
    map<int, bool> start_path_vec;
    vector<int>    end_path_vec;
    while (end_search_radius <= 0.6) {
        if (Helper::GetReferencelinesWithRadiusAndAngle(end_point_, all_referencelines_, end_search_radius, end_path_vec)) {
            if (searched_flag == true) {
                return false;
            }
            searched_flag = true;
            threadLogger_->info("终点搜索半径：{},搜索到路径数量:{}", end_search_radius, end_path_vec.size());
            threadLogger_->info("搜索到的路径ID信息如下");
            for (auto i : end_path_vec) {
                threadLogger_->info(i);
            }
            start_search_radius = 0.5;
            while (start_search_radius <= 200) {
                if (Helper::GetReferencelinesWithRadius(start_point_, all_referencelines_, start_search_radius, start_path_vec)) {
                    threadLogger_->info("起点搜索半径：{},搜索到路径数量:{}", start_search_radius, start_path_vec.size());
                    threadLogger_->info("搜索到的路径ID信息如下");
                    for (auto i : start_path_vec) {
                        threadLogger_->info(i.first);
                    }
                    map<int, bool> start_path_vec_switch;
                    vector<int>    end_path_vec_switch;
                    for (auto i : start_path_vec) {
                        start_path_vec_switch[GlobalVariable::getInstance()->BinarySearch(sequence_mapping_, i.first)] = i.second;
                    }

                    for (auto i : end_path_vec) {
                        end_path_vec_switch.push_back(GlobalVariable::getInstance()->BinarySearch(sequence_mapping_, i));
                    }

                    // 在start_path_vec_switch和end_path_vec_switch中查找连通路径
                    for (auto start : start_path_vec_switch) {
                        for (auto end : end_path_vec_switch) {
                            if (HasSearched(start.first, end)) {
                                threadLogger_->info("路径{}->路径{}已经计算过，为节约计算资源，予以跳过", start.first, end);
                                continue;
                            }
                            threadLogger_->info("索引  start:{},end:{}", start.first, end);
                            if (IsConnect(start.first, end)) {
                                threadLogger_->info("路径{}与路径{}联通", sequence_mapping_.at(start.first), sequence_mapping_.at(end));
                                success_pair.push_back(make_pair(make_pair(start.first, end), road_sequence_.size()));
                                // 如何找到的连通路径是顺向的，并且起点搜索距离已经大于5m，就可以退出来，没必要继续扩大搜索了
                                if (start.second == false) {
                                    threadLogger_->info("找到顺向车道，准备break");
                                    is_found = true; // 标记为已找到
                                    break;           // 退出内层循环
                                }
                            }
                            else {
                                threadLogger_->info("start:{},end:{}", start.first, end);
                                threadLogger_->info("路径{}与路径{}不联通", sequence_mapping_.at(start.first), sequence_mapping_.at(end));
                            }

                            v_has_calculate_pair_.push_back(pair(start.first, end));
                        }
                        if (is_found) break; // 如果已找到，退出中间层循环
                    }
                    if (is_found) break; // 如果已找到，退出外层循环
                }
                else {
                    threadLogger_->info("起点搜索半径{},无参考路径", start_search_radius);
                }
                start_search_radius += 0.5;
            }
            if (is_found) break;
        }
        else {
            threadLogger_->info("终点搜索,半径{}内无参考路径", end_search_radius);
        }
        end_search_radius += 0.5;
    }

    if (success_pair.empty()) {
        error_type_ = ErrorType::ROAD_GRAPH_ERROR;
        return false;
    }
    else {
        threadLogger_->info("规划算法找到的成功路径对id如下：");
        for (int i = 0; i < success_pair.size(); i++) {
            threadLogger_->info("{},{}", sequence_mapping_.at(success_pair.at(i).first.first), sequence_mapping_.at(success_pair.at(i).first.second));
        }
    }


    // 从success_pair中挑选最优的路径对
    int            min = INT_MAX;
    pair<int, int> best_pair;
    for (int i = 0; i < success_pair.size(); i++) {
        if (success_pair.at(i).second < min) {
            best_pair.first  = success_pair.at(i).first.first;
            best_pair.second = success_pair.at(i).first.second;
            min              = success_pair.at(i).second;
        }
    }

    dijkstra_.searchpath(best_pair.first, best_pair.second);
    road_sequence_ = dijkstra_.GetPath();


    threadLogger_->info("找到路径对{}-{}", sequence_mapping_.at(best_pair.first), sequence_mapping_.at(best_pair.second));
    // 找到起点、终点对应的索引及其横纵向距离
    _SingleTraj start_traj, end_traj;

    start_key_ = sequence_mapping_.at(best_pair.first);
    end_key_   = sequence_mapping_.at(best_pair.second);
    start_traj = all_referencelines_.at(start_key_);
    end_traj   = all_referencelines_.at(end_key_);
    Helper::CalNearestIndex(start_point_, start_traj, start_index_, start_lat_dis_, start_lon_dis_, start_distance_, start_angle_diff_);
    Helper::CalNearestIndex(end_point_, end_traj, end_index_, end_lat_dis_, end_lon_dis_, end_distance_, end_angle_diff_);
    threadLogger_->info("起点匹配上的路径索引{}，横向距离{}，纵向距离{}, 角度误差{}", start_index_, start_lat_dis_, start_lon_dis_, start_angle_diff_ / M_PI * 180.0);
    threadLogger_->info("终点匹配上的路径索引{}，横向距离{}，纵向距离{}, 角度误差{}", end_index_, end_lat_dis_, end_lon_dis_, end_angle_diff_ / M_PI * 180.0);

    // 路径裁剪拼接
    PathClipAndSplice();
    return true;
}
bool Planning::HasSearched(int start, int end) {
    for (auto pair : v_has_calculate_pair_) {
        if (pair.first == start && pair.second == end) return true;
    }
    return false;
}


bool Planning::IsConnect(int start, int end) {
    dijkstra_.threadLogger_ = threadLogger_;
    dijkstra_.InitialDijkstra(road_directed_graph_);
    if (dijkstra_.searchpath(start, end)) {
        road_sequence_ = dijkstra_.GetPath();
        return true;
    }
    else {
        return false;
    }
}
void Planning::StartEndPointProcess() {
    // 计算全局路径第一个点与起点的角度偏差
    threadLogger_->info("StartEndPointProcess 开始");


    // float start_angle_diff;
    // start_angle_diff = atan2(start_point_.y - global_path_.front().y, start_point_.x - global_path_.front().x);
    // if (start_angle_diff < 0) {
    //     start_angle_diff += 2 * M_PI; // 将终点与全局路径最后一个点的角度偏差规范[0,2π）
    // }
    // float first_angle_diff = fabs(start_angle_diff - global_path_.front().yaw) * 180.0 / M_PI >= 180 ? 360 - fabs(start_angle_diff - global_path_.front().yaw) * 180 / M_PI : fabs(start_angle_diff - global_path_.front().yaw) * 180 / M_PI;
    // if ((first_angle_diff < 90 && global_path_.front().direction == 0) || (first_angle_diff > 90 && global_path_.front().direction == 1) || fabs(start_point_.x - global_path_.front().x) <= 0.3 && fabs(start_point_.y - global_path_.front().y) <= 0.3) {
    //     global_path_.erase(global_path_.begin());
    //     threadLogger_->info("全局路径第一个位于实际起点前面，或者太近，现予以去除");
    // }
    // else {}
    // // 添加起点到全局路径
    // _TrajectoryPoint first_point;
    // first_point.x           = start_point_.x;
    // first_point.y           = start_point_.y;
    // first_point.z           = start_point_.z;
    // first_point.yaw         = start_point_.yaw;
    // first_point.speed_limit = 0;
    // first_point.speed       = 0;
    // first_point.curvature   = 0;
    // first_point.distance    = 0;
    // first_point.direction   = global_path_.front().direction;
    // global_path_.insert(global_path_.begin(), first_point);

    // 将终点添加到全局路径中
    // 判断终点与全局路径最后一个点的角度偏差，基于角度偏差信息来判断是否 将其抛弃
    float end_point_last_point_angle_diff;
    end_point_last_point_angle_diff = atan2(end_point_.y - global_path_.back().y, end_point_.x - global_path_.back().x);
    if (end_point_last_point_angle_diff < 0) {
        end_point_last_point_angle_diff += 2 * M_PI; // 将终点与全局路径最后一个点的角度偏差规范[0,2π）
    }
    float last_angle_diff = fabs(end_point_last_point_angle_diff - global_path_.back().yaw) * 180.0 / M_PI >= 180 ? 360 - fabs(end_point_last_point_angle_diff - global_path_.back().yaw) * 180 / M_PI : fabs(end_point_last_point_angle_diff - global_path_.back().yaw) * 180 / M_PI;

    if ((last_angle_diff > 90 && global_path_.back().direction == 0) || (fabs(end_point_.x - global_path_.back().x) <= 0.3 && fabs(end_point_.y - global_path_.back().y) <= 0.3) || (last_angle_diff < 90 && global_path_.back().direction == 1)) {
        global_path_.pop_back();
    }
    else {}
    _TrajectoryPoint last_point;
    last_point.x           = end_point_.x;
    last_point.y           = end_point_.y;
    last_point.z           = end_point_.z;
    last_point.yaw         = end_point_.yaw;
    last_point.speed_limit = 0;

    last_point.speed     = 0;
    last_point.curvature = 0;
    last_point.distance  = 0;
    last_point.direction = global_path_.back().direction;
    global_path_.push_back(last_point);
    threadLogger_->info("将规划终点作为最后一个点添加进global_path的末尾");
    threadLogger_->info("StartEndPointProcess 结束");
}
bool Planning::PathOffset() {
    threadLogger_->info("均匀碾压功能开启");
    for (int i = 0; i < global_path_.size(); i++) {
        global_path_.at(i).offset_flag = true; // 先将所有路径点的offset_flag属性设置为true
    }
    // 设置temp中，每个点的offset_flag信息，来确定此次规划任务需要偏移的路段，true表示需要偏移，false表示不需要偏移
    for (int i = 0; i < global_path_.size(); i++) {
        if (global_path_.at(i).attribute == 6 || global_path_.at(i).attribute == 7) {
            for (int j = i - 10; j < i + 10; j++) {
                if (j >= 0 && j < global_path_.size()) {
                    global_path_.at(j).offset_flag = false; // 将过磅点和洗车点左右10m设置为无需偏移的路段
                }
            }
        }
        if (global_path_.at(i).direction == 1) {
            global_path_.at(i).offset_flag = false; // 将倒车的路段offset_flag也设置为false,即不需要进行偏移
        }
    }

    if (!RandomOffsetWithoutCuravture()) // 不基于曲率的轨迹偏移
    {
        error_type_ = ErrorType::OFFSET_FAIL;
        return false;
    }
    threadLogger_->info("均匀碾压功能完毕");
    return true;
}
void Planning::PathClipAndSplice() {
    if (road_sequence_.size() == 1) {
        threadLogger_->info("起点、终点位于同一条参考路径");
        int temp_key = sequence_mapping_.at(road_sequence_.at(0));
        if (start_index_ <= end_index_) {
            global_path_.insert(global_path_.end(), all_referencelines_.at(temp_key).trajectory.begin() + start_index_, all_referencelines_.at(temp_key).trajectory.begin() + end_index_ + 1);
        }
        else // 同一路段，支持短距离倒车
        {
            global_path_.insert(global_path_.end(), all_referencelines_.at(temp_key).trajectory.begin() + end_index_, all_referencelines_.at(temp_key).trajectory.begin() + start_index_ + 1);
            reverse(global_path_.begin(), global_path_.end());
            for (auto point : global_path_) {
                if (point.direction == 0) {
                    point.direction = 1; // 修改轨迹的direction
                }
            }
        }
    }
    else {
        threadLogger_->info("打印road_sequence_信息");
        for (auto i : road_sequence_) {
            threadLogger_->info(sequence_mapping_.at(i));
        }
        for (int i = 0; i < road_sequence_.size(); i++) {
            int temp_key = sequence_mapping_.at(road_sequence_.at(i));
            if (i == 0) {
                global_path_.insert(global_path_.end(), all_referencelines_.at(temp_key).trajectory.begin() + start_index_, all_referencelines_.at(temp_key).trajectory.end());
            }
            else if (i == road_sequence_.size() - 1) {
                global_path_.insert(global_path_.end(), all_referencelines_.at(temp_key).trajectory.begin(), all_referencelines_.at(temp_key).trajectory.begin() + end_index_);
            }
            else {
                global_path_.insert(global_path_.end(), all_referencelines_.at(temp_key).trajectory.begin(), all_referencelines_.at(temp_key).trajectory.end());
            }
        }
    }

    threadLogger_->info("PathClipAndSplice---global_path_.size():{}", global_path_.size());
}
bool Planning::HybirdAStarFitting() {
    //  初始化HybrdiA*算法地图边界及voronoi图
    my_optimal_path_.threadLogger_ = threadLogger_;
    my_optimal_path_.InitVoronoiAndBound(start_point_, map_border_, inner_borders_, vehicle_param_, true);
    // 基于横纵向距离来判断是否进行hybirdA*拟合
    threadLogger_->info("Enter HybirdAStarFitting");
    double        lat_threshold = 0.7, lon_threshold = 3;
    unsigned char rule_id_1 = 4, rule_id_3 = 5;
    long long     time_threshold     = 0.8 * 1000 * 1000;
    bool          start_need_fitting = false, end_need_fitting = false;
    int           off_set = 23;
    if (start_lat_dis_ > lat_threshold || fabs(start_lon_dis_) > lon_threshold || start_angle_diff_ > 8.0 / 180.0 * M_PI) { // 横向阈值大于0.7m,或者纵向阈值大于3m,就需要进行hybirdA*拟合
        start_need_fitting = true;
        // 当start_index==0,end_index==0,start_key_==end_key_时，说明这是一个从装载点到驶离装载点的任务，off_set必须是0
        if (start_index_ == 0) {
            off_set = 0;
        }
    }
    if (end_lat_dis_ > lat_threshold || fabs(end_lon_dis_) > lon_threshold) {
        end_need_fitting = true;
    }

    // 先看起点
    if (start_need_fitting) // 起点需要进行HybirdA*拟合
    {
        threadLogger_->info("起点需要HybirdA*拟合,offset:{}", off_set);
        vector<_TrajectoryPoint> temp_traj;

        int search_index = 0;
        if (JudgeFittingDirection(start_point_, 0, true)) {
            if (!ProgressiveHybirdAStar(start_point_, true, 0, search_index, temp_traj, rule_id_3, off_set)) {
                threadLogger_->error("调度，起点需要hybirdA*拟合，off_set:{},规划失败", off_set);
                error_type_ = ErrorType::POINT_UNREASONABLE;
                return false;
            }
        }
        else {
            if (!ProgressiveHybirdAStar(start_point_, true, 0, search_index, temp_traj, rule_id_1, off_set)) {
                threadLogger_->error("调度，起点需要hybirdA*拟合，规划失败");
                error_type_ = ErrorType::POINT_UNREASONABLE;
                return false;
            }
        }
        global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
        global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
    }
    // 最后看终点
    if (end_need_fitting) // 终点需要进行HybirdA*拟合
    {
        threadLogger_->info("终点需要HybirdA*拟合");
        vector<_TrajectoryPoint> temp_traj;

        int search_index = 0;
        if (JudgeFittingDirection(end_point_, global_path_.size() - 1, false)) {
            if (!ProgressiveHybirdAStar(end_point_, false, global_path_.size() - 1, search_index, temp_traj, rule_id_3, off_set)) {
                threadLogger_->error("调度，终点需要hybirdA*正向拟合，规划失败");
                error_type_ = ErrorType::POINT_UNREASONABLE;
                return false;
            }
        }
        else {
            if (!ProgressiveHybirdAStar(end_point_, false, global_path_.size() - 1, search_index, temp_traj, rule_id_1, off_set)) {
                threadLogger_->error("调度，终点需要hybirdA*倒车拟合，规划失败");
                error_type_ = ErrorType::POINT_UNREASONABLE;
                return false;
            }
        }
        global_path_.erase(global_path_.begin() + search_index, global_path_.end());
        global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.end());
    }
    my_optimal_path_.DeleteVoronoiSpace(true);
    threadLogger_->info("HybirdAStarFitting结束");
    return true;
}
bool Planning::JudgeFittingDirection(_SinglePoint point, int search_index, bool is_start) {
    // 判断tra
    // if (is_start) {
    //     if ((search_index + 10) < global_path_.size()) {
    //         double lon_dis = (global_path_.at(search_index + 10).x - point.x) * cos(point.yaw) + (global_path_.at(search_index + 10).y - point.y) * sin(point.yaw);
    //         if (lon_dis >= 0) {
    //             threadLogger_->info("正向拟合");
    //             return true; // 正向拟合
    //         }
    //         else {
    //             threadLogger_->info("倒车拟合");
    //             return false; // 倒车拟合
    //         }
    //     }
    //     return true;
    // }
    // else {
    //     if ((search_index - 10) >= 0) {
    //         double lon_dis = (global_path_.at(search_index - 10).x - point.x) * cos(point.yaw) + (global_path_.at(search_index - 10).y - point.y) * sin(point.yaw);
    //         if (lon_dis >= 0) {
    //             threadLogger_->info("倒向拟合");
    //             return false; // 倒车拟合
    //         }
    //         else {
    //             threadLogger_->info("正向拟合");
    //             return true; // 正向拟合
    //         }
    //     }
    //     return true;
    // }
    if (is_start) {
        if ((search_index + 10) < global_path_.size()) {
            double lon_dis = (point.x - global_path_.at(search_index + 10).x) * cos(global_path_.at(search_index + 10).yaw) + (point.y - global_path_.at(search_index + 10).y) * sin(global_path_.at(search_index + 10).yaw);
            if (lon_dis <= 0) {
                threadLogger_->info("正向拟合");
                return true; // 正向拟合
            }
            else {
                threadLogger_->info("倒车拟合 point:({},{})  global_path_.at(search_index + 10):({},{},{})  lon_dis:{}", point.x, point.y, global_path_.at(search_index + 10).x, global_path_.at(search_index + 10).y, global_path_.at(search_index + 10).yaw, lon_dis);
                return false; // 倒车拟合
            }
        }
        return true;
    }
    else {
        if ((search_index - 10) >= 0) {
            double lon_dis = (point.x - global_path_.at(search_index - 10).x) * cos(global_path_.at(search_index - 10).yaw) + (point.y - global_path_.at(search_index - 10).y) * sin(global_path_.at(search_index - 10).yaw);
            if (lon_dis <= 0) {
                threadLogger_->info("倒向拟合");
                return false; // 倒车拟合
            }
            else {
                threadLogger_->info("正向拟合");
                return true; // 正向拟合
            }
        }
        return true;
    }
}
bool Planning::SpeedPlanning() {
    my_speed_planning_.threadLogger_ = threadLogger_;

    if (!my_speed_planning_.SpeedPlanning(global_path_, vehicle_param_)) {
        threadLogger_->error("SpeedPlanning  failed !!!");

        error_type_ = ErrorType::SPEED_PLANNING_FAIL;
        return false;
    }
    threadLogger_->info("SpeedPlanning() end");
    return true;
}
bool Planning::IsShortDistance() {
    if (global_path_.size() <= 2) {
        threadLogger_->info("超短距离规划");
        global_path_.clear();
        _TrajectoryPoint temp_point;
        temp_point.x           = start_point_.x;
        temp_point.y           = start_point_.y;
        temp_point.z           = start_point_.z;
        temp_point.yaw         = start_point_.yaw / M_PI * 180.0;
        temp_point.curvature   = 0;
        temp_point.speed       = 0;
        temp_point.distance    = 0;
        temp_point.attribute   = 0;
        temp_point.speed_limit = 0;
        temp_point.direction   = 1;
        global_path_.push_back(temp_point);
        temp_point.x           = end_point_.x;
        temp_point.y           = end_point_.y;
        temp_point.z           = end_point_.z;
        temp_point.yaw         = end_point_.yaw / M_PI * 180.0;
        temp_point.curvature   = 0;
        temp_point.speed       = 0;
        temp_point.distance    = 0;
        temp_point.attribute   = 0;
        temp_point.speed_limit = 0;
        temp_point.direction   = 1;
        global_path_.push_back(temp_point);
        if ((end_point_.x - start_point_.x) * cos(start_point_.yaw) + (end_point_.y - start_point_.y) * sin(start_point_.yaw) > 0) {
            global_path_.at(0).direction = 0;
            global_path_.at(1).direction = 0;
        }
        else {
            global_path_.at(0).direction = 1;
            global_path_.at(1).direction = 1;
        }

        Helper::CalDistance(global_path_); // 计算路径的位移信息


        return true;
    }
    threadLogger_->info("不是超短距离规划");
    return false;
}
