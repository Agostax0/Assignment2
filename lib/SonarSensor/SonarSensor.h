#ifndef __SONARSENSOR__
#define __SONARSENSOR__
#include "Arduino.h"
const float vs = 331.5 + 0.6*20;
class SonarSensor
{
public:
    SonarSensor(){}

    SonarSensor(const uint8_t TrigPin, const uint8_t EchoPin)
    {
        this->TrigPin = TrigPin;
        this->EchoPin = EchoPin;
        pinMode(this->TrigPin, OUTPUT);
        pinMode(this->EchoPin, INPUT);
    }

    double getDistance(const int powerOfTen)
    {
        long duration;
        double distance;

        digitalWrite(this->TrigPin, LOW);
        delayMicroseconds(2);

        digitalWrite(this->TrigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(TrigPin, LOW);

        duration = pulseIn(this->EchoPin, HIGH);

        distance = duration / 1000.0 / 1000.0 / pow(10,powerOfTen) * vs / 2.0;

        return distance;
    }

private:
    unsigned short TrigPin;
    unsigned short EchoPin;
};

#endif