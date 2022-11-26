#include "AlarmTask.h"
#include "Util.h"

#define alpha(x) 100 - ((x)-5) * 10;

AlarmTask::AlarmTask(StepMotor motor, Potentiometer pot, SonarSensor sonar, Led b, BlinkingLed c, SmartLighting lights, LCD_I2C lcd, Bounce button)
{
    this->mot = motor;
    this->pot = pot;
    this->sonar_sensor = sonar;
    this->led_B = b;
    this->led_C = c;
    this->lights = lights;
    this->lcd = lcd;
    this->btn = button;

    this->pot_last_read = false;
}

void AlarmTask::init(int period)
{
    Task::init(period);
    this->pot_last_read = false;
    this->manual = false;
}

void AlarmTask::tick()
{
    this->sonar_sensor.calcDistance(cm);
    if (getState(sonar_sensor.getDistance(cm)) == ALARM)
    {
        this->lights.turnOff();

        this->led_B.switchOff();

        this->led_C.switchOn();

        lcd.clear();

        lcd.setCursor(0, 0);

        lcd.print("ALARM");

        lcd.setCursor(10, 0);

        lcd.print(sonar_sensor.getDistance(cm));

        bool change = digitalRead(12);

        if (!this->manual && change)
        {                        // manual=false && button was pressed
            this->manual = true; // activate manual mode
            Serial.println("Activating Manual Mode");
            this->mot.reset();
        }
        else if (this->manual && change)
        {                         // manual=true && button was pressed
            this->manual = false; // deactivate manual mode
            Serial.println("DeActivating Manual Mode");
            this->mot.reset();
            this->pot_last_read = -1;
        }
        else if (this->manual && !change)
        { // manual=true && button was not pressed
            // actual manual handling
            this->manualInput();
            this->mot.tick();
        }
        else
        { // this is the 00 case in the truth table -> the automatic handling
            this->automaticInput();
        }
    }
    else
    {
        Serial.println("NOT ALARM SITUATION");
        this->manual = false;
        this->pot_last_read = false;

        if (digitalRead(12))
        {
            this->mot.reset();
        }

        this->mot.resetToZero();
    }
}

void AlarmTask::automaticInput()
{

    if (!this->mot.getStepsLeft()) // controls if this command was already called and issued a movement to the motor
    {
        int alpha_value = alpha(this->sonar_sensor.getDistance(cm));
        this->mot.moveOfGivenSteps(alpha_value);
    }
    else // if the motor has some steps to take
    {
        this->mot.tick();
    }
}

void AlarmTask::manualInput()
{

    Serial.println("Manual");

    double half = 1023 / 2;
    int read = this->pot.read();
    last = (!pot_last_read) ? read : last;
    if (!range(read, last, 1)) // for the first iteration last = read -> always true
    {
        //Serial.println("\t outside of range");
        double mapToDegree;
        short orientation = (last - read < 0) ? 1 : -1;
        mapToDegree = (90.0 / half) * (abs((last - read)));
        if (mapToDegree > 5)
        { // 5 being the 1% of the average read of the potentiometer, otherwise the motor was called for a less than doable degree
            //Serial.println("\t\t move of: " + String(orientation * (int)mapToDegree));
            this->mot.moveOfGivenAngle(orientation * (int)mapToDegree);
            last = read;
        }
    }
}