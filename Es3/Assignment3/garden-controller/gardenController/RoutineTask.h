#ifndef __ROUTINE__
#define __ROUTINE__

#include "Task.h"
#include "Garden.h"

class RoutineTask:public Task
{

  Garden *garden;

  public:
    RoutineTask(Garden *garden);
    void init(int period);
    void tick();
    void turnOnAllLed();
    void turnOffAllLed();
    void activateIrrigationSystem();
  
};



#endif
