#include "Arduino.h"
#include "Display.h"
#include "Product.h"
#include "ButtonImpl.h"
#include "ServoMotorImpl.h"
#include "Machine.h"

#define N_MAX_QUANTITY 50




#define B_UP 2
#define B_DOWN 3
#define B_MAKE 4

Machine::Machine(){
  this->servo = new ServoMotorImpl(10);
  this->display_lcd = new Display();
  this->coffee = new Product(N_MAX_QUANTITY , "Coffee");
  this->tea = new Product(N_MAX_QUANTITY , "Tea");
  this->chocolate = new Product(N_MAX_QUANTITY , "Chocolate");
  this->bUp = new ButtonImpl(B_UP);
  this-> bDown = new ButtonImpl(B_DOWN);
  this->bMake = new ButtonImpl(B_MAKE);
}
