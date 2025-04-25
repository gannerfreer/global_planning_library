#include "globalvariable.h"
// 静态成员初始化
GlobalVariable* GlobalVariable::instance = nullptr;
std::mutex      GlobalVariable::mtx;

int GlobalVariable::BinarySearch(const std::vector<int>& input_vec, int target) {
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


void GlobalVariable::CreateSelfDrivingSequenceMapping(const std::map<int, _SingleTraj> all_self_driving_referencelines_) {
    for (const auto& pair : all_self_driving_referencelines_) {
        self_driving_sequence_mapping_.push_back(pair.first);
    }
    std::cout << "self_driving_sequence_mapping_信息：" << std::endl;
    for (int i = 0; i < self_driving_sequence_mapping_.size(); i++) {
        std::cout << self_driving_sequence_mapping_.at(i) << " ";
    }
    std::cout << std::endl;
}


void GlobalVariable::CreateSelfDrivingDirectedGraph(const std::map<int, std::vector<int>>& self_driving_referenceline_relation_) {
    std::cout << "开始构建无人有向图" << std::endl;
    // 预设二维权重矩阵self_driving_referenceline_graph_空间，并先统统设置为0
    self_driving_referenceline_graph_.resize(self_driving_sequence_mapping_.size());
    for (auto& row : self_driving_referenceline_graph_) {
        row.resize(self_driving_sequence_mapping_.size(), 100000000);
    }
    // 遍历self_driving_referenceline_relation_，结合映射序列来给self_driving_referenceline_graph_赋值

    int row_index = 0, col_index = 0;
    for (const auto& pair : self_driving_referenceline_relation_) {
        row_index = BinarySearch(self_driving_sequence_mapping_, pair.first);
        for (int num : pair.second) {
            col_index = BinarySearch(self_driving_sequence_mapping_, num);
            if (col_index != -1) {
                self_driving_referenceline_graph_.at(row_index).at(col_index) = 1;
            }
        }
    }
    std::cout << "无人权重矩阵如下:" << self_driving_referenceline_graph_.size() << " " << self_driving_referenceline_graph_.at(0).size() << std::endl;
    for (int i = 0; i < self_driving_referenceline_graph_.size(); i++) {
        for (int j = 0; j < self_driving_referenceline_graph_.at(i).size(); j++) {
            std::cout << self_driving_referenceline_graph_.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}
