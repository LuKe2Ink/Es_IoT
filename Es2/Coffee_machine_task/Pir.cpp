#include "Pir.h"
#include "Arduino.h"

Pir::Pir(int pin){
  this->pin = pin;
    pinMode(this->pin, INPUT);
  for(int i = 0; i < 10; i++){
    delay(1000);
  }
}

bool Pir::isPresent(){
    return digitalRead(this->pin) == HIGH;
}
