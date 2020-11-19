#include <cstdint>
#include <stack>

bool BracketsStack(const char* inStr, uint8_t& count)
{
    std::stack<char> brackets;
    count = 0;

    if(inStr != nullptr) {
        do {
            count++;
            char symbol = *inStr++;

            if(symbol == '(')
                brackets.push('O');

            if(symbol == ')') {
                if(brackets.empty() == false)
                    brackets.pop();
                else
                    return false;
            }

        } while(*inStr != '\0');

    } else
        return false;

    if(brackets.empty() == true)
        return true;
    else
        return false;
}

bool BracketsBool(const char* in, int& count)
{
    uint64_t result = 1;
    count = 0;

    if(in != nullptr) {
        while(*in != '\0') {
            count++;
            if(*in == '(')
                result <<= 1;
            if(*in++ == ')')
                result >>= 1;
            if(result == 0)
                return false;
        }
    }

    if(result == 1)
        return true;
    else
        return false;
}

bool BracketsCount(const char* in, int& countError)
{
    int counter = 0;
    countError = 0;

    if(in != nullptr) {
        while(*in != '\0') {
            countError++;
            if(*in == '(') {
                counter++;
            } else {
                if(*in == ')')
                    counter--;
                if(counter < 0)
                    return false;
            }
            in++;
        }
    }

    if(counter == 0)
        return true;
    else
        return false;
}