#include "RoutineTask.h"

RoutineTask::RoutineTask(Garden* garden){
  this->garden = garden;
}

void RoutineTask::init(int period){
  Task::init(period);
}

void RoutineTask::tick()
{

  switch(this->garden->state){
    case AUTO:
      if(garden->photoresistor->isLessThenMax()){
        turnOnAllLed();
        if(this->garden->isIrrigationSystemOperating && garden->photoresistor->isLessThenMin()){
          activateIrrigationSystem();
        }
      }else{
        turnOffAllLed();
      }
      break;
    case MANUAL:
      break;
    case ALARM:
      break;
  }
  
}

void RoutineTask::turnOnAllLed(){
  garden->led_a->turnOn();
  garden->led_b->turnOn();
  garden->led_c->turnOn();
  garden->led_d->turnOn();
}

void RoutineTask::turnOffAllLed(){
  garden->led_a->turnOff();
  garden->led_b->turnOff();
  garden->led_c->turnOff();
  garden->led_d->turnOff();
}

void RoutineTask::activateIrrigationSystem(){
  garden->moveServo = true;
}
