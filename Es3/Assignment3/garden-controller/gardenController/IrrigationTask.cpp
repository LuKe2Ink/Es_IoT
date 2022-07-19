#include "IrrigationTask.h"

long initTime;

IrrigationTask::IrrigationTask(Garden* garden){
  this->garden = garden;
}

void IrrigationTask::init(int period){
  Task::init(period);
}

void IrrigationTask::tick()
{

  switch(this->garden->stateIrrigation){
    case OPERATING:
      initTime = millis();
      break;
    case NOT_OPERATING:
      long actualTime = millis();
      if(actualTime - initTime > IRRIGATION_SLEEP_TIME){
        this->garden->stateIrrigation = OPERATING;
      }
      break;
  }
  
}
