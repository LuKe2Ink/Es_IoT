#include "CheckTask.h"

int count = 0;

CheckTask::CheckTask(Machine *machine)
{
    this->machine = machine;
    this->state = CHECK;
    this->count = 0;
}

void CheckTask::init(int period)
{
    Task::init(period);
}

void CheckTask::tick()
{
    // Interrupt check if the machine is in assistance mode
    switch(state){
      case CHECK:
        count++;
<<<<<<< HEAD
        //Serial.print("Check count: ");
        //Serial.println(count);
        if(this->machine->state != ASSISTANCE && count == 4){
=======
        Serial.print("Check count: ");
        Serial.println(count);
        if(this->machine->state != ASSISTANCE && count == 6){
>>>>>>> f39d633c9666e35a416551164a44c0605ccd4598
          count = 0;
          state = TEST;
        }
      break;
      case TEST:
        this->machine->display_lcd->setText("DOING CHECK");
        this->moveBackAndForward();
        this->checkTemp();
        this->machine->checkDone++;
        this->state = CHECK;
      break;
    }
}


void CheckTask::checkTemp(){
    int temp = analogRead(TEMP_PIN);
    int value_in_mV = temp * 4.8876;
    double value_in_C = value_in_mV * 0.1;
<<<<<<< HEAD
    //Serial.println(value_in_C);
=======
>>>>>>> f39d633c9666e35a416551164a44c0605ccd4598
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
  machine->servo->moveServo(true);
  machine->servo->moveServo(false);
}
