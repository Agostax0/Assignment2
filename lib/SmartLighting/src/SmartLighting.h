#ifndef __SMARTLIGHTING__
#define __SMARTLIGHTING__
#include "Task.h"
#include "Led.h"
#include "InfraredSensor.h"
#include "LightSensor.h"
class SmartLighting : public Task
{
public:
    SmartLighting(){}
    SmartLighting(Led A, LightSensor ll, InfraredSensor pir);
    void init();
    void tick();

private:
    long pir_cooldown;
    Led A;
    LightSensor ll;
    InfraredSensor pir;
};
#endif