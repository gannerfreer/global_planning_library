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
    PlanResult result = PlanResult::Plan_OK;
    error_type_       = ErrorType::SUCCESS;
    // 路径规划：作业点参考路径匹配及裁剪拼接
    result = PathPlanning();

    if (result != PlanResult::Plan_OK) {
        threadLogger_->info("PathPlanning 失败");
        cout << "PathPlanning 失败" << endl;
        FillErrorCode(result);
        return;
    }


    threadLogger_->info("PathPlanning 成功");
    cout << "PathPlanning 成功" << endl;

    // 只针对DISPATCH任务进行参考路径拼接
    //  HybirdA*拟合：起点、终点需要拟合则拟合，否则跳过
    if (task_type_ == TaskType::DISPATCH) {
        result = HybirdAStarFitting();
        if (result != PlanResult::Plan_OK) {
            threadLogger_->info("hybridA*算法在处理起点到参考路径拟合的路段失败");
            cout << "hybridA*算法在处理起点到参考路径拟合的路段失败" << endl;
            FillErrorCode(result);
            return;
        }
    }

    // 处理路径点只有2个的情况，这种case无法执行后续的速度规划逻辑，只能在此进行特殊处理
    if (IsShortDistance()) {
        path = global_path_;
        return;
    }

    Helper::RemoveAfterSamePoint(global_path_);

    threadLogger_->info("StartEndPointProcess global_path_.size():{}", global_path_.size());
    // 将起点、终点放入全局路径
    StartEndPointProcess();


    threadLogger_->info("global_path_.size():{}", global_path_.size());
    CurvatureCal(global_path_);
    threadLogger_->info("执行均匀碾压前路径点曲率");
    for (auto i : global_path_) {
        threadLogger_->info("x:{}  y:{}  direction:{}  curvature:{}   yaw:{}", i.x, i.y, i.direction, i.curvature, i.yaw / M_PI * 180);
    }


    // 均匀碾压：对除了过磅、洗车和倒车之外的路段进行横向偏移
    if (vehicle_param_.uniform_compaction_enable == true) {
        threadLogger_->info("开启均匀碾压");
        if (!PathOffset()) {
            error_type_ = ErrorType::ALGORITHM_ERROR_UNIFORM_COMPACTION;
            return;
        }
    }


    // 对进行速度规划前的路径基于梯度下降进行平滑
    std::ofstream file_out;
    file_out.open("total_path_smooth_before.txt");
    for (size_t index = 0; index < global_path_.size(); index++) {
        file_out << global_path_.at(index).x << " " << global_path_.at(index).y << " " << global_path_.at(index).yaw / M_PI * 180 << " " << (int)global_path_.at(index).direction << " " << global_path_.at(index).curvature << endl;
    }
    file_out.close();
    SmoothPath(global_path_);
    // 计算累计s
    Helper::CalDistance(global_path_);
    CurvatureCal(global_path_);
    file_out.open("total_path_smooth_after.txt");
    for (size_t index = 0; index < global_path_.size(); index++) {
        file_out << global_path_.at(index).x << " " << global_path_.at(index).y << " " << global_path_.at(index).yaw / M_PI * 180 << " " << (int)global_path_.at(index).direction << " " << global_path_.at(index).curvature << endl;
    }
    file_out.close();

    threadLogger_->info("执行均匀碾压后路径点曲率");
    for (auto i : global_path_) {
        threadLogger_->info("x:{}  y:{}  direction:{}  curvature:{}   yaw:{}", i.x, i.y, i.direction, i.curvature, i.yaw / M_PI * 180);
    }


    // 角度转换
    Helper::Calrad2deg(global_path_);


    // 速度规划：限速设置、梯形速度规划
    my_speed_planning_.threadLogger_ = threadLogger_;
    my_speed_planning_.SpeedPlanning(global_path_, vehicle_param_);
    threadLogger_->info("梯形速度规划完成");

    Helper::RemoveAfterSamePoint(global_path_);

    // 再次重新计算曲率
    CurvatureCal(global_path_);

    // 路径断裂检查,涉及相邻点间距和相邻点角度差
    if (!Helper::CheckPathFracture(global_path_)) {
        error_type_ = ErrorType::ALGORITHM_ERROR_TRAJECTORY_VERIFY_PATH_BREAK;
        threadLogger_->error("CheckPathFracture fail");
        return;
    }
    threadLogger_->info("轨迹连续性校验通过");

    // 超速检测
    if (!Helper::OverSpeedCheck(global_path_, vehicle_param_.wheel_base)) {
        threadLogger_->error("存在超速，检测失败");
        error_type_ = ErrorType::ALGORITHM_ERROR_TRAJECTORY_VERIFY_SPEED_OVER;
        return;
    }
    threadLogger_->info("超速校验通过");


    // 路径点顺序和direction校验
    if (!Helper::SequenceAndDirectionCheck(global_path_)) {
        threadLogger_->error("路径点顺序或direction校验不通过");
        error_type_ = ErrorType::ALGORITHM_ERROR_TRAJECTORY_VERIFY_DIRECTION_ERROR;
        return;
    }

    // 计算加速度
    Helper::calculateAcceleration(global_path_);
    threadLogger_->info("CalAcc");

    path = global_path_;
    threadLogger_->info("规划成功，即将返回轨迹 final_out global_Path.size():{}", global_path_.size());
    return;
}


// PlanResult Planning::ProgressiveHybirdAStar(_SinglePoint& input_point, int& search_index, vector<_TrajectoryPoint>& result_trajectory, const PlanRule& rule_id) {
//     long long    time_threshold    = 0.8 * 1000 * 1000;
//     int          counter           = 0;
//     bool         success_flag      = false;
//     bool         verification_flag = false;
//     _SinglePoint temp_start, temp_end;
//     int          cal = 0;
//     PlanResult   result;
//     for (int i = 0; i < global_path_.size(); i += 5) {
//         cal++;
//         counter++;
//         temp_end.x   = global_path_.at(i).x;
//         temp_end.y   = global_path_.at(i).y;
//         temp_end.z   = global_path_.at(i).z;
//         temp_end.yaw = global_path_.at(i).yaw;
//         if (rule_id == PlanRule::Forward_All_Time || rule_id == PlanRule::Backward_All_Time) { // 这两种规划规则，可采用dubins预先校验
//             if (rule_id == PlanRule::Forward_All_Time) {
//                 verification_flag = false;
//             }
//             else {
//                 verification_flag = true;
//             }

//             if (PoseVerificationInterface(input_point, temp_end, verification_flag)) { // false表示默认由起点向终点拟合
//                 threadLogger_->info("第 {}个候选点，其索引：{},坐标：({},{},{}), rule_id:{},经过dubins曲线预先校验，合格", cal, i, temp_end.x, temp_end.y, temp_end.yaw / M_PI * 180, static_cast<int>(rule_id));
//                 result = ApplyHibridAStarWithTime(input_point, temp_end, result_trajectory, rule_id, time_threshold);
//                 if (result == PlanResult::Plan_OK) {
//                     search_index = i;
//                     success_flag = true;
//                     break;
//                 }
//             }
//             else {
//                 threadLogger_->info("第 {}个候选点，其索引：{},坐标：({},{},{}), rule_id:{},经过dubins曲线预先校验，不合格", cal, i, temp_end.x, temp_end.y, temp_end.yaw / M_PI * 180, static_cast<int>(rule_id));
//             }
//         } // 这种规划规则，不采用dubins进行预先校验
//         else {
//             threadLogger_->info("第 {}个候选点，其索引：{},坐标：({},{},{}), rule_id:{}", cal, i, temp_end.x, temp_end.y, temp_end.yaw / M_PI * 180, static_cast<int>(rule_id));
//             result = ApplyHibridAStarWithTime(input_point, temp_end, result_trajectory, rule_id, time_threshold);
//             if (result == PlanResult::Plan_OK) {
//                 search_index = i;
//                 success_flag = true;
//                 break;
//             }
//         }

//         if (counter > 18) {
//             threadLogger_->info("最多搜索18个点");
//             return result;
//         }
//     }
//     if (success_flag == true) {
//         threadLogger_->info("ProgressiveHybirdAStar success");
//         return result;
//     }
//     else {
//         return result;
//     }
// }

PlanResult Planning::ApplyHibridAStarWithTime(_SinglePoint s_point, _SinglePoint e_point, vector<_TrajectoryPoint>& traj, const PlanRule& plan_rule_id, long long time_threshold) {
    // 起始点、目标点结构转换
    Point temp_start_point(s_point.x, s_point.y, s_point.z, s_point.yaw, MotionDirection ::Forward);
    Point temp_end_point(e_point.x, e_point.y, e_point.z, e_point.yaw, MotionDirection ::Forward);

    // 搜索获取轨迹
    traj.clear();
    Path       final_path;
    PlanResult result = my_optimal_path_.SearchGlobalPath(temp_start_point, temp_end_point, vehicle_param_, final_path, time_threshold, plan_rule_id);
    if (result == PlanResult::Plan_OK) {
        threadLogger_->info("SearchGlobalPath success");
        _TrajectoryPoint temp_point;
        for (int i = 0; i < final_path.size(); i++) {
            temp_point.Clear();
            temp_point.x         = final_path.at(i).x;
            temp_point.y         = final_path.at(i).y;
            temp_point.z         = final_path.at(i).z;
            temp_point.yaw       = final_path.at(i).angle;
            temp_point.direction = final_path.at(i).direction;
            temp_point.attribute = PointAttribute::dump_road;
            temp_point.curvature = final_path.at(i).curvature;
            traj.emplace_back(temp_point);
        }
        // 绕圈检查，检查原理：判断角度是否产生0~2M_PI的变化
        if (plan_rule_id != PlanRule::Normal_Planning) {
            if (Helper::doesTrajectorySelfIntersect(final_path)) {
                threadLogger_->info("检测到路径绕圈");
                return PlanResult::Plan_Infeasible;
            }
            threadLogger_->info("绕圈检测达标");
            int count = 0;
            for (int i = 0; i < final_path.size() - 1; i++) {
                if (final_path.at(i).direction != final_path.at(i + 1).direction) {
                    count++;
                }
            }
            if (count > 1) {
                threadLogger_->error("路径段数大于2段，不予输出");
                return PlanResult::Plan_Infeasible;
            }
            threadLogger_->info("段数检测达标");
        }
        return PlanResult::Plan_OK;
    }
    else {
        threadLogger_->error(" Failed to plan the path by hibrid A star  ");
        return result;
    }
}


// 成功：true，失败：false
bool Planning::RandomOffsetWithoutCuravture() {
    vector<_TrajectoryPoint> input_points, temp_path, global_path_copy;
    global_path_copy = global_path_;
    random_device rd;
    mt19937       gen(rd());

    // 定义您想要生成的浮点数的集合
    vector<float> weights = {-1.0, 0, 1.0};

    // 使用uniform_int_distribution从集合中随机选择一个索引
    uniform_int_distribution<size_t> dis(0, weights.size() - 1);
    float                            weight = 0.0;


    global_path_.clear();
    temp_path = global_path_copy;
    // 从集合中随机选择一个权重
    weight = weights[dis(gen)];
    threadLogger_->info("weight：{}", weight);
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

    bool  start_need_offset = true; // 判断起步是否需要偏移标志位，默认可以偏移
    float off_set           = 0.0;
    if (reverse_section.size()) {
        if (reverse_section.front().first == 0) {
            // 起步不需要偏移
            start_need_offset = false;
        }
    }
    if (start_need_offset) {
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
                if (end - start > 21) {
                    off_set = CalculateOffSetWithoutCuravture(a, sum + 1, weight); //
                    threadLogger_->info("索引：{}  off_set:{}", m, off_set);
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
    threadLogger_->info("当前权重：{}", weight);
    return true;
}

float Planning::CalculateOffSetWithoutCuravture(int index, int sum, float weight) {
    float L = 0.3 * weight; // 控制默认偏移量
    L       = L * WeightFunction(index, sum);
    return L;
}


float Planning::WeightFunction(int k, int sum) {
    int sita = 5;
    int x;
    if (k < sum / 2) {
        x = k;
    }
    else {
        x = sum - 1 - k;
    }
    return 1.0 / (1 + pow(2.85, (-(x - sita))));
}


// 全局轨迹规划--路径规划
PlanResult Planning::PathPlanning() {
    threadLogger_->info("Enter PathPlanning");
    PlanResult result = PlanResult::Plan_OK;
    time_t     start_time, end_time;
    time(&start_time);
    start_point_.yaw = start_point_.yaw / 180.0 * M_PI;
    end_point_.yaw   = end_point_.yaw / 180.0 * M_PI;
    threadLogger_->info(" task_type_: {}", (int)task_type_);

    if (task_type_ == TaskType::TEMP_MOVE_CAR) {
        // 临时挪车任务直接采用hybridA*规划路径
        threadLogger_->info("挪车");
        result = NotFollowReferencelinePlanning();
        return result;
    }
    else {
        threadLogger_->info("调度、装载、卸载");

        // 在这里判断装载和卸载任务终点是否位于参考路径上
        double temp_end_lat_dis, temp_end_lon_dis     = 0;
        double temp_start_lat_dis, temp_start_lon_dis = 0;
        int    end_path_id   = Helper::GetNearestReferencelines(end_point_, all_referencelines_, temp_end_lat_dis, temp_end_lon_dis);
        int    start_path_id = Helper::GetNearestReferencelines(start_point_, all_referencelines_, temp_start_lat_dis, temp_start_lon_dis);

        if (task_type_ != TaskType::DISPATCH) {
            // 对于 装载体/卸载之类的任务，下述条件满足其一，就直接采用hybridA*算法直接规划
            if (fabs(temp_end_lat_dis) > 1 || fabs(temp_end_lon_dis) > 1 || fabs(temp_start_lat_dis) > 1 || fabs(temp_start_lon_dis) > 1 || end_path_id != start_path_id) {
                threadLogger_->info("此次装卸载任务无参考路径");
                result = NotFollowReferencelinePlanning();
                return result;
            }
        }
        else {
            // 对于常规调度任务，需上来就判断终点是否位于参考路径上
            if (fabs(temp_end_lat_dis) > 0.3 || fabs(temp_end_lon_dis) > 0.3) {
                threadLogger_->info("终点偏离参考路径，采用hybridA*算法直接规划，temp_end_lat_dis:{} temp_end_lon_dis:{}", temp_end_lat_dis, temp_end_lon_dis);
                return PlanResult::EndPoint_Deviation;
            }
            else {
                // 终点位于参考路径上，才可以开启沿参考路径规划策略
                threadLogger_->info("终点位于参考路径上，采用沿参考路径规划策略，temp_end_lat_dis:{} temp_end_lon_dis:{}", temp_end_lat_dis, temp_end_lon_dis);
                result = FollowReferencelinePlanning();
                return result;
            }
        }
    }
}
// 非调度规划任务
PlanResult Planning::NotFollowReferencelinePlanning() {
    my_optimal_path_.threadLogger_ = threadLogger_;

    my_optimal_path_.InitVoronoiAndBound(start_point_, map_border_, inner_borders_, vehicle_param_, false);
    vector<_TrajectoryPoint> temp_traj;
    long long                time_threshold = 2 * 1000 * 1000;
    PlanRule                 rule_id_1 = PlanRule::Forward_All_Time, rule_id_2 = PlanRule::Backward_All_Time, rule_id_3 = PlanRule::Start_Front_End_Back;
    bool                     success_flag = false;
    PlanResult               result;
    if (task_type_ == TaskType::TEMP_MOVE_CAR) { // 临时挪车任务，先采用纯倒车的规划，再采用纯往前开的策略
        // 先倒车规划，不行正向规划
        threadLogger_->info("挪车");

        result = ApplyHibridAStarWithTime(start_point_, end_point_, temp_traj, PlanRule::Normal_Planning, time_threshold);
        if (result != PlanResult::Plan_OK) {
            threadLogger_->error("Hybird A*无法规划出当前起点至终点的路径");
            return result;
        }
        global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.end());
        threadLogger_->info("临时挪车,路长:{}", global_path_.size());
    }
    else if (task_type_ == TaskType::LOAD) { // 装载任务，先纯倒车，纯倒车不行再往前开，再倒车
        threadLogger_->info("装载");
        int load_point_end_offset_distance = vehicle_param_.load_point_end_offset_distance;
        while (load_point_end_offset_distance >= 1) {
            my_optimal_path_.start_offset_distance_ = vehicle_param_.load_start_straight_length;
            my_optimal_path_.end_offset_distance_   = load_point_end_offset_distance;
            threadLogger_->info("当前装载任务，起点直线延长:    {} m", my_optimal_path_.start_offset_distance_);
            threadLogger_->info("当前装载任务，终点直线延长:    {} m", my_optimal_path_.end_offset_distance_);
            result = ApplyHibridAStarWithTime(start_point_, end_point_, temp_traj, PlanRule::Backward_All_Time, time_threshold);
            if (result != PlanResult::Plan_OK) {
                threadLogger_->error("装载任务，PlanRule::Backward_All_Time，装载点直线延伸 {} m，Hybird A*无法规划出当前起点至终点的路径", load_point_end_offset_distance);
            }
            else {
                global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.end());
                threadLogger_->info("装载,路长:{}", global_path_.size());
                success_flag = true;
                break;
            }
            load_point_end_offset_distance--;
        }
        if (success_flag == false) {
            threadLogger_->info("更换规则，采用Start_Front_End_Back规划方式");
            my_optimal_path_.start_offset_distance_ = 3;
            my_optimal_path_.end_offset_distance_   = vehicle_param_.load_point_end_offset_distance;
            result                                  = ApplyHibridAStarWithTime(start_point_, end_point_, temp_traj, PlanRule::Start_Front_End_Back, time_threshold);
            if (result != PlanResult::Plan_OK) {
                threadLogger_->error("装载任务，PlanRule::Start_Front_End_Back规则，装载点直线延伸 {} m，Hybird A*无法规划出当前起点至终点的路径", vehicle_param_.load_point_end_offset_distance);
            }
            else {
                global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.end());
                threadLogger_->info("装载,路长:{}", global_path_.size());
                success_flag = true;
            }
            if (success_flag == false) {
                if (result == PlanResult::EndPoint_Collision) return result;
                if (result == PlanResult::Plan_Infeasible) return PlanResult::Load_Queue_Point_Unreasonable;
            }
        }
    }
    else { // 卸载任务，先前进，后倒退进入卸载点
        threadLogger_->info("卸载");
        int unload_point_end_offset_distance = vehicle_param_.load_point_end_offset_distance;
        while (unload_point_end_offset_distance >= 1) {
            my_optimal_path_.start_offset_distance_ = 3;
            my_optimal_path_.end_offset_distance_   = unload_point_end_offset_distance;
            threadLogger_->info("终点直线延长:    {} m", my_optimal_path_.end_offset_distance_);
            result = ApplyHibridAStarWithTime(start_point_, end_point_, temp_traj, PlanRule::Start_Front_End_Back, time_threshold);
            if (result != PlanResult::Plan_OK) {
                threadLogger_->error("卸载任务，PlanRule::Start_Front_End_Back，卸载点直线延伸 {} m，Hybird A*无法规划出当前起点至终点的路径", unload_point_end_offset_distance);
            }
            else {
                global_path_.insert(global_path_.end(), temp_traj.begin(), temp_traj.end());
                threadLogger_->info("卸载,路长:{}", global_path_.size());
                success_flag = true;
                break;
            }
            unload_point_end_offset_distance--;
        }
        if (success_flag == false) {
            return PlanResult::Unload_Queue_Point_Unreasonable;
        }
    }

    my_optimal_path_.DeleteVoronoiSpace(false);
    return result;
}


// 沿路网路径规划
PlanResult Planning::FollowReferencelinePlanning() {
    // 搜索策略，终点只搜索0.2m范围内的参考路径，起点采用渐进式扩大搜索策略，从0.5m初始搜索半径开始
    vector<pair<int, int>> success_pair;
    v_has_calculate_pair_.clear();
    bool        is_found          = false; // 用于跟踪是否找到了成功的路径对
    double      end_search_radius = 0.3, start_search_radius = 0.5;
    vector<int> start_path_vec, end_path_vec;
    cout << "开始进入起点、终点搜索环节" << endl;
    cout << "end_search_radius:" << end_search_radius << endl;

    Helper::GetReferencelinesWithRadiusAndAngle(end_point_, all_referencelines_, end_search_radius, end_path_vec);
    threadLogger_->info("终点搜索半径：{},搜索到路径数量:{}", end_search_radius, end_path_vec.size());
    cout << "终点搜索半径:" << end_search_radius << "  搜索到路径数量:  " << end_path_vec.size() << endl;
    threadLogger_->info("搜索到的路径ID信息如下");
    cout << "搜索到的路径ID信息如下:" << endl;
    for (auto i : end_path_vec) {
        threadLogger_->info(i);
        cout << i << " ";
    }
    cout << endl;

    start_search_radius = 0.5;
    // 起点采用渐进式扩大搜索策略，从0.5m初始搜索半径开始,一直搜索到100m结束，将搜索到的所有联通路径pair存进success_pair
    while (start_search_radius <= 100) {
        if (Helper::GetReferencelinesWithRadius(start_point_, all_referencelines_, start_search_radius, start_path_vec)) {
            threadLogger_->info("起点搜索半径：{},搜索到路径数量:{}", start_search_radius, start_path_vec.size());
            threadLogger_->info("搜索到的路径ID信息如下");
            cout << "起点搜索半径：:" << start_search_radius << "  搜索到路径数量:  " << start_path_vec.size() << endl;
            cout << "搜索到的路径ID信息如下:" << endl;
            for (auto i : start_path_vec) {
                threadLogger_->info(i);
                cout << i << " ";
            }
            cout << endl;

            vector<int> start_path_vec_switch, end_path_vec_switch;
            for (auto i : start_path_vec) {
                start_path_vec_switch.push_back(GlobalVariable::getInstance()->BinarySearch(sequence_mapping_, i));
            }
            for (auto i : end_path_vec) {
                end_path_vec_switch.push_back(GlobalVariable::getInstance()->BinarySearch(sequence_mapping_, i));
            }

            // 在start_path_vec_switch和end_path_vec_switch中查找连通路径
            for (auto start : start_path_vec_switch) {
                for (auto end : end_path_vec_switch) {
                    if (HasSearched(start, end)) {
                        // threadLogger_->info("路径{}->路径{}已经计算过，为节约计算资源，予以跳过", start.first, end);
                        continue;
                    }
                    threadLogger_->info("索引  start:{},end:{}", start, end);
                    if (IsConnect(start, end)) {
                        threadLogger_->info("路径{}与路径{}联通", sequence_mapping_.at(start), sequence_mapping_.at(end));
                        cout << "路径 " << sequence_mapping_.at(start) << " 与路径 " << sequence_mapping_.at(end) << " 联通" << endl;
                        success_pair.push_back(make_pair(start, end));
                    }
                    else {
                        threadLogger_->info("start:{},end:{}", start, end);
                        threadLogger_->info("路径{}与路径{}不联通", sequence_mapping_.at(start), sequence_mapping_.at(end));
                        cout << "路径 " << sequence_mapping_.at(start) << " 与路径 " << sequence_mapping_.at(end) << " 不联通" << endl;
                    }
                    v_has_calculate_pair_.push_back(pair(start, end));
                }
            }
        }
        else {
            threadLogger_->info("起点搜索半径{},无参考路径", start_search_radius);
            cout << "起点搜索半径" << start_search_radius << "无参考路径 " << endl;
        }
        start_search_radius += 0.5;
    }

    if (success_pair.empty()) {
        return PlanResult::Map_Infeasible;
    }
    else {
        threadLogger_->info("规划算法找到的成功路径对id如下：");
        cout << "规划算法找到的成功路径对id如下：" << endl;
        for (int i = 0; i < success_pair.size(); i++) {
            threadLogger_->info("{},{}", sequence_mapping_.at(success_pair.at(i).first), sequence_mapping_.at(success_pair.at(i).second));
            cout << sequence_mapping_.at(success_pair.at(i).first) << "  " << sequence_mapping_.at(success_pair.at(i).second) << endl;
        }
    }

    threadLogger_->info("从中挑选最优秀的一对");
    cout << "从中挑选最优秀的一对" << endl;
    // 从success_pair中挑选最优的路径对
    int                               min = INT_MAX;
    pair<int, int>                    best_pair;
    vector<pair<pair<int, int>, int>> record;
    for (int i = 0; i < success_pair.size(); i++) {
        record.push_back(pair<pair<int, int>, int>(success_pair.at(i), 0));
    }
    threadLogger_->info("初始化recrod完毕");
    cout << "初始化recrod完毕" << endl;
    float       cost1, cost2, cost3 = 0;
    _SingleTraj temp_start_traj, temp_end_traj;
    int         temp_start_key, temp_end_key;
    int         temp_start_index, temp_end_index;
    double      temp_start_lat_dis, temp_start_lon_dis, temp_start_distance, temp_start_angle_diff = 0;
    double      temp_end_lat_dis, temp_end_lon_dis, temp_end_distance, temp_end_angle_diff         = 0;

    for (auto& i : record) {
        temp_start_key = sequence_mapping_.at(i.first.first);
        temp_end_key   = sequence_mapping_.at(i.first.second);

        temp_start_traj = all_referencelines_.at(temp_start_key);
        temp_end_traj   = all_referencelines_.at(temp_end_key);
        Helper::CalNearestIndex(start_point_, temp_start_traj, temp_start_index, temp_start_lat_dis, temp_start_lon_dis, temp_start_distance, temp_start_angle_diff);
        Helper::CalNearestIndex(end_point_, temp_end_traj, temp_end_index, temp_end_lat_dis, temp_end_lon_dis, temp_end_distance, temp_end_angle_diff);
        if (temp_start_angle_diff > M_PI / 2) {
            cost1 = 200;
        }
        else {
            cost1 = 0;
        }
        cost2    = temp_start_distance * 10;
        cost3    = ReferencelineTotalDis(i.first, temp_start_index, temp_end_index);
        i.second = cost1 + cost2 + cost3;
        threadLogger_->info("路径对 {}--{}  cost1: {}  cost2: {}  cost3: {}  total_cost:{}", sequence_mapping_.at(i.first.first), sequence_mapping_.at(i.first.second), cost1, cost2, cost3, cost1 + cost2 + cost3);
        cout << "路径对" << sequence_mapping_.at(i.first.first) << "--" << sequence_mapping_.at(i.first.second) << "  cost1:" << cost1 << " cost2:" << cost2 << " cost3:" << cost3 << endl;
    }
    threadLogger_->info("计算代价完毕");
    cout << "计算代价完毕" << endl;
    float min_cost  = FLT_MAX;
    int   min_index = -1;
    for (int i = 0; i < record.size(); i++) {
        if (record.at(i).second < min_cost) {
            min_cost  = record.at(i).second;
            min_index = i;
        }
    }
    threadLogger_->info("min_index:{}", min_index);
    cout << "min_index:" << min_index << endl;
    best_pair.first  = record.at(min_index).first.first;
    best_pair.second = record.at(min_index).first.second;
    threadLogger_->info("找到的最优路径对：{} --{}", best_pair.first, best_pair.second);
    cout << "找到的最优路径对 " << best_pair.first << "  " << best_pair.second << endl;

    dijkstra_.searchpath(best_pair.first, best_pair.second);
    road_sequence_ = dijkstra_.GetPath();


    threadLogger_->info("找到路径对{}-{}", sequence_mapping_.at(best_pair.first), sequence_mapping_.at(best_pair.second));
    cout << "找到路径对" << sequence_mapping_.at(best_pair.first) << "   " << sequence_mapping_.at(best_pair.second) << endl;
    // 找到起点、终点对应的索引及其横纵向距离


    start_key_      = sequence_mapping_.at(best_pair.first);
    end_key_        = sequence_mapping_.at(best_pair.second);
    temp_start_traj = all_referencelines_.at(start_key_);
    temp_end_traj   = all_referencelines_.at(end_key_);
    Helper::CalNearestIndex(start_point_, temp_start_traj, start_index_, start_lat_dis_, start_lon_dis_, start_distance_, start_angle_diff_);
    Helper::CalNearestIndex(end_point_, temp_end_traj, end_index_, end_lat_dis_, end_lon_dis_, end_distance_, end_angle_diff_);
    threadLogger_->info("起点匹配上的路径索引{}，横向距离{}，纵向距离{}, 角度误差{}", start_index_, start_lat_dis_, start_lon_dis_, start_angle_diff_ / M_PI * 180.0);
    threadLogger_->info("终点匹配上的路径索引{}，横向距离{}，纵向距离{}, 角度误差{}", end_index_, end_lat_dis_, end_lon_dis_, end_angle_diff_ / M_PI * 180.0);
    cout << "起点匹配上的路径索引" << start_index_ << " 横向距离" << start_lat_dis_ << " 纵向距离" << start_lon_dis_ << " 角度误差" << start_angle_diff_ / M_PI * 180.0 << endl;
    cout << "终点匹配上的路径索引" << end_index_ << " 横向距离" << end_lat_dis_ << "  纵向距离" << end_lon_dis_ << " 角度误差" << end_angle_diff_ / M_PI * 180.0 << endl;


    // 路径裁剪拼接
    PathClipAndSplice();
    return PlanResult::Plan_OK;
}
bool Planning::HasSearched(int start, int end) {
    for (auto pair : v_has_calculate_pair_) {
        if (pair.first == start && pair.second == end) {
            return true;
        }
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


    // 将终点添加到全局路径中
    // 判断终点与全局路径最后一个点的角度偏差，基于角度偏差信息来判断是否 将其抛弃
    float end_point_last_point_angle_diff;
    end_point_last_point_angle_diff = atan2(end_point_.y - global_path_.back().y, end_point_.x - global_path_.back().x);
    if (end_point_last_point_angle_diff < 0) {
        end_point_last_point_angle_diff += 2 * M_PI; // 将终点与全局路径最后一个点的角度偏差规范[0,2π）
    }
    threadLogger_->info("路径最后一个点与终点的角度:{}", end_point_last_point_angle_diff / M_PI * 180.0);
    float last_angle_diff = fabs(end_point_last_point_angle_diff - global_path_.back().yaw) * 180.0 / M_PI >= 180 ? 360 - fabs(end_point_last_point_angle_diff - global_path_.back().yaw) * 180 / M_PI : fabs(end_point_last_point_angle_diff - global_path_.back().yaw) * 180 / M_PI;
    threadLogger_->info("路径最后一个点direction：{}，角度差：{}", global_path_.back().direction, last_angle_diff);
    if ((last_angle_diff > 90 && global_path_.back().direction == 0) || (fabs(end_point_.x - global_path_.back().x) <= 0.3 && fabs(end_point_.y - global_path_.back().y) <= 0.3) || (last_angle_diff < 90 && global_path_.back().direction == 1)) {
        threadLogger_->info("将路径最后一个点剔除");
        global_path_.pop_back();
    }
    else {
        threadLogger_->info("路径最后一个点无需剔除");
    }
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
    last_point.attribute = global_path_.back().attribute;
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
        if (global_path_.at(i).attribute == PointAttribute::weight_point || global_path_.at(i).attribute == PointAttribute::clean_point) {
            for (int j = i - 10; j < i + 10; j++) {
                if (j >= 0 && j < global_path_.size()) {
                    global_path_.at(j).offset_flag = false; // 将过磅点和洗车点左右10m设置为无需偏移的路段
                }
            }
        }
        if (global_path_.at(i).direction == 1) {
            global_path_.at(i).offset_flag = false; // 将倒车的路段offset_flag也设置为false,即不需要进行偏移
        }

        // 曲率超标的部分也不偏移
        // if (fabs(global_path_.at(i).curvature) > 0.01) {
        //     global_path_.at(i).offset_flag = false;
        // }
    }

    if (!RandomOffsetWithoutCuravture()) // 不基于曲率的轨迹偏移
    {
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
            threadLogger_->info("短距离倒车");
            global_path_.insert(global_path_.end(), all_referencelines_.at(temp_key).trajectory.begin() + end_index_, all_referencelines_.at(temp_key).trajectory.begin() + start_index_ + 1);
            reverse(global_path_.begin(), global_path_.end());
            for (auto& point : global_path_) {
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
PlanResult Planning::HybirdAStarFitting() {
    //  初始化HybrdiA*算法地图边界及voronoi图
    PlanResult result              = PlanResult::Plan_OK;
    my_optimal_path_.threadLogger_ = threadLogger_;
    my_optimal_path_.InitVoronoiAndBound(start_point_, map_border_, inner_borders_, vehicle_param_, false);
    // 基于横纵向距离来判断是否进行hybirdA*拟合
    threadLogger_->info("Enter HybirdAStarFitting");
    double lat_threshold = 0.3, lon_threshold = 0.8;
    bool   start_need_fitting     = false;
    bool   load_unload_start_flag = false; // 此标志位为true时，表明是从装载点\卸载点出来的调度任务
    bool   success_flag           = false;
    double lon_dis                = 0;
    // 这里的逻辑主要是区分global_path位于start_point_前方还是后方，如果是前方，配合start_lat_dis_和start_lon_dis_来判断是常规调度还是装载点调度
    if (global_path_.size() > 1) {
        lon_dis = (start_point_.x - global_path_.at(1).x) * cos(global_path_.at(1).yaw) + (start_point_.y - global_path_.at(1).y) * sin(global_path_.at(1).yaw);
    }
    else {
        lon_dis = (start_point_.x - global_path_.front().x) * cos(global_path_.front().yaw) + (start_point_.y - global_path_.front().y) * sin(global_path_.front().yaw);
    }
    threadLogger_->info("起点与参考路径第一个点的纵向距离:{}", lon_dis);
    if (start_lat_dis_ > lat_threshold || fabs(start_lon_dis_) > lon_threshold || start_angle_diff_ > 8.0 / 180.0 * M_PI) { // 横向阈值大于0.7m,或者纵向阈值大于3m,就需要进行hybirdA*拟合
        start_need_fitting = true;
        if ((start_lat_dis_ > 10 || fabs(start_lon_dis_) > 10) && lon_dis < eps) {
            // 说明这是个从卸载点（无参考路径情况下）或从装载点出发的任务，由于可能有乱石堆的存在，这种直线延伸距离需要额外自行配置
            load_unload_start_flag = true;
        }
    }


    // 只看起点
    if (start_need_fitting) // 起点需要进行HybirdA*拟合
    {
        // 下面需要将从装载点调度起步和常规调度起步区分开，是为了能够区分异常类型，便于给后台反馈到底是驶离装载点不合理，还是任务起点不合理，不然就合并代码统一处理了，没必要写的这么冗余
        if (load_unload_start_flag) {
            int start_point_offset_distance = vehicle_param_.load_point_start_offset_distance;
            while (start_point_offset_distance >= 1) {
                my_optimal_path_.start_offset_distance_ = start_point_offset_distance;
                my_optimal_path_.end_offset_distance_   = 1;
                threadLogger_->info("识别出从装载点或卸载点出发，当前起点直线距离 {}，这种情况下此采用Forward_Fitting规则 ", start_point_offset_distance);
                cout << "识别出从装载点或卸载点出发，当前起点直线距离" << start_point_offset_distance << " 这种情况下此采用Forward_Fitting规则" << endl;
                vector<_TrajectoryPoint> temp_traj;
                int                      search_index = std::numeric_limits<int>::max();
                // 需要先找到global_path_中排队点、过磅、洗车点的具体索引，hybrida*做路径拟合不能越过这些点
                for (int i = 0; i < global_path_.size(); i++) {
                    if (global_path_.at(i).attribute == PointAttribute::queue_point || global_path_.at(i).attribute == PointAttribute::weight_point || global_path_.at(i).attribute == PointAttribute::clean_point) {
                        threadLogger_->info("找到排队点、过磅、洗车点，索引为{}", i);
                        search_index = i;
                        break;
                    }
                }
                search_index = std::min(search_index, std::min((int)global_path_.size() - 1, 100));
                result       = FindBestTrajectory(start_point_, search_index, temp_traj, PlanRule::Forward_All_Time);
                // result                                = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Forward_All_Time);
                if (result != PlanResult::Plan_OK) {
                    threadLogger_->error("从装载点/卸载点调度出去，起点直线距离 {}  ,起点hybirdA*拟合失败,拟合规则为Forward_Fitting", my_optimal_path_.start_offset_distance_);
                }
                else {
                    global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
                    global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
                    success_flag = true;
                    break;
                }
                start_point_offset_distance--;
            }
            if (success_flag == false) {
                return PlanResult::Leaving_Load_Point_Too_Close;
            }
        }
        else {
            threadLogger_->info("常规调度任务，起点需要HybirdA*拟合");
            cout << "常规调度任务，起点需要HybirdA*拟合" << endl;
            my_optimal_path_.start_offset_distance_ = 3;
            my_optimal_path_.end_offset_distance_   = 1;
            vector<_TrajectoryPoint> temp_traj;
            int                      search_index = std::numeric_limits<int>::max();
            // 需要先找到global_path_中排队点、过磅、洗车点的具体索引，hybrida*做路径拟合不能越过这些点
            for (int i = 0; i < global_path_.size(); i++) {
                if (global_path_.at(i).attribute == PointAttribute::queue_point || global_path_.at(i).attribute == PointAttribute::weight_point || global_path_.at(i).attribute == PointAttribute::clean_point) {
                    threadLogger_->info("找到排队点、过磅、洗车点，索引为{}", i);
                    search_index = i;
                    break;
                }
            }
            search_index = std::min(search_index, std::min((int)global_path_.size() - 1, 100));
            if (JudgeFittingDirection()) {
                threadLogger_->info("参考路径位于车头前方,或可以向前掉头开往对向参考路径，这种情况下采用 Forward_All_Time 规则进行规划");
                result = FindBestTrajectory(start_point_, search_index, temp_traj, PlanRule::Forward_All_Time);
                // result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Forward_All_Time);
                if (result != PlanResult::Plan_OK) {
                    threadLogger_->error("常规调度任务，起点hybirdA*采用Forward_All_Time拟合失败，即将调整拟合规则为 Start_Back_End_Front");
                    result = FindBestTrajectory(start_point_, search_index, temp_traj, PlanRule::Start_Back_End_Front);
                    // result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Start_Back_End_Front);
                    if (result != PlanResult::Plan_OK) {
                        threadLogger_->error("常规调度任务，起点hybirdA*采用 Start_Back_End_Front 依旧拟合失败");
                        return result;
                    }
                }
            }
            else {
                threadLogger_->info("参考路径位于车头后方，这种情况下采用Back_Fitting规则进行规划");
                result = FindBestTrajectory(start_point_, search_index, temp_traj, PlanRule::Backward_All_Time);

                // result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Backward_All_Time);
                if (result != PlanResult::Plan_OK) {
                    threadLogger_->error("常规调度任务，起点hybirdA*采用 Backward_All_Time 拟合失败，即将调整拟合规则为 Start_Front_End_Back");
                    result = FindBestTrajectory(start_point_, search_index, temp_traj, PlanRule::Start_Front_End_Back);
                    // result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Start_Front_End_Back);
                    if (result != PlanResult::Plan_OK) {
                        threadLogger_->error("常规调度任务，起点hybirdA*采用 Start_Front_End_Back 依旧拟合失败");
                        return result;
                    }
                }
            }
            global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
            global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
        }
    }

    my_optimal_path_.DeleteVoronoiSpace(false);
    threadLogger_->info("HybirdAStarFitting结束");
    return result;
}
bool Planning::JudgeFittingDirection() {
    if (10 < global_path_.size()) {
        double lon_dis = (start_point_.x - global_path_.at(10).x) * cos(global_path_.at(10).yaw) + (start_point_.y - global_path_.at(10).y) * sin(global_path_.at(10).yaw);
        if (lon_dis <= 0) {
            threadLogger_->info("正向起步");
            return true;
        }
        else {
            threadLogger_->info("倒车起步 point:({},{})  global_path_.at( 10):({},{},{})  lon_dis:{}", start_point_.x, start_point_.y, global_path_.at(10).x, global_path_.at(10).y, global_path_.at(10).yaw / M_PI * 180.0, lon_dis);
            return false;
        }
    }
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
        temp_point.attribute   = PointAttribute::regular_road;
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
        temp_point.attribute   = PointAttribute::regular_road;
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

bool Planning::PoseVerificationInterface(const _SinglePoint& start_pose, const _SinglePoint& end_pose, const bool flag, std::vector<curve::Point>& output_path) {
    threadLogger_->info("PoseVerificationInterface--start_pose:{},{},{}     end_pose:{} ,{},{}", start_pose.x, start_pose.y, start_pose.yaw, end_pose.x, end_pose.y, end_pose.yaw);
    curve::Point dubins_start, dubins_end;
    if (flag == 0) {
        auto x = start_pose.x + 3.0 * std::cos(start_pose.yaw);
        auto y = start_pose.y + 3.0 * std::sin(start_pose.yaw);
        dubins_start.SetX(x);
        dubins_start.SetY(y);
        dubins_start.SetAngle(start_pose.yaw / M_PI * 180.0);
        x = end_pose.x - 1.0 * std::cos(end_pose.yaw);
        y = end_pose.y - 1.0 * std::sin(end_pose.yaw);
        dubins_end.SetX(x);
        dubins_end.SetY(y);
        dubins_end.SetAngle(end_pose.yaw / M_PI * 180.0);
    }
    else if (flag == 1) {
        auto x = end_pose.x + 1.0 * std::cos(end_pose.yaw);
        auto y = end_pose.y + 1.0 * std::sin(end_pose.yaw);
        dubins_start.SetX(x);
        dubins_start.SetY(y);
        dubins_start.SetAngle(end_pose.yaw / M_PI * 180.0);
        x = start_pose.x - 3.0 * std::cos(start_pose.yaw);
        y = start_pose.y - 3.0 * std::sin(start_pose.yaw);
        dubins_end.SetX(x);
        dubins_end.SetY(y);
        dubins_end.SetAngle(start_pose.yaw / M_PI * 180.0);
    }
    else {
        std::cout << "入参有误！！！" << std::endl;
        return false;
    }
    curve::Dubins dubis;
    dubis.SetRadius(vehicle_param_.radious);
    threadLogger_->info("dubins radius:{}", dubis.GetRadius());
    output_path.clear();
    bool result = dubis.GetDubinsPath(dubins_start, dubins_end, output_path);
    if (!result) {
        threadLogger_->error("Dubins路径规划失败");
        return false;
    }
    // 将起点和终点的直线延长的点也加入到output_path中，其中，起点部分延长3m，终点部分延长1m，对flag==0和flag==1分别进行处理
    if (flag == 0) {
        // 起点部分延长3m,加入到output_path的前端，终点部分延长1m,加入到output_path的后端
        curve::Point temp_point;
        for (int i = 0; i < 3; i++) {
            temp_point.SetX(start_pose.x + i * std::cos(start_pose.yaw));
            temp_point.SetY(start_pose.y + i * std::sin(start_pose.yaw));
            temp_point.SetAngle(start_pose.yaw);
            output_path.insert(output_path.begin(), temp_point);
        }

        temp_point.SetX(end_pose.x);
        temp_point.SetY(end_pose.y);
        temp_point.SetAngle(end_pose.yaw);
        output_path.push_back(temp_point);


        return true;
    }
    else {
        // 终点部分延长1m,加入到output_path的前端，起点部分延长3m,加入到output_path的后端
        curve::Point temp_point;

        temp_point.SetX(end_pose.x);
        temp_point.SetY(end_pose.y);
        temp_point.SetAngle(end_pose.yaw);
        output_path.insert(output_path.begin(), temp_point);

        for (int i = 2; i >= 0; i--) {
            temp_point.SetX(start_pose.x - i * std::cos(start_pose.yaw));
            temp_point.SetY(start_pose.y - i * std::sin(start_pose.yaw));
            temp_point.SetAngle(start_pose.yaw);
            output_path.push_back(temp_point);
        }
        // 对output_path倒序
        std::reverse(output_path.begin(), output_path.end());
        return true;
    }
}
float Planning::ReferencelineTotalDis(pair<int, int>& input_pair, int start_index, int end_index) {
    // threadLogger_->info("计算{}到{}之间的路径", sequence_mapping_.at(input_pair.first), sequence_mapping_.at(input_pair.second));
    dijkstra_.searchpath(input_pair.first, input_pair.second);
    road_sequence_   = dijkstra_.GetPath();
    int total_length = 0;
    if (road_sequence_.size() > 1) {
        for (int i = 0; i < road_sequence_.size(); i++) {
            int temp_key = sequence_mapping_.at(road_sequence_.at(i));
            if (i == 0) {
                total_length += all_referencelines_.at(temp_key).trajectory.size() - start_index;
                // threadLogger_->info("i:{}  total_length:{} all_referencelines_.at(temp_key).trajectory.size():{} start_index:{}", i, total_length, all_referencelines_.at(temp_key).trajectory.size(), start_index);
            }
            else if (i == road_sequence_.size() - 1) {
                total_length += end_index;
                // threadLogger_->info("i:{}  total_length:{} end_index:{}", i, total_length, end_index);
            }
            else {
                total_length += all_referencelines_.at(temp_key).trajectory.size();
                // threadLogger_->info("i:{}  total_length:{} all_referencelines_.at(temp_key).trajectory.size():{}", i, total_length, all_referencelines_.at(temp_key).trajectory.size());
            }
        }
        return total_length;
    }
    else {
        if (start_index > end_index) { // 不允许倒车
            return 100000;
        }
        else {
            return end_index - start_index;
        }
    }
}

void Planning::CalculateCubicSplineCurve(bool flag, const Path& points, Path& cubicspline_path) {
    vector<double> x_set;
    vector<double> y_set;
    x_set.reserve(points.size());
    y_set.reserve(points.size());
    for (const auto& pt : points) {
        x_set.push_back(pt.x);
        y_set.push_back(pt.y);
    }

    CalculateStation(x_set, y_set);
    sx_.set_points(s_, x_set);
    sy_.set_points(s_, y_set);
    kDeltaS = 1;

    float  epsilon = 0.0001; // 容差值
    double s       = 0.0;
    for (s = 0.0; s <= s_.back(); s += kDeltaS) {
        kDeltaS   = 1;
        double dx = sx_.deriv(1, s);
        double dy = sy_.deriv(1, s);

        double ddx = sx_.deriv(2, s);
        double ddy = sy_.deriv(2, s);

        // float angle = atan(dy / dx);
        // if (dx < 0)
        //     angle = angle + M_PI;
        // else if (dx >= 0 && dy < 0)
        //     angle = angle + 2 * M_PI;
        float angle = atan2(dy, dx);
        if (angle < 0) {
            angle += 2 * M_PI;
        }
        double cur = (ddy * dx - ddx * dy) / pow(dx * dx + dy * dy, 3.0 / 2);
        Point  temp_point;
        temp_point.x         = sx_(s);
        temp_point.y         = sy_(s);
        temp_point.angle     = angle;
        temp_point.curvature = cur;
        if (flag == true)
            temp_point.direction = MotionDirection::Forward;
        else
            temp_point.direction = MotionDirection::Backward;
        cubicspline_path.emplace_back(temp_point);
    }
    s        = s_.back();
    float dx = sx_.deriv(1, s);
    float dy = sy_.deriv(1, s);

    float ddx   = sx_.deriv(2, s);
    float ddy   = sy_.deriv(2, s);
    float angle = atan2(dy, dx);
    if (angle < 0) {
        angle += 2 * M_PI;
    }
    float cur = (ddy * dx - ddx * dy) / pow(dx * dx + dy * dy, 3.0 / 2);
    Point temp_point;
    temp_point.x         = sx_(s);
    temp_point.y         = sy_(s);
    temp_point.angle     = angle;
    temp_point.curvature = cur;
    if (flag == true)
        temp_point.direction = MotionDirection::Forward;
    else
        temp_point.direction = MotionDirection::Backward;
    cubicspline_path.emplace_back(temp_point);

    if (flag == false) {
        for (auto& i : cubicspline_path) {
            i.angle += M_PI;
            if (i.angle > 2 * M_PI) i.angle -= 2 * M_PI;
        }
    }
}
void Planning::CalculateStation(const vector<double>& xs, const vector<double>& ys) {
    double cum = 0.0;
    s_.clear();
    s_.push_back(cum);

    for (unsigned int i = 1; i < xs.size(); i++) {
        double dx = xs.at(i) - xs.at(i - 1);
        double dy = ys.at(i) - ys.at(i - 1);
        cum += hypot(dx, dy);
        s_.push_back(cum);
    }
}


void Planning::CurvatureCal(vector<_TrajectoryPoint>& input_path) {
    _TrajectoryPoint p1, p2, p3;
    double           crossProduct = 0;
    // 计算三角形外接圆的半径
    if (input_path.size() > 2) {
        for (int i = 1; i < input_path.size() - 1; i++) {
            if (input_path.at(i).direction == input_path.at(i + 1).direction) {
                p1           = input_path.at(i - 1);
                p2           = input_path.at(i);
                p3           = input_path.at(i + 1);
                crossProduct = (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x);
                double a     = hypot(p2.x - p3.x, p2.y - p3.y);
                double b     = hypot(p1.x - p3.x, p1.y - p3.y);
                double c     = hypot(p1.x - p2.x, p1.y - p2.y);
                double s     = (a + b + c) / 2.0;
                double area  = std::sqrt(fabs(s * (s - a) * (s - b) * (s - c)));
                double r     = (a * b * c) / (4.0 * area);
                if (r == 0 || area == 0) {
                    input_path.at(i).curvature = 0;
                }
                else {
                    input_path.at(i).curvature = 1.0 / r;
                }
            }
            else {
                if (i - 1 > 0) {
                    input_path.at(i).curvature = input_path.at(i - 1).curvature;
                }
                else {
                    input_path.at(i).curvature = 0;
                }
            }
            if (crossProduct < 0) {
                if (input_path.at(i).curvature > 0) {
                    input_path.at(i).curvature *= -1;
                }
            }
        }
        input_path.front().curvature = input_path.at(1).curvature;
        input_path.back().curvature  = input_path.at(input_path.size() - 2).curvature;
    }
}
void Planning::SmoothPath(vector<_TrajectoryPoint>& input_path) {
    // 得到节点和固定点索引
    unordered_set<unsigned int> cusp_set, fixpoint_set;
    for (unsigned int i = 1; i < input_path.size(); ++i) {
        if (input_path.at(i).direction != input_path.at(i - 1).direction) {
            cusp_set.insert(i - 1);
        }
    }
    for (auto it = cusp_set.begin(); it != cusp_set.end(); ++it) {
        fixpoint_set.insert(*it - 1);
        fixpoint_set.insert(*it);
        fixpoint_set.insert(*it + 1);
    }
    fixpoint_set.insert(0);
    fixpoint_set.insert(1);
    fixpoint_set.insert(input_path.size() - 1);
    fixpoint_set.insert(input_path.size() - 2);


    unsigned int max_opti_num = 50;

    int            L     = input_path.size();
    double         x_sat = 6;
    vector<double> coeff;
    for (int i = 0; i < L; i++) {
        double x    = (i < L / 2) ? i : (L - 1.0 - i);
        double temp = 1 / (1 + exp(-x + x_sat));
        coeff.push_back(temp);
    }

    unsigned int iterations = 0;
    double       a1, a2, b1, b2, c1, c2, d1, d2, e1, e2;


    // 梯度下降法迭代优化
    while (iterations++ < max_opti_num) {
        for (unsigned int i = 2; i < input_path.size() - 2; i++) {
            if (fixpoint_set.count(i)) {
                continue;
            }
            // 优化路径的当前点前两点、当前点、当前点后两点及原路径当前点
            a1 = input_path.at(i - 2).x;
            a2 = input_path.at(i - 2).y;
            b1 = input_path.at(i - 1).x;
            b2 = input_path.at(i - 1).y;
            c1 = input_path.at(i).x;
            c2 = input_path.at(i).y;
            d1 = input_path.at(i + 1).x;
            d2 = input_path.at(i + 1).y;
            e1 = input_path.at(i + 2).x;
            e2 = input_path.at(i + 2).y;

            input_path.at(i).x -= coeff.at(i) * 0.1 * (e1 - 4 * d1 + 6 * c1 - 4 * b1 + a1);
            input_path.at(i).y -= coeff.at(i) * 0.1 * (e2 - 4 * d2 + 6 * c2 - 4 * b2 + a2);
        }
    }

    for (unsigned int i = 1; i < input_path.size() - 1; i++) {
        if (cusp_set.count(i)) {
            continue;
        }
        double dx    = (input_path.at(i + 1).x - input_path.at(i - 1).x);
        double dy    = (input_path.at(i + 1).y - input_path.at(i - 1).y);
        double angle = atan(dy / dx);
        if (dx < 0)
            angle = angle + M_PI;
        else if (dx >= 0 && dy < 0)
            angle = angle + 2 * M_PI;
        else
            ;
        if (input_path.at(i).direction == MotionDirection::Backward) // 表示后退
        {
            input_path.at(i).yaw = Helper::NormalizeAngleRad(angle + M_PI);
        }
        else {
            input_path.at(i).yaw = Helper::NormalizeAngleRad(angle);
        }
    }
}

void Planning::FillErrorCode(PlanResult result) {
    threadLogger_->info("FillErrorCode  result:{}", static_cast<int>(result));


    switch (result) {
        case PlanResult::Plan_Infeasible:
            error_type_ = ErrorType::Plan_Infeasible;
            break; // 可选的
        case PlanResult::Plan_Overtime:
            error_type_ = ErrorType::UnReasonable_Task;
            break; // 可选的
        case PlanResult::StartPoint_Collision:
            error_type_ = ErrorType::StartPoint_Collision;
            break; // 可选的
        case PlanResult::StartPoint_Angle_Error:
            error_type_ = ErrorType::StartPoint_Angle_Error;
            break; // 可选的
        case PlanResult::EndPoint_Deviation:
            error_type_ = ErrorType::EndPoint_Deviation;
            break; // 可选的
        case PlanResult::EndPoint_Collision:
            error_type_ = ErrorType::EndPoint_Collision;
            break; // 可选的
        case PlanResult::EndPoint_Infeasible:
            error_type_ = ErrorType::EndPoint_Infeasible;
            break; // 可选的
        case PlanResult::Map_Infeasible:
            error_type_ = ErrorType::ROAD_GRAPH_ERROR;
            break; // 可选的
        case PlanResult::Leaving_Load_Point_Too_Close:
            error_type_ = ErrorType::Leaving_Load_Point_Too_Close;
            break; // 可选的
        case PlanResult::Load_Queue_Point_Unreasonable:
            error_type_ = ErrorType::Load_Queue_Point_Unreasonable;
            break; // 可选的
        case PlanResult::Unload_Queue_Point_Unreasonable:
            error_type_ = ErrorType::Unload_Queue_Point_Unreasonable;
            break; // 可选的
    }
}

PlanResult Planning::FindBestTrajectory(_SinglePoint& input_point, int& search_end_index, vector<_TrajectoryPoint>& result_trajectory, const PlanRule& rule_id) {
    // global_path_为全局路径，只允许在[0,search_end_index]这个区间上进行路径拟合
    // 在这段路径上，从0开始进行采样，每隔5m采一个点，利用dubins基于特定的规划进行规划，将规划成功的所有轨迹及其对应点索引进行存储
    // 从中挑选出得分最佳的轨迹，并获得对应的i
    // 将这个最优秀的i对应的temp_end作为终点交给hybridA*进行规划，成功则退出，失败则将该列表中重新找最优秀的index来进行规划，直至成功
    // 将hybridA*规划出的路径与global_path_进行融合，得到新的result_trajectory
    // 将result_trajectory作为最终的输出
    long long                  time_threshold = 0.8 * 1000 * 1000;
    _SinglePoint               temp_end;
    bool                       verification_flag = false;
    PlanResult                 plan_result       = PlanResult::Plan_OK;
    std::multimap<double, int> mul_score_index; // 存储dubins预拟合的路径得分和对应的拟合点在global_path_中的index
    bool                       dubins_success = false, hybridA_success = false;
    std::vector<curve::Point>  dubins_path;
    vector<_TrajectoryPoint>   total_path, temp_trajectory;
    _TrajectoryPoint           xip2, xip1, xi, xim1, xim2;
    double                     score = 0.0;
    _TrajectoryPoint           temp_point;
    threadLogger_->info("search_end_index {} ", search_end_index);
    for (int i = 0; i <= search_end_index; i += 5) { // 这里-1的原因是为了防止total_path.insert(total_path.end(), global_path_.begin() + i + 1, global_path_.begin() + search_end_index);拼接出错
        threadLogger_->info("i:{}", i);
        temp_end.x   = global_path_.at(i).x;
        temp_end.y   = global_path_.at(i).y;
        temp_end.z   = global_path_.at(i).z;
        temp_end.yaw = global_path_.at(i).yaw;
        if (rule_id == PlanRule::Forward_All_Time || rule_id == PlanRule::Backward_All_Time) { // 这两种规划规则，可采用dubins预先校验
            if (rule_id == PlanRule::Forward_All_Time) {
                verification_flag = false;
            }
            else {
                verification_flag = true;
            }
            // 如果flag==0，则表示默认由起点向终点拟合，否则由终点向起点拟合
            if (PoseVerificationInterface(input_point, temp_end, verification_flag, dubins_path)) {
                threadLogger_->info("索引 {} 拟合成功 dubins_path.size():{}", i, dubins_path.size());
                score = 0.0;
                total_path.clear();
                // 将dubins_path中的点转换为_TrajectoryPoint并存储到tatal_path中
                for (auto it = dubins_path.begin(); it != dubins_path.end(); ++it) {
                    temp_point.x   = it->GetX();
                    temp_point.y   = it->GetY();
                    temp_point.yaw = it->GetAngle();
                    total_path.push_back(temp_point);
                }
                // 将global_path_中[i,search_end_index]这段路径拼接到total_path中
                total_path.insert(total_path.end(), global_path_.begin() + i, global_path_.begin() + search_end_index);
                Helper::RemoveBeforeSamePoint(total_path);
                // 计算total_path的得分,基于平滑度打分
                double score = 0.0;
                double a, b = 0.0;

                for (int i = 2; i < total_path.size() - 2; i++) {
                    xip2 = total_path.at(i - 2);
                    xip1 = total_path.at(i - 1);
                    xi   = total_path.at(i);
                    xim1 = total_path.at(i + 1);
                    xim2 = total_path.at(i + 2);
                    a    = 0.1 * (xip2.x - 4 * xip1.x + 6 * xi.x - 4 * xim1.x + xim2.x);
                    b    = 0.1 * (xip2.y - 4 * xip1.y + 6 * xi.y - 4 * xim1.y + xim2.y);
                    score += sqrt(a * a + b * b);
                }
                dubins_success = true;
                mul_score_index.insert({score, i});
            }
            else {
                threadLogger_->info("索引 {} dubins拟合失败", i);
                dubins_success = false;
            }
        }
        else {
            plan_result = ApplyHibridAStarWithTime(input_point, temp_end, temp_trajectory, rule_id, time_threshold);
            if (plan_result == PlanResult::Plan_OK) {
                // 将temp_trajectory与global_path_进行融合，得到result_trajectory
                result_trajectory.insert(result_trajectory.end(), temp_trajectory.begin(), temp_trajectory.end());
                // 将global_path_中[best_index+1,global_path_.size())这段路径也拼接到result_trajectory中
                result_trajectory.insert(result_trajectory.end(), global_path_.begin() + i, global_path_.begin() + search_end_index);
                Helper::RemoveBeforeSamePoint(result_trajectory);
                return PlanResult::Plan_OK;
            }
        }
    }
    threadLogger_->info("dubins_success:{}", dubins_success);
    if (!dubins_success) {
        return PlanResult::StartPoint_Angle_Error;
    }
    threadLogger_->info("mul_score_index.size():{} 基本信息如下：", mul_score_index.size());
    for (auto it = mul_score_index.begin(); it != mul_score_index.end(); ++it) {
        threadLogger_->info("score:{} index:{}", it->first, it->second);
    }

    // 从mul_score_index中挑选出得分最低的轨迹，并获得对应的index
    double best_score;
    int    best_index;
    while (!mul_score_index.empty()) {
        best_score = mul_score_index.begin()->first;
        best_index = mul_score_index.begin()->second;
        threadLogger_->info("当前选中的  best_score:{}  best_index:{}", best_score, best_index);
        temp_end.x   = global_path_.at(best_index).x;
        temp_end.y   = global_path_.at(best_index).y;
        temp_end.z   = global_path_.at(best_index).z;
        temp_end.yaw = global_path_.at(best_index).yaw;
        // 将temp_end作为终点交给hybridA*进行规划
        temp_trajectory.clear();
        plan_result = ApplyHibridAStarWithTime(input_point, temp_end, temp_trajectory, rule_id, time_threshold);
        if (plan_result == PlanResult::Plan_OK) {
            hybridA_success = true;
            break;
        }
        else {
            // 删除mul_score_index中得分最高的轨迹
            threadLogger_->info("当前选中的  best_score:{}  best_index:{} 规划失败，删除该轨迹", best_score, best_index);
            mul_score_index.erase(mul_score_index.begin());
        }
    }
    if (!hybridA_success) {
        threadLogger_->info("所有轨迹规划失败，返回规划失败");
        return PlanResult::Plan_Infeasible;
    }
    // 将temp_trajectory与global_path_进行融合，得到result_trajectory
    result_trajectory.insert(result_trajectory.end(), temp_trajectory.begin(), temp_trajectory.end());
    // 将global_path_中[best_index+1,global_path_.size())这段路径也拼接到result_trajectory中
    result_trajectory.insert(result_trajectory.end(), global_path_.begin() + best_index, global_path_.begin() + search_end_index);
    Helper::RemoveBeforeSamePoint(result_trajectory);
    threadLogger_->info("规划成功，返回规划成功");
    return PlanResult::Plan_OK;
}
