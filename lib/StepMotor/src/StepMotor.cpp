#include "StepMotor.h"
#include "Arduino.h"

StepMotor::StepMotor(unsigned short actPin, unsigned short dirPin, unsigned short pulsePin)
{
    this->actPin = actPin;
    this->dirPin = dirPin;
    this->pulsePin = pulsePin;
    this->stepsLeft = 0;
    this->current_steps = 0;
    pinMode(this->actPin, OUTPUT);
    pinMode(this->dirPin, OUTPUT);
    pinMode(this->pulsePin, OUTPUT);
}

void StepMotor::init(int period)
{
    Task::init(period);
}

void StepMotor::moveOfGivenAngle(int degree)
{
    this->stepsLeft += degreeToStep(degree);
}

void StepMotor::moveOfGivenSteps(int steps)
{
    this->stepsLeft += steps;
}

void StepMotor::tick()
{
    if (this->stepsLeft != 0)
    {
        // MOVIMENTO
        digitalWrite(this->actPin, LOW);
        if (this->stepsLeft < 0)
        { // COUNTERCLOCKWISE
            digitalWrite(this->dirPin, HIGH);
            this->stepsLeft++;
            this->current_steps--;
        }
        else
        { // CLOCKWISE
            digitalWrite(this->dirPin, LOW);
            this->stepsLeft--;
            this->current_steps++;
        }
        // MAKES A STEP
        digitalWrite(this->pulsePin, LOW);
        delayMicroseconds(1);
        digitalWrite(this->pulsePin, HIGH);
        // delay(5);
    }
    else
    {
        digitalWrite(this->actPin, HIGH);
    }
}

void StepMotor::resetToZero()
{

    if (this->current_steps != 0)
    {
        this->stepsLeft = -current_steps;
        this->current_steps = 0;
    }
    else
    {
        this->tick();
        this->current_steps = 0;
    }
}