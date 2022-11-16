#include "LightSensor.h"

LightSensor::LightSensor(const uint8_t pin){
    this->pin = pin;
    pinMode(this->pin,INPUT);
}

unsigned short LightSensor::getLightLevel(){
    currentLightLevel = analogRead(this->pin);
    return this->currentLightLevel;
}
