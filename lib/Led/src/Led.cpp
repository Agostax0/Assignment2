#include "Led.h"
#include "Arduino.h"

Led::Led(unsigned short pin)
{
    this->pin = pin;
    this->state = LOW;
    pinMode(this->pin, OUTPUT);
    digitalWrite(this->pin,LOW);
}

void Led::switchOff()
{
    digitalWrite(this->pin, LOW);
    this->state = LOW;
}

void Led::switchOn()
{
    digitalWrite(this->pin, HIGH);
    this->state = HIGH;
}
int Led::getState()
{
    return this->state;
}