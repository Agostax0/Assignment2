#ifndef __BLINKING__
#define __BLINKING___
#include "Arduino.h"
#include "Led.h"

class BlinkingLed{
    public:
        BlinkingLed(const unsigned short pin);


        void tick();
        void setSpeed(short speed);

        void switchOff();
        void switchOn();

    private:
        unsigned short pin;
        unsigned short currentBrightness;
        short speed;
};
#endif