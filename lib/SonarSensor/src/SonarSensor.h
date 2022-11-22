#ifndef __SONARSENSOR__
#define __SONARSENSOR__
const float vs = 331.5 + 0.6 * 20;
class SonarSensor
{
public:
    SonarSensor(const unsigned short TrigPin, const unsigned short EchoPin);

    double getDistance(const short powerOfTen);

private:
    unsigned short TrigPin;
    unsigned short EchoPin;
};

#endif