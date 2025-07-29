
/**
 * Created Time: 2024.07.10
 * File name:    interface.h
 * Author:      yanyifeng(yanyifeng@wicri.org)
 * Brief:        规划库编译为动态库后，对外的接口
 * Include:      Class: GlobalVariable 单例类，相当于整个系统的全局变量
 * Copyright:    2024 WICRI
 */
#ifndef GLOBAL_PLANNING_INTERFACE_INTERFACE_H
#define GLOBAL_PLANNING_INTERFACE_INTERFACE_H

#include <filesystem>
#include <iostream>
#include <mutex>

#include "globalvariable.h"
#include "parser/parser.h"

namespace fs = std::filesystem;

extern "C" {
char* GlobalPathPlanning(char* point_veh_start_end); // 全局轨迹规划
bool  GetMap(char* parea);                           // 初始化自动获取地图信息
char* PathPredicting(char* input_info);              // 有人车路径预测
char* LoadAreaPlanning(char* point_veh_start_end);//装载区排队点自动生存算法
}


#endif // GLOBAL_PLANNING_INTERFACE_INTERFACE_H