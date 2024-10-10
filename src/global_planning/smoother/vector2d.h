#ifndef VECTOR2D
#define VECTOR2D

#include <cmath>
#include <iostream>
// namespace GlobalPlanning {
// ###################################################
//                                             VECTOR2
// ###################################################
/// A class describing a simple 2D vector
class Vector2D {
  public:
    /// default constructor
    inline Vector2D(const float x = 0, const float y = 0) {
        this->x = x;
        this->y = y;
    }
    /// a method to multiply a vector by a scalar
    inline Vector2D operator*(const float k) const {
        return Vector2D(x * k, y * k);
    }
    /// a method to divide a vector by a scalar
    inline Vector2D operator/(const float k) const {
        return Vector2D(x / k, y / k);
    }
    /// a method to add a vector to a vector
    inline Vector2D operator+(const Vector2D& b) const {
        return Vector2D(x + b.x, y + b.y);
    }
    /// a method to subtract a vector from a vector
    inline Vector2D operator-(const Vector2D& b) const {
        return Vector2D(x - b.x, y - b.y);
    }
    /// a method to negate a vector
    inline Vector2D operator-() const {
        return Vector2D(-x, -y);
    }
    /// a convenience method to print a vector
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& b) {
        os << "(" << b.x << "|" << b.y << ")";
        return os;
    }
    /// a method to calculate the length of the vector
    float length() const {
        return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }
    // 归一化向量
    void Normalize() {
        float len = length();
        if (len > 0) {
            x /= len;
            y /= len;
        }
    }
    // 计算当前向量与给定向量之间的距离
    float DistanceTo(const Vector2D& b) const {
        return std::sqrt(std::pow(x - b.x, 2) + std::pow(y - b.y, 2));
    }
    // 计算当前向量与给定向量之间的平方距离
    float DistanceSquareTo(const Vector2D& b) const {
        return std::pow(x - b.x, 2) + std::pow(y - b.y, 2);
    }
    // 计算两个向量的叉积
    float CrossProd(const Vector2D& b) const {
        return x * b.y - y * b.x;
    }
    // 计算两个向量的点积
    float InnerProd(const Vector2D& b) const {
        return x * b.x + y * b.y;
    }
    // 获取向量与正 x 半轴之间的角度
    float Angle() const {
        return std::atan2(y, x);
    }
    /// 根据给定角度创建单位向量
    static Vector2D CreateUnitVec2d(const float angle) {
        return Vector2D(std::cos(angle), std::sin(angle));
    }
    /// 将当前向量自身旋转给定角度
    void SelfRotate(const float angle) {
        float tempX = x * std::cos(angle) - y * std::sin(angle);
        y           = x * std::sin(angle) + y * std::cos(angle);
        x           = tempX;
    }
    /// 将向量旋转给定角度
    Vector2D rotate(const float angle) const {
        Vector2D rotated(*this);
        rotated.SelfRotate(angle);
        return rotated;
    }
    /// a method to calculate the length of the vector
    float sqlength() const {
        return x * x + y * y;
    }
    /// a method to calculate the dot product of two vectors
    float dot(Vector2D b) const {
        return x * b.x + y * b.y;
    }
    /// a method that returns the orthogonal complement of two vectors
    inline Vector2D ort(Vector2D b) const {
        Vector2D a(this->x, this->y);
        Vector2D c;
        // multiply b by the dot product of this and b then divide it by b's length
        c = a - b * a.dot(b) / b.sqlength();
        return c;
    }
    inline float getX() {
        return x;
    }
    inline float getY() {
        return y;
    }
    //  void setT(float t) { this->t = t; }
    //  float getT() { return t; }
  public:
    /// the x part of the vector
    float x;
    /// the y part of the vector
    float y;
    //  /// the theta part for plotting purposes
    //  float t;
};
inline Vector2D operator*(double k, const Vector2D& b) {
    return (b * k);
}
// } // namespace GlobalPlanning
#endif // VECTOR2D
