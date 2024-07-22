
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
            right = mid - 1;
        }
        else if (input_vec.at(mid) > target) {
            left = mid + 1;
        }
        else
            return mid;
    }
    return -1;
}
bool GlobalVariable::CreateDirectedGraph(const map<int, vector<int>>& referenceline_relation_) {
    // 遍历referenceline_relation_，将所有的key存入sequence_mapping_中
    int total_size = 0;
    for (const auto& pair : referenceline_relation_) {
        sequence_mapping_.at(total_size++) = pair.first;
    }
    // 预设二维权重矩阵referenceline_graph_空间，并先统统设置为0
    referenceline_graph_.resize(total_size);
    for (auto& row : referenceline_graph_) {
        row.resize(total_size, 0);
    }
    // 遍历referenceline_relation_，结合映射序列来给referenceline_graph_赋值

    int row_index = 0, col_index = 0;
    for (const auto& pair : referenceline_relation_) {
        for (int num : pair.second) {
            // 给referenceline_graph_中的每个位置赋值，col_index要根据piar.second()中的内容，结合sequence_mapping_进行反映射
            col_index = BinarySearch(sequence_mapping_, num);
            if (col_index != -1) {
                referenceline_graph_.at(row_index).at(col_index) = 1;
            }
        }
    }
}