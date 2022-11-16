#include "Led.h"
#include "Arduino.h"

Led::Led(const unsigned short pin){
    this->pin = pin;
    pinMode(pin,OUTPUT);
}

void Led::switchOn(){
    digitalWrite(this->pin,HIGH);
}

void Led::switchOff(){
    digitalWrite(this->pin,LOW);
}