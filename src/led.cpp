#include "Arduino.h"
#include "common.h"

class Led 
{
private:
    const int analogOutPin = 9; 
    int _expectedPwm = 0;
    int _actualPwm = 0;

public:
    Led()
    {        
    }    

    void setBright(double bright)
    {
        if (bright < 0) bright = 0;
        if (bright > 100) bright = 100;
        
        int pwm = map_double(bright, 0.0, 100.0, 0, 1023);

        pwm = fixPWM(pwm);

        //Serial.print("pwm=");
        //Serial.println(pwm);

        _expectedPwm = pwm;   
    }

    void doWork()
    {
        if(_actualPwm > _expectedPwm) _actualPwm -= 1;
        if(_actualPwm < _expectedPwm) _actualPwm += 1;  
        
        analogWrite(analogOutPin, _actualPwm);        
    }

private:
    int fixPWM(int pwm)
    {
        while (pwm >= 254 && pwm <= 256) pwm = 253;
        return pwm;
    }    
};