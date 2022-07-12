#include "RoutineTask.h"

SoftwareSerial btChannel(RX, TX);

RoutineTask::RoutineTask(Garden* garden){
  btChannel.begin(9600);
  this->garden = garden;
}

void RoutineTask::init(int period){
  Task::init(period);
}

void RoutineTask::tick()
{
  this->setData();
  switch(this->garden->state){
    case AUTO:
      if(garden->sensorBoard->photoresistor->isLessThenMax()){
        turnOnAllLed();
        garden->led_c->setLuminosity(1);
        garden->led_d->setLuminosity(4);
        garden->sensorBoard->photoresistor->setValue(1);
        if( !this->garden->isIrrigationSystemOperating && garden->sensorBoard->photoresistor->isLessThenMin()){
          this->garden->isIrrigationSystemOperating = true;
          activateIrrigationSystem();
        }
      }else{
        turnOffAllLed();
      }
      break;
    case MANUAL:
      break;
    case ALARM:
      break;
  }
  
}

void RoutineTask::turnOnAllLed(){
  garden->led_a->turnOn();
  garden->led_b->turnOn();
}

void RoutineTask::turnOffAllLed(){
  garden->led_a->turnOff();
  garden->led_b->turnOff();
  garden->led_c->turnOff();
  garden->led_d->turnOff();
}

void RoutineTask::activateIrrigationSystem(){
  //garden->moveServo = true;
  garden->servo->moveServo();
}

void RoutineTask::setData(){
 if (btChannel.available()){
    String msg = btChannel.readString();
    this->garden->led_b->turnOff();
    this->garden->state = MANUAL;
    Serial.println(msg);
  }

  String msg = "";

  
 
  
//  int incomingByte = 0; // for incoming serial data
//
//  
//  if (Serial.available() > 0) {
//    // read the incoming byte:
//    incomingByte = Serial.read();
//
//    // say what you got:
//    
//    Serial.print("{\"received\": 12 }");
//    Serial.println(incomingByte, DEC);
//  }
//  
  
//  //while(Serial.available() > 0){
//  String msg = Serial.readString();
//  Serial.println("serial: " + msg );
//  if(msg != NULL){ 
//  this->garden->led_b->turnOff();
//  this->garden->state = MANUAL;
//  //}
//  }
//  
}
