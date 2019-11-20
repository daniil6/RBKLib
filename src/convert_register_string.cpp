#include <iostream>

const uint8_t sizeAlphabetEng = 26;
const uint8_t sizeAlphabetRus = 33;

const char upperEng[sizeAlphabetEng] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

const char lowerEng[sizeAlphabetEng] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

// const char16_t lowerRus[sizeAlphabetRus] = { "а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м",
// "н",
//    "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я" };
//
// const char16_t upperRus[sizeAlphabetRus] = { "А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И", "Й", "К", "Л", "М",
// "Н",
//    "О", "П", "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я" };

std::string ConvertRegisterString(std::string strIn)
{
    std::string strOut;
    if(strIn.empty() == false) {
        for(auto& p : strIn) {
            bool find = false;
            for(int i = 0; i < sizeAlphabetEng; i++) {
                if(p == lowerEng[i]) {
                    strOut.push_back(upperEng[i]);
                    find = true;
                }
            }

            if(find == false)
                strOut.push_back(p);
        }
    }
    return strOut;
}