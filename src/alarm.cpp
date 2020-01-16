#include "Arduino.h"
#include "ThreeWire.h"
#include "RtcDS1302.h"
#include "time.h"
#include "led.cpp"
#include "common.h"
#include "Thread.h"

class Alarm : public Thread
{
private:
    Time _alarmTime;
    RtcDateTime _currentTime;
    int _glowDurationMinutes;
    int _warmDurationMinutes;
    Led* _pLed;

public:
    Alarm(Led* pLed, Time alarmTime, int glowDurationMin, int warmDurationMinutes)
    {
        _glowDurationMinutes = glowDurationMin;
        _alarmTime = alarmTime;
        _warmDurationMinutes = warmDurationMinutes;
        _pLed = pLed;
        setInterval(1000); 
    }

    void setAlarmTime(Time time)
    {
        _alarmTime = time;
    }

    void setTime(RtcDateTime now)
    {
        _currentTime = now;
    }

    void run()
    {
        RtcDateTime alarmDateTime = RtcDateTime(
            _currentTime.Year(),
            _currentTime.Month(),
            _currentTime.Day(),
            _alarmTime.getHour(),
            _alarmTime.getMinute(),
            0
        );

        long nowSec = _currentTime.TotalSeconds64();
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
            
            _pLed->setBright(bright);
        }

		runned();
    }
};
