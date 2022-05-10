#include "Arduino.h"

#include "Machine.h"


Machine::Machine(){
  this->servo = new ServoMotorImpl(SERVO_PIN);
  this->sonar = new NewPing(TRIG_PIN, ECHO_PIN, SONAR_DISTANCE);
  this->display_lcd = new Display();
  this->temp = new Temp(TEMP_PIN);
  this->pir = new Pir(PIR_PIN);
  this->coffee = new Product(30 , "Coffee");
  this->tea = new Product(N_MAX_QUANTITY , "Tea al limone");
  this->chocolate = new Product(N_MAX_QUANTITY , "Chocolate");
  this->bUp = new ButtonImpl(B_UP);
  this-> bDown = new ButtonImpl(B_DOWN);
  this->bMake = new ButtonImpl(B_MAKE);
  this->state = state;
  this->checkDone = 0;
  this->lastMove = false;
}
