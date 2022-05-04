#include "SelfTestTask.h"
#include "Arduino.h"

#define T_CHECK 10000

SelfTestTask::SelfTestTask(Machine* machine){
  this->machine = machine;
}

void SelfTestTask::init(int period){
  Task::init(period);   
  startTimeSelfTest = millis();
}
  
void SelfTestTask::tick(){
  currentTimeSelfTest = millis();
  if(currentTimeSelfTest - startTimeSelfTest > T_CHECK){
    machine->servo->on();
    for (int pos = 0; pos < 180; pos += 1){
      machine->servo->setPosition(pos);         
      delay(T_MAKING);            
    }
    machine->servo->off();
    Serial.println(machine->temp->getTemp());
    startTimeSelfTest = millis();
  }
}
