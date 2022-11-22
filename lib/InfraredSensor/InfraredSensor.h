#ifndef __INFRAREDPASSIVESENSOR__
#define __INFRAREDPASSIVESENSOR__
#include "Arduino.h"
class InfraredSensor
{
public:
    InfraredSensor(const unsigned short pin)
    {
        this->pin = pin;
        pinMode(pin, INPUT);
        this->lastState = false;
    }
    bool readChangeInMovement()
    {
        unsigned short value = digitalRead(this->pin);
        if (value == this->lastState)
        {
            return false;
        }
        else
        {
            this->lastState = value;
            return true;
        }
    }

private:
    unsigned short pin;
    bool lastState;
};

#endif