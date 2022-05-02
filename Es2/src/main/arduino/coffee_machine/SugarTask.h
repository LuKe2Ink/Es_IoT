#ifndef __SUGARTASK__
#define __SUGARTASK__

#include "Task.h"

class SugarTask: public Task {

  float currentSugar;

public:

  void init(int period);  
  void tick();
};

#endif
