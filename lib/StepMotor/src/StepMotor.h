#ifndef __STEPMOTOR__
#define __STEPMOTOR__



#define stepToDegree(step) (step) * 200 / 360 /* 200:360 = 1:x */
#define degreeToStep(degree) (degree) / 1.8   /* 360:200 = 1:x */

class StepMotor
{
public:
    StepMotor(){}

    StepMotor(unsigned short actPin, unsigned short dirPin, unsigned short pulsePin);

    void moveOfGivenAngle(int degree);

    void moveToGivenAngle(int degree);

    void tick_step_buffer();

    void setSteps(int steps){this->steps=steps;}

    int getSteps(){return this->steps;}
private:
    unsigned short actPin;
    unsigned short dirPin;
    unsigned short pulsePin;
    int degrees;

    int steps;
};

#endif