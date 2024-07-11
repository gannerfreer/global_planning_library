#include <iostream>
#include <dlfcn.h>
#include "cpp-httplib-master/httplib.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace httplib;
// 定义全局函数指针
typedef char *(*GlobalPathPlanningFunc)(const char *);
GlobalPathPlanningFunc globalPathPlanning = nullptr;
GlobalPathPlanningFunc globalPathPlanning2 = nullptr;

typedef void (*GetMapFunc)(const char *);
GetMapFunc getMap = nullptr;
GetMapFunc getMap2 = nullptr;

int globalPathPlanning_handler(const httplib::Request &req, httplib::Response &res)
{
    cout << "进入调度接口函数" << endl;
    try
    {
        const std::string &input = req.body;
        if (!input.empty() && globalPathPlanning != nullptr)
        {
            const char *response_str = globalPathPlanning(input.c_str());
            res.set_content(response_str, "application/json");
            res.status = 200;
        }
        else
        {
            res.set_content("Missing input data or function not loaded", "text/plain");
            res.status = 400;
        }
    }
    catch (const std::exception &e)
    {
        res.set_content(e.what(), "text/plain");
        res.status = 500;
    }
    return res.status;
}

int globalPathPlanning_handler2(const httplib::Request &req, httplib::Response &res)
{
    cout << "进入编辑规划接口函数" << endl;
    try
    {
        const std::string &input = req.body;
        if (!input.empty() && globalPathPlanning2 != nullptr)
        {
            const char *response_str = globalPathPlanning2(input.c_str());
            res.set_content(response_str, "application/json");
            res.status = 200;
        }
        else
        {
            res.set_content("Missing input data or function not loaded", "text/plain");
            res.status = 400;
        }
    }
    catch (const std::exception &e)
    {
        res.set_content(e.what(), "text/plain");
        res.status = 500;
    }
    return res.status;
}




int main()
{
    cout << "welcome to server" << endl;
    const string host = "localhost";
    const string port = "8080";
    const string call_map_topic = "/call_map";
    const string bianji_map = "2";

    const std::string diaodu_map = "1";

    // 创建一个 RapidJSON 的 Document 对象，这里我们使用 Object 类型
    rapidjson::Document document;
    document.SetObject();

    // 在 Document 中添加一个名为 "value" 的字段，其值为 diaodu_map
    rapidjson::Document::AllocatorType &allocator = document.GetAllocator();
    document.AddMember("value", rapidjson::Value(diaodu_map.c_str(), allocator).Move(), allocator);

    // 创建一个 StringBuffer 来存储转换后的 JSON 字符串
    rapidjson::StringBuffer buffer;

    // 使用 Writer 将 Document 对象写入到 StringBuffer 中
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    // 获取转换后的 JSON 字符串
    std::string diaodu_map_string = buffer.GetString();

    // 创建一个 RapidJSON 的 Document 对象，这里我们使用 Object 类型
    rapidjson::Document document2;
    document2.SetObject();

    // 在 Document 中添加一个名为 "value" 的字段，其值为 bianji_map
    rapidjson::Document::AllocatorType &allocator2 = document2.GetAllocator();
    document2.AddMember("value", rapidjson::Value(bianji_map.c_str(), allocator2).Move(), allocator2);

    // 创建一个 StringBuffer 来存储转换后的 JSON 字符串
    rapidjson::StringBuffer buffer2;

    // 使用 Writer 将 Document 对象写入到 StringBuffer 中
    rapidjson::Writer<rapidjson::StringBuffer> writer2(buffer2);
    document2.Accept(writer2);

    // 获取转换后的 JSON 字符串
    std::string bianji_map_string = buffer2.GetString();

    try
    {
        void *handle = dlopen("./lib/libGlobalPlanning-diaodu.so", RTLD_NOW);
        void *handle2 = dlopen("./lib/libGlobalPlanning-bianji.so", RTLD_NOW);
        cout << "line121" << endl;
        if (!handle || !handle2)
        {
            throw std::runtime_error("Failed to load shared library: " + std::string(dlerror()));
        }

        // 加载函数
        globalPathPlanning = (GlobalPathPlanningFunc)dlsym(handle, "GlobalPathPlanning");
        getMap = (GetMapFunc)dlsym(handle, "GetMap");

        globalPathPlanning2 = (GlobalPathPlanningFunc)dlsym(handle2, "GlobalPathPlanning");
        getMap2 = (GetMapFunc)dlsym(handle2, "GetMap");

        if (!globalPathPlanning || !getMap || !globalPathPlanning2 || !getMap2)
        {
            throw std::runtime_error("Failed to load function: " + std::string(dlerror()));
        }
        cout << "line136" << endl;

        httplib::Server svr;
        svr.set_payload_max_length(50 * 1024 * 1024); // 设置请求体大小限制为30MB

        // 主动申请地图
        string input;
        Client cli(host.c_str(), stoi(port));
        if (auto res = cli.Post(call_map_topic.c_str(), diaodu_map_string, "application/json"))
        {
            if (res->status == 200)
            {
                input = res->body;
                getMap(input.c_str());
            }
            else
            {
                cout << "申请调度返回状态码异常 : " << res->status << endl;
            }
        }
        else
        {
            cout << "申请调度地图失败" << endl;
        }

        if (auto res = cli.Post(call_map_topic.c_str(), bianji_map_string, "application/json"))
        {
            if (res->status == 200)
            {
                input = res->body;
                getMap2(input.c_str());
            }
            else
            {
                cout << "申请编辑地图返回状态码异常 : " << res->status << endl;
            }
        }
        else
        {
            cout << "申请编辑地图失败" << endl;
        }

        // 设置路由和处理函数

        svr.Post("/globalPathPlanning_diaodu", globalPathPlanning_handler);

        svr.Post("/globalPathPlanning_bianji", globalPathPlanning_handler2);

        // 启动服务器，监听端口8080
        svr.listen("localhost", 8080);
        cout << "Server is running at http://localhost:8080" << endl;

        dlclose(handle);
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
