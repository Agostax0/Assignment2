#ifndef __SONARTASK__
#define __SONARTASK__
#include "Task.h"
#include "SonarSensor.h"
class SonarTask:public Task{
    public:
        SonarTask(unsigned short TrigPin,unsigned short EchoPin);
        void init();
        void tick();
    private:
        SonarSensor sensor;
};

#endif