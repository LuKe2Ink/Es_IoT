#ifndef __CHECK__
#define __CHECK__

#include "Task.h"
#include "Machine.h"

#define TEMP_PIN A0 
#define TEMP_MIN 17
#define TEMP_MAX 24

enum testState{
  CHECK,
  TEST
};

class CheckTask : public Task{

    public:
        CheckTask(Machine* machine);
        void moveBackAndForward();
        void checkTemp();
        void init(int period);
        void tick();

        Machine* machine;

   private:
      testState state;
      int count;

};

#endif
