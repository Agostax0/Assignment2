#include "SmartLighting.h"
#include "Util.h"
SmartLighting::SmartLighting(Led A, LightSensor ll, InfraredSensor pir)
{
    this->A = A;
    this->ll = ll;
    this->pir = pir;
}
void SmartLighting::init()
{
    this->pir_cooldown = -1;
}
void SmartLighting::tick()
{
    if (pir_cooldown == -1)
    {
        pir_cooldown = millis();
    }

    bool light_level = (this->ll.getLightLevel() < TH_L) ? true : false;

    bool cooldown = (millis() - this->pir_cooldown > T1) ? true : false;

    if (!light_level || (!this->pir.readChangeInMovement() && cooldown)) //TOO MUCH LIGHT OR (THERE WAS NONE && T1 TIME HAS ELAPSED SINCE LAST DETECTION)
    {
        this->A.switchOff();
        pir_cooldown = -1;
    }
    else
    {

        if (!this->A.getState() && this->pir.readChangeInMovement()) //TURN ON THE LED AFTER CHECKING PRESENCE
        {
            this->A.switchOn();
        }

        if (this->pir.readChangeInMovement())
        {
            pir_cooldown = millis();
        }
    }
}

void SmartLighting::turnOff()
{
    this->A.switchOff();
}