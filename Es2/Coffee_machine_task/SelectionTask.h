#ifndef __SELECTION__
#define __SELECTION__

#include "Task.h"
#include "Product.h"
#include "Machine.h"
#include "MsgService.h"



class SelectionTask: public Task {
  
    Msg* service;
    Machine* machine;
    Product* product[PROD_NUM];
    int unaviableProd;
    int selectedProd;
    unsigned long currentMillis;
    unsigned long startMillis;
    int pos;
    unsigned long idleMillis;
    
  public:
    SelectionTask(Machine* machine);
    void init(int period);  
    void tick();
    void checkSleepMode();
    void incSelect();
    void decSelect();
    void makeProduct();
    void moveServo(bool orario);
    void startTimer();
    void machineOn();
    void disableInterruptButton();
    boolean debounce(int pin);
    static void awake();

  private:
    int countIdle;
};

#endif
