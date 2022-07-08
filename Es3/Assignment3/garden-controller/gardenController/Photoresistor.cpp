#include "Photoresistor.h"
#include "Arduino.h"

Photoresistor::Photoresistor(int pin)
{
  this->pin = pin;
}

int Photoresistor::getValue()
{
  int value = analogRead(this->pin);
  value /= 128;
  return value;
}

bool Photoresistor::isLessThenMax(){
  if(getValue() < MAX_VALUE){
    return true;
  }
  return false;
}

bool Photoresistor::isLessThenMin(){
  if(getValue() < MIN_VALUE){
    return true;
  }
  return false;
}
