#include <stdint.h>

struct tDataTime {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;
};

long CalculateTime(uint8_t second,
    uint8_t minute,
    uint8_t hour,
    uint8_t day,
    uint8_t month,
    uint16_t year,
    uint8_t timeZone = 3);

long CalculateTime(tDataTime dataTime);