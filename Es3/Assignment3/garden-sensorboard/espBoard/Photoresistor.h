#ifndef __PHOTORESISTOR__
#define __PHOTORESISTOR__

#include <WString.h>

#define MAX_VALUE 5
#define MIN_VALUE 2 

class Photoresistor
{

  public:
    Photoresistor(int pin);
    int getValue();
    bool isLessThenMax();
    bool isLessThenMin();

  private:
    int pin;
};

#endif
