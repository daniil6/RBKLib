#include <include/wtime.h>

#include <vector>

#define DAYSEC 24 * 60 * 60

long CalculateTime(uint8_t second,
    uint8_t minute,
    uint8_t hour,
    uint8_t day,
    uint8_t month,
    uint16_t year,
    uint8_t timeZone)
{
    long result = 0;

    long secMinute(0), secHour(0), secDay(0), secMonth(0), secYear(0);

    int countLeapYear = 0;

    std::vector<uint16_t> leapYear;
    for(int i = 2020; i > 1970; i = i - 4)
        leapYear.push_back(i);

    for(int i = year - 1; i > 1970; i--)
        for(auto& p : leapYear)
            if(i == p)
                countLeapYear++;

    secYear = (365 * (year - 1970 - countLeapYear) + 366 * countLeapYear) * DAYSEC;

    uint8_t leapDay = 28;
    for(auto& p : leapYear)
        if(p == year)
            leapDay = 29;

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

long CalculateTime(tDataTime dataTime)
{
    CalculateTime(dataTime.second, dataTime.minute, dataTime.hour, dataTime.day, dataTime.month, dataTime.year);
}
