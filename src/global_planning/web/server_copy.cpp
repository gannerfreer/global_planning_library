#include <iostream>
#include <dlfcn.h>
#include "cpp-httplib-master/httplib.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
// 定义全局函数指针
typedef char *(*GlobalPathPlanningFunc)(const char *);
GlobalPathPlanningFunc globalPathPlanning = nullptr;

typedef void (*GetMapFunc)(const char *);
GetMapFunc getMap = nullptr;

typedef char *(*PathGenerationFunc)(const char *);
PathGenerationFunc pathGeneration = nullptr;

int globalPathPlanning_handler(const httplib::Request &req, httplib::Response &res)
{
    const std::string &input = req.body;
    if (!input.empty() && globalPathPlanning != nullptr)
    {
        const char *response_str = globalPathPlanning(input.c_str());
        // 解析response_str中的JSON数据
        rapidjson::Document doc;
        doc.Parse(response_str);

        if (!doc.HasParseError())
        {
            if (doc.HasMember("ID") && doc["ID"].IsString())
            {
                std::string id = doc["ID"].GetString();

                // 获取当前时间并格式化
                std::time_t t = std::time(nullptr);
                char time_str[100];
                if (std::strftime(time_str, sizeof(time_str), "%Y-%m-%d", std::localtime(&t)))
                {
                    // 生成文件名
                    std::string filename = "http_back/" + std::string(time_str) + "-" + id + ".json";

                    // 将response_str保存到本地文件
                    std::ofstream outfile(filename);
                    if (outfile.is_open())
                    {
                        outfile << response_str;
                        outfile.close();
                        cout << "Response saved to " << filename << endl;
                    }
                    else
                    {
                        cerr << "Failed to open file for writing" << endl;
                    }
                }
                else
                {
                    cerr << "Failed to format time" << endl;
                }
            }
            else
            {
                cerr << "ID not found in the response" << endl;
            }
        }

        res.set_content(response_str, "application/json");
        res.status = 200;
    }
    else
    {
        res.set_content("Missing input data or function not loaded", "text/plain");
        res.status = 400;
    }
    return res.status;
}

int getMap_handler(const httplib::Request &req, httplib::Response &res)
{
    const std::string &input = req.body;
    if (!input.empty() && getMap != nullptr)
    {
        getMap(input.c_str());
        res.set_content("Map loaded successfully", "text/plain");
        res.status = 200;
    }
    else
    {
        res.set_content("Missing input data or function not loaded", "text/plain");
        res.status = 400;
    }
    return res.status;
}

int pathGeneration_handler(const httplib::Request &req, httplib::Response &res)
{
    const std::string &input = req.body;
    if (!input.empty() && pathGeneration != nullptr)
    {
        const char *response_str = pathGeneration(input.c_str());
        res.set_content(response_str, "application/json");
        res.status = 200;
    }
    else
    {
        res.set_content("Missing input data or function not loaded", "text/plain");
        res.status = 400;
    }
    return res.status;
}

int main()
{
    void *handle = dlopen("./lib/libGlobalPlanning.so", RTLD_NOW);
    void *handle1 = dlopen("./lib/libPathGeneration.so", RTLD_NOW);
    if (!handle)
    {
        cerr << "Failed to load libGlobalPlanning.so library: " << dlerror() << endl;
    }
    else if (!handle1)
    {
        cerr << "Failed to load libPathGeneration.so library: " << dlerror() << endl;
    }
    else
    {
        // 加载函数
        globalPathPlanning = (GlobalPathPlanningFunc)dlsym(handle, "GlobalPathPlanning");
        getMap = (GetMapFunc)dlsym(handle, "GetMap");
        pathGeneration = (GlobalPathPlanningFunc)dlsym(handle, "PathEditInterfaceForHoutai");

        if (!globalPathPlanning || !getMap || !pathGeneration)
        {
            cerr << "Failed to load function: " << dlerror() << endl;
        }
        else
        {
            httplib::Server svr;
            svr.set_payload_max_length(50 * 1024 * 1024); // 设置请求体大小限制为30MB
            // svr.set_max_content_length(1024 * 1024 * 50); // 设置请求体大小限制为30MB
            //  设置路由和处理函数
            svr.Post("/globalPathPlanning", globalPathPlanning_handler);
            svr.Post("/getMap", getMap_handler);
            svr.Post("/pathGeneration", pathGeneration_handler);
            // 启动服务器，监听端口8080
            svr.listen("0.0.0.0", 8080);
            // svr.listen("localhost", 8080);
            cout << "Server is running at http://localhost:8080" << endl;
        }

        dlclose(handle);
    }

    return 0;
}