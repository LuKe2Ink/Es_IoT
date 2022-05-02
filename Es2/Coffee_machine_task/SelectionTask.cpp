#include "SelectionTask.h"
#include "Machine.h"
#include "Arduino.h"


SelectionTask::SelectionTask(Machine* machine, Product* product){
    this->machine = machine;
    this->product = product;
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
        enableInterrupt(B_UP, this->incSelect, RISING);
        enableInterrupt(B_DOWN, this->decSelect, RISING);
        enableInterrupt(B_MAKE, this->makeProduct, RISING);
        
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
        Serial.println("Making a " + productList[this->selectedProd]->toString());
        moveServo(true);
        Serial.println("The " + productList[this->selectedProd]->toString() + " is ready");
        //decreaseSelectedItem(productList[this->selectedProd]->toString());

        //state = READY;
        
        this->machine->state = WAITING_REMOVING;
        startTimer();
        break;
    }
}

void SelectionTask::checkSleepMode(){

}

void SelectionTask::makeProduct(int select){
    this->machine->state = MAKING;
    //disabilitare i bottoni(oltre alle nostre menti)
    this->product[select]->decQuantity();
    if(product[select]->isNotAviable()){
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
  this->this->selectedProd--;
  if(this->selectedProd == -1){
    this->selectedProd = PROD_NUM-1;
  } 
  if(productList[this->selectedProd]->isNotAviable()){
    this->decSelect();
  }
  //currentProd = productList[this->selectedProd]->toString();
  //Serial.println(currentProd +" "+ productList[this->selectedProd]->getQuantity());
  this->startTimer();
}


void SelectionTask::startTimer(){
  startMillis = millis();
}