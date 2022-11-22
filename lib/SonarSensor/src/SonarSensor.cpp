#include "SonarSensor.h"
#include "Arduino.h"
SonarSensor::SonarSensor(const unsigned short TrigPin, const unsigned short EchoPin)
{
    this->TrigPin = TrigPin;
    this->EchoPin = EchoPin;
    pinMode(this->TrigPin, OUTPUT);
    pinMode(this->EchoPin, INPUT);
}
double SonarSensor::getDistance(const short powerOfTen)
{
    long duration;
    double distance;

    digitalWrite(this->TrigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(this->TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);

    duration = pulseIn(this->EchoPin, HIGH);

    distance = duration / 1000.0 / 1000.0 / pow(10, powerOfTen) * vs / 2.0;

    return distance;
}