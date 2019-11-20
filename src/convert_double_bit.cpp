#include "include/convert_double_bit.h"

#include <vector>

std::string ConvertDoubleToBit(double value)
{
    std::string out;

    std::vector<uint8_t> bits;
    std::vector<uint8_t> bytes;
    uint8_t* pointDouble = (uint8_t*)&value;

    for(unsigned int i = 0; i < sizeof(value); i++)
        bytes.push_back(*pointDouble++);

    for(auto itr = bytes.rbegin(); itr != bytes.rend(); ++itr)
        for(int i = 7; i >= 0; i--)
            bits.push_back(*itr >> i & 1);

    uint8_t count = 1;
    for(auto itr = bits.begin(); itr != bits.end(); ++itr) {
        uint8_t t = *itr;
        if(t == 1)
            out.push_back('1');
        if(t == 0)
            out.push_back('0');
        if(std::distance(bits.begin(), itr) == count * 4) {
            out.push_back(' ');
            count++;
        }
    }

    return out;
}