#ifndef __TASK__
#define __TASK__

enum alarmState{
    NORMAL,  
    PRE_ALARM,
    ALARM
};

class Task{
    public:
        virtual void tick() = 0;
        virtual void init() = 0;
};

#endif