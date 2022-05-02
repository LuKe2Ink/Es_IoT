#ifndef __SUGARTASK__
#define __SUGARTASK__

#include "Task.h"

class SugarTask : public Task{
    int pot_pin;
    int current_level;

    public: 
      SugarTask(int pot_pin);
      void init(int period);
      void tick();
        
  };

#endif
