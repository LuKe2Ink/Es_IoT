#include "SelectionTask.h"
#include <EnableInterrupt.h>


#define ORARIO 1
#define ANTI_ORARIO -1
#define PROD_NUM 3

SelectionTask::SelectionTask(Machine* machine){ 
    this->machine = machine;
    this->product[0] = this->machine->coffee;
    this->product[1] = this->machine->tea;
    this->product[2] = this->machine->chocolate;
    this->unaviableProd = 0;
    this->selectedProd = 0;
    pos=0;
}

void SelectionTask::init(int period){
  Task::init(period);
}
  
void SelectionTask::tick(){
  switch(this->machine->state){
        case WELCOME:
            this->machine->display_lcd->setText("Welcome");
            Serial.println("Welcome");
            delay(4000);
            this->machine->state = READY;
        break;
        case READY:
        //display_lcd->setText("Ready");
        this->selectedProd = 0;
        this->startMillis = 0;
        
        moveServo(ORARIO);
        Serial.println("Ready"); 
        if(this->unaviableProd == PROD_NUM){
            Serial.println("Assistance");
            //display_lcd->setText("Assistance required");
            this->machine->state = ASSISTANCE;
        }else{
            this->startMillis = 0;
            this->machine->state = SELECT;
            //idleMillis = millis(); Michi merda
        }
        break;
        case SELECT:
//        enableInterrupt(B_UP, SelectionTask.incSelect, RISING);
//        enableInterrupt(B_DOWN, decSelect, RISING);
//        enableInterrupt(B_MAKE, makeProduct, RISING);

        if(machine->bUp->isPressed()){
          incSelect();
          Serial.println("porco il dio");
        }
        
        if(machine->bDown->isPressed()){
          decSelect();
          Serial.println("porco il dio 1");
        }
        
        if(machine->bMake->isPressed()){
          makeProduct();
          Serial.println("porco il dio 2");
        }
        
        this->currentMillis = millis();

        //checkSleepMode();

        if(this->currentMillis - this->startMillis > T_OUT && this->startMillis != 0){
            this->machine->state = READY;
            } else {
            //display_lcd->setText(currentProd +" "+ productList[this->selectedProd]->getQuantity());
            }
        break;
        
        case MAKING:
        //display_lcd->setText("Making a " + productList[this->selectedProd]->toString());
        Serial.println("Making a " + this->product[this->selectedProd]->toString());
        moveServo(true);
        Serial.println("The " + this->product[this->selectedProd]->toString() + " is ready");
        //decreaseSelectedItem(productList[this->selectedProd]->toString());

        //state = READY;
        
        this->machine->state = WAITING_REMOVING;
        startTimer();
        break;
    }
}

void SelectionTask::checkSleepMode(){

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
  Serial.println(product[selectedProd]->toString() +" "+ product[selectedProd]->getQuantity());
  startTimer();
}



void SelectionTask::moveServo(bool orario){
  machine->servo->on();
  for (int i = 0; i < 180; i++) {
    machine->servo->setPosition(pos);         
    delay(T_MAKING);            
    pos += orario ? 1 : -1;
    Serial.println(pos);
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
}


void SelectionTask::startTimer(){
  startMillis = millis();
}
