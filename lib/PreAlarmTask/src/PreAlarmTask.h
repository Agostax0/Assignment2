#ifndef __PREALARMTASK__
#define __PREALARMTASK__
#include "Task.h"
#include "BlinkingLed.h"
#include "SonarSensor.h"
#include "SmartLighting.h"
#include "LCD_I2C.h"
class PreAlarmTask : public Task
{
public:
    PreAlarmTask(SonarSensor sonar, Led b, BlinkingLed c, SmartLighting lights, LCD_I2C lcd);

    void init();

    void tick();

private:
    long sonar_sampling;
    LCD_I2C lcd;
    SonarSensor sonar_sensor;
    SmartLighting lights;
    Led led_B;
    BlinkingLed led_C;
};

#endif