#include "BlinkingLed.h"

BlinkingLed::BlinkingLed(const unsigned short pin){
    this->pin = pin;
    this->speed = 1;
    this->currentBrightness = 0;
    pinMode(this->pin,OUTPUT);
}

void BlinkingLed::switchOff(){
    digitalWrite(this->pin,LOW);
    this->currentBrightness = 0;
}

void BlinkingLed::switchOn(){
    digitalWrite(this->pin,HIGH);
    this->currentBrightness = 255;
}

void BlinkingLed::setSpeed(short speed){
    this->speed = speed;
}

void BlinkingLed::tick(){
    if(currentBrightness < 0 || currentBrightness > 255){
        speed = (-1 * speed);
    }
    this->currentBrightness+=this->speed;

    analogWrite(this->pin,this->currentBrightness);
}

