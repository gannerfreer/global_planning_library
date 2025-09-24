// #include <fstream>
// #include <iostream>
// #include <chrono>
// #include <dlfcn.h>
// #include <string.h>
// #include <vector>

// // Function to read file content into a std::string
// std::string ReadFileContent(const std::string& file_path)
// {
//     std::ifstream ifs(file_path, std::ios::in | std::ios::binary);
//     if (!ifs.is_open()) { // Check if the file was opened successfully
//         std::cerr << "Failed to open file: " << file_path << std::endl;
//         return ""; // Return empty string on failure
//     }

//     // Read the entire file content into a stringstream, then convert to string
//     std::string content((std::istreambuf_iterator<char>(ifs)),
//                          std::istreambuf_iterator<char>());
//     return content;
// }
// //
// void SaveJsonToFile(const char* jsonContent, const std::string& filename) {
//     std::ofstream outputFile(filename);
//     if (outputFile.is_open()) {
//         outputFile << jsonContent;
//         outputFile.close();
//         std::cout << "JSON content saved to file: " << filename << std::endl;
//     } else {
//         std::cerr << "Unable to open file for writing: " << filename << std::endl;
//     }
// }
// int main() {
//     void* handle = dlopen("../lib/libconflictsolve.so", RTLD_NOW);
//     if (!handle) {
//         std::cerr << "Failed to load shared library: " << dlerror() << std::endl;
//     }

//     typedef char* (*ConflictSolve_T)(const char*);
//     ConflictSolve_T ConflictSolve_func = (ConflictSolve_T)dlsym(handle, "ConflictSolve");
//     if (!ConflictSolve_func) {
//         std::cerr << "Failed to load function: " << dlerror() << std::endl;
//     }
//     auto start = std::chrono::high_resolution_clock::now();
//     // 读取json参数
//     std::string test_file = "./vehicle_info.json";
//     std::string vehicle_info_str      = ReadFileContent(test_file);
//     std::vector<char> vehicle_info_char_buffer(vehicle_info_str.begin(), vehicle_info_str.end());
//     vehicle_info_char_buffer.push_back('\0'); // Null-terminate

//     char* wait_command  = ConflictSolve_func(vehicle_info_char_buffer.data());

//     auto                          end  = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> diff = end - start;
//     std::cout << "Time taken by testFunction(): " << diff.count() * 1000 << " ms\n";

//     std::string filename = "test_so_output.json"; // 要保存的 JSON 文件名

//     SaveJsonToFile(wait_command, filename);

//     dlclose(handle);

//     return 0;
// }

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
#include <dlfcn.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>

#include "../common/common_struct.h"

// #include "global_speed_planning_test.h"


#include "../third_lib/rapidjson/document.h"
#include "../third_lib/rapidjson/filereadstream.h"
#include "../third_lib/rapidjson/filewritestream.h"
#include "../third_lib/rapidjson/prettywriter.h"
#include "../third_lib/rapidjson/writer.h"
using rapidjson::Value;
using namespace GlobalPlanning;
using namespace std;

char* ReadFile(char* file_path) {
    std::ifstream ifs(file_path, std::ios::in | std::ios::binary);
    if (!ifs) {
        std::cout << "Failed to open file!" << file_path << std::endl;
        return nullptr;
    }
    char* buffer;
    int   length = 0;
    FILE* file;
    file = fopen(file_path, "rb+");
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    buffer = new char[length + 1];
    fseek(file, 0, SEEK_SET);
    memset(buffer, 0, length + 1);
    fread(buffer, length, 1, file);

    return buffer;
}
void SaveJsonToFile(const char* jsonContent, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << jsonContent;
        outputFile.close();
        std::cout << "JSON content saved to file: " << filename << std::endl;
    }
    else {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

int main() {
    void* handle = dlopen("../lib/libGlobalPlanning.so", RTLD_NOW);
    if (!handle) {
        std::cerr << "Failed to load shared library: " << dlerror() << std::endl;
    }

    typedef bool (*my_function_t)(char*);
    my_function_t GetMap = (my_function_t)dlsym(handle, "GetMap");
    if (!GetMap) {
        std::cerr << "Failed to load function: " << dlerror() << std::endl;
    }
    auto start = std::chrono::high_resolution_clock::now();
    // 读取json参数
    char* map_file = "../map/map.json";
    char* map      = ReadFile(map_file);

    GetMap(map);
    
    auto                          end  = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time taken by testFunction(): " << diff.count() * 1000 << " ms\n";

    typedef char* (*my_function_t2)(char*);
    my_function_t2 GlobalPathPlanning = (my_function_t2)dlsym(handle, "GlobalPathPlanning");
    if (!GlobalPathPlanning) {
        std::cerr << "Failed to load function: " << dlerror() << std::endl;
    }

    typedef char* (*my_function_t3)(char*);
    my_function_t3 HumanVehPredicting = (my_function_t3)dlsym(handle, "PathPredicting");
    if (!HumanVehPredicting) {
        std::cerr << "Failed to load function: " << dlerror() << std::endl;
    }

    typedef char* (*my_function_t4)(char*);
    my_function_t4 QueuePointGenerator = (my_function_t4)dlsym(handle, "QueuePointGenerator");
    if (!QueuePointGenerator) {
        std::cerr << "Failed to load function: " << dlerror() << std::endl;
    }


    char* global_planning_parameters              = "test_input.json";
    char* global_param                            = ReadFile(global_planning_parameters);
    char* human_veh_parameters                    = "human_test_input.json";
    char* human_veh_param                         = ReadFile(human_veh_parameters);
    char* load_waitting_point_auto_gen_parameters = "load_area_planning_input.json";
    char* load_waitting_point_auto_gen_param      = ReadFile(load_waitting_point_auto_gen_parameters);

    // char *out_put = GlobalPathPlanning(global_param);
    // GlobalPathPlanning(global_param);
    // char *out_put=HumanVehPredicting(human_veh_param);
    // cout << "即将调用LoadAreaPlanning接口" << endl;
    char* out_put = QueuePointGenerator(load_waitting_point_auto_gen_param);
    // cout << "调用LoadAreaPlanning接口成功" << endl;

    std::string filename = "load_area_planning_output.json"; // 要保存的 JSON 文件名
    cout << "hello world" << endl;

    SaveJsonToFile(out_put, filename);

    dlclose(handle);

    return 0;
}
