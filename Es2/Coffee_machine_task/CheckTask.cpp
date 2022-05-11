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
  switch (state)
  {
  case CHECK:
    count++;
    if (this->machine->state != ASSISTANCE && count == 5)
    {
      // 30k * 6 = 180k ms
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

void CheckTask::checkTemp()
{
  int temp = analogRead(TEMP_PIN);
  int value_in_mV = temp * 4.8876;
  double value_in_C = value_in_mV * 0.1;
  // sensor disfunction solution
  value_in_C -= 25;
  if (value_in_C < TEMP_MIN || value_in_C > TEMP_MAX)
  {
    this->machine->state = ASSISTANCE;
    this->machine->display_lcd->setText("Assistance");
  }
  else
  {
    this->machine->state = READY;
  }
}

void CheckTask::moveBackAndForward()
{
  machine->servo->moveServo(true);
  machine->servo->moveServo(false);
}
