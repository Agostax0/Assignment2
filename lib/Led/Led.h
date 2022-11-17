#ifndef __LED__
#define __LED__

#include "Light.h"
#include "Arduino.h"
class Led : public Light
{
public:
    Led(const unsigned short pin)
    {
        this->pin = pin;
        pinMode(pin, OUTPUT);
    }
    void switchOn()
    {
        digitalWrite(this->pin, HIGH);
        this->state = HIGH;
    }
    void switchOff()
    {
        digitalWrite(this->pin, LOW);
        this->state = LOW;
    }

    int getState(){
        return this->state;
    }

protected:
    unsigned short pin;
    unsigned short state;
};

#endif