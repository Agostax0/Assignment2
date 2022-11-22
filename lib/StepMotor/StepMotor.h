#ifndef __STEPMOTOR__
#define __STEPMOTOR__

#include "Arduino.h"

#define stepToDegree(step) (step) * 200 / 360 /* 200:360 = 1:x */
#define degreeToStep(degree) (degree) / 1.8   /* 360:200 = 1:x */

void print_request_mot(String name, double value)
{
    Serial.print("current" + name + ": ");
    Serial.print(value);
    Serial.println();
}
class StepMotor
{
public:
    StepMotor(const unsigned short actPin, const unsigned short dirPin, const unsigned short pulsePin)
    {
        this->actPin = actPin;
        this->dirPin = dirPin;
        this->pulsePin = pulsePin;
        pinMode(this->actPin, OUTPUT);
        pinMode(this->dirPin, OUTPUT);
        pinMode(this->pulsePin, OUTPUT);
        this->currentDegree = 0;
    }

    void moveOfGivenAngle(int degree)
    {
        this->currentDegree += degree;
        // MOVIMENTO
        digitalWrite(this->actPin, LOW);
        if (degree <= 0)
        { // COUNTERCLOCKWISE
            digitalWrite(this->dirPin, HIGH);
        }
        else
        { // CLOCKWISE
            digitalWrite(this->dirPin, LOW);
        }
        do_n_steps(degreeToStep(abs(degree)));

        digitalWrite(this->actPin, HIGH);
    }

    void resetToZero()
    {
        this->moveOfGivenAngle(this->startingDegree);
    }

    void setAsZeroDegree()
    {
        this->startingDegree = this->currentDegree;
    }

    short getCurrentDegree()
    {
        return this->currentDegree;
    }

private:
    unsigned short actPin;
    unsigned short dirPin;
    unsigned short pulsePin;
    short startingDegree;
    short currentDegree;

    void do_n_steps(short steps)
    {
        for (short i = 0; i <= steps; i++)
        {
            digitalWrite(this->pulsePin, LOW);
            delay(5);
            digitalWrite(this->pulsePin, HIGH);
            delay(5);
        }
    }
};

#endif