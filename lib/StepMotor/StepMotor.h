#ifndef __STEPMOTOR__
#define __STEPMOTOR__

#include "Arduino.h"

class StepMotor{
    public:
        StepMotor(const uint8_t actPin, const uint8_t movPin, const uint8_t powPin);

        void moveOfGivenAngle(const short degrees);

        void resetToZero();

        void setAsZeroDegree();
    private:
        uint8_t actPin; 
        uint8_t movPin; 
        uint8_t powPin;
        short startingDegree;
        short currentDegree;
};


#endif