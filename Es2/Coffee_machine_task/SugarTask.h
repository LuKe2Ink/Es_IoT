#ifndef __SUGARTASK__
#define __SUGARTASK__

#include "Task.h"
#include "Machine.h"

enum sugarState
{
  NO_CHECK,
  CHECK_SUGAR
};

class SugarTask : public Task
{

  float currentSugar;

public:
  SugarTask(Machine *machine);
  void init(int period);
  void tick();
  void checkSugar();
  Machine *machine;

private:
  sugarState s;
};

#endif
