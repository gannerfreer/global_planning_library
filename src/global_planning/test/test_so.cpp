/*
 * @Author: WuYa
 * @Date: 2023-04- 31 14:46:37
 * @LastEditors: WuYa
 * @LastEditTime: 2023-05-29 11:39:11
 * @FilePath: /GlobalPlanning/test_so.cpp
 * @Description:
 *
 * Copyright (c) 2023 by wicri All Rights Reserved.
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <dlfcn.h>

#include "include/common_struct.h"
#include "include/general_class.h"
#include "include/constants.h"

#include <thread>

// #include "global_speed_planning_test.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"

#include <hiredis/hiredis.h>

using rapidjson::Value;
using namespace GlobalPlanning;
using namespace std;
ReferenceTrajectory ret;
vehicle_param m_Veh_Param;

zones m_map_Area;
vector<Trajectory_Point> result;
char *ReadFile(char *file_path)
{
    std::ifstream ifs(file_path, std::ios::in | std::ios::binary);
    if (!ifs)
    {
        std::cout << "Failed to open file!" << file_path << std::endl;
        return nullptr;
    }
    char *buffer;
    int length = 0;
    FILE *file;
    file = fopen(file_path, "rb+");
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    buffer = new char[length + 1];
    fseek(file, 0, SEEK_SET);
    memset(buffer, 0, length + 1);
    fread(buffer, length, 1, file);

    return buffer;
}
void SaveJsonToFile(const char *jsonContent, const std::string &filename)
{
    std::ofstream outputFile(filename);
    if (outputFile.is_open())
    {
        outputFile << jsonContent;
        outputFile.close();
        std::cout << "JSON content saved to file: " << filename << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

int main()
{

    void *handle = dlopen("./lib/libGlobalPlanning-G_V1.0.0.20240702_RC.so", RTLD_NOW);
    if (!handle)
    {
        std::cerr << "Failed to load shared library: " << dlerror() << std::endl;
    }

    typedef void (*my_function_t)(char *);
    my_function_t GetMap = (my_function_t)dlsym(handle, "GetMap");
    if (!GetMap)
    {
        std::cerr << "Failed to load function: " << dlerror() << std::endl;
    }
    auto start = std::chrono::high_resolution_clock::now();
    // 读取json参数
    char *map_file = "./map/map_lunan.json";
    char *map = ReadFile(map_file);

    GetMap(map);
    cout << "line643" << endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time taken by testFunction(): " << diff.count() * 1000 << " ms\n";

    typedef void (*my_function_t2)(char *);
    my_function_t2 GlobalPathPlanning = (my_function_t2)dlsym(handle, "GlobalPathPlanning");
    if (!GlobalPathPlanning)
    {
        std::cerr << "Failed to load function: " << dlerror() << std::endl;
    }
    char *global_planning_parameters = "test_input.json";
    char *global_param = ReadFile(global_planning_parameters);

    // char *out_put = GlobalPathPlanning(global_param);
    GlobalPathPlanning(global_param);

    std::string filename = "test_so_output.json"; // 要保存的 JSON 文件名
    cout << "hello world" << endl;

    // SaveJsonToFile(out_put, filename);

    dlclose(handle);

    return 0;
}
