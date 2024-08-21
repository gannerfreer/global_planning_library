/***************************************************/
/*            Author: Yang Fan                     */
/*            Contact: allenyangfan@163.com        */
/*            Last update: 2020-04-22              */
/***************************************************/
/*
  Description: The .cpp file for C++ class r_s_curve.
*/

#include "r_s_curve_for_h.h"

namespace GlobalPlanning {
// 构造函数
RSCurve_H::RSCurve_H() {
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
RSCurve_H::~RSCurve_H() {}
void RSCurve_H::Init(_VehicleParam& vehicleparam) {
    m_vehicle_prarm_ = vehicleparam;
}

/**
 * @brief RS曲线规划类接口函数
 */
bool RSCurve_H::PlanRSPath(const Point start, const Point end) {
    //     cout << "6666m_vehicle_prarm_.radious = " << m_vehicle_prarm_.radious << "\n";
    // threadLogger_->info("start:{},{},{}  end:{},{},{}", start.x, start.y, start.angle, end.x, end.y, end.angle);

    // opti_rs_path.length = DBL_MAX;
    opti_rs_path.set(reeds_shepp_path_type_v.at(0), 0, 0, 0, 0, 0, DBL_MAX);
    CoordinateTransformation(start, end, m_vehicle_prarm_.radious); // 坐标转换及归一化
    if (ReedsSheppGeneration()) {
        if (opti_rs_path.type.empty()) return false;
        return true;
    }
    else {
        return false;
    }
}


/**
 * @brief 坐标系转换和归一化函数
 */
void RSCurve_H::CoordinateTransformation(Point start, Point end, double kRadious) {
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
// bool RSCurve_H::LengthValid() {
//     if (fabs(opti_rs_path.t) > 0 && fabs(opti_rs_path.u) > 0 && fabs(opti_rs_path.v) > 0) {
//         vector<double> s;
//         s.push_back(opti_rs_path.t);
//         s.push_back(opti_rs_path.u);
//         s.push_back(opti_rs_path.v);
//         if (fabs(opti_rs_path.w) > 1e-6) s.push_back(opti_rs_path.w);
//         if (fabs(opti_rs_path.x) > 1e-6) s.push_back(opti_rs_path.x);

//         double sum = 0;
//         for (unsigned int i = 0; i < s.size() - 1; i++) {
//             sum += fabs(s.at(i)) * m_vehicle_prarm_.radious;
//             if (s.at(i) * s.at(i + 1) > 0)
//                 continue;
//             else {
//                 if (i == 0) {
//                     int temp_direction_rs    = (s.at(0) < 0) ? -1 : 1;
//                     int temp_direction_astar = (a_star_direction != Forward) ? -1 : 1;
//                     if (1 == temp_direction_astar * temp_direction_rs)
//                         continue;
//                     else
//                         ;
//                 }
//                 else if (i == s.size() - 2) {
//                     if (fabs(s.at(s.size() - 1)) * m_vehicle_prarm_.radious < m_vehicle_prarm_.min_path_Length) {
//                         //threadLogger_->info("fabs(s.at(s.size() - 1)) * m_vehicle_prarm_.radious < m_vehicle_prarm_.min_path_Length");
//                         return false;
//                     }
//                 }
//                 else
//                     ;
//                 if (sum < m_vehicle_prarm_.min_path_Length) {
//                     //threadLogger_->info("sum < m_vehicle_prarm_.min_path_Length");
//                     return false;
//                 }
//                 else
//                     ;
//             }
//             sum = 0;
//         }
//         return true;
//     }
//     else {}
//     return false;
// }

/**
 * @brief 生成最优Reeds-Shepp路段
 */
bool RSCurve_H::ReedsSheppGeneration() {
    CSC();
    // if (!LengthValid()) // true:存在路段长度小于最短长度限制,清空 opti_rs_path
    // {
    //     //threadLogger_->info("CSC fail");
    //     opti_rs_path.set(reeds_shepp_path_type_v.at(0), 0, 0, 0, 0, 0, 0);
    // }
    // else
    //     ;
    CCC();
    // if (!LengthValid()) {
    //     //threadLogger_->info("CCC fail");
    //     opti_rs_path.set(reeds_shepp_path_type_v.at(0), 0, 0, 0, 0, 0, 0);
    // }
    // else
    //     ;
    CCCC();
    // if (!LengthValid()) {
    //     //threadLogger_->info("CCCC fail");
    //     opti_rs_path.set(reeds_shepp_path_type_v.at(0), 0, 0, 0, 0, 0, 0);
    // }
    // else
    //     ;
    CCSC();
    // if (!LengthValid()) {
    //     //threadLogger_->info("CCSC fail");
    //     opti_rs_path.set(reeds_shepp_path_type_v.at(0), 0, 0, 0, 0, 0, 0);
    // }
    // else
    //     ;
    CCSCC();
    // if (!LengthValid()) {
    //     //threadLogger_->info("CCSCC fail");
    //     opti_rs_path.set(reeds_shepp_path_type_v.at(0), 0, 0, 0, 0, 0, 0);
    // }
    // else
    //     ;
    // return true;
    if (fabs(opti_rs_path.t) > 1e-6 && fabs(opti_rs_path.u) > 1e-6 && fabs(opti_rs_path.v) > 1e-6)
        return true; // RS路径前三段存在则认为生成最优RS路径成功
    else {
        if (fabs(opti_rs_path.t) <= 1e-6) {
            // threadLogger_->info("t<=0");
        }
        if (fabs(opti_rs_path.u) <= 1e-6) {
            // threadLogger_->info("u<=0");
        }
        if (fabs(opti_rs_path.v) <= 1e-6) {
            // threadLogger_->info("v<=0");
        }
        return false;
    }
}


/**
 * @brief 计算辅助函数
 */
inline double RSCurve_H::Mod2pi(double x) {
    double v = fmod(x, 2. * M_PI);
    if (v < -M_PI)
        v += 2. * M_PI;
    else if (v > M_PI)
        v -= 2. * M_PI;
    return v;
}

inline void RSCurve_H::Polar(double x, double y, double& r, double& theta) {
    r     = sqrt(x * x + y * y);
    theta = atan2(y, x);
}

inline bool RSCurve_H::Valid(double theta) {
    if (theta >= 0 && theta <= M_PI)
        return true;
    else
        return false;
}


/**
 * @brief CSC类RS路径计算
 */
// formula 8.1
inline bool RSCurve_H::LpSpLp(double x, double y, double phi, double& t, double& u, double& v) {
    // threadLogger_->info("enter LpSpLp");
    Polar(x - sin(phi), y - 1. + cos(phi), u, t);
    v = Mod2pi(phi - t);
    if (Valid(v) && Valid(t)) {
        // threadLogger_->info("LpSpLp success");
        return true;
    }
    else {
        // threadLogger_->info("LpSpLp fail");
    }
    t = 0;
    u = 0;
    v = 0;
    return false;
}
// formula 8.2
inline bool RSCurve_H::LpSpRp(double x, double y, double phi, double& t, double& u, double& v) {
    // threadLogger_->info("enter LpSpRp");
    double t1, u1, theta;
    Polar(x + sin(phi), y - 1. - cos(phi), u1, t1);
    u1 = u1 * u1;
    if (u1 >= 4.) {
        u     = sqrt(u1 - 4.);
        theta = atan2(2., u);
        t     = Mod2pi(t1 + theta);
        v     = Mod2pi(t - phi);
        if (Valid(t) && Valid(v)) {
            // threadLogger_->info("LpSpRp success");
            return true;
        }
        else {
            // threadLogger_->info("LpSpRp fail");
        }
    }
    else {
        // threadLogger_->info("LpSpRp fail");
    }

    t = 0;
    u = 0;
    v = 0;
    return false;
}
void RSCurve_H::CSC() {
    double t, u, v, Lmin = DBL_MAX, L;
    double x = new_end.x, y = new_end.y, phi = new_end.angle;
    if (LpSpLp(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(14), t, u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpSpLp(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(14), -t, -u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpSpLp(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(15), t, u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpSpLp(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(15), -t, -u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpSpRp(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(12), t, u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpSpRp(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(12), -t, -u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpSpRp(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(13), t, u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpSpRp(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip + reflect
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
inline bool RSCurve_H::LpRnLp(double x, double y, double phi, double& t, double& u, double& v) {
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
inline bool RSCurve_H::LpRnLn(double x, double y, double phi, double& t, double& u, double& v) {
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
inline bool RSCurve_H::LpRpLn(double x, double y, double phi, double& t, double& u, double& v) {
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
void RSCurve_H::CCC() {
    double t, u, v, Lmin = opti_rs_path.length, L;
    if (Lmin < 1e-6)
        Lmin = DBL_MAX;
    else
        ;
    double x = new_end.x, y = new_end.y, phi = new_end.angle;
    if (LpRnLp(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), t, -u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRnLp(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), -t, u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRnLp(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(1), t, -u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRnLp(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(1), -t, u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;

    if (LpRnLn(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), t, -u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRnLn(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), -t, u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRnLn(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(1), t, -u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRnLn(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(1), -t, u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    // backwards
    if (LpRpLn(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), t, u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRpLn(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(0), -t, -u, v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRpLn(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(1), t, u, -v, 0, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRpLn(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v))) // timeflip + reflect
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
inline bool RSCurve_H::LpRupLumRm(double x, double y, double phi, double& t, double& u, double& v) {
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
inline bool RSCurve_H::LpRumLumRp(double x, double y, double phi, double& t, double& u, double& v) {
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
void RSCurve_H::CCCC() {
    double t, u, v, Lmin = opti_rs_path.length, L;
    if (Lmin < 1e-6)
        Lmin = DBL_MAX;
    else
        ;
    double x = new_end.x, y = new_end.y, phi = new_end.angle;
    //         if (
    //               LpRupLumRm(x, y, phi, t, u, v)
    //             && Lmin > (L = fabs(t) + 2.*fabs(u) + fabs(v)))
    //         {
    //             opti_rs_path.set(reeds_shepp_path_type_v.at(2),t,u,-u,-v,0,L);
    //             Lmin = L;
    //         }
    //         else;
    if (LpRupLumRm(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + 2. * fabs(u) + fabs(v))) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(2), -t, -u, u, v, 0, L);
        Lmin = L;
    }
    else
        ;
    //         if (
    //               LpRupLumRm(x, -y, -phi, t, u, v)
    //             && Lmin > (L = fabs(t) + 2.*fabs(u) + fabs(v))) // reflect
    //         {
    //             opti_rs_path.set(reeds_shepp_path_type_v.at(3),t,u,-u,-v,0,L);
    //             Lmin = L;
    //         }
    //         else;
    if (LpRupLumRm(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + 2. * fabs(u) + fabs(v))) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(3), -t, -u, u, v, 0, L);
        Lmin = L;
    }
    else
        ;

    if (LpRumLumRp(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + 2. * fabs(u) + fabs(v))) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(2), t, -u, -u, v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRumLumRp(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + 2. * fabs(u) + fabs(v))) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(2), -t, u, u, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRumLumRp(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + 2. * fabs(u) + fabs(v))) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(3), t, -u, -u, v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRumLumRp(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + 2. * fabs(u) + fabs(v))) // timeflip + reflect
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
inline bool RSCurve_H::LpRmSmLm(double x, double y, double phi, double& t, double& u, double& v) {
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
inline bool RSCurve_H::LpRmSmLmBack(double x, double y, double phi, double& t, double& u, double& v) {
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
inline bool RSCurve_H::LpRmSmRm(double x, double y, double phi, double& t, double& u, double& v) {
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
inline bool RSCurve_H::LpRmSmRmBack(double x, double y, double phi, double& t, double& u, double& v) {
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
void RSCurve_H::CCSC() {
    double t, u, v, Lmin = opti_rs_path.length, L;
    if (Lmin < 1e-6)
        Lmin = DBL_MAX;
    else
        ;
    double x = new_end.x, y = new_end.y, phi = new_end.angle;
    if (LpRmSmLm(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(4), t, -0.5 * M_PI, -u, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSmLm(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(4), -t, 0.5 * M_PI, u, v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSmLm(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(5), t, -0.5 * M_PI, -u, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSmLm(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(5), -t, 0.5 * M_PI, u, v, 0, L);
        Lmin = L;
    }
    else
        ;

    if (LpRmSmRm(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(8), t, -0.5 * M_PI, -u, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSmRm(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(8), -t, 0.5 * M_PI, u, v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSmRm(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(9), t, -0.5 * M_PI, -u, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSmRm(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(9), -t, 0.5 * M_PI, u, v, 0, L);
        Lmin = L;
    }
    else
        ;

    // backwards
    if (LpRmSmLmBack(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(6), t, u, 0.5 * M_PI, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSmLmBack(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(6), -t, -u, -0.5 * M_PI, v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSmLmBack(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(7), t, u, 0.5 * M_PI, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSmLmBack(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(7), -t, -u, -0.5 * M_PI, v, 0, L);
        Lmin = L;
    }
    else
        ;

    if (LpRmSmRmBack(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(11), t, u, 0.5 * M_PI, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSmRmBack(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(11), -t, -u, -0.5 * M_PI, v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSmRmBack(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(10), t, u, 0.5 * M_PI, -v, 0, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSmRmBack(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + 0.5 * M_PI)) // timeflip + reflect
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
inline bool RSCurve_H::LpRmSLmRp(double x, double y, double phi, double& t, double& u, double& v) {
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
void RSCurve_H::CCSCC() {
    double t, u, v, Lmin = opti_rs_path.length, L;
    if (Lmin < 1e-6)
        Lmin = DBL_MAX;
    else
        ;
    double x = new_end.x, y = new_end.y, phi = new_end.angle;
    if (LpRmSLmRp(x, y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + M_PI)) {
        opti_rs_path.set(reeds_shepp_path_type_v.at(16), t, -0.5 * M_PI, -u, -0.5 * M_PI, v, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSLmRp(-x, y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + M_PI)) // timeflip
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(16), -t, 0.5 * M_PI, u, 0.5 * M_PI, -v, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSLmRp(x, -y, -phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + M_PI)) // reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(17), t, -0.5 * M_PI, -u, -0.5 * M_PI, v, L);
        Lmin = L;
    }
    else
        ;
    if (LpRmSLmRp(-x, -y, phi, t, u, v) && Lmin > (L = fabs(t) + fabs(u) + fabs(v) + M_PI)) // timeflip + reflect
    {
        opti_rs_path.set(reeds_shepp_path_type_v.at(17), -t, 0.5 * M_PI, u, 0.5 * M_PI, -v, L);
    }
    else
        ;
};

} // namespace GlobalPlanning
