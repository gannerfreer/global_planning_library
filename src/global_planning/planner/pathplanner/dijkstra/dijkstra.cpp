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
    threadLogger_->info("即将调用disktra算法判断节点 {}->{} 是否连通", start_, end_);
    cout << "即将调用disktra算法判断节点" << start_ << "->" << end_ << "是否连通" << endl;
    path.clear();
    if (start_ == end_) {
        cout << start_ << "=" << end_ << " 判定连通" << endl;
        path.push_back(start_);
        return true;
    }


    int start_index = start_;
    int end_index   = end_;
    int len         = (int)MGraph.size();
    cout << "MGraph大小：" << len << endl;
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
    // cout << "初始化结点信息完成" << endl;
    // threadLogger_->info("初始化结点信息完成");
    if (start_index >= 0 && start_index < len) {
        dist.at(start_index) = 0; // 将起始节点到起始点的最短距离设为0
    }
    else {
        cout << "传入的节点异常  " << start_index << endl;
        threadLogger_->info("传入的节点异常 {}", start_index);
        return false;
    }

    int max_loop_num = 2999;
    // threadLogger_->info("开始进入主循环");
    // cout << "开始进入主循环  " << endl;
    for (int i = 1; i <= max_loop_num; i++) {
        min = 100000;
        // 找出dist最小的点作为curNode，并根据close属性，剔除已经搜索过的区域
        for (int w = 0; w < len; w++) {
            if (!close.at(w) && dist.at(w) < min) {
                curNode = w;
                min     = dist.at(w);
            }
        }
        // threadLogger_->info("当前节点：{}, min:{}", curNode, min);
        // cout << "当前节点 " << curNode << endl;
        // 将curNode加入close中
        if (close.at(curNode) == true) {
            cout << "终点节点不可达 " << endl;
            return false;
        }
        close.at(curNode) = true;
        if (curNode == end_index) {
            // threadLogger_->info("搜索到终点");
            // cout << "搜索到终点 " << endl;
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
            cout << "...The dijkstra search is failed... " << endl;
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
        if (step - i >= 0 && step - i < path.size() && i >= 0 && i < path.size()) {
            int temp          = path.at(step - i);
            path.at(step - i) = path.at(i);
            path.at(i)        = temp;
        }
        else {
            cout << "路径回溯失败 " << endl;
            return false;
        }
    }
    for (int i = 0; i < path.size(); i++) {
        // path.at(i) += 1;
        // threadLogger_->info("path.at(i) = {}", path.at(i));
    }

    return true;
}
