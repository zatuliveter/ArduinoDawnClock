
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
Time alarmTime = Time(12, 23);
Led led;
Alarm alarm = Alarm(&led, alarmTime, 60, 15);


void changeTime()
{
    RtcDateTime now = clock.getTime();    
    display.setTime(now);
    alarm.setTime(now);
}

void setup () 
{
    Serial.begin(9600);
    
    // Serial.print("compiled time: ");
    // Serial.print(__DATE__);
    // Serial.println(__TIME__);
    led.init();

    mainThread.setInterval(500);
    mainThread.onRun(changeTime);

    threads.add(&mainThread);
	threads.add(&display); 
	threads.add(&alarm); 
	threads.add(&led); 
}


void loop () 
{
    threads.run(); 
}
