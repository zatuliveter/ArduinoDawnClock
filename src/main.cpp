
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
Time alarmTime = Time(10, 00);
Led led = Led();
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
    
    // увеличиваем частоту шим чтобы led подсветка не моргала
    // D9 и D10 - 15.6 кГц 10bit
    TCCR1A = 0b00000011; // 10bit
    TCCR1B = 0b00001001; // x1 fast pwm

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
