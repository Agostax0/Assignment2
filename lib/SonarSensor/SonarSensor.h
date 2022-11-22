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

    

    double getDistance(const short powerOfTen){
        if(this->distance == -1){
            this->calcDistance(powerOfTen);
        }
        return this->distance;
    }

private:
    unsigned short TrigPin;
    unsigned short EchoPin;
    double distance = -1;

    void calcDistance(const short powerOfTen)
    {
        long duration;
        double temp;

        digitalWrite(this->TrigPin, LOW);
        delayMicroseconds(2);

        digitalWrite(this->TrigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(TrigPin, LOW);

        duration = pulseIn(this->EchoPin, HIGH);

        temp = duration / 1000.0 / 1000.0 / pow(10,powerOfTen) * vs / 2.0;

        this->distance = temp;
    }
};

#endif