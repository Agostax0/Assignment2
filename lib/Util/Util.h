#ifndef __UTIL__
#define __UTIL___

#include "SonarSensor.h"
#include "LightSensor.h"
#include "StepMotor.h"
#include "InfraredSensor.h"
#include "BlinkingLed.h"
#include "Led.h"
#include "Potentiometer.h"
#include "LCD_I2C.h"
#include "Bounce2.h"



#define PE_normal 2000
#define PE_pre_alarm 1000
#define PE_alarm 500

#define T1 200
#define TH_L 800

#define WL1 15
#define WL2 10
#define WL_MAX 5

enum alarmState
{
    NORMAL,
    PRE_ALARM,
    ALARM
};


bool range(int value, int expected, int percentage)
{
    double percentage_value = expected * (percentage / 100.0);

    int lower_bound = expected - percentage_value;

    int upper_bound = expected + percentage_value;

    return (value > lower_bound && value < upper_bound) ? true : false;
}


int getState(double distance)
{
    if (distance < WL1)
    {
        return NORMAL;
    }
    if (distance < WL2 && distance > WL1)
    {
        return PRE_ALARM;
    }
    if (distance > WL_MAX || ((distance > WL2) && (distance < WL_MAX)))
    {
        return ALARM;
    }
}



#endif