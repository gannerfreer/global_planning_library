#include "globalvariable.h"
// 静态成员初始化
GlobalVariable* GlobalVariable::instance = nullptr;
std::mutex      GlobalVariable::mtx;
int             GlobalVariable::BinarySearch(const vector<int>& input_vec, int target) {
    int left = 0, right = 0, mid = 0, size = 0;
    size  = input_vec.size();
    right = size - 1;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (input_vec.at(mid) < target) {
            left = mid + 1;
        }
        else if (input_vec.at(mid) > target) {
            right = mid - 1;
        }
        else
            return mid;
    }
    return -1;
}
void GlobalVariable::CreateSequenceMapping(const map<int, _SingleTraj> all_referencelines_) {
    for (const auto& pair : all_referencelines_) {
        sequence_mapping_.push_back(pair.first);
    }
    cout << "sequence_mapping_信息：" << endl;
    for (int i = 0; i < sequence_mapping_.size(); i++) {
        cout << sequence_mapping_.at(i) << endl;
    }
}
void GlobalVariable::CreateDirectedGraph(const map<int, vector<int>>& referenceline_relation_) {
    cout << "开始构建有向图" << endl;
    // 预设二维权重矩阵referenceline_graph_空间，并先统统设置为0
    referenceline_graph_.resize(sequence_mapping_.size());
    for (auto& row : referenceline_graph_) {
        row.resize(sequence_mapping_.size(), 0);
    }
    // 遍历referenceline_relation_，结合映射序列来给referenceline_graph_赋值

    int row_index = 0, col_index = 0;
    for (const auto& pair : referenceline_relation_) {
        cout << "pair.first:" << pair.first << endl;
        row_index = BinarySearch(sequence_mapping_, pair.first);
        cout << "row_index:" << row_index << endl;
        for (int num : pair.second) {
            // 给referenceline_graph_中的每个位置赋值，col_index要根据piar.second()中的内容，结合sequence_mapping_进行反映射
            cout << "num:" << num << endl;
            col_index = BinarySearch(sequence_mapping_, num);
            cout << "col_index:" << col_index << endl;
            if (col_index != -1) {
                referenceline_graph_.at(row_index).at(col_index) = 1;
            }
        }
    }
    cout << "权重矩阵如下:" << referenceline_graph_.size() << " " << referenceline_graph_.at(0).size() << endl;
    for (int i = 0; i < referenceline_graph_.size(); i++) {
        for (int j = 0; j < referenceline_graph_.at(i).size(); j++) {
            cout << referenceline_graph_.at(i).at(j) << " ";
        }
        cout << endl;
    }
}