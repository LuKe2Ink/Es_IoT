#include "CheckTask.h"

CheckTask::CheckTask(Machine* machine){
    this->machine = machine;
}

void CheckTask::init(int period){
  Task::init(period);   
}

void CheckTask::tick(){
    int i = 0;
    for (; i < 180; i++)
    {
        this->machine->servo->setPosition(i);
        delay(1);
    }

   for (; i >= 0; i--)
    {
        this->machine->servo->setPosition(i);
        delay(1);
    } 

    int temp = analogRead(TEMP_PIN);
    int value_in_mV = temp *  4.8876 ;
    double value_in_C = value_in_mV * 0.1;
    if(value_in_C < TEMP_MIN || value_in_C > TEMP_MAX){
        this->machine->display_lcd->setText("ASSISTENCE REQUIRED");
        //TODO settare a 0 i numeri di ogni prodotto
    }
}