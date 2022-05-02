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
//        Serial.println("We have a difference");
//        this->current_level = newValue;
//      }
//      
//  }
#include "SugarTask.h"
#include "Arduino.h"

SugarTask::SugarTask(int pin){
    this->pot_pin = pin;
    pinMode(this->pot_pin, INPUT) ;
  
  }
 
void SugarTask::init(int period){
  Task::init(period);   
  currentSugar = 0;
}
  
void SugarTask::tick(){
  int sugarValue = analogRead(this->pot_pin);
  sugarValue /= 128;
  sugarValue /= 2;
  if(this->currentSugar != sugarValue){
    this->currentSugar = sugarValue;
    Serial.print(this->currentSugar);
    Serial.println(" cucchiaini di zucchero");
  }
}
