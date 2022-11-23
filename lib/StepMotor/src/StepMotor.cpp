#include "StepMotor.h"
#include "Arduino.h"

StepMotor::StepMotor(unsigned short actPin, unsigned short dirPin, unsigned short pulsePin)
{
    this->actPin = actPin;
    this->dirPin = dirPin;
    this->pulsePin = pulsePin;
    this->degrees = 90;
    pinMode(this->actPin, OUTPUT);
    pinMode(this->dirPin, OUTPUT);
    pinMode(this->pulsePin, OUTPUT);
}

void StepMotor::moveOfGivenAngle(int degree)
{
    this->degrees += degree;
    this->steps += degreeToStep(degree);
}

void StepMotor::tick_step_buffer()
{
    if (this->steps != 0)
    {
        // MOVIMENTO
        digitalWrite(this->actPin, LOW);
        if (this->steps < 0)
        { // COUNTERCLOCKWISE
            digitalWrite(this->dirPin, HIGH);
        }
        else
        { // CLOCKWISE
            digitalWrite(this->dirPin, LOW);
        }
        //MAKES A STEP
        digitalWrite(this->pulsePin, LOW);
        delay(5);
        digitalWrite(this->pulsePin, HIGH);
        delay(5);
        //REMOVES A STEP FROM THE STEPS TO MAKE
        this->degrees = (this->steps > 0) ? this->degrees - stepToDegree(1) : this->degrees + stepToDegree(1);
        this->steps = (this->steps > 0) ? this->steps-1 : this->steps+1;
        

        digitalWrite(this->actPin, HIGH);
    }
}

void StepMotor::moveToGivenAngle(int degree){
    this->moveOfGivenAngle(this->degrees-degree);
}