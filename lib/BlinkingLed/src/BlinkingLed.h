#ifndef __BLINKING__
#define __BLINKING___
#include "Arduino.h"
#include "Led.h"

class BlinkingLed : public Led
{
public:
    BlinkingLed(const unsigned short pin);

    void tick();

    void setSpeed(float speed);

    void switchOff();
    void switchOn();

private:
    unsigned short pin;
    float currentBrightness;
    float speed;
};
#endif