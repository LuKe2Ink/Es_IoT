#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

class ServoMotor {

public:
  virtual void on() = 0;
  virtual void setPosition(int angle) = 0;
  virtual void off() = 0;
};

#endif
