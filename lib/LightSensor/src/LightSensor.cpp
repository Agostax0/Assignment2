#include "LightSensor.h"

LightSensor::LightSensor(uint8_t pin)
{
    this->pin = pin;
    pinMode(this->pin, INPUT);
}
unsigned short LightSensor::getLightLevel()
{
    return analogRead(this->pin);

}