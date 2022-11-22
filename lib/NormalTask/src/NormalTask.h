#ifndef __NORMALTASK__
#define __NORMALTASK__
#include "Task.h"
#include "Util.h"


class NormalTask : public Task
{
public:
    NormalTask(SonarSensor sonar, LightSensor light, Led b,Led a, BlinkingLed c, InfraredSensor pir);
    void init();
    void tick();

private:
    long sonar_sampling;
    bool detected;
    long pir_cooldown;
    SonarSensor sonar_sensor;
    LightSensor light_sensor;
    Led led_A;
    Led led_B;
    BlinkingLed led_C;
    InfraredSensor pir_sensor;
};

#endif