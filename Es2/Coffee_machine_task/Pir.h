#ifndef __PIR__
#define __PIR__

class Pir
{

public:
  Pir(int pin);
  bool isPresent();

private:
  int pin;
};

#endif
