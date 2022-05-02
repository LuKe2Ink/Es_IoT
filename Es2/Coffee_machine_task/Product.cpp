#include "Product.h"
#include "Arduino.h"

Product::Product(int quantity, String productName){
  this->quantity = quantity;
  this -> productName = productName;
}

void Product::decQuantity(){
  this->quantity--;
}

void Product::setQuantity(int quantity){
  this->quantity = quantity;
}

bool Product::isNotAviable(){
  return this->quantity == 0;
}

int Product::getQuantity(){
  return this->quantity;
}

String Product::toString(){
    return this-> productName;
  }
