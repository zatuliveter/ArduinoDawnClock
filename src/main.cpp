
#include "Arduino.h"
#include "clock.cpp"
#include "display.cpp"
#include "time.h"
#include "alarm.cpp"
#include "Thread.h"
#include "ThreadController.h"


ThreadController threads = ThreadController();

Clock clock;
Display display;
Time alarmTime = Time(9, 0);
Alarm alarm = Alarm(alarmTime, 60, 15);

void setup () 
{
    Serial.begin(9600);
    
    // увеличиваем частоту шим чтобы подсветка не моргала
    // D9 и D10 - 15.6 кГц 10bit
    TCCR1A = 0b00000011; // 10bit
    TCCR1B = 0b00001001; // x1 fast pwm

	threads.add(&display); 
}

void loop () 
{
    RtcDateTime now = clock.getTime();

    display.setTime(now);

    alarm.doWork(now);
    

    threads.run(); 
}
