#ifndef __LIGHTSENSOR__
#define __LIGHTSENSOR__

#include "Task.h"
#include "Arduino.h"

class LightSensor
{
public:
    LightSensor(){};

    LightSensor(const uint8_t pin)
    {
        this->pin = pin;
        pinMode(this->pin, INPUT);
    }
    unsigned short getLightLevel()
    {
        currentLightLevel = analogRead(this->pin);
        return this->currentLightLevel;
    }

private:
    unsigned short currentLightLevel = 0;
    uint8_t pin;
};

#endif