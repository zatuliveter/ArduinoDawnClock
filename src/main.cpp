
#include "Arduino.h"
#include "clock.cpp"
#include "display.cpp"
#include "time.h"
#include "alarm.cpp"
#include "Thread.h"
#include "ThreadController.h"


ThreadController threads = ThreadController();
Thread mainThread = Thread();

Clock clock;
Display display;
Time alarmTime = Time(13, 00);
Led* pLed;
Alarm* pAlarm;


void changeTime()
{
    RtcDateTime now = clock.getTime();    
    display.setTime(now);
    pAlarm->setTime(now);
}

void setup () 
{
    Serial.begin(9600);
        
    pLed = new Led();
    pAlarm = new Alarm(pLed, alarmTime, 60, 15);

    // Serial.print("compiled time: ");
    // Serial.print(__DATE__);
    // Serial.println(__TIME__);

    mainThread.setInterval(500);
    mainThread.onRun(changeTime);

    threads.add(&mainThread);
	threads.add(&display); 
	threads.add(pAlarm); 
	threads.add(pLed); 
}


void loop () 
{
    threads.run(); 
}
