#include "MsgService.h"
#include "Display.h"
#include "Product.h"
#include "ButtonImpl.h"
#include "ServoMotorImpl.h"
#include <EnableInterrupt.h>

enum {
  WELCOME,
  READY,
  SELECT,
  MAKING
}state;

#define N_MAX_QUANTITY 50

#define B_UP 2
#define B_DOWN 3
#define B_MAKE 4

//#define B_UP 7
//#define B_DOWN 6
//#define B_MAKE 5
//#define PIR_PIN 4
#define TEMP_PIN A0 
#define TRIG 13
#define ECHO 12
#define POT A1

#define T_OUT 5000L
#define T_MAKING 55



ServoMotor* servo;
Display* display_lcd;
Product* coffee;
Product* tea;
Product* chocolate;
Button* bUp;
Button* bDown;
Button* bMake;
int selectedProduct;
Product* productList[3];
unsigned long startMillis;
unsigned long currentMillis;
int pos;   
int delta;

void setup() {
  /*MsgService.init();*/
  Serial.begin(9600);


  
  servo = new ServoMotorImpl(9);
  state = WELCOME;
  display_lcd = new Display();
  coffee = new Product(N_MAX_QUANTITY, "Coffee");
  tea = new Product(N_MAX_QUANTITY, "Tea");
  chocolate = new Product(N_MAX_QUANTITY, "Chocolate");
  bUp = new ButtonImpl(B_UP);
  bDown = new ButtonImpl(B_DOWN);
  bMake = new ButtonImpl(B_MAKE);
  pos = 0;
  delta = 1;
  productList[0] = coffee;
  productList[1] = tea;
  productList[2] = chocolate;

}

void loop() {

  switch(state){
    case WELCOME:
        display_lcd->setText("Welcome");
        Serial.println("Welcome");
        delay(4000);
        state = READY;
    break;
    case READY:
      display_lcd->setText("Ready");
      selectedProduct = 0;
      startMillis = 0;
      Serial.println("Ready");
      state = SELECT;
    break;
    case SELECT:
      enableInterrupt(B_UP, incSelect, RISING);
      enableInterrupt(B_DOWN, decSelect, RISING);
      enableInterrupt(B_MAKE, makeProduct, RISING);
      
      currentMillis = millis();

      if(currentMillis - startMillis > T_OUT && startMillis != 0){
        state = READY;
        disableInterruptButton();
      }
    break;
    case MAKING:
      display_lcd->setText("Making a " + productList[selectedProduct]->toString());
      Serial.println("Making a " + productList[selectedProduct]->toString());
      moveServo();
      Serial.println("The " + productList[selectedProduct]->toString() + " is ready");
      decreaseSelectedItem(productList[selectedProduct]->toString());
      state = READY;
    break;
  }
 
}

void disableInterruptButton(){
  disableInterrupt(B_UP);
  disableInterrupt(B_DOWN);
  disableInterrupt(B_MAKE);
}



void incSelect(){
  
  if(selectedProduct < 2){
      selectedProduct++;
   //   display_lcd->setText(productList[selectedProduct]->toString());
      Serial.println(productList[selectedProduct]->toString());
  }
  startTimer();
}


void decreaseSelectedItem(String productList){
  switch(selectedProduct){
    case 0:
      coffee->decQuantity();
      //Serial.println(coffee->getQuantity());
    break;
    case 1:
      tea->decQuantity();
      //Serial.println(tea->getQuantity());
    break;
    case 2:
      chocolate->decQuantity();
      //Serial.println(chocolate->getQuantity());
    break;
  }
}

void moveServo(){
  servo->on();
  for (int i = 0; i < 180; i++) {
    servo->setPosition(pos);         
    delay(T_MAKING);            
    pos += delta;
  }
  servo->off();
}

void decSelect(){
  if(selectedProduct > 0){
    selectedProduct--;
      display_lcd->setText(productList[selectedProduct]->toString());
      Serial.println(productList[selectedProduct]->toString());
  }
  startTimer();
}

void makeProduct(){
  checkSugar();
  state = MAKING;
  disableInterruptButton();
}

void startTimer(){
  startMillis = millis();
}

void checkSugar(){
  int sugarValue = analogRead(A0);
  sugarValue /= 128;
  sugarValue /= 2;
  Serial.print(sugarValue);
  Serial.println(" cucchiaini di zucchero");
}
