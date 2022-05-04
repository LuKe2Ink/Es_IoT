#ifndef __SELFTESTTASK__
#define __SELFTESTTASK__

#include "Task.h"
#include "Machine.h"

class SelfTestTask: public Task {

public:
  SelfTestTask(Machine* machine);
  void init(int period);  
  void tick();
  Machine* machine;

  private:
    int startTimeSelfTest;
    int currentTimeSelfTest;
};

#endif
