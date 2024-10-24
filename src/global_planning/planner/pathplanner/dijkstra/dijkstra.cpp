#include "dijkstra.h"
// Dijkstra :: Dijkstra()
//{
// }

// Dijkstra::~Dijkstra()
//{
// }

void Dijkstra::InitialDijkstra(vector<vector<double>> MGraph_) {
    MGraph = MGraph_; // 邻接矩阵
}

vector<int> Dijkstra::GetPath() {
    vector<int> temp_path;
    for (int i = 0; i < path.size(); i++) {
        int temp = path.at(i);
        temp_path.emplace_back(temp);
    }

    return temp_path;
}

bool Dijkstra::searchpath(int start_, int end_) {
    // threadLogger_->info("dijkstra start");
    path.clear();
    if (start_ == end_) {
        path.push_back(start_);
        return true;
    }


    int    start_index = start_;
    int    end_index   = end_;
    int    len         = (int)MGraph.size();
    double min;         // 最小距离临时变量
    int    curNode = 0; // 当前结点，记录当前结点的Index

    vector<bool>   close(len);  // 加入close集时为true
    vector<double> dist(len);   // 各节点到起点的最短距离，即cost代价
    vector<int>    father(len); // 父结点

    // 初始化结点信息
    for (int v = 0; v < len; v++) {
        close.at(v)  = false;
        dist.at(v)   = 100000;
        father.at(v) = -1;
    }
    // threadLogger_->info("初始化结点信息完成");


    dist.at(start_index) = 0; // 将起始节点到起始点的最短距离设为0
    int max_loop_num     = 2999;
    // 主循环
    // threadLogger_->info("开始进入主循环");

    for (int i = 1; i <= max_loop_num; i++) {
        min = 100000;
        // 找出dist最小的点作为curNode，并根据close属性，剔除已经搜索过的区域
        for (int w = 0; w < len; w++) {
            if (!close.at(w) && dist.at(w) < min) {
                curNode = w;
                min     = dist.at(w);
            }
        }
        // threadLogger_->info("当前节点：{},min:{}", curNode, min);
        // cout<<"当前节点 "<<curNode<<endl;
        // 将curNode加入close中
        if (close.at(curNode) == true) {
            return false;
        }
        close.at(curNode) = true;
        if (curNode == end_index) {
            // threadLogger_->error("搜索到终点");
            break;
        }
        // 以curNode为基准进行拓展搜索，并更新其他节点的相关值
        bool found = false;
        for (int j = 0; j < len; j++) {
            double step = MGraph.at(curNode).at(j);
            // 如果这一步是INF，则表示curNode与j之间没有连接
            int pre_dist = dist.at(j);
            int new_dist = dist.at(curNode) + step;
            if (!close.at(j) && (new_dist < pre_dist)) {
                dist.at(j)   = new_dist;
                father.at(j) = curNode;
                found        = true;
            }
        }

        // if (found == false) {
        //     threadLogger_->error("本轮没有找到相邻的节点");
        //     return false;
        // }
        cout << "更新一轮完毕" << endl;
        // 全部点都已经close时，则退出
        bool flag = false;
        for (int jj = 0; jj < len; jj++) {
            if (!close.at(jj)) flag = true;
        }
        if (flag) {
            continue;
        }
        else {
            cout << "进入break了" << endl;
            // threadLogger_->error("进入break了");
            break;
        }

        if (i == max_loop_num) {
            threadLogger_->error("...The dijkstra search is failed...");

            return false;
        }
    }
    // 路径回溯
    int e = end_index, step = 0;
    path.push_back(e);
    while (e != start_index) {
        step++;
        if (e == -1) {
            return false;
        }
        path.push_back(father.at(e));
        e = father.at(e);
    }
    for (int i = step; i > step / 2; i--) {
        int temp          = path.at(step - i);
        path.at(step - i) = path.at(i);
        path.at(i)        = temp;
    }
    for (int i = 0; i < path.size(); i++) {
        // path.at(i) += 1;
        // threadLogger_->info("path.at(i) = {}", path.at(i));
    }

    return true;
}
