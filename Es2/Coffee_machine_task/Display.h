#ifndef __DISPLAY__
#define __DISPLAY__

#include <WString.h>

#define LCD_ADDR 0x27
#define COLS 20
#define ROWS 4

class Display
{

public:
  Display();
  void setText(String msg);
  void on();
  void off();
};

#endif
