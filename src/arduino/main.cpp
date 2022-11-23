#include <Arduino.h>

#include "StepMotor.h"

#include "Potentiometer.h"

#include "Bounce2.h"
#include "SmartLighting.h"
#include "Scheduler.h"
#include "NormalTask.h"
#include "PreAlarmTask.h"
#include "AlarmTask.h"
// TODO divide into tasks
// TODO MCD for sampling times
// TODO Test Blinking Led
// TODO Test PiR sensor
// TODO Java side Program


// REMEMBER during ALARM phase the Blinking Led speed to blink every 2 sec is 0,255


Scheduler scheduler = Scheduler();
SonarSensor sonarSensor(7, 6);
LightSensor lightSensor(A2);
StepMotor motor (9, 10, 11);
InfraredSensor pirSensor (8);
BlinkingLed blinkingLed (3);
LCD_I2C lcd(0x27, 20, 4);
Potentiometer pot (A0);
Led LedA (2);
Led LedB (4);
Bounce button = Bounce();

SmartLighting lights = SmartLighting(LedA, lightSensor, pirSensor);

Task* normal = new  NormalTask(sonarSensor, LedB, blinkingLed, lights);
Task* pre_alarm = new PreAlarmTask(sonarSensor,LedB,blinkingLed,lights,lcd);
Task* alarm = new AlarmTask(motor,pot,sonarSensor,LedB,blinkingLed,lights,lcd,button);
bool once = false;
void setup()
{
  Serial.begin(9600);
  button.attach(5, INPUT);
  button.interval(25);
  lcd.begin();
  lcd.backlight();

  int period = 10;

  normal->init(period);
  pre_alarm->init(period);
  alarm->init(period);
  // scheduler.init(period);
  // scheduler.addTask(normal);
  // scheduler.addTask(pre_alarm);
  // scheduler.addTask(alarm);

}

void loop()
{
  // scheduler.schedule();
  if (!once)
  {

    int times = 1000;
    unsigned long time0 = millis();
    for (int i = 0; i < times; i++)
    {
      //scheduler.schedule();
      normal->tick();
      
    }
    unsigned long time1 = millis();
    Serial.print("Normal Task Time: "); //47.33 ms
    //Serial.print("Pre-Alarm Task Time: "); //104.00 ms
    Serial.print(time1 - time0);
    Serial.println();

    once = true;
  }
  else
  {
  }
}
