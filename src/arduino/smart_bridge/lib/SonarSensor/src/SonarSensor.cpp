#include "SonarSensor.h"
#include "Arduino.h"
const float vs = 331.5 + 0.6 * 20;
SonarSensor::SonarSensor(unsigned short TrigPin, unsigned short EchoPin)
{
    this->TrigPin = TrigPin;
    this->EchoPin = EchoPin;
    pinMode(this->TrigPin, OUTPUT);
    pinMode(this->EchoPin, INPUT);
    this->measured_distance = -1;
}
/* This function activates the sonar and receives the distance of the first obj in front of it */
void SonarSensor::calcDistance(short powerOfTen)
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

    this->measured_distance = distance;


}
/* this function return the distance measured beforehand */
double SonarSensor::getDistance(short powerOfTen){
        if(this->measured_distance == -1){
            this->calcDistance(powerOfTen);
        }
        Serial.println(String(measured_distance));
        return this->measured_distance;
    }