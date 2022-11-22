#ifndef __UTIL__
#define __UTIL__

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


/*bool range(int value, int expected, int percentage)
{
    double percentage_value = expected * (percentage / 100.0);

    int lower_bound = expected - percentage_value;

    int upper_bound = expected + percentage_value;

    return (value > lower_bound && value < upper_bound) ? true : false;
}
*/



#endif