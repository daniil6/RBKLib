#include <stack>

bool Brackets(const char* inStr)
{
    std::stack<char> brackets;

    if(inStr != nullptr) {
        do {
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