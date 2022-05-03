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
    this->moveBackAndForward();
    this->checkTemp();
}


void CheckTask::checkTemp(){
int temp = analogRead(TEMP_PIN);
    int value_in_mV = temp * 4.8876;
    double value_in_C = value_in_mV * 0.1;
    if (value_in_C < TEMP_MIN || value_in_C > TEMP_MAX)
    {
        this->machine->display_lcd->setText("ASSISTENCE REQUIRED");
        // TODO settare a 0 i numeri di ogni prodotto
    }
}

void CheckTask::moveBackAndForward()
{
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
}