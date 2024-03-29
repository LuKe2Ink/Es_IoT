#include <EnableInterrupt.h>

#include "SelectionTask.h"
#include <NewPing.h>
#include <avr/sleep.h>

#define ORARIO 1
#define ANTI_ORARIO -1
#define PROD_NUM 3
#define T_IDLE 30000

SelectionTask::SelectionTask(Machine *machine)
{
  this->machine = machine;
  this->product[0] = this->machine->coffee;
  this->product[1] = this->machine->tea;
  this->product[2] = this->machine->chocolate;
  this->unaviableProd = 0;
  this->selectedProd = 0;
  this->pos = 0;
  this->countIdle = 0;
}

String json;

void SelectionTask::init(int period)
{
  Task::init(period);
  MsgService.init();
  // send message to GUI
  update = new UpdateMessage(this->machine->coffee->getQuantity(), this->machine->tea->getQuantity(), this->machine->chocolate->getQuantity(), this->machine->checkDone, this->machine->statusMachine);
  json = update->toJson();

  MsgService.sendMsg(json);
}

void SelectionTask::tick()
{
  switch (this->machine->state)
  {
  case WELCOME:
    machine->display_lcd->setText("Welcome");
    delay(4000);
    this->machine->state = READY;

    // check if the machine onStart has any products that have quantity = 0
    for (int i = 0; i < PROD_NUM; i++)
    {
      if (this->product[i]->isNotAviable())
      {
        this->unaviableProd++;
      }
    }
    break;
  case READY:
    this->idleMillis = millis();
    this->currentMillis = millis();
    machine->display_lcd->setText("Ready");
    this->selectedProd = 0;
    this->startMillis = 0;

    // sends data to GUI
    sendUpdateData();

    // machine has no products available so goes into assistence mode
    if (this->unaviableProd == PROD_NUM)
    {
      // Serial.println("Assistance");
      this->machine->display_lcd->setText("Assistance required");
      this->machine->state = ASSISTANCE;
      this->machine->display_lcd->setText("Assistance");
    }
    else
    {
      this->startMillis = 0;
      // Serial.println("vado in select");
      this->machine->state = SELECT;
      this->machine->statusMachine = "working";
      // sends data to GUI
      sendUpdateData();
    }
    break;
  case SELECT:

    if (machine->bUp->debounce() == HIGH)
      incSelect(); // incrementa di 1 se il pulsante è premuto

    if (machine->bDown->debounce() == HIGH)
      decSelect(); // incrementa di 1 se il pulsante è premuto

    if (machine->bMake->isPressed())
      makeProduct();

    checkSleepMode();

    // if in T_OUT user does not select a product goes to READY state
    if (this->currentMillis - this->startMillis > T_OUT && this->startMillis != 0)
    {
      this->machine->state = READY;
    }
    break;

  case MAKING:

    machine->display_lcd->setText("Making a " + product[selectedProd]->toString());
    machine->servo->moveServo(true);
    machine->display_lcd->setText("The " + product[selectedProd]->toString() + " is ready");

    this->machine->state = WAITING_REMOVING;
    this->machine->statusMachine = "working";
    startTimer();
    break;
  case WAITING_REMOVING:
    this->statusMachine = "idle";
    currentMillis = millis();
    if (currentMillis - startMillis > T_OUT || machine->sonar->ping_cm() == 0)
    {
      machine->servo->moveServo(false);
      machine->state = READY;
    }
    break;
  case SLEEP:
    machine->display_lcd->off();

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    enableInterrupt(PIR_PIN, awake, RISING);

    sleep_enable();

    sleep_mode();

    sleep_disable();

    machine->display_lcd->on();
    this->machine->statusMachine = "idle";
    this->machine->state = WELCOME;
    disableInterrupt(PIR_PIN);
    break;
  case ASSISTANCE:

    if (this->machine->statusMachine != "assistance")
    {
      this->machine->statusMachine = "assistance";
      // send message to GUI
      sendUpdateData();
    }

    if (MsgService.isMsgAvailable())
    {
      this->service = MsgService.receiveMsg();

      // receive message from GUI and change status on GUI
      if (service->getContent() == "refill")
      {
        this->machine->display_lcd->setText("Received refill");
        this->machine->coffee->setQuantity(N_MAX_QUANTITY);
        this->machine->tea->setQuantity(N_MAX_QUANTITY);
        this->machine->chocolate->setQuantity(N_MAX_QUANTITY);
        this->unaviableProd = 0;
        this->machine->statusMachine = "idle";
        this->machine->state = READY;
      }
      else if (service->getContent() == "recover")
      {
        this->machine->display_lcd->setText("Recover");
        this->machine->statusMachine = "idle";
        this->machine->state = READY;
      }
    }
    break;
  }
}

void SelectionTask::awake()
{
  disableInterrupt(PIR_PIN);
}

void SelectionTask::sendUpdateData()
{
  update->setMessage(this->machine->coffee->getQuantity(), this->machine->tea->getQuantity(), this->machine->chocolate->getQuantity(), this->machine->checkDone, this->machine->statusMachine);
  json = update->toJson();

  MsgService.sendMsg(json);
}

void SelectionTask::checkSleepMode()
{
  currentMillis = millis();
  if (currentMillis - idleMillis > T_IDLE && countIdle < 2)
  {
    countIdle++;
    this->idleMillis = millis();
  }
  if (countIdle == 2 && !(machine->pir->isPresent()))
  {
    machine->state = SLEEP;
    this->countIdle = 0;
    this->idleMillis = 0;
  }
}

void SelectionTask::makeProduct()
{
  machine->state = MAKING;
  // disabilitare i bottoni(oltre alle nostre menti)
  product[selectedProd]->decQuantity();
  if (product[selectedProd]->isNotAviable())
  {
    unaviableProd++;
  }
}

void SelectionTask::incSelect()
{

  selectedProd++;
  if (selectedProd == PROD_NUM)
  {
    selectedProd = 0;
  }
  if (product[selectedProd]->isNotAviable())
  {
    incSelect();
  }
  else
  {
    machine->display_lcd->setText(product[selectedProd]->toString());
    startTimer();
    this->idleMillis = millis();
  }
}

void SelectionTask::decSelect()
{
  selectedProd--;
  if (selectedProd == -1)
  {
    selectedProd = PROD_NUM - 1;
  }
  if (product[selectedProd]->isNotAviable())
  {
    decSelect();
  }
  else
  {
    machine->display_lcd->setText(product[selectedProd]->toString());
    startTimer();
    this->idleMillis = millis();
  }
}

void SelectionTask::startTimer()
{
  startMillis = millis();
}
