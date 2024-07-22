#ifndef TIME_HELPER_H
#define TIME_HELPER_H

// #include "../os/os.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

namespace utility {
class CTimeClock {
  public:
    CTimeClock(std::chrono::system_clock::time_point time = std::chrono::system_clock::now()) {
        clock_ = time;
    }
    // 获取老时间time_t
    long long ToTimet() {
        return std::chrono::system_clock::to_time_t(clock_);
    }
    long long ToMTimet() {
        auto tp  = std::chrono::time_point_cast<std::chrono::milliseconds>(clock_);
        auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
        return tmp.count();
    }
    string ToString() {
        char       tmp[100] = {0};
        time_t     ts       = ToTimet();
        struct tm* area     = localtime(&ts);
        sprintf(tmp, "%04d-%02d-%02d %02d:%02d:%02d", area->tm_year + 1900, area->tm_mon + 1, area->tm_mday,
                area->tm_hour, area->tm_min, area->tm_sec);
        return tmp;
    }
    string ToString2() {
        char       tmp[100] = {0};
        time_t     ts       = ToTimet();
        struct tm* area     = localtime(&ts);
        sprintf(tmp, "%04d-%02d-%02d~%02d:%02d:%02d", area->tm_year + 1900, area->tm_mon + 1, area->tm_mday,
                area->tm_hour, area->tm_min, area->tm_sec);
        return tmp;
    }
    CTimeClock& operator+=(long long ms) {
        clock_ += std::chrono::milliseconds(ms);
        return *this;
    }

  public:
    std::chrono::system_clock::time_point clock_;
};

class CTimeHelper {
  public:
    static long long GetTimeIntervalSeconds(CTimeClock clock_begin, CTimeClock clock_end = CTimeClock()) {
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(clock_end.clock_ - clock_begin.clock_);
        return duration.count();
    }
    static long long GetTimeIntervalMilliseconds(CTimeClock clock_begin, CTimeClock clock_end = CTimeClock()) {
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(clock_end.clock_ - clock_begin.clock_);
        return duration.count();
    }
    static long long GetTimeIntervalMicroseconds(CTimeClock clock_begin, CTimeClock clock_end = CTimeClock()) {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(clock_end.clock_ - clock_begin.clock_);
        return duration.count();
    }
    static long long GetNowTimes() {
        CTimeClock now;
        return now.ToTimet();
    }
    static long long GetNowTimeMs() {
        CTimeClock now;
        return now.ToMTimet();
    }
    static string GetTimeString(time_t ts = 0) {
        char tmp[100] = {0};
        if (ts <= 0) ts = time(nullptr);
        struct tm* area = localtime(&ts);
        sprintf(tmp, "%d-%d-%d %d:%d:%d", area->tm_year + 1900, area->tm_mon + 1, area->tm_mday, area->tm_hour,
                area->tm_min, area->tm_sec);
        return tmp;
    }
};


class CTimeLog {
  public:
    CTimeLog(std::string str = "时间测试") {
        str_log_ = str + ":\r\n";
    }
    ~CTimeLog() {
        if (!flag_) {
            cout << GetLog() << endl;
        }
    }
    std::string GetLog() {
        flag_ = true;
        return str_log_;
    }
    void AddLog(std::string str) {
        CTimeClock now;
        long long  t1         = CTimeHelper::GetTimeIntervalMicroseconds(begin_, now);
        long long  t2         = CTimeHelper::GetTimeIntervalMicroseconds(cur_, now);
        double     d1         = static_cast<double>(t1) / 1000.0;
        double     d2         = static_cast<double>(t2) / 1000.0;
        char       buf[10240] = {0};
        if (str.length() > 10000) {
            str = "";
        }
        sprintf(buf, "%s;耗时:%.3f ms;总耗时:%.3f ms.\r\n", str.c_str(), d2, d1);
        str_log_ += buf;
        cur_ = now;
    }

  protected:
    CTimeClock  begin_;
    CTimeClock  cur_;
    std::string str_log_;
    bool        flag_ = false;
};

class CTimeCounter {
  public:
    CTimeCounter() {}
    ~CTimeCounter() {
        cout << str_header_ << "\tcounter:" << to_string(counter_) << "\tusing_time:" << to_string(using_time_ / 1000.0)
             << "ms\tarvage_time:" << to_string(using_time_ / 1000.0 / counter_) << "ms" << endl;
    }
    void SetHeader(string str_header) {
        str_header_ = str_header;
    }
    void AddCounter() {
        ++counter_;
    }
    void AddUsingTime(long long using_time) {
        using_time_ += using_time;
    }
    unsigned int GetCounter() {
        return counter_;
    }
    long long GetUsingTime() {
        return using_time_;
    }

  protected:
    string       str_header_ = "CTimeCounter";
    unsigned int counter_    = 0;
    long long    using_time_ = 0;
};

class CTimeCounterTool {
  public:
    CTimeCounterTool(CTimeCounter* time_counter_p) {
        if (time_counter_p) {
            begin_          = CTimeClock();
            time_counter_p_ = time_counter_p;
            time_counter_p->AddCounter();
        }
    }
    ~CTimeCounterTool() {
        if (time_counter_p_) {
            CTimeClock now;
            long long  t1 = CTimeHelper::GetTimeIntervalMicroseconds(begin_, now);
            time_counter_p_->AddUsingTime(t1);
        }
    }

  protected:
    CTimeClock    begin_;
    CTimeCounter* time_counter_p_ = nullptr;
};
} // namespace utility
#endif // TIME_HELPER_H
