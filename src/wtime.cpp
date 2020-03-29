#include <include/wtime.h>

#include <vector>

#define DAYSEC 24 * 60 * 60

const long secYear = 365 * DAYSEC;
const long secLeapYear = 366 * DAYSEC;
const long secMounth = 28 * DAYSEC;
const long secDay = DAYSEC;
const long secHour = 60 * 60;
const long secMin = 60;

uint8_t cntLeapYear(const uint16_t year, uint8_t& leapDay)
{
    int countLeapYear = 0;

    std::vector<uint16_t> leapYear;
    for(int i = year; i > 1970; i = i - 4)
        leapYear.push_back(i);

    for(int i = year - 1; i > 1970; i--)
        for(auto& p : leapYear)
            if(i == p)
                countLeapYear++;

    for(auto& p : leapYear)
        if(p == year)
            leapDay = 29;

    return countLeapYear;
}

long CalculateTime(const uint8_t second,
    const uint8_t minute,
    const uint8_t hour,
    const uint8_t day,
    const uint8_t month,
    const uint16_t year,
    const uint8_t timeZone = 3)
{
    long result = 0;

    long secMinute(0), secHour(0), secDay(0), secMonth(0), secYear(0);

    uint8_t leapDay = 28;
    int countLeapYear = cntLeapYear(year, leapDay);

    secYear = (365 * (year - 1970 - countLeapYear) + 366 * countLeapYear) * DAYSEC;

    switch(month) {
    case 2:
        secMonth = (1 * 31 + 30 * 0) * DAYSEC;
        break;
    case 3:
        secMonth = (1 * 31 + 30 * 0 + leapDay) * DAYSEC;
        break;
    case 4:
        secMonth = (2 * 31 + 30 * 0 + leapDay) * DAYSEC;
        break;
    case 5:
        secMonth = (2 * 31 + 30 * 1 + leapDay) * DAYSEC;
        break;
    case 6:
        secMonth = (3 * 31 + 30 * 1 + leapDay) * DAYSEC;
        break;
    case 7:
        secMonth = (3 * 31 + 30 * 2 + leapDay) * DAYSEC;
        break;
    case 8:
        secMonth = (4 * 31 + 30 * 2 + leapDay) * DAYSEC;
        break;
    case 9:
        secMonth = (5 * 31 + 30 * 2 + leapDay) * DAYSEC;
        break;
    case 10:
        secMonth = (5 * 31 + 30 * 3 + leapDay) * DAYSEC;
        break;
    case 11:
        secMonth = (6 * 31 + 30 * 3 + leapDay) * DAYSEC;
        break;
    case 12:
        secMonth = (6 * 31 + 30 * 4 + leapDay) * DAYSEC;
        break;
    }

    secDay = (day - 1) * DAYSEC;
    secHour = (hour - timeZone) * 60 * 60;
    secMinute = minute * 60;

    result = second + secMinute + secHour + secDay + secMonth + secYear;
    return result;
}

tDateTime convertSecToDateTime(long sec)
{
    uint16_t year = 0;
    uint8_t month = 0;
    uint8_t day = 0;
    uint8_t hour = 0;
    uint8_t min = 0;

    std::vector<uint16_t> leapYear;
    for(int i = 2020; i > 1970; i -= 4)
        leapYear.push_back(i);

    uint8_t leapDay = 0;
    while(sec > secYear) {
        year++;
        if(year % 4 == 0) {
            sec -= secLeapYear;
            leapDay = 29;
        } else {
            sec -= secYear;
            leapDay = 28;
        }
    }

    while(sec > secMounth) {
        month++;
        switch(month) {
        case 2:
            sec -= 31 * DAYSEC;
            break;
        case 3:
            sec -= leapDay * DAYSEC;
            break;
        case 4:
            sec -= 31 * DAYSEC;
            break;
        case 5:
            sec -= 30 * DAYSEC;
            break;
        case 6:
            sec -= 31 * DAYSEC;
            break;
        case 7:
            sec -= 30 * DAYSEC;
            break;
        case 8:
            sec -= 31 * DAYSEC;
            break;
        case 9:
            sec -= 30 * DAYSEC;
            break;
        case 10:
            sec -= 30 * DAYSEC;
            break;
        case 11:
            sec -= 31 * DAYSEC;
            break;
        case 12:
            sec -= 30 * DAYSEC;
            break;
        }
    }

    while(sec > secDay) {
        sec -= secDay;
        day++;
    }

    while(sec > secHour) {
        sec -= secHour;
        hour++;
    }

    while(sec > secMin) {
        sec -= secMin;
        min++;
    }

    tDateTime dataTime{ (uint8_t)sec, min, (uint8_t)(hour + 3), (uint8_t)(day + 1), (uint8_t)(month + 1),
        (uint16_t)(year + 1970) };
    return dataTime;
}

long convertDateTimeToSec(tDateTime dataTime)
{
    CalculateTime(dataTime.second, dataTime.minute, dataTime.hour, dataTime.day, dataTime.month, dataTime.year);
}
