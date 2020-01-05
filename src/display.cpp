#include "Arduino.h"
#include "ThreeWire.h"
#include "RtcDS1302.h"
#include "TM1637.h"
#include "Thread.h"

#define CLK 2//pins definitions for TM1637 and can be changed to other ports
#define DIO 3

class Display : public Thread
{
private:
    bool clockPoint = true;
    int8_t TimeDisp[4] = {0x00, 0x00, 0x00, 0x00};
    TM1637 tm1637;

public:
    Display()
    : tm1637(CLK, DIO)
    {
        tm1637.set();
        tm1637.init();
        setInterval(500);          
    }

    void setTime(const RtcDateTime& dt)
    {
        int hour = dt.Hour();
        int minute = dt.Minute();
        
        TimeDisp[0] = hour / 10;
        TimeDisp[1] = hour % 10;
        TimeDisp[2] = minute / 10;
        TimeDisp[3] = minute % 10;
            
        tm1637.display(TimeDisp);
    }

	void run()
    {		
        if(clockPoint)
            tm1637.point(POINT_ON);
        else 
            tm1637.point(POINT_OFF);

        clockPoint = !clockPoint;

		runned();
	}
};
