//#include "MsgService.h"
#include "Display.h"
#include "Product.h"
#include "ButtonImpl.h"
#include "ServoMotorImpl.h"
#include <EnableInterrupt.h>

#include "Scheduler.h"




#define N_MAX_QUANTITY 50

#define B_UP 2
#define B_DOWN 3
#define B_MAKE 4

//#define B_UP 7
//#define B_DOWN 6
//#define B_MAKE 5
#define PIR_PIN 7
#define TEMP_PIN A0 
#define TRIG 13
#define ECHO 12
#define POT A1

#define T_OUT 5000L
#define T_MAKING 55

#define PROD_NUM 3

#define ORARIO 1
#define ANTI_ORARIO -1


enum state{
  WELCOME,
  READY,
  SELECT,
  MAKING
}state;

struct Machine {
  ServoMotor* servo = new ServoMotorImpl(10);
  Display* display_lcd = new Display();
  Product* coffee = new Product(N_MAX_QUANTITY , "Coffee");
  Product* tea = new Product(N_MAX_QUANTITY , "Tea");
  Product* chocolate = new Product(N_MAX_QUANTITY , "Chocolate");
  Button* bUp = new ButtonImpl(B_UP);
  Button* bDown= new ButtonImpl(B_DOWN);
  Button* bMake = new ButtonImpl(B_MAKE);
  
};

void setup() {
  Machine coffee_machine;
}

void loop() {

}
