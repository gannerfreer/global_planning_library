/******************************************
 > Copyright(C):    湖南大学
 > File name:       point.h
 > Author:          cxp(chenxinpeng_hnu@163.com)
 > Created Time:    2021/10/09
 > Brief:           2维坐标点运算类实现
 * ****************************************/
#ifndef POINT_H
#define POINT_H
#include <iostream>

namespace curve {
class Point {
  public:
    /// 默认构造
    inline Point(const float x = 0, const float y = 0, const float angle = 0, const float curvature = 0) {
        this->x         = x;
        this->y         = y;
        this->angle     = angle;
        this->curvature = curvature;
    }
    /// 右乘标量k
    inline Point operator*(const float k) const {
        return Point(x * k, y * k, angle);
    }
    /// 除以标量k
    inline Point operator/(const float k) const {
        return Point(x / k, y / k);
    }
    /// 两点相加
    inline Point operator+(const Point& point) const {
        return Point(x + point.x, y + point.y, angle);
    }
    /// 两点相减
    inline Point operator-(const Point& point) const {
        return Point(x - point.x, y - point.y);
    }
    /// 复合赋值运算符-=
    inline Point& operator+=(const Point& point) {
        this->x += point.x;
        this->y += point.y;
        return *this;
    }
    /// 复合赋值运算符-
    inline Point& operator-=(const Point& point) {
        this->x -= point.x;
        this->y -= point.y;
        return *this;
    }

    /// 声明类外左乘标量k重载函数为该类的友元函数
    friend inline Point operator*(const float, const Point&);

    /// 加负号
    inline Point operator-() const {
        return Point(-x, -y);
    }
    /// 打印
    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "(" << point.x << "," << point.y << ")";
        return os;
    }

    inline void SetX(float x) {
        this->x = x;
    }
    inline void SetY(float y) {
        this->y = y;
    }
    inline void SetAngle(float angle) {
        this->angle = angle;
    }
    inline void SetCurvature(float curvature) {
        this->curvature = curvature;
    }
    inline float GetX() const {
        return x;
    }
    inline float GetY() const {
        return y;
    }
    inline float GetAngle() const {
        return angle;
    }
    inline float GetCurvature() const {
        return curvature;
    }

  private:
    float x;
    float y;
    float angle;
    float curvature;
};
/// 类外重载，实现左乘标量
inline Point operator*(const float k, const Point& point) {
    return (point * k);
}
} // namespace curve
#endif // POINT_H
