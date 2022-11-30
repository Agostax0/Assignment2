//TODO add matricola
/* 
  Componenti del gruppo:

  -Agosta Alessandro 


  -Riccardo Tassinari 

*/
#include <Arduino.h>
#include "Util.h"
#include "StepMotor.h"
#include "Potentiometer.h"
#include "SmartLighting.h"
#include "Scheduler.h"
#include "NormalTask.h"
#include "PreAlarmTask.h"
#include "AlarmTask.h"
#include "MsgService.h"
#define TrigPin 7
#define EchoPin 6
#define LightSensorPin A1
#define PotentiometerPin A0
#define ActPin 9
#define DirPin 10
#define PulsePin 11
#define PirPin 8
#define BlinkingPin 3
#define LedAPin 2
#define LedBPin 4
#define ButtonPin 12

Scheduler scheduler;
SonarSensor sonarSensor(TrigPin, EchoPin);
LightSensor lightSensor(LightSensorPin);
StepMotor motor(ActPin, DirPin, PulsePin);
InfraredSensor pirSensor(PirPin);
BlinkingLed blinkingLed(BlinkingPin);
LCD_I2C lcd(0x27, 20, 4);
Potentiometer pot(PotentiometerPin);
Led LedA(LedAPin);
Led LedB(LedBPin);
int buttonPin = ButtonPin;
SmartLighting lights = SmartLighting(LedA, lightSensor, pirSensor);

Task *normal = new NormalTask(sonarSensor, LedB, blinkingLed, lights);
Task *pre_alarm = new PreAlarmTask(sonarSensor, LedB, blinkingLed, lights, lcd);
Task *alarm = new AlarmTask(motor, pot, sonarSensor, LedB, blinkingLed, lights, lcd, buttonPin);

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  MsgService.init();

  normal->init(mcd_period);
  pre_alarm->init(mcd_period);
  alarm->init(mcd_period);
  scheduler.init(mcd_period);
  
  scheduler.addTask(normal);
  scheduler.addTask(pre_alarm);
  scheduler.addTask(alarm);
}

void loop()
{
  scheduler.schedule();
  //delay(500);
}
