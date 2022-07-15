#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

class ServoMotor
{

public:
  virtual void moveServo() = 0;
  virtual void setSpeedServo(int speedLevel) = 0;

private:
  virtual void off() = 0;
  virtual void on() = 0;
};

#endif
