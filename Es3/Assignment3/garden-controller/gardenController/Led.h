#ifndef __LED__
#define __LED__

#include "Arduino.h"

class Led
{
    public:
        int pin;
        Led(int pin);
        void turnOn();
        void turnOff();
        void setLuminosity(int value);
};

#endif