#include <string>

void parse(char* ch, double& out, float& count, bool& divider, const char delimiter)
{
    if(*ch != '\0') {
        uint16_t tmp = *ch - '0';
        if(divider == false) {
            count /= 10;
            out += tmp * count;
        }
        if(*ch == delimiter)
            divider = false;
        parse(++ch, out, count, divider, delimiter);
        if(*ch == delimiter) {
            divider = true;
            count = 1;
        }
        if(divider == true) {
            out += tmp * count;
            count *= 10;
        }
    }
}

double ConvertCharToDouble(char* ch, const char delimiter)
{
    double out = 0;
    float count = 1;
    bool divider = true;
    if(*ch == '-') {
        parse(++ch, out, count, divider, delimiter);
        out *= -1;
    } else
        parse(ch, out, count, divider, delimiter);

    return out;
}

double ConvertStringToDouble(std::string string, const char delimiter)
{
    return ConvertCharToDouble(&string.front(), delimiter);
}
