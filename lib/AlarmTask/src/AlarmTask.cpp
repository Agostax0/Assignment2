#include "AlarmTask.h"
#include "MsgService.h"
#include "Util.h"

#define alpha(x) 100 - ((x)-5) * 10;

AlarmTask::AlarmTask(StepMotor motor, Potentiometer pot, SonarSensor sonar, Led b, BlinkingLed c, SmartLighting lights, LCD_I2C lcd, int button)
{
    this->mot = motor;
    this->pot = pot;
    this->sonar_sensor = sonar;
    this->led_B = b;
    this->led_C = c;
    this->lights = lights;
    this->lcd = lcd;
    this->btn = button;
    this->manual = false;
}

void AlarmTask::init(int period)
{
    Task::init(period);
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

        bool change = digitalRead(this->btn);

        if (serial)
        {
            lcd.setCursor(0, 3);
            lcd.print("SERIAL");
            serialInput(serial_read);
            this->mot.tick();
        }
        else
        {
            serial_last = -1;
            if (!this->manual && change)
            {                        // manual=false && button was pressed
                this->manual = true; // activate manual mode
                this->mot.reset();
            }
            else if (this->manual && change)
            {                         // manual=true && button was pressed
                this->manual = false; // deactivate manual mode
                this->mot.reset();
                this->last = -1;
            }
            else if (this->manual && !change)
            { // manual=true && button was not pressed
                // actual manual handling
                lcd.setCursor(0, 3);
                lcd.print("MANUAL");
                this->manualInput();
                this->mot.tick();
            }
            else
            { // this is the 00 case in the truth table -> the automatic handling
                lcd.setCursor(0, 3);
                lcd.print("AUTO");
                this->automaticInput();
            }
        }
    }
    else
    {
        if(getState(this->sonar_sensor.getDistance(cm))==NORMAL){
            lcd.clear();
        }
        updateSerial();
        this->manual = false;

        this->mot.resetToZero();
        this->last = -1;
        serial_last = -1;
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
    int potVal = map(this->pot.read(), 0, 1024, 0, 100);

    potVal = 100 - potVal;

    if (last == -1)
    {
        last = potVal;
    }
    
    this->mot.moveOfGivenSteps(last - potVal);

    last = potVal;
}

void AlarmTask::serialInput(int read)
{
    int potVal = map(read, 0, 1024, 0, 100);

    potVal = 100 - potVal;

    if (serial_last == -1)
    {
        serial_last = potVal;
    }

    this->mot.moveOfGivenSteps(serial_last - potVal);

    serial_last = potVal;
}