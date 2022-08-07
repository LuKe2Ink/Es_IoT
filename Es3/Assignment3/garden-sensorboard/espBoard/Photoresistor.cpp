#include "Photoresistor.h"
#include "Arduino.h"

Photoresistor::Photoresistor(int pin)
{
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
}

int Photoresistor::getValue()
{
  int value = analogRead(this->pin);
  value /= 128;
  // Serial.println(value);
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
