#ifndef __IRRIGATION__
#define __IRRIGATION__

#include "Task.h"
#include "Garden.h"

enum stateIrrigation
{
  OPERATING,
  NOT_OPERATING
};

class IrrigationTask:public Task
{

  Garden *garden;

  public:
    stateIrrigation state;
    IrrigationTask(Garden *garden);
    void init(int period);
    void tick();
  
};



#endif
