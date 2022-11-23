#include <Arduino.h>


#include "Util.h"


double distance;
int state;


#include "Potentiometer.h"

Potentiometer pot(A0);
Bounce button = Bounce();

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

void waitForCenteredPotentiometer()
{
    while (!range(pot.read(), (int)1023 / 2, 5))
    {
        //lcd.print();
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
                short orientation = (last - read < 0) ? 1 : -1;
                mapToDegree = (90.0 / half) * (abs((last - read)));
                if (mapToDegree > 5)
                { // 5 being the 1% of the average read of the potentiometer, otherwise the motor was called for a less than doable degree
                    motor.moveOfGivenAngle(orientation * (int)mapToDegree);
                    last = read;
                }
            }
    }

    motor.setAsZeroDegree();
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
        
    }
};