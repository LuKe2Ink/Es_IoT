#ifndef __SERVOMOTORIMPL__
#define __SERVOMOTORIMPL__

#include "ServoMotor.h"
#include "ServoTimer2.h"

class ServoMotorImpl : public ServoMotor
{

public:
  ServoMotorImpl(int pin);
  void moveServo();
  void setSpeedServo(int speedLevel);

private:
  int pin;
  int pos;
  ServoTimer2 servo;
  void off();
  void on();
};

#endif
