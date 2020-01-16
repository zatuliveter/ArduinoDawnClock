#include "Arduino.h"
#include "common.h"
#include "Thread.h"
#include "wiring_private.h"

class Led : public Thread
{
private:
    const int analogOutPin = 9; 
    int _expectedPwm = 0;
    int _actualPwm = 0;

public:
    Led()
    {        
        // увеличиваем частоту шим чтобы led подсветка не моргала
        // D9 и D10 - 15.6 кГц 10bit
        TCCR1A = 0b00000011; // 10bit
        TCCR1B = 0b00001001; // x1 fast pwm
        pinMode(analogOutPin, OUTPUT);

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
            
            // код используемый в место analogWrite, т.к. последний глючит при значении шим = 255 (мы используем 10bit шим а не 8bit так что это критично)
            sbi(TCCR1A, COM1A1);
			OCR1A = _actualPwm; // set pwm duty
        }

		runned();
    }
};