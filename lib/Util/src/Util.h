#ifndef __UTIL__
#define __UTIL__

#define PE_normal 300
#define PE_pre_alarm 200
#define PE_alarm 100

#define T1 200
#define TH_L 200

#define WL1 15
#define WL2 10
#define WL_MAX 5

enum alarmState
{
    NORMAL,
    PRE_ALARM,
    ALARM
};

int getState(double distance);
bool range(int value, int expected, int percentage);




#endif