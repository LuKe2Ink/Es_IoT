#ifndef __SUGARTASK__
#define __SUGARTASK__

#include "Task.h"
#include "Machine.h"

//class SugarTask : public Task{
//    int pot_pin;
//    int current_level;
//
//    public: 
//      SugarTask(int pot_pin);
//      void init(int period);
//      void tick();
//        
//  };

//class SugarTask: public Task {
//
//  int pot_pin;
//  float currentSugar;
//
//public:
//  SugarTask(int pot_pin);
//  void init(int period);  
//  void tick();
//};
//

class SugarTask: public Task {

  float currentSugar;

public:
  void init(int period);  
  void tick();
  Machine* machine;
};

#endif
