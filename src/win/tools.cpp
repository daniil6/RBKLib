#include "win/tools.h"

#include <chrono>
#include <windows.h>

#include <iomanip>

std::string getGuid()
{
    std::string value;

    GUID guid;
    CoCreateGuid(&guid);

    RPC_CSTR str;

    UuidToStringA((UUID*)&guid, &str);

    value.append((char*)str);

    RpcStringFreeA(&str);

    return value;
}

unsigned long long toLong(const char* value) {

    unsigned long long l = 0;

    try {

        char *end_ptr = nullptr;
        l = std::strtoll(value, &end_ptr, 10);

    } catch (...) {

    }

    return l;
}

long long getTimeLong()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
        .count();
}

std::string getTimeString(long long add_time)
{
    time_t time_long = getTimeLong() + add_time;
    std::string time_string = std::to_string(time_long);
    return time_string;
}

std::string getTimeFormat(const char* time)
{
    std::string result;

    try {

        char* end_ptr = nullptr;
        unsigned long long l = std::strtoll(time, &end_ptr, 10);

        result = getTimeFormat(l / 1000);

    } catch(...) {

    }

    return result;
}

std::string getTimeFormat(const time_t& time)
{
    std::ostringstream oss;
    auto tm = *std::localtime(&time);

    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    return oss.str();
}

std::string getTimeFormatMS()
{
    CHAR sysTimeStr[25] = { 0 };
    SYSTEMTIME systemTime;
    GetLocalTime(&systemTime);
    int len = sprintf_s(sysTimeStr, "%u-%02u-%02u %u:%02u:%02u.%03u", systemTime.wYear, systemTime.wMonth,
        systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds);

    return std::string(sysTimeStr, len);
}