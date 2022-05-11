#include "Product.h"
#include "Machine.h"
#include "Scheduler.h"
#include "SugarTask.h"
#include "SelectionTask.h"
#include "CheckTask.h"

#define T_OUT 5000L
#define T_MAKING 55
#define T_CHECK 180000

Machine *machine;
Scheduler scheda;
SugarTask *sugar;
SelectionTask *selection;
CheckTask *check;

void setup()
{
  Serial.begin(9600);
  machine = new Machine();
  scheda.init(100);

  /*Sugar Task*/
  sugar = new SugarTask(machine);
  sugar->init(20);
  scheda.addTask(sugar);

  /*Selection Task*/
  selection = new SelectionTask(machine);
  selection->init(100);
  scheda.addTask(selection);

  /*Check task*/
  check = new CheckTask(machine);
  check->init(30000);
  scheda.addTask(check);

  machine->state = WELCOME;
}

void loop()
{
  scheda.schedule();
}
