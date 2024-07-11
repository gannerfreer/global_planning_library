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
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <stdio.h>
#include <random>

// 解析ini的头文件
#include "dictionary.h"
#include "iniparser.h"
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"

// 公共文件
#include "common_struct.h"
#include "c_conf_struct.h"
#include "constants.h"
// #include "config_io.h"
#include <geometry_msgs/Point.h>

using std ::cout;
using std ::endl;
using namespace GlobalPlanning;
using rapidjson::Value;
using namespace HybridAStar::Constants;
#define DEBUG true // 0:潍柴地图 1：园区规划
class CConfigureIO
{
public:
    CConfigureIO() = default;
    ~CConfigureIO() {}

public:
    static bool GetMap(std::vector<Single_Zone> &all_zones, Directed_Graph &road_directed_graph, GlobalPlanning::tarRviz &tar_rviz);
    static bool GetVehicleParam(vehicle_param &vehicle_param);
    static void rand_param(float64 &rand_dist);
#if 0
    static bool pareasmap(char* parse);
    static bool Get_Map_Common(int& nmum,std :: string& strversion);
    //园区规划
    static bool Get_Map_SingleZone(std :: string&,std :: vector<GlobalPlanning :: Single_Zone>&,GlobalPlanning :: tarRviz &);
    //区域ID、区域类型、区域属性、最大速度
    static bool Get_Map_Zone(const int,uint8&,uint8&,uint8&,float32&);
    //区域内的停车点集
    static bool Get_Map_Parking_Spot(const int,std :: vector<GlobalPlanning :: Single_Point>& );
    //区域内的装载点集
    static bool Get_Map_Load(const int,std :: vector<GlobalPlanning :: Single_Point>& );
    //区域内的卸载点集
    static bool Get_Map_Unload(const int,std :: vector<GlobalPlanning :: Single_Point>& );
    //区域的内外边界
    static bool Get_Map_Border(const int,GlobalPlanning :: Single_Border&,std :: vector<GlobalPlanning :: Single_Border>&,GlobalPlanning :: tarRviz &tar_rviz);
    //区域内的参考路径
    static bool Get_Map_Reference_Path(const int,std :: vector<GlobalPlanning :: Single_Trajectory>&);
    //ReferencePath
    static bool Get_Reference_Path(const std :: string strref, GlobalPlanning :: Single_Trajectory&);
    //有向图
    static bool Get_Directed_Graph(GlobalPlanning :: Directed_Graph& );
#endif
private:
    // static inline bool Init_Map();
    // static void SplitString(const std::string &s, std::vector<std::string> &v, const std::string &c);
    // static void Separate_StringList_To_Double(const std::vector<string> &, vector<double>&);

public:
    static char *buffer;
    // static constexpr dictionary * GetPath_txt(std :: string& _txt);
    // constexpr CConfigureIO(std :: string& _area,std :: string& _reference_path,std :: string& _undirected);
private:
    // 用于存放地图名字
    static const std ::string map_file_name;
    // static const std :: string directed_graph;
    // static const std :: string refe_path;
    // static const std :: string area;

    // static dictionary *init_path_txt_;
    // static dictionary *reference_txt_;
    // static dictionary *graph_map_txt_;
    static const int INF2;

public:
    // test for rviz
    static std ::vector<std ::vector<geometry_msgs::Point>> global_path_;
};

#endif // C_CONF_IO_H
