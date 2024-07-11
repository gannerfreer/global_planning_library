#include "cpp-httplib-master/httplib.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string readFileContents(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [1 for GetMap | 2 for GlobalPathPlanning]" << std::endl;
        return 1;
    }

    httplib::Client cli("http://localhost:8080");
    int option = std::atoi(argv[1]);

    switch (option) {
        case 1: {
            std::string mapJson = readFileContents("./map/map_lunan_1m.json");
            std::cout << "Size of mapJson: " << mapJson.size() << " bytes" << std::endl;
            auto res = cli.Post("/getMap", mapJson, "application/json");
            if (res && res->status == 200) {
                std::cout << "GetMap response: " << res->body << std::endl;
            } else {
                std::cerr << "Error or no response from GetMap: " << (res ? std::to_string(res->status) : "Connection failed") << std::endl;
            }
            break;
        }
        case 2: {
            std::string planningJson = readFileContents("test_input_lunan.json");
            std::cout << "Size of planningJson: " << planningJson.size() << " bytes" << std::endl;
            auto res = cli.Post("/globalPathPlanning", planningJson, "application/json");
            if (res && res->status == 200) {
                std::cout << "GlobalPathPlanning response: " << res->body << std::endl;
            } else {
                std::cerr << "Error or no response from GlobalPathPlanning: " << (res ? std::to_string(res->status) : "Connection failed") << std::endl;
            }
            break;
        }
        default:
            std::cerr << "Invalid option. Use 1 for GetMap or 2 for GlobalPathPlanning." << std::endl;
            return 1;
    }

    return 0;
}