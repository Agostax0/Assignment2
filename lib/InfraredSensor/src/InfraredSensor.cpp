#include "InfraredSensor.h"
InfraredSensor::InfraredSensor(unsigned short pin)
{
    this->pin = pin;
    pinMode(pin, INPUT);
    this->lastState = false;
}

bool InfraredSensor::readChangeInMovement()
{
    unsigned short value = digitalRead(this->pin);
    if (value == this->lastState)
    {
        return false;
    }
    else
    {
        this->lastState = value;
        return true;
    }
}