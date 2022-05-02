#include "SetupTask.h"
#include "Arduino.h"



SetupTask::SetupTask(){
        //display_lcd->setText("Welcome");
        Serial.println("Welcome");
        delay(4000);
  }
