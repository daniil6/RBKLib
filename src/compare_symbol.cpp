#include "compare_symbol.h"

bool CompareSymbol(const char a[], const char b[])
{
    for(int i = 0; a[i] != '\0'; i++)
        if(a[i] != b[i])
            return false;
    return true;
}

int compare(const char* a, const int& aSize, const char* b, const int& bSize)
{
    int min = aSize < bSize ? aSize : bSize;
    int max = aSize > bSize ? aSize : bSize;

    for(int i = 0; i < min; i++)
        if(a[i] != b[i])
            return i;

    for(int i = min; i < max; i++)
        return min;

    return -1;
}