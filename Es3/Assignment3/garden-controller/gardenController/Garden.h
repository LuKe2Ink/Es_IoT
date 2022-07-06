#ifndef __GARDEN__
#define __GARDEN__

#define LED_A 13
#define LED_B 12
#define LED_C 11
#define LED_D 10

#include "Led.h"

enum stato
{
  AUTO,
  MANUAL,
  ALARM
};

class Garden {
    public:
        stato state;
        Led* led_a = new Led(LED_A);
        Led* led_b = new Led(LED_B);
        Led* led_c = new Led(LED_C);
        Led* led_d = new Led(LED_D);
};

#endif