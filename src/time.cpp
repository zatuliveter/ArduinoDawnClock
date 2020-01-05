#include "time.h"

Time::Time()
{
    this->_hour = 7;
    this->_minute = 0;
}

Time::Time(int hour, int minute)
{
    this->setTime(hour, minute);
}

void Time::setTime(int hour, int minute)
{
    this->_hour = hour;
    this->_minute = minute;
}

int Time::getHour()
{
    return this->_hour;
}

int Time::getMinute()
{
    return this->_minute;
}