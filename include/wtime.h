#include <stdint.h>

struct tDataTime {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;

    //tDataTime()
    //{
    //    second = 0;
    //    minute = 0;
    //    hour = 0;
    //    day = 1;
    //    month = 1;
    //    year = 2020;
    //}
};

long CalculateTime(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t month, uint16_t year);

long CalculateTime(tDataTime dataTime);