#include <Arduino.h>
#include "Util.h"
#include "StepMotor.h"

#include "Potentiometer.h"

#include "Bounce2.h"
#include "SmartLighting.h"
#include "Scheduler.h"
#include "NormalTask.h"
#include "PreAlarmTask.h"
#include "AlarmTask.h"



// TODO Test Alarm
// TODO Java side Program
// TODO state diagram

Scheduler scheduler;
SonarSensor sonarSensor(7, 6);
LightSensor lightSensor(A2);
StepMotor motor(9, 10, 11);
InfraredSensor pirSensor(8);
BlinkingLed blinkingLed(3);
LCD_I2C lcd(0x27, 20, 4);
Potentiometer pot(A0);
Led LedA(2);
Led LedB(4);
Bounce button = Bounce();

SmartLighting lights = SmartLighting(LedA, lightSensor, pirSensor);

Task *normal = new NormalTask(sonarSensor, LedB, blinkingLed, lights);
Task *pre_alarm = new PreAlarmTask(sonarSensor, LedB, blinkingLed, lights, lcd);
Task *alarm = new AlarmTask(motor, pot, sonarSensor, LedB, blinkingLed, lights, lcd, button);

void setup()
{
  Serial.begin(9600);
  button.attach(5, INPUT);
  button.interval(25);
  lcd.begin();
  lcd.backlight();

  normal->init(mcd_period);
  pre_alarm->init(mcd_period);
  alarm->init(mcd_period);
  scheduler.init(mcd_period);
  //scheduler.addTask(normal);
  scheduler.addTask(pre_alarm);
  // scheduler.addTask(alarm);
}

void loop()
{
  scheduler.schedule();
}
