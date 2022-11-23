#include "AlarmTask.h"
#include "Util.h"

#define alpha(x) ((x) * -36) + 360

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
}

void AlarmTask::init(int period)
{
    Task::init(period);
    this->sonar_sampling = -1;
    this->last = -1;
}

void AlarmTask::tick()
{
    if (getState(sonar_sensor.getDistance(-2)) == ALARM || 1)
    {

        if (sonar_sampling == -1)
        {
            sonar_sampling = millis();
        }
        else
        {
            if ((millis() - sonar_sampling) > PE_alarm)
            {
                this->sonar_sensor.calcDistance(-2);
                sonar_sampling = -1;
                Serial.println("Sampled in ALARM");
            }
        }
        this->lights.turnOff();

        if (this->led_B.getState())
        {
            this->led_B.switchOff();
        }

        if (!this->led_C.getState())
        {
            this->led_C.switchOn();
        }

        lcd.clear();

        lcd.setCursor(0, 0);

        lcd.print("ALARM");

        lcd.setCursor(10, 0);

        lcd.print(sonar_sensor.getDistance(-2));

        this->btn.update();

        bool change = this->btn.rose();

        if (!this->manual && change)
        {                        // manual=false && button was pressed
            this->manual = true; // activate manual mode
        }
        else if (this->manual && change)
        {                         // manual=true && button was pressed
            this->manual = false; // deactivate manual mode
        }
        else if (this->manual && !change)
        { // manual=true && button was not pressed
            // actual manual handling

        }
        else
        { // this is the 00 case in the truth table -> the automatic handling
            this->automaticInput();
        }
    }
    else
    {
        sonar_sampling = -1;
        this->mot.setSteps(0); // stops from getting unwanted steps from pregress alarms
        this->manual = false;
    }
}

void AlarmTask::automaticInput()
{
    if (!this->mot.getSteps()) // controls if this command was already called and issued a movement to the motor
    {
        int alpha_value = alpha(this->sonar_sensor.getDistance(-2)) - 90; // the motor knows values from -90 to +90 degrees

        this->mot.moveToGivenAngle(alpha_value);
    }
    else // if the motor has some steps to take
    {
        this->mot.tick_step_buffer();
    }
}

void AlarmTask::manualInput()
{
    double half = 1023 / 2;
    int read = this->pot.read();
    if (!range(read, (last==-1) ? read : last, 1)) //for the first iteration last = read -> always true
    {
        double mapToDegree;
        short orientation = (last - read < 0) ? 1 : -1;
        mapToDegree = (90.0 / half) * (abs((last - read)));
        if (mapToDegree > 5)
        { // 5 being the 1% of the average read of the potentiometer, otherwise the motor was called for a less than doable degree
            this->mot.moveOfGivenAngle(orientation * (int)mapToDegree);
            last = read;
        }
    }
}