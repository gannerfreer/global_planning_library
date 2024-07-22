/***************************************************/
/*            Author: cxp                          */
/*            Contact: chenxinpeng_hnu@163.com     */
/*            Last update: 2021-11-16              */
/***************************************************/
/*
Description: The source file for C++ class node2d.
*/

#include "node2d.h"

using namespace GlobalPlanning;


// possible directions
const short Node2D::dir = 8;
// possible movements：8个方向相对中心(0, 0)的移动
const short Node2D::dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const short Node2D::dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
const float Node2D::dg[] = {1, 1.414, 1, 1.414, 1, 1.414, 1, 1.414};

Node2D Node2D::createSuccessor(const short index) {
    short xSucc = x + Node2D::dx[index];
    short ySucc = y + Node2D::dy[index];
    return Node2D(xSucc, ySucc, g + dg[index], 0);
}
