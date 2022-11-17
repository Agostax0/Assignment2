#ifndef __BLINKING__
#define __BLINKING___
#include "Arduino.h"
#include "Led.h"

class BlinkingLed
{
public:
    BlinkingLed(const unsigned short pin)
    {
        this->pin = pin;
        this->speed = 1;
        this->currentBrightness = 0;
        pinMode(this->pin, OUTPUT);
    }

    void tick()
    {
        if (currentBrightness < 0 || currentBrightness > 255)
        {
            speed = (-1 * speed);
        }
        this->currentBrightness += this->speed;

        analogWrite(this->pin, this->currentBrightness);
    }
    void setSpeed(short speed)
    {
        this->speed = speed;
    }

    void switchOff()
    {
        digitalWrite(this->pin, LOW);
        this->currentBrightness = 0;
    }
    void switchOn()
    {
        digitalWrite(this->pin, HIGH);
        this->currentBrightness = 255;
    }

private:
    unsigned short pin;
    unsigned short currentBrightness;
    short speed;
};
#endif