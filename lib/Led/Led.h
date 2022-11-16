#ifndef __LED__
#define __LED__

#include "Light.h"

class Led : public Light{
    public:
        Led(const unsigned short pin);
        void switchOn();
        void switchOff();
    protected:
        unsigned short pin;
    
};



#endif