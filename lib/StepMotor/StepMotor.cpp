#include "StepMotor.h"

#define stepToDegree(step) (step) * 200 / 360 /* 200:360 = 1:x */
#define degreeToStep(degree) (degree) * 360 / 200/* 360:200 = 1:x */




StepMotor::StepMotor(const uint8_t actPin, const uint8_t movPin, const uint8_t powPin){
    this->actPin = actPin;
    this->movPin = movPin;
    this->powPin = powPin;
    //pinMode(this->actPin,);
    //pinMode(this->movPin,);
    //pinMode(this->powPin,);
    this->currentDegree = 0;
}

void StepMotor::moveOfGivenAngle(short degree){
    this->currentDegree += degree;
    //movimento
}

void StepMotor::resetToZero(){
    this->moveOfGivenAngle(this->startingDegree);
}

void StepMotor::setAsZeroDegree(){
    this->startingDegree = this->currentDegree;
}