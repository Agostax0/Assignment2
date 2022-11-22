#ifndef __BLINKING__
#define __BLINKING___
#include "Led.h"

class BlinkingLed : public Led
{
public:
    BlinkingLed(unsigned short pin);

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