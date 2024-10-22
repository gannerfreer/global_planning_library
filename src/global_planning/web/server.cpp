#include <dlfcn.h>

#include <iostream>

#include "cpp-httplib-master/httplib.h"

using namespace std;
// 定义全局函数指针
typedef char* (*GlobalPathPlanningFunc)(const char*);
GlobalPathPlanningFunc globalPathPlanning = nullptr;

typedef void (*GetMapFunc)(const char*);
GetMapFunc getMap = nullptr;

typedef char* (*PoseVerificationInterfaceForHoutaiFunc)(const char*);
PoseVerificationInterfaceForHoutaiFunc PoseVerificationInterfaceForHoutai = nullptr;

int globalPathPlanning_handler(const httplib::Request& req, httplib::Response& res) {
    const std::string& input = req.body;
    if (!input.empty() && globalPathPlanning != nullptr) {
        const char* response_str = globalPathPlanning(input.c_str());
        res.set_content(response_str, "application/json");
        res.status = 200;
    }
    else {
        res.set_content("Missing input data or function not loaded", "text/plain");
        res.status = 400;
    }
    return res.status;
}

int getMap_handler(const httplib::Request& req, httplib::Response& res) {
    const std::string& input = req.body;
    if (!input.empty() && getMap != nullptr) {
        getMap(input.c_str());
        res.set_content("Map loaded successfully", "text/plain");
        res.status = 200;
    }
    else {
        res.set_content("Missing input data or function not loaded", "text/plain");
        res.status = 400;
    }
    return res.status;
}
int PoseVerificationInterfaceForHoutai_handler(const httplib::Request& req, httplib::Response& res) {
    const std::string& input = req.body;
    if (!input.empty() && PoseVerificationInterfaceForHoutai != nullptr) {
        const char* response_str = PoseVerificationInterfaceForHoutai(input.c_str());
        res.set_content(response_str, "application/json");
        res.status = 200;
    }
    else {
        res.set_content("Missing input data or function not loaded", "text/plain");
        res.status = 400;
    }
    return res.status;
}
int main() {
    void* handle         = dlopen("./lib/libGlobalPlanning.so", RTLD_NOW);
    void* another_handle = dlopen("./lib/libPoseVerification.so", RTLD_NOW);
    if (!handle || !another_handle) {
        cerr << "Failed to load shared library: " << dlerror() << endl;
    }
    else {
        // 加载函数
        globalPathPlanning                 = (GlobalPathPlanningFunc)dlsym(handle, "GlobalPathPlanning");
        getMap                             = (GetMapFunc)dlsym(handle, "GetMap");
        PoseVerificationInterfaceForHoutai = (PoseVerificationInterfaceForHoutaiFunc)dlsym(another_handle, "PoseVerificationInterfaceForHoutai");

        if (!globalPathPlanning || !getMap || !PoseVerificationInterfaceForHoutai) {
            cerr << "Failed to load function: " << dlerror() << endl;
        }
        else {
            httplib::Server svr;
            svr.set_payload_max_length(50 * 1024 * 1024); // 设置请求体大小限制为30MB
            // svr.set_max_content_length(1024 * 1024 * 50); // 设置请求体大小限制为30MB
            //  设置路由和处理函数
            svr.Post("/globalPathPlanning", globalPathPlanning_handler);
            svr.Post("/getMap", getMap_handler);
            svr.Post("/PoseVerificationInterfaceForHoutai", PoseVerificationInterfaceForHoutai_handler);
            // 启动服务器，监听端口8080
            svr.listen("0.0.0.0", 8080);
            // svr.listen("localhost", 8080);
            cout << "Server is running at http://localhost:8080" << endl;
        }

        dlclose(handle);
        dlclose(another_handle);
    }

    return 0;
}