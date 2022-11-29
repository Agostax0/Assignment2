#include "LightSensor.h"

LightSensor::LightSensor(uint8_t pin)
{
    this->pin = pin;
    pinMode(this->pin, INPUT);
    //pinMode(A1,INPUT);
}
int LightSensor::getLightLevel()
{
    return analogRead(this->pin /*A1*/);
}