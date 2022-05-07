#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

class ServoMotor {

public:
  virtual void moveServo(bool orario) = 0;

private:
  virtual void off() = 0;
  virtual void on() = 0;
  
};

#endif
