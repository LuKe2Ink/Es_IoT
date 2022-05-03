#ifndef __SELECTION__
#define __SELECTION__

#include "Task.h"
#include "Product.h"
#include "Machine.h"


class SelectionTask: public Task {

    Machine* machine;
    Product* product[PROD_NUM];
    int unaviableProd;
    int selectedProd;
    int currentMillis;
    int startMillis;
    int pos;
    
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
    void disableInterruptButton();
};

#endif
