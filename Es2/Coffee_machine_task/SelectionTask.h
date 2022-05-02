#ifndef __SELECTION__
#define __SELECTION__

#include "Task.h"
#include "Product.h"
#include "Machine.h"


class SelectionTask: public Task {

  public:
    SelectionTask(Machine* machine);
    static Machine* machine;
    static Product* product[PROD_NUM];
    static int unaviableProd;
    static int selectedProd;
    int currentMillis;
    static int startMillis;
    int pos;
    
    void init(int period);  
    void tick();
    void checkSleepMode();
    static void incSelect();
    static void decSelect();
    static void makeProduct();
    void moveServo(bool orario);
    static void startTimer();
    void disableInterruptButton();
};

#endif
