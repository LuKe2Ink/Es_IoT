#include "Scheduler.h"
#include "Garden.h"

#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "RoutineTask.h"
#include "IrrigationTask.h"

Scheduler scheda;
Garden* garden;
RoutineTask *routine;
IrrigationTask *irrigation;


void setup() {
  Serial.begin(9600);
  garden = new Garden();
  scheda.init(100);

  routine = new RoutineTask(garden);
  routine->init(700);
  scheda.addTask(routine);

  irrigation = new IrrigationTask(garden);
  irrigation->init(20);
  scheda.addTask(irrigation);

  garden->state = AUTO;
  garden->stateIrrigation = OPERATING;
}

void loop() {
 scheda.schedule(); 
}


