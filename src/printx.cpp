#include <cstdio>

void printx(const char* data, int size)
{
    for(int i = 0; i < size; i++)
        printf("0x%02X,", data[0]);
    printf("\n");
}
