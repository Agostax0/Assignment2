#include "AlarmTask.h"
#include "Util.h"

#define alpha(x) ((x) * (-18)) + 270

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

    this->once = false;
}

void AlarmTask::init(int period)
{
    Task::init(period);
    this->last = -1;
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

        btn.read();

        this->btn.update();

        bool change = digitalRead(12);

        // Serial.println("Manual: " + String(this->manual) + "\t Button: " + String(digitalRead(12)));

        if (!this->manual && change)
        {                        // manual=false && button was pressed
            this->manual = true; // activate manual mode
            Serial.println("Activating Manual Mode");
        }
        else if (this->manual && change)
        {                         // manual=true && button was pressed
            this->manual = false; // deactivate manual mode
            Serial.println("DeActivating Manual Mode");
        }
        else if (this->manual && !change)
        { // manual=true && button was not pressed
            // actual manual handling
            // Serial.println("Called Manual");
            this->manualInput();
            this->mot.tick();
        }
        else
        { // this is the 00 case in the truth table -> the automatic handling
            // Serial.println("Called Auto");
            this->automaticInput();
        }
    }
    else
    {
        Serial.println("NOT ALARM SITUATION");
        //this->mot.resetSteps(); // stops from getting unwanted steps from pregress alarms
        this->manual = false;
        this->last = -1;

        int stepsLeft = this->mot.getSteps();
        if(stepsLeft!=0){
            if(stepsLeft>0){
                this->mot.tick();
            }
            else{
                Serial.println("Going back");
                this->mot.resetToZero();
                
            }
        }
    }
}

void AlarmTask::automaticInput()
{

    if (!this->mot.getSteps()) // controls if this command was already called and issued a movement to the motor
    {
        int alpha_value = 100 - (this->sonar_sensor.getDistance(cm) - 5) * 10; // alpha(this->sonar_sensor.getDistance(cm)) - 90; // the motor knows values from -90 to +90 degrees
        Serial.println("Given: " + String(this->sonar_sensor.getDistance(cm)) + " im moving by steps: " + String(alpha_value));
        // this->mot.moveOfGivenAngle(alpha_value);
            this->mot.moveOfGivenSteps(alpha_value);
    }
    else // if the motor has some steps to take
    {
        this->mot.tick();
    }
}

void AlarmTask::manualInput()
{
    double half = 1023 / 2;
    int read = this->pot.read();
    if (!range(read, (last == -1) ? read : last, 1)) // for the first iteration last = read -> always true
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
    // Serial.println("Exiting Manual function");
}