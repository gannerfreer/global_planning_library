/***************************************************/
/*            Author: Yang Fan                     */
/*            Contact: allenyangfan@163.com        */
/*            Last update: 2020-04-22              */
/***************************************************/
/*
  Description: The .cpp file for C++ class r_s_curve.
*/

#include "r_s_curve.h"

namespace GlobalPlanning {
// 构造函数
RSCurve::RSCurve() {
    vector<ReedsSheppPathSegmentType> temp_vector;
    for (int i = 0; i < 18; i++) {
        vector<ReedsSheppPathSegmentType>().swap(temp_vector);
        for (int j = 0; j < 5; j++) {
            temp_vector.push_back(reedsSheppPathType[i][j]);
        }
        reeds_shepp_path_type_v.push_back(temp_vector);
    }
}
// 析构函数
RSCurve::~RSCurve() {}
void RSCurve::Init(_VehicleParam& vehicleparam) {
    m_vehicle_prarm_ = vehicleparam;
}

/**
 * @brief RS曲线规划类接口函数
 */
bool RSCurve::PlanRSPath(const Point start, const Point end, Path& rs_path, PlanRule plan_rule) {
    //     cout << "6666m_vehicle_prarm_.radious = " << m_vehicle_prarm_.radious << "\n";
    threadLogger_->info("start:{},{},{}  end:{},{},{}", start.x, start.y, start.angle, end.x, end.y, end.angle);
    rs_plan_rule = plan_rule;
    if (rs_plan_rule == PlanRule::Forward_All_Time) {
        rs_plan_rule = PlanRule::Forward_To_End;
    }
    // opti_rs_path.length = DBL_MAX;
    opti_rs_path.set(reeds_shepp_path_type_v.at(0), 0, 0, 0, 0, 0, DBL_MAX);
    a_star_direction = start.direction;
    Path().swap(rs_path);
    CoordinateTransformation(start, end, m_vehicle_prarm_.radious); // 坐标转换及归一化
    if (ReedsSheppGeneration()) {
        if (opti_rs_path.type.empty()) return false;
        Interpolate(start, rs_path); // 插值、还原得到最终RS路径
        if (a_star_direction != rs_path.at(0).direction) return false;
        return true;
    }
    else {
        return false;
    }
}

bool RSCurve::PlanRSPath_another(const Point start, const Point end, Path& rs_path, PlanRule plan_rule) {
    //     cout << "6666m_vehicle_prarm_.radious = " << m_vehicle_prarm_.radious << "\n";
    rs_plan_rule = plan_rule;
    if (rs_plan_rule == PlanRule::Forward_All_Time) {
        rs_plan_rule = PlanRule::Forward_To_End;
    }
    // opti_rs_path.length = DBL_MAX;
    opti_rs_path.set(reeds_shepp_path_type_v.at(0), 0, 0, 0, 0, 0, DBL_MAX);
    a_star_direction = start.direction;
    Path().swap(rs_path);
    CoordinateTransformation(start, end, m_vehicle_prarm_.radious); // 坐标转换及归一化
    if (ReedsSheppGeneration()) {
        if (opti_rs_path.type.empty()) {
            return false;
        }
        Interpolate(start, rs_path); // 插值、还原得到最终RS路径

        return true;
    }
    else
        return false;
}

/**
 * @brief 坐标系转换和归一化函数
 */
void RSCurve::CoordinateTransformation(Point start, Point end, double kRadious) {
    double dx = end.x - start.x, dy = end.y - start.y, dz = end.z - start.z, dangle = end.angle - start.angle;
    double c = cos(start.angle), s = sin(start.angle);
    double x = c * dx + s * dy, y = -s * dx + c * dy;
    new_end.x     = x / kRadious;
    new_end.y     = y / kRadious;
    new_end.z     = dz;
    new_end.angle = dangle;
}

/**
 * @brief 判断生成的最优RS路径各段是否满足最小长度要求
 */
bool RSCurve::LengthValid() {
    if (fabs(opti_rs_path.t) > 0 && fabs(opti_rs_path.u) > 0 && fabs(opti_rs_path.v) > 0) {
        vector<double> s;
        s.push_back(opti_rs_path.t);
        s.push_back(opti_rs_path.u);
        s.push_back(opti_rs_path.v);
        if (fabs(opti_rs_path.w) > 1e-6) s.push_back(opti_rs_path.w);
        if (fabs(opti_rs_path.x) > 1e-6) s.push_back(opti_rs_path.x);

        double sum = 0;
        for (unsigned int i = 0; i < s.size() - 1; i++) {
            sum += fabs(s.at(i)) * m_vehicle_prarm_.radious;
            if (s.at(i) * s.at(i + 1) > 0)
                continue;
            else {
                if (i == 0) {
                    int temp_direction_rs    = (s.at(0) < 0) ? -1 : 1;
                    int temp_direction_astar = (a_star_direction != Forward) ? -1 : 1;
                    if (1 == temp_direction_astar * temp_direction_rs)
                        continue;
                    else
                        ;
                }
                else if (i == s.size() - 2) {
                    if (fabs(s.at(s.size() - 1)) * m_vehicle_prarm_.radious < m_vehicle_prarm_.min_path_Length) {
                        threadLogger_->info("fabs(s.at(s.size() - 1)) * m_vehicle_prarm_.radious < m_vehicle_prarm_.min_path_Length");
                        return false;
                    }
                }
                else
                    ;
                if (sum < m_vehicle_prarm_.min_path_Length) {
                    threadLogger_->info("sum < m_vehicle_prarm_.min_path_Length");
                    return false;
                }
                else
                    ;
            }
            sum = 0;
        }
        return true;
    }
    else {}
    return false;
}

/**
 * @brief 生成最优Reeds-Shepp路段
 */
bool RSCurve::ReedsSheppGeneration() {
    CSC();
    if (!LengthValid()) // true:存在路段长度小于最短长度限制,清空 opti_rs_path
    {
        threadLogger_->info("CSC fail");
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), 0, 0, 0, 0, 0, 0);
    }
    else
        ;
    CCC();
    if (!LengthValid()) {
        threadLogger_->info("CCC fail");
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), 0, 0, 0, 0, 0, 0);
    }
    else
        ;
    CCCC();
    if (!LengthValid()) {
        threadLogger_->info("CCCC fail");
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), 0, 0, 0, 0, 0, 0);
    }
    else
        ;
    CCSC();
    if (!LengthValid()) {
        threadLogger_->info("CCSC fail");
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), 0, 0, 0, 0, 0, 0);
    }
    else
        ;
    CCSCC();
    if (!LengthValid()) {
        threadLogger_->info("CCSCC fail");
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), 0, 0, 0, 0, 0, 0);
    }
    else
        ;
    // return true;
    if (fabs(opti_rs_path.t) > 1e-6 && fabs(opti_rs_path.u) > 1e-6 && fabs(opti_rs_path.v) > 1e-6)
        return true; // RS路径前三段存在则认为生成最优RS路径成功
    else {
        if (fabs(opti_rs_path.t) <= 1e-6) {
            threadLogger_->info("t<=0");
        }
        if (fabs(opti_rs_path.u) <= 1e-6) {
            threadLogger_->info("u<=0");
        }
        if (fabs(opti_rs_path.v) <= 1e-6) {
            threadLogger_->info("v<=0");
        }
        return false;
    }
}

/**
 * @brief 对生成的最优RS路段进行插值
 */
void RSCurve::Interpolate(Point start, Path& rs_path) {
    //       cout<< "77777m_vehicle_prarm_.step_length =" << m_vehicle_prarm_.step_length << "\n";
    Point temp_point;
    temp_point.x     = 0;
    temp_point.y     = 0;
    temp_point.z     = 0;
    temp_point.angle = Mod2pi(start.angle);
    RSPoint_Vertex rspoint_vertex;
    rspoint_vertex.types  = opti_rs_path.type.at(0);
    rspoint_vertex.length = opti_rs_path.t;
    rspoint_vertex.x      = 0;
    rspoint_vertex.y      = 0;
    rspoint_vertex.theta  = Mod2pi(start.angle);
    RSPoint rspoint;
    rspoint.push_back(rspoint_vertex);
    MotionDirection directions;
    for (int i = 0; i < 4; i++) {
        if (opti_rs_path.type.at(i + 1) == RS_NOP) {
            break;
        }
        else {
            if (i == 0) {
                CalNextPoint(opti_rs_path.t, temp_point.x, temp_point.y, temp_point.angle, opti_rs_path.type.at(i), temp_point, directions);
                rspoint_vertex.length = opti_rs_path.u;
            }
            else if (i == 1) {
                CalNextPoint(opti_rs_path.u, rspoint.at(rspoint.size() - 1).x, rspoint.at(rspoint.size() - 1).y, rspoint.at(rspoint.size() - 1).theta, opti_rs_path.type.at(i), temp_point, directions);
                rspoint_vertex.length = opti_rs_path.v;
            }
            else if (i == 2) {
                CalNextPoint(opti_rs_path.v, rspoint.at(rspoint.size() - 1).x, rspoint.at(rspoint.size() - 1).y, rspoint.at(rspoint.size() - 1).theta, opti_rs_path.type.at(i), temp_point, directions);
                rspoint_vertex.length = opti_rs_path.w;
            }
            else if (i == 3) {
                CalNextPoint(opti_rs_path.w, rspoint.at(rspoint.size() - 1).x, rspoint.at(rspoint.size() - 1).y, rspoint.at(rspoint.size() - 1).theta, opti_rs_path.type.at(i), temp_point, directions);
                rspoint_vertex.length = opti_rs_path.x;
            }
            rspoint_vertex.types = opti_rs_path.type.at(i + 1);
            rspoint_vertex.x     = temp_point.x;
            rspoint_vertex.y     = temp_point.y;
            rspoint_vertex.theta = temp_point.angle;
            rspoint.push_back(rspoint_vertex);
        };
    }
    double total_length = opti_rs_path.length;
    double step_size    = m_vehicle_prarm_.step_length / m_vehicle_prarm_.radious;
    Point  np;
    for (int i = 0; i < rspoint.size(); i++) {
        double s = 0;
        while (s < fabs(rspoint.at(i).length)) {
            double sign_s = (rspoint.at(i).length > 0) ? s : (-s);
            CalNextPoint(sign_s, rspoint.at(i).x, rspoint.at(i).y, rspoint.at(i).theta, rspoint.at(i).types, np, directions);
            np.x     = np.x * m_vehicle_prarm_.radious + start.x;
            np.y     = np.y * m_vehicle_prarm_.radious + start.y;
            np.angle = Mod2pi(np.angle);
            if (0.0 == s) {
                directions = (rspoint.at(i).length > 0) ? Forward : Backward;
            }
            np.direction = directions;
            rs_path.push_back(np);
            s += step_size;
        }
    }
    CalNextPoint(rspoint.at(rspoint.size() - 1).length, rspoint.at(rspoint.size() - 1).x, rspoint.at(rspoint.size() - 1).y, rspoint.at(rspoint.size() - 1).theta, rspoint.at(rspoint.size() - 1).types, np, directions);
    np.x         = np.x * m_vehicle_prarm_.radious + start.x;
    np.y         = np.y * m_vehicle_prarm_.radious + start.y;
    np.angle     = Mod2pi(np.angle);
    np.direction = directions;
    rs_path.push_back(np);

    if (sqrt(pow(rs_path.at(rs_path.size() - 1).x - rs_path.at(rs_path.size() - 2).x, 2) + pow(rs_path.at(rs_path.size() - 1).x - rs_path.at(rs_path.size() - 2).x, 2)) < 0.6) {
        auto iter1 = rs_path.erase(rs_path.end() - 2);
    }
}

/**
 * @brief 计算辅助函数
 */
inline double RSCurve::Mod2pi(double x) {
    double v = fmod(x, 2. * M_PI);
    if (v < -M_PI)
        v += 2. * M_PI;
    else if (v > M_PI)
        v -= 2. * M_PI;
    return v;
}

inline void RSCurve::Polar(double x, double y, double& r, double& theta) {
    r     = sqrt(x * x + y * y);
    theta = atan2(y, x);
}

inline bool RSCurve::Valid(double theta) {
    if (theta >= 0 && theta <= M_PI)
        return true;
    else
        return false;
}

/**
 * @brief 根据当前点计算下一点
 */
void RSCurve::CalNextPoint(double s, double x, double y, double th, ReedsSheppPathSegmentType type_, Point& point, MotionDirection& directions) {
    if (s > 0)
        directions = Forward;
    else
        directions = Backward;
    switch (type_) {
        case RS_LEFT:
            point.x     = x + sin(th + s) - sin(th);
            point.y     = y - cos(th + s) + cos(th);
            point.z     = 0;
            point.angle = th + s;
            break;

        case RS_STRAIGHT:
            point.x     = x + s * cos(th);
            point.y     = y + s * sin(th);
            point.z     = 0;
            point.angle = th;
            break;

        case RS_RIGHT:
            point.x     = x - sin(th - s) + sin(th);
            point.y     = y + cos(th - s) - cos(th);
            point.z     = 0;
            point.angle = th - s;
            break;

        case RS_NOP:
            break;
    }
}

/**
 * @brief CSC类RS路径计算
 */
// formula 8.1
inline bool RSCurve::LpSpLp(double x, double y, double phi, double& t, double& u, double& v) {
    threadLogger_->info("enter LpSpLp");
    Polar(x - sin(phi), y - 1. + cos(phi), u, t);
    v = Mod2pi(phi - t);
    if (Valid(v) && Valid(t)) {
        threadLogger_->info("LpSpLp success");
        return true;
    }
    else {
        threadLogger_->info("LpSpLp fail");
    }
    t = 0;
    u = 0;
    v = 0;
    return false;
}
// formula 8.2
inline bool RSCurve::LpSpRp(double x, double y, double phi, double& t, double& u, double& v) {
    threadLogger_->info("enter LpSpRp");
    double t1, u1, theta;
    Polar(x + sin(phi), y - 1. - cos(phi), u1, t1);
    u1 = u1 * u1;
    if (u1 >= 4.) {
        u     = sqrt(u1 - 4.);
        theta = atan2(2., u);
        t     = Mod2pi(t1 + theta);
        v     = Mod2pi(t - phi);
        if (Valid(t) && Valid(v)) {
            threadLogger_->info("LpSpRp success");
            return true;
        }
        else {
            threadLogger_->info("LpSpRp fail");
        }
    }
    else {
        threadLogger_->info("LpSpRp fail");
    }

    t = 0;
    u = 0;
    v = 0;
    return false;
}
void RSCurve::CSC() {
    double t, u, v, Lmin = DBL_MAX, L;
    double x = new_end.x, y = new_end.y, phi = new_end.angle;
    if (PlanRule::Backward_All_Time != rs_plan_rule && LpSpLp(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(14), t, u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Forward_To_End != rs_plan_rule && LpSpLp(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(14), -t, -u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Backward_All_Time != rs_plan_rule && LpSpLp(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(15), t, u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Forward_To_End != rs_plan_rule && LpSpLp(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(15), -t, -u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Backward_All_Time != rs_plan_rule && LpSpRp(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(12), t, u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Forward_To_End != rs_plan_rule && LpSpRp(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(12), -t, -u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Backward_All_Time != rs_plan_rule && LpSpRp(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(13), t, u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Forward_To_End != rs_plan_rule && LpSpRp(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(13), -t, -u, -v, 0, 0, L);
    }
    else
        ;
}

/**
 * @brief CCC类RS路径计算
 */
// formula 8.3 *** C|C|C ***
inline bool RSCurve::LpRnLp(double x, double y, double phi, double& t, double& u, double& v) {
    double xi = x - sin(phi), eta = y - 1. + cos(phi), u1, theta, alpha;
    Polar(xi, eta, u1, theta);
    if (u1 <= 4.) {
        alpha = acos(u1 / 4);
        t     = Mod2pi(0.5 * M_PI + theta + alpha);
        u     = Mod2pi(M_PI - 2 * alpha);
        v     = Mod2pi(phi - t - u);
        if (Valid(t) && Valid(v) && Valid(u)) {
            return true;
        }
    }
    else
        ;
    t = 0;
    u = 0;
    v = 0;
    return false;
}
// formula 8.4  *** C|CC ***
inline bool RSCurve::LpRnLn(double x, double y, double phi, double& t, double& u, double& v) {
    double xi = x - sin(phi), eta = y - 1. + cos(phi), u1, theta;
    Polar(xi, eta, u1, theta);
    if (u1 <= 4.) {
        double alpha = acos(u1 / 4);
        t            = Mod2pi(0.5 * M_PI + theta + alpha);
        u            = Mod2pi(M_PI - 2 * alpha);
        v            = Mod2pi(-phi + t + u);
        if (Valid(t) && Valid(v) && Valid(u))
            return true;
        else
            ;
    }
    else
        ;
    t = 0;
    u = 0;
    v = 0;
    return false;
}
// formula 8.4  *** CC|C ***
inline bool RSCurve::LpRpLn(double x, double y, double phi, double& t, double& u, double& v) {
    double xi = x - sin(phi), eta = y - 1. + cos(phi), u1, theta;
    Polar(xi, eta, u1, theta);
    if (u1 <= 4.) {
        u            = acos((8 - u1 * u1) / 8);
        double va    = sin(u);
        double alpha = asin(2 * va / u1);
        t            = Mod2pi(0.5 * M_PI + theta - alpha);
        v            = Mod2pi(-phi + t - u);
        if (Valid(t) && Valid(v) && Valid(u)) return true;
    }
    else
        ;
    t = 0;
    u = 0;
    v = 0;
    return false;
}
void RSCurve::CCC() {
    double t, u, v, Lmin = opti_rs_path.length, L;
    if (Lmin < 1e-6)
        Lmin = DBL_MAX;
    else
        ;
    double x = new_end.x, y = new_end.y, phi = new_end.angle;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRnLp(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), t, -u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRnLp(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), -t, u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRnLp(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(1), t, -u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRnLp(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(1), -t, u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;

    if (PlanRule::Forward_To_End != rs_plan_rule && PlanRule::Backward_All_Time != rs_plan_rule && LpRnLn(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), t, -u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRnLn(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), -t, u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Forward_To_End != rs_plan_rule && PlanRule::Backward_All_Time != rs_plan_rule && LpRnLn(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(1), t, -u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRnLn(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(1), -t, u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    // backwards
    if (PlanRule::Forward_To_End != rs_plan_rule && PlanRule::Backward_All_Time != rs_plan_rule && LpRpLn(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), t, u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRpLn(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), -t, -u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Forward_To_End != rs_plan_rule && PlanRule::Backward_All_Time != rs_plan_rule && LpRpLn(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(1), t, u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRpLn(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(1), -t, -u, v, 0, 0, L);
    }
    else
        ;
};

/**
 * @brief CCCC类RS路径计算
 */
// formula 8.7
inline bool RSCurve::LpRupLumRm(double x, double y, double phi, double& t, double& u, double& v) {
    double xi = x + sin(phi), eta = y - 1. - cos(phi), u1, theta, alpha;
    Polar(xi, eta, u1, theta);
    if (u1 <= 4) {
        if (u1 > 2) {
            alpha = acos(u1 / 4 - 0.5);
            t     = Mod2pi(M_PI / 2 + theta - alpha);
            u     = Mod2pi(M_PI - alpha);
            v     = Mod2pi(phi - t + 2 * u);
        }
        else {
            alpha = acos(u1 / 4 + 0.5);
            t     = Mod2pi(M_PI / 2 + theta + alpha);
            u     = Mod2pi(alpha);
            v     = Mod2pi(phi - t + 2 * u);
        }
        if (Valid(t) && Valid(v) && Valid(u)) return true;
    }
    else
        ;
    t = 0;
    u = 0;
    v = 0;
    return false;
}
// formula 8.8
inline bool RSCurve::LpRumLumRp(double x, double y, double phi, double& t, double& u, double& v) {
    double xi = x + sin(phi), eta = y - 1. - cos(phi), u1, theta, alpha, va1, va2;
    Polar(xi, eta, u1, theta);
    if (u1 <= 6) {
        va1 = 1.25 - u1 * u1 / 16;
        if (va1 >= 0 && va1 <= 1) {
            u     = acos(va1);
            va2   = sin(u);
            alpha = asin(2 * va2 / u1);
            t     = Mod2pi(M_PI / 2 + theta + alpha);
            v     = Mod2pi(t - phi);
            if (Valid(t) && Valid(v) && Valid(u)) return true;
        }
    }
    else
        ;
    t = 0;
    u = 0;
    v = 0;
    return false;
}
void RSCurve::CCCC() {
    double t, u, v, Lmin = opti_rs_path.length, L;
    if (Lmin < 1e-6)
        Lmin = DBL_MAX;
    else
        ;
    double x = new_end.x, y = new_end.y, phi = new_end.angle;
    //         if (PlanRule::Forward_To_End != rs_plan_rule &&
    //             PlanRule::Backward_All_Time != rs_plan_rule && LpRupLumRm(x, y, phi, t, u, v)
    //             && Lmin > (L = fabs(t) + 2.*fabs(u) + fabs(v)))
    //         {
    //             opti_rs_path.set(reeds_shepp_path_type_v.at(2),t,u,-u,-v,0,L);
    //             Lmin = L;
    //         }
    //         else;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRupLumRm(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + 2. * fabs(u) + fabs(v))) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(2), -t, -u, u, v, 0, L);
        Lmin = L;
    }
    else
        ;
    //         if (PlanRule::Forward_To_End != rs_plan_rule &&
    //             PlanRule::Backward_All_Time != rs_plan_rule && LpRupLumRm(x, -y, -phi, t, u, v)
    //             && Lmin > (L = fabs(t) + 2.*fabs(u) + fabs(v))) // reflect
    //         {
    //             opti_rs_path.set(reeds_shepp_path_type_v.at(3),t,u,-u,-v,0,L);
    //             Lmin = L;
    //         }
    //         else;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRupLumRm(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + 2. * fabs(u) + fabs(v))) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(3), -t, -u, u, v, 0, L);
        Lmin = L;
    }
    else
        ;

    if (PlanRule::Normal_Planning == rs_plan_rule && LpRumLumRp(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + 2. * fabs(u) + fabs(v))) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(2), t, -u, -u, v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRumLumRp(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + 2. * fabs(u) + fabs(v))) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(2), -t, u, u, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRumLumRp(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + 2. * fabs(u) + fabs(v))) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(3), t, -u, -u, v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRumLumRp(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + 2. * fabs(u) + fabs(v))) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(3), -t, u, u, -v, 0, L);
    }
    else
        ;
};

/**
 * @brief CCSC类RS路径
 */
// formula 8.9（forward）
inline bool RSCurve::LpRmSmLm(double x, double y, double phi, double& t, double& u, double& v) {
    double xi = x - sin(phi), eta = y - 1. + cos(phi), u1_squar, u1, theta, alpha, va1;
    Polar(xi, eta, u1, theta);
    u1_squar = u1 * u1;
    if (u1_squar >= 4) {
        va1 = 1.25 - u1 * u1 / 16;
        if (va1 >= 0 && va1 <= 1) {
            u = sqrt(u1_squar - 4) - 2;
            if (u >= 0) {
                alpha = atan2(2, u + 2);
                t     = Mod2pi(M_PI / 2 + theta + alpha);
                v     = Mod2pi(t + M_PI / 2 - phi);
                if (Valid(t) && Valid(v)) return true;
            }
        }
    }
    else
        ;
    t = 0;
    u = 0;
    v = 0;
    return false;
}
// formula 8.9（backward）
inline bool RSCurve::LpRmSmLmBack(double x, double y, double phi, double& t, double& u, double& v) {
    double xi = x - sin(phi), eta = y - 1. + cos(phi), u1_squar, u1, theta, alpha;
    Polar(xi, eta, u1, theta);
    u1_squar = u1 * u1;
    if (u1 >= 4) {
        u = sqrt(u1_squar - 4) - 2;
        if (u > 0) {
            alpha = atan2(u + 2, 2);
            t     = Mod2pi(M_PI / 2 + theta - alpha);
            v     = Mod2pi(t - M_PI / 2 - phi);
            if (Valid(t) && Valid(v)) {
                return true;
            }
        }
    }
    else
        ;
    t = 0;
    u = 0;
    v = 0;
    return false;
}

// formula 8.10
inline bool RSCurve::LpRmSmRm(double x, double y, double phi, double& t, double& u, double& v) {
    double xi = x + sin(phi), eta = y - 1. - cos(phi), u1, theta;
    Polar(xi, eta, u1, theta);
    if (u1 >= 2) {
        t = Mod2pi(M_PI / 2 + theta);
        u = u1 - 2;
        v = Mod2pi(phi - t - M_PI / 2);
        if (Valid(t) && Valid(v)) {
            return true;
        }
    }
    else
        ;
    t = 0;
    u = 0;
    v = 0;
    return false;
}
// formula 8.10(backward)
inline bool RSCurve::LpRmSmRmBack(double x, double y, double phi, double& t, double& u, double& v) {
    double xi = x + sin(phi), eta = y - 1. - cos(phi), u1, theta;
    Polar(xi, eta, u1, theta);
    if (u1 >= 2) {
        t = Mod2pi(theta);
        u = u1 - 2;
        v = Mod2pi(phi - t - M_PI / 2);
        if (Valid(t) && Valid(v)) {
            return true;
        }
    }
    else
        ;
    t = 0;
    u = 0;
    v = 0;
    return false;
}
void RSCurve::CCSC() {
    if (PlanRule::Backward_All_Time == rs_plan_rule) {
        return;
    }
    double t, u, v, Lmin = opti_rs_path.length, L;
    if (Lmin < 1e-6)
        Lmin = DBL_MAX;
    else
        ;
    double x = new_end.x, y = new_end.y, phi = new_end.angle;
    if (PlanRule::Forward_To_End != rs_plan_rule && PlanRule::Backward_All_Time != rs_plan_rule && LpRmSmLm(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(4), t, -0.5 * M_PI, -u, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRmSmLm(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(4), -t, 0.5 * M_PI, u, v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Forward_To_End != rs_plan_rule && LpRmSmLm(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(5), t, -0.5 * M_PI, -u, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRmSmLm(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(5), -t, 0.5 * M_PI, u, v, 0, L);
        Lmin = L;
    }
    else
        ;

    if (PlanRule::Forward_To_End != rs_plan_rule && PlanRule::Backward_All_Time != rs_plan_rule && LpRmSmRm(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(8), t, -0.5 * M_PI, -u, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRmSmRm(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(8), -t, 0.5 * M_PI, u, v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Forward_To_End != rs_plan_rule && PlanRule::Backward_All_Time != rs_plan_rule && LpRmSmRm(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(9), t, -0.5 * M_PI, -u, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRmSmRm(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(9), -t, 0.5 * M_PI, u, v, 0, L);
        Lmin = L;
    }
    else
        ;

    // backwards
    if (PlanRule::Forward_To_End != rs_plan_rule && PlanRule::Backward_All_Time != rs_plan_rule && LpRmSmLmBack(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(6), t, u, 0.5 * M_PI, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRmSmLmBack(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(6), -t, -u, -0.5 * M_PI, v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Forward_To_End != rs_plan_rule && PlanRule::Backward_All_Time != rs_plan_rule && LpRmSmLmBack(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(7), t, u, 0.5 * M_PI, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRmSmLmBack(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(7), -t, -u, -0.5 * M_PI, v, 0, L);
        Lmin = L;
    }
    else
        ;

    if (PlanRule::Forward_To_End != rs_plan_rule && PlanRule::Backward_All_Time != rs_plan_rule && LpRmSmRmBack(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(11), t, u, 0.5 * M_PI, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRmSmRmBack(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(11), -t, -u, -0.5 * M_PI, v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Forward_To_End != rs_plan_rule && PlanRule::Backward_All_Time != rs_plan_rule && LpRmSmRmBack(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(10), t, u, 0.5 * M_PI, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRmSmRmBack(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(10), -t, -u, -0.5 * M_PI, v, 0, L);
    }
    else
        ;
};

/**
 * @brief CCSCC类RS路径计算
 */
// formula 8.11
inline bool RSCurve::LpRmSLmRp(double x, double y, double phi, double& t, double& u, double& v) {
    double xi = x + sin(phi), eta = y - 1. - cos(phi), u1, theta, u1_squar, alpha;
    Polar(xi, eta, u1, theta);
    u1_squar = u1 * u1;
    if (u1_squar >= 16) {
        u = sqrt(u1_squar - 4) - 4;
        if (u >= 0) {
            alpha = atan2(2, u + 4);
            t     = Mod2pi(M_PI / 2 + theta + alpha);
            v     = Mod2pi(t - phi);
            if (Valid(t) && Valid(v)) {
                return true;
            }
        }
    }
    else
        ;
    t = 0;
    u = 0;
    v = 0;
    return false;
}
void RSCurve::CCSCC() {
    double t, u, v, Lmin = opti_rs_path.length, L;
    if (PlanRule::Normal_Planning == rs_plan_rule && Lmin < 1e-6)
        Lmin = DBL_MAX;
    else
        ;
    double x = new_end.x, y = new_end.y, phi = new_end.angle;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRmSLmRp(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + M_PI)) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(16), t, -0.5 * M_PI, -u, -0.5 * M_PI, v, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRmSLmRp(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + M_PI)) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(16), -t, 0.5 * M_PI, u, 0.5 * M_PI, -v, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRmSLmRp(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + M_PI)) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(17), t, -0.5 * M_PI, -u, -0.5 * M_PI, v, L);
        Lmin = L;
    }
    else
        ;
    if (PlanRule::Normal_Planning == rs_plan_rule && LpRmSLmRp(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + M_PI)) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(17), -t, 0.5 * M_PI, u, 0.5 * M_PI, -v, L);
    }
    else
        ;
};

} // namespace GlobalPlanning
