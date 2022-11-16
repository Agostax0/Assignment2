#ifndef __SONARSENSOR__
#define __SONARSENSOR__
#include "Arduino.h"

class SonarSensor{
    public:
        SonarSensor(unsigned short TrigPin,unsigned short EchoPin);

        virtual double getDistance(const int powerOfTen) = 0;
    private:
        unsigned short TrigPin;
        unsigned short EchoPin;
};


#endif