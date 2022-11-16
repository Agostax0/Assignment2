#ifndef __LIGHTSENSOR__
#define __LIGHTSENSOR__

#include "Task.h"
#include "Arduino.h"

class LightSensor{
    public:
        LightSensor(const uint8_t pin);
        virtual unsigned short getLightLevel() = 0;
    private:
        unsigned short currentLightLevel = 0;
        uint8_t pin;
};


#endif