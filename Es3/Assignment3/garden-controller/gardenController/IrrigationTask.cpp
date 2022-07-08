#include "IrrigationTask.h"

IrrigationTask::IrrigationTask(Garden* garden){
  this->garden = garden;
}

void IrrigationTask::init(int period){
  Task::init(period);
}

void IrrigationTask::tick()
{

  switch(this->state){
    case OPERATING:
      if(garden->moveServo){
        
      }
      break;
    case NOT_OPERATING:
      break;
  }
  
}
