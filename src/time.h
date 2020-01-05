#ifndef TIME_h
#define TIME_h

class Time
{
private:
    int _hour;
    int _minute;

public:
    Time();
    Time(int hour, int minute);
    void setTime(int hour, int minute);
    int getHour();
    int getMinute();
};

#endif