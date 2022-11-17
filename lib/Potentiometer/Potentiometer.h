#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__
#include "Arduino.h"
class Potentiometer
{
public:
    Potentiometer(const uint8_t pin)
    {
        this->pin = pin;
        pinMode(this->pin, INPUT);
    }

    unsigned short read()
    {
        return analogRead(this->pin);
    }

private:
    uint8_t pin;
};

#endif