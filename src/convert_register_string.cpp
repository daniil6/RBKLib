#include "convert_register_string.h"

const uint8_t sizeAlphabetEng = 26;
const uint8_t sizeAlphabetRus = 33;
const uint8_t size = sizeAlphabetEng + sizeAlphabetRus;

const unsigned char lower[size] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
    'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xf1, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa,
    0xab, 0xac, 0xad, 0xae, 0xaf, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed,
    0xee, 0xef };

const unsigned char upper[size] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
    'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0xf0, 0x86, 0x87, 0x88, 0x89, 0x8a,
    0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d,
    0x9e, 0x9f };

std::string ConvertRegisterString(std::string strIn, char* mode)
{
    const unsigned char* compare_1 = nullptr;
    const unsigned char* compare_2 = nullptr;

    if(mode != nullptr && *mode == 'l') {
        compare_1 = &lower[0];
        compare_2 = &upper[0];
    } else {
        compare_1 = &upper[0];
        compare_2 = &lower[0];
    }

    std::string strOut;
    if(strIn.empty() == false) {
        for(unsigned char p : strIn) {
            bool find = false;
            for(int i = 0; i < size; i++) {
                if(p == compare_1[i]) {
                    strOut.push_back(compare_2[i]);
                    find = true;
                }
            }

            if(find == false)
                strOut.push_back(p);
        }
    }
    return strOut;
}