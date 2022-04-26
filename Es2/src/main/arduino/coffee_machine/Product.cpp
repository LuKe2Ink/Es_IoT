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

int Product::getQuantity(){
  return this->quantity;
}
