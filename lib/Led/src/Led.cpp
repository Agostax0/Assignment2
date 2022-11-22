#include "Led.h"
#include "Arduino.h"

Led::Led(unsigned short pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
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