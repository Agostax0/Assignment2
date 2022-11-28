#ifndef __UTIL__
#define __UTIL__

#define cm -2

#define PE_normal 600
#define PE_pre_alarm 400
#define PE_alarm 200

#define mcd_period 200

#define T1 5000
#define TH_L 200

#define WL1 25
#define WL2 15
#define WL_MAX 5

enum alarmState
{
    NORMAL,
    PRE_ALARM,
    ALARM
};

int getState(double distance);
bool range(int value, int expected, int percentage);

void updateSerial();

extern bool serial;
extern int serial_read;

#endif