#include "NormalTask.h"
#include "Util.h"
int getState(double distance)
{
    if (distance < WL1)
    {
        return NORMAL;
    }
    if (distance < WL2 && distance > WL1)
    {
        return PRE_ALARM;
    }
    if (distance > WL_MAX || ((distance > WL2) && (distance < WL_MAX)))
    {
        return ALARM;
    }
}
NormalTask::NormalTask(SonarSensor sonar, Led b, BlinkingLed c, SmartLighting lights)
{
    this->sonar_sensor = sonar;
    this->lights = lights;
    this->led_B = b;
    this->led_C = c;
}

void NormalTask::init()
{
    this->sonar_sampling = -1;
    this->lights.init();
}

void NormalTask::tick()
{
    if (getState(sonar_sensor.getDistance(-2)) == NORMAL /* || 1*/)
    {
        if (sonar_sampling == -1)
        {
            sonar_sampling = millis();
        }
        else
        {
            if ((millis() - sonar_sampling) > PE_normal)
            {
                this->sonar_sensor.getDistance(-2);
                sonar_sampling = -1;
            }

            if(!led_B.getState()){
                led_B.switchOn();
            }
            if(led_C.getState()){
                led_C.switchOff();
            }
            

            this->lights.tick();
        }
    }
    else
    {
        sonar_sampling = -1;
    }
}