//#include "MsgService.h"
#include "Product.h"
#include "Machine.h"
#include "Scheduler.h"
#include "SugarTask.h"
#include "SelectionTask.h"





//#define B_UP 7
//#define B_DOWN 6
//#define B_MAKE u
#define PIR_PIN 7
#define TRIG 13
#define ECHO 12
#define POT A0

#define T_OUT 5000L
#define T_MAKING 55



Machine* machine;
Scheduler scheda;
SugarTask* sugar;
SelectionTask* selection;

int selectedProduct;
Product* productList[3];
unsigned long startMillis;
unsigned long currentMillis;
unsigned long idleMillis;
int pos;   
int delta;
String currentProd;
int aviableProd;

// enum {
//   WELCOME,
//   READY,
//   SELECT,
//   MAKING,
//   WAITING_REMOVING,
//   ASSISTANCE,
//   SLEEP
// }state;

void setup() {
  Serial.begin(9600);
  machine = new Machine();
  scheda.init(100);

  /*Sugar Task*/
  sugar = new SugarTask(machine);
  sugar->init(500);
  scheda.addTask(sugar);
  /*Selection Task*/
  
  //REGA DECOMMENTATE PER AVERE ERRORI CHE BHO NON CAPISCO

// vi voglio bene <3

   selection = new SelectionTask(machine);
   selection->init(100);
   scheda.addTask(selection);

  machine->state = WELCOME;
  // state = WELCOME;
  pos = 0;
  delta = 1;
  productList[0] = machine->coffee;
  productList[1] = machine->tea;
  productList[2] = machine->chocolate;
  // machine->servo->setPosition(180);

  
}

void loop() {
//  sugar->tick();
  scheda.schedule();


  
}
