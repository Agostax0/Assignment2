#ifndef __ALARMTASK__
#define __ALARMTASK__

#include "Task.h"
#include "SmartLighting.h"
#include "SonarSensor.h"
#include "BlinkingLed.h"
#include "LCD_I2C.h"
#include "Led.h"
#include "StepMotor.h"
#include "Potentiometer.h"
#include "Bounce2.h"

class AlarmTask : public Task
{
public:
    AlarmTask() {}

    AlarmTask(StepMotor motor, Potentiometer pot, SonarSensor sonar, Led b, BlinkingLed c, SmartLighting lights, LCD_I2C lcd, Bounce btn);

    void init(int period);

    void tick();

private:
    SonarSensor sonar_sensor;
    SmartLighting lights;
    Led led_B;
    BlinkingLed led_C;
    LCD_I2C lcd;
    Potentiometer pot;
    StepMotor mot;
    Bounce btn;

    int last;

    bool manual;

    void automaticInput();

    void manualInput();
};

#endif