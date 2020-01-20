
#include "Arduino.h"
#include "clock.cpp"
#include "display.cpp"
#include "time.h"
#include "alarm.cpp"
#include "Thread.h"
#include "ThreadController.h"


ThreadController threads = ThreadController();
Thread mainThread = Thread();

Clock* pClock;
Display* pDisplay;
Led* pLed;
Alarm* pAlarm;


void changeTime()
{
    RtcDateTime now = pClock->getTime();    
    pDisplay->setTime(now);
    pAlarm->setTime(now);
}

void setup () 
{
    Serial.begin(9600);
    
    pClock = new Clock();
    pDisplay = new Display();    
    pLed = new Led();
    
    Time alarmTime = Time(9, 00);
    pAlarm = new Alarm(pLed, alarmTime, 60, 15);

    // Serial.print("compiled time: ");
    // Serial.print(__DATE__);
    // Serial.println(__TIME__);

    mainThread.setInterval(500);
    mainThread.onRun(changeTime);

    threads.add(&mainThread);
	threads.add(pDisplay); 
	threads.add(pAlarm); 
	threads.add(pLed); 
}


void loop () 
{
    threads.run(); 
}
