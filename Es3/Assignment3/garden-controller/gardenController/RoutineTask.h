#ifndef __ROUTINE__
#define __ROUTINE__

#include "Task.h"
#include "Garden.h"
#include <ArduinoJson.h>

#define RX 2
#define TX 3

class RoutineTask:public Task
{

  Garden *garden;

  public:
    RoutineTask(Garden *garden);
    void init(int period);
    void tick();
    void turnOffAllLed();
    void activateIrrigationSystem();
//    void setData();
    void checkManualControl();
    void checkChanges(JsonObject root);
    void checkAlarmDeactivated(JsonObject root);
    void checkLed1(bool op);
    void checkLed2(bool op);
    void checkLed3(String op);
    void checkLed4(String op);
    void checkIrrigation(String op);
    
  private:
    void turnOnAllLed();
    
};



#endif
