#ifndef __TEMP__
#define __TEMP__

#include <WString.h>

class Temp
{

  public:
    Temp(int pin);
    int getTemp();

  private:
    int pin;
};

#endif
