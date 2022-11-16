#ifndef __SONARSENSOR__
#define __SONARSENSOR__
#include "Arduino.h"

class SonarSensor{
    public:
        SonarSensor(const uint8_t TrigPin,const uint8_t EchoPin);

        virtual double getDistance(const int powerOfTen) = 0;
    private:
        uint8_t TrigPin;
        uint8_t EchoPin;
};


#endif