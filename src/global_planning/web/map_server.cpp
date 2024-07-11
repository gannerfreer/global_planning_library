#include <iostream>
#include <dlfcn.h>
#include "cpp-httplib-master/httplib.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace httplib;
string map_text1;
string map_text2;
// 根据接收到的req内容，分发不同版本的地图
int call_map_handler(const httplib::Request &req, httplib::Response &res)
{
    cout << "进入call_map_handler函数" << endl;
    std::string value;
    try
    {
        const std::string &input = req.body;
        cout << "line20" << endl;
        if (!input.empty())
        {
            rapidjson::Document document;
            if (document.Parse(input.c_str()).HasParseError())
            {
                cout << "map_server解析value错误" << endl;
            }
            if (document.HasMember("value") && document["value"].IsString())
            {
                cout << "line25" << endl;
                // 获取"value"字段的值
                value = document["value"].GetString();
                // 处理value
                std::cout << "Received value: " << value << std::endl;
            }
            else
            {
                std::cout << "JSON does not contain a string 'value' field" << std::endl;
            }
            if (value == "1")
            {
                cout << "发送map1" << endl;
                string response = map_text1;
                res.set_content(response, "application/json");
                res.status = 200;
            }
            else if (value == "2")
            {
                cout << "发送map2" << endl;
                string response = map_text2;
                res.set_content(response, "application/json");
                res.status = 200;
            }
            else
            {
                cout << "undefined value" << endl;
            }
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

int main()
{
    const string map1 = "map/map_lunan.json";
    const string map2 = "map/map_lunan.json";
    map_text1 = readJsonFile(map1);
    map_text2 = readJsonFile(map2);

    httplib::Server svr;
    svr.set_payload_max_length(50 * 1024 * 1024); // 设置请求体大小限制为30MB

    // 设置路由和处理函数

    svr.Post("/call_map", call_map_handler);

    // 启动服务器，监听端口8080
    svr.listen("localhost", 8080);
    cout << "Server is running at http://localhost:8080" << endl;

    return 0;
}
