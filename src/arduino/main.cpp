#include <Arduino.h>

#include "StepMotor.h"

#include "Potentiometer.h"

#include "Bounce2.h"
#include "SmartLighting.h"
#include "Scheduler.h"
#include "NormalTask.h"
#include "PreAlarmTask.h"
// TODO divide into tasks
// TODO MCD for sampling times
// TODO Test Blinking Led
// TODO Test PiR sensor
// TODO Java side Program

// REMEMBER during ALARM phase the Blinking Led speed to blink every 2 sec is 0,255


Scheduler scheduler = Scheduler();
SonarSensor sonarSensor = SonarSensor(7, 6);
LightSensor lightSensor = LightSensor(A2);
StepMotor motor = StepMotor(9, 10, 11);
InfraredSensor pirSensor = InfraredSensor(8);
BlinkingLed blinkingLed = BlinkingLed(3);
LCD_I2C lcd(0x27, 20, 4);
Potentiometer pot = Potentiometer(A0);
Led LedA = Led(2);
Led LedB = Led(4);
Bounce button = Bounce();

SmartLighting lights = SmartLighting(LedA, lightSensor, pirSensor);

NormalTask normal = NormalTask(sonarSensor, LedB, blinkingLed, lights);
PreAlarmTask pre_alarm = PreAlarmTask(sonarSensor,LedB,blinkingLed,lights,lcd);
bool once = false;
void setup()
{
  Serial.begin(9600);
  button.attach(5, INPUT);
  button.interval(25);
  lcd.begin();
  lcd.backlight();
  // scheduler.init();
  // scheduler.addTask(normal);

}

void loop()
{
  // scheduler.schedule();
  if (!once)
  {
    normal.init();
    pre_alarm.init();
    int times = 1000;
    unsigned long time0 = millis();
    for (int i = 0; i < times; i++)
    {
      //normal.tick();
      pre_alarm.tick();
    }
    unsigned long time1 = millis();
    //Serial.print("Normal Task Time: "); //47.33 ms
    //Serial.print("Pre-Alarm Task Time: "); //104.00 ms
    Serial.print((float)(time1 - time0) / times);
    Serial.println();

    once = true;
  }
  else
  {
  }
}
