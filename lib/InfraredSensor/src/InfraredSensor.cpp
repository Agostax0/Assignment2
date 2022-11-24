#include "InfraredSensor.h"
InfraredSensor::InfraredSensor(unsigned short pin)
{
    this->pin = pin;
    pinMode(pin, INPUT);
    this->lastState = LOW;
}

bool InfraredSensor::readChangeInMovement()
{
    short value = digitalRead(this->pin);

    return value;
}