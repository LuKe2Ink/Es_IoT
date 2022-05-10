#ifndef __UPDATEMESSAGE__
#define __UPDATEMESSAGE__

#include "Arduino.h"

class UpdateMessage {

    int coffeeMsg;
    int teaMsg;
    int chocolateMsg;
    String statoMsg;
    
  public:
    UpdateMessage(int coffee, int tea, int chocolate, String stato);
    void setMessage(int coffee, int tea, int chocolate, String stato);
    String toJson();
};

#endif
