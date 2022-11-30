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


class AlarmTask : public Task
{
public:
    AlarmTask() {}

    AlarmTask(StepMotor motor, Potentiometer pot, SonarSensor sonar, Led b, BlinkingLed c, SmartLighting lights, LCD_I2C lcd, int btn);

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
    int btn;

    int last = -1;
    int serial_last = -1;

    bool manual;
    /* Automatic input, rules how much the motor should move to get back to PRE-ALARM levels */
    void automaticInput();
    /* Manual input, dictated by the potentiometer movement */
    void manualInput();
    /* Serial input, dictated by the serial-side slider movement */
    void serialInput(int value);
};

#endif