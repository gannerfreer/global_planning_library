/***************************************************/
/*            Author: cxp                          */
/*            Contact: chenxinpeng_hnu@163.com     */
/*            Last update: 2021-11-16              */
/***************************************************/
/*
Description: The header file for C++ class node2d.
*/
#ifndef NODE2D_H
#define NODE2D_H

#include "../os/os.h"
#include "constants.h"

namespace HybridAStar {
/*!
\brief 二维栅格A*算法的节点类定义
       参考：https://github.com/karlkurzer/path_planner
*/
class Node2D
{
public:
    Node2D():Node2D(0, 0, 0, 0) {}
    Node2D(int16 x, int16 y, float32 g, float32 h)
    {
        this->x = x;
        this->y = y;
        this->g = g;
        this->h = h;
        this->idx = setIdx();
    }

    /// set the index of the node in the 2D array
    inline uint32 setIdx() const
    {
        uint32 hash = 0;
        hash |= (this->x) << 16;
        hash |= (this->y & 0x0000FFFF);
        return hash;
    }

    /// open the node
    void open() { o = true; c = false; }
    /// close the node
    void close() { c = true; o = false; }
    /// set the node neither open nor closed
    void reset() { c = false; o = false; }
    /// discover the node
    void discover() { d = true; }


    /// get the x position
    int16 getX() const { return x; }
    /// get the y position
    int16 getY() const { return y; }
    /// get the cost-so-far (real value)
    float32 getG() const { return g; }
    /// get the cost-to-come (heuristic value)
    float32 getH() const { return h; }
    /// get the total estimated cost
    float32 getF() const { return g + h; }
    /// get the index of the node in the 2D array
    uint32 getIdx() const { return idx; }

    /// determine whether the node is open
    bool  isOpen() const { return o; }
    /// determine whether the node is closed
    bool  isClosed() const { return c; }
    /// determine whether the node is discovered
    bool  isDiscovered() const { return d; }
    ///更新启发值，即离目标的预估代价
    void updateH(const Node2D& goal) { h = sqrt((x - goal.x) * (x - goal.x) + (y - goal.y) * (y - goal.y));}
    ///节点比较函数，当两个节点的x,y一致时为同一节点
    bool operator == (const Node2D& rhs) const {return x == rhs.x && y == rhs.y;}
    ///创建successor
    Node2D createSuccessor(const int16 index);

    ///可能的方向个数
    static const int16 dir;
    ///X-方向可能的移动方向
    static const int16 dx[];
    ///y-方向可能的移动方向
    static const int16 dy[];
    ///每个方向移动对应的位移
    static const float32 dg[];
private:
    int16 x;       //节点x栅格坐标
    int16 y;       //节点y栅格坐标
    float32 g;     //节点累计代价值
    float32 h;     //节点启发值
    uint32 idx;    //节点对应哈希值索引
    bool o;        //是否被加入open集中
    bool c;        //是否被加入close集中
    bool d;        //是否被探索
};

}

#endif // NODE2D_H
