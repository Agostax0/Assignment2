#ifndef __LIGHTSENSOR__
#define __LIGHTSENSOR__

#include "Task.h"
#include "Arduino.h"

class LightSensor
{
public:
    LightSensor(){}

    LightSensor(uint8_t pin);

    int getLightLevel();

private:
    uint8_t pin;
};

#endif