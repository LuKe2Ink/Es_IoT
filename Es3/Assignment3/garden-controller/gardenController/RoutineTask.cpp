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
  //If the temperature value is equal to 5 and the irrigation system is in pause, the system status must be changed to ALARM.
  if(garden->sensorBoard->temp->getTemp() == 5 && !garden->servo->isIrrigationSystemOperating){
    this->garden->state = ALARM;
  }
  switch(this->garden->state){
    case AUTO:
      if(garden->sensorBoard->photoresistor->isLessThenMax()){
        turnOnAllLed();
        garden->led_c->setLuminosity(1);
        garden->led_d->setLuminosity(4);
        // decommentare questo che andrebbe letto da esp --> seriale
        garden->sensorBoard->photoresistor->setValue(1);
        if(!this->garden->servo->isIrrigationSystemOperating  && garden->sensorBoard->photoresistor->isLessThenMin()){
          this->garden->servo->isIrrigationSystemOperating = true;
          activateIrrigationSystem();
        }
      }else{
        turnOffAllLed();
      }
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
    //the operator intervention is requested both in the dashboard and in the app. The ALARM mode can be deactivated only by the operator using the app. 
      if (btChannel.available()){
         String bluetooth_message = btChannel.readString();
          Serial.println(bluetooth_message );
          // parso il JSON per vedere se ho disattivato ALARM
        DeserializationError error = deserializeJson(doc, bluetooth_message );

        // Test if parsing succeeds.
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return;
        }

        // per JSON cosi {"alarm" : 0}, 0 e' bool
        if(doc["alarm"]){
          this->garden->state = AUTO;
        }
      }
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
}

void RoutineTask::activateIrrigationSystem(){
  //garden->moveServo = true;
  garden->servo->moveServo();
}



// CASO MANUAL
// void RoutineTask::setData(){
//   // ma runnando questo codice, rileva i messaggi bluetooth da solo senza bloccare ?
//  if (btChannel.available()){
//     String bluetooth_message = btChannel.readString();
//     Serial.println(bluetooth_message );

//     // parso il JSON per vedere se ho switchato in manual mode
//     StaticJsonDocument<200> doc1;

//    DeserializationError error = deserializeJson(doc1, bluetooth_message );

//   // Test if parsing succeeds.
//   if (error) {
//     Serial.print(F("deserializeJson() failed: "));
//     Serial.println(error.f_str());
//     return;
//   }

//   if(doc1["state"] == "MANUAL"){
//     this->garden->state = MANUAL;
//   }

//   // Fetch values.
//   bool led = doc1["led1"];
//   bool led2 = doc1["led2"];
//   int led3 = doc1["led3"];
//   int led4 = doc1["led4"];
  
//   //irrigazione
//   int speed = doc1["water"];

//   if(led){
//     this->garden->led_a->turnOn();
//   }
//   if(led2){
//     this->garden->led_b->turnOn();
//   }
//   this->garden->led_c->setLuminosity(led3);
//   this->garden->led_c->setLuminosity(led4);


//   }


  
// }
 
  
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
}

void RoutineTask::checkLed4(String op){
  if(op == "inc"){
    int lum = garden->led_d->getLuminosity() + 1;
    garden->led_d->setLuminosity(lum);
  }else{
    int lum = garden->led_d->getLuminosity() - 1;
    garden->led_d->setLuminosity(lum);
  }
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
