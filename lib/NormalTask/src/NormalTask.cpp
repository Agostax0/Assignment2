#include "NormalTask.h"

NormalTask::NormalTask(SonarSensor sonar, LightSensor light, Led b, Led a, BlinkingLed c, InfraredSensor pir)
{
    this->sonar_sensor = sonar;
    this->light_sensor = light;
    this->led_A = a;
    this->led_B = b;
    this->led_C = c;
    this->pir_sensor = pir;
    this->detected = false;
}

void NormalTask::init()
{
    this->sonar_sampling = -1;
}

void NormalTask::tick()
{
    if (getState(sonar_sensor.getDistance(-2)) == NORMAL)
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

            led_B.switchOn();
            led_C.switchOff();

            if (pir_cooldown == -1)
            {
                pir_cooldown = millis();
            }

            bool light_level = (this->light_sensor.getLightLevel() < TH_L) ? true : false;
            bool cooldown = (millis() - this->pir_cooldown > T1) ? true : false;

            if (!light_level || (!this->pir_sensor.readChangeInMovement() && cooldown))
            {
                this->led_A.switchOff();
                pir_cooldown = -1;
            }
            else
            {
                this->led_A.switchOn();
                if (this->pir_sensor.readChangeInMovement())
                {
                    pir_cooldown = millis();
                }
            }
        }
    }
    else
    {
        sonar_sampling = -1;
    }
}