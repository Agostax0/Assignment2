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
    // Serial.println(this->sonar_sensor.getDistance(cm));
    if (getState(sonar_sensor.getDistance(cm)) == NORMAL)
    {
        // Serial.println("Normal");
        led_B.switchOn();
        led_C.switchOff();

        this->lights.tick();
    }
}