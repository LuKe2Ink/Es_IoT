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
    deserializeJson(doc, msg);
    JsonObject root = doc.as<JsonObject>();
    String control = root["control"];
    Serial.println(control);
    if(control == "manual"){
      this->garden->state = MANUAL;
    }
  }
}

void RoutineTask::checkChanges(JsonObject root){
  if(root.containsKey("led1")){
    checkLed1();
    return;
  }
  if(root.containsKey("led2")){
    checkLed2();
    return;
  }
  if(root.containsKey("led3")){
    String op = root["led3"];
    checkLed3(op);
    return;
  }
  if(root.containsKey("led4")){
    String op = root["led4"];
    checkLed4(op);
    return;
  }
  if(root.containsKey("irrigation")){
    String op = root["irrigation"];
    checkIrrigation(op);
    return;
  }
}

void RoutineTask::checkLed1(){
  if(garden->led_a->isOn()) garden->led_a->turnOff();
  else garden->led_a->turnOn();
}

void RoutineTask::checkLed2(){
  if(garden->led_b->isOn()) garden->led_b->turnOff();
  else garden->led_b->turnOn();
}

void RoutineTask::checkLed3(String op){
  if(op == "inc"){
    int lum = garden->led_c->getLuminosity() + 1;
    garden->led_c->setLuminosity(lum);
  }else{
    int lum = garden->led_c->getLuminosity() - 1;
    garden->led_c->setLuminosity(lum);
  }
  Serial.println(garden->led_c->getLuminosity());
}

void RoutineTask::checkLed4(String op){
  if(op == "inc"){
    int lum = garden->led_d->getLuminosity() + 1;
    garden->led_d->setLuminosity(lum);
  }else{
    int lum = garden->led_d->getLuminosity() - 1;
    garden->led_d->setLuminosity(lum);
  }
  Serial.println(garden->led_d->getLuminosity());
}

void RoutineTask::checkIrrigation(String op){
  if(op == "change"){
    garden->servo->moveServo();
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
