#ifndef __STEPMOTOR__
#define __STEPMOTOR__



#define stepToDegree(step) (step) * 200 / 360 /* 200:360 = 1:x */
#define degreeToStep(degree) (degree) / 1.8   /* 360:200 = 1:x */

class StepMotor
{
public:
    StepMotor(unsigned short actPin, unsigned short dirPin, unsigned short pulsePin);

    void moveOfGivenAngle(int degree);

    void tick_step_buffer();
private:
    unsigned short actPin;
    unsigned short dirPin;
    unsigned short pulsePin;

    int steps;
};

#endif