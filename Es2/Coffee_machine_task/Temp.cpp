#include "Temp.h"
#include "Arduino.h"

Temp::Temp(int pin){
  this->pin = pin;    
} 
  
int Temp::getTemp(){
  return (analogRead(this->pin)*0.48828125);
}
