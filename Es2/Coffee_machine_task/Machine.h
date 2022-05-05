#include <NewPing.h>

#ifndef __MACHINE__
#define __MACHINE__

#include "Display.h"
#include "Product.h"
#include "ButtonImpl.h"
#include "ServoMotorImpl.h"
#include "Temp.h"
#include "Pir.h"


#define N_MAX_QUANTITY 50
#define T_OUT 5000L
#define T_MAKING 55

#define B_UP 2
#define B_DOWN 3
#define B_MAKE 4
#define PIR_PIN 5

#define PROD_NUM 3

enum stato{
  WELCOME,
  READY,
  SELECT,
  MAKING,
  WAITING_REMOVING,
  ASSISTANCE,
  SLEEP
};


class Machine {


  public:
    Machine();
    NewPing* sonar;
    Pir* pir;
    ServoMotor* servo ;
    Display* display_lcd ;
    Temp* temp;
    Product* coffee ;
    Product* tea ;
    Product* chocolate ;
    Button* bUp;
    Button* bDown ;
    Button* bMake ;
    stato state;
};

#endif
