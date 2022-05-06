#include "CheckTask.h"

CheckTask::CheckTask(Machine *machine)
{
    this->machine = machine;
}

void CheckTask::init(int period)
{
    Task::init(period);
}

void CheckTask::tick()
{
    // Interrupt check if the machine is in assistance mode
    if(this->machine->state == ASSISTANCE) return;

    this->machine->display_lcd->setText("Make a check onichan");
    this->moveBackAndForward();
    this->checkTemp();
    this->machine->checkDone++;
}


void CheckTask::checkTemp(){
int temp = analogRead(TEMP_PIN);
    int value_in_mV = temp * 4.8876;
    double value_in_C = value_in_mV * 0.1;
    if (value_in_C < TEMP_MIN || value_in_C > TEMP_MAX)
    {
        this->machine->state = ASSISTANCE;
        // set to 0 quantities
        this->machine->coffee->setQuantity(0);
        this->machine->tea->setQuantity(0);
        this->machine->chocolate->setQuantity(0);
    }
}

void CheckTask::moveBackAndForward()
{
  machine->servo->on();
    int pos = 0;
    for (pos = 0; pos <= 180; pos += 1)
    { 
        this->machine->servo->setPosition(pos); 
                                                
        delay(15);                              
    }
    for (pos = 180; pos >= 0; pos -= 1)
    {                                           
        this->machine->servo->setPosition(pos); 
        delay(15);                              
    }

  machine->servo->off();
}