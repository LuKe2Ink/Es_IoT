#include "Arduino.h"

#include "Machine.h"


Machine::Machine(){
  this->servo = new ServoMotorImpl(10);
  this->sonar = new NewPing(7, 8, 40);
  this->display_lcd = new Display();
  this->temp = new Temp(3);
  this->pir = new Pir(5);
  this->coffee = new Product(1 , "Coffee");
  this->tea = new Product(1 , "Tea al limone");
  this->chocolate = new Product(1 , "Chocolate");
  this->bUp = new ButtonImpl(B_UP);
  this-> bDown = new ButtonImpl(B_DOWN);
  this->bMake = new ButtonImpl(B_MAKE);
  this->state = state;
}
