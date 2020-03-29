#include <stdint.h>

struct tDateTime {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;
};

tDateTime convertSecToDateTime(long sec);

long convertDateTimeToSec(const tDateTime dataTime);