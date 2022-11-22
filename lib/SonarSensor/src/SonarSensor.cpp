#include "SonarSensor.h"
#include "Arduino.h"
const float vs = 331.5 + 0.6 * 20;
SonarSensor::SonarSensor(unsigned short TrigPin, unsigned short EchoPin)
{
    this->TrigPin = TrigPin;
    this->EchoPin = EchoPin;
    pinMode(this->TrigPin, OUTPUT);
    pinMode(this->EchoPin, INPUT);
}
double SonarSensor::getDistance(short powerOfTen)
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