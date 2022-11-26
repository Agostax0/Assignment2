#ifndef __STEPMOTOR__
#define __STEPMOTOR__
#include "Task.h"


#define stepToDegree(step) (step) * 200 / 360 /* 200:360 = 1:x */
#define degreeToStep(degree) (degree) / 1.8   /* 360:200 = 1:x */

class StepMotor : public Task
{
public:
    StepMotor(){}

    StepMotor(unsigned short actPin, unsigned short dirPin, unsigned short pulsePin);

    void moveOfGivenAngle(int degree);

    void moveOfGivenSteps(int steps);

    void resetToZero(int degree);

    void init(int period);

    void tick();

    void resetToZero();

    int getSteps(){return this->current_steps;}
private:
    unsigned short actPin;
    unsigned short dirPin;
    unsigned short pulsePin;
    int degrees;

    int current_steps;

    int steps;
};

#endif