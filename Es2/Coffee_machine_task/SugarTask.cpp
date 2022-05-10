//#include "SugarTask.h" 
//#include "Arduino.h"
//
//SugarTask::SugarTask(int pin){
//    this->pot_pin = pin;
//    pinMode(this->pot_pin, INPUT) ;
//    this->current_level = analogRead(this->pot_pin);
//  }
//
//void SugarTask::init(int period){
//  Task::init(period);
//  }
//
//void SugarTask::tick(){
//    int newValue = analogRead(this->pot_pin);
//    if(!(this->current_level - 40 < newValue && this->current_level + 40 > newValue)){
//        //Serial.println("We have a difference");
//        this->current_level = newValue;
//      }
//      
//  }
#include "SugarTask.h"
#include "Arduino.h"
#define POT A1

//SugarTask::SugarTask(int pin){
//    this->pot_pin = pin;
//    pinMode(this->pot_pin, INPUT) ;
//  
//  }
// 
//void SugarTask::init(int period){
//  Task::init(period);   
//  currentSugar = 0;
//}
//  
//void SugarTask::tick(){
//  int sugarValue = analogRead(A1);
//  sugarValue /= 128;
//  sugarValue /= 2;
//  if(this->currentSugar != sugarValue){
//    this->currentSugar = sugarValue;
//    //Serial.print(this->currentSugar);
//    //Serial.println(" cucchiaini di zucchero");
//  }
//}

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
    //Serial.print(this->currentSugar);
    //Serial.println(" cucchiaini di zucchero");
    //this->machine->display_lcd->setText(String(this->currentSugar) + " scoops");
  }
}
