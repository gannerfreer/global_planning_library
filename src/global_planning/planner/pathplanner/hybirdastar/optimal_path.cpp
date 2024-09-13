/***************************************************/
/*				Author: Biao Xu				       */
/*				Contact: dr_xubiao@163.com		   */
/*				Last update: 2020-04-15			   */
/***************************************************/
/*
    Description: The header file for C++ class OptimalPath.
*/

#include "optimal_path.h"

#include "../../../math/helper.h"
#include "../../../math/opti/path_opti.h"
#include "../../../time/StringHelper.h"
#include "../../../time/TimeHelper.h"
using namespace GlobalPlanning;

/**
 *@brief: 路径规划接口函数
 *@param
 *return
 */
PlanResult OptimalPath::SearchGlobalPath(const Point start, const Point end, const Bound& road_bound, const Bound& obstacle_bound, const _VehicleParam m_vehicle_param, Path& final_path, long long time_threshold, const PlanRule plan_path_rule) {
    m_vehicle_param_ = m_vehicle_param;
    my_r_s_curve.Init(m_vehicle_param_);
    my_r_s_curve_h.Init(m_vehicle_param_);

    my_r_s_curve.threadLogger_   = threadLogger_;
    my_r_s_curve_h.threadLogger_ = threadLogger_;
    dubins_.SetParam(m_vehicle_param_.radious, end, plan_path_rule);
    plan_path_rule_ = plan_path_rule;

    utility::CTimeLog timelog("SearchGlobalPath");
    InitData(start, end, road_bound, obstacle_bound);
    timelog.AddLog("InitData");

    collison_check_.InitParam(m_vehicle_param_);
    collison_check_.InitBoundMap(road_bound_);
    collison_check_.InitObstacleMap(obstacle_bound_);
    timelog.AddLog("InitBoundMap");

    GenerateBoundSet();
    threadLogger_->info("GenerateBoundSet");
    timelog.AddLog("GenerateBoundSet");


    nodes2D_set_.clear();
    h_cost_map_.clear();
    nodes2D_map_.clear();

    // 终点区域碰撞判断
    if (true == collison_check_.IsVehicleCollision(end_)) {
        threadLogger_->info("终点碰撞检测不通过");

        return PlanResult::EndPoint_Infeasible;
    }
    if (true == collison_check_.IsVehicleCollision(actual_start_)) {
        threadLogger_->info("起点碰撞检测不通过");

        return PlanResult::StartPoint_Infeasible;
    }
    timelog.AddLog("IsVehicleCollision");
    // threadLogger_->info( "plan_path_rule_:" << static_cast<float>(plan_path_rule) );

    if (collison_check_.IsVehicleCollision(end_r_) || plan_path_rule_ == PlanRule::Backward_To_End || plan_path_rule_ == PlanRule::Backward_All_Time) {
        if (collison_check_.IsVehicleCollision(end_r_)) {
            threadLogger_->info("终点碰撞检测不通过(end_r_)");
        }
        else {
            threadLogger_->info("plan_path_rule_ == PlanRule::Backward_To_End");
        }

        threadLogger_->info(" fitting_direction_ = FittingDirection::Backward_Fitting");

        fitting_direction_ = FittingDirection::Backward_Fitting;
    }
    else if (collison_check_.IsVehicleCollision(end_f_) || plan_path_rule_ == PlanRule::Forward_To_End || plan_path_rule_ == PlanRule::Forward_All_Time) {
        if (collison_check_.IsVehicleCollision(end_f_)) {
            threadLogger_->info("终点碰撞检测不通过(end_f_)");
        }
        else {
            threadLogger_->info("plan_path_rule_ == PlanRule::Forward_To_End");
        }
        threadLogger_->info(" fitting_direction_ = FittingDirection::Forword_Fitting");

        fitting_direction_ = FittingDirection::Forword_Fitting;
    }
    else {
        threadLogger_->info("  fitting_direction_ = FittingDirection::Both_Fitting");

        fitting_direction_ = FittingDirection::Both_Fitting;
    }
    // threadLogger_->info( "FittingDirection:" << static_cast<int>(fitting_direction_) );
    // 混合A*搜索 确定调整后的起点、终点、前向终点、后向终点、区域i边界后、拟合方式后开始干活
    // threadLogger_->info( "规划终点符合碰撞要求,前延点/后延点也符合碰撞要求,开始hybird A*拟合" );
    // cout << "调用A*" << endl;
    PlanResult result = AStarPath(final_path, time_threshold);
    // cout << "line121" << endl;
    timelog.AddLog("AStarPath");
    threadLogger_->info(timelog.GetLog());
    return result;
}


/**
 *@brief: 数据初始化函数，将数据减小，放置精度丢失
 *@param
 *return
 */
void OptimalPath::InitData(Point start, Point end, const Bound& road_bound, const Bound& obstacle_bound) {
    // 以起点和终点的中心点作为原点
    midpoint_.x = (start.x + end.x) / 2;
    midpoint_.y = (start.y + end.y) / 2;
    midpoint_.z = 0;

    start_ = start;
    start_.x -= midpoint_.x;
    start_.y -= midpoint_.y;

    end_ = end;
    end_.x -= midpoint_.x;
    end_.y -= midpoint_.y;
    // threadLogger_->info("start_:{} {}", m_vehicle_param_.end_offset_distance);
    // threadLogger_->info("end_", m_vehicle_param_.end_offset_distance);
    threadLogger_->info("终点进行{}米的延伸", m_vehicle_param_.end_offset_distance);

    // 计算终点前直线补偿点位置
    end_f_.angle = end_.angle;
    end_f_.x     = end_.x + m_vehicle_param_.end_offset_distance * cos(end_.angle);
    end_f_.y     = end_.y + m_vehicle_param_.end_offset_distance * sin(end_.angle);

    // 计算终点后直线补偿点位置
    end_r_.angle = end_.angle;
    end_r_.x     = end_.x - m_vehicle_param_.end_offset_distance * cos(end_.angle);
    end_r_.y     = end_.y - m_vehicle_param_.end_offset_distance * sin(end_.angle);

    // 计算平移后地图边界点
    road_bound_.clear();
    for (unsigned int i = 0; i < road_bound.size(); ++i) {
        vector<Coordinate> temp_bound = road_bound.at(i);
        vector<Coordinate> temp_bound_2;
        for (int j = 0; j < temp_bound.size(); ++j) {
            Coordinate temp_point;
            temp_point.z = 0;
            temp_point.x = temp_bound.at(j).x - midpoint_.x;
            temp_point.y = temp_bound.at(j).y - midpoint_.y;
            temp_bound_2.push_back(temp_point);
        }
        road_bound_.push_back(temp_bound_2);
    }

    // 计算平移后障碍物边界点
    obstacle_bound_.clear();
    for (unsigned int i = 0; i < obstacle_bound.size(); ++i) {
        vector<Coordinate> temp_bound = obstacle_bound.at(i);
        vector<Coordinate> temp_bound_2;
        for (int j = 0; j < temp_bound.size(); ++j) {
            Coordinate temp_point;
            temp_point.z = 0;
            temp_point.x = temp_bound.at(j).x - midpoint_.x;
            temp_point.y = temp_bound.at(j).y - midpoint_.y;
            temp_bound_2.push_back(temp_point);
        }
        obstacle_bound_.push_back(temp_bound_2);
    }
    actual_start_ = start_;
    if (plan_path_rule_ == PlanRule::Backward_To_End || plan_path_rule_ == PlanRule::Forward_All_Time) {
        threadLogger_->info("起点进行{}米的延伸", m_vehicle_param_.start_offset_distance);
        actual_start_ = start_;
        start_.x      = start_.x + m_vehicle_param_.start_offset_distance * cos(start_.angle);
        start_.y      = start_.y + m_vehicle_param_.start_offset_distance * sin(start_.angle);
    }

    if (plan_path_rule_ == PlanRule::Backward_All_Time) {
        threadLogger_->info("纯倒车，起点向后进行{}米的延伸", m_vehicle_param_.start_offset_distance);
        actual_start_ = start_;
        start_.x      = start_.x - m_vehicle_param_.start_offset_distance * cos(start_.angle);
        start_.y      = start_.y - m_vehicle_param_.start_offset_distance * sin(start_.angle);
    }
}

/**
 *@brief: 混合A*搜索主函数
 *@param
 *return path
 */
PlanResult OptimalPath::AStarPath(Path& path, long long timeThreshold) {
    // 以下3行代码用于超时退出
    utility::CTimeClock init_time;
    InitOpenClose();                                                                        // 初始化open集和close集
    long long init_time_end = utility::CTimeHelper::GetTimeIntervalMicroseconds(init_time); // 开始时间精确到微秒
    threadLogger_->info("InitOpenClose 耗时:{} ms", init_time_end * 0.001);


    Vertex3D           current_point;
    unsigned long long time_spend_collsion = 0, time_spend_dynamic = 0, time_spend_other = 0, expand_time_collision = 0, expand_time_dynamic = 0, expand_time_other = 0;
    long long          total_time                = 0;
    long long          expand_time               = 0;
    long long          total_time_Expand_dynamic = 0;
    int                sum                       = 0;
    All                                          = 0;
    utility::CTimeClock start_time;
    threadLogger_->info("hybirdA*搜索启动");
    while (!open_map_f_.empty()) {
        long long cal_time = utility::CTimeHelper::GetTimeIntervalMicroseconds(start_time); // 开始时间精确到微秒
        threadLogger_->info("open_map_f_.size():{}", open_map_f_.size());
        if (cal_time > timeThreshold) // 若超过最大迭代次数则直接返回
        {
            threadLogger_->info("A star overtime!, timeThreshold:{} ms,AStarPath while循环已经被调用: {} 次", timeThreshold * 0.001, sum);

            threadLogger_->info("拓展总用时: {} ms", 0.001 * expand_time);
            threadLogger_->info("拓展-运动学搜索用时: {} ms", 0.001 * expand_time_dynamic);
            threadLogger_->info("拓展-碰撞检测用时: {} ms", 0.001 * expand_time_collision);
            threadLogger_->info("拓展-其他步骤用时: {} ms", 0.001 * expand_time_other);

            threadLogger_->info("拓展节点统计，open_map_.sie():{}  close_map_.size():{}", open_map_.size(), close_map_.size());

            return PlanResult::Plan_Overtime;
        }

        // 从优先队列open集中取出第一个点索引，及取出f值最小的点索引
        unsigned long long current_point_index = open_map_f_.begin()->second.id;
        current_point                          = open_map_[current_point_index]; // 通过key值获取当前点
        // threadLogger_->info("current_point:{},{}", current_point.x, current_point.y);
        open_map_.erase(current_point_index);
        open_map_f_.erase(open_map_f_.begin()); // 将该点从open集中删除
        close_map_[current_point_index] = current_point;

        // 判断能否可以rs曲线拟合成功

        sum++;


        if (true == IfExitAStar(current_point)) {
            total_time = utility::CTimeHelper::GetTimeIntervalMicroseconds(start_time);
            threadLogger_->info("搜索总计用时: {} ms, (multimap)open_map_f 一共弹出{}次,close_map_.size():{},open_map_.size():{}", 0.001 * total_time, sum, close_map_.size(), open_map_.size());
            threadLogger_->info("拓展总用时: {} ms", 0.001 * expand_time);
            threadLogger_->info("拓展-运动学搜索用时: {} ms", 0.001 * expand_time_dynamic);
            threadLogger_->info("拓展-碰撞检测用时: {} ms", 0.001 * expand_time_collision);
            threadLogger_->info("拓展-其他步骤用时: {} ms", 0.001 * expand_time_other);
            threadLogger_->info("拓展节点统计，open_map_.sie():{}  close_map_.size():{}", open_map_.size(), close_map_.size());
            total_time  = 0;
            expand_time = 0;
            sum         = 0;
            break;
        }

        // 基于当前点进行节点拓展
        utility::CTimeClock start_time_expand;
        // threadLogger_->info("FindExpandVertex");
        FindExpandVertex(current_point, time_spend_dynamic, time_spend_collsion, time_spend_other);
        expand_time_collision += time_spend_collsion;
        expand_time_dynamic += time_spend_dynamic;
        expand_time_other += time_spend_other;
        expand_time += utility::CTimeHelper::GetTimeIntervalMicroseconds(start_time_expand);
    }


    if (open_map_f_.empty()) // 如果open_set为空表示无法搜索到可行路径
    {
        threadLogger_->info("Cannot find feasible path!");
        return PlanResult::Plan_Infeasible;
    }
    threadLogger_->info("Find feasible path Successfuly!");

    TracePath(current_point); // 混合A*路径回溯
    threadLogger_->info("TracePath() Successfuly!");
    PathIntegration(); // 将混合A*搜索路径、RS曲线拟合路径与终点补偿的直线路径整合
    threadLogger_->info("PathIntegration() Successfuly!");

    // 保存路点，并打印出来
    // std::ofstream file_out;
    // file_out.open("yaw.txt", std::ios::app);
    // for (size_t index = 0; index < path_a_star_.size(); index++) {
    //     file_out << path_a_star_.at(index).angle << endl;
    // }
    // file_out.close();

    Path temp_path;
    temp_path = path_a_star_; // 弧度
    removeDuplicates(temp_path, path_a_star_);
    threadLogger_->info("removeDuplicates() Successfuly!");

    // 保存路点，并打印出来
    // std::ofstream file_out;
    // file_out.open("init_path.txt", std::ios::out);
    // for (size_t index = 0; index < path_a_star_.size(); index++)
    // {
    //     file_out << path_a_star_.at(index).x << " " << path_a_star_.at(index).y << endl;
    // }
    // file_out.close();

    utility::CTimeClock start_time_opti;
    threadLogger_->info("Hybird A*运行完成，并将其与RS曲线连接");

    // 平滑前打印路径曲率
    threadLogger_->info("path_a_star_.size():{}", path_a_star_.size());
    // cout << "path_a_star_.size():" << path_a_star_.size() << endl;
    CalCurv(path_a_star_);


    // 路径优化，得到最终的path
    Path_Opti my_path_opti;

    my_path_opti.OptimizePath(path_a_star_, path, collison_check_, m_vehicle_param_);
    threadLogger_->info("OptimizePath() Successfuly!");


    long long cal_time2 = utility::CTimeHelper::GetTimeIntervalMicroseconds(start_time_opti);
    threadLogger_->info("路径优化完成，用时: {} ms ", 0.001 * cal_time2);

    utility::CTimeClock start_time_dis;
    // GetLeftAndRightDistance(path);

    threadLogger_->info("GetLeftAndRightDistance() Successfuly!");
    long long cal_time3 = utility::CTimeHelper::GetTimeIntervalMicroseconds(start_time_dis);
    threadLogger_->info("获取左右边界用时: {} ms", 0.001 * cal_time3);

    RestoreData(path); // 数据恢复

    threadLogger_->info("RestoreData() Successfuly!");

    return PlanResult::Plan_OK;
}
bool OptimalPath::removeDuplicates(Path& input, Path& result) {
    result.clear();
    result.push_back(input.front());
    for (int i = 1; i < input.size(); i++) {
        if (fabs(input.at(i).x - input.at(i - 1).x) <= 1e-6 && fabs(input.at(i).y - input.at(i - 1).y) <= 1e-6) {
            continue;
        }
        result.push_back(input.at(i));
    }
}
// void OptimalPath::GetLeftAndRightDistance(Path& final_path) {
//     IntCoordinate temp_point_left, temp_point_right;
//     double       max_distance = 15;
//     for (int i = 0; i < final_path.size(); i++) {
//         if (i % 5 != 0) {
//             final_path.at(i).left  = final_path.at(i - 1).left;
//             final_path.at(i).right = final_path.at(i - 1).right;
//             continue;
//         }
//         final_path.at(i).left = max_distance;
//         for (double d = 1.0; d < max_distance; d += m_vehicle_param_.grid_dist / 2.0) {
//             temp_point_left.x = final_path.at(i).x - d * sin(final_path.at(i).angle);
//             temp_point_left.y = final_path.at(i).y + d * cos(final_path.at(i).angle);
//             if (true == IsBoundGrid(temp_point_left)) {
//                 final_path.at(i).left = d;
//                 break;
//             }
//         }
//         final_path.at(i).right = max_distance;
//         for (double d = 1.0; d < max_distance; d += m_vehicle_param_.grid_dist / 2.0) {
//             temp_point_right.x = final_path.at(i).x + d * sin(final_path.at(i).angle);
//             temp_point_right.y = final_path.at(i).y - d * cos(final_path.at(i).angle);
//             if (true == IsBoundGrid(temp_point_right)) {
//                 final_path.at(i).right = d;
//                 break;
//             }
//         }
//     }
// }

/**
 *@brief: 初始化CLOSE集和OPEN集
 *@param
 *return
 */
void OptimalPath::InitOpenClose() {
    // 清空相关容器
    close_map_.clear();
    open_map_.clear();
    open_map_f_.clear();

    // open中分别存入起点的前进构型和后退构型
    Vertex3D temp_vertex;
    temp_vertex.x         = start_.x;
    temp_vertex.y         = start_.y;
    temp_vertex.z         = start_.z;
    temp_vertex.angle     = start_.angle;
    temp_vertex.parent_id = 0;
    temp_vertex.g         = 0;
    temp_vertex.direction = Forward;

    CalHValue(temp_vertex); // 查询起点H值


    temp_vertex.f = temp_vertex.h + temp_vertex.g;

    temp_vertex.id            = Vertex2Hash(temp_vertex);
    open_map_[temp_vertex.id] = temp_vertex;
    open_map_f_.insert(make_pair(temp_vertex.f, temp_vertex));
    temp_vertex.parent_id = 0;
    temp_vertex.g         = 0;
    temp_vertex.direction = Backward; // 倒退

    CalHValue(temp_vertex);


    temp_vertex.f = temp_vertex.h + temp_vertex.g;

    temp_vertex.id            = Vertex2Hash(temp_vertex);
    open_map_[temp_vertex.id] = temp_vertex;
    open_map_f_.insert(make_pair(temp_vertex.f, temp_vertex));
}

/**
 *@brief: 判断是否退出A*算法
 *@param
 *return min_point
 */
bool OptimalPath::IfExitAStar(const Vertex3D& min_point) {
    // 判断是否可以进行RS曲线拟合
    double dis = hypot(min_point.x - end_.x, min_point.y - end_.y);

    if (dis < m_vehicle_param_.max_fitting_radius) {
        All++;
        flag_dubins_ = true;
        Point temp_start_point;
        temp_start_point.x         = min_point.x;
        temp_start_point.y         = min_point.y;
        temp_start_point.z         = min_point.z;
        temp_start_point.angle     = min_point.angle;
        temp_start_point.direction = min_point.direction;

        // 根据fitting_direction_值选择合适的RS拟合方式

        switch (fitting_direction_) {
            case FittingDirection::Backward_Fitting:

                if ((true == my_r_s_curve.PlanRSPath(temp_start_point, end_f_, path_r_s_, plan_path_rule_)) && (MotionDirection::Backward == path_r_s_.back().direction)) {
                    if (false == collison_check_.IsRSPathCollision(path_r_s_)) {
                        threadLogger_->info("RS曲线Backward_Fitting oneshot成功，一共oneshot了 {}  次 ", All);

                        return true;
                    }
                }
                else {
                    threadLogger_->info("RS曲线规划失败");
                }
                break;
            case FittingDirection::Forword_Fitting:

                if ((true == my_r_s_curve.PlanRSPath(temp_start_point, end_r_, path_r_s_, plan_path_rule_)) && (MotionDirection::Forward == path_r_s_.back().direction)) {
                    if (false == collison_check_.IsRSPathCollision(path_r_s_)) {
                        threadLogger_->info("RS曲线Forword_Fitting成功，一共oneshot了{}次 ", All);

                        return true;
                    }
                    else {
                        threadLogger_->info("RS曲线碰撞检测失败");
                    }
                }
                else {
                    threadLogger_->info("RS曲线规划失败");
                }
                break;
            case FittingDirection::Both_Fitting:

                if ((true == my_r_s_curve.PlanRSPath(temp_start_point, end_r_, path_r_s_, plan_path_rule_)) && (MotionDirection::Forward == path_r_s_.back().direction)) {
                    if (false == collison_check_.IsRSPathCollision(path_r_s_)) {
                        threadLogger_->info("RS曲线Forword_Fitting成功，一共oneshot了{}次 ", All);

                        fitting_direction_ = FittingDirection::Forword_Fitting;
                        return true;
                    }
                }
                else if ((true == my_r_s_curve.PlanRSPath(temp_start_point, end_f_, path_r_s_, plan_path_rule_)) && (MotionDirection::Backward == path_r_s_.back().direction)) {
                    if (false == collison_check_.IsRSPathCollision(path_r_s_)) {
                        threadLogger_->info("RS曲线Backward_Fitting oneshot成功，一共oneshot了 {}  次 ", All);

                        fitting_direction_ = FittingDirection::Backward_Fitting;
                        return true;
                    }
                }

            default:
                break;
        }
    }
    return false;
}

/**
 *@brief: 找到所有拓展节点
 *@param
 *return
 */
void OptimalPath::FindExpandVertex(const Vertex3D& current_point, unsigned long long& time_dy, unsigned long long& time_collsion, unsigned long long& time_other) {
    // auto start_time = ros::Time::now();
    bool               flag  = false;
    unsigned long long time1 = 0, time2 = 0, time3 = 0;

    // 根据规划规则判定拓展规则
    start_d_ = (plan_path_rule_ == PlanRule::Backward_All_Time) ? Backward : Forward;
    end_d_   = (plan_path_rule_ == PlanRule::NO_Backward_In_Start || plan_path_rule_ == PlanRule::Forward_All_Time || ((pow(current_point.x - start_.x, 2) + pow(current_point.y - start_.y, 2)) > (pow(m_vehicle_param_.backward_search_range, 2)))) ? Forward : Backward;

    // 计算转向角离散增量
    const double delta_angle = (m_vehicle_param_.max_steering - m_vehicle_param_.min_steering) / (m_vehicle_param_.angle_discrete_num - 1);
    for (unsigned int i = 0; i < m_vehicle_param_.angle_discrete_num; ++i) {
        double   temp_steering = m_vehicle_param_.min_steering + i * delta_angle;
        Vertex3D end_point;

        for (MotionDirection direction = start_d_; direction <= end_d_; direction = (MotionDirection)(direction + 1)) {
            // 根据车辆当前点位置、拓展方向和角度，得到拓展终点消息
            utility::CTimeClock start_time_rs_;
            VehDynam(current_point, direction, temp_steering, end_point);
            time1 += utility::CTimeHelper::GetTimeIntervalMicroseconds(start_time_rs_);
            end_point.id = Vertex2Hash(end_point); // 计算哈希值索引
            // 判断拓展点是否碰撞
            Point               temp_point(end_point.x, end_point.y, end_point.z, end_point.angle, end_point.direction);
            utility::CTimeClock start_time_rs;
            flag = collison_check_.IsVehicleCollision(temp_point);
            time2 += utility::CTimeHelper::GetTimeIntervalMicroseconds(start_time_rs);
            utility::CTimeClock start_time_rs__;
            if (flag == false) {
                // 计算该点g值
                CalGValue(current_point, end_point);
                // 判断该点是否已经存放于open集中或close集中
                if (open_map_.find(end_point.id) != open_map_.end()) // 如果在open集中
                {
                    // g值检查，判断该点g值是否小于open集中相应点g值
                    if (open_map_[end_point.id].g > end_point.g) {
                        // 节点更新
                        double f                = open_map_[end_point.id].f;
                        end_point.h             = open_map_[end_point.id].h;
                        end_point.f             = end_point.h + end_point.g;
                        open_map_[end_point.id] = end_point;

                        // open_multimap_f_中找到该点并替换
                        auto iter = open_map_f_.find(f);
                        if (iter != open_map_f_.end()) {
                            // static int num = 0;
                            while (iter->second.id != end_point.id && fabs(iter->second.f - f) < 1e-6) {
                                // ++num;
                                ++iter;
                            }
                            // std::threadLogger_->info( "num =" << num << std::endl;
                            if (iter->second.id == end_point.id) {
                                open_map_f_.erase(iter);
                            }
                        }
                        open_map_f_.insert(make_pair(end_point.f, end_point));
                    }
                }
                else if (close_map_.find(end_point.id) == close_map_.end()) // 如果不在close集中
                {
                    // open集中存入该点
                    CalHValue(end_point);
                    end_point.f             = 0.5 * end_point.g + 0.5 * end_point.h;
                    open_map_[end_point.id] = end_point;
                    open_map_f_.insert(make_pair(end_point.f, end_point));
                }
            }
            else {
                threadLogger_->info("探索过程中的点碰撞");
            }
            time3 += utility::CTimeHelper::GetTimeIntervalMicroseconds(start_time_rs__);
        }
        // threadLogger_->info("line561");
    }
    // threadLogger_->info("line561");
    // 在每个离散转向角处进行节点扩展

    // auto end_time = ros::Time::now();

    time_dy       = time1;
    time_collsion = time2;
    time_other    = time3;
    // ros::Duration time_difference = end_time - start_time;
    // double time_difference_seconds = time_difference.toSec();
    // time_expand_another = time_difference_seconds * 1000000;
}

/**
 *@brief: 回溯路径
 *@param
 *return
 */
void OptimalPath::TracePath(const Vertex3D final_point) {
    Vertex3D         temp_point = final_point;
    vector<Vertex3D> temp_path;
    // 从当前传入点开始，根据每个点存储的父节点id信息迭代查找，得到逆序路径
    while (true) {
        temp_path.push_back(temp_point);
        if (0 == temp_point.parent_id) {
            break;
        }
        if (close_map_.find(temp_point.parent_id) == close_map_.end()) {
            break;
        }
        temp_point = close_map_[temp_point.parent_id];
    }

    // 路径翻转，并转换格式
    Point path_point;
    Path().swap(path_a_star_);

    for (int i = static_cast<int>(temp_path.size() - 1); i >= 0; --i) {
        path_point.x         = temp_path.at(i).x;
        path_point.y         = temp_path.at(i).y;
        path_point.z         = temp_path.at(i).z;
        path_point.angle     = temp_path.at(i).angle;
        path_point.direction = temp_path.at(i).direction;
        path_a_star_.push_back(path_point);
    }
    // 改变尖点属性
    for (unsigned int i = 0; i < path_a_star_.size() - 1; ++i) {
        if (path_a_star_.at(i).direction != path_a_star_.at(i + 1).direction) {
            path_a_star_.at(i).direction = path_a_star_.at(i + 1).direction;
        }
    }
}

/**
 *@brief: 路径整合
 *@param
 *return
 */
void OptimalPath::PathIntegration() {
    /*拼接起点直线路径*/
    Point temp_point;
    Path  temp_path;

    threadLogger_->info("PathIntegration--start_offset_distance:{}", m_vehicle_param_.start_offset_distance);

    if (plan_path_rule_ == PlanRule::Backward_To_End || plan_path_rule_ == PlanRule::Forward_All_Time) {
        threadLogger_->info("向前路径拼接");
        temp_point.angle = actual_start_.angle;
        cout << "start_offset_distance:" << m_vehicle_param_.start_offset_distance << endl;
        for (double i = 0; i <= m_vehicle_param_.start_offset_distance + 1e-3; i += m_vehicle_param_.step_length) {
            temp_point.x         = actual_start_.x + i * cos(actual_start_.angle);
            temp_point.y         = actual_start_.y + i * sin(actual_start_.angle);
            temp_point.z         = 0;
            temp_point.direction = MotionDirection::Forward;
            temp_path.emplace_back(temp_point);
        }
        temp_path.pop_back();
        cout << "temp_path.size();" << temp_path.size() << endl;
        path_a_star_.insert(path_a_star_.begin(), temp_path.begin(), temp_path.end());
        path_a_star_.pop_back();
        cout << "拼接起点" << endl;
        for (int i = 0; i < path_a_star_.size(); i++) {
            cout << path_a_star_.at(i).angle << endl;
        }
    }

    if (plan_path_rule_ == PlanRule::Backward_All_Time) {
        threadLogger_->info("向后路径拼接");
        temp_point.angle = actual_start_.angle;
        for (double i = 0; i <= m_vehicle_param_.start_offset_distance + 1e-3; i += m_vehicle_param_.step_length) {
            temp_point.x         = actual_start_.x - i * cos(actual_start_.angle);
            temp_point.y         = actual_start_.y - i * sin(actual_start_.angle);
            temp_point.z         = 0;
            temp_point.direction = MotionDirection::Backward;
            temp_path.emplace_back(temp_point);
        }
        temp_path.pop_back();
        path_a_star_.insert(path_a_star_.begin(), temp_path.begin(), temp_path.end());
        path_a_star_.pop_back();
    }

    // 拼接RS路径
    path_a_star_.insert(path_a_star_.end(), path_r_s_.begin(), path_r_s_.end());
    Path().swap(path_r_s_);

    cout << "拼接RS" << endl;
    for (int i = 0; i < path_a_star_.size(); i++) {
        cout << path_a_star_.at(i).angle << endl;
    }

    // 拼接终点直线路径
    if (fitting_direction_ == FittingDirection::Forword_Fitting) // 前进直线拼接
    {
        Point temp_point;
        temp_point.angle = end_r_.angle;
        // cout << "temp_point.angle:" << temp_point.angle << endl;
        for (double i = m_vehicle_param_.step_length; i <= m_vehicle_param_.end_offset_distance; i += m_vehicle_param_.step_length) {
            temp_point.x         = end_r_.x + i * cos(end_r_.angle);
            temp_point.y         = end_r_.y + i * sin(end_r_.angle);
            temp_point.z         = 0;
            temp_point.direction = MotionDirection::Forward;
            cout << "temp_point.angle" << temp_point.angle << endl;
            path_a_star_.push_back(temp_point);
        }
        cout << "拼接完终点" << endl;
        for (int i = 0; i < path_a_star_.size(); i++) {
            cout << path_a_star_.at(i).angle << endl;
        }
    }
    else // 倒退直线拼接
    {
        Point temp_point;
        temp_point.angle = end_f_.angle;
        for (double i = m_vehicle_param_.step_length; i <= m_vehicle_param_.end_offset_distance; i += m_vehicle_param_.step_length) {
            temp_point.x         = end_f_.x - i * cos(end_f_.angle);
            temp_point.y         = end_f_.y - i * sin(end_f_.angle);
            temp_point.z         = 0;
            temp_point.direction = MotionDirection::Backward;
            path_a_star_.push_back(temp_point);
        }
    }
}

/**
 *@brief: 路径点数据还原
 *@param
 *return
 */
void OptimalPath::RestoreData(Path& path) {
    for (int i = 0; i < path.size(); ++i) {
        path.at(i).x += midpoint_.x;
        path.at(i).y += midpoint_.y;
    }
}

/**
 * @brief 连续的车辆运动学模型
 */
/**
 *@brief: 连续的车辆运动学模型
 *@param
 *return
 */
void OptimalPath::VehDynam(const Vertex3D& start, const MotionDirection direction, const double steering, Vertex3D& end) {
    // std::threadLogger_->info( "m_vehicle_param_.delta_dist = " << m_vehicle_param_.delta_dist << "\n";
    // std::threadLogger_->info( "m_vehicle_param_.wheel_base = " << m_vehicle_param_.wheel_base << "\n";

    double flag_pos_neg;
    if (MotionDirection::Forward == direction)
        flag_pos_neg = 1.0;
    else
        flag_pos_neg = -1.0;

    // 直线拓展
    if (fabs(steering) < 1e-6) {
        // std::threadLogger_->info( "00000" << "\n";
        end.x     = start.x + flag_pos_neg * m_vehicle_param_.delta_dist * cos(start.angle);
        end.y     = start.y + flag_pos_neg * m_vehicle_param_.delta_dist * sin(start.angle);
        end.angle = start.angle;
        end.angle = Helper::NormalizeAngleRad(end.angle);
    }
    else // 转向拓展
    {
        // std::threadLogger_->info( "11111" << "\n";
        double beta = m_vehicle_param_.delta_dist / m_vehicle_param_.wheel_base * tan(steering);
        double R    = m_vehicle_param_.delta_dist / beta;

        end.x     = start.x + flag_pos_neg * R * (sin(start.angle + beta) - sin(start.angle));
        end.y     = start.y + flag_pos_neg * R * (cos(start.angle) - cos(start.angle + beta));
        end.angle = start.angle + beta;
        end.angle = Helper::NormalizeAngleRad(end.angle);
    }

    end.direction = direction;
    // std::threadLogger_->info( "end.direction = " << (int)end.direction << "\n";
    end.parent_id = start.id;
}
/**
 * @brief 计算g值
 * @return 返回说明：无
 */
/**
 *@brief: 计算g值
 *@param
 *return
 */
void OptimalPath::CalGValue(const Vertex3D& start_point, Vertex3D& end_point) {
    // 保证开始时优先直线搜索
    double coeff = (pow(end_point.x - start_.x, 2) + pow(end_point.y - start_.y, 2) > m_vehicle_param_.linear_preferred_distance_square) ? 1 : 5;
    end_point.g  = start_point.g + m_vehicle_param_.delta_dist * ((m_vehicle_param_.backward_penalty - 1) * end_point.direction + 1.0) + coeff * m_vehicle_param_.turnning_penalty * fabs(fmod(end_point.angle - start_point.angle + 3 * M_PI, 2 * M_PI) - M_PI) + m_vehicle_param_.switch_penalty * fabs(start_point.direction - end_point.direction);
}

/**
 * @brief 计算h值(与终点代价的估计值)
 */
/**
 *@brief: 计算h值(与终点代价的估计值)
 *@param
 *return
 */
void OptimalPath::CalHValue(Vertex3D& point) {
    double a_start_h = 0, rs_h = 0;
    // Point  start(point.x, point.y, point.z, point.angle, point.direction);
    // dubins_h = dubins_.GetDubinsCost(start);

    // threadLogger_->info("BFSSearch2D begin");
    // BFSSearch2D();
    // threadLogger_->info("BFSSearch2D end");
    // IntCoordinate temp_point;
    // temp_point.x = static_cast<int>(floor(point.x / m_vehicle_param_.grid_dist));
    // temp_point.y = static_cast<int>(floor(point.y / m_vehicle_param_.grid_dist));

    // unsigned long long hash = Coordinate2Hash(temp_point);
    // if (h_cost_map_.find(hash) == h_cost_map_.end())
    //     bfs_h = DBL_MAX;
    // else
    //     bfs_h = h_cost_map_[hash];
    // if (m_vehicle_param_.hybrid_h_use_rs || m_vehicle_param_.hybrid_h_use_max) {
    // 使用rs曲线来评估当前point距离终点的启发值
    Point temp_start_point;
    temp_start_point.x         = point.x;
    temp_start_point.y         = point.y;
    temp_start_point.z         = point.z;
    temp_start_point.angle     = point.angle;
    temp_start_point.direction = point.direction;

    Point temp_end_point;
    temp_end_point.x     = end_.x;
    temp_end_point.y     = end_.y;
    temp_end_point.z     = end_.z;
    temp_end_point.angle = end_.angle;

    if (!my_r_s_curve_h.PlanRSPath(temp_start_point, temp_end_point)) {
        threadLogger_->info("采用RS曲线进行估算h值失败，这是不可能发生的");
    }
    rs_h = my_r_s_curve_h.opti_rs_path.length * 15;

    // threadLogger_->info("RS曲线到终点的预测距离：{}", my_r_s_curve_h.opti_rs_path.length * 15);
    // }
    // if (m_vehicle_param_.hybrid_h_use_a_star || m_vehicle_param_.hybrid_h_use_max) {
    utility::CTimeClock init_time;

    // 以A*搜索结果为启发值
    Node2D current2D(static_cast<short>(floor(point.x / m_vehicle_param_.grid_dist)), static_cast<short>(floor(point.y / m_vehicle_param_.grid_dist)), 0, 0);
    auto   iter = nodes2D_map_.find(current2D.getIdx());
    if (iter == nodes2D_map_.end()) {
        // static int num = 0;
        // if(num++ >40)
        // {
        //     point.h = 1000000000;
        //     return;
        // }

        Node2D goal2D(static_cast<short>(floor(end_.x / m_vehicle_param_.grid_dist)), static_cast<short>(floor(end_.y / m_vehicle_param_.grid_dist)), 0, 0);
        int    total = 0;

        a_start_h = AStarSearch2D(goal2D, current2D, total);


        long long init_time_end = utility::CTimeHelper::GetTimeIntervalMicroseconds(init_time); // 开始时间精确到微秒
        threadLogger_->info("本次A*搜素{}轮，耗时:{} ms", total, init_time_end * 0.001);
    }
    else {
        a_start_h = iter->second.getG();
        // threadLogger_->info("本次A*不用搜索");
    }
    // }


    // Node2D current2D_(static_cast<short>(floor(point.x / m_vehicle_param_.grid_dist)), static_cast<short>(floor(point.y / m_vehicle_param_.grid_dist)), 0, 0);
    // Node2D goal2D_(static_cast<short>(floor(end_.x / m_vehicle_param_.grid_dist)), static_cast<short>(floor(end_.y / m_vehicle_param_.grid_dist)), 0, 0);
    // point.h = hypot(goal2D_.getX() - current2D_.getX(), goal2D_.getY() - current2D_.getY());
    // point.h = max(a_start_h, rs_h);
    // if (m_vehicle_param_.hybrid_h_use_a_star) {
    //     point.h = a_start_h;
    //     threadLogger_->info("A*:{}", a_start_h);
    // }
    // else if (m_vehicle_param_.hybrid_h_use_rs) {
    //     point.h = rs_h;
    //     threadLogger_->info("RS:{}", rs_h);
    // }
    // else {
    point.h = max(a_start_h, rs_h);
    // threadLogger_->info("RS:{},A*:{}", rs_h, a_start_h);
    // }
}

/**
 *@brief: 采用广度优先算法遍历计算与终点距离
 *@param
 *return
 */
bool OptimalPath::BFSSearch2D() {
    clock_t startTime, endTime; // 计时
    startTime = clock();        // 计时开始
    h_cost_map_.clear();

    vector<vector<IntCoordinate>> point_set;    // 遍历过的点，按照层存储
    vector<vector<bool>>          is_bound_set; // 对应上面的点集是否是边界
    vector<IntCoordinate>         temp_layer;   // 临时存储每层的点
    vector<bool>                  temp_bound;   // 临时存储每层点是否是边界的信息
    IntCoordinate                 temp_point;

    temp_point.x = static_cast<short>(floor(end_.x / m_vehicle_param_.grid_dist));
    temp_point.y = static_cast<short>(floor(end_.y / m_vehicle_param_.grid_dist));
    temp_layer.push_back(temp_point);
    temp_bound.push_back(false);
    point_set.push_back(temp_layer);
    is_bound_set.push_back(temp_bound);

    unsigned int hash = Coordinate2Hash(temp_point);
    h_cost_map_[hash] = 0.0;

    // 从终点栅格开始层层向外拓展
    while (true) {
        endTime = clock();
        if ((double)(endTime - startTime) / CLOCKS_PER_SEC > 5) // 超时退出
            return false;
        vector<IntCoordinate>().swap(temp_layer);                     // 清空临时变量，存储新拓展层的坐标
        vector<bool>().swap(temp_bound);                              // 清空临时变量，存储新拓展层的边界信息
        vector<IntCoordinate> last_layer       = point_set.back();    // 上一层的坐标
        vector<bool>          last_layer_bound = is_bound_set.back(); // 上一层的边界信息

        for (int i = 0; i < last_layer.size(); ++i) // 每个节点进行拓展
        {
            double value_last_point = h_cost_map_.find(Coordinate2Hash(last_layer.at(i)))->second;

            if (last_layer_bound.at(i) == false) // 若节点不为边界才进行拓展
            {
                double temp_h;
                // 向西拓展
                temp_point.x = last_layer.at(i).x - 1;
                temp_point.y = last_layer.at(i).y;
                hash         = Coordinate2Hash(temp_point);
                auto iter    = h_cost_map_.find(hash);
                if (iter == h_cost_map_.end()) // 若拓展节点不在map中，则加入
                {
                    temp_layer.push_back(temp_point);
                    double value      = value_last_point + 1 * m_vehicle_param_.grid_dist;
                    h_cost_map_[hash] = value;
                    if (IsBoundGrid(temp_point) == false) // 拓展的节点不为边界
                        temp_bound.push_back(false);
                    else
                        temp_bound.push_back(true);
                }
                else {
                    temp_h       = iter->second;
                    double value = value_last_point + 1 * m_vehicle_param_.grid_dist;
                    if (value < temp_h) {
                        iter->second = value;
                    }
                }

                // 向西北拓展
                temp_point.x = last_layer.at(i).x - 1;
                temp_point.y = last_layer.at(i).y + 1;
                hash         = Coordinate2Hash(temp_point);
                iter         = h_cost_map_.find(hash);
                if (iter == h_cost_map_.end()) // 若拓展节点不在map中，则加入
                {
                    temp_layer.push_back(temp_point);
                    double value      = value_last_point + 1.414 * m_vehicle_param_.grid_dist;
                    h_cost_map_[hash] = value;
                    if (IsBoundGrid(temp_point) == false) // 拓展的节点不为边界
                        temp_bound.push_back(false);
                    else
                        temp_bound.push_back(true);
                }
                else {
                    temp_h       = iter->second;
                    double value = value_last_point + 1.414 * m_vehicle_param_.grid_dist;
                    if (value < temp_h) {
                        iter->second = value;
                    }
                }

                // 向北拓展
                temp_point.x = last_layer.at(i).x;
                temp_point.y = last_layer.at(i).y + 1;
                hash         = Coordinate2Hash(temp_point);
                iter         = h_cost_map_.find(hash);
                if (iter == h_cost_map_.end()) // 若拓展节点不在map中，则加入
                {
                    temp_layer.push_back(temp_point);
                    double value      = value_last_point + 1 * m_vehicle_param_.grid_dist;
                    h_cost_map_[hash] = value;
                    if (IsBoundGrid(temp_point) == false) // 拓展的节点不为边界
                        temp_bound.push_back(false);
                    else
                        temp_bound.push_back(true);
                }
                else {
                    temp_h       = iter->second;
                    double value = value_last_point + 1 * m_vehicle_param_.grid_dist;
                    if (value < temp_h) {
                        iter->second = value;
                    }
                }

                // 向东北拓展
                temp_point.x = last_layer.at(i).x + 1;
                temp_point.y = last_layer.at(i).y + 1;
                hash         = Coordinate2Hash(temp_point);
                iter         = h_cost_map_.find(hash);
                if (iter == h_cost_map_.end()) // 若拓展节点不在map中，则加入
                {
                    temp_layer.push_back(temp_point);
                    double value      = value_last_point + 1.414 * m_vehicle_param_.grid_dist;
                    h_cost_map_[hash] = value;
                    if (IsBoundGrid(temp_point) == false) // 拓展的节点不为边界
                        temp_bound.push_back(false);
                    else
                        temp_bound.push_back(true);
                }
                else {
                    temp_h       = iter->second;
                    double value = value_last_point + 1.414 * m_vehicle_param_.grid_dist;
                    if (value < temp_h) {
                        iter->second = value;
                    }
                }

                // 向东拓展
                temp_point.x = last_layer.at(i).x + 1;
                temp_point.y = last_layer.at(i).y;
                hash         = Coordinate2Hash(temp_point);
                iter         = h_cost_map_.find(hash);
                if (iter == h_cost_map_.end()) // 若拓展节点不在map中，则加入
                {
                    temp_layer.push_back(temp_point);
                    double value      = value_last_point + 1 * m_vehicle_param_.grid_dist;
                    h_cost_map_[hash] = value;
                    if (IsBoundGrid(temp_point) == false) // 拓展的节点不为边界
                        temp_bound.push_back(false);
                    else
                        temp_bound.push_back(true);
                }
                else {
                    temp_h       = iter->second;
                    double value = value_last_point + 1 * m_vehicle_param_.grid_dist;
                    if (value < temp_h) {
                        iter->second = value;
                    }
                }

                // 向东南拓展
                temp_point.x = last_layer.at(i).x + 1;
                temp_point.y = last_layer.at(i).y - 1;
                hash         = Coordinate2Hash(temp_point);
                iter         = h_cost_map_.find(hash);
                if (iter == h_cost_map_.end()) // 若拓展节点不在map中，则加入
                {
                    temp_layer.push_back(temp_point);
                    double value      = value_last_point + 1.414 * m_vehicle_param_.grid_dist;
                    h_cost_map_[hash] = value;
                    if (IsBoundGrid(temp_point) == false) // 拓展的节点不为边界
                        temp_bound.push_back(false);
                    else
                        temp_bound.push_back(true);
                }
                else {
                    temp_h       = iter->second;
                    double value = value_last_point + 1.414 * m_vehicle_param_.grid_dist;
                    if (value < temp_h) {
                        iter->second = value;
                    }
                }

                // 向南拓展
                temp_point.x = last_layer.at(i).x;
                temp_point.y = last_layer.at(i).y - 1;
                hash         = Coordinate2Hash(temp_point);
                iter         = h_cost_map_.find(hash);
                if (iter == h_cost_map_.end()) // 若拓展节点不在map中，则加入
                {
                    temp_layer.push_back(temp_point);
                    double value      = value_last_point + 1 * m_vehicle_param_.grid_dist;
                    h_cost_map_[hash] = value;
                    if (IsBoundGrid(temp_point) == false) // 拓展的节点不为边界
                        temp_bound.push_back(false);
                    else
                        temp_bound.push_back(true);
                }
                else {
                    temp_h       = iter->second;
                    double value = value_last_point + 1 * m_vehicle_param_.grid_dist;
                    if (value < temp_h) {
                        iter->second = value;
                    }
                }

                // 向西南拓展
                temp_point.x = last_layer.at(i).x - 1;
                temp_point.y = last_layer.at(i).y - 1;
                hash         = Coordinate2Hash(temp_point);
                iter         = h_cost_map_.find(hash);
                if (iter == h_cost_map_.end()) // 若拓展节点不在map中，则加入
                {
                    temp_layer.push_back(temp_point);
                    double value      = value_last_point + 1.414 * m_vehicle_param_.grid_dist;
                    h_cost_map_[hash] = value;
                    if (IsBoundGrid(temp_point) == false) // 拓展的节点不为边界
                        temp_bound.push_back(false);
                    else
                        temp_bound.push_back(true);
                }
                else {
                    temp_h       = iter->second;
                    double value = value_last_point + 1.414 * m_vehicle_param_.grid_dist;
                    if (value < temp_h) {
                        iter->second = value;
                    }
                }
            }
            else
                ;
        } // end for
        if (temp_layer.size() == 0) // 若未拓展到点，则退出拓展
            break;
        else
            ;
        point_set.push_back(temp_layer);
        is_bound_set.push_back(temp_bound);

    } // end while

    return true;
}

float OptimalPath::AStarSearch2D(Node2D& start, Node2D& goal, int& num) {
    if (!nodes2D_set_.empty()) {
        nodes2D_set_.clear();
        for (auto iter = nodes2D_map_.begin(); iter != nodes2D_map_.end(); ++iter) {
            if (iter->second.isOpen()) {
                iter->second.updateH(goal);
                unsigned long long hash = iter->second.getIdx() | (static_cast<unsigned long long>(iter->second.getF() * 1000) << 32);
                nodes2D_set_.insert(hash);
            }
        }
    }


    threadLogger_->info("start = {},{}", start.getX(), start.getY());
    threadLogger_->info("goal = {},{}", goal.getX(), goal.getY());

    start.updateH(goal);
    threadLogger_->info("start.getH():{}", start.getH());
    start.open();
    unsigned long long hash = start.getIdx() | (static_cast<unsigned long long>(start.getF() * 1000) << 32); // 包含点的F值和索引
    nodes2D_set_.insert(hash);                                                                               // 存入起点
    threadLogger_->info("start's idx:{},  start's x:{},   start's y:{}", start.getIdx(), start.getIdx() >> 16, short(start.getIdx() & 0xFFFF));
    nodes2D_map_[start.getIdx()] = start;
    Node2D       nPred, nSucc; // 当前操作的点和其继任点
    unsigned int iPred, iSucc;
    num = 0;
    float newG;
    threadLogger_->info("nodes2D_set_.size():{} ", nodes2D_set_.size());
    threadLogger_->info("nodes2D_map_.size():{} ", nodes2D_map_.size());
    while (!nodes2D_set_.empty()) {
        num++;
        // if (num > 1500) {
        //     threadLogger_->info("搜索超过1500轮,强制退出");
        //     break;
        // }
        // threadLogger_->info("第{}轮,开始从node2D_set_中挑选最小代价点", num);.
        iPred = *nodes2D_set_.begin() & 0x00000000FFFFFFFF;
        // threadLogger_->info("iPred:{} ", iPred);
        nPred = nodes2D_map_[iPred];
        // threadLogger_->info("nPred:{} {} ", nPred.getX(), nPred.getY());
        if (nodes2D_map_[iPred].isClosed()) {
            // threadLogger_->info("nodes2D_map_[iPred] is Closed");
            nodes2D_set_.erase(nodes2D_set_.begin());
            continue;
        }

        if (nodes2D_map_[iPred].isOpen()) {
            // threadLogger_->info("nodes2D_map_[iPred] is Open");
            nodes2D_set_.erase(nodes2D_set_.begin());
            nodes2D_map_[iPred].close();
            nodes2D_map_[iPred].discover();
            if (nPred == goal) {
                threadLogger_->info("nPred is goal");
                return nPred.getG();
            }
            for (int i = 0; i < Node2D::dir; ++i) {
                nSucc = nPred.createSuccessor(i);
                // threadLogger_->info("");
                // threadLogger_->info("nSucc :{} {}", nSucc.getX(), nSucc.getY());
                iSucc = nSucc.getIdx();
                // threadLogger_->info("iSucc :{}", iSucc);
                IntCoordinate point(nSucc.getX(), nSucc.getY(), 0);
                bool          flag_in_nodes2D = (nodes2D_map_.find(iSucc) != nodes2D_map_.end());
                if (!IsBoundGrid(point) && (!flag_in_nodes2D || !nodes2D_map_[iSucc].isClosed())) { // 节点不是边界点且节点没有探索过，或者探索过，但是不是close的，就可以作为继承点
                    // threadLogger_->info("符合要求的点");
                    nSucc.open();
                    nSucc.discover();

                    newG = nSucc.getG();
                    // threadLogger_->info("newG:{}", newG);
                    if (flag_in_nodes2D && nodes2D_map_[iSucc].isOpen()) // 节点探索过，并且是open性质
                    {
                        // threadLogger_->info("iSucc is Open");
                        if (newG < nodes2D_map_[iSucc].getG()) {
                            // threadLogger_->info("更小的G值");
                            hash      = nodes2D_map_[iSucc].getIdx() | (static_cast<unsigned long long>(nodes2D_map_[iSucc].getF() * 1000) << 32);
                            auto iter = nodes2D_set_.find(hash);
                            if (iter != nodes2D_set_.end()) {
                                nodes2D_set_.erase(iter);
                            }
                        }
                        else
                            continue;
                    }
                    nSucc.updateH(goal);
                    hash = nSucc.getIdx() | (static_cast<unsigned long long>(nSucc.getF() * 1000) << 32);
                    // threadLogger_->info("hash:{}", hash);
                    nodes2D_set_.insert(hash);
                    nodes2D_map_[iSucc] = nSucc;
                }
                else {
                    // if (IsBoundGrid(point)) {
                    //     // threadLogger_->info("该点是边界点或者该点已经被探索过，但已经进close");
                    // }
                    // else {
                    //     // threadLogger_->info("该该点已经被探索过，但已经进close");
                    // }
                }
            }
        }
    }
    // threadLogger_->info("line1405 ");
}

/**
 * @brief 判断点是否在边界上
 * @return 返回说明：无
 */
/**
 *@brief: 判断点是否在边界上
 *@param
 *return
 */
bool OptimalPath::IsBoundGrid(IntCoordinate point) {
    unsigned int hash = Coordinate2Hash(point);

    // 计算相邻8个栅格点位置
    IntCoordinate point_west;
    point_west.x = point.x - 1;
    point_west.y = point.y;
    point_west.z = point.z;

    IntCoordinate point_east;
    point_east.x = point.x + 1;
    point_east.y = point.y;
    point_east.z = point.z;

    IntCoordinate point_north;
    point_north.x = point.x;
    point_north.y = point.y + 1;
    point_north.z = point.z;

    IntCoordinate point_south;
    point_south.x = point.x;
    point_south.y = point.y - 1;
    point_south.z = point.z;

    IntCoordinate point_west_north;
    point_west_north.x = point.x - 1;
    point_west_north.y = point.y + 1;
    point_west_north.z = point.z;

    IntCoordinate point_east_north;
    point_east_north.x = point.x + 1;
    point_east_north.y = point.y + 1;
    point_east_north.z = point.z;

    IntCoordinate point_west_south;
    point_west_south.x = point.x - 1;
    point_west_south.y = point.y - 1;
    point_west_south.z = point.z;

    IntCoordinate point_east_south;
    point_east_south.x = point.x + 1;
    point_east_south.y = point.y - 1;
    point_east_south.z = point.z;

    // 以下5种情况都表明当前点是边界点
    if (bound_set_for_Astar_.count(hash) == 1) // 当前点在边界上
        return true;
    else if ((bound_set_for_Astar_.count(Coordinate2Hash(point_west)) == 1) &&     // 当前点西和北方向是边界，西北方向
             (bound_set_for_Astar_.count(Coordinate2Hash(point_north)) == 1) &&    // 不是边界，则当前点是
             (bound_set_for_Astar_.count(Coordinate2Hash(point_west_north)) == 0)) // 边界点，下同理
        return true;
    else if ((bound_set_for_Astar_.count(Coordinate2Hash(point_west)) == 1) &&     // 当前点西和北方向是边界，西北方向
             (bound_set_for_Astar_.count(Coordinate2Hash(point_south)) == 1) &&    // 不是边界，则当前点是
             (bound_set_for_Astar_.count(Coordinate2Hash(point_west_south)) == 0)) // 边界点，下同理
        return true;
    else if ((bound_set_for_Astar_.count(Coordinate2Hash(point_east)) == 1) &&     // 当前点西和北方向是边界，西北方向
             (bound_set_for_Astar_.count(Coordinate2Hash(point_south)) == 1) &&    // 不是边界，则当前点是
             (bound_set_for_Astar_.count(Coordinate2Hash(point_east_south)) == 0)) // 边界点，下同理
        return true;
    else if ((bound_set_for_Astar_.count(Coordinate2Hash(point_east)) == 1) &&     // 当前点西和北方向是边界，西北方向
             (bound_set_for_Astar_.count(Coordinate2Hash(point_north)) == 1) &&    // 不是边界，则当前点是
             (bound_set_for_Astar_.count(Coordinate2Hash(point_east_north)) == 0)) // 边界点，下同理
        return true;
    else
        return false;
}

/**
 *@brief: 将内外边界变为整数坐标形式，并存入bound_set种
 *@param
 *return
 */
void OptimalPath::GenerateBoundSet() {
    IntCoordinate temp_point;
    bound_set_.clear();
    bound_set_for_Astar_.clear(); // 这个地图边界是为了给hybridA*算法中，采用A*计算h值时使用的边界，下面的代码会对此边界进行膨胀
    unsigned int hash;

    // 计算地图边界栅格
    for (int i = 0; i < road_bound_.size(); ++i) {
        for (int j = 0; j < road_bound_.at(i).size(); ++j) {
            temp_point.x = static_cast<short>(floor(road_bound_.at(i).at(j).x / m_vehicle_param_.grid_dist));
            temp_point.y = static_cast<short>(floor(road_bound_.at(i).at(j).y / m_vehicle_param_.grid_dist));
            hash         = Coordinate2Hash(temp_point);
            bound_set_.insert(hash);
        }
    }

    // 计算障碍物边界栅格
    for (int i = 0; i < obstacle_bound_.size(); ++i) {
        for (int j = 0; j < obstacle_bound_.at(i).size(); ++j) {
            temp_point.x = static_cast<short>(floor(obstacle_bound_.at(i).at(j).x / m_vehicle_param_.grid_dist));
            temp_point.y = static_cast<short>(floor(obstacle_bound_.at(i).at(j).y / m_vehicle_param_.grid_dist));
            hash         = Coordinate2Hash(temp_point);
            bound_set_.insert(hash);
        }
    }
    bound_set_for_Astar_ = bound_set_;

    // // 计算A*地图边界栅格
    // float         radius = m_vehicle_param_.veh_center_2_side; // 实际上，我们使用半径的两倍作为正方形的边长
    // IntCoordinate tp;
    // for (int i = 0; i < road_bound_.size(); ++i) {
    //     for (int j = 0; j < road_bound_.at(i).size(); ++j) {
    //         temp_point.x = static_cast<short>(floor(road_bound_.at(i).at(j).x / m_vehicle_param_.grid_dist));
    //         temp_point.y = static_cast<short>(floor(road_bound_.at(i).at(j).y / m_vehicle_param_.grid_dist));

    //         // 之所以进行膨胀，是为了堵住一些低于车辆车宽的狭隘间隙
    //         for (int i = 0; i < 360; i++) {
    //             tp.x = temp_point.x + radius * cos(i / 180.0 * M_PI);
    //             tp.y = temp_point.y + radius * sin(i / 180.0 * M_PI);
    //             hash = Coordinate2Hash(tp);
    //             bound_set_for_Astar_.insert(hash);
    //         }
    //     }
    // }

    // // 计算A*障碍物边界栅格
    // for (int i = 0; i < obstacle_bound_.size(); ++i) {
    //     for (int j = 0; j < obstacle_bound_.at(i).size(); ++j) {
    //         temp_point.x = static_cast<short>(floor(obstacle_bound_.at(i).at(j).x / m_vehicle_param_.grid_dist));
    //         temp_point.y = static_cast<short>(floor(obstacle_bound_.at(i).at(j).y / m_vehicle_param_.grid_dist));
    //         for (int i = 0; i < 360; i++) {
    //             tp.x = temp_point.x + radius * cos(i / 180.0 * M_PI);
    //             tp.y = temp_point.y + radius * sin(i / 180.0 * M_PI);
    //             hash = Coordinate2Hash(tp);
    //             bound_set_for_Astar_.insert(hash);
    //         }
    //     }
    // }
}

void OptimalPath::CalCurv(Path& temp_path) {
    vector<double> cur_vec;
    cur_vec.resize(temp_path.size());
    for (int i = 1; i < temp_path.size() - 1; ++i) {
        double curvature = computeCurvature(temp_path.at(i - 1), temp_path.at(i), temp_path.at(i + 1));
        cur_vec.at(i)    = curvature;
    }
    cur_vec.front() = cur_vec.at(1);
    cur_vec.back()  = cur_vec.at(cur_vec.size() - 2);
}
double OptimalPath::computeCurvature(const Point& p1, const Point& p2, const Point& p3) {
    double x1 = p1.x;
    double x2 = p2.x;
    double x3 = p3.x;
    double y1 = p1.y;
    double y2 = p2.y;
    double y3 = p3.y;

    double curvature = (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / pow((pow(x1 - x2, 2) + pow(y1 - y2, 2)) * (pow(x2 - x3, 2) + pow(y2 - y3, 2)) * (pow(x3 - x1, 2) + pow(y3 - y1, 2)), 0.5);
    return curvature;
}
