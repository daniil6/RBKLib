#include <string>

bool ValidatorBool(const char* in, char* out, int& count);

void ValidatorArray(char in[], char out[]);

void ValidatorPoint(const char* in, char* out);

void ValidatorString(const std::string& in, std::string& out);

char* ValidatorNewArray(const char* inStr);