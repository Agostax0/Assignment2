#include <Arduino.h>
#include "Scheduler.h"
#include "SonarTask.h"
#include "SonarSensor.h"

Scheduler scheduler;
SonarTask *sonar = new SonarTask(4,5);

void setup() {
  scheduler = Scheduler(); 
  scheduler.addTask(sonar);
}

void loop() {
  scheduler.schedule();
}