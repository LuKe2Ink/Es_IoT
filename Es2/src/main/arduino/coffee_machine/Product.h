#ifndef __PRODUCT__
#define __PRODUCT__

#include "Arduino.h"

class Product {

  public:
    Product(int quantity);
    void decQuantity();
    void setQuantity(int quantity);
    int getQuantity();
  private:
    int quantity;

};

#endif
