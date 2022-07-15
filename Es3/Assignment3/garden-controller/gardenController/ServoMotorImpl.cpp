#include <ServoTimer2.h>
#include "ServoMotorImpl.h"
#include "Arduino.h"

long servointerval = 2;
long previousMillis = 0;

long elapsed_time = 0;

ServoMotorImpl::ServoMotorImpl(int pin)
{
  this->pin = pin;
  this->pos = 750;
}

void ServoMotorImpl::on()
{
  this->servo.attach(this->pin);
}

void ServoMotorImpl::moveServo()
{
  on();
  previousMillis = millis();
  for (int i = MIN_PULSE_WIDTH; i < MAX_PULSE_WIDTH;)
  {
    unsigned long servoMillis = millis();

     if(servoMillis - previousMillis > servointerval)
        {
         previousMillis = servoMillis;
         this->servo.write(pos);
         pos += 1; // da cambiare
         i++;
        }
  }
  off();
}

void ServoMotorImpl::off()
{
  this->servo.detach();
  this->isIrrigationSystemOperating = false;
}
