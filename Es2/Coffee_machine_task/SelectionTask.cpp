#include "SelectionTask.h"
#include <NewPing.h>
#include <avr/sleep.h>



#define ORARIO 1
#define ANTI_ORARIO -1
#define PROD_NUM 3
#define T_IDLE 10000


SelectionTask::SelectionTask(Machine* machine){ 
    this->machine = machine;
    this->product[0] = this->machine->coffee;
    this->product[1] = this->machine->tea;
    this->product[2] = this->machine->chocolate;
    this->unaviableProd = 0;
    this->selectedProd = 0;
}

void SelectionTask::init(int period){
  Task::init(period);
}
  
void SelectionTask::tick(){
  switch(this->machine->state){
        case WELCOME:
            idleMillis = millis();
            this->machine->display_lcd->setText("Welcome");
            Serial.println("Welcome");
            delay(4000);
            this->machine->state = READY;
        break;
        case READY:
        idleMillis = millis();
        //display_lcd->setText("Ready");
        this->selectedProd = 0;
        this->startMillis = 0;
        
        Serial.println("Ready"); 
        if(this->unaviableProd == PROD_NUM){
            Serial.println("Assistance");
            //display_lcd->setText("Assistance required");
            this->machine->state = ASSISTANCE;
        }else{
            this->startMillis = 0;
            this->machine->state = SELECT;
        }
        break;
        case SELECT:
//        enableInterrupt(B_UP, SelectionTask.incSelect, RISING);
//        enableInterrupt(B_DOWN, decSelect, RISING);
//        enableInterrupt(B_MAKE, makeProduct, RISING);

          if(machine->bUp->debounce()==HIGH) incSelect(); //incrementa di 1 se il pulsante è premuto
          
//        if(machine->bUp->isPressed()){
//          incSelect();
//          Serial.println("porco il dio");
//        }
        
        if(machine->bDown->debounce()==HIGH) decSelect(); //incrementa di 1 se il pulsante è premuto
        
        
        if(machine->bMake->isPressed()) makeProduct();

        checkSleepMode();

        if(this->currentMillis - this->startMillis > T_OUT && this->startMillis != 0){
            this->machine->state = READY;
            } else {
            //display_lcd->setText(currentProd +" "+ productList[this->selectedProd]->getQuantity());
            }
        break;
        
        case MAKING:
        //display_lcd->setText("Making a " + productList[this->selectedProd]->toString());
        Serial.println("Making a " + this->product[this->selectedProd]->toString());
        moveServo();
        Serial.println("The " + this->product[this->selectedProd]->toString() + " is ready");
        //decreaseSelectedItem(productList[this->selectedProd]->toString());

        //state = READY;
        
        this->machine->state = WAITING_REMOVING;
        startTimer();
        break;
        case WAITING_REMOVING:
          currentMillis = millis();
      
          if(currentMillis - startMillis > T_OUT || machine->sonar->ping_cm() == 0){
            moveServo();
            machine->state = READY;
          }
          //Serial.println(sonar.ping_cm());
    break;
    case SLEEP:
      Serial.println("Sleep");
    break;
    }
}

void SelectionTask::machineOn(){
  machine->state = WELCOME;
  idleMillis = millis();
}

void SelectionTask::checkSleepMode(){
  currentMillis = millis();
  if(currentMillis - idleMillis > T_IDLE && machine->sonar->ping_cm() == 0){
    machine->state = SLEEP;
  }
}

void SelectionTask::makeProduct(){
    machine->state = MAKING;
    //disabilitare i bottoni(oltre alle nostre menti)
    product[selectedProd]->decQuantity();
    if(product[selectedProd]->isNotAviable()){
        unaviableProd++;
    } 
    idleMillis = millis();
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
  Serial.println(product[selectedProd]->toString() +" "+ product[selectedProd]->getQuantity());
  startTimer();
  idleMillis = millis();
}



void SelectionTask::moveServo(){
  machine->servo->on();

  for (int pos = 0; pos < 180; pos += 1){
    machine->servo->setPosition(pos);         
    delay(T_MAKING);            
  }
  machine->servo->off();
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
  Serial.println(product[selectedProd]->toString() +" "+ product[selectedProd]->getQuantity());
  startTimer();
  idleMillis = millis();
}


void SelectionTask::startTimer(){
  startMillis = millis();
}
