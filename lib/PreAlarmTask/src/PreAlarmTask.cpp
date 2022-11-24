#include "PreAlarmTask.h"
#include "BlinkingLed.h"
#include "Util.h"
PreAlarmTask::PreAlarmTask(SonarSensor sonar, Led b, BlinkingLed c, SmartLighting lights, LCD_I2C lcd)
{
    this->lcd = lcd;
    this->sonar_sensor = sonar;
    this->led_B = b;
    this->led_C = c;
    this->lights = lights;
}

void PreAlarmTask::init(int period)
{   
    Task::init(period);
    this->led_C.setSpeed(255.0/(1000/mcd_period));
}

void PreAlarmTask::tick()
{
    if (getState(sonar_sensor.getDistance(-2)) == PRE_ALARM || 1)
    {
        if (this->led_B.getState())
        {
            this->led_B.switchOff();
        }

        lcd.clear();

        lcd.setCursor(0, 0);

        lcd.print("PRE-ALARM");

        lcd.setCursor(10, 0);

        lcd.print(sonar_sensor.getDistance(-2));

        this->led_C.tick();

        this->lights.tick();
    }
}