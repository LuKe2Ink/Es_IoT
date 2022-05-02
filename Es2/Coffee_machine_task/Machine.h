#ifndef __MACHINE__
#define __MACHINE__

class Machine {
  public:
    Machine();
    ServoMotor* servo ;
    Display* display_lcd ;
    Product* coffee ;
    Product* tea ;
    Product* chocolate ;
    Button* bUp;
    Button* bDown ;
    Button* bMake ;
};

#endif
