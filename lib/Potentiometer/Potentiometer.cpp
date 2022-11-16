#include "Potentiometer.h"

Potentiometer::Potentiometer(const uint8_t pin){
    this->pin = pin;
    pinMode(this->pin,INPUT);
}

unsigned short Potentiometer::read(){
    return analogRead(this->pin);
}