#ifndef __UPDATEMESSAGE__
#define __UPDATEMESSAGE__

#include "Arduino.h"

class UpdateMessage
{

  int coffeeMsg;
  int teaMsg;
  int chocolateMsg;
  int checks;
  String statoMsg;

public:
  UpdateMessage(int coffee, int tea, int chocolate, int checks, String stato);
  void setMessage(int coffee, int tea, int chocolate, int checks, String stato);
  String toJson();
};

#endif
