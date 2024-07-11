/*******************************************************************/
/*                      Author: qxh                                */
/*                     Contact: qxh880507@163.com                  */
/*                 Last update: 2019-07-12                         */
/*******************************************************************/

/*
  Description: The cpp file for C++ class Config.
  The class reads config files and returns variables in given data types.
  Usage: Please refer to the header file.
*/


#include "config_io.h"

#include <unistd.h> // To use: access.

#include <fstream>  // To use: open, is_open, close.
#include <iostream> // To use: cout, endl.
#include <string>   // To use: string.

namespace hivelab_config_io {

std::shared_ptr<Config> Config::ptr_ = nullptr; // Set ptr_ to nullptr during compiling process.

Config::Config() {}

Config::~Config() {
    if (file_->is_open()) file_->close();
    delete file_;
}

bool Config::SetConfigPath(const std::string& _file_name, std::string _seperator, int _max_file_len) {
    if (ptr_ == nullptr)                            // If this is the 1st time we call this func.
        ptr_ = std::shared_ptr<Config>(new Config); // Construct a new class obj.

    ptr_->kSeperator_ = _seperator;    // Assign seperator. Default: "=".
    ptr_->kMaxFileLen = _max_file_len; // Max num of config file lines. Default: 1000.

    ptr_->file_ = new std::fstream;
    ptr_->file_->open(_file_name.c_str()); // By default, the file mode is: read | write.
    if (!ptr_->file_->is_open()) {
        ptr_->PrintErrInfo("Config file " + _file_name + " open failed!");
        return false;
    }

    ReadConfigFile();

    return true; // File opened correctly.
}


bool Config::ReadConfigFile() {
    if (!ptr_->file_->is_open()) // Double check if the file is open.
        return false;

    std::string tmp_file_line;
    std::string tmp_curr_field_name;
    for (int i = 0; std::getline(*(ptr_->file_), tmp_file_line) && i < ptr_->kMaxFileLen; i++) {
        switch (ParseTrimLine(tmp_file_line, *(ptr_->file_))) {
            case 1: // For field name.
                tmp_curr_field_name.assign(tmp_file_line);
                if (ptr_->config_strs_.find(tmp_curr_field_name) == ptr_->config_strs_.end()) {
                    ConfigField tmp_field;
                    ptr_->config_strs_[tmp_curr_field_name] = tmp_field;
                }
                break;

            case 2: // For field data.
                RecordConfigLine(tmp_file_line, ptr_->config_strs_[tmp_curr_field_name]);
                break;

            default:
                break;
        }
    }

    int tmp_line_cnt = 0;
    for (auto iter : ptr_->config_strs_) tmp_line_cnt += iter.second.size();
    ptr_->PrintInfo(std::to_string(ptr_->config_strs_.size()) + " cfg fields");
    ptr_->PrintInfo(std::to_string(tmp_line_cnt) + " cfg contents");
    return true;
}

/**
 * @brief Config::RecordConfigLine 获取行文本键值对
 * @param _line
 * @param _field
 */
void Config::RecordConfigLine(const std::string& _line, Config::ConfigField& _field) {
    const std::string& kSep           = ptr_->kSeperator_;
    std::string        tmp_field_name = _line.substr(0, _line.find(kSep));

    if (_field.find(tmp_field_name) != _field.end())
        ptr_->PrintWarnInfo("Duplicated names! The last one will be read!");

    _field[tmp_field_name].data_.assign(_line.substr(_line.find(kSep) + 1, _line.size() - _line.find(kSep) - 1));
}


/**
 * @brief Config::ParseTrimLine 分析裁剪行文本
 * @param _file_line
 * @param _file
 * @return 1:域配置名 2:
 */
int Config::ParseTrimLine(std::string& _file_line, std::fstream& _file) {
    const std::string& kSep = ptr_->kSeperator_;
    std::string        tmp_str(_file_line);

    ptr_->TrimSpacingComment(tmp_str); // Trim spacings and comments.

    if (tmp_str.find("[") == 0 && tmp_str.find("]") == tmp_str.size() - 1) // Check field title syntax.
    {
        _file_line.assign(tmp_str.substr(1, tmp_str.size() - 2)); // Copy field title.
        return 1;
    }
    else if (tmp_str.find(kSep) != tmp_str.size() - 1 && tmp_str.find(kSep) != std::string::npos &&
             tmp_str.find(kSep) != 0) {
        if (tmp_str.find(kSep + "{") == std::string::npos) // Normal config read.
        {
            _file_line.assign(tmp_str);
        }
        else // For vectors.
        {
            std::string tmp_str_line;
            if (tmp_str.find("}") == std::string::npos) // If the vector possesses multiple lines.
            {
                while (std::getline(*(ptr_->file_), tmp_str_line)) {
                    ptr_->TrimSpacingComment(tmp_str_line);
                    tmp_str += tmp_str_line.c_str();
                    if (tmp_str_line.find("}") != std::string::npos) // The end of the vector.
                        break;
                }
            }
            _file_line.assign(tmp_str);
        }
        return 2;
    }

    return 0;
}


void Config::TrimSpacingComment(std::string& _str) // 删掉从"空"和"#"开始到字符串结尾的字符
{
    while (_str.find(" ") != std::string::npos) // Trim all the spacings.
        _str.erase(_str.find(" "), 1);

    if (_str.find("#") != std::string::npos) // Trim comments.
        _str.erase(_str.find("#"));
}

void Config::PrintInfo(std::string _str) {
    std::cout << "\033[35m"
              << "cfg info: \033[0m" << _str << std::endl;
}


void Config::PrintErrInfo(std::string _str) {
    std::cerr << "\033[31m"
              << " cfg error: " << _str << "\033[0m" << std::endl;
}


void Config::PrintWarnInfo(std::string _str) {
    std::cerr << "\033[33m"
              << "cfg warn: " << _str << "\033[0m" << std::endl;
}


void Config::UseDefaultPath(std::string _file_name) {
    const std::string kRosLaunchPath = "../../../src/config/" + _file_name;
    const std::string kRosRunPath    = "./src/config/" + _file_name;

    std::string tmp_path_str = kRosRunPath;
    if (access(tmp_path_str.c_str(), R_OK) == -1) {
        tmp_path_str.assign(kRosLaunchPath);
    }

    if (access(tmp_path_str.c_str(), R_OK) == -1) {
        ptr_->PrintErrInfo("cfg default path error. Did you set cwd = \"node\" in launch file?");
        exit(1);
    }

    ptr_->PrintInfo("path: " + tmp_path_str);
    SetConfigPath(tmp_path_str);
}


} // namespace hivelab_config_io
