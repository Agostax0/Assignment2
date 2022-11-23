#include <Arduino.h>

#include "StepMotor.h"

#include "Potentiometer.h"

#include "Bounce2.h"
#include "SmartLighting.h"
#include "Scheduler.h"
#include "NormalTask.h"
#include "PreAlarmTask.h"
#include "AlarmTask.h"

// TODO MCD for sampling times
// TODO Test Alarm
// TODO Better Blinking Led
// TODO Java side Program
// TODO state diagram

Scheduler scheduler = Scheduler();
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

NormalTask normal = NormalTask(sonarSensor, LedB, blinkingLed, lights);
PreAlarmTask pre_alarm = PreAlarmTask(sonarSensor, LedB, blinkingLed, lights, lcd);
AlarmTask alarm = AlarmTask(motor, pot, sonarSensor, LedB, blinkingLed, lights, lcd, button);
bool once = false;
void setup()
{
  Serial.begin(9600);
  button.attach(5, INPUT);
  button.interval(25);
  lcd.begin();
  lcd.backlight();

  int period = 10;

  normal.init(period);
  pre_alarm.init(period);
  alarm.init(period);
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

    int times = 100;
    for (int j = 0; j < 5; j++)
    {
      unsigned long time0 = millis();
      for (int i = 0; i < times; i++)
      {
        // scheduler.schedule();
        // normal.tick();
        // pre_alarm.tick();
        // alarm.tick();
      }
      unsigned long time1 = millis();
      // Serial.print("Normal Task Time: "); //(ms) 0.18 , 0.2 , 0.18 , 0.2 , 0.18 || avg = 0,188
      //Serial.print("Pre-Alarm Task Time: "); //(ms) 27.26 , 20.42 , 23.07 , 27.28 , 27.48 || avg = 25.10
      //Serial.print("Alarm Task Time: "); //(ms)  || avg = 
      double time_per_tick = (double)(time1 - time0) / times;
      Serial.print(time_per_tick);
      Serial.println();
    }

    once = true;
  }
  else
  {
  }
}
