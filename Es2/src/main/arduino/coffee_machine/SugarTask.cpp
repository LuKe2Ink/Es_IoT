#include "SugarTask.h"
#include "Arduino.h"
  
void SugarTask::init(int period){
  Task::init(period);   
  currentSugar = 0;
}
  
void SugarTask::tick(){
  int sugarValue = analogRead(A0);
  sugarValue /= 128;
  sugarValue /= 2;
  if(this->currentSugar != sugarValue){
    this->currentSugar = sugarValue;
    Serial.print(this->currentSugar);
    Serial.println(" cucchiaini di zucchero");
  }
}
