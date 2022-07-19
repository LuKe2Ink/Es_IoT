#include "RoutineTask.h"
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

SoftwareSerial btChannel(RX, TX);
StaticJsonDocument<200> doc;

RoutineTask::RoutineTask(Garden* garden){
  btChannel.begin(9600);
  this->garden = garden;
}

void RoutineTask::init(int period){
  Task::init(period);
}

void RoutineTask::tick()
{
//  this->setData();
  switch(this->garden->state){
    case AUTO:
//      if(garden->sensorBoard->photoresistor->isLessThenMax()){
//        turnOnAllLed();
//        garden->led_c->setLuminosity(1);
//        garden->led_d->setLuminosity(4);
//        garden->sensorBoard->photoresistor->setValue(1);
////        if( !this->garden->isIrrigationSystemOperating && garden->sensorBoard->photoresistor->isLessThenMin()){
////          this->garden->isIrrigationSystemOperating = true;
////          activateIrrigationSystem();
////        }
//      }else{
//        turnOffAllLed();
//      }
      checkManualControl();
      break;
    case MANUAL:
      if(btChannel.available()){
        String msg = btChannel.readString();
        Serial.println(msg);
        deserializeJson(doc, msg);
        JsonObject root = doc.as<JsonObject>();
        checkChanges(root);
      }
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

void RoutineTask::checkManualControl(){
  if(btChannel.available()){
    String msg = btChannel.readString();
    Serial.println(msg);
    deserializeJson(doc, msg);
    JsonObject root = doc.as<JsonObject>();
    String control = root["state"];
    Serial.println(control);
    if(control == "manual"){
      this->garden->state = MANUAL;
      checkChanges(root);
    }
  }
}

void RoutineTask::checkChanges(JsonObject root){
  if(root.containsKey("led1")){
    bool op = root["led1"];
    checkLed1(op);
  }
  if(root.containsKey("led2")){
    bool op = root["led2"];
    checkLed2(op);
  }
  if(root.containsKey("led3")){
    String op = root["led3"];
    checkLed3(op);
  }
  if(root.containsKey("led4")){
    String op = root["led4"];
    checkLed4(op);
  }
  if(root.containsKey("irrigation")){
    String op = root["irrigation"];
    checkIrrigation(op);
  }
}

void RoutineTask::checkLed1(bool op){
  if(op) garden->led_a->turnOn();
  else garden->led_a->turnOff();
}

void RoutineTask::checkLed2(bool op){
  if(op) garden->led_b->turnOn();
  else garden->led_b->turnOff();
}

void RoutineTask::checkLed3(String op){
  garden->led_c->setLuminosity(op.toInt());
}

void RoutineTask::checkLed4(String op){
  garden->led_d->setLuminosity(op.toInt());
}

void RoutineTask::checkIrrigation(String op){
  if(op == "change"){
    garden->servo->moveServo();
  }else{
    garden->servo->setSpeedServo(op.toInt());
  }
}

//void RoutineTask::setData(){
// if (btChannel.available()){
//    String msg = btChannel.readString();
//    this->garden->led_b->turnOff();
//    this->garden->state = MANUAL;
//    Serial.println(msg);
//  }
//
//  String msg = "";
//
//  
// 
//  
////  int incomingByte = 0; // for incoming serial data
////
////  
////  if (Serial.available() > 0) {
////    // read the incoming byte:
////    incomingByte = Serial.read();
////
////    // say what you got:
////    
////    Serial.print("{\"received\": 12 }");
////    Serial.println(incomingByte, DEC);
////  }
////  
//  
////  //while(Serial.available() > 0){
////  String msg = Serial.readString();
////  Serial.println("serial: " + msg );
////  if(msg != NULL){ 
////  this->garden->led_b->turnOff();
////  this->garden->state = MANUAL;
////  //}
////  }
////  
//}
