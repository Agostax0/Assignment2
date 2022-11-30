#include "InfraredSensor.h"
InfraredSensor::InfraredSensor(unsigned short pin)
{
    this->pin = pin;
    pinMode(pin, INPUT);
    this->lastState = LOW;
}

bool InfraredSensor::readChangeInMovement()
{
    short value = digitalRead(8);
    if(value == HIGH){
        //Serial.println("PIR: " + String(value));
    }
    
    return value;
}