#include "Arduino.h"

#define countof(a) (sizeof(a) / sizeof(a[0]))

#include "ThreeWire.h"
#include "RtcDS1302.h"

// CONNECTIONS:
// DS1302 CLK/SCLK --> 6
// DS1302 DAT/IO --> 5
// DS1302 RST/CE --> 4
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND

class Clock
{
private:
    ThreeWire myWire;
    RtcDS1302<ThreeWire> rtc;


public:
    Clock()
        : myWire(5, 6, 4) // IO, SCLK, CE
        , rtc(myWire)
    {     
        rtc.Begin();
        
        RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
        rtc.SetDateTime(compiled);

        Serial.print("compiled time: ");                
        printDateTime(compiled);
          
        if (rtc.GetIsWriteProtected())
        {
            Serial.println("RTC was write protected, enabling writing now");
            rtc.SetIsWriteProtected(false);
        }
        
        if (!rtc.GetIsRunning())
        {
            Serial.println("RTC was not actively running, starting now");
            rtc.SetIsRunning(true);
        }
        
        RtcDateTime now = rtc.GetDateTime();
        if (now < compiled) 
        {
            Serial.println("RTC is older than compile time!  (Updating DateTime)");
            rtc.SetDateTime(compiled);
        }

        //TODO: переместить надо наверное куда-то или сделать обработчик этой невалидной ситуации
        if (!now.IsValid())
        {
            // Common Causes:
            //    1) the battery on the device is low or even missing and the power line was disconnected
            Serial.println("RTC lost confidence in the DateTime!");
        }
    }

    RtcDateTime getTime()
    {
        RtcDateTime now = rtc.GetDateTime();        
        return now;
    } 
    
private:
    void printDateTime(const RtcDateTime& dt)
    {
        char datestring[20];

        snprintf_P(
            datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() 
        );

        Serial.println(datestring);
    }

};
