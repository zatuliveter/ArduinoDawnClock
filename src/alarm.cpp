#include "Arduino.h"
#include "ThreeWire.h"
#include "RtcDS1302.h"
#include "time.h"
#include "led.cpp"
#include "common.h"

class Alarm
{
private:
    Time _alarmTime;
    int _glowDurationMinutes;
    int _warmDurationMinutes;    
    Led led;

public:
    Alarm(Time alarmTime, int glowDurationMin, int warmDurationMinutes)
    {
        _glowDurationMinutes = glowDurationMin;
        _alarmTime = alarmTime;
        _warmDurationMinutes = warmDurationMinutes;
    }

    void setAlarmTime(Time time)
    {
        _alarmTime = time;
    }

    void doWork(RtcDateTime now)
    {
        RtcDateTime alarmDateTime = RtcDateTime(
            now.Year(),
            now.Month(),
            now.Day(),
            _alarmTime.getHour(),
            _alarmTime.getMinute(),
            0
        );

        long nowSec = now.TotalSeconds64();
        long alarmSec = alarmDateTime.TotalSeconds64();
        
        if (nowSec > alarmSec)
        {
            // Serial.print("nowSec=");
            // Serial.print(nowSec);
            // Serial.print("alarmSec=");
            // Serial.println(alarmSec);
            // Serial.println("");

            int difSec = nowSec - alarmSec;
            double bright;

            if (difSec / 60.0 < _warmDurationMinutes)
            {
                bright = map_double(difSec, 0, _warmDurationMinutes * 60.0, 0, 100.0);
                    
                // Serial.print("bright=");
                // Serial.println(bright);
                // Serial.println("");
            }
            else if (difSec / 60 < _glowDurationMinutes)
            {
                bright = 100;
            }
            else
            {
                bright = 0;
            }
                        
            led.setBright(bright);
        }

        led.doWork();
    }
};
