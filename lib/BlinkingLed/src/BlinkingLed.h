#ifndef __BLINKING__
#define __BLINKING__
#include "Led.h"

class BlinkingLed : public Led
{
public:
    BlinkingLed(){}

    BlinkingLed(unsigned short pin);

    void tick();

    void setSpeed(float speed);

    void switchOff();

    int getState();

    void switchOn();

private:
    unsigned short pin;
    float currentBrightness;
    float speed;
};
#endif