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
  // reads data from serial, JSON sent by garden-service
  //TODO i dati vanno letti solo nella modalita AUTO altrimenti bisogna (non so come) inviare i dati all'esp per fargli ricevere il comando di accendere un led 
  readSerial();
//  this->setData();
  switch(this->garden->state){
    checkAlarmCondition();
    case AUTO:
    // Serial.print("light: ");
    // Serial.println(garden->sensorBoard->photoresistor->getValue());
    // Serial.print("temp: ");
    // Serial.println(garden->sensorBoard->temp->getTemp());
//TODO ora arduino riceve i dati sulla seriale dal server che li riceve dall'esp e li invia 
     if(garden->sensorBoard->photoresistor->isLessThenMax()){
       turnOnAllLed();
       if(this->garden->stateIrrigation == NOT_OPERATING && garden->sensorBoard->photoresistor->isLessThenMin()){
         this->garden->stateIrrigation = OPERATING;
         activateIrrigationSystem();
       }
     }else{
       turnOffAllLed();
     }
      checkManualControl();
      break;
    case MANUAL:
    checkAlarmCondition();
      if(btChannel.available()){
        String msg = btChannel.readString();
        // Serial.println(msg);
        deserializeJson(doc, msg);
        JsonObject root = doc.as<JsonObject>();
        Serial.println("{\"MANUELLLLL\" : 0}");
        checkChanges(root);
      }
      break;
    case ALARM:
      if(btChannel.available()){
        String msg = btChannel.readString();
        // Serial.println(msg);
        deserializeJson(doc, msg);
        JsonObject root = doc.as<JsonObject>();
        checkAlarmDeactivated(root);
      }
      break;
  }
  
  // print JSON on serial to comunicate with garden-service
  //TODO decomentare
  makeJson();
}

void RoutineTask::checkAlarmCondition(){
  if(garden->sensorBoard->temp->getTemp() == 5 && garden->stateIrrigation == NOT_OPERATING){
    this->garden->state = ALARM;
    // LED esp tunr on
    this->garden->led_esp->turnOn();
    //TODO spegnerlo da qualche parte....
  }
}

void RoutineTask::readSerial(){
  String inData = "";
    if(Serial.available() > 0){
      inData = Serial.readString();
      //make inData a JSON obj
      StaticJsonDocument<200> doc1;
      DeserializationError error = deserializeJson(doc1, inData);
      // Test if parsing succeeds.
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        Serial.println(inData);
        return;
      }
      //reads temp and lumionosity
      garden->sensorBoard->temp->setTemp(doc1["temp"]);
      garden->sensorBoard->photoresistor->setValue(doc1["bright"]);
    }
}


void RoutineTask::makeJson(){
  StaticJsonDocument<200> doc;
  //
  // doc["sensor"] = "gps";
  // doc["time"] = 1351824120;
  
  //
  doc["led1"] = garden->led_a->getLuminosity() > 0;
  doc["led2"] = garden->led_b->getLuminosity() > 0;
  doc["led3"] = garden->led_c->getLuminosity();
  doc["led4"] = garden->led_d->getLuminosity();
  // doc["led_esp"] = garden->led_esp->getLuminosity(); //TODO is on
  // doc["led_esp"] = 1; //TEST
  doc["state"] = garden->state;
  //TODO NON CI GIUREREI 
  doc["water"] = garden->stateIrrigation;
  // JsonArray data = doc.createNestedArray("data");
  // data.add(48.756080);
  // data.add(2.302038);
  //
  //  //stampa json
  serializeJson(doc, Serial);
  //  // fondamentale
  Serial.println("\r\n");
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
  if(garden->stateIrrigation == OPERATING){
      garden->servo->moveServo();
      garden->stateIrrigation = NOT_OPERATING; 
  }
}

void RoutineTask::checkManualControl(){
  if(btChannel.available()){
    String msg = btChannel.readString();
    // Serial.println(msg);
    deserializeJson(doc, msg);
    JsonObject root = doc.as<JsonObject>();
    String control = root["state"];
    Serial.println(root);
    Serial.println("ZIO CAN");
    if(control == "manual"){
      this->garden->state = MANUAL;
      checkChanges(root);
    }
  }
}

void RoutineTask::checkAlarmDeactivated(JsonObject root){
  if(root.containsKey("state")){
    String state = root["state"];
    if(state == "manual"){
      this->garden->state = MANUAL;
    }else if(state == "auto"){
      this->garden->state = AUTO;
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
    activateIrrigationSystem();
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
