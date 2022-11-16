#ifndef __INFRAREDPASSIVESENSOR__
#define __INFRAREDPASSIVESENSOR__
#include "Arduino.h"

class InfraredSensor{
    public:
        InfraredSensor(const uint8_t pin);
        virtual bool readChangeInMovement() = 0;
    private:
        uint8_t pin;
        bool lastState;
};

#endif