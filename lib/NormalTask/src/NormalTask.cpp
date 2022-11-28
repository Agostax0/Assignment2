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
    this->sonar_sensor.calcDistance(cm);
    if (getState(sonar_sensor.getDistance(cm)) == NORMAL)
    {
        led_B.switchOn();
        led_C.switchOff();

        this->lights.tick();
    }
    else{
        updateSerial();
    }
}