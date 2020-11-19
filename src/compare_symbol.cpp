#include "compare_symbol.h"

bool CompareSymbol(const char a[], const char b[])
{
    for(int i = 0; a[i] != '\0'; i++)
        if(a[i] != b[i])
            return false;
    return true;
}
