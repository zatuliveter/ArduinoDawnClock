#include "Arduino.h"
#include "common.h"
#include "Thread.h"

class Led : public Thread
{
private:
    const int analogOutPin = 9; 
    int _expectedPwm = 0;
    int _actualPwm = 0;

public:
    Led()
    {
        setInterval(100);
    }    

    void setBright(double bright)
    {
        if (bright < 0) bright = 0;
        if (bright > 100) bright = 100;
        
        _expectedPwm = map_double(bright, 0.0, 100.0, 0, 1023);
        
        // Serial.print("pwm=");
        // Serial.println(_expectedPwm);
    }

    void run()
    {        
        // Serial.print("_actualPwm=");
        // Serial.println(_actualPwm);
        // Serial.println("");

        // Serial.print("_expectedPwm=");
        // Serial.println(_expectedPwm);
        // Serial.println("");
        
        if(_actualPwm != _expectedPwm)
        {
            if(_actualPwm > _expectedPwm) _actualPwm -= 1;
            if(_actualPwm < _expectedPwm) _actualPwm += 1;
            
            _actualPwm = fixPWM(_actualPwm);

            analogWrite(analogOutPin, _actualPwm);
        }

		runned();
    }

private:
    int fixPWM(int pwm)
    {
        while (pwm >= 254 && pwm <= 256) pwm = 253;
        return pwm;
    }    
};