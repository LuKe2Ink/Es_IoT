#ifndef __BUTTONIMPL__
#define __BUTTONIMPL__

#include "Button.h"
#include "Arduino.h"

class ButtonImpl: public Button {
 
public: 
  ButtonImpl(int pin);
  bool isPressed();
  int toString();

private:
  int pin;

};

#endif
