#include <string>

// Link RPCRT4.dll

std::string getGuid();

unsigned long long toLong(const char* value);

long long getTimeLong();

std::string getTimeString(long long add_time = 0);

std::string getTimeFormatMS();

std::string getTimeFormat(const time_t& time);

std::string getTimeFormat(const char* time);