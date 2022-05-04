#include "Arduino.h"

#include "Machine.h"


Machine::Machine(){
  this->servo = new ServoMotorImpl(10);
  this->sonar = new NewPing(7, 8, 40);
  this->display_lcd = new Display();
  this->temp = new Temp(3);
  this->coffee = new Product(N_MAX_QUANTITY , "Coffee");
  this->tea = new Product(N_MAX_QUANTITY , "Tea");
  this->chocolate = new Product(N_MAX_QUANTITY , "Chocolate");
  this->bUp = new ButtonImpl(B_UP);
  this-> bDown = new ButtonImpl(B_DOWN);
  this->bMake = new ButtonImpl(B_MAKE);
  this->state = state;
}
