#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <float.h>
#include <stdio.h>

#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <vector>

#include "../../../common/common_struct.h"

// #include "../../../os/os_type.h"

using namespace std;
using std::list;
using std::map;
#define INF 0x7fffffff
class Dijkstra {
  private:
    vector<vector<double>> MGraph;
    // 起始节点与目标节点最小值均为1
    int         start;
    int         end;
    vector<int> path;

  public:
    bool searchpath(int start, int end);
    Dijkstra() {}
    ~Dijkstra() {}
    void                            InitialDijkstra(vector<vector<double>> MGraph_);
    vector<int>                     GetPath();
    std::shared_ptr<spdlog::logger> threadLogger_;


    //    bool           flag;
    //    int            len;
    //    int            curNode;
    //    vector<bool>   close;
    //    vector<int>    father;
    //    vector<double> dist;
};

#endif // DIJKSTRA_H
