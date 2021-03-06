#ifndef __LED__
#define __LED__

#include "Arduino.h"

#define MAX_LUMINOSITY 4
#define MIN_LUMINOSITY 0

class Led
{
    public:
        int pin;
        int luminosity;
        Led(int pin);
        void turnOn();
        void turnOff();
        void setLuminosity(int value);
        int getLuminosity();
};

#endif
