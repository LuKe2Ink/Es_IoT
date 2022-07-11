#ifndef __PHOTORESISTOR__
#define __PHOTORESISTOR__

#include <WString.h>

#define MAX_VALUE 5
#define MIN_VALUE 2 

class Photoresistor
{

  public:
    int getValue();
    void setValue(int v);
    bool isLessThenMax();
    bool isLessThenMin();
    int value;

};

#endif
