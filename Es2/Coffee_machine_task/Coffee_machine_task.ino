//#include "MsgService.h"
#include "Display.h"
#include "Product.h"
#include "ButtonImpl.h"
#include "ServoMotorImpl.h"
#include <EnableInterrupt.h>
#include "Machine.h"
#include "Scheduler.h"
#include "SugarTask.h"





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

Machine* machine;
Scheduler scheda;
SugarTask* sugar;

int selectedProduct;
Product* productList[3];
unsigned long startMillis;
unsigned long currentMillis;
unsigned long idleMillis;
int pos;   
int delta;
String currentProd;
int aviableProd;

enum {
  WELCOME,
  READY,
  SELECT,
  MAKING,
  WAITING_REMOVING,
  ASSISTANCE,
  SLEEP
}state;

void setup() {
  Serial.begin(9600);
  machine = new Machine();
  scheda.init(100);
  sugar = new SugarTask(POT);
  sugar->init(500);
  scheda.addTask(sugar);

  state = WELCOME;
  pos = 0;
  delta = 1;
  productList[0] = machine->coffee;
  productList[1] = machine->tea;
  productList[2] = machine->chocolate;
  machine->servo->setPosition(180);

  
}

void loop() {
//  sugar->tick();
  scheda.schedule();


  
}
