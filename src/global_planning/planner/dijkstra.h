#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <vector>
#include <float.h>
#include <iostream>
#include <mutex>
#include <list>
#include <map>
#include "../os/os_type.h"

using namespace std;
using std::list;
using std::map;
#define INF 0x7fffffff
class Dijkstra
{
private:
    vector<vector<double> > MGraph;
    //起始节点与目标节点最小值均为1
    int start;
    int end;
    vector<int> path;

public:
    bool searchpath();
    Dijkstra(){}
    ~Dijkstra(){}
    void InitialDijkstra(vector< vector<double> > MGraph_,int start_,int end_);
    vector<unsigned char> GetPath();
    std::shared_ptr<spdlog::logger> threadLogger_;


//    bool           flag;
//    int            len;
//    int            curNode;
//    vector<bool>   close;
//    vector<int>    father;
//    vector<double> dist;



};

#endif // DIJKSTRA_H
