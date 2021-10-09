#include "check/validator.h"

bool ValidatorBool(const char* in, char* out, int& count)
{
    char ch;
    count = 0;

    if(out != nullptr && in != nullptr) {
        while((ch = *in++)) {
            count++;
            if(ch > 0x27 && ch < 0x3A)
                *out++ = ch;
            else
                return false;
        }
    }
    return true;
}

void ValidatorArray(char in[], char out[])
{
    if(out != nullptr && in != nullptr) {
        char ch;
        for(uint8_t i = 0, j = 0; (ch = in[i]); i++)
            if(ch > 0x27 && ch < 0x3A)
                out[j++] = ch;
    }
}

void ValidatorPoint(const char* in, char* out)
{
    char ch;
    if(out != nullptr && in != nullptr)
        while((ch = *in++))
            if(ch > 0x27 && ch < 0x3A)
                *out++ = ch;
}

void ValidatorString(const std::string& in, std::string& out)
{
    for(auto& p : in)
        if(p > 0x27 && p < 0x3A)
            out.push_back(p);
}

char* ValidatorNewArray(const char* inStr) // ???
{
    /*
    char* outStr = nullptr;
    char* t_outStr = nullptr;
    int outSize = 1;

    if(inStr != nullptr) {
        do {
            char symbol = *inStr++;
            if(symbol > 0x27 && symbol < 0x3A) {

                outStr = new char[outSize++] { 0 };
                int t_int = 0;
                while(t_outStr != nullptr && *t_outStr != '\0') {
                    *outStr++ = *t_outStr++;
                    t_int++;
                }
                delete[] t_outStr;
                t_outStr = outStr - t_int;

                *(outStr++) = symbol;
                *(outStr++) = '\0';
            }
        } while(*inStr != '\0');

        if(outStr != nullptr)
            return outStr - outSize;
        else
            return nullptr;
    } else
        return nullptr;
    */

    return nullptr;
}