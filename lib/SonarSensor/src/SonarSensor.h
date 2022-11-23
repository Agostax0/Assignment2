#ifndef __SONARSENSOR__
#define __SONARSENSOR__

class SonarSensor
{
public:
    SonarSensor(){}

    SonarSensor(unsigned short TrigPin, unsigned short EchoPin);

    double getDistance(short powerOfTen){
        if(this->measured_distance == -1){
            this->calcDistance(powerOfTen);
        }
        return this->measured_distance;
    }
    void calcDistance(short powerOfTen);

private:
    unsigned short TrigPin;
    unsigned short EchoPin;
    double measured_distance;

    
};

#endif