#include "StepMotor.h"
#include "Arduino.h"

StepMotor::StepMotor(unsigned short actPin, unsigned short dirPin, unsigned short pulsePin)
{
    this->actPin = actPin;
    this->dirPin = dirPin;
    this->pulsePin = pulsePin;
    this->steps = 0;
    this->current_steps = 0;
    pinMode(this->actPin, OUTPUT);
    pinMode(this->dirPin, OUTPUT);
    pinMode(this->pulsePin, OUTPUT);
}

void StepMotor::init(int period){
    Task::init(period);
}

void StepMotor::moveOfGivenAngle(int degree)
{
    this->steps += degreeToStep(degree);
}

void StepMotor::moveOfGivenSteps(int steps)
{
    if(steps > this->current_steps){
        int delta = (steps - this->current_steps);
        this->current_steps += delta;
        this->steps += delta;
    }
    
}

void StepMotor::tick()
{
    if (this->steps != 0)
    {
        Serial.println("Steps left: " + String(this->steps));
        // MOVIMENTO
        digitalWrite(this->actPin, LOW);
        if (this->steps < 0)
        { // COUNTERCLOCKWISE
            digitalWrite(this->dirPin, HIGH);
            this->steps++;
            this->current_steps--;
        }
        else
        { // CLOCKWISE
            digitalWrite(this->dirPin, LOW);
            this->steps--;
            this->current_steps++;
        }
        //MAKES A STEP
        digitalWrite(this->pulsePin, LOW);
        delayMicroseconds(1);
        digitalWrite(this->pulsePin, HIGH);
        //delay(5);
    }
    else{
        digitalWrite(this->actPin, HIGH);
    }
}

void StepMotor::resetToZero(){
    this->steps = - this->current_steps;
}