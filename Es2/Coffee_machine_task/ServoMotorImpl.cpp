#include <ServoTimer2.h>
#include "ServoMotorImpl.h"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl(int pin){
  this->pin = pin;  
  this->pos = 750;
} 

void ServoMotorImpl::on(){
  servo.attach(pin);    
}

void ServoMotorImpl::moveServo(bool orario){
  on();
  for (int i = MIN_PULSE_WIDTH; i < MAX_PULSE_WIDTH; i++) {
    servo.write(pos);      
    delay(6);            
    pos += orario ? 1 : -1;
  }  
  off();            
}

void ServoMotorImpl::off(){
  servo.detach();    
}
