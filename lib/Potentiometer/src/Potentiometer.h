#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__
#include "Arduino.h"
class Potentiometer
{
public:
    Potentiometer(const uint8_t pin);

    unsigned short read();

private:
    uint8_t pin;
};

#endif