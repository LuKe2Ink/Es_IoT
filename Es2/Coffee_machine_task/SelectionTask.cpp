#include "SelectionTask.h"
#include "Machine.h"
#include "Arduino.h"

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
        startMillis = 0;
        
        moveServo(ORARIO);
        //Serial.println("Ready"); Proco dio
        if(this->unaviableProd == PROD_NUM){
            Serial.println("Assistance");
            //display_lcd->setText("Assistance required");
            this->machine->state = ASSISTANCE;
        }else{
            startMillis = 0;
            this->machine->state = SELECT;
            //idleMillis = millis(); Michi merda
        }
        break;
        case SELECT:
          enableInterrupt(B_UP, incSelect, RISING);
          enableInterrupt(B_DOWN, decSelect, RISING);
          enableInterrupt(B_MAKE, makeProduct, RISING);
          
          currentMillis = millis();

          checkSleepMode();

          if(currentMillis - startMillis > T_OUT && startMillis != 0){
              this->machine->state = READY;
              disableInterruptButton();
              } else {
              //display_lcd->setText(currentProd +" "+ productList[this->selectedProd]->getQuantity());
              }
        break;
        
        case MAKING:
        //display_lcd->setText("Making a " + productList[this->selectedProd]->toString());
        Serial.println("Making a " + product[this->selectedProd]->toString());
        moveServo(true);
        Serial.println("The " + product[this->selectedProd]->toString() + " is ready");
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
    this->machine->state = MAKING;
    //disabilitare i bottoni(oltre alle nostre menti)
    this->product[this->selectedProd]->decQuantity();
    if(product[selectedProd]->isNotAviable()){
        this->unaviableProd++;
  } 
}

void SelectionTask::incSelect(){
  
  this->selectedProd++;
  if(this->selectedProd == PROD_NUM){
    this->selectedProd = 0;
  } 
  if(this->product[this->selectedProd]->isNotAviable()){
    incSelect();
  }
  //currentProd = productList[this->selectedProd]->toString();
  //Serial.println(currentProd +" "+ this->product[this->selectedProd]->getQuantity());
  startTimer();
}



void SelectionTask::moveServo(bool orario){
  this->machine->servo->on();
  for (int i = 0; i < 180; i++) {
    this->machine->servo->setPosition(pos);         
    delay(T_MAKING);            
    pos += orario ? 1 : -1;
    Serial.println(pos);
  }
  this->machine->servo->off();
}

void SelectionTask::decSelect(){
  this->selectedProd--;
  if(this->selectedProd == -1){
    this->selectedProd = PROD_NUM-1;
  } 
  if(product[this->selectedProd]->isNotAviable()){
    this->decSelect();
  }
  //currentProd = productList[this->selectedProd]->toString();
  //Serial.println(currentProd +" "+ productList[this->selectedProd]->getQuantity());
  this->startTimer();
}


void SelectionTask::startTimer(){
  startMillis = millis();
}

// Potrebbe essere inutile ma nel caso stica e la teniamo
void SelectionTask::disableInterruptButton(){
  disableInterrupt(B_UP);
  disableInterrupt(B_DOWN);
  disableInterrupt(B_MAKE);
}