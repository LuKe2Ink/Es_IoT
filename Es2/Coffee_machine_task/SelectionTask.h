#ifndef __SELECTION__
#define __SELECTION__

#include "Task.h"

class SelectionTask: public Task {

  public:
    SelectionTask(Machine* machine, Product* product);
    Machine* machine;
    Product* product[3];
    int unaviableProd;
    int selectedProd;
    int currentMillis;
    int startMillis;
    int pos;
    
    void init(int period);  
    void tick();

  private:
    void checkSleepMode();
    void incSelect();
    void decSelect();
    void moveServo();
    void makeProduct();
    void startTimer();
};

#endif
