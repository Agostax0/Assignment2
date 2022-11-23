#include "BlinkingLed.h"
#include "Arduino.h"
#include "Led.h"
BlinkingLed::BlinkingLed(unsigned short pin)
{
    this->pin = pin;
    this->speed = 1;
    this->currentBrightness = 0;
    pinMode(this->pin, OUTPUT);
    digitalWrite(this->pin,LOW);
}

void BlinkingLed::tick()
{
    if (currentBrightness < 0 || currentBrightness > 255)
    {
        speed = (-1 * speed);
    }
    this->currentBrightness += this->speed;

    analogWrite(this->pin, this->currentBrightness);
}

void BlinkingLed::setSpeed(float speed)
{
    this->speed = speed;
}
void BlinkingLed::switchOff()
{
    digitalWrite(this->pin, LOW);
    this->currentBrightness = 0;
}
void BlinkingLed::switchOn()
{
    digitalWrite(this->pin, HIGH);
    this->currentBrightness = 255;
}

int BlinkingLed::getState(){
    return (this->currentBrightness>0) ? 1 : 0; 
}