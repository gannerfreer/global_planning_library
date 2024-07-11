/******************************************
 > File name:       c_common.h
 > Author:          jh
 > Created Time:    2021/07/28
 > Brief:           编写并构建程序框架,完成函数功能,完善程序逻辑
 * ****************************************/
#ifndef __C_COMMON_H__
#define __C_COMMON_H__
// #include <ros/ros.h>

#include "config_header/config_io.h"
#include "easylogging++.h"

#define __filename(x) strrchr(x, '/') ? strrchr(x, '/') + 1 : x
#define formatTime()                                                 \
    ({                                                               \
        struct timespec ts;                                          \
        int             status = clock_gettime(CLOCK_REALTIME, &ts); \
        time_t          t      = ts.tv_sec + 8 * 3600;               \
        struct tm*      p;                                           \
        p = gmtime(&t);                                              \
        static char s[100];                                          \
        strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", p);              \
        sprintf(&(s[19]), ".%d", int(ts.tv_nsec / 1000000));         \
        s;                                                           \
    })
#define formatlog                                  \
    "[" << formatTime() << "]"                     \
        << "[" << ros::this_node::getName() << "]" \
        << "[" << (char*)(__filename(__FILE__)) << " " << __LINE__ << "]: "



#define FORMAT_TIME ({ \
    time_t t = time(NULL); \
    static char time_str[64] = {0}; \
    strftime(time_str, sizeof(time_str) - 1, "%H:%M:%S", localtime(&t)); \
    time_str; \
    })
#define COUT std::cout << "[" << FORMAT_TIME << " "<< (char*)(__filename(__FILE__)) << " " << __FUNCTION__ << " " << __LINE__ << "] "

#ifdef DEBUG_FLAG
#define ABORT                     \
	COUT << "abort" << std::endl; \
	abort();
#else
#define ABORT COUT << "abort" << std::endl;
#endif

#ifndef SETUP_DEFAULT_EASYLOGGINGPP
#define SETUP_DEFAULT_EASYLOGGINGPP_3(config_file, RolloutHandler, file_name) {  \
   el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);                \
   el::Configurations conf(config_file);                                         \
   conf.set(el::Level::Info, el::ConfigurationType::Filename, file_name);        \
   el::Loggers::reconfigureLogger("default", conf);                              \
   el::Helpers::installPreRollOutCallback(RolloutHandler);                       \
} 
#define SETUP_DEFAULT_EASYLOGGINGPP(config_file, RolloutHandler) {  \
   el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);   \
   el::Configurations conf(config_file);                            \
   el::Loggers::reconfigureLogger("default", conf);                 \
   el::Helpers::installPreRollOutCallback(RolloutHandler);          \
} 
#endif 

#endif