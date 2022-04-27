#include "Product.h"
#include "Arduino.h"

Product::Product(int quantity){
  this->quantity = quantity;
}

void Product::decQuantity(){
  this->quantity--;
}

void Product::setQuantity(int quantity){
  this->quantity = quantity;
}

bool Product::isNotAveable(){
  return this->quantity == 0;
}

int Product::getQuantity(){
  return this->quantity;
}
