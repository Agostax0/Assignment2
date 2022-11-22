#ifndef __NORMALTASK__
#define __NORMALTASK__
#include "Task.h"
#include "SonarSensor.h"
#include "SmartLighting.h"
#include "BlinkingLed.h"

class NormalTask : public Task
{
public:
    NormalTask(SonarSensor sonar, Led b, BlinkingLed c, SmartLighting lights);
    void init();
    void tick();

private:
    long sonar_sampling;
    SonarSensor sonar_sensor;
    SmartLighting lights;
    Led led_B;
    BlinkingLed led_C;
};

#endif