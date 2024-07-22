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

using std ::cout;
using std ::endl;
using namespace GlobalPlanning;
using rapidjson::Value;
#define DEBUG true // 0:潍柴地图 1：园区规划
class CConfigureIO {
  public:
    CConfigureIO() = default;
    ~CConfigureIO() {}

  public:
    static bool GetMap(std::vector<Single_Zone>& all_zones, Directed_Graph& road_directed_graph,
                       GlobalPlanning::tarRviz& tar_rviz);
    static bool GetVehicleParam(vehicle_param& vehicle_param);


  public:
    static char* buffer;

  private:
    // 用于存放地图名字
    static const std ::string map_file_name;

    static const int INF2;

  public:
    // test for rviz
    static std ::vector<std ::vector<geometry_msgs::Point>> global_path_;
};

#endif // C_CONF_IO_H
