#ifndef __ROUTINE__
#define __ROUTINE__

#include "Task.h"
#include "Garden.h"
#include <SoftwareSerial.h>

#define RX 2
#define TX 3

class RoutineTask:public Task
{

  Garden *garden;

  public:
    RoutineTask(Garden *garden);
    void init(int period);
    void tick();
    void turnOffAllLed();
    void activateIrrigationSystem();
    void setData();
  private:
    void turnOnAllLed();
    
};



#endif
