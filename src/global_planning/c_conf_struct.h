#ifndef C_CONF_STRUCT_H
#define C_CONF_STRUCT_H

#include <string>
#include <vector>
#include <map>

#include "../os/os.h"
//#include <QString>
//#include <QPolygonF>
//#include <QPointF>
#include "general_class.h"
//#include <geometry_msgs/Point.h>

using std::string;
using std::vector;
using std::map;

#define DEFAULT_SPEED 5.5

#if 0
typedef struct
{
  double x;
  double y;
  double z;
}Point_3d;

typedef struct
{
    double      d_Crossing_speed;
    double      d_Max_Acc;
    double      d_Min_Acc;
    double      d_Max_Deceleration;
}tar_Speed,*ptar_Speed;
#endif

struct coordinate
{
    coordinate() {
        this->x = 0.0;
        this->y = 0.0;
        this->z = 0.0;
        this->ntype = 1;
    }
    coordinate(float64 x_, float64 y_, float64 z_,int ntype_=1)
    {
        this->x = x_;
        this->y = y_;
        this->z = z_;
        this->ntype =ntype_;
    }
    float64 x;  // x坐标, 单位：m
    float64 y;  // y坐标, 单位：m
    float64 z;  // z坐标, 单位：m
    int ntype; //1为不可跨越，0为可跨越
};

/**
* @brief 路点结构体
*/
struct point
{
    point() {
        this->x = 0.0;
        this->y = 0.0;
        this->z = 0.0;
        this->left = 2.0;
        this->right = 2.0;
        this->angle = 0.0;
        this->reversing = 0.0;
        this->slop = 0.0;
        this->speed = DEFAULT_SPEED;
        this->unwaypointattr = 0;
    }
    point(float64 x_, float64 y_, float64 z_,float64 angle_)
    {
        this->x = x_;
        this->y = y_;
        this->z = z_;
        this->left = 2.0;
        this->right = 2.0;
        this->angle = angle_;
        this->reversing = 0.0;
        this->slop = 0.0;
        this->speed = DEFAULT_SPEED;
        this->unwaypointattr = 0;
    }
    float64 x;  // x坐标, 单位：m
    float64 y;  // y坐标, 单位：m
    float64 z;  // z坐标, 单位：m
    float64 left; //距左边界值
    float64 right;//距右边界值
    float64 angle;  // 方向, 单位：rad
    float64 reversing;
    float64 slop;
    float64 speed;
    short   unwaypointattr;//2表示路口    从0开始
};

//属性
typedef struct
{
    string                      str_area_Id;                //区域id
    string                     str_area_name;              //区域名
    double                      n_max_speed;                //限速
    string                     str_area_type;              //区域类型
}Attribute,*pAttribute;


//子属性
typedef struct
{
    string                     str_load_type;         //装载类型
}Sub_Attribute,*pSub_Attribute;

//边界点
typedef struct
{
    int                         n_point_num;                //边界点的数量
    vector<coordinate >          vec_area_point;               //边界点
    // QPolygonF                    polygon;
}Border,*pBorder;

typedef struct
{
    coordinate                  coor_x_y_z;
    double                       f_angle;
}my3D_angle_Point,*pmy3D_angle_Point;

//排队点
typedef struct
{
    int                         n_num;                      //排队点数量
    vector<my3D_angle_Point>    vec_queue;
}Queue,*pQueue;

//装载点
typedef struct
{
    int                         n_num;                    //装载点数量
    vector<my3D_angle_Point>    vec_queue;
}Load,*pLoad;

//装载点
typedef struct
{
    int                         n_num;                    //卸载点数量
    vector<my3D_angle_Point>    vec_queue;
}UnLoad,*pUnLoad;

//停车点
typedef struct
{
    int                         n_num;               //点的数量
    vector<my3D_angle_Point>    vec_point;
}ParkingSpot,*pParkingSpot;

//参考路径
typedef struct
{
    int                     n_num;
    map<std :: string,vector<point> > map_vec_ref;            //key为参考路径名，value为指定参考路径的路点信息
//    vector<QString>         vec_Id_Name;
}ReferencePath,*pReferencePath;

//无向图
typedef struct
{
    int                                n_num_undirected;                               //无向图顶点个数
    vector <std :: string>             vec_node_id_undirected;                         //无向图顶点名称
    map <std :: string,int>            map_undirected;                                 //key为顶点名，value为顶点序号（从0开始）
    vector < vector<double> >          vec_path_undirected;                            //无向图
}UnDirected_Graph,*pUnDirected_Graph;



//区域
typedef struct
{
    double                      Crossing_speed;         //路口速度
    string                      strversion;             //map版本号
    Attribute                   tag_Attribute;          //区域的属性
    Sub_Attribute               tag_Sub_Attribute;      //区域的子属性
    Border                      tag_Border;             //区域边界
    Queue                       tag_Queue;              //区域排土点
    Load                        tag_Load;               //区域装载点
    UnLoad                      tag_UnLoad;               //区域装载点
    ReferencePath               tag_ReferencePath;      //区域的参考路径
    ParkingSpot                 tag_Parking_Spot;       //区域停车点
}Area,*pArea;




#if 0
//typedef struct
//{
//    global_path::Coordinate                 coor_x_y_z;
////    int                                     n_type;         //点属性，分为可跨越和不可跨越
//}my3D_Point,*pmy3D_Point;




//typedef struct
//{
//    my3D_angle_Point    point;
//    double              left;
//    double              right;
//    double              reversing;
//}Ref_Path_Point,*pRef_Path_Point;

//可视化
typedef struct
{
    vector<Point_3d> vec_point;
    double minx;
    double miny;
}tarRviz,*ptarRviz;

//kafka参数
typedef struct
{
    string strHost_Port;
    string strTopic_infor;
    string strTopic_vstate;
    string strGlobal_return;
    vector<string> vec_all_topic;
    string strGroupid;
}tarKafka,*ptarKafka;

////静态障碍物，测试用
//typedef
//typedef struct
//{
//    int x;
//    int y;
//    int z;
//    int orientation;
//    int track_state;
//    vector<
//}

#endif

#endif // C_CONF_STRUCT_H
