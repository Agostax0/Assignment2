#ifndef __LED__
#define __LED__

#include "Light.h"
#include "Arduino.h"
class Led : public Light
{
public:
    
    Led(const unsigned short pin);
    void switchOn();
    void switchOff();

    int getState();

protected:
    unsigned short pin;
    unsigned short state;
};

#endif