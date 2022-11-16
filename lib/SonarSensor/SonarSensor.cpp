#include "SonarSensor.h"

#define sound_velocity(temperature) (temperature) * 0.6 + 331.5

SonarSensor::SonarSensor(const uint8_t TrigPin,const uint8_t EchoPin){
    this->TrigPin = TrigPin;
    this->EchoPin = EchoPin;
    pinMode(this->TrigPin,OUTPUT);
    pinMode(this->EchoPin,INPUT);
}

double SonarSensor::getDistance(const int powerOfTen){
    long duration;
    double distance;

    digitalWrite(this->TrigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(this->TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);


    duration = pulseIn(this->EchoPin, HIGH);


    distance = duration * pow(10,powerOfTen) * sound_velocity(20/* expected current enviroment temp */) / 2;


    return distance;
}