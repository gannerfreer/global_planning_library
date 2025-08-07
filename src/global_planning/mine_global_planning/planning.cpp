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
    machine_borders_.clear();
    wall_borders_.clear();
    all_referencelines_.clear();
    global_path_.clear();
    v_has_calculate_pair_.clear();
    reference_paths_.clear();

    task_type_               = TaskType::RESERVED;
    hybridAstar_path_length_ = 0;


#ifdef SKIP_HEADER // 此宏在采用makefile方式进行编译时会使用
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
void Planning::GlobalPathPlanningInterface(vector<_TrajectoryPoint>& path) {
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

    result = HybirdAStarFitting();
    if (result != PlanResult::Plan_OK) {
        threadLogger_->info("hybridA*算法在处理起点到参考路径拟合的路段失败");
        cout << "hybridA*算法在处理起点到参考路径拟合的路段失败" << endl;
        FillErrorCode(result);
        return;
    }

    // 处理路径点只有2个的情况，这种case无法执行后续的速度规划逻辑，只能在此进行特殊处理
    if (IsShortDistance()) {
        path = global_path_;
        return;
    }

    threadLogger_->info("执行RemoveAfterSamePoint");


    Helper::RemoveAfterSamePoint(global_path_);
    for (int i = 0; i < global_path_.size(); i++) {
        threadLogger_->info("x:{}  y:{}  direction:{}  curvature:{}   yaw:{}  attribute:{}", global_path_.at(i).x, global_path_.at(i).y, global_path_.at(i).direction, global_path_.at(i).curvature, global_path_.at(i).yaw / M_PI * 180, static_cast<int>(global_path_.at(i).attribute));
    }

    threadLogger_->info("StartEndPointProcess global_path_.size():{}", global_path_.size());
    // 将起点、终点放入全局路径
    StartEndPointProcess();


    threadLogger_->info("global_path_.size():{}", global_path_.size());
    CurvatureCal(global_path_);
    threadLogger_->info("执行均匀碾压前路径点曲率");
    for (int i = 0; i < global_path_.size(); i++) {
        threadLogger_->info("x:{}  y:{}  direction:{}  curvature:{}   yaw:{}  attribute:{}", global_path_.at(i).x, global_path_.at(i).y, global_path_.at(i).direction, global_path_.at(i).curvature, global_path_.at(i).yaw / M_PI * 180, static_cast<int>(global_path_.at(i).attribute));
    }
    // 将global_path_保存到 before_uniform_compaction.txt文件中
    //  std::ofstream file_out;
    //  file_out.open("before_uniform_compaction.txt");
    //  for (auto i : global_path_) {
    //      file_out << i.x << " " << i.y << " " << i.yaw / M_PI * 180 << " " << (int)i.direction << " " << i.curvature << " " << static_cast<int>(i.attribute) << endl;
    //  }
    //  file_out.close();


    // 均匀碾压：对除了过磅、洗车和倒车之外的路段进行横向偏移
    if (vehicle_param_.uniform_compaction_enable == true) {
        // 先检查一遍global_path_的曲率，如果超标就不执行均匀碾压
        double curvature_threshold = -1;
        if (vehicle_param_.is_light) {
            curvature_threshold = tan(vehicle_param_.light_forward_max_steering) / vehicle_param_.wheel_base;
        }
        else {
            curvature_threshold = tan(vehicle_param_.heavy_forward_max_steering) / vehicle_param_.wheel_base;
        }
        bool skip_path_offset = false;
        for (auto i : global_path_) {
            if (fabs(i.curvature) > curvature_threshold + eps) {
                skip_path_offset = true;
                threadLogger_->info("路径存在曲率超标，为避免均匀碾压陷入死循环，跳过均匀均匀碾压");
            }
        }
        if (!skip_path_offset) {
            threadLogger_->info("开启均匀碾压");
            if (!PathOffset()) {
                error_type_ = ErrorType::ALGORITHM_ERROR_UNIFORM_COMPACTION;
                return;
            }
        }
    }
    // 将global_path_保存到 after_uniform_compaction.txt文件中
    //  file_out.open("after_uniform_compaction.txt");
    //  for (auto i : global_path_) {
    //      file_out << i.x << " " << i.y << " " << i.yaw / M_PI * 180 << " " << (int)i.direction << " " << i.curvature << " " << static_cast<int>(i.attribute) << endl;
    //  }
    //  file_out.close();


    // 对进行速度规划前的路径基于梯度下降进行平滑
    // std::ofstream file_out;
    // file_out.open("total_path_smooth_before.txt");
    // for (size_t index = 0; index < global_path_.size(); index++) {
    //     file_out << global_path_.at(index).x << " " << global_path_.at(index).y << " " << global_path_.at(index).yaw / M_PI * 180 << " " << (int)global_path_.at(index).direction << " " << global_path_.at(index).curvature << " " << static_cast<int>(global_path_.at(index).attribute) << endl;
    // }
    // file_out.close();
    SmoothPath(global_path_);
    // 计算累计s
    Helper::CalDistance(global_path_);
    CurvatureCal(global_path_);
    // file_out.open("total_path_smooth_after.txt");
    // for (size_t index = 0; index < global_path_.size(); index++) {
    //     file_out << global_path_.at(index).x << " " << global_path_.at(index).y << " " << global_path_.at(index).yaw / M_PI * 180 << " " << (int)global_path_.at(index).direction << " " << global_path_.at(index).curvature << " " << static_cast<int>(global_path_.at(index).attribute) << endl;
    // }
    // file_out.close();

    threadLogger_->info("执行均匀碾压后路径点曲率");
    for (auto i : global_path_) {
        threadLogger_->info("x:{}  y:{}  direction:{}  curvature:{}   yaw:{}  attribute:{} speed_limit:{} acc:{}", i.x, i.y, i.direction, i.curvature, i.yaw / M_PI * 180, static_cast<int>(i.attribute), i.speed_limit, i.acc);
    }
    // 将global_path_保存到 after_smooth.txt文件中
    //  file_out.open("after_smooth.txt");
    //  for (auto i : global_path_) {
    //      file_out << i.x << " " << i.y << " " << i.yaw / M_PI * 180 << " " << (int)i.direction << " " << i.curvature << " " << static_cast<int>(i.attribute) << endl;
    //  }
    //  file_out.close();


    // 角度转换
    Helper::Calrad2deg(global_path_);


    // 速度规划：限速设置、梯形速度规划
    my_speed_planning_.threadLogger_            = threadLogger_;
    my_speed_planning_.hybridAstar_path_length_ = hybridAstar_path_length_;
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

    // 检查全局路径是否与地图边界发生碰撞
    if (!IsGlobalPathCollision()) {
        threadLogger_->error("全局路径与地图边界发生碰撞，放弃此次规划结果");
        error_type_ = ErrorType::ALGORITHM_ERROR_TRAJECTORY_VERIFY_PATH_COLLISION;
        return;
    }

    path = global_path_;
    threadLogger_->info("规划成功，即将返回轨迹  轨迹总长:{}", global_path_.size());
    return;
}


PlanResult Planning::ProgressiveHybirdAStar(_SinglePoint& input_point, int& search_index, vector<_TrajectoryPoint>& result_trajectory, const PlanRule& rule_id, int max_search_index, double start_point_offset_distance, vector<_TrajectoryPoint>& input_path) {
    long long time_threshold = vehicle_param_.plan_time * 1000 * 1000;
    threadLogger_->info("规划时间：{} ms", vehicle_param_.plan_time * 1000);
    bool                       verification_flag = false;
    _SinglePoint               temp_start, temp_end;
    int                        cal = 0;
    PlanResult                 result;
    std::vector<curve::Point>  dubins_path, total_dubins_path;
    curve::Point               xip2, xip1, xi, xim1, xim2;
    double                     score = 0.0;
    std::multimap<double, int> mul_score_index;                                                                                                                                             // 存储dubins预拟合的路径得分和对应的拟合点在global_path_中的index
    double                     lat_dis = fabs((input_point.y - input_path.front().y) * cos(input_path.front().yaw) - (input_point.x - input_path.front().x) * sin(input_path.front().yaw)); // 横向距离先不区分左正右负

    std::vector<curve::Point> temp_path;
    temp_path.clear();
    // 将input_path拷贝一份到temp_path
    curve::Point temp_point;
    for (int i = 0; i < min((int)input_path.size(), vehicle_param_.sample_num + 10); i++) {
        temp_point.SetX(input_path[i].x);
        temp_point.SetY(input_path[i].y);
        temp_path.push_back(temp_point);
    }
    max_search_index = min(max_search_index, vehicle_param_.sample_num);
    for (int i = 0; i <= max_search_index; i += 1) {
        cal++;

        temp_end.x   = input_path.at(i).x;
        temp_end.y   = input_path.at(i).y;
        temp_end.z   = input_path.at(i).z;
        temp_end.yaw = input_path.at(i).yaw;

        if (rule_id == PlanRule::Forward_All_Time || rule_id == PlanRule::Backward_All_Time) { // 这两种规划规则，可采用dubins预先校验
            if (rule_id == PlanRule::Forward_All_Time) {
                verification_flag = false;
            }
            else {
                verification_flag = true;
            }

            // 如果flag==0，则表示默认由起点向终点拟合，否则由终点向起点拟合
            if (PoseVerificationInterface(input_point, temp_end, verification_flag, start_point_offset_distance, dubins_path)) {
                // // 将dubins_path保存到txt文件中，文件名后缀用i
                // std::ofstream outfile("dubins_path_" + std::to_string(i) + ".txt");
                // for (int i = 0; i < dubins_path.size(); i++) {
                //     outfile << dubins_path[i].GetX() << " " << dubins_path[i].GetY() << std::endl;
                // }
                // outfile.close();

                threadLogger_->info("索引 {} 拟合成功 dubins_path.size():{}", i, dubins_path.size());
                total_dubins_path.clear();
                total_dubins_path = dubins_path;
                total_dubins_path.insert(total_dubins_path.end(), temp_path.begin() + i + 1, temp_path.end());
                // 计算total_dubins_path的累积长度
                double total_length = 0;
                for (int i = 1; i < total_dubins_path.size(); i++) {
                    total_length += std::hypot(total_dubins_path[i].GetX() - total_dubins_path[i - 1].GetX(), total_dubins_path[i].GetY() - total_dubins_path[i - 1].GetY());
                }
                if (fabs(lat_dis) >= vehicle_param_.dis_threshold) {
                    score = total_length;
                }
                else {
                    threadLogger_->info("横向距离小于{} m，采用优先从最近点切入参考路径策略", vehicle_param_.dis_threshold);
                    score = 1.0 / total_length;
                }

                mul_score_index.insert({score, i});
                threadLogger_->info("第 {}个候选点，其索引：{},坐标：({},{},{}), rule_id:{},经过dubins曲线预先校验，合格,得分：{} ", cal, i, temp_end.x, temp_end.y, temp_end.yaw / M_PI * 180, static_cast<int>(rule_id), score);
            }
            else {
                // threadLogger_->info("索引 {} dubins拟合失败", i);
                result = PlanResult::StartPoint_Unreasonable;
            }
        } // 这种规划规则，不采用dubins进行预先校验
        else {
            threadLogger_->info("第 {}个候选点，其索引：{},坐标：({},{},{}), rule_id:{}", cal, i, temp_end.x, temp_end.y, temp_end.yaw / M_PI * 180, static_cast<int>(rule_id));
            result = ApplyHibridAStarWithTime(input_point, temp_end, result_trajectory, rule_id, time_threshold);
            if (result == PlanResult::Plan_OK) {
                search_index = i;
                return result;
            }
            else {
                threadLogger_->info("本次规划失败，失败码：{}", static_cast<int>(result));
            }
        }
    }

    if (mul_score_index.empty()) {
        threadLogger_->info("最多搜索 {} 个点,这些点要么dubins校验统统失败,要么采用特殊规则规划都失败", vehicle_param_.sample_num);
        return result;
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
        temp_end.x   = input_path.at(best_index).x;
        temp_end.y   = input_path.at(best_index).y;
        temp_end.z   = input_path.at(best_index).z;
        temp_end.yaw = input_path.at(best_index).yaw;
        // 将temp_end作为终点交给hybridA*进行规划
        result = ApplyHibridAStarWithTime(input_point, temp_end, result_trajectory, rule_id, time_threshold);
        if (result == PlanResult::Plan_OK) {
            search_index = best_index;
            return result;
        }
        else {
            // 删除mul_score_index中得分最高的轨迹
            threadLogger_->info("当前选中的  best_score:{}  best_index:{} 规划失败，删除该轨迹", best_score, best_index);
            mul_score_index.erase(mul_score_index.begin());
        }
    }
    return result;
}

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

        // 长距离倒车检查，检查远离：对于大于1段的，起步就倒车的，进行倒车距离检测
        // 先判断路径段数
        int sum = 1;
        for (int i = 0; i < final_path.size() - 1; i++) {
            if (final_path.at(i).direction != final_path.at(i + 1).direction) {
                sum++;
            }
        }
        if (sum > 1) {
            int total_length = 0;
            if (final_path.front().direction == MotionDirection::Backward) {
                for (int i = 0; i < final_path.size() - 1; i++) {
                    if (final_path.at(i).direction == final_path.at(i + 1).direction) {
                        total_length += hypot(final_path.at(i).x - final_path.at(i + 1).x, final_path.at(i).y - final_path.at(i + 1).y);
                    }
                }
                if (total_length > 20) {
                    threadLogger_->error("检测出起步倒车，且倒车距离过长，放弃此次规划结果");
                    return PlanResult::Plan_Infeasible;
                }
            }
        }
        return PlanResult::Plan_OK;
    }
    else {
        threadLogger_->error(" Failed to plan the path by hibrid A star  ");
        threadLogger_->error(" result:{}", static_cast<int>(result));
        return result;
    }
}


float Planning::CalculateOffSetWithoutCuravture(int index, int sum, float weight) {
    float L = vehicle_param_.offset_distance * weight; // 控制默认偏移量
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

    if (reference_paths_.size() > 0) {
        // 如果后台下发的要求拟合的参考路径不为空，则采用拟合的参考路径
        // 遍历每个路径的最后一个点，判断哪条路径的最后一个点距离end_point_最近，挑选出的这条路径,并算出start_point_距离这条路最近点的索引
        double min_distance = 1000;
        int    min_index    = 0;
        for (int i = 0; i < reference_paths_.size(); i++) {
            double distance = hypot(reference_paths_[i].back().x - end_point_.x, reference_paths_[i].back().y - end_point_.y);
            if (distance < min_distance) {
                min_distance = distance;
                min_index    = i;
            }
        }
        if (min_distance > 0.3) {
            if (task_type_ != TaskType::EXIT_LOAD) {
                threadLogger_->error("给定终点偏离参考路径，放弃此次规划");
                return PlanResult::EndPoint_Deviation;
            }
            else {
                threadLogger_->info("exit load");
                threadLogger_->info("打印referce_paths_最后一条路径信息");
                for(int i=0;i<reference_paths_.back().size();i++){
                    threadLogger_->info("x:{} y:{} yaw:{} direction:{}", reference_paths_.back().at(i).x, reference_paths_.back().at(i).y, reference_paths_.back().at(i).yaw/M_PI*180, reference_paths_.back().at(i).direction  );
                }
                
                Helper::CalNearestIndex(start_point_, reference_paths_.back(), start_index_, start_lat_dis_, start_lon_dis_, start_distance_, start_angle_diff_);
                global_path_.insert(global_path_.end(), reference_paths_.back().begin() + start_index_, reference_paths_.back().end());
                threadLogger_->info("global_path_.size():{}", global_path_.size());
                threadLogger_->info("起点匹配上的路径索引{}，横向距离{}，纵向距离{}, 角度误差{}", start_index_, start_lat_dis_, start_lon_dis_, start_angle_diff_ / M_PI * 180.0);
                cout << "起点匹配上的路径索引" << start_index_ << " 横向距离" << start_lat_dis_ << " 纵向距离" << start_lon_dis_ << " 角度误差" << start_angle_diff_ / M_PI * 180.0 << endl;
                _SinglePoint new_start_point;
                new_start_point.x   = reference_paths_.back().back().x;
                new_start_point.y   = reference_paths_.back().back().y;
                new_start_point.yaw = reference_paths_.back().back().yaw;
                vector<int> success_path_vec;
                // 找all_referencelines_中每条路径第一个点与new_start_point几何距离小于1.5m的最近的路径
                for (auto it = all_referencelines_.begin(); it != all_referencelines_.end(); ++it) {
                    if (hypot(it->second.trajectory.at(0).x - new_start_point.x, it->second.trajectory.at(0).y - new_start_point.y) < 1.5) {
                        success_path_vec.push_back(it->first);
                    }
                }
                threadLogger_->info("success_path_vec.size():{}", success_path_vec.size());
                vector<int> success_path_vec_switch;
                for (auto i : success_path_vec) {
                    success_path_vec_switch.push_back(GlobalVariable::getInstance()->BinarySearch(sequence_mapping_, i));
                }

                double temp_end_lat_dis, temp_end_lon_dis = 0;
                int    end_id             = Helper::GetNearestReferencelines(end_point_, all_referencelines_, temp_end_lat_dis, temp_end_lon_dis);
                int    end_id_switch      = GlobalVariable::getInstance()->BinarySearch(sequence_mapping_, end_id);
                bool   found_Connect_path = false;
                for (auto i : success_path_vec_switch) {
                    if (IsConnect(i, end_id_switch)) {
                        threadLogger_->info("找到连接路径");
                        found_Connect_path = true;
                        dijkstra_.searchpath(i, end_id_switch);
                        road_sequence_            = dijkstra_.GetPath();
                        threadLogger_->info("road_sequence_.size():{}", road_sequence_.size());
                        end_key_                  = sequence_mapping_.at(end_id_switch);
                        _SingleTraj temp_end_traj = all_referencelines_.at(end_key_);
                        Helper::CalNearestIndex(end_point_, temp_end_traj, end_index_, end_lat_dis_, end_lon_dis_, end_distance_, end_angle_diff_);
                        start_index_ = 0;
                        PathClipAndSplice();
                        return PlanResult::Plan_OK;
                    }
                }
                if (found_Connect_path == false) {
                    return PlanResult::Map_Infeasible;
                }
            }

            // 计算start_point_距离这条路最近点的索引
            Helper::CalNearestIndex(start_point_, reference_paths_[min_index], start_index_, start_lat_dis_, start_lon_dis_, start_distance_, start_angle_diff_);
            // 将匹配到的路径添加到全局路径中
            threadLogger_->info("起点匹配上的路径索引{}，横向距离{}，纵向距离{}, 角度误差{}", start_index_, start_lat_dis_, start_lon_dis_, start_angle_diff_ / M_PI * 180.0);

            global_path_.insert(global_path_.end(), reference_paths_[min_index].begin() + start_index_, reference_paths_[min_index].end());
            cout << "起点匹配上的路径索引" << start_index_ << " 横向距离" << start_lat_dis_ << " 纵向距离" << start_lon_dis_ << " 角度误差" << start_angle_diff_ / M_PI * 180.0 << endl;
            return PlanResult::Plan_OK;
        }
    }

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
            threadLogger_->info("temp_end_lat_dis:{} temp_end_lon_dis:{} temp_start_lat_dis:{} temp_start_lon_dis:{} end_path_id:{} start_path_id:{}", temp_end_lat_dis, temp_end_lon_dis, temp_start_lat_dis, temp_start_lon_dis, end_path_id, start_path_id);

            // 对于 装载体/卸载之类的任务，下述条件满足其一，就直接采用hybridA*算法直接规划
            if (fabs(temp_end_lat_dis) > 1 || fabs(temp_end_lon_dis) > 1 || fabs(temp_start_lat_dis) > 1 || fabs(temp_start_lon_dis) > 1) {
                threadLogger_->info("此次装卸载任务无参考路径");
                result = NotFollowReferencelinePlanning();
                return result;
            }
            else {
                // 终点位于参考路径上，才可以开启沿参考路径规划策略
                threadLogger_->info("终点位于参考路径上，采用沿参考路径规划策略，temp_end_lat_dis:{} temp_end_lon_dis:{}", temp_end_lat_dis, temp_end_lon_dis);
                result = FollowReferencelinePlanning();
                return result;
            }
        }
        else {
            // 对于常规调度任务，需上来就判断终点是否位于参考路径上
            if (hypot(temp_end_lat_dis, temp_end_lon_dis) > 0.3) {
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

    my_optimal_path_.InitBound(start_point_, map_border_, machine_borders_, wall_borders_, vehicle_param_);
    vector<_TrajectoryPoint> temp_traj;
    long long                time_threshold = 0.9 * 1000 * 1000;
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
        int load_point_end_offset_distance = vehicle_param_.L2;
        while (load_point_end_offset_distance >= 1) {
            my_optimal_path_.start_offset_distance_ = vehicle_param_.L1;
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
            time_threshold                          = 10 * 1000 * 1000;
            my_optimal_path_.start_offset_distance_ = 0;
            my_optimal_path_.end_offset_distance_   = vehicle_param_.L2;
            result                                  = ApplyHibridAStarWithTime(start_point_, end_point_, temp_traj, PlanRule::Start_Front_End_Back, time_threshold);
            if (result != PlanResult::Plan_OK) {
                threadLogger_->error("装载任务，PlanRule::Start_Front_End_Back规则，装载点直线延伸 {} m，Hybird A*无法规划出当前起点至终点的路径", vehicle_param_.L2);
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
        int unload_point_end_offset_distance = vehicle_param_.L2;
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

    return result;
}


PlanResult Planning::FollowReferencelinePlanning() {
    // 搜索策略，终点只搜索0.2m范围内的参考路径，起点采用渐进式扩大搜索策略，从0.5m初始搜索半径开始
    bool        is_found          = false; // 用于跟踪是否找到了成功的路径对
    double      end_search_radius = 0.3, start_search_radius = 0.5;
    vector<int> start_path_vec, end_path_vec;
    cout << "开始进入起点、终点搜索环节" << endl;
    cout << "end_search_radius:" << end_search_radius << endl;


    Helper::GetReferencelinesWithRadiusAndAngle(end_point_, all_referencelines_, end_search_radius, end_path_vec);
    threadLogger_->info("终点搜索半径：{},搜索到路径数量:{}", end_search_radius, end_path_vec.size());
    cout << "终点搜索半径:" << end_search_radius << "  搜索到路径数量:  " << end_path_vec.size() << endl;
    if (end_path_vec.empty()) {
        return PlanResult::EndPoint_Deviation;
    }
    threadLogger_->info("搜索到的路径ID信息如下");
    cout << "搜索到的路径ID信息如下:" << endl;
    for (auto i : end_path_vec) {
        threadLogger_->info(i);
        cout << i << " ";
    }
    cout << endl;

    start_search_radius = 0.5;
    // 起点采用渐进式扩大搜索策略，从0.5m初始搜索半径开始
    while (start_search_radius <= 100) {
        if (Helper::GetReferencelinesWithRadius(start_point_, all_referencelines_, start_search_radius, start_path_vec)) {
            cout << "起点搜索半径：:" << start_search_radius << "  搜索到路径数量:  " << start_path_vec.size() << endl;

            vector<int> start_path_vec_switch, end_path_vec_switch;
            for (auto i : start_path_vec) {
                is_found = true;
                start_path_vec_switch.push_back(GlobalVariable::getInstance()->BinarySearch(sequence_mapping_, i));
            }
            for (auto i : end_path_vec) {
                end_path_vec_switch.push_back(GlobalVariable::getInstance()->BinarySearch(sequence_mapping_, i));
            }

            // 在start_path_vec_switch和end_path_vec_switch中查找连通路径
            for (auto start : start_path_vec_switch) {
                for (auto end : end_path_vec_switch) {
                    if (HasSearched(start, end)) {
                        continue;
                    }
                    threadLogger_->info("索引  start:{},end:{}", start, end);
                    if (IsConnect(start, end)) {
                        threadLogger_->info("路径{}与路径{}联通", sequence_mapping_.at(start), sequence_mapping_.at(end));
                        cout << "路径 " << sequence_mapping_.at(start) << " 与路径 " << sequence_mapping_.at(end) << " 联通" << endl;

                        // 找到连通路径后立即处理并返回
                        dijkstra_.searchpath(start, end);
                        road_sequence_ = dijkstra_.GetPath();

                        start_key_                  = sequence_mapping_.at(start);
                        end_key_                    = sequence_mapping_.at(end);
                        _SingleTraj temp_start_traj = all_referencelines_.at(start_key_);
                        _SingleTraj temp_end_traj   = all_referencelines_.at(end_key_);
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
    if (is_found) {
        // 起点周围有参考路径，但是没有联通的参考路径
        return PlanResult::Map_Infeasible;
    }
    else {
        // 说明起点附近100m未找到参考路径
        return PlanResult::Start_Point_Too_Far;
    }
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
    threadLogger_->info("路径最后一个点与终点的角度:{}  几何距离:{}", end_point_last_point_angle_diff / M_PI * 180.0, hypot(end_point_.x - global_path_.back().x, end_point_.y - global_path_.back().y));
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
    last_point.speed_limit = global_path_.back().speed_limit;

    last_point.speed     = 0;
    last_point.curvature = global_path_.back().curvature;
    last_point.distance  = 0;
    last_point.direction = global_path_.back().direction;
    last_point.attribute = global_path_.back().attribute;
    global_path_.push_back(last_point);

    threadLogger_->info("将规划终点作为最后一个点添加进global_path的末尾");
    threadLogger_->info("StartEndPointProcess 结束");
}
bool Planning::PathOffset() {
    threadLogger_->info("均匀碾压功能开启");
    vector<_TrajectoryPoint> path_before_offset, path_after_offset, input_points;

    Bound              map_border;
    vector<Coordinate> vC;
    for (unsigned int i = 0; i < map_border_.size(); ++i) {
        Coordinate temp_point;
        temp_point.z = 0;
        temp_point.x = map_border_.at(i).x;
        temp_point.y = map_border_.at(i).y;
        vC.push_back(temp_point);
    }
    map_border.push_back(vC);


    collison_check_.InitParam(vehicle_param_);
    collison_check_.InitBoundMap(map_border);


    for (int i = 0; i < global_path_.size(); i++) {
        global_path_.at(i).offset_flag = true; // 先将所有路径点的offset_flag属性设置为true
    }
    // 设置temp中，每个点的offset_flag信息，来确定此次规划任务需要偏移的路段，true表示需要偏移，false表示不需要偏移
    for (int i = 0; i < global_path_.size(); i++) {
        if (global_path_.at(i).attribute == PointAttribute::weight_point || global_path_.at(i).attribute == PointAttribute::clean_point) {
            for (int j = i - 20; j < i + 20; j++) {
                if (j >= 0 && j < global_path_.size()) {
                    global_path_.at(j).offset_flag = false; // 将过磅点和洗车点左右10m设置为无需偏移的路段
                }
            }
        }
        if (global_path_.at(i).direction == 1) {
            global_path_.at(i).offset_flag = false; // 将倒车的路段offset_flag也设置为false,即不需要进行偏移
        }
        if (i < 20) {
            global_path_.at(i).offset_flag = false;
        }
    }

    path_before_offset = global_path_;


    // 定义您想要生成的浮点数的集合
    random_device rd;
    mt19937       gen(rd());
    vector<float> weights = {0, 1.0};
    // 使用uniform_int_distribution从集合中随机选择一个索引
    uniform_int_distribution<size_t> dis(0, weights.size() - 1);
    float                            weight = 0.0;
    // 从集合中随机选择一个权重
    weight = weights[dis(gen)];
    threadLogger_->info("weight：{}", weight);

    // 下属代码逻辑为先对路径偏移一次，找出碰撞检测失败的点的index
    set<int> record_where_is_collision; // 记录哪些index点碰撞检测会失败
    record_where_is_collision.clear();

    vector<pair<int, int>> reverse_section, forward_section;
    int                    start = 0, end = 0;
    bool                   flag1;
    if (path_before_offset.front().offset_flag == true) // 起步就是需要偏移的路段
    {
        threadLogger_->info("起步就是需要偏移的路段");

        flag1 = true;
        for (int i = 0; i < path_before_offset.size() - 1; i++) {
            if (path_before_offset.at(i + 1).offset_flag != path_before_offset.at(i).offset_flag) {
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
        for (int i = 0; i < path_before_offset.size() - 1; i++) {
            if (path_before_offset.at(i + 1).offset_flag != path_before_offset.at(i).offset_flag) {
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
    if (path_before_offset.back().offset_flag == true) // 最后一段为需要偏移的道路
    {
        forward_section.push_back(make_pair(start, path_before_offset.size() - 1));
    }
    else {
        reverse_section.push_back(make_pair(start, path_before_offset.size() - 1));
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

                path_before_offset.at(m).x = path_before_offset.at(m).x + off_set * cos(path_before_offset.at(m).yaw + M_PI / 2);
                path_before_offset.at(m).y = path_before_offset.at(m).y + off_set * sin(path_before_offset.at(m).yaw + M_PI / 2);


                input_points.push_back(path_before_offset.at(m));
                vec_off_set.push_back(off_set);
            }


            path_after_offset.insert(path_after_offset.end(), input_points.begin(), input_points.end());


            if (j < reverse_section.size()) {
                path_after_offset.insert(path_after_offset.end(), path_before_offset.begin() + reverse_section.at(j).first, path_before_offset.begin() + reverse_section.at(j).second + 1);
                j++;
            }
        }
    }
    else {
        int i = 0;
        for (int j = 0; j < reverse_section.size(); j++) {
            path_after_offset.insert(path_after_offset.end(), path_before_offset.begin() + reverse_section.at(j).first, path_before_offset.begin() + reverse_section.at(j).second + 1);
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

                    path_before_offset.at(m).x = path_before_offset.at(m).x + off_set * cos(path_before_offset.at(m).yaw + M_PI / 2);
                    path_before_offset.at(m).y = path_before_offset.at(m).y + off_set * sin(path_before_offset.at(m).yaw + M_PI / 2);

                    input_points.push_back(path_before_offset.at(m));
                }

                if (m != end + 1) {
                    input_points.push_back(path_before_offset.at(end));
                }
                threadLogger_->info("输入点的数量：{}", input_points.size());

                threadLogger_->info("当前偏移的权重：{}", weight);

                path_after_offset.insert(path_after_offset.end(), input_points.begin(), input_points.end());
                i++;
            }
        }
    }
    // 对global_path进行碰撞检测，碰撞检测失败的点，其offset标志位置为false，曲率超标的点，其offset标志为也置为false
    for (int i = 0; i < path_after_offset.size(); i++) {
        if (collison_check_.IsVehicleCollisionWithAll(Point(path_after_offset.at(i).x, path_after_offset.at(i).y, path_after_offset.at(i).z, path_after_offset.at(i).yaw, static_cast<GlobalPlanning::MotionDirection>(path_after_offset.at(i).direction)))) {
            record_where_is_collision.insert(i);
            threadLogger_->info("偏移后路径点存在碰撞 {}", i);
        }
    }
    for (const auto i : record_where_is_collision) {
        threadLogger_->info("i:{}", i);
        global_path_.at(i).offset_flag = false; // 将倒车的路段offset_flag也设置为false,即不需要进行偏移
    }


    input_points.clear();


    set<int> record_where_is_curvature_exceed; // 记录global_path_中不需要进行偏移的点的index
    do {
        for (const auto i : record_where_is_curvature_exceed) {
            threadLogger_->info("i:{}", i);
            global_path_.at(i).offset_flag = false; // 将倒车的路段offset_flag也设置为false,即不需要进行偏移
        }
        record_where_is_curvature_exceed.clear();
        path_after_offset.clear();
        path_before_offset = global_path_;
        threadLogger_->info("path_before_offset = global_path_");
        for (int i = 0; i < path_before_offset.size(); i++) {
            threadLogger_->info("i:{} curvature:{} radius:{}", i, path_before_offset.at(i).curvature, 1.0 / fabs(path_before_offset.at(i).curvature));
        }

        vector<pair<int, int>> reverse_section, forward_section;
        int                    start = 0, end = 0;
        bool                   flag1;
        if (path_before_offset.front().offset_flag == true) // 起步就是需要偏移的路段
        {
            threadLogger_->info("起步就是需要偏移的路段");

            flag1 = true;
            for (int i = 0; i < path_before_offset.size() - 1; i++) {
                if (path_before_offset.at(i + 1).offset_flag != path_before_offset.at(i).offset_flag) {
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
            for (int i = 0; i < path_before_offset.size() - 1; i++) {
                if (path_before_offset.at(i + 1).offset_flag != path_before_offset.at(i).offset_flag) {
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
        if (path_before_offset.back().offset_flag == true) // 最后一段为需要偏移的道路
        {
            forward_section.push_back(make_pair(start, path_before_offset.size() - 1));
        }
        else {
            reverse_section.push_back(make_pair(start, path_before_offset.size() - 1));
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

                    path_before_offset.at(m).x = path_before_offset.at(m).x + off_set * cos(path_before_offset.at(m).yaw + M_PI / 2);
                    path_before_offset.at(m).y = path_before_offset.at(m).y + off_set * sin(path_before_offset.at(m).yaw + M_PI / 2);


                    input_points.push_back(path_before_offset.at(m));
                    vec_off_set.push_back(off_set);
                }


                path_after_offset.insert(path_after_offset.end(), input_points.begin(), input_points.end());


                if (j < reverse_section.size()) {
                    path_after_offset.insert(path_after_offset.end(), path_before_offset.begin() + reverse_section.at(j).first, path_before_offset.begin() + reverse_section.at(j).second + 1);
                    j++;
                }
            }
        }
        else {
            int i = 0;
            for (int j = 0; j < reverse_section.size(); j++) {
                path_after_offset.insert(path_after_offset.end(), path_before_offset.begin() + reverse_section.at(j).first, path_before_offset.begin() + reverse_section.at(j).second + 1);
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

                        path_before_offset.at(m).x = path_before_offset.at(m).x + off_set * cos(path_before_offset.at(m).yaw + M_PI / 2);
                        path_before_offset.at(m).y = path_before_offset.at(m).y + off_set * sin(path_before_offset.at(m).yaw + M_PI / 2);

                        input_points.push_back(path_before_offset.at(m));
                    }

                    if (m != end + 1) {
                        input_points.push_back(path_before_offset.at(end));
                    }
                    threadLogger_->info("输入点的数量：{}", input_points.size());

                    threadLogger_->info("当前偏移的权重：{}", weight);

                    path_after_offset.insert(path_after_offset.end(), input_points.begin(), input_points.end());
                    threadLogger_->info("input_points.size():{}", input_points.size());
                    i++;
                }
            }
        }

        CurvatureCal(path_after_offset);
        double curvature_threshold = -1;
        if (vehicle_param_.is_light) {
            curvature_threshold = tan(vehicle_param_.light_forward_max_steering) / vehicle_param_.wheel_base;
        }
        else {
            curvature_threshold = tan(vehicle_param_.heavy_forward_max_steering) / vehicle_param_.wheel_base;
        }
        threadLogger_->info("radius_threshold: {}", 1.0 / fabs(curvature_threshold));
        for (int i = 0; i < path_after_offset.size(); i++) {
            if (1.0 / fabs(path_after_offset.at(i).curvature) < 1.0 / fabs(curvature_threshold) - eps) {
                if (i > 0) record_where_is_curvature_exceed.insert(i - 1);
                record_where_is_curvature_exceed.insert(i);
                if (i < path_after_offset.size() - 1) record_where_is_curvature_exceed.insert(i + 1);
                threadLogger_->info("偏移后路径点曲率超标 {} radius:{}", i, 1.0 / fabs(path_after_offset.at(i).curvature));
            }
        }
    } while (!record_where_is_curvature_exceed.empty());
    threadLogger_->info("均匀碾压功能完毕");
    global_path_ = path_after_offset;
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
                else {
                    point.direction = 0;
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
                global_path_.insert(global_path_.end(), all_referencelines_.at(temp_key).trajectory.begin(), all_referencelines_.at(temp_key).trajectory.begin() + end_index_ + 1);
            }
            else {
                global_path_.insert(global_path_.end(), all_referencelines_.at(temp_key).trajectory.begin(), all_referencelines_.at(temp_key).trajectory.end());
            }
        }
    }
    threadLogger_->info("从参考路径中截取的路段信息如下，全长大约 {} m", global_path_.size());
    for (int i = 0; i < global_path_.size(); i++) {
        threadLogger_->info("x:{} y:{} yaw:{} direction:{} attribute:{}", global_path_.at(i).x, global_path_.at(i).y, global_path_.at(i).yaw / M_PI * 180.0, static_cast<int>(global_path_.at(i).direction), static_cast<int>(global_path_.at(i).attribute));
    }
}
PlanResult Planning::HybirdAStarFitting() {
    //  初始化HybrdiA*算法地图边界及voronoi图
    PlanResult result              = PlanResult::Plan_OK;
    my_optimal_path_.threadLogger_ = threadLogger_;
    my_optimal_path_.InitBound(start_point_, map_border_, machine_borders_, wall_borders_, vehicle_param_);

    Bound              part_map_border;
    vector<Coordinate> vC;
    for (unsigned int i = 0; i < map_border_.size(); ++i) {
        Coordinate temp_point;
        temp_point.z = 0;
        temp_point.x = map_border_.at(i).x;
        temp_point.y = map_border_.at(i).y;
        if (hypot(start_point_.x - temp_point.x, start_point_.y - temp_point.y) < 100) {
            vC.push_back(temp_point);
        }
    }
    part_map_border.push_back(vC);
    collison_check_.InitParam(vehicle_param_);
    collison_check_.InitBoundMap(part_map_border);


    // 基于横纵向距离来判断是否进行hybirdA*拟合
    threadLogger_->info("Enter HybirdAStarFitting");
    bool   start_need_fitting     = false;
    bool   load_unload_start_flag = false; // 此标志位为true时，表明是从装载点\卸载点出来的调度任务
    double nearest_distance       = 0;
    // 这里的逻辑主要是区分global_path位于start_point_前方还是后方，如果是前方，配合start_lat_dis_和start_lon_dis_来判断是常规调度还是装载点调度
    nearest_distance = hypot(start_point_.x - global_path_.front().x, start_point_.y - global_path_.front().y);
    threadLogger_->info("起点与参考路径最近点的几何距离:{},其中，横向距离：{},纵向距离：{}", nearest_distance, start_lat_dis_, start_lon_dis_);

    if (fabs(start_lat_dis_) > 0.2 || fabs(start_lon_dis_) > 0.8 || start_angle_diff_ > 8.0 / 180.0 * M_PI) {
        start_need_fitting = true;

        if (nearest_distance > 20) {
            // nearest_distance>20之间诶判定从卸载点（无参考路径情况下）或从装载点出发的任务，由于可能有乱石堆的存在，这种直线延伸距离需要额外自行配置
            load_unload_start_flag = true;
        }
    }


    // 只看起点
    if (start_need_fitting) // 起点需要进行HybirdA*拟合
    {
        // 对global_path的构型进行识别，
        if (IsForwardAndBackwardReferencePath()) {
            threadLogger_->info("识别出global_path_为特殊构型");

            // 基于参考路径搞出三段待拟合的路径，分别为前进段、长后退段、短后退段
            vector<_TrajectoryPoint> path1, path2, path3;
            for (int i = 0; i < global_path_.size(); i++) {
                if (i > 0) {
                    if (global_path_.at(i).direction != global_path_.at(i - 1).direction) {
                        break;
                    }
                }

                path1.push_back(global_path_.at(i));
            }

            for (int i = global_path_.size() - 1; i >= 0; i--) {
                if (i > 0) {
                    if (global_path_.at(i).direction != global_path_.at(i - 1).direction) {
                        break;
                    }
                }
                path2.push_back(global_path_.at(i));
            }
            reverse(path2.begin(), path2.end());
            double nearest_dis   = std::numeric_limits<double>::max();
            int    nearest_index = -1;
            for (int i = 0; i < path2.size(); i++) {
                double temp_dis = hypot(path2.at(i).x - start_point_.x, path2.at(i).y - start_point_.y);
                if (temp_dis < nearest_dis) {
                    nearest_dis   = temp_dis;
                    nearest_index = i;
                }
            }
            threadLogger_->info("nearest_index:{}", nearest_index);
            path3.insert(path3.end(), global_path_.begin() + path1.size() + nearest_index + 1, global_path_.end());
            threadLogger_->info("path1.size():{}  path2.size():{}  path3.size():{}", path1.size(), path2.size(), path3.size());

            if (IsPath1Success(path1) == PlanResult::Plan_OK) {
                threadLogger_->info("Path1 拟合成功");
                return PlanResult::Plan_OK;
            }
            else if (IsPath3Success(path3) == PlanResult::Plan_OK) {
                threadLogger_->info("Path3 拟合成功");
                return PlanResult::Plan_OK;
            }
            else if (IsPath2Success(path2) == PlanResult::Plan_OK) {
                threadLogger_->info("Path 拟合成功");
            }
            else {
                threadLogger_->info("启动最后的path1拟合，策略更换");
                auto result = IsPath4Success(path1);
                return result;
            }
        }
        else {
            // 非特殊构型参考路径采用以下处理逻辑
            int max_search_index = std::numeric_limits<int>::max();
            // 需要先找到global_path_中排队点、过磅、洗车点的具体索引，hybrida*做路径拟合不能越过这些点
            for (int i = 0; i < global_path_.size(); i++) {
                if (global_path_.at(i).attribute == PointAttribute::weight_point || global_path_.at(i).attribute == PointAttribute::clean_point) {
                    threadLogger_->info("找到过磅、洗车点，索引为{}", i);
                    max_search_index = i;
                    break;
                }
            }

            max_search_index = std::min(max_search_index - 10, (int)global_path_.size() - 1);
            if (max_search_index <= 0) {
                max_search_index = 0;
            }
            int start_point_offset_distance = 4;
            if (load_unload_start_flag) {
                start_point_offset_distance = vehicle_param_.L3;
            }
            int                      end_point_offset_distance = 0;
            int                      search_index              = 0;
            vector<_TrajectoryPoint> temp_traj;
            while (start_point_offset_distance >= 0) {
                my_optimal_path_.start_offset_distance_ = start_point_offset_distance;
                dubins_straight_distance_               = start_point_offset_distance;
                my_optimal_path_.end_offset_distance_   = end_point_offset_distance;
                threadLogger_->info("起点需要拟合，当前直线延伸配置：{} {}", my_optimal_path_.start_offset_distance_, my_optimal_path_.end_offset_distance_);
                threadLogger_->info("结合特殊点位置，最终确定hybridA*前向搜索截至距离为{}", max_search_index);
                temp_traj.clear();
                search_index = 0;
                // 判断拟合模式，JudgeFittingDirection()返回true，表示车辆在参考路径后方，需要先采用Bcack_Fitting模式，不行再采用Start_Front_End_Back模式，反之同理
                if (JudgeFittingDirection(global_path_)) {
                    threadLogger_->info("参考路径位于车头前方，这种情况下采用 Forward_All_Time模式，不行再采用Start_Back_End_Front模式");
                    result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Forward_All_Time, max_search_index, start_point_offset_distance, global_path_);
                    if (result == PlanResult::Plan_OK) {
                        // 成功规划出路径
                        global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
                        global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
                        hybridAstar_path_length_ = temp_traj.size();

                        return result;
                    }
                    if (result == PlanResult::StartPoint_Collision) {
                        return result;
                    }
                }
                else {
                    threadLogger_->info("参考路径位于车头后方，这种情况下先采用Back_Fitting模式，不行再采用Start_Front_End_Back模式");
                    result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Backward_All_Time, max_search_index, start_point_offset_distance, global_path_);
                    if (result == PlanResult::Plan_OK) {
                        // 成功规划出路径
                        global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
                        global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
                        hybridAstar_path_length_ = temp_traj.size();

                        return result;
                    }
                    if (result == PlanResult::StartPoint_Collision) {
                        return result;
                    }
                }
                //   如果代码运行到这里,表明起点直线延伸太长了，得降低直线延长距离
                start_point_offset_distance--;
            }
            // 对于不是从装载点或卸载点出来的调度，如果上述规划都失败，可以采用下述策略再进行规划
            if (!load_unload_start_flag) {
                start_point_offset_distance = 4;
                while (start_point_offset_distance >= 0) {
                    my_optimal_path_.start_offset_distance_ = start_point_offset_distance;
                    dubins_straight_distance_               = start_point_offset_distance;
                    my_optimal_path_.end_offset_distance_   = 0;
                    search_index                            = 0;
                    temp_traj.clear();
                    if (JudgeFittingDirection(global_path_)) {
                        threadLogger_->error("Forward_All_Time模式不行，即将调整拟合规则为 Start_Back_End_Front模式");
                        result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Start_Back_End_Front, max_search_index, start_point_offset_distance, global_path_);
                        if (result == PlanResult::Plan_OK) {
                            // 成功规划出路径
                            global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
                            global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
                            hybridAstar_path_length_ = temp_traj.size();
                            return result;
                        }
                    }
                    else {
                        threadLogger_->error("Forward_All_Time模式不行，即将调整拟合规则为 Start_Back_End_Front模式");
                        result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Start_Front_End_Back, max_search_index, start_point_offset_distance, global_path_);
                        if (result == PlanResult::Plan_OK) {
                            // 成功规划出路径
                            global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
                            global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
                            hybridAstar_path_length_ = temp_traj.size();
                            return result;
                        }
                    }
                    start_point_offset_distance--;
                }
            }
        }
    }
    // 如果代码运行到这里，表面没有规划出路径
    if (load_unload_start_flag) {
        if (result == PlanResult::StartPoint_Collision) {
            return result;
        }
        return PlanResult::Leaving_Load_Point_Too_Close;
    }
    if (result == PlanResult::EndPoint_Collision) {
        return PlanResult::StartPoint_Unreasonable;
    }
    return result;
}
bool Planning::JudgeFittingDirection(vector<_TrajectoryPoint>& input_path) {
    if (input_path.front().direction == 0) {
        threadLogger_->info("正向起步");
        return true;
    }
    else {
        threadLogger_->info("倒车起步");
        return false;
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
bool Planning::PoseVerificationInterface(const _SinglePoint& start_pose, const _SinglePoint& end_pose, const bool flag, const int L, std::vector<curve::Point>& output_path) {
    output_path.clear();
    // threadLogger_->info("PoseVerificationInterface--start_pose:{},{},{}     end_pose:{} ,{},{}", start_pose.x, start_pose.y, start_pose.yaw / M_PI * 180.0, end_pose.x, end_pose.y, end_pose.yaw / M_PI * 180.0);
    curve::Point dubins_start, dubins_end;
    if (flag == 0) {
        auto x = start_pose.x + L * std::cos(start_pose.yaw);
        auto y = start_pose.y + L * std::sin(start_pose.yaw);
        dubins_start.SetX(x);
        dubins_start.SetY(y);
        dubins_start.SetAngle(start_pose.yaw / M_PI * 180.0);
        x = end_pose.x - 0.0 * std::cos(end_pose.yaw);
        y = end_pose.y - 0.0 * std::sin(end_pose.yaw);
        dubins_end.SetX(x);
        dubins_end.SetY(y);
        dubins_end.SetAngle(end_pose.yaw / M_PI * 180.0);
    }
    else if (flag == 1) {
        auto x = end_pose.x + 0.0 * std::cos(end_pose.yaw);
        auto y = end_pose.y + 0.0 * std::sin(end_pose.yaw);
        dubins_start.SetX(x);
        dubins_start.SetY(y);
        dubins_start.SetAngle(end_pose.yaw / M_PI * 180.0);
        x = start_pose.x - L * std::cos(start_pose.yaw);
        y = start_pose.y - L * std::sin(start_pose.yaw);
        dubins_end.SetX(x);
        dubins_end.SetY(y);
        dubins_end.SetAngle(start_pose.yaw / M_PI * 180.0);
    }
    else {
        std::cout << "入参有误！！！" << std::endl;
        return false;
    }
    curve::Dubins dubins;
    dubins.threadLogger_ = threadLogger_;
    if (vehicle_param_.is_light) {
        dubins.SetRadius(vehicle_param_.wheel_base / tan(vehicle_param_.light_forward_max_steering));
    }
    else {
        dubins.SetRadius(vehicle_param_.wheel_base / tan(vehicle_param_.heavy_forward_max_steering));
    }
    // threadLogger_->info("dubins_start:({},{},{})   L:{}   dubins radius:{}", dubins_start.GetX(), dubins_start.GetY(), dubins_start.GetAngle(), L, dubins.GetRadius());
    bool is_reasonable = dubins.GetDubinsPath(dubins_start, dubins_end, output_path);
    // 将path和直线延长的部分拼接到一起
    curve::Point temp_point;
    if (flag == 0) {
        for (int i = 1; i <= L; i++) {
            temp_point.SetX(dubins_start.GetX() - i * std::cos(start_pose.yaw));
            temp_point.SetY(dubins_start.GetY() - i * std::sin(start_pose.yaw));
            temp_point.SetAngle(start_pose.yaw / M_PI * 180.0);
            output_path.insert(output_path.begin(), temp_point);
        }
    }
    else {
        for (int i = 1; i <= L; i++) {
            temp_point.SetX(dubins_end.GetX() + i * std::cos(start_pose.yaw));
            temp_point.SetY(dubins_end.GetY() + i * std::sin(start_pose.yaw));
            temp_point.SetAngle(dubins_end.GetAngle() / M_PI * 180.0);
            output_path.push_back(temp_point);
        }
        // 对output_path倒序
        std::reverse(output_path.begin(), output_path.end());
    }


    if (is_reasonable == false) {
        // threadLogger_->info("dubins预校验失败");
        return false;
    }
    for (int i = 0; i < output_path.size(); i++) {
        if (flag == 1) {
            if (collison_check_.IsVehicleCollisionWithAll(Point(output_path.at(i).GetX(), output_path.at(i).GetY(), 0, output_path.at(i).GetAngle() / 180.0 * M_PI, static_cast<GlobalPlanning::MotionDirection>(1)))) {
                // threadLogger_->info("第 {} 个路径点({},{},{})碰撞检测失败", i, output_path.at(i).GetX(), output_path.at(i).GetY(), output_path.at(i).GetAngle());
                // break;
                return false;
            }
        }
        else {
            if (collison_check_.IsVehicleCollisionWithAll(Point(output_path.at(i).GetX(), output_path.at(i).GetY(), 0, output_path.at(i).GetAngle() / 180.0 * M_PI, static_cast<GlobalPlanning::MotionDirection>(0)))) {
                // threadLogger_->info("第 {} 个路径点({},{},{})碰撞检测失败", i, output_path.at(i).GetX(), output_path.at(i).GetY(), output_path.at(i).GetAngle());
                // break;
                return false;
            }
        }
    }
    threadLogger_->info("dubins碰撞检测成功");
    return true;
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
    vector<_TrajectoryPoint>    origin_path = input_path;
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

    unsigned int out_iterations = 0, in_iterations = 0;
    double       a1, a2, b1, b2, c1, c2, d1, d2, e1, e2;


    // 梯度下降法迭代优化
    while (out_iterations++ < 10) {
        /* code */

        input_path    = origin_path;
        in_iterations = 0;
        while (in_iterations++ < max_opti_num) {
            for (unsigned int i = 2; i < input_path.size() - 2; i++) {
                if (fixpoint_set.count(i)) {
                    threadLogger_->info("第 {} 个点跳过", i);
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


                input_path.at(i).x -= 0.2 * (e1 - 4 * d1 + 6 * c1 - 4 * b1 + a1);
                input_path.at(i).y -= 0.2 * (e2 - 4 * d2 + 6 * c2 - 4 * b2 + a2);
            }
        }
        auto curvature_exceed = CurvatureCheck(input_path);
        threadLogger_->info("curvature_exceed.size():{}", curvature_exceed.size());
        if (!curvature_exceed.empty()) // 若无碰撞且曲率不超标
        {
            for (unsigned int i = 0; i < curvature_exceed.size(); i++) {
                unsigned int index = curvature_exceed.at(i);
                fixpoint_set.insert(index);
            }
        }
        else {
            break;
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
        case PlanResult::StartPoint_Unreasonable:
            error_type_ = ErrorType::StartPoint_Unreasonable;
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
        case PlanResult::Start_Point_Too_Far:
            error_type_ = ErrorType::Start_Point_Too_Far;
            break; // 可选的
    }
}


vector<unsigned int> Planning::CurvatureCheck(vector<_TrajectoryPoint>& input_path) {
    CurvatureCal(input_path);


    double curvature_threshold = 1.0;

    vector<unsigned int> curvature_exceed_point;
    curvature_exceed_point.clear();
    for (unsigned int i = 1; i < input_path.size() - 1; i++) {
        double curvature = input_path.at(i).curvature;
        if (input_path.at(i).direction == MotionDirection::Forward) {
            if (vehicle_param_.is_light) {
                curvature_threshold = tan(vehicle_param_.light_forward_max_steering) / vehicle_param_.wheel_base;
            }
            else {
                curvature_threshold = tan(vehicle_param_.heavy_forward_max_steering) / vehicle_param_.wheel_base;
            }
        }
        else {
            if (vehicle_param_.is_light) {
                curvature_threshold = tan(vehicle_param_.light_backward_max_steering) / vehicle_param_.wheel_base;
            }
            else {
                curvature_threshold = tan(vehicle_param_.heavy_backward_max_steering) / vehicle_param_.wheel_base;
            }
        }
        if (fabs(curvature) > curvature_threshold + 1e-2) {
            threadLogger_->info("第 {} 个点曲率超标，点坐标为({},{}),曲率为{},此点将被列为anchor点,> {}", i, input_path.at(i).x, input_path.at(i).y, input_path.at(i).curvature, curvature_threshold);
            curvature_exceed_point.push_back(i);
            curvature_exceed_point.push_back(i - 1);
            curvature_exceed_point.push_back(i + 1);
        }
    }
    return curvature_exceed_point;
}

bool Planning::IsForwardAndBackwardReferencePath() {
    bool flag = false;
    for (int i = 0; i < global_path_.size() - 1; i++) {
        if (global_path_.at(i).direction != global_path_.at(i + 1).direction) {
            flag = true;
            break;
        }
    }
    if (flag == true && global_path_.size() < 100) {
        return true;
    }
    return false;
}
PlanResult Planning::IsPath1Success(vector<_TrajectoryPoint>& input_path) {
    threadLogger_->info("");
    threadLogger_->info("enter IsPath1Success function");
    PlanResult result           = PlanResult::Plan_OK;
    int        max_search_index = std::numeric_limits<int>::max();
    max_search_index            = std::min(max_search_index - 10, (int)input_path.size() - 1);
    if (max_search_index <= 0) {
        max_search_index = 0;
    }
    int start_point_offset_distance = 4;

    int                      end_point_offset_distance = 0;
    int                      search_index              = 0;
    vector<_TrajectoryPoint> temp_traj;
    while (start_point_offset_distance >= 0) {
        my_optimal_path_.start_offset_distance_ = start_point_offset_distance;
        dubins_straight_distance_               = start_point_offset_distance;
        my_optimal_path_.end_offset_distance_   = end_point_offset_distance;
        threadLogger_->info("起点需要拟合，当前直线延伸配置：{} {}", my_optimal_path_.start_offset_distance_, my_optimal_path_.end_offset_distance_);
        threadLogger_->info("结合特殊点位置，最终确定hybridA*前向搜索截至距离为{}", max_search_index);
        temp_traj.clear();
        search_index = 0;
        // 判断拟合模式，JudgeFittingDirection()返回true，表示车辆在参考路径后方，需要先采用Bcack_Fitting模式，不行再采用Start_Front_End_Back模式，反之同理
        if (JudgeFittingDirection(input_path)) {
            threadLogger_->info("车头位于参考路径后方，这种情况下采用 Forward_All_Time模式");
            result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Forward_All_Time, max_search_index, start_point_offset_distance, input_path);
            if (result == PlanResult::Plan_OK) {
                // 成功规划出路径
                global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
                global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
                hybridAstar_path_length_ = temp_traj.size();
                return result;
            }
        }
        else {
            threadLogger_->info("车头位于参考路径前方，这种情况下采用Back_Fitting模式");
            result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Backward_All_Time, max_search_index, start_point_offset_distance, input_path);
            if (result == PlanResult::Plan_OK) {
                // 成功规划出路径
                global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
                global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
                hybridAstar_path_length_ = temp_traj.size();
                return result;
            }
        }
        //   如果代码运行到这里,表明起点直线延伸太长了，得降低直线延长距离
        start_point_offset_distance--;
    }
    return result;
}
PlanResult Planning::IsPath2Success(vector<_TrajectoryPoint>& input_path) {
    threadLogger_->info("");
    threadLogger_->info("enter IsPath2Success function");
    PlanResult result           = PlanResult::Plan_OK;
    int        max_search_index = std::numeric_limits<int>::max();
    max_search_index            = std::min(max_search_index - 10, (int)input_path.size() - 1);
    if (max_search_index <= 0) {
        max_search_index = 0;
    }
    int start_point_offset_distance = 4;

    int                      end_point_offset_distance = 0;
    int                      search_index              = 0;
    vector<_TrajectoryPoint> temp_traj;
    while (start_point_offset_distance >= 0) {
        my_optimal_path_.start_offset_distance_ = start_point_offset_distance;
        dubins_straight_distance_               = start_point_offset_distance;
        my_optimal_path_.end_offset_distance_   = end_point_offset_distance;
        threadLogger_->info("起点需要拟合，当前直线延伸配置：{} {}", my_optimal_path_.start_offset_distance_, my_optimal_path_.end_offset_distance_);
        threadLogger_->info("结合特殊点位置，最终确定hybridA*前向搜索截至距离为{}", max_search_index);
        temp_traj.clear();
        search_index = 0;
        // 判断拟合模式，JudgeFittingDirection()返回true，表示车辆在参考路径后方，需要先采用Bcack_Fitting模式，不行再采用Start_Front_End_Back模式，反之同理
        if (JudgeFittingDirection(input_path)) {
            threadLogger_->info("车头位于参考路径后方，这种情况下采用 Start_Front_End_Back模式");
            result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Start_Front_End_Back, max_search_index, start_point_offset_distance, input_path);
            if (result == PlanResult::Plan_OK) {
                // 成功规划出路径
                global_path_ = input_path;
                global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
                global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
                hybridAstar_path_length_ = temp_traj.size();
                return result;
            }
        }
        else {
            threadLogger_->info("车头位于参考路径前方，这种情况下先采用Start_Back_End_Front模式");
            result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Start_Back_End_Front, max_search_index, start_point_offset_distance, input_path);
            if (result == PlanResult::Plan_OK) {
                // 成功规划出路径
                global_path_ = input_path;
                global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
                global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
                hybridAstar_path_length_ = temp_traj.size();
                return result;
            }
        }
        //   如果代码运行到这里,表明起点直线延伸太长了，得降低直线延长距离
        start_point_offset_distance--;
    }
    return result;
}
PlanResult Planning::IsPath3Success(vector<_TrajectoryPoint>& input_path) {
    threadLogger_->info("");
    threadLogger_->info("enter IsPath3Success function");
    PlanResult result           = PlanResult::Plan_OK;
    int        max_search_index = std::numeric_limits<int>::max();


    max_search_index = std::min(max_search_index - 10, (int)input_path.size() - 1);
    if (max_search_index <= 0) {
        max_search_index = 0;
    }
    int start_point_offset_distance = 4;

    int                      end_point_offset_distance = 0;
    int                      search_index              = 0;
    vector<_TrajectoryPoint> temp_traj;
    while (start_point_offset_distance >= 0) {
        my_optimal_path_.start_offset_distance_ = start_point_offset_distance;
        dubins_straight_distance_               = start_point_offset_distance;
        my_optimal_path_.end_offset_distance_   = end_point_offset_distance;
        threadLogger_->info("起点需要拟合，当前直线延伸配置：{} {}", my_optimal_path_.start_offset_distance_, my_optimal_path_.end_offset_distance_);
        threadLogger_->info("结合特殊点位置，最终确定hybridA*前向搜索截至距离为{}", max_search_index);
        temp_traj.clear();
        search_index = 0;
        // 判断拟合模式，JudgeFittingDirection()返回true，表示车辆在参考路径后方，需要先采用Bcack_Fitting模式，不行再采用Start_Front_End_Back模式，反之同理
        if (JudgeFittingDirection(input_path)) {
            threadLogger_->info("车头位于参考路径后方，这种情况下采用 Forward_All_Time模式");
            result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Forward_All_Time, max_search_index, start_point_offset_distance, input_path);
            if (result == PlanResult::Plan_OK) {
                // 成功规划出路径
                global_path_ = input_path;
                global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
                global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
                hybridAstar_path_length_ = temp_traj.size();
                return result;
            }
        }
        else {
            threadLogger_->info("车头位于参考路径前方，这种情况下先采用Back_Fitting模式");
            result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Backward_All_Time, max_search_index, start_point_offset_distance, input_path);
            if (result == PlanResult::Plan_OK) {
                // 成功规划出路径
                global_path_ = input_path;
                global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
                global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
                hybridAstar_path_length_ = temp_traj.size();
                return result;
            }
        }
        //   如果代码运行到这里,表明起点直线延伸太长了，得降低直线延长距离
        start_point_offset_distance--;
    }
    return result;
}
PlanResult Planning::IsPath4Success(vector<_TrajectoryPoint>& input_path) {
    threadLogger_->info("");
    threadLogger_->info("enter IsPath4Success function");
    PlanResult result           = PlanResult::Plan_OK;
    int        max_search_index = std::numeric_limits<int>::max();
    max_search_index            = std::min(max_search_index - 10, (int)input_path.size() - 1);
    if (max_search_index <= 0) {
        max_search_index = 0;
    }
    int start_point_offset_distance = 4;

    int                      end_point_offset_distance = 0;
    int                      search_index              = 0;
    vector<_TrajectoryPoint> temp_traj;
    while (start_point_offset_distance >= 0) {
        my_optimal_path_.start_offset_distance_ = start_point_offset_distance;
        dubins_straight_distance_               = start_point_offset_distance;
        my_optimal_path_.end_offset_distance_   = end_point_offset_distance;
        threadLogger_->info("起点需要拟合，当前直线延伸配置：{} {}", my_optimal_path_.start_offset_distance_, my_optimal_path_.end_offset_distance_);
        threadLogger_->info("结合特殊点位置，最终确定hybridA*前向搜索截至距离为{}", max_search_index);
        temp_traj.clear();
        search_index = 0;
        // 判断拟合模式，JudgeFittingDirection()返回true，表示车辆在参考路径后方，需要先采用Bcack_Fitting模式，不行再采用Start_Front_End_Back模式，反之同理
        if (JudgeFittingDirection(input_path)) {
            threadLogger_->info("车头位于参考路径后方，这种情况下采用 Start_Back_End_Front 模式");
            result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Start_Back_End_Front, max_search_index, start_point_offset_distance, input_path);
            if (result == PlanResult::Plan_OK) {
                // 成功规划出路径
                global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
                global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
                hybridAstar_path_length_ = temp_traj.size();
                return result;
            }
        }
        else {
            threadLogger_->info("车头位于参考路径前方，这种情况下采用 Start_Front_End_Back 模式");
            result = ProgressiveHybirdAStar(start_point_, search_index, temp_traj, PlanRule::Start_Front_End_Back, max_search_index, start_point_offset_distance, input_path);
            if (result == PlanResult::Plan_OK) {
                // 成功规划出路径
                global_path_.erase(global_path_.begin(), global_path_.begin() + search_index + 1);
                global_path_.insert(global_path_.begin(), temp_traj.begin(), temp_traj.end());
                hybridAstar_path_length_ = temp_traj.size();
                return result;
            }
        }
        //   如果代码运行到这里,表明起点直线延伸太长了，得降低直线延长距离
        start_point_offset_distance--;
    }
    return result;
}

// 检查全局路径是否与所有地图边界发生碰撞
bool Planning::IsGlobalPathCollision() {
    // 1. 构造Bound类型边界
    Bound                   all_map_borders;
    std::vector<Coordinate> border_coords;
    for (const auto& bp : map_border_) {
        Coordinate temp_point;
        temp_point.x = bp.x;
        temp_point.y = bp.y;
        temp_point.z = bp.z;
        border_coords.push_back(temp_point);
    }
    all_map_borders.push_back(border_coords);


    // 2. 初始化碰撞检测参数和边界
    collison_check_.InitParam(vehicle_param_);
    collison_check_.InitBoundMap(all_map_borders);


    // 3. 检查global_path_每个点
    for (size_t i = 0; i < global_path_.size(); ++i) {
        const auto& pt = global_path_[i];
        Point       check_point(pt.x, pt.y, pt.z, pt.yaw / 180.0 * M_PI, static_cast<MotionDirection>(pt.direction));
        if (collison_check_.IsVehicleCollisionWithAll(check_point)) {
            threadLogger_->info("全局路径与地图边界发生碰撞，碰撞点索引：{} {} {}", pt.x, pt.y, pt.yaw);
            return false;
        }
    }
    threadLogger_->info("全局路径与地图边界未发生碰撞");
    return true;
}