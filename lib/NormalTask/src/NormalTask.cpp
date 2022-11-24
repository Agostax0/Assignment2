#include "NormalTask.h"
#include "Util.h"
NormalTask::NormalTask(SonarSensor sonar, Led b, BlinkingLed c, SmartLighting lights)
{
    this->sonar_sensor = sonar;
    this->lights = lights;
    this->led_B = b;
    this->led_C = c;
}

void NormalTask::init(int period)
{
    Task::init(period);
    this->lights.init();
}

void NormalTask::tick()
{
    if (getState(sonar_sensor.getDistance(-2)) == NORMAL || 1)
    {
        if (!led_B.getState())
        {
            led_B.switchOn();
        }
        if (led_C.getState())
        {
            led_C.switchOff();
        }

        this->lights.tick();

    }
}