#ifndef __STEPMOTOR__
#define __STEPMOTOR__

#include "Arduino.h"

class StepMotor
{
public:
    StepMotor(const unsigned short actPin, const unsigned short dirPin, const unsigned short pulsePin)
    {
        this->actPin = actPin;
        this->dirPin = dirPin;
        this->pulsePin = pulsePin;
        pinMode(this->actPin,OUTPUT);
        pinMode(this->dirPin,OUTPUT);
        pinMode(this->pulsePin,OUTPUT);
        this->currentDegree = 0;
    }

    void moveOfGivenAngle(short degree)
    {
        this->currentDegree += degree;
        //MOVIMENTO
        digitalWrite(this->actPin,HIGH);
        if(degree <= 0){//COUNTERCLOCKWISE
            
        }
        else{//CLOCKWISE

        }
        digitalWrite(this->actPin,LOW);
    }

    void resetToZero()
    {
        this->moveOfGivenAngle(this->startingDegree);
    }

    void setAsZeroDegree()
    {
        this->startingDegree = this->currentDegree;
    }

private:
    unsigned short actPin;
    unsigned short dirPin;
    unsigned short pulsePin;
    short startingDegree;
    short currentDegree;
};

#endif