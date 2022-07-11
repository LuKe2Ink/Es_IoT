#ifndef __SENSORBOARD__
#define __SENSORBOARD__


#include "Task.h"
#include "Photoresistor.h"
#include "Temp.h"
#include "Led.h"

class SensorBoard{
    public:
        SensorBoard();
        Photoresistor *photoresistor; 
        Temp *temp;
        //Led* led;
};
#endif
