/***************************************************/
/*            Author: cxp                          */
/*            Contact: chenxinpeng_hnu@163.com     */
/*            Last update: 2021-11-16              */
/***************************************************/
/*
Description: The source file for C++ class node2d.
*/

#include "../include/node2d.h"

using namespace HybridAStar;


// possible directions
const int16 Node2D::dir = 8;
// possible movements：8个方向相对中心(0, 0)的移动
const int16 Node2D::dx[] = { -1, -1, 0, 1, 1,  1,  0, -1 };
const int16 Node2D::dy[] = {  0,  1, 1, 1, 0, -1, -1, -1 };
const float32 Node2D::dg[] = {1, 1.414, 1, 1.414, 1, 1.414, 1, 1.414} ;

Node2D Node2D::createSuccessor(const int16 index)
{
    int16 xSucc = x + Node2D::dx[index];
    int16 ySucc = y + Node2D::dy[index];
    return Node2D(xSucc, ySucc, g + dg[index], 0);
}
