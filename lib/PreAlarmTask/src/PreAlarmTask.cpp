#include "PreAlarmTask.h"
#include "Util.h"
PreAlarmTask::PreAlarmTask(SonarSensor sonar, Led b, BlinkingLed c, SmartLighting lights, LCD_I2C lcd){
    this->lcd = lcd;
    this->sonar_sensor = sonar;
    this->led_B = b;
    this->led_C = c;
    this->lights = lights;
}

void PreAlarmTask::init(){
    this->sonar_sampling = -1;
}
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
void PreAlarmTask::tick(){
    if (getState(sonar_sensor.getDistance(-2)) == PRE_ALARM /*|| 1*/)
    {
        if (sonar_sampling == -1)
        {
            sonar_sampling = millis();
        }
        else
        {
            if ((millis() - sonar_sampling) > PE_pre_alarm)
            {
                this->sonar_sensor.getDistance(-2);
                sonar_sampling = -1;
            }
            
            if(this->led_B.getState()){
                this->led_B.switchOff();
            }

            lcd.clear();

            lcd.setCursor(0,0);

            lcd.print("PRE-ALARM");

            lcd.setCursor(10,0);

            lcd.print(sonar_sensor.getDistance(-2));



            this->lights.tick();
        }
    }
    else
    {
        sonar_sampling = -1;
    }
}