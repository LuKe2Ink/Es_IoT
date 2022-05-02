#ifndef __SELECTION__
#define __SELECTION__

#include "Task.h"
#include "Product.h"
#include "Machine.h"
#include <EnableInterrupt.h>


class SelectionTask: public Task {

  public:
    SelectionTask(Machine* machine);
    Machine* machine;
    Product* product[PROD_NUM];
    int unaviableProd;
    int selectedProd;
    int currentMillis;
    int startMillis;
    int pos;
    
    void init(int period);  
    void tick();
    void checkSleepMode();
    void incSelect();
    void decSelect();
    void moveServo(bool orario);
    void makeProduct();
    void startTimer();
    void disableInterruptButton();
};

#endif
