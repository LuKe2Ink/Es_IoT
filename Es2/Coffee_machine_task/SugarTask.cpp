#include "SugarTask.h"
#include "Arduino.h"
#define POT A1

SugarTask::SugarTask(Machine* machine){
  this->machine = machine;
  pinMode(POT, INPUT) ;
  this->s = NO_CHECK;
}

void SugarTask::init(int period){
  Task::init(period);   
  currentSugar = 0;
}
  
void SugarTask::tick(){
  switch(this->s){
    case NO_CHECK:
      if(this->machine->state == SELECT){
        this->s = CHECK_SUGAR;
      }
    break;
    case CHECK_SUGAR:
      if(this->machine->state != SELECT){
        this->s = NO_CHECK;
      }
      checkSugar();
    break;
  }
  
}

void SugarTask::checkSugar(){
  int sugarValue = analogRead(POT);
  sugarValue /= 128;
  sugarValue /= 2;
  if(this->currentSugar != sugarValue){
    this->currentSugar = sugarValue;
    this->machine->display_lcd->setText(String(this->currentSugar) + " scoops");
  }
}
