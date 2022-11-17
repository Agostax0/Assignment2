#include <Arduino.h>
#include "SonarSensor.h"
#include "LightSensor.h"
#include "StepMotor.h"
#include "InfraredSensor.h"
#include "BlinkingLed.h"
#include "Led.h"
#include "Potentiometer.h"

#define WL1 5
#define WL2 10
#define WL_MAX 14

#define TH_L 300

SonarSensor sonarSensor = SonarSensor(7, 6);
LightSensor lightSensor = LightSensor(A2);
StepMotor motor = StepMotor(9, 10, 11);
InfraredSensor pirSensor = InfraredSensor(8);
BlinkingLed blinkingLed = BlinkingLed(3);
;
Potentiometer pot = Potentiometer(A0);
Led LedA = Led(2);
Led LedB = Led(4);

double distance;
int state;

enum alarmState
{
  NORMAL,
  PRE_ALARM,
  ALARM
};

void setup()
{
  Serial.begin(9600);
}
void print_request(String name, double value)
{
  Serial.print("current" + name + ": ");
  if (name == "state")
  {
    switch ((int)value)
    {
    case NORMAL:
      Serial.print("NORMAL");
      break;
    case PRE_ALARM:
      Serial.print("PRE_ALARM");
      break;
    case ALARM:
      Serial.print("ALARM");
      break;
    default:
      Serial.print("ERROR");
      break;
    }
  }
  else
  {
    Serial.print(value);
  }

  Serial.println();
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
  if (distance > WL2 && distance < WL_MAX)
  {
    return ALARM;
  }
  return -1;
}
void loop()
{
  double distance = sonarSensor.getDistance(-2);

  state = getState(distance);

  print_request("distance", distance);

  print_request("state", state);

  switch (state)
  {
  case NORMAL:
    // B
    LedB.switchOn();
    LedA.switchOff();
    blinkingLed.switchOff();
    break;
  case PRE_ALARM:
    // BLINKING
    LedB.switchOff();
    LedA.switchOff();
    blinkingLed.switchOn();
    break;
  case ALARM:
    // A
    LedB.switchOff();
    LedA.switchOn();
    blinkingLed.switchOff();
    break;
  default:
    Serial.println("TOO FAR");
    break;
  }

  print_request("light_sensor", lightSensor.getLightLevel());

  if (lightSensor.getLightLevel() < TH_L)
  {
    LedB.switchOff();
    LedA.switchOff();
    blinkingLed.switchOff();
  }

  

  delay(1000);
  /*switch(state){
    case NORMAL:
      normal_smart_lighting();
      break;
    case PRE_ALARM:
      pre_alarm_smart_lighting();
      break;
    case ALARM:
      alarm_smart_lighting();
      break;
    default:
      Serial.println("ERROR");
      break;
  }*/
}

void normal_smart_lighting()
{
}

void pre_alarm_smart_lighting()
{
}

void alarm_smart_lighting()
{
}