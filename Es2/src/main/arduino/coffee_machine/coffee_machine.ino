#include "MsgService.h"
#include "Display.h"
#include "Product.h"
#include "ButtonImpl.h"
#include "ServoMotorImpl.h"
#include <EnableInterrupt.h>

#include "Scheduler.h"

#include "SugarTask.h"

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
#define PIR_PIN 7
#define TEMP_PIN A0 
#define TRIG 13
#define ECHO 12
#define POT A1

#define T_OUT 5000L
#define T_MAKING 55

#define PROD_NUM 3

#define ORARIO 1
#define ANTI_ORARIO -1


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
String currentProd;
int aviableProd;
Scheduler sch;
SugarTask* sugar;

void setup() {
  /*MsgService.init();*/
  Serial.begin(9600);

  sch.init(100);
  
  servo = new ServoMotorImpl(10);
  state = WELCOME;
  display_lcd = new Display();
  coffee = new Product(50, "Coffee");
  tea = new Product(50, "Tea");
  chocolate = new Product(50, "Chocolate");
  bUp = new ButtonImpl(B_UP);
  bDown = new ButtonImpl(B_DOWN);
  bMake = new ButtonImpl(B_MAKE);

 sugar = new SugarTask(POT);

  sugar->init(500);
  sch.addTask(sugar);
  

  
  pos = 0;
  delta = 1;
  productList[0] = coffee;
  productList[1] = tea;
  productList[2] = chocolate;
  servo->setPosition(180);
}

void loop() {
  //  sch.schedule();
  sugar-> tick();
  switch(state){
    case WELCOME:
        display_lcd->setText("Welcome");
        Serial.println("Welcome");
        delay(4000);
        state = READY;
    break;
    case READY:
//      display_lcd->setText("Ready");
      selectedProduct = 0;
      startMillis = 0;
      
      moveServo(ORARIO);
      Serial.println("Ready");
      state = SELECT;
    break;
    case SELECT:
//      if(aviableProd == PROD_NUM){
//        display_lcd->setText("No caffeina coglione");
//      }
      enableInterrupt(B_UP, caccapopoSu, RISING);
      enableInterrupt(B_DOWN, caccapopoGiu, RISING);
      enableInterrupt(B_MAKE, makeProduct, RISING);
      
      currentMillis = millis();

      if(currentMillis - startMillis > T_OUT && startMillis != 0){
        state = READY;
        disableInterruptButton();
        } else {
          display_lcd->setText(currentProd +" "+ productList[selectedProduct]->getQuantity());
        }
    break;
    case MAKING:
      display_lcd->setText("Making a " + productList[selectedProduct]->toString());
      Serial.println("Making a " + productList[selectedProduct]->toString());
      Serial.println("The " + productList[selectedProduct]->toString() + " is ready");
//      decreaseSelectedItem(productList[selectedProduct]->toString());
      moveServo(ANTI_ORARIO);

      state = READY;
      

    break;
  }
 
}

void disableInterruptButton(){
  disableInterrupt(B_UP);
  disableInterrupt(B_DOWN);
  disableInterrupt(B_MAKE);
}

void printProduct(){
  
}
void caccapopoSu(){
  selectedProduct++;
  if(selectedProduct == PROD_NUM){
    selectedProduct = 0;
  } 
  if(productList[selectedProduct]->isNotAviable()){
    caccapopoSu();
  }
  currentProd = productList[selectedProduct]->toString();
}
void caccapopoGiu(){
  selectedProduct--;
  if(selectedProduct == -1){
    selectedProduct = PROD_NUM-1;
  } 
  if(productList[selectedProduct]->isNotAviable()){
    caccapopoGiu();
  }
  currentProd = productList[selectedProduct]->toString();
}


//void incSelect(){
//  
//  if(selectedProduct < 2){
//      selectedProduct++;
//      currentProd = productList[selectedProduct]->toString();
//      Serial.println(productList[selectedProduct]->toString());
//  }
//  startTimer();
//}



void moveServo(int grades){
  servo->on();
  if(grades > 0){
  for (int i = 0; i < 180; i++) {
    servo->setPosition(pos%180);         
    delay(T_MAKING);            
    pos = pos + (grades > 0 ? 1 : -1);
    Serial.println(pos);
  }
  } else {
    for (int i = 180; i > 0; i--) {
    servo->setPosition(pos%180);         
    delay(T_MAKING);            
    pos = pos + (grades > 0 ? 1 : -1);
    Serial.println(pos);
    }

}
  servo->off();
}

//void decSelect(){
//  if(selectedProduct > 0){
//    selectedProduct--;
//    currentProd = productList[selectedProduct]->toString();
//      Serial.println(productList[selectedProduct]->toString());
//  }
//  startTimer();
//}

void makeProduct(){
  checkSugar();
  state = MAKING;
  disableInterruptButton();
  productList[selectedProduct]->decQuantity();
  if(productList[selectedProduct]->isNotAviable()){
        aviableProd++;
      }
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
