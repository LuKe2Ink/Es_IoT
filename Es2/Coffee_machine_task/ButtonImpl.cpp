#include "ButtonImpl.h"
#include "Arduino.h"

ButtonImpl::ButtonImpl(int pin){
  this->pin = pin;
  this->debounceDelay = 50;
  pinMode(pin, INPUT);     
} 
  
bool ButtonImpl::isPressed(){
  return digitalRead(pin) == HIGH;
}

int ButtonImpl::toString(){
  return digitalRead(pin);
}

boolean ButtonImpl::debounce()
{
  boolean state;
  boolean previousState;
  previousState = digitalRead(pin);
  for(int counter=0; counter < debounceDelay; counter++) {
    delay(1);
    state = digitalRead(pin);
    if( state != previousState) {
      counter = 0;
      previousState = state; }
  }
  return state;
}
