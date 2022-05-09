#ifndef __DISPLAY__
#define __DISPLAY__

#include <WString.h>

class Display {

  public:
    Display();
    void setText(String msg);
    void on();
    void off();

};

#endif
