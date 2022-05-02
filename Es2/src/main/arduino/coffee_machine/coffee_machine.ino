#include "MsgService.h"
#include "Display.h"
#include "Product.h"
#include "ButtonImpl.h"
#include "ServoMotorImpl.h"
#include "Scheduler.h"
#include "SugarTask.h"
#include <EnableInterrupt.h>
#include <NewPing.h>
#include <avr/sleep.h>

enum {
  WELCOME,
  READY,
  SELECT,
  MAKING,
  WAITING_REMOVING,
  ASSISTANCE,
  SLEEP
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
#define T_IDLE 60000L
#define T_MAKING 55

#define PROD_NUM 3

NewPing sonar(7, 8, 40);
Scheduler sched;
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
unsigned long idleMillis;
int pos;   
int delta;
String currentProd;
int aviableProd;

void setup() {
  MsgService.init();
  Serial.begin(9600);
  sched.init(100);

  Task* t0 = new SugarTask();
  t0->init(100);
  sched.addTask(t0);
  servo = new ServoMotorImpl(10);
  state = WELCOME;
  display_lcd = new Display();
  coffee = new Product(1, "Coffee");
  tea = new Product(1, "Tea");
  chocolate = new Product(1, "Chocolate");
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
  //sched.schedule();
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
      Serial.println("Ready");
      if(aviableProd == PROD_NUM){
        Serial.println("Assistance");
        //display_lcd->setText("Assistance required");
        state = ASSISTANCE;
      }else{
        startMillis = 0;
        state = SELECT;
        idleMillis = millis();
      }
    break;
    case SELECT:
      enableInterrupt(B_UP, incSelect, RISING);
      enableInterrupt(B_DOWN, decSelect, RISING);
      enableInterrupt(B_MAKE, makeProduct, RISING);
      
      currentMillis = millis();

      checkSleepMode();

      if(currentMillis - startMillis > T_OUT && startMillis != 0){
        state = READY;
        disableInterruptButton();
        } else {
          //display_lcd->setText(currentProd +" "+ productList[selectedProduct]->getQuantity());
        }
    break;
    case MAKING:
      //display_lcd->setText("Making a " + productList[selectedProduct]->toString());
      Serial.println("Making a " + productList[selectedProduct]->toString());
      moveServo(true);
      Serial.println("The " + productList[selectedProduct]->toString() + " is ready");
//      decreaseSelectedItem(productList[selectedProduct]->toString());

      state = WAITING_REMOVING;
      startTimer();
    break;
    case WAITING_REMOVING:
      currentMillis = millis();
      
      if(currentMillis - startMillis > T_OUT || sonar.ping_cm() == 0){
        moveServo(false);
        state = READY;
      }
      Serial.println(sonar.ping_cm());
    break;
    case ASSISTANCE:
      if (MsgService.isMsgAvailable()) {
        Msg* msg = MsgService.receiveMsg();    
        if (msg->getContent() == "refill"){
          state = READY;
          refill();
          MsgService.sendMsg("okk");
        }
    /* NOT TO FORGET: message deallocation */
        delete msg;
      }
    break;
    case SLEEP:
      Serial.println("Sleep");
      delay(500);
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
      enableInterrupt(B_UP, machineOn, RISING);
      enableInterrupt(B_DOWN, machineOn, RISING);
      enableInterrupt(B_MAKE, machineOn, RISING);
      sleep_enable();
      sleep_mode();  
      sleep_disable(); 
    break;
  }
 
}

void machineOn(){
  state = WELCOME;
  disableInterruptButton();
}

void checkSleepMode(){
  if(currentMillis - idleMillis > T_IDLE && sonar.ping_cm() == 0){
    state = SLEEP;
  }
}

void refill(){
  for(int i = 0 ; i < PROD_NUM; i++){
     productList[i]->setQuantity(N_MAX_QUANTITY);
  }
}

void disableInterruptButton(){
  disableInterrupt(B_UP);
  disableInterrupt(B_DOWN);
  disableInterrupt(B_MAKE);
}

void incSelect(){
  
  selectedProduct++;
  if(selectedProduct == PROD_NUM){
    selectedProduct = 0;
  } 
  if(productList[selectedProduct]->isNotAviable()){
    incSelect();
  }
  currentProd = productList[selectedProduct]->toString();
  Serial.println(currentProd +" "+ productList[selectedProduct]->getQuantity());
  startTimer();
}



void moveServo(bool orario){
  servo->on();
  for (int i = 0; i < 180; i++) {
    servo->setPosition(pos);         
    delay(T_MAKING);            
    pos += orario ? 1 : -1;
    Serial.println(pos);
  }
  servo->off();
}

void decSelect(){
  selectedProduct--;
  if(selectedProduct == -1){
    selectedProduct = PROD_NUM-1;
  } 
  if(productList[selectedProduct]->isNotAviable()){
    decSelect();
  }
  currentProd = productList[selectedProduct]->toString();
  Serial.println(currentProd +" "+ productList[selectedProduct]->getQuantity());
  startTimer();
}

void makeProduct(){
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
