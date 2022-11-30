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
/* This method sets the led brightness according */
void BlinkingLed::tick()
{
    if (currentBrightness <= 0 || currentBrightness > 255)
    {
        speed = (-1 * speed);
    }
    this->currentBrightness += this->speed;

    this->currentBrightness = (this->currentBrightness < 0) ? 0 : this->currentBrightness; 

    analogWrite(this->pin, this->currentBrightness);
}
/* This method sets the speed of which it should increase in brightness */
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