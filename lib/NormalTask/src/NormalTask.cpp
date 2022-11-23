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
    this->sonar_sampling = -1;
    this->lights.init();
}

void NormalTask::tick()
{
    if (getState(sonar_sensor.getDistance(-2)) == NORMAL || 1)
    {
        if (sonar_sampling == -1)
        {
            sonar_sampling = millis();
        }
        else
        {
            if ((millis() - sonar_sampling) > PE_normal)
            {
                this->sonar_sensor.calcDistance(-2);
                sonar_sampling = -1;
                Serial.println("Sampled in NORMAL");
            }
        }
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
    else
    {
        sonar_sampling = -1;
    }
}