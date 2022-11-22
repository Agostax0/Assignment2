#ifndef __SONARSENSOR__
#define __SONARSENSOR__

class SonarSensor
{
public:
    SonarSensor(){}

    SonarSensor(unsigned short TrigPin, unsigned short EchoPin);

    double getDistance( short powerOfTen);

private:
    unsigned short TrigPin;
    unsigned short EchoPin;
};

#endif