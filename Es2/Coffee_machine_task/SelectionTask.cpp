#include <EnableInterrupt.h>

#include "SelectionTask.h"
#include <NewPing.h>
#include <avr/sleep.h>



#define ORARIO 1
#define ANTI_ORARIO -1
#define PROD_NUM 3
#define T_IDLE 30000


SelectionTask::SelectionTask(Machine* machine){
    this->machine = machine;
    this->product[0] = this->machine->coffee;
    this->product[1] = this->machine->tea;
    this->product[2] = this->machine->chocolate;
    this->unaviableProd = 0;
    this->selectedProd = 0;
    this->pos = 0;
    this->countIdle = 0;
}

void SelectionTask::init(int period){
  Task::init(period);
  MsgService.init();
  String json = "";
  json = json + "{'coffee':"+this->machine->coffee->getQuantity()+",'tea': "+this->machine->tea->getQuantity()+",'chocolate': "+this->machine->chocolate->getQuantity()+ "}";

  MsgService.sendMsg(json);
}
  
void SelectionTask::tick(){
  switch(this->machine->state){
        case WELCOME:
            machine->display_lcd->setText("Welcome");
            delay(4000);
            this->machine->state = READY;
        break;
        case READY:
        this->idleMillis = millis();
        this->currentMillis = millis();
        machine->display_lcd->setText("Ready");
        this->selectedProd = 0;
        this->startMillis = 0;
        
        if(this->unaviableProd == PROD_NUM){
            Serial.println("Assistance");
            //display_lcd->setText("Assistance required");
            this->machine->state = ASSISTANCE;
        }else{
            this->startMillis = 0;
            Serial.println("vado in select");
            this->machine->state = SELECT;
        }
        break;
        case SELECT:

          if(machine->bUp->debounce()==HIGH) incSelect(); //incrementa di 1 se il pulsante è premuto
        
        if(machine->bDown->debounce()==HIGH) decSelect(); //incrementa di 1 se il pulsante è premuto
        
        
        if(machine->bMake->isPressed()) makeProduct();

        checkSleepMode();

        if(this->currentMillis - this->startMillis > T_OUT && this->startMillis != 0){
            this->machine->state = READY;
            }
        break;
        
        case MAKING:
        machine->display_lcd->setText("Making a " + product[selectedProd]->toString());
        machine->servo->moveServo(true);
        machine->display_lcd->setText("The " + product[selectedProd]->toString() + " is ready");
        //decreaseSelectedItem(productList[this->selectedProd]->toString());

        //state = READY;
        
        this->machine->state = WAITING_REMOVING;
        startTimer();
        break;
        case WAITING_REMOVING:
          currentMillis = millis();
          Serial.println(currentMillis - startMillis);
          Serial.println(machine->sonar->ping_cm());
          if(currentMillis - startMillis > T_OUT || machine->sonar->ping_cm() == 0){
            machine->servo->moveServo(false);
            machine->state = READY;
          }
          //Serial.println(sonar.ping_cm());
        break;
        case SLEEP:
          machine->display_lcd->off();
          set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
          enableInterrupt(PIR_PIN, awake, RISING);

          sleep_enable(); 
 
          sleep_mode(); 

          sleep_disable(); 

          machine->display_lcd->on();
          this->machine->state = WELCOME;
          disableInterrupt(PIR_PIN);
        break;
        case ASSISTANCE:
          if(MsgService.isMsgAvailable()){
            this->service = MsgService.receiveMsg();
            if(service->getContent() == "refill"){
              this->machine->display_lcd->setText("Received");
            }
          }          
          this->machine->display_lcd->setText("Assistance");
          Serial.println("Assistance");
        break;
    }
}

void SelectionTask::awake(){
  disableInterrupt(PIR_PIN);
  Serial.println("Esco");
}

void SelectionTask::checkSleepMode(){
  currentMillis = millis();
  if(currentMillis - idleMillis > T_IDLE && countIdle < 2){
    countIdle++;
    this->idleMillis = millis();
  }
  if(countIdle == 2 && !(machine->pir->isPresent())){
    machine->state = SLEEP;
    this->countIdle = 0;
    this->idleMillis = 0;
    Serial.println("Sleep");
  }
}

void SelectionTask::makeProduct(){
    machine->state = MAKING;
    //disabilitare i bottoni(oltre alle nostre menti)
    product[selectedProd]->decQuantity();
    if(product[selectedProd]->isNotAviable()){
        unaviableProd++;
    } 
}

void SelectionTask::incSelect(){
  
  selectedProd++;
  if(selectedProd == PROD_NUM){
    selectedProd = 0;
  } 
  if(product[selectedProd]->isNotAviable()){
    incSelect();
  }
  //currentProd = productList[selectedProd]->toString();
  machine->display_lcd->setText(product[selectedProd]->toString());
  startTimer();
  this->idleMillis = millis();
}

void SelectionTask::decSelect(){
  selectedProd--;
  if(selectedProd == -1){
    selectedProd = PROD_NUM-1;
  } 
  if(product[selectedProd]->isNotAviable()){
    decSelect();
  }
  //currentProd = productList[selectedProd]->toString();
  machine->display_lcd->setText(product[selectedProd]->toString());
  startTimer();
  this->idleMillis = millis();
}


void SelectionTask::startTimer(){
  startMillis = millis();
}
