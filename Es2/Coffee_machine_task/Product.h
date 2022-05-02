#ifndef __PRODUCT__
#define __PRODUCT__

#include "Arduino.h"

class Product {

  public:
    Product(int quantity, String productName);
    void decQuantity();
    void setQuantity(int quantity);
    int getQuantity();
    bool isNotAviable();
    String toString();
  private:
    String productName;
    int quantity;
    

};

#endif
