#include "SonarTask.h"
#include "SonarSensor.cpp"

SonarTask::SonarTask(unsigned short TrigPin, unsigned short EchoPin){
    this->sensor = SonarSensor(TrigPin, EchoPin);
}

void SonarTask::init(){

}

void SonarTask::tick(){

}