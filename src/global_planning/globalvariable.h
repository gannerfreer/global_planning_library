/**
 * Created Time: 2024.07.10
 * File name:    interface.h
 * Author:      yanyifeng(yanyifeng@wicri.org)
 * Brief:        规划库编译为动态库后，对外的接口
 * Include:      Class: GlobalVariable 单例类，相当于整个系统的全局变量
 * Copyright:    2024 WICRI
 */
#ifndef GLOBAL_PLANNING_GLOBALVARIABLE_H
#define GLOBAL_PLANNING_GLOBALVARIABLE_H

#include <iostream>
#include <mutex>

#include "common/common_struct.h"


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
    static int BinarySearch(const std::vector<int>& input_vec, int target);

    const void ClearData() {
        map_border_.clear();
        self_driving_referenceline_relation_.clear();
        human_driving_referenceline_relation_.clear();
        self_driving_referenceline_graph_.clear();
        self_driving_sequence_mapping_.clear();
    }

    const std::vector<_BorderPoint>& GetMapBorder() const {
        return map_border_;
    }

    void SetAllSelfDrivingReferencelines(const std::map<int, _SingleTraj>& newAllReferencelines) {
        all_self_driving_referencelines_ = newAllReferencelines;
    }
    const std::map<int, _SingleTraj>& GetAllSelfDrivingReferencelines() const {
        return all_self_driving_referencelines_;
    }

    const std::map<int, _SingleTraj>& GetAllHumanDrivingReferencelines() const {
        return all_human_driving_referencelines_;
    }
    void SetAllHumanDrivingReferencelines(const std::map<int, _SingleTraj>& newAllReferencelines) {
        all_human_driving_referencelines_ = newAllReferencelines;
    }


    int GetDispatchNums() const {
        return dispatch_nums;
    }

    const std::string& GetGlobalStr() const {
        return global_str;
    }

    // 注意：返回char* 可能会导致悬挂指针等问题，这里仅作为示例
    char* GetReceivePtr() const {
        return receive_ptr;
    }

    // 新增的 self_driving_referenceline_relation_ 的 get 和 set 方法
    const std::map<int, std::vector<int>>& GetSelfDrivingReferencelineRelation() const {
        return self_driving_referenceline_relation_;
    }
    void SetSelfDrivingReferencelineRelation(const std::map<int, std::vector<int>>& newRelation) {
        self_driving_referenceline_relation_ = newRelation;
    }

    // 新增的 human_driving_referenceline_relation_ 的 get 和 set 方法
    const std::map<int, std::vector<int>>& GetHumanDrivingReferencelineRelation() const {
        return human_driving_referenceline_relation_;
    }
    void SetHumanDrivingReferencelineRelation(const std::map<int, std::vector<int>>& newRelation) {
        human_driving_referenceline_relation_ = newRelation;
    }

    // 新增的 self_driving_referenceline_graph_ 的 get 和 set 方法
    const std::vector<std::vector<double>>& GetSelfDrivingReferencelineGraph() const {
        return self_driving_referenceline_graph_;
    }
    void SetSelfDrivingReferencelineGraph(const std::vector<std::vector<double>>& newGraph) {
        self_driving_referenceline_graph_ = newGraph;
    }


    // 新增的 self_driving_sequence_mapping_ 的 get 和 set 方法
    const std::vector<int>& GetSelfDrivingSequenceMapping() const {
        return self_driving_sequence_mapping_;
    }
    void SetSelfDrivingSequenceMapping(const std::vector<int>& newMapping) {
        self_driving_sequence_mapping_ = newMapping;
    }

    // 新增的 self_driving_sequence_mapping_ 的 get 和 set 方法
    const map<int,vector<_SingleTraj>>& GetInGuidingPaths() const {
        return in_guiding_paths_;
    }
    void SetInGuidingPaths(const map<int,vector<_SingleTraj>>& input_paths) {
        in_guiding_paths_ = input_paths;
    }

    // 新增的 self_driving_sequence_mapping_ 的 get 和 set 方法
    const map<int,vector<_SingleTraj>>& GetOutGuidingPaths() const {
        return out_guiding_paths_;
    }
    void SetOutGuidingPaths(const map<int,vector<_SingleTraj>>& output_paths) {
        out_guiding_paths_ = output_paths;
    }


    // Setters
    void SetMapBorder(const std::vector<_BorderPoint>& newMapBorder) {
        map_border_ = newMapBorder;
    }


    void SetDispatchNums(int newDispatchNums) {
        dispatch_nums = newDispatchNums;
    }

    void SetGlobalStr(const std::string& newGlobalStr) {
        global_str = newGlobalStr;
    }

    // 注意：直接设置char*可能导致内存泄漏，通常建议使用智能指针或其他内存管理策略
    // 这里仅提供示例，实际使用中应谨慎
    void SetReceivePtr(char* newReceivePtr) {
        receive_ptr = newReceivePtr;
    }


    // 全局锁
    std::shared_mutex parse_func_write_lock, record_file_write_lock, return_write_lock, assignment_operation_lock, cppad_operation_lock;

    void CreateSelfDrivingDirectedGraph(const std::map<int, std::vector<int>>& self_driving_referenceline_relation);

    void CreateSelfDrivingSequenceMapping(const std::map<int, _SingleTraj> all_self_driving_referencelines);


  private:
    std::vector<_BorderPoint>        map_border_;
    std::map<int, _SingleTraj>       all_self_driving_referencelines_;
    std::map<int, _SingleTraj>       all_human_driving_referencelines_;
    std::map<int, std::vector<int>>  self_driving_referenceline_relation_, human_driving_referenceline_relation_;
    std::vector<std::vector<double>> self_driving_referenceline_graph_;
    std::vector<int>                 self_driving_sequence_mapping_; // 序列映射关系
    int                              dispatch_nums = 0;
    std::map<int,vector<_SingleTraj>>         in_guiding_paths_, out_guiding_paths_;
    std::string                      global_str;
    char*                            receive_ptr;
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
};


#endif // GLOBAL_PLANNING_GLOBALVARIABLE_H