/* ****************************************
 * 作者: cxp(chenxinpeng_hnu@163.com)、jh、yzy(yangzeyu@wicri.org)
 * 日期: 2020/08/21
 * 内容: 完成函数功能实现,完善修改程序逻辑
 * 功能：考虑到达时间、速度平滑性以及加速度限制，
 *       对一条不同路段赋有不同最高限速的路径
 *       (可能包含多段前进、后退路段)规划全局速度
 * ****************************************/
#include "global_speed_planning.h"

#define eps 1e-4

using namespace GlobalPlanning;

// void GlobalSpeedPlanning(){}

/**
 *@brief: 初始化速度规划参数
 *@param [in] m_veh_param 车辆参数
 *return
 */
void GlobalSpeedPlanning::InitSpeedParam(_VehicleParam m_veh_param) {
    max_acceleration      = m_veh_param.max_acceleration;
    min_acceleration      = m_veh_param.min_acceleration;
    speed_error_term      = m_veh_param.speed_error_term;
    speed_smooth_term     = m_veh_param.speed_smooth_term;
    speed_discrete_number = m_veh_param.speed_discrete_number;
    reverse_speed         = m_veh_param.reverse_speed;


    threadLogger_->info("max_acceleration ={} ", max_acceleration);

    threadLogger_->info("min_acceleration ={} ", min_acceleration);


    threadLogger_->info("speed_error_term ={} ", speed_error_term);

    threadLogger_->info("speed_smooth_term ={} ", speed_smooth_term);

    threadLogger_->info("speed_discrete_number ={} ", speed_discrete_number);

    threadLogger_->info("reverse_speed ={} ", reverse_speed);
    vehicle_param = m_veh_param;
}
/**
 * @brief: 速度规划接口函数
 * @param  total_time：总时间需求；departure_time：出发时间；trajectory：规划后的路径；mode：规划模式：
 * 0：最短时间策略；1：准点策略
 * @return true：规划成功；false：规划失败
 */
bool GlobalSpeedPlanning::SpeedPlanning(vector<_TrajectoryPoint>& trajectory, const _VehicleParam m_veh_param, const int total_time, const int departure_time) {
    InitSpeedParam(m_veh_param);
    trajectory_fragments.clear();
    key_points.clear();
    global_speeds.clear();
    opti_global_speeds.clear();
    final_trajectory_points.clear();
    trajectory_points = trajectory;


    /*限速设置*/
    ReplanPointMaxSpeed();
    /* 根据前进、后退分割点对全局路径进行分割 */
    if (!SplitPath()) return false;
    /* 获取每一段路径的关键点 */
    if (!GetKeypoint()) return false;
    // 获取速度规划的关键点
    if (!AdpKeyPoints()) return false;
    // 减速安全检查，调整关键点
    if (!KeyPointsDecelerationCheck()) return false;

    if (!PlanCase0(departure_time)) {
        threadLogger_->error(" ...The Shortest_Time mode speed planning failed...");

        return false;
    }


    trajectory = final_trajectory_points;
    return true;
}


/**
 *@brief: 模式0 Shortest_Time 速度规划的主流程函
 *@param  departure_time：出发时间
 *return  true: 规划成功；false：规划失败
 */
bool GlobalSpeedPlanning::PlanCase0(const int departure_time) {
    threadLogger_->info("key_points.size() = {}", key_points.size());

    for (unsigned char i = 0; i < key_points.size(); i++) {
        threadLogger_->info(" ...plan for the {} the segment...", (float)(i + 1));

        /* 得到梯形速度曲线 */
        if (!TrapezoidalSpeedPlanning(i)) {
            threadLogger_->error(" ...TrapezoidalSpeedPlanning failed in {} 端路径... ", (float)i);

            return false;
        }


        threadLogger_->info("begin SpeedCurveSmooth");

        /* 对速度曲线进行平滑处理 */
        SpeedCurveSmooth(i);


        threadLogger_->info("begin SpeedCurveInterpolation");


        SpeedCurveInterpolation(i);
    }
    AddTimeInformation(departure_time);
    final_trajectory_points.clear();
    for (unsigned char i = 0; i < key_points.size(); i++) {
        for (int j = 0; j < trajectory_fragments.at(i).size(); j++) {
            if (trajectory_fragments.at(i).at(j).direction == 1) {
                trajectory_fragments.at(i).at(j).speed = -trajectory_fragments.at(i).at(j).speed;
            }
        }
        final_trajectory_points.insert(final_trajectory_points.end(), trajectory_fragments.at(i).begin(), trajectory_fragments.at(i).end());
    }

    return true;
}


/**
 * @brief: 梯形速度规划函数
 * @param  num：trajectory_fragments中的第num条
 * @return 无
 */
bool GlobalSpeedPlanning::TrapezoidalSpeedPlanning(unsigned char num) {
    vector<SparseSpeedPoint> temp_sparsespeedpoints;
    vector<SparseSpeedPoint> temp_sparsespeedpoints_all;
    vector<KeyPoint>         temp_keypoint = key_points.at(num);
    threadLogger_->info("temp_keypoint.size():{}", temp_keypoint.size());

    for (int i = 0; i < temp_keypoint.size(); i++) {
        threadLogger_->info("index:{}, speed_limit_left :{}, speed_limit_right:{}", temp_keypoint.at(i).index, temp_keypoint.at(i).speed_limit_left, temp_keypoint.at(i).speed_limit_right);
    }
    KeyPoint         keypoint1, keypoint2;
    SparseSpeedPoint temp_sparsepoint;
    float            last_speed;   // PlanForSingleSegment()函数规划后，车辆能够达到的速度，最后一个点的速度
    if (2 == temp_keypoint.size()) // 若只有两个关键点，后面合成一条路径的时候再来根据方向，改变速度符号
    {
        threadLogger_->error("2 == temp_keypoint.size()");
        keypoint1 = temp_keypoint.at(0);
        keypoint2 = temp_keypoint.at(1);
        if (!PlanForSingleSegment(num, keypoint1, keypoint2, temp_sparsespeedpoints, last_speed)) {
            threadLogger_->error("...Plan for the segment {} failed...", (float)num);

            return false;
        }
        /* 加入最后一个点 */
        temp_sparsepoint.index = keypoint2.index;
        temp_sparsepoint.speed = last_speed;
        //     threadLogger_->info("...last_speed is "<<last_speed<<" ..."<<endl;
        temp_sparsespeedpoints.push_back(temp_sparsepoint);
        threadLogger_->info("此段规划完毕，temp_sparsespeedpoints.size():{}", temp_sparsespeedpoints.size());
        global_speeds.emplace_back(temp_sparsespeedpoints);
        return true;
    }
    else if (2 < temp_keypoint.size()) // 若大于两个关键点
    {
        threadLogger_->info("2 <temp_keypoint.size()");
        temp_sparsespeedpoints_all.clear();
        /*循环遍历关键点集*/
        float last_speed = temp_keypoint.at(0).speed_limit_left;
        for (unsigned int i = 0; i < temp_keypoint.size() - 1; i++) {
            keypoint1 = temp_keypoint.at(i);
            keypoint2 = temp_keypoint.at(i + 1);
            //           threadLogger_->info("...keypoint1.index= "<<keypoint1.index<<"..."<<endl;
            //           threadLogger_->info("...keypoint2.index= "<<keypoint2.index<<"..."<<endl;
            keypoint1.speed_limit_left = last_speed;
            if (!PlanForSingleSegment(num, keypoint1, keypoint2, temp_sparsespeedpoints, last_speed)) {
                threadLogger_->error("...Plan for the segment {} failed...", (float)num);

                return false;
            }
            threadLogger_->info("...last_speed is {} ", last_speed);

            temp_sparsespeedpoints_all.insert(temp_sparsespeedpoints_all.end(), temp_sparsespeedpoints.begin(), temp_sparsespeedpoints.end());
        }
        /*加入最后一个点*/
        temp_sparsepoint.index = keypoint2.index;
        threadLogger_->info("99999 last_speed ={} ", last_speed);

        temp_sparsepoint.speed = last_speed;
        threadLogger_->info("last point temp_sparsepoint.speed = {}", temp_sparsepoint.speed);

        temp_sparsespeedpoints_all.emplace_back(temp_sparsepoint);
        threadLogger_->info("此段规划完毕，temp_sparsespeedpoints.size():{}", temp_sparsespeedpoints.size());
        global_speeds.emplace_back(temp_sparsespeedpoints_all);

        return true;
    }
    else {
        threadLogger_->error("...Plan for the segment {}  failed, the keypoint number is less than 2...", (float)num);

        return false;
    }
}
bool GlobalSpeedPlanning::KeyPointsDecelerationCheck() {
    // 这个函数主要确保降速
    bool flag = true;
    threadLogger_->info("开始KeyPointsDecelerationCheck() ,路径段落个数:{}", key_points.size());

    float                    v1, v2;
    KeyPoint                 keypoint1, keypoint2;
    vector<_TrajectoryPoint> temp_traj;
    for (int i = 0; i < key_points.size(); i++) {
        temp_traj = trajectory_fragments.at(i);
        for (int j = 0; j < key_points.at(i).size() - 1; j++) {
            keypoint1 = key_points.at(i).at(j);
            keypoint2 = key_points.at(i).at(j + 1);
            v1        = keypoint1.speed_limit_right;
            v2        = keypoint2.speed_limit_right;
            threadLogger_->info("第{}段的第{}个关键点的索引 {},左限速 {},右限速 {}", (float)(i + 1), j + 1, key_points.at(i).at(j).index, key_points.at(i).at(j).speed_limit_left, key_points.at(i).at(j).speed_limit_right);

            threadLogger_->info("第{}段的第{}个关键点的索引 {},左限速 {},右限速 {}", (float)(i + 1), j + 2, key_points.at(i).at(j + 1).index, key_points.at(i).at(j + 1).speed_limit_left, key_points.at(i).at(j + 1).speed_limit_right);

            // 遍历的过程中，发现 v1>v2的情况就需要进行降速合理性检查，不符合要求就要调整，并重新执行for循环
            if (v1 > v2) {
                threadLogger_->info("减速检查");

                float s_total = temp_traj.at(keypoint2.index).distance - temp_traj.at(keypoint1.index).distance; // 该路段的路径长度(可能为弧线)
                float s_min   = (pow(v2, 2) - pow(v1, 2)) / (2 * min_acceleration);                              // v1_left加速到v1_right所需的最小欧式距离

                if ((s_total + eps) < s_min) // 若减速距离不够，得将v1结合车辆最大减速度进行合理调整
                {
                    threadLogger_->warn("warnning ,减速距离不够");

                    threadLogger_->info("s_total = {}", s_total);

                    threadLogger_->info("s_min ={} ", s_min);

                    key_points.at(i).at(j).speed_limit_right    = sqrt(pow(v2, 2) + 2 * (max_acceleration - 0.1) * s_total);
                    key_points.at(i).at(j + 1).speed_limit_left = key_points.at(i).at(j).speed_limit_right;
                    threadLogger_->info("右限速调整为：{}", key_points.at(i).at(j).speed_limit_right);

                    flag = false;
                }
                else {
                    threadLogger_->info("s_total = {}", s_total);

                    threadLogger_->info("s_min ={} ", s_min);

                    threadLogger_->info("PASS ,减速距离达标");
                }
            }
            if (flag == false) {
                j = -1; // 从新开始遍历这个key_points
                threadLogger_->info("重新开始一轮");

                flag = true;
            }
        }
    }
    threadLogger_->info("结束KeyPointsDecelerationCheck() ,路径段落个数:{}", key_points.size());

    return true;
}
bool GlobalSpeedPlanning::AdpKeyPoints() {
    bool flag = true;
    threadLogger_->info("开始AdpKeyPoints[new] ,路径段落个数:{}", key_points.size());

    cout << "开始AdpKeyPoints ,路径段落个数:" << key_points.size() << endl;
    vector<vector<KeyPoint>> temp_key_points;
    vector<KeyPoint>         temp_point;
    vector<_TrajectoryPoint> temp_traj;
    temp_key_points     = key_points;
    unsigned char index = 0;
    while (flag) {
        threadLogger_->info("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");

        flag = false;
        key_points.clear();
        key_points = temp_key_points;
        temp_key_points.clear();
        for (int i = 0; i < key_points.size(); i++) {
            temp_traj.clear();
            threadLogger_->info("第{}段全局路径有{}个点", i + 1, trajectory_fragments.at(i).size());

            temp_traj = trajectory_fragments.at(i);
            temp_point.clear();
            if (key_points.at(i).size() < 2) {
                return false;
            }
            else {
                // 新的限速曲线平滑方式
                /*该循环中，如限速关键点符合优化条件，在进行优化后，若对keypoint1优化了，需将其将其添加到关键点集中；
                 若只对keypoint2进行优化，则直接continue，下一次循环时，keypoint1因未保存，将自动删除*/
                Deletekeypoints(key_points.at(i));
                for (int j = 0; j < key_points.at(i).size() - 1; j++) {
                    // threadLogger_->info("key_points.at(i).size() = " << key_points.at(i).size()<<  ;

                    float    v1_left, v1_right, v2_left, v2_right;
                    KeyPoint keypoint1, keypoint2;
                    keypoint1 = key_points.at(i).at(j);
                    keypoint2 = key_points.at(i).at(j + 1);
                    v1_left   = keypoint1.speed_limit_left;
                    v1_right  = keypoint1.speed_limit_right;
                    v2_left   = keypoint2.speed_limit_left;
                    v2_right  = keypoint2.speed_limit_right;
                    threadLogger_->info("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

                    threadLogger_->info("v1_index = {}", keypoint1.index);

                    threadLogger_->info("v1_left = {}", v1_left);

                    threadLogger_->info("v1_right = {}", v1_right);

                    threadLogger_->info("v2_index = {}", keypoint2.index);

                    threadLogger_->info("v2_left = {}", v2_left);

                    threadLogger_->info("v2_right  = {}", v2_right);

                    if (fabs(v1_right - v2_left) >= 0.01) {
                        threadLogger_->info("左右速度不等");

                        if (v1_right - v2_left > 0.01) {
                            key_points.at(i).at(j).speed_limit_right = v2_left;
                            temp_point.emplace_back(key_points.at(i).at(j));
                            flag = true;
                            continue;
                        }
                        else if (v2_left - v1_right > 0.01) {
                            key_points.at(i).at(j + 1).speed_limit_left = v1_right;
                            flag                                        = true;
                            continue;
                        }
                    }
                    // 为了避免短距离不合理加速，现引入以下限速关键点调整逻辑
                    /* 先升速，后降速，但降低不严重*/
                    if ((v1_left + eps) < v1_right && (v2_right + eps) < v1_right && v1_left <= (v2_right + eps)) {
                        // 判断距离 若距离符合 将中速降低为最小速度
                        float s_total = temp_traj.at(keypoint2.index).distance - temp_traj.at(keypoint1.index).distance;
                        float s_min   = (pow(v1_right, 2) - pow(v1_left, 2)) / (2 * max_acceleration) + (pow(v2_right, 2) - pow(v1_right, 2)) / (2 * min_acceleration) + 10; // v1_left加速到v1_right，然后再由v1_right减速到v2_right所需要的极限距离
                        threadLogger_->info("s_total = {}", s_total);

                        threadLogger_->info("s_min ={} ", s_min);

                        if ((v2_right - 0.0) > eps) // 最后的一段倒车轨迹，需要特殊处理
                        {
                            if ((s_total + eps) < s_min) // 若加速距离小于两关键点之间距离的一半
                            {
                                threadLogger_->info("不合理加速，现予以调整");

                                key_points.at(i).at(j).speed_limit_right    = v2_right; // 每一次的赋值,都是为了在下一个循环中使用当前的修改
                                key_points.at(i).at(j + 1).speed_limit_left = v2_right;
                                flag                                        = true;
                                temp_point.emplace_back(key_points.at(i).at(j));
                                continue;
                            }
                        }
                    }
                    /* 先升速，后降速，但降低严重的*/
                    if ((v1_left + eps) < v1_right && (v2_right + eps) < v1_right && v1_left > (v2_right + eps)) {
                        // 判断距离 若距离符合 将中速降低为最小速度
                        float s_total = temp_traj.at(keypoint2.index).distance - temp_traj.at(keypoint1.index).distance;
                        float s_min   = (pow(v1_right, 2) - pow(v1_left, 2)) / (2 * max_acceleration) + (pow(v2_right, 2) - pow(v1_right, 2)) / (2 * min_acceleration) + 10; // v1_left加速到v1_right，然后再由v1_right减速到v2_right所需要的极限距离
                        threadLogger_->info("s_total = {}", s_total);

                        threadLogger_->info("s_min ={} ", s_min);

                        if ((s_total + eps) < s_min) // 若加速距离小于两关键点之间距离的一半
                        {
                            threadLogger_->info("不合理加速，现予以调整");

                            key_points.at(i).at(j + 1).speed_limit_left = v1_left;
                            flag                                        = true;
                            continue;
                        }
                    }

                    threadLogger_->info("key_points.at(i).at(j).index = {}", key_points.at(i).at(j).index);

                    threadLogger_->info("key_points.at(i).at(j).left = {}", key_points.at(i).at(j).speed_limit_left);

                    threadLogger_->info("key_points.at(i).at(j).right = {}", key_points.at(i).at(j).speed_limit_right);

                    temp_point.emplace_back(key_points.at(i).at(j));
                }
                temp_point.emplace_back(key_points.at(i).back());
            }
            temp_key_points.emplace_back(temp_point);
        }
        index++;
        threadLogger_->info("index = {}", (int)index);

        if (index > 10000) return true;
    }

    key_points.clear();
    key_points = temp_key_points;

    // std::ofstream file_out;
    // file_out.open("key_point_information.txt");
    // for (size_t index = 0; index < key_points.size(); index++)
    // {
    //     for (size_t jndex = 0; jndex < key_points.at(index).size(); jndex++)
    //     {
    //         file_out << key_points.at(index).at(jndex).index << " " <<
    //         key_points.at(index).at(jndex).speed_limit_left << " " <<
    //         key_points.at(index).at(jndex).speed_limit_right << endl;
    //     }
    // }
    // file_out.close();

    threadLogger_->info("Function() AdpKeyPoints[new] End ");

    return true;
}

void GlobalSpeedPlanning::Deletekeypoints(std::vector<KeyPoint>& m_keypoints) {
    std::vector<KeyPoint> temp_keypoints;
    for (size_t index = 0; index < m_keypoints.size(); index++) {
        if (fabs(m_keypoints.at(index).speed_limit_left - m_keypoints.at(index).speed_limit_right) < 1e-4) {
            threadLogger_->info(" repate ");

            continue;
        }
        else {
            temp_keypoints.emplace_back(m_keypoints.at(index));
        }
    }
    m_keypoints.clear();
    m_keypoints = temp_keypoints;
    threadLogger_->info(" Functions Delete keypoints !!");
}

/**
 * @brief 对单个路段进行速度规划
 * @param [in]
 * num：trajectory_fragments中的第num条；keypoint1、keypoint2：该路段的两个关键点；temp_sparsespeedpoints：规划后的速度点；last_speed：规划后的末速度
 * @param [return]
 */
bool GlobalSpeedPlanning::PlanForSingleSegment(unsigned char num, KeyPoint keypoint1, KeyPoint keypoint2, vector<SparseSpeedPoint>& temp_sparsespeedpoints, float& last_speed) {
    temp_sparsespeedpoints.clear();
    vector<_TrajectoryPoint> temp_traj = trajectory_fragments.at(num);
    SparseSpeedPoint         temp_sparsepoint;
    float                    v0, v1, v2;
    v0 = keypoint1.speed_limit_left;
    v1 = keypoint1.speed_limit_right;
    v2 = keypoint2.speed_limit_right;
    threadLogger_->info("v0= {}", v0);

    threadLogger_->info("v1= {}", v1);

    threadLogger_->info("v2= {}", v2);

    if (fabs(v1 - keypoint2.speed_limit_left) > 0.01) // 关键点设置错误，导致两关键点之间出现两个不同最大速度
    {
        threadLogger_->info("keypoint1.index ={}  {}  {} ", keypoint1.index, keypoint1.speed_limit_left, keypoint1.speed_limit_right);

        threadLogger_->info("keypoint2.index ={}  {}  {} ", keypoint2.index, keypoint2.speed_limit_left, keypoint2.speed_limit_right);

        threadLogger_->info("...key_point1.speed_limit_right != key_point2.speed_limit_left...");

        return false;
    }
    if (v0 > v1 + 0.05) // v0 为前一段规划后的末端车速或者实际初始车速，不能比该段的最大车速大
    {
        threadLogger_->info("...The real speed > the max speed...");

        return false;
    }

    /* 情况1: v0 = v1 && v2 >= v1:
      在两关键点之间生成稀疏速度点,并把v1作为该段的速度 */
    if (fabs(v0 - v1) < 0.01 && v2 >= v1) {
        threadLogger_->info("...Case 1...");

        unsigned int i = 0;
        for (i = keypoint1.index; i < keypoint2.index; i += speed_discrete_number) // 不从key_point1.index开始
        {
            temp_sparsepoint.index = i;
            temp_sparsepoint.speed = v1;
            temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
        }
        last_speed = v1;
        return true;
    }

    /* 情况2: v0 = v1 && v2 < v1:
      需要减速，先判断能否完成减速，不能完成减速，就判定为规划失败 */
    if (fabs(v0 - v1) < 0.01 && v2 < v1) {
        threadLogger_->info("...Case 2...");

        float s_total = temp_traj.at(keypoint2.index).distance - temp_traj.at(keypoint1.index).distance; // 该路段的路径长度
        float s_min   = (pow(v2, 2) - pow(v1, 2)) / (2 * min_acceleration);                              // 减速到v2所需的最小距离
        if (s_min - s_total > 0.001) {
            threadLogger_->error("keypoint1.index:{},keypoint2.index:{}", keypoint1.index, keypoint2.index);

            threadLogger_->error("...Case 4: s_total ={}  s_min ={}  s_total < s_min...", s_total, s_min);

            // threadLogger_->error("..Case 2: s_total < s_min...");
            return false;
        }
        else {
            float s_temp, s_d;
            float s_1 = s_total - s_min; // 匀速截止的距离
            float s_0 = temp_traj.at(keypoint1.index).distance;
            for (unsigned int i = keypoint1.index; i < keypoint2.index; i += speed_discrete_number) {
                s_temp = fabs(temp_traj.at(i).distance - s_0);
                if (s_temp <= s_1) {
                    temp_sparsepoint.index = i;
                    temp_sparsepoint.speed = v1;
                    temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
                }
                else {
                    s_d                    = s_temp - s_1; // 减速距离，从v1减速
                    temp_sparsepoint.index = i;
                    temp_sparsepoint.speed = sqrt(pow(v1, 2) + 2 * min_acceleration * s_d); // 最小加速度为负
                    temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
                }
            }
            last_speed = v2;
            return true;
        }
    }

    /* 情况3: v0 < v1 && v2 >= v1:
    需要一直加速 */
    if (v0 < v1 && v2 >= v1) {
        threadLogger_->info("...Case 3...");

        float s_total = temp_traj.at(keypoint2.index).distance - temp_traj.at(keypoint1.index).distance; // 该路段的路径长度
        float s_min   = (pow(v1, 2) - pow(v0, 2)) / (2 * max_acceleration);                              // 加速到v2所需的最小距离
        float s_temp;
        float s_0 = temp_traj.at(keypoint1.index).distance;
        for (unsigned int i = keypoint1.index; i < keypoint2.index; i += speed_discrete_number) {
            s_temp = fabs(temp_traj.at(i).distance - s_0); // 距起点的距离
            if (s_temp < s_min) {
                temp_sparsepoint.index = i;
                temp_sparsepoint.speed = sqrt(pow(v0, 2) + 2 * max_acceleration * s_temp);
                temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
            }
            else {
                temp_sparsepoint.index = i;
                temp_sparsepoint.speed = v1;
                temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
            }
        }
        if (s_total < s_min) // 一直在加速
            last_speed = sqrt(pow(v0, 2) + 2 * max_acceleration * s_total);
        else
            last_speed = v1;
        return true;
    }

    /* 情况4: v0 < v1 && v2 < v1 && v2 <= v0:
   需要加速，再减速 */
    if (v0 < v1 && v2 < v1 && v2 <= v0) {
        threadLogger_->info("...Case 4...");

        threadLogger_->info("keypoint1.index ={} ", keypoint1.index);

        threadLogger_->info("keypoint2.index ={} ", keypoint2.index);

        float s_total = temp_traj.at(keypoint2.index).distance - temp_traj.at(keypoint1.index).distance; // 该路段的路径长度
        float s_min   = (pow(v2, 2) - pow(v0, 2)) / (2 * min_acceleration);                              // 减速到v2所需的最小距离
        if (s_total < s_min) {
            threadLogger_->error("...Case 4: s_total ={}  s_min ={}  s_total < s_min...", s_total, s_min);

            return false;
        }
        float s_acc = (pow(v1, 2) - pow(v0, 2)) / (2 * max_acceleration);
        float s_dec = (pow(v2, 2) - pow(v1, 2)) / (2 * min_acceleration);
        if (s_acc + s_dec < s_total) // 先加速到最大速度，再减速到v2
        {
            threadLogger_->info("先加速到最大速度，再减速到v2");

            float s_temp;
            float s_0 = temp_traj.at(keypoint1.index).distance;
            threadLogger_->error("...Case 4:s_0:{}", s_0);

            for (unsigned int i = keypoint1.index; i < keypoint2.index; i += speed_discrete_number) {
                s_temp = fabs(temp_traj.at(i).distance - s_0); // 距起点的距离
                threadLogger_->error("...Case 4:temp_traj.at(i).distance :{} ", temp_traj.at(i).distance);

                if (s_temp < s_acc) // 加速
                {
                    temp_sparsepoint.index = i;
                    temp_sparsepoint.speed = sqrt(pow(v0, 2) + 2 * max_acceleration * s_temp);

                    threadLogger_->error("...Case 4: temp_sparsepoint.speed :{} index:{} v0:{} s_temp:{}", temp_sparsepoint.speed, temp_sparsepoint.index, v0, s_temp);
                    temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
                }
                else if (s_temp < s_total - s_dec) // 匀速
                {
                    temp_sparsepoint.index = i;
                    temp_sparsepoint.speed = v1;
                    temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
                }
                else // 减速
                {
                    float s_d              = s_temp - (s_total - s_dec); // 减速距离
                    temp_sparsepoint.index = i;
                    temp_sparsepoint.speed = sqrt(pow(v1, 2) + 2 * min_acceleration * s_d);
                    temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
                }
            }
            last_speed = v2;
            threadLogger_->info("temp_sparsespeedpoints.size():{}", temp_sparsespeedpoints.size());
            return true;
        }
        else if (s_acc + s_dec >= s_total) // 先加速，再减速，无匀速阶段
        {
            threadLogger_->info("先加速，再减速，无匀速阶段");
            float s_as  = (2 * min_acceleration * s_total - pow(v2, 2) + pow(v0, 2)) / (2 * (min_acceleration - max_acceleration)); // 加速的距离
            float v_max = sqrt((2 * min_acceleration * max_acceleration * s_total + min_acceleration * pow(v0, 2) - max_acceleration * pow(v2, 2)) / (min_acceleration - max_acceleration));
            float s_temp;
            float s_0 = temp_traj.at(keypoint1.index).distance;
            for (unsigned int i = keypoint1.index; i < keypoint2.index; i += speed_discrete_number) {
                s_temp = fabs(temp_traj.at(i).distance - s_0); // 距起点的距离
                if (s_temp < s_as)                             // 加速
                {
                    temp_sparsepoint.index = i;
                    temp_sparsepoint.speed = sqrt(pow(v0, 2) + 2 * max_acceleration * s_temp);
                    temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
                }
                else // 减速
                {
                    float s_d              = s_temp - s_as; // 减速距离
                    temp_sparsepoint.index = i;
                    temp_sparsepoint.speed = sqrt(pow(v_max, 2) + 2 * min_acceleration * s_d);
                    temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
                }
            }
            last_speed = v2;
            return true;
        }
    }

    /* 情况5: v0 < v1 && v2 < v1 && v2 > v0:
    需要加速，再减速 */
    if (v0 < v1 && v2 < v1 && v2 > v0) {
        threadLogger_->info("...Case 5...");

        float s_total = temp_traj.at(keypoint2.index).distance - temp_traj.at(keypoint1.index).distance; // 该路段的路径长度
        float s_min   = (pow(v2, 2) - pow(v0, 2)) / (2 * max_acceleration);                              // 加速到v2所需的最小距离
        float s_acc   = (pow(v1, 2) - pow(v0, 2)) / (2 * max_acceleration);
        float s_dec   = (pow(v2, 2) - pow(v1, 2)) / (2 * min_acceleration);
        if (s_acc + s_dec < s_total) // 先加速到最大速度，再减速到v2
        {
            float s_temp;
            float s_0 = temp_traj.at(keypoint1.index).distance;
            for (unsigned int i = keypoint1.index; i < keypoint2.index; i += speed_discrete_number) {
                s_temp = fabs(temp_traj.at(i).distance - s_0); // 距起点的距离
                if (s_temp < s_acc)                            // 加速
                {
                    temp_sparsepoint.index = i;
                    temp_sparsepoint.speed = sqrt(pow(v0, 2) + 2 * max_acceleration * s_temp);
                    temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
                }
                else if (s_temp < s_total - s_dec) // 匀速
                {
                    temp_sparsepoint.index = i;
                    temp_sparsepoint.speed = v1;
                    temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
                }
                else // 减速
                {
                    float s_d              = s_temp - (s_total - s_dec); // 减速距离
                    temp_sparsepoint.index = i;
                    temp_sparsepoint.speed = sqrt(pow(v1, 2) + 2 * min_acceleration * s_d);
                    temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
                }
            }
            last_speed = v2;
            return true;
        }
        else if (s_acc + s_dec >= s_total && s_total > s_min) // 先加速，再减速，无匀速阶段
        {
            float s_as  = (2 * min_acceleration * s_total - pow(v2, 2) + pow(v0, 2)) / (2 * (min_acceleration - max_acceleration)); // 加速的距离
            float v_max = sqrt((2 * min_acceleration * max_acceleration * s_total + min_acceleration * pow(v0, 2) - max_acceleration * pow(v2, 2)) / (min_acceleration - max_acceleration));
            float s_temp;
            float s_0 = temp_traj.at(keypoint1.index).distance;
            for (unsigned int i = keypoint1.index; i < keypoint2.index; i += speed_discrete_number) {
                s_temp = fabs(temp_traj.at(i).distance - s_0); // 距起点的距离
                if (s_temp < s_as)                             // 加速
                {
                    temp_sparsepoint.index = i;
                    temp_sparsepoint.speed = sqrt(pow(v0, 2) + 2 * max_acceleration * s_temp);
                    temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
                }
                else // 减速
                {
                    float s_d              = s_temp - s_as; // 减速距离
                    temp_sparsepoint.index = i;
                    temp_sparsepoint.speed = sqrt(pow(v_max, 2) + 2 * min_acceleration * s_d);
                    temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
                }
            }
            last_speed = v2;
            return true;
        }
        else if (s_total <= s_min) // 一直加速
        {
            float s_temp;
            float s_0 = temp_traj.at(keypoint1.index).distance;
            for (unsigned int i = keypoint1.index; i < keypoint2.index; i += speed_discrete_number) {
                s_temp                 = fabs(temp_traj.at(i).distance - s_0); // 距起点的距离
                temp_sparsepoint.index = i;
                temp_sparsepoint.speed = sqrt(pow(v0, 2) + 2 * max_acceleration * s_temp);
                temp_sparsespeedpoints.emplace_back(temp_sparsepoint);
            }
            last_speed = sqrt(pow(v0, 2) + 2 * max_acceleration * s_total);
            return true;
        }
    }
}


void GlobalSpeedPlanning::ReplanPointMaxSpeed() {
    double regular_road_speed_limit      = 1;   // 常规路面限速
    double narrow_road_speed_limit       = 1;   // 会车道路限速
    double intersection_road_speed_limit = 1;   // 路口限速
    double slope_road_speed_limit        = 1;   // 坡路限速
    double bumpy_road_speed_limit        = 1;   // 颠簸路段限速
    double reverse_speed                 = 1;   // 倒车限速
    double a                             = 0.8; // a表示一级限速到二级限速之间的缩放比例
    double b                             = 0.6; // b表示一级限速到三级限速之间的缩放比例
    double c                             = 0.7; // c表示轻载到重载之间的缩放比例

    if (vehicle_param.weather == true && vehicle_param.is_day == true) { // 晴天+白天【一级限速】
        threadLogger_->info("晴天+白天【一级限速】");
        regular_road_speed_limit      = vehicle_param.regular_road_speed_limit;
        narrow_road_speed_limit       = vehicle_param.narrow_road_speed_limit;
        intersection_road_speed_limit = vehicle_param.intersection_road_speed_limit;
        slope_road_speed_limit        = vehicle_param.slope_road_speed_limit;
        bumpy_road_speed_limit        = vehicle_param.bumpy_road_speed_limit;
    }
    else if ((vehicle_param.weather == true && vehicle_param.is_day == false) || (vehicle_param.weather == false && vehicle_param.is_day == true)) { // 晴天+晚上      雨天+白天 【二级限速】
        threadLogger_->info("晴天+晚上      雨天+白天 【二级限速】");
        regular_road_speed_limit      = a * vehicle_param.regular_road_speed_limit;
        narrow_road_speed_limit       = a * vehicle_param.narrow_road_speed_limit;
        intersection_road_speed_limit = a * vehicle_param.intersection_road_speed_limit;
        slope_road_speed_limit        = a * vehicle_param.slope_road_speed_limit;
        bumpy_road_speed_limit        = a * vehicle_param.bumpy_road_speed_limit;
    }
    else { // 雨天+晚上 【三级限速】
        threadLogger_->info("雨天+晚上 【三级限速】");
        regular_road_speed_limit      = b * vehicle_param.regular_road_speed_limit;
        narrow_road_speed_limit       = b * vehicle_param.narrow_road_speed_limit;
        intersection_road_speed_limit = b * vehicle_param.intersection_road_speed_limit;
        slope_road_speed_limit        = b * vehicle_param.slope_road_speed_limit;
        bumpy_road_speed_limit        = b * vehicle_param.bumpy_road_speed_limit;
    }

    if (vehicle_param.is_light == 0) {
        threadLogger_->info("重载");
        regular_road_speed_limit      = c * regular_road_speed_limit;
        narrow_road_speed_limit       = c * narrow_road_speed_limit;
        intersection_road_speed_limit = c * intersection_road_speed_limit;
        slope_road_speed_limit        = c * slope_road_speed_limit;
        bumpy_road_speed_limit        = c * bumpy_road_speed_limit;
    }
    reverse_speed = vehicle_param.reverse_speed;

    // 先通过direction属性，将前进后退轨迹进行区分(direction 0:前进 1:后退),后退轨迹限速均为1m/s
    vector<_TrajectoryPoint>::iterator iter = trajectory_points.begin();
    for (; iter != trajectory_points.end(); iter++) {
        if (iter->direction == 0) {
            if (iter->attribute == PointAttribute::regular_road) // 正常路
            {
                iter->speed_limit = regular_road_speed_limit;
            }
            else if (iter->attribute == PointAttribute::narrow_road) // 会车路
            {
                iter->speed_limit = narrow_road_speed_limit;
            }
            else if (iter->attribute == PointAttribute::intersection_road) // 路口
            {
                iter->speed_limit = intersection_road_speed_limit;
            }
            else if (iter->attribute == PointAttribute::slope_road) // 坡路
            {
                iter->speed_limit = slope_road_speed_limit;
            }
            else if (iter->attribute == PointAttribute::dump_road) // 颠簸路
            {
                iter->speed_limit = bumpy_road_speed_limit;
            }
            else // 未定义的路面属性
            {
                iter->speed_limit = 1;
            }
        }
        else {
            // 此时，该点为后退路径上的点,后退轨迹限速均为2m/s
            iter->speed_limit = vehicle_param.reverse_speed;
        }
    }

    // 遍历整个trajectory_points，检核每个点的限速是否合理；根据方向盘最大转速以及每个点的瞬时曲率来确定每个点的合理限速
    float         L_vehicle                = vehicle_param.wheel_base;
    float         max_Steering_wheel_speed = 0.175;
    float         temp_max_speed;
    float         wheel_delta_angle, wheel_angle1, wheel_angle2;
    float         sampling_distance = 1;
    vector<float> vec_temp_max_speed; // 记录全局路径上基于曲率变化算出限速信息

    for (int i = 0; i < trajectory_points.size() - 1; i++) //
    {
        wheel_angle1   = atan(L_vehicle * trajectory_points.at(i).curvature);
        wheel_angle2   = atan(L_vehicle * trajectory_points.at(i + 1).curvature);
        temp_max_speed = sampling_distance * max_Steering_wheel_speed / (fabs(wheel_angle1 - wheel_angle2) + eps); // 根据控制给的方向盘最高转速和预定的采样距离算出的每个点的最大限速
        if (temp_max_speed >= 10) temp_max_speed = 10;
        vec_temp_max_speed.push_back(temp_max_speed);
    }

    for (int i = 0; i < vec_temp_max_speed.size(); i++) {
        if (vec_temp_max_speed.at(i) < trajectory_points.at(i).speed_limit) {
            if (trajectory_points.at(i).direction == 0) {
                trajectory_points.at(i).speed_limit = vec_temp_max_speed.at(i);
                // 为了便于控制跟踪，将i附近的10(10m) 路径点限速也降低i为vec_temp_max_speed.at(i)
                for (int j = i - 5; j < i + 5; j++) {
                    if (j >= 0 && j < vec_temp_max_speed.size()) {
                        if (trajectory_points.at(j).direction == 0) {
                            if (trajectory_points.at(j).speed_limit > vec_temp_max_speed.at(i)) {
                                trajectory_points.at(j).speed_limit = vec_temp_max_speed.at(i);
                            }
                        }
                    }
                }
            }
        }
    }

    // std::ofstream file_out;
    // file_out.open("speed_limit0.txt");
    // for (size_t index = 0; index < trajectory_points.size(); index++) {
    //     file_out << 0 << " " << trajectory_points.at(index).speed_limit << endl;
    // }
    // file_out.close();
    // 曲率限速
    iter = trajectory_points.begin();
    for (; iter != trajectory_points.end(); iter++) {
        if (iter->speed_limit > sqrt(0.2 / fabs(iter->curvature))) {
            iter->speed_limit = sqrt(0.2 / fabs(iter->curvature));
        }
    }

    // file_out.open("speed_limit1.txt");
    // for (size_t index = 0; index < trajectory_points.size(); index++) {
    //     file_out << 0 << " " << trajectory_points.at(index).speed_limit << endl;
    // }
    // file_out.close();
}
/**
 * @brief: 路径划分，将全局路径按照前进、后退切换的点划分为不同的片段，分别进行速度规划
 * @return 无
 */
bool GlobalSpeedPlanning::SplitPath() {
    unsigned int start_id, end_id;
    start_id = 0;
    end_id   = 0;
    vector<_TrajectoryPoint> temp_traj;
    for (unsigned int i = 0; i < trajectory_points.size() - 1; i++) {
        if (trajectory_points.at(i).direction != trajectory_points.at(i + 1).direction || trajectory_points.at(i).attribute == PointAttribute::weight_point || trajectory_points.at(i).attribute == PointAttribute::clean_point) {
            temp_traj.clear();
            end_id = i;
            temp_traj.insert(temp_traj.begin(), trajectory_points.begin() + start_id, trajectory_points.begin() + end_id + 1);
            start_id = end_id;
            trajectory_fragments.emplace_back(temp_traj);
        }

        if (i == trajectory_points.size() - 2) //  最后一段
        {
            temp_traj.clear();
            temp_traj.insert(temp_traj.begin(), trajectory_points.begin() + start_id, trajectory_points.end());
            trajectory_fragments.emplace_back(temp_traj);
        }
    }

    threadLogger_->info("trajectory_fragments.size():{}", trajectory_fragments.size());

    if (trajectory_fragments.at(0).size() <= 2) {
        trajectory_fragments.erase(trajectory_fragments.begin());
    }
    threadLogger_->info("SplitPath 成功");
    return true;
}

/**
 *@brief: 获取关键点函数
 */
bool GlobalSpeedPlanning::GetKeypoint() {
    KeyPoint                 temp_keypoint;
    vector<KeyPoint>         temp_keypoints;
    vector<_TrajectoryPoint> temp_traj;
    if (trajectory_fragments.size()) {
        for (unsigned int i = 0; i < trajectory_fragments.size(); i++) {
            temp_traj.clear();
            temp_traj = trajectory_fragments.at(i);
            // 如果是倒车，暂时按照最简单的加速、匀速、加速的模式进行速度规划，全段最大速度提前设定为
            if (1 == temp_traj.at(1).direction) { // 判断第一个点的原因在于分段时会存在重合点
                temp_keypoints.clear();
                temp_keypoint.Set(0, temp_traj.at(0).distance, 1, 0, reverse_speed); // 给关键点赋值
                temp_keypoints.emplace_back(temp_keypoint);                          // 倒车模式下的关键点只有两个
                temp_keypoint.Set(temp_traj.size() - 1, temp_traj.back().distance, 1, reverse_speed, 0.0);
                temp_keypoints.emplace_back(temp_keypoint); // 倒车模式下的关键点只有两个
                key_points.emplace_back(temp_keypoints);
            }
            else if (0 == temp_traj.at(1).direction) // 如果是前行，可能有多个不同的限速，关键点数量大于等于两个
            {
                temp_keypoints.clear();
                temp_keypoint.Set(0, temp_traj.at(0).distance, 0, 0, temp_traj.at(1).speed_limit); // 给关键点赋值
                temp_keypoints.emplace_back(temp_keypoint);
                for (unsigned int j = 1; j < temp_traj.size() - 1; j++) {
                    if (temp_traj.at(j).speed_limit != temp_traj.at(j + 1).speed_limit) // 最大速度改变处设置一个关键点
                    {
                        temp_keypoint.Set(j, temp_traj.at(j).distance, 0, temp_traj.at(j).speed_limit,
                                          temp_traj.at(j + 1).speed_limit); // 给关键点赋值
                        temp_keypoints.emplace_back(temp_keypoint);
                    }
                    if (temp_traj.size() - 2 == j) // 最后一个路径点也作为关键点
                    {
                        temp_keypoint.Set(j + 1, temp_traj.at(j + 1).distance, 0, temp_traj.at(j + 1).speed_limit,
                                          0.0); // 给关键点赋值

                        temp_keypoints.emplace_back(temp_keypoint);
                    }
                }
                key_points.emplace_back(temp_keypoints);
            }
        }
    }
    else {
        threadLogger_->info("...The trajectory_fragments.size is 0... ");

        return false;
    }
    threadLogger_->info("本次任务的全局路径一共{}段", key_points.size());

    for (int i = 0; i < key_points.size(); i++) {
        threadLogger_->info("第{}段有{}关键点", (float)(i + 1), key_points.at(i).size());

        for (int j = 0; j < key_points.at(i).size(); j++) {
            threadLogger_->info("第{}段的第{}个关键点的索引{},左限速{},右限速{}", (float)(i + 1), j + 1, key_points.at(i).at(j).index, key_points.at(i).at(j).speed_limit_left, key_points.at(i).at(j).speed_limit_right);
        }
    }

    return true;
}

/**
 * @brief: 速度曲线平滑函数
 * @param  num：trajectory_fragments中的第num条
 */
void GlobalSpeedPlanning::SpeedCurveSmooth(unsigned char num) {
    std::vector<SparseSpeedPoint> temp_opti_global_speed = global_speeds.at(num);

    for (int i = 0; i < temp_opti_global_speed.size(); i++) {
        threadLogger_->info("temp_opti_global_speed.at{}.speed:{}  index:{}", i, temp_opti_global_speed.at(i).speed, temp_opti_global_speed.at(i).index);
    }
    //   threadLogger_->info("~~~~~temp_opti_global_speed.back().index = " << temp_opti_global_speed.back().index <<
    //   "\n"; threadLogger_->info("~~~~~temp_opti_global_speed.back().speed = " << temp_opti_global_speed.back().speed
    //   << "\n";
    unsigned int iterations = 0;
    // 最大遍历次数为30次
    while (iterations++ < 100) {
        // 遍历稀疏速度曲线，分别计算出目标函数中每一项的梯度值，采用梯度下降法对速度曲线优化。
        for (unsigned int i = 1; i < global_speeds.at(num).size() - 1; i++) {
            float v0 = temp_opti_global_speed.at(i - 1).speed;
            float v1 = temp_opti_global_speed.at(i).speed;
            float v2 = temp_opti_global_speed.at(i + 1).speed;
            float vo = global_speeds.at(num).at(i).speed;

            float gradient_error  = speed_error_term * (vo - v1);
            float gradient_smooth = speed_smooth_term * (v0 + v2 - 2 * v1);


            temp_opti_global_speed.at(i).speed += gradient_error + gradient_smooth;
            // threadLogger_->info("优化过程中实时速度：{}", temp_opti_global_speed.at(i).speed);
        }
    }
    opti_global_speeds.emplace_back(temp_opti_global_speed);
    //   threadLogger_->info("opti_global_speeds.back().back().speed = " << opti_global_speeds.back().back().speed <<
    //   "\n";
    threadLogger_->info("...SpeedCurveSmooth() finish...");
}


/**
 * @brief: 速度曲线插值函数
 * @param  num：trajectory_fragments中的第num条
 */
void GlobalSpeedPlanning::SpeedCurveInterpolation(unsigned char num) {
    vector<SparseSpeedPoint> temp_opti_global_speed = opti_global_speeds.at(num);
    vector<_TrajectoryPoint> temp_traj              = trajectory_fragments.at(num);

    // 遍历稀疏速度曲线
    for (unsigned int i = 1; i < temp_opti_global_speed.size(); i++) {
        // 计算出相邻两个插值点之间的距离。
        float total_s = temp_traj.at(temp_opti_global_speed.at(i).index).distance - temp_traj.at(temp_opti_global_speed.at(i - 1).index).distance;
        // 计算当前两稀疏速度值之间的加速度
        float a       = (pow(temp_opti_global_speed.at(i).speed, 2) - pow(temp_opti_global_speed.at(i - 1).speed, 2)) / (2 * total_s);
        float delta_s = 0;
        // 计算需要插值的路点数，采用匀加速模型进行速度插值，计算得到每个插值点的速度。
        for (int j = temp_opti_global_speed.at(i - 1).index; j < temp_opti_global_speed.at(i).index; j++) {
            float temp_speed = sqrt(pow(temp_opti_global_speed.at(i - 1).speed, 2) + 2 * a * delta_s);

            // cout << "j - temp_opti_global_speed.at(0).index:" << j - temp_opti_global_speed.at(0).index << "           temp_speed:" << temp_speed << endl;
            temp_traj.at(j - temp_opti_global_speed.at(0).index).speed = temp_speed;

            delta_s += temp_traj.at(j + 1).distance - temp_traj.at(j).distance;

        } // 该循环内只将到该段路径终点前的所有点的速度进行了赋值，未对终点速度进行重新赋值
    }
    temp_traj.back().speed = 0.0;
    //   threadLogger_->info("##temp_traj.back().speed = "<< temp_traj.back().speed << "\n";
    trajectory_fragments.at(num) = temp_traj; // 赋速度值以后的路径
    threadLogger_->info("...The SpeedCurveInterpolation() finish...");
}

/**
 *@brief: 获取时间信息函数，得到每个路点的时间信息
 *@param  start_time 开始发车时间
 *return
 */

void GlobalSpeedPlanning::AddTimeInformation(const int& start_time_) {
    double t = 0.0 + start_time_;
    // 遍历插值后的速度曲线
    for (unsigned int i = 0; i < trajectory_fragments.size(); i++) {
        trajectory_fragments.at(i).at(0).t = t;
        for (unsigned int j = 1; j < trajectory_fragments.at(i).size(); j++) {
            // 计算出相邻两个插值点之间的距离。
            float delta_s = trajectory_fragments.at(i).at(j).distance - trajectory_fragments.at(i).at(j - 1).distance;
            // 累加相邻两个插值点之间的时间。
            float ave_speed = (trajectory_fragments.at(i).at(j - 1).speed + trajectory_fragments.at(i).at(j).speed) / 2;
            ave_speed       = ave_speed > 0 ? ave_speed : 0.01;
            t += delta_s / ave_speed;
            trajectory_fragments.at(i).at(j).t = t;
        }
    }
}
