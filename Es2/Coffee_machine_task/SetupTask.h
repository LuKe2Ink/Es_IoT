#ifndef __SETUP__
#define __SETUP__ 

#include "Task.h"

class SetupTask : public Task {
  
    public: 
      SetupTask();
      void init(int period);
      void tick();
  };

#endif
