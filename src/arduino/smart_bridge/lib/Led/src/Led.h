#ifndef __LED__
#define __LED__

#include "Light.h"

class Led : public Light
{
public:
    Led(){}
    
    Led(unsigned short pin);

    void switchOn();
    void switchOff();

    int getState();

protected:
    unsigned short pin;
    unsigned short state;
};

#endif