#include "Photoresistor.h"
#include "Arduino.h"

int Photoresistor::getValue()
{
  return this->value;
}

bool Photoresistor::isLessThenMax(){
  return this->getValue() < MAX_VALUE;
}

bool Photoresistor::isLessThenMin(){
  return this->getValue() < MIN_VALUE;
}


void Photoresistor::setValue(int v){
  this->value = v;
}