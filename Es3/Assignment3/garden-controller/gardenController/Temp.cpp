#include "Temp.h"
#include "Arduino.h"

int Temp::getTemp()
{
  return this->temp;
}

void Temp::setTemp(int t)
{
  this->temp = t;
}
