#ifndef __AWAKETASK__
#define __AWAKETASK__

#include "Task.h"
#include "Machine.h"

class AwakeTask: public Task {

public:
  AwakeTask(Machine* machine);
  void init(int period);  
  void tick();
  Machine* machine;
};

#endif
