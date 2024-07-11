#include <fstream>
#include <sstream>
#include <vector>
#include "cpp-httplib-master/httplib.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace httplib;

// 读取本地JSON文件的函数
string readJsonFile(const string &filepath)
{
    ifstream file(filepath);
    if (!file.is_open())
    {
        throw runtime_error("Could not open file: " + filepath);
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// 发送POST请求的函数
void sendPostRequest(const string &host, const string &port, const string &target, const string &json)
{
    Client cli(host.c_str(), stoi(port));
    if (auto res = cli.Post(target.c_str(), json, "application/json"))
    {
        if (res->status == 200)
        {
            // cout << "Response: " << res->body << endl;
        }
        else
        {
            cout << "Error in : " << res->status << endl;
        }
    }
    else
    {
        cout << "Error: " << res.error() << endl;
    }
}


int main()
{
    const string host = "localhost";
    const string port = "8080";
    const string targetGlobalPathPlanning = "/globalPathPlanning_diaodu";
    const string targetGetMap = "/getMap_diaodu";
    const string targetGlobalPathPlanning2 = "/globalPathPlanning_bianji";
    const string targetGetMap2 = "/getMap_bianji";
    const string jsonFilePath = "map/map_lunan.json";       // 你的JSON文件路径
    const string jsonFilePath1 = "./test_input.json"; // 你的JSON文件路径
    try
    {
        // // 读取JSON内容
        // string jsonContent = readJsonFile(jsonFilePath);
        string jsonContent1 = readJsonFile(jsonFilePath1);

        // // 首先，单独调用getMap方法
        // sendPostRequest(host, port, targetGetMap, jsonContent);
        // sendPostRequest(host, port, targetGetMap2, jsonContent);
        // 创建一个10秒的持续时间
        std::chrono::seconds duration(10);

        // 使用std::this_thread::sleep_for进行延时
        std::this_thread::sleep_for(duration);
        std::chrono::seconds duration1(5);
        while (1)
        {
            sendPostRequest(host, port, targetGlobalPathPlanning, jsonContent1);
            // 使用std::this_thread::sleep_for进行延时
            // std::this_thread::sleep_for(duration1);
            sendPostRequest(host, port, targetGlobalPathPlanning2, jsonContent1);
            // std::this_thread::sleep_for(duration1);
        }

        // // 定义线程数量
        // const int numThreads = 10; // 你希望执行的线程数
        // vector<thread> threads;

        // // 启动多个线程进行压力测试
        // for (int i = 0; i < numThreads; ++i) {
        //     threads.push_back(thread(sendPostRequest, host, port, targetGlobalPathPlanning, jsonContent1));
        // }

        // // 等待所有线程完成
        // for (auto& t : threads) {
        //     t.join();
        // }
    }
    catch (const exception &e)
    {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }

    return 0;
}
