#ifndef __INFRAREDPASSIVESENSOR__
#define __INFRAREDPASSIVESENSOR__
#include "Arduino.h"
class InfraredSensor
{
public:
    InfraredSensor(const unsigned short pin);
    
    bool readChangeInMovement();

private:
    unsigned short pin;
    bool lastState;
};

#endif