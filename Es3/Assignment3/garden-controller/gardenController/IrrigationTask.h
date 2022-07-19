#ifndef __IRRIGATION__
#define __IRRIGATION__

#include "Task.h"
#include "Garden.h"

#define IRRIGATION_SLEEP_TIME 60000

class IrrigationTask:public Task
{

  Garden *garden;

  public:
    IrrigationTask(Garden *garden);
    void init(int period);
    void tick();
    
  
};



#endif
