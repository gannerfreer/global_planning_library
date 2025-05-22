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
#include "../../../smoother/path_opti.h"
#include "../../../time/StringHelper.h"
#include "../../../time/TimeHelper.h"
using namespace GlobalPlanning;


void OptimalPath::InitBound(const _SinglePoint start_point, const vector<_BorderPoint>& map_border, const vector<vector<_BorderPoint>>& inner_borders, const _VehicleParam& m_vehicle_param) {
    // 初始化当前任务HybridA*所需要的地图边界和障碍物边界
    //  区域外边界、区域内边界转换
    threadLogger_->info("初始化当前任务HybridA*所需要的地图边界、障碍物边界及Voronoi图");
    Coordinate temp_Coordinate;
    v_road_outer_bound_.clear();
    v_road_inner_bound_.clear();
    init_road_bound_.clear();
    init_obstacle_bound_.clear();
    // 获取道路外边界 (以传入参数的外边界点作为道路外边界)
    for (int index = 0; index < map_border.size(); index++) {
        temp_Coordinate.x = map_border.at(index).x;
        temp_Coordinate.y = map_border.at(index).y;
        temp_Coordinate.z = map_border.at(index).z;
        if (hypot(start_point.x - temp_Coordinate.x, start_point.y - temp_Coordinate.y) < 100) {
            v_road_outer_bound_.emplace_back(temp_Coordinate);
        }
    }
    // threadLogger_->info("內边界大小  inner_borders_.size():{} ,inner_borders_.at(0).size():{}", inner_borders_.size(), inner_borders_.at(0).size());
    // 获取道路内边界 (暂时以传入参数的障碍物边界作为道路内边界)
    for (int index = 0; index < inner_borders.size(); index++) {
        for (int j = 0; j < inner_borders.at(index).size(); j++) {
            temp_Coordinate.x = inner_borders.at(index).at(j).x;
            temp_Coordinate.y = inner_borders.at(index).at(j).y;
            temp_Coordinate.z = inner_borders.at(index).at(j).z;
            // cout << "x:" << temp_Coordinate.x << "  y:" << temp_Coordinate.y << "  z:" << temp_Coordinate.z << endl;
            if (hypot(start_point.x - temp_Coordinate.x, start_point.y - temp_Coordinate.y) < 100) {
                v_road_inner_bound_.emplace_back(temp_Coordinate);
            }
        }
    }
    threadLogger_->info("v_road_outer_bound_.size():{}", v_road_outer_bound_.size());
    threadLogger_->info("v_road_inner_bound_.size():{}", v_road_inner_bound_.size());
    // std::ofstream file_out;
    // file_out.open("selected_border.txt");
    // for (int i = 0; i < v_road_outer_bound_.size(); i++) {
    //     file_out << v_road_outer_bound_.at(i).x << " " << v_road_outer_bound_.at(i).y << endl;
    // }
    // file_out.close();

    init_road_bound_.emplace_back(v_road_outer_bound_);
    init_obstacle_bound_.emplace_back(v_road_inner_bound_); // 这里填充好的road_inner_bound_和road_outer_bound_会在调用globalPlanning()函数时作为入参传入
}


/**
 *@brief: 路径规划接口函数
 *@param
 *return
 */
PlanResult OptimalPath::SearchGlobalPath(const Point start, const Point end, const _VehicleParam m_vehicle_param, Path& final_path, long long time_threshold, const PlanRule& plan_path_rule) {
    m_vehicle_param_ = m_vehicle_param;
    my_r_s_curve.Init(m_vehicle_param_);

    my_r_s_curve.threadLogger_ = threadLogger_;
    plan_path_rule_            = plan_path_rule;

    utility::CTimeLog timelog("SearchGlobalPath");
    InitData(start, end);
    timelog.AddLog("InitData");

    collison_check_.InitParam(m_vehicle_param_);
    collison_check_.InitBoundMap(offset_road_bound_);
    collison_check_.InitObstacleMap(offset_obstacle_bound_);
    timelog.AddLog("InitBoundMap");

    GenerateBoundSet();
    threadLogger_->info("GenerateBoundSet 执行完毕");
    timelog.AddLog("GenerateBoundSet");

    nodes2D_set_.clear();
    h_cost_map_.clear();
    nodes2D_map_.clear();

    if (true == collison_check_.IsVehicleCollision(actual_start_)) {
        threadLogger_->info("起点碰撞检测不通过");
        return PlanResult::StartPoint_Collision;
    }

    cout << "开启对终点的碰撞检测" << endl;
    // 终点区域碰撞判断
    if (true == collison_check_.IsVehicleCollision(end_)) {
        threadLogger_->info("终点碰撞检测不通过 {} {}  {}", end_.x + midpoint_.x, end_.y + midpoint_.y, end_.angle / M_PI * 180.0);
        cout << "终点碰撞检测不通过" << endl;
        return PlanResult::EndPoint_Collision;
    }
    cout << "终点碰撞检测通过" << endl;
    bool end_f_collison_flag = false, end_r_collison_flag = false;
    end_r_collison_flag = collison_check_.IsVehicleCollision(end_r_);
    end_f_collison_flag = collison_check_.IsVehicleCollision(end_f_);


    if ((plan_path_rule_ == PlanRule::Forward_All_Time || plan_path_rule_ == PlanRule::Start_Back_End_Front) && end_r_collison_flag) {
        threadLogger_->info("PlanRule::Forward_All_Time||PlanRule::Start_Back_End_Front  ,but end_r_ 碰撞检测失败 ");
        return PlanResult::EndPoint_Infeasible;
    }
    else {
        threadLogger_->info("PlanRule::Forward_All_Time||PlanRule::Start_Back_End_Front  ,end_r_ 碰撞检测成功 ");
    }

    if ((plan_path_rule_ == PlanRule::Backward_All_Time || plan_path_rule_ == PlanRule::Start_Front_End_Back) && end_f_collison_flag) {
        threadLogger_->info("PlanRule::Backward_All_Time||plan_path_rule_ == PlanRule::Start_Front_End_Back ,but end_f_ 碰撞检测失败 ");
        return PlanResult::EndPoint_Infeasible;
    }
    else {
        threadLogger_->info("PlanRule::Backward_All_Time||plan_path_rule_ == PlanRule::Start_Front_End_Back ,end_f_ 碰撞检测成功 ");
    }
    timelog.AddLog("IsVehicleCollision");


    if (plan_path_rule_ == PlanRule::Start_Front_End_Back || plan_path_rule_ == PlanRule::Backward_All_Time) {
        threadLogger_->info("plan_path_rule_ == PlanRule::Start_Front_End_Back || plan_path_rule_ == PlanRule::Backward_All_Time---  Backward_Fitting");
        fitting_direction_ = FittingDirection::Backward_Fitting;
    }
    else if (plan_path_rule_ == PlanRule::Forward_All_Time || plan_path_rule_ == PlanRule::Start_Back_End_Front) {
        threadLogger_->info("plan_path_rule_ == PlanRule::Forward_All_Time || plan_path_rule_ == PlanRule::Start_Back_End_Front---  Forword_Fitting");
        fitting_direction_ = FittingDirection::Forword_Fitting;
    }
    else if (plan_path_rule_ == PlanRule::Normal_Planning) {
        if (end_r_collison_flag) {
            fitting_direction_ = FittingDirection::Backward_Fitting;
            threadLogger_->info("plan_path_rule_ == PlanRule::Normal_Planning---  由于终点后向点碰撞，只能采用Backward_Fitting");
        }
        else if (end_f_collison_flag) {
            fitting_direction_ = FittingDirection::Forword_Fitting;
            threadLogger_->info("plan_path_rule_ == PlanRule::Normal_Planning---  由于终点前向点碰撞，只能采用Forward_Fitting");
        }
        else {
            fitting_direction_ = FittingDirection::Both_Fitting;
            threadLogger_->info("plan_path_rule_ == PlanRule::Normal_Planning---  Both_Fitting");
        }
    }
    else {
        threadLogger_->info(" 未投入实际使用的plan_path_rule");
    }


    cout << "开始AStarPath" << endl;
    PlanResult result = AStarPath(final_path, time_threshold);
    timelog.AddLog("AStarPath");
    threadLogger_->info(timelog.GetLog());
    return result;
}


/**
 *@brief: 数据初始化函数，将数据减小，放置精度丢失
 *@param
 *return
 */
void OptimalPath::InitData(Point start, Point end) {
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
    threadLogger_->info("midpoint_.x:{}  midpoint_.y:{}", midpoint_.x, midpoint_.y);


    // 计算平移后地图边界点
    offset_road_bound_.clear();
    for (unsigned int i = 0; i < init_road_bound_.size(); ++i) {
        vector<Coordinate> temp_bound = init_road_bound_.at(i);
        vector<Coordinate> temp_bound_2;
        for (int j = 0; j < temp_bound.size(); ++j) {
            Coordinate temp_point;
            temp_point.z = 0;
            temp_point.x = temp_bound.at(j).x - midpoint_.x;
            temp_point.y = temp_bound.at(j).y - midpoint_.y;
            temp_bound_2.push_back(temp_point);
        }
        threadLogger_->info("外边界大小：{}", temp_bound_2.size());
        offset_road_bound_.push_back(temp_bound_2);
    }
    // std::ofstream file_out;
    // file_out.open("hybridatar_border.txt");
    // for (int i = 0; i < offset_road_bound_.size(); i++) {
    //     for (int j = 0; j < offset_road_bound_.at(i).size(); j++) {
    //         file_out << offset_road_bound_.at(i).at(j).x << " " << offset_road_bound_.at(i).at(j).y << endl;
    //     }
    // }
    // file_out.close();

    // 计算平移后障碍物边界点
    offset_obstacle_bound_.clear();
    for (unsigned int i = 0; i < init_obstacle_bound_.size(); ++i) {
        vector<Coordinate> temp_bound = init_obstacle_bound_.at(i);
        vector<Coordinate> temp_bound_2;
        for (int j = 0; j < temp_bound.size(); ++j) {
            Coordinate temp_point;
            temp_point.z = 0;
            temp_point.x = temp_bound.at(j).x - midpoint_.x;
            temp_point.y = temp_bound.at(j).y - midpoint_.y;
            temp_bound_2.push_back(temp_point);
        }
        threadLogger_->info("内边界大小：{}", temp_bound_2.size());
        offset_obstacle_bound_.push_back(temp_bound_2);
    }

    // 计算终点前直线补偿点位置
    threadLogger_->info("终点偏移距离 { }米", end_offset_distance_);
    end_f_.angle = end_.angle;
    end_f_.x     = end_.x + end_offset_distance_ * cos(end_.angle);
    end_f_.y     = end_.y + end_offset_distance_ * sin(end_.angle);

    // 计算终点后直线补偿点位置
    end_r_.angle = end_.angle;
    end_r_.x     = end_.x - end_offset_distance_ * cos(end_.angle);
    end_r_.y     = end_.y - end_offset_distance_ * sin(end_.angle);

    actual_start_ = start_;
    if (plan_path_rule_ == PlanRule::Forward_All_Time || plan_path_rule_ == PlanRule::Start_Front_End_Back) {
        threadLogger_->info("规划规则：{} 起点向前进行{}米的延伸", static_cast<int>(plan_path_rule_), start_offset_distance_);
        start_.x = start_.x + start_offset_distance_ * cos(start_.angle);
        start_.y = start_.y + start_offset_distance_ * sin(start_.angle);
    }

    if (plan_path_rule_ == PlanRule::Backward_All_Time || plan_path_rule_ == PlanRule::Start_Back_End_Front) {
        threadLogger_->info("规划规则：{} 起点向后进行{}米的延伸", static_cast<int>(plan_path_rule_), start_offset_distance_);
        start_.x = start_.x - start_offset_distance_ * cos(start_.angle);
        start_.y = start_.y - start_offset_distance_ * sin(start_.angle);
    }
}

/**
 *@brief: 混合A*搜索主函数
 *@param
 *return path
 */
PlanResult OptimalPath::AStarPath(Path& path, long long timeThreshold) {
    // 以下3行代码用于超时退出
    my_path_opti.threadLogger_ = threadLogger_;


    utility::CTimeClock init_time;
    InitOpenClose();                                                                        // 初始化open集和close集
    long long init_time_end = utility::CTimeHelper::GetTimeIntervalMicroseconds(init_time); // 开始时间精确到微秒
    if (init_time_end > 1000000) {
        threadLogger_->info("InitOpenClose()函数执行超时");
        cout << "InitOpenClose()函数执行超时" << endl;
        // 如果InitOpenClose函数执行时间过长，表面A*无法搜索出连接起点终点的路，大概率是通道太窄
        return PlanResult::Map_Infeasible;
    }
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
        // threadLogger_->info("open_map_f_.size():{}", open_map_f_.size());
        // cout << "open_map_f_.size():" << open_map_f_.size() << endl;
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
        // threadLogger_->info("新的一轮  current_point:{},{}", current_point.x, current_point.y);
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

    // // 平滑前打印路径曲率
    // Helper::CalCurv(path_a_star_);
    // // CalCurv(path_a_star_);

    // threadLogger_->info("HybridA_star规划出的原始路径（无尖点延伸）,曲率通过三点式原理计算得来");
    // for (int i = 0; i < path_a_star_.size() - 1; i++) {
    //     threadLogger_->info("x:{} y:{} angle:{}  curvature:{} direction:{} del_s:{} ", path_a_star_.at(i).x, path_a_star_.at(i).y, path_a_star_.at(i).angle / M_PI * 180.0, path_a_star_.at(i).curvature, path_a_star_.at(i).direction, hypot(path_a_star_.at(i).x - path_a_star_.at(i + 1).x, path_a_star_.at(i).y - path_a_star_.at(i + 1).y));
    // }
    // threadLogger_->info("x:{} y:{} angle:{}  curvature:{} direction:{}", path_a_star_.back().x, path_a_star_.back().y, path_a_star_.back().angle / M_PI * 180.0, path_a_star_.back().curvature, path_a_star_.back().direction);


    CurvatureCal(path_a_star_);
    threadLogger_->info("HybridA_star规划出的原始路径（无尖点延伸）,曲率通过外接圆原理计算得来");
    for (int i = 0; i < path_a_star_.size() - 1; i++) {
        threadLogger_->info("x:{} y:{} angle:{}  curvature:{} direction:{} del_s:{} ", path_a_star_.at(i).x, path_a_star_.at(i).y, path_a_star_.at(i).angle / M_PI * 180.0, path_a_star_.at(i).curvature, path_a_star_.at(i).direction, hypot(path_a_star_.at(i).x - path_a_star_.at(i + 1).x, path_a_star_.at(i).y - path_a_star_.at(i + 1).y));
    }
    threadLogger_->info("x:{} y:{} angle:{}  curvature:{} direction:{}", path_a_star_.back().x, path_a_star_.back().y, path_a_star_.back().angle / M_PI * 180.0, path_a_star_.back().curvature, path_a_star_.back().direction);


    // 路径优化，得到最终的path
    my_path_opti.OptimizePath(path_a_star_, path, collison_check_, m_vehicle_param_);
    threadLogger_->info("平滑后路径点信息");
    for (auto i : path) {
        threadLogger_->info("x:{} y:{} angle:{} curvature:{} direction:{} ", i.x, i.y, i.angle / M_PI * 180.0, i.curvature, i.direction);
    }

    long long cal_time2 = utility::CTimeHelper::GetTimeIntervalMicroseconds(start_time_opti);
    threadLogger_->info("路径优化完成，用时: {} ms ", 0.001 * cal_time2);

    utility::CTimeClock start_time_dis;
    // GetLeftAndRightDistance(path);

    threadLogger_->info("GetLeftAndRightDistance() Successfuly!");
    long long cal_time3 = utility::CTimeHelper::GetTimeIntervalMicroseconds(start_time_dis);
    threadLogger_->info("获取左右边界用时: {} ms", 0.001 * cal_time3);

    RestoreData(path); // 数据恢复
    threadLogger_->info("RestoreData() Successfuly!");
    for (auto i : path) {
        threadLogger_->info("x:{} y:{} angle:{} curvature:{} direction:{} ", i.x, i.y, i.angle / M_PI * 180.0, i.curvature, i.direction);
    }


    return PlanResult::Plan_OK;
}
void OptimalPath::removeDuplicates(Path& input, Path& result) {
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
                // cout << "本次调用RS函数的起点坐标：" << temp_start_point.x << "  " << temp_start_point.y << "  " << temp_start_point.angle << "终点坐标" << end_f_.x << "  " << end_f_.y << "  " << end_f_.angle << endl;
                if ((true == my_r_s_curve.PlanRSPath(temp_start_point, end_f_, path_r_s_, plan_path_rule_)) && (MotionDirection::Backward == path_r_s_.back().direction)) {
                    if (false == collison_check_.IsRSPathCollision(path_r_s_)) {
                        threadLogger_->info("RS曲线Backward_Fitting oneshot成功，一共oneshot了 {}  次 ", All);
                        // 对RS曲线规划结果进行角度规划统一到[0,2*M_PI)
                        for (auto& i : path_r_s_) {
                            if (i.angle < 0) i.angle += 2 * M_PI;
                            threadLogger_->info("{} {} {} {}", i.x, i.y, i.angle / M_PI * 180.0, i.direction);
                        }
                        return true;
                    }
                    else {
                        // threadLogger_->info("尝试RS曲线拟合，RS曲线拟合成功，但碰撞检测失败");
                    }
                }
                else {
                    // threadLogger_->info("尝试RS曲线拟合，RS曲线因加入构型限制，规划失败");
                }
                break;
            case FittingDirection::Forword_Fitting:
                // threadLogger_->info("本次调用RS函数的起点坐标：({},{},{}),终点坐标:({},{},{})", temp_start_point.x, temp_start_point.y, temp_start_point.angle, end_r_.x, end_r_.y, end_r_.angle);
                if ((true == my_r_s_curve.PlanRSPath(temp_start_point, end_r_, path_r_s_, plan_path_rule_)) && (MotionDirection::Forward == path_r_s_.back().direction)) {
                    if (false == collison_check_.IsRSPathCollision(path_r_s_)) {
                        threadLogger_->info("RS曲线Forword_Fitting成功，一共oneshot了{}次 ", All);
                        // 对RS曲线规划结果进行角度规划统一到[0,2*M_PI)
                        for (auto& i : path_r_s_) {
                            if (i.angle < 0) i.angle += 2 * M_PI;
                        }
                        for (int i = 0; i < path_r_s_.size() - 1; i++) {
                            threadLogger_->info("x: {}  y: {}  yaw: {}  direction: {}", path_r_s_.at(i).x, path_r_s_.at(i).y, path_r_s_.at(i).angle / M_PI * 180.0, path_r_s_.at(i).direction);
                            threadLogger_->info("delta_s:{}", hypot(path_r_s_.at(i).x - path_r_s_.at(i + 1).x, path_r_s_.at(i).y - path_r_s_.at(i + 1).y));
                        }
                        return true;
                    }
                    else {
                        // threadLogger_->info("尝试RS曲线拟合，RS曲线拟合成功，路径点个数为{}个，但碰撞检测失败", path_r_s_.size());
                    }
                }
                else {
                    // threadLogger_->info("尝试RS曲线拟合，RS曲线因加入构型限制，规划失败");
                }
                break;
            case FittingDirection::Both_Fitting:
                if ((true == my_r_s_curve.PlanRSPath(temp_start_point, end_r_, path_r_s_, plan_path_rule_)) && (MotionDirection::Forward == path_r_s_.back().direction)) {
                    if (false == collison_check_.IsRSPathCollision(path_r_s_)) {
                        threadLogger_->info("RS曲线Forword_Fitting成功，一共oneshot了{}次 ", All);
                        for (auto& i : path_r_s_) {
                            if (i.angle < 0) i.angle += 2 * M_PI;
                            threadLogger_->info("x: {}  y: {}  yaw: {}  direction: {}", i.x, i.y, i.angle / M_PI * 180.0, i.direction);
                        }
                        fitting_direction_ = FittingDirection::Forword_Fitting;
                        return true;
                    }
                }
                else if ((true == my_r_s_curve.PlanRSPath(temp_start_point, end_f_, path_r_s_, plan_path_rule_)) && (MotionDirection::Backward == path_r_s_.back().direction)) {
                    if (false == collison_check_.IsRSPathCollision(path_r_s_)) {
                        threadLogger_->info("RS曲线Backward_Fitting oneshot成功，一共oneshot了 {}  次 ", All);
                        for (auto& i : path_r_s_) {
                            if (i.angle < 0) i.angle += 2 * M_PI;
                            threadLogger_->info("{} {} {} {}", i.x, i.y, i.angle / M_PI * 180.0, i.direction);
                        }
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
    if (plan_path_rule_ == PlanRule::Forward_All_Time || plan_path_rule_ == PlanRule::Start_Front_End_Back) {
        start_d_ = Forward;
        end_d_   = Forward;
    }
    else if (plan_path_rule_ == PlanRule::Backward_All_Time || plan_path_rule_ == PlanRule::Start_Back_End_Front) {
        start_d_ = Backward;
        end_d_   = Backward;
    }
    else {
        start_d_ = Forward;
        end_d_   = Backward;
    }
    // 计算转向角离散增量
    double delta_angle1 = 0, delta_angle2 = 0;
    if (m_vehicle_param_.is_light) {
        delta_angle1 = 2 * m_vehicle_param_.light_forward_max_steering / (m_vehicle_param_.angle_discrete_num - 1);
        delta_angle2 = 2 * m_vehicle_param_.light_backward_max_steering / (m_vehicle_param_.angle_discrete_num - 1);
    }
    else {
        delta_angle1 = 2 * m_vehicle_param_.heavy_forward_max_steering / (m_vehicle_param_.angle_discrete_num - 1);
        delta_angle2 = 2 * m_vehicle_param_.heavy_backward_max_steering / (m_vehicle_param_.angle_discrete_num - 1);
    }
    for (unsigned int i = 0; i < m_vehicle_param_.angle_discrete_num; ++i) {
        double temp_steering1 = 0, temp_steering2 = 0;
        if (m_vehicle_param_.is_light) {
            temp_steering1 = -1.0 * m_vehicle_param_.light_forward_max_steering + i * delta_angle1;
            temp_steering2 = -1.0 * m_vehicle_param_.light_backward_max_steering + i * delta_angle2;
        }
        else {
            temp_steering1 = -1.0 * m_vehicle_param_.heavy_forward_max_steering + i * delta_angle1;
            temp_steering2 = -1.0 * m_vehicle_param_.heavy_backward_max_steering + i * delta_angle2;
        }

        Vertex3D end_point;

        for (MotionDirection direction = start_d_; direction <= end_d_; direction = (MotionDirection)(direction + 1)) {
            // 根据车辆当前点位置、拓展方向和角度，得到拓展终点消息
            utility::CTimeClock start_time_rs_;
            double              temp_steering = 0;
            if (MotionDirection::Forward == direction) {
                temp_steering = temp_steering1;
            }
            else {
                temp_steering = temp_steering2;
            }
            VehDynam(current_point, direction, temp_steering, end_point);
            time1 += utility::CTimeHelper::GetTimeIntervalMicroseconds(start_time_rs_);
            end_point.id = Vertex2Hash(end_point); // 计算哈希值索引
            // 判断拓展点是否碰撞
            Point               temp_point(end_point.x, end_point.y, end_point.z, end_point.angle, end_point.direction);
            utility::CTimeClock start_time_rs;
            // threadLogger_->info("检测运动学拓展的点({} {} {})是否碰撞", end_point.x, end_point.y, end_point.angle / M_PI * 180.0);
            flag = collison_check_.IsVehicleCollision(temp_point);

            time2 += utility::CTimeHelper::GetTimeIntervalMicroseconds(start_time_rs);
            utility::CTimeClock start_time_rs__;
            if (flag == false) {
                // threadLogger_->info("不碰撞");
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
                            while (iter->second.id != end_point.id && fabs(iter->second.f - f) < 1e-6) {
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
                    end_point.f             = end_point.g + end_point.h;
                    open_map_[end_point.id] = end_point;
                    open_map_f_.insert(make_pair(end_point.f, end_point));
                }
            }
            else {
                // threadLogger_->info("探索过程中的点碰撞");
            }
            time3 += utility::CTimeHelper::GetTimeIntervalMicroseconds(start_time_rs__);
        }
    }


    time_dy       = time1;
    time_collsion = time2;
    time_other    = time3;
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

    threadLogger_->info("运动学搜索出来的点坐标");
    for (auto i : path_a_star_) {
        threadLogger_->info("x: {}  y: {}  yaw: {}  direction: {}", i.x, i.y, i.angle / M_PI * 180.0, i.direction);
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
    threadLogger_->info("PathIntegration--PlanRule:{}  本次HybridA*起点直线延长:{}  终点直线延长:{}", static_cast<int>(plan_path_rule_), start_offset_distance_, end_offset_distance_);

    if (plan_path_rule_ == PlanRule::Forward_All_Time || plan_path_rule_ == PlanRule::Start_Front_End_Back) {
        threadLogger_->info("Forward_All_Time or  Start_Front_End_Back  起点向前直线延长{} m", start_offset_distance_);
        temp_point.angle = actual_start_.angle;
        for (double i = 0; i <= start_offset_distance_ + 1e-3; i += m_vehicle_param_.hybridastar_step_length) {
            temp_point.x         = actual_start_.x + i * cos(actual_start_.angle);
            temp_point.y         = actual_start_.y + i * sin(actual_start_.angle);
            temp_point.z         = 0;
            temp_point.direction = MotionDirection::Forward;
            temp_path.emplace_back(temp_point);
        }
        temp_path.pop_back();
        path_a_star_.insert(path_a_star_.begin(), temp_path.begin(), temp_path.end());
        path_a_star_.pop_back();
    }

    if (plan_path_rule_ == PlanRule::Backward_All_Time || plan_path_rule_ == PlanRule::Start_Back_End_Front) {
        if (path_a_star_.size() >= 2) {
            if (path_a_star_.at(0).direction == 0 && path_a_star_.at(1).direction == 1) {
                path_a_star_.at(0).direction = MotionDirection::Backward;
            }
        }
        if (path_a_star_.at(0).direction == 0) {
            path_a_star_.at(0).direction = MotionDirection::Backward;
        }
        threadLogger_->info("Backward_All_Time or Start_Back_End_Front  起点向后直线延长{} m", start_offset_distance_);
        temp_point.angle = actual_start_.angle;
        for (double i = 0; i <= start_offset_distance_ + 1e-3; i += m_vehicle_param_.hybridastar_step_length) {
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
    threadLogger_->info("拼接完起点的路径，信息如下");
    for (auto i : path_a_star_) {
        threadLogger_->info("x: {}  y: {}  yaw: {}  direction: {}", i.x, i.y, i.angle / M_PI * 180.0, i.direction);
    }
    // 拼接RS路径
    path_a_star_.insert(path_a_star_.end(), path_r_s_.begin(), path_r_s_.end());
    Path().swap(path_r_s_);

    threadLogger_->info("拼接完RS路径");
    for (auto i : path_a_star_) {
        threadLogger_->info("x: {}  y: {}  yaw: {}  direction: {}", i.x, i.y, i.angle / M_PI * 180.0, i.direction);
    }

    // 拼接终点直线路径
    if (fitting_direction_ == FittingDirection::Forword_Fitting) // 前进直线拼接
    {
        Point temp_point;
        temp_point.angle = end_r_.angle;
        // cout << "temp_point.angle:" << temp_point.angle << endl;
        for (double i = m_vehicle_param_.hybridastar_step_length; i <= end_offset_distance_; i += m_vehicle_param_.hybridastar_step_length) {
            temp_point.x         = end_r_.x + i * cos(end_r_.angle);
            temp_point.y         = end_r_.y + i * sin(end_r_.angle);
            temp_point.z         = 0;
            temp_point.direction = MotionDirection::Forward;
            // cout << "temp_point.angle" << temp_point.angle << endl;
            path_a_star_.push_back(temp_point);
        }
        // threadLogger_->info("拼接完成终点的路径");
        // for (auto i : path_a_star_) {
        //     threadLogger_->info("x: {}  y: {}  yaw: {}  direction: {}", i.x, i.y, i.angle / M_PI * 180.0, i.direction);
        // }
    }
    else // 倒退直线拼接
    {
        Point temp_point;
        temp_point.angle = end_f_.angle;
        for (double i = m_vehicle_param_.hybridastar_step_length; i <= end_offset_distance_; i += m_vehicle_param_.hybridastar_step_length) {
            temp_point.x         = end_f_.x - i * cos(end_f_.angle);
            temp_point.y         = end_f_.y - i * sin(end_f_.angle);
            temp_point.z         = 0;
            temp_point.direction = MotionDirection::Backward;
            path_a_star_.push_back(temp_point);
        }
        // threadLogger_->info("拼接完成终点的路径");
        // for (auto i : path_a_star_) {
        //     threadLogger_->info("x: {}  y: {}  yaw: {}  direction: {}", i.x, i.y, i.angle / M_PI * 180.0, i.direction);
        // }
    }

    threadLogger_->info("拼接完成终点的路径");
    for (auto i : path_a_star_) {
        threadLogger_->info("x: {}  y: {}  yaw: {}  direction: {}  curvature:{}", i.x, i.y, i.angle / M_PI * 180.0, i.direction, i.curvature);
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
    double coeff = hypot(end_point.x - start_.x, end_point.y - start_.y) > m_vehicle_param_.linear_preferred_distance ? 1 : 5;
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
    double a_start_h = 0;


    utility::CTimeClock init_time;
    // 以A*搜索结果为启发值
    Node2D current2D(static_cast<short>(floor(point.x / m_vehicle_param_.grid_dist)), static_cast<short>(floor(point.y / m_vehicle_param_.grid_dist)), 0, 0);
    auto   iter = nodes2D_map_.find(current2D.getIdx());
    if (iter == nodes2D_map_.end() || nodes2D_map_[current2D.getIdx()].isOpen()) {
        Node2D        goal2D(static_cast<short>(floor(end_.x / m_vehicle_param_.grid_dist)), static_cast<short>(floor(end_.y / m_vehicle_param_.grid_dist)), 0, 0);
        int           total = 0;
        IntCoordinate temp_point;
        temp_point.x = current2D.getX();
        temp_point.y = current2D.getY();
        if (IsBoundGrid(temp_point)) {
            threadLogger_->info("该节点为障碍物节点,坐标为{} {}", temp_point.x, temp_point.y);
            a_start_h = numeric_limits<double>::max();
        }
        else {
            // threadLogger_->info("该节点非障碍物节点");
            a_start_h = AStarSearch2D(goal2D, current2D, total);
        }
        long long init_time_end = utility::CTimeHelper::GetTimeIntervalMicroseconds(init_time); // 开始时间精确到微秒
        // threadLogger_->info("本次A*搜素{}轮，耗时:{} ms,点坐标：{} {}", total, init_time_end * 0.001, temp_point.x, temp_point.y);
    }
    else {
        // threadLogger_->info("该节点可通过增量式A*直接查询");
        a_start_h = iter->second.getG();
    }


    // Node2D current2D_(static_cast<short>(floor(point.x / m_vehicle_param_.grid_dist)), static_cast<short>(floor(point.y / m_vehicle_param_.grid_dist)), 0, 0);
    // Node2D goal2D_(static_cast<short>(floor(end_.x / m_vehicle_param_.grid_dist)), static_cast<short>(floor(end_.y / m_vehicle_param_.grid_dist)), 0, 0);
    // point.h = hypot(goal2D_.getX() - current2D_.getX(), goal2D_.getY() - current2D_.getY());

    point.h = a_start_h;
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
    // threadLogger_->info("start = {},{}", start.getX(), start.getY());
    // threadLogger_->info("goal = {},{}", goal.getX(), goal.getY());

    start.updateH(goal);
    // threadLogger_->info("start.getH():{}", start.getH());
    start.open();
    unsigned long long hash = start.getIdx() | (static_cast<unsigned long long>(start.getF() * 1000) << 32); // 包含点的F值和索引
    nodes2D_set_.insert(hash);                                                                               // 存入起点
    nodes2D_map_[start.getIdx()] = start;
    Node2D       nPred, nSucc; // 当前操作的点和其继任点
    unsigned int iPred, iSucc;
    num = 0;
    float newG;
    // threadLogger_->info("nodes2D_set_.size():{} ", nodes2D_set_.size());
    // threadLogger_->info("nodes2D_map_.size():{} ", nodes2D_map_.size());
    clock_t start_time = clock();
    while (!nodes2D_set_.empty()) {
        clock_t current_time = clock();
        double  elapsed_time = static_cast<double>(current_time - start_time) / CLOCKS_PER_SEC;

        if (elapsed_time > 1.0) {
            break;
        }
        num++;
        // threadLogger_->info("nodes2D_set_.size():{}", nodes2D_set_.size());
        // threadLogger_->info("nodes2D_map_.size():{} ", nodes2D_map_.size());

        // if (num > 1500) {
        //     threadLogger_->info("搜索超过3000轮,强制退出");
        //     break;
        // }
        // threadLogger_->info("第{}轮,开始从node2D_set_中挑选最小代价点", num);
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
            nodes2D_set_.erase(nodes2D_set_.begin());
            nodes2D_map_[iPred].close();
            nodes2D_map_[iPred].discover();

            for (int i = 0; i < Node2D::dir; ++i) {
                nSucc = nPred.createSuccessor(i);
                // threadLogger_->info("");
                // threadLogger_->info("nSucc :{} {}", nSucc.getX(), nSucc.getY());
                iSucc = nSucc.getIdx();
                // threadLogger_->info("iSucc :{}", iSucc);
                IntCoordinate point(nSucc.getX(), nSucc.getY(), 0);
                bool          flag_in_nodes2D = (nodes2D_map_.find(iSucc) != nodes2D_map_.end());
                if (!IsBoundGrid(point) && (!flag_in_nodes2D || !nodes2D_map_[iSucc].isClosed())) { // 节点不是边界点，节点没有探索过，或者探索过，但是不是close的，就可以作为继承点
                    // threadLogger_->info("节点不是边界点，节点没有探索过，或者探索过，但是不是close的");
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
                    nodes2D_set_.insert(hash);
                    nodes2D_map_[iSucc] = nSucc;
                }
                else {
                    if (IsBoundGrid(point)) {
                        // threadLogger_->info("{} {}该点是边界点", point.x, point.y);
                    }
                    else {
                        // threadLogger_->info("{} {}该点已经被探索过，但已经进close", point.x, point.y);
                    }
                }
            }
            if (nPred == goal) {
                // threadLogger_->info("nPred is goal");
                return nPred.getG();
            }
        }
    }
    cout << "目标点不可达" << endl;
    threadLogger_->info("目标点不可达");
    return numeric_limits<double>::max();
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
    for (int i = 0; i < offset_road_bound_.size(); ++i) {
        for (int j = 0; j < offset_road_bound_.at(i).size(); ++j) {
            temp_point.x = static_cast<short>(floor(offset_road_bound_.at(i).at(j).x / m_vehicle_param_.grid_dist));
            temp_point.y = static_cast<short>(floor(offset_road_bound_.at(i).at(j).y / m_vehicle_param_.grid_dist));
            hash         = Coordinate2Hash(temp_point);
            bound_set_.insert(hash);
        }
    }

    // 计算障碍物边界栅格
    for (int i = 0; i < offset_obstacle_bound_.size(); ++i) {
        for (int j = 0; j < offset_obstacle_bound_.at(i).size(); ++j) {
            temp_point.x = static_cast<short>(floor(offset_obstacle_bound_.at(i).at(j).x / m_vehicle_param_.grid_dist));
            temp_point.y = static_cast<short>(floor(offset_obstacle_bound_.at(i).at(j).y / m_vehicle_param_.grid_dist));
            hash         = Coordinate2Hash(temp_point);
            bound_set_.insert(hash);
        }
    }
    threadLogger_->info("GenerateBoundSet--bound_set_.size():{}", bound_set_.size());

    bound_set_for_Astar_ = bound_set_;

    // // 计算A*地图边界栅格
    // float         radius = m_vehicle_param_.veh_center_2_side; // 实际上，我们使用半径的两倍作为正方形的边长
    // IntCoordinate tp;
    // for (int i = 0; i < offset_road_bound_.size(); ++i) {
    //     for (int j = 0; j < offset_road_bound_.at(i).size(); ++j) {
    //         temp_point.x = static_cast<short>(floor(offset_road_bound_.at(i).at(j).x / m_vehicle_param_.grid_dist));
    //         temp_point.y = static_cast<short>(floor(offset_road_bound_.at(i).at(j).y / m_vehicle_param_.grid_dist));

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
    // for (int i = 0; i < offset_obstacle_bound_.size(); ++i) {
    //     for (int j = 0; j < offset_obstacle_bound_.at(i).size(); ++j) {
    //         temp_point.x = static_cast<short>(floor(offset_obstacle_bound_.at(i).at(j).x / m_vehicle_param_.grid_dist));
    //         temp_point.y = static_cast<short>(floor(offset_obstacle_bound_.at(i).at(j).y / m_vehicle_param_.grid_dist));
    //         for (int i = 0; i < 360; i++) {
    //             tp.x = temp_point.x + radius * cos(i / 180.0 * M_PI);
    //             tp.y = temp_point.y + radius * sin(i / 180.0 * M_PI);
    //             hash = Coordinate2Hash(tp);
    //             bound_set_for_Astar_.insert(hash);
    //         }
    //     }
    // }
}


void OptimalPath::CurvatureCal(Path& input_path) {
    Point  p1, p2, p3;
    double crossProduct = 0;
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

                threadLogger_->info("点信息({},{})  a:{} b:{} c:{} s:{} area:{}", input_path.at(i).x, input_path.at(i).y, a, b, c, s, area);
                double r = (a * b * c) / (4.0 * area);
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