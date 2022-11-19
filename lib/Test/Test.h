#include <Arduino.h>
#include "SonarSensor.h"
#include "LightSensor.h"
#include "StepMotor.h"
#include "InfraredSensor.h"
#include "BlinkingLed.h"
#include "Led.h"
#include "Potentiometer.h"
#include "LCD_I2C.h"
#include "Bounce2.h"
#define WL1 5
#define WL2 10
#define WL_MAX 15

#define TH_L 300

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

double distance;
int state;

enum alarmState
{
    NORMAL,
    PRE_ALARM,
    ALARM
};
String stateToString(int state)
{
    switch (state)
    {
    case NORMAL:
        return "NORMAL";
        break;
    case PRE_ALARM:
        return "PRE_ALARM";
        break;
    case ALARM:
        return "ALARM";
        break;
    default:
        return "ERROR";
        break;
    }
}
void print_request(String name, double value)
{
    Serial.print("last" + name + ": ");
    if (name == "state")
    {
        Serial.print(stateToString((int)value));
    }
    else
    {
        Serial.print(value);
    }

    Serial.println();
}
bool range(int value, int expected, int percentage)
{
    double percentage_value = expected * (percentage / 100.0);

    int lower_bound = expected - percentage_value;

    int upper_bound = expected + percentage_value;

    return (value > lower_bound && value < upper_bound) ? true : false;
}
void waitForCenteredPotentiometer()
{
    while (!range(pot.read(), (int)1023 / 2, 5))
    {
        print_request("pot", pot.read());
    }
}
void mapPotentiometerToMotor()
{

    waitForCenteredPotentiometer();

    int last = pot.read();

    while (!button.rose())
    {
        button.update();
        double half = 1023 / 2;
        int read = pot.read();
        if (!range(read, last, 1))
        {
            double mapToDegree;
            short orientation = (last-read < 0) ? 1 : -1;
            mapToDegree = (90.0/half) * (abs((last-read)));
            if(mapToDegree>5){
                motor.moveOfGivenAngle(orientation * (int)mapToDegree);
                last = read;
            }
            

        }
    }

    motor.setAsZeroDegree();
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
void print_state()
{

    state = getState(distance);

    print_request("distance", distance);

    print_request("state", state);

    print_request("lightLevel", lightSensor.getLightLevel());

    print_request("pot", pot.read());

    delay(100);
}
bool first = false;
class Test
{
public:
    Test()
    {
    }

    void init()
    {
        Serial.begin(9600);
        button.attach(5, INPUT);
        button.interval(25);
        lcd.begin();
        lcd.backlight();
    }

    void tick()
    {
        if (!first)
        {
            mapPotentiometerToMotor();
            first = true;
        }
        else
        {
            Serial.println("finished");
        }
        delay(5000);
    }
};