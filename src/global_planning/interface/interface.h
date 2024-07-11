
/**
 * Created Time: 2024.07.10
 * File name:    interface.h
 * Author:      Yanyifeng(yanyifeng@wicri.org)
 * Brief:        规划库编译为动态库后，对外的接口
 * Include:      Class: GlobalVariable 单例类，相当于整个系统的全局变量
 * Copyright:    2024 WICRI
 */
#ifndef GLOBAL_PLANNING_INTERFACE_INTERFACE_H
#define GLOBAL_PLANNING_INTERFACE_INTERFACE_H

#include <iostream>
#include <mutex>

#include "../common/common_struct.h"

using namespace GlobalPlanning;

class GlobalVariable // 单例类
{
  public:
    // 全局访问点
    static GlobalVariable* getInstance() {
        std::lock_guard<std::mutex> lock(mtx); // 加锁
        if (instance == nullptr) {
            instance = new GlobalVariable(); // 懒汉式单例创建实例
        }
        return instance;
    }

    // 以下成员变量相当于整个系统的全局变量

    vector<_BorderPoint>   map_border_;
    vector<_SingleTraj>    all_referencelines_;
    map<int, vector<int>>  referenceline_relation_;
    vector<vector<double>> referenceline_graph_;
    vector<int>            sequence_mapping_; // 序列映射关系
    int                    dispatch_nums;
    string                 global_str;
    char*                  receive_ptr;
    // 全局锁
    std::shared_mutex parse_func_write_lock, record_file_write_lock, return_write_lock, assignment_operation_lock;

    bool CreateDirectedGraph(map<int, vector<int>>& referenceline_relation_);

  private:
    // 静态成员变量，存储类的唯一实例
    static GlobalVariable* instance;
    // 静态互斥锁，用于线程安全
    static std::mutex mtx;

    // 私有构造函数，防止外部直接创建实例
    GlobalVariable() {}

    // 私有拷贝构造函数和赋值运算符，防止拷贝
    GlobalVariable(const GlobalVariable&)            = delete;
    GlobalVariable& operator=(const GlobalVariable&) = delete;

    // 基于referenceline_relation_来构建二维权重矩阵referenceline_graph_

    int BinarySearch(vector<int>& input_vec, int target);
};


#endif // GLOBAL_PLANNING_INTERFACE_INTERFACE_H