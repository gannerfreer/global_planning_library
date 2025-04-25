/******************************************
 > Copyright(C):    湖南大学
 > File name:       c_map_analysis.h
 > Author:          jh(HaoJiangYit@163.com)
 > Created Time:    2021/11/24
 > Brief:           编写并构建程序框架,完成函数功能,完善程序逻辑
 * ****************************************/
/*
    Park map analysis
*/
#ifndef __C_MAP_ANALYSIS_H__
#define __C_MAP_ANALYSIS_H__
// c++文件
#include <stdio.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "../third_lib/rapidjson/document.h"
#include "../third_lib/rapidjson/stringbuffer.h"
#include "../third_lib/rapidjson/writer.h"

// 公共文件
// #include "../common/c_conf_struct.h"
#include "../common/common_struct.h"
// #include "config_io.h"
#include <geometry_msgs/Point.h>

#include "../globalvariable.h"
#include "algorithm"


using namespace GlobalPlanning;
using rapidjson::Value;
#define DEBUG true // 0:潍柴地图 1：园区规划
class CConfigureIO {
  public:
    CConfigureIO() = default;
    ~CConfigureIO() {}

  public:
    static bool GetMap(vector<vector<double>>& road_directed_graph_, vector<_BorderPoint>& map_border_, map<int, _SingleTraj>& all_referencelines_, vector<int>& sequence_mapping_, tarRviz& tar_rviz);
    static bool GetVehicleParam(_VehicleParam& vehicle_param);
    static bool GetMap_PathPredicting(map<int, _SingleTraj>& all_referencelines, map<int, vector<int>>& referenceline_relation, tarRviz& tar_rviz);

  public:
    static char* buffer;

  private:
    // 用于存放地图名字
    static const string map_file_name;

    static const int INF2;

  public:
    // test for rviz
    static vector<vector<geometry_msgs::Point>> global_path_;
};

#endif // C_CONF_IO_H
