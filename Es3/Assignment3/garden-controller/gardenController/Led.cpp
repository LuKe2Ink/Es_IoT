#include "Led.h"

Led::Led(int pin){
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void Led::turnOn(){
  digitalWrite(this->pin, HIGH);
}

void Led::turnOff(){
  digitalWrite(this->pin, LOW);
}

void Led::setLuminosity(int value){
    int conv_value = (value) * 63;
    analogWrite(this->pin, conv_value);
}