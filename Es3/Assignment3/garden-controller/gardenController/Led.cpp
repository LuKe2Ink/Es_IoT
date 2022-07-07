#include "Led.h"

Led::Led(int pin){
  this->pin = pin;
  pinMode(pin, OUTPUT);
  this->luminosity = 0;
}

void Led::turnOn(){
  digitalWrite(this->pin, HIGH);
  this->luminosity = 1;
}

void Led::turnOff(){
  digitalWrite(this->pin, LOW);
  this->luminosity = 0;
}

void Led::setLuminosity(int value){
    int conv_value = (value) * 63;
    analogWrite(this->pin, conv_value);
    this->luminosity = value;
}

int Led::getLuminosity(){
  return this->luminosity;
}
