#ifndef __LIGHTSENSOR__
#define __LIGHTSENSOR__

#include "Task.h"
#include "Arduino.h"

class LightSensor
{
public:
    LightSensor(const uint8_t pin);

    unsigned short getLightLevel();

private:
    uint8_t pin;
};

#endif