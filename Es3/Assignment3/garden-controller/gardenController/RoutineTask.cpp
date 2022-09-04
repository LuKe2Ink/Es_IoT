#include "RoutineTask.h"
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define SERVO_SPEED 5 

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
  readSerial();
  switch(this->garden->state){
    case AUTO:
    checkAlarmCondition();
     if(garden->sensorBoard->photoresistor->isLessThenMax()){
       turnOnAllLed();
       if(this->garden->stateIrrigation == OPERATING && garden->sensorBoard->photoresistor->isLessThenMin()){
          garden->servo->setSpeedServo(SERVO_SPEED);
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
       // Serial.println("manual try: " + msg);
        deserializeJson(doc, msg);
        JsonObject root = doc.as<JsonObject>();
        checkChanges(root);
      }
      break;
    case ALARM:
      if(btChannel.available()){
        String msg = btChannel.readString();
        //Serial.println("alarm try: " + msg);
        deserializeJson(doc, msg);
        JsonObject root = doc.as<JsonObject>();
        checkAlarmDeactivated(root);
      }
      break;
  }
  // print JSON on serial to comunicate with garden-service
  makeJson();
}

void RoutineTask::checkAlarmCondition(){
  int t = garden->sensorBoard->temp->getTemp();
  if(garden->sensorBoard->temp->getTemp() == 5 && garden->stateIrrigation == NOT_OPERATING){
    this->garden->state = ALARM;
    // LED esp turn on
    this->garden->led_esp->turnOn();
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
        Serial.println("failed serial msg: " + inData);
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }
      // reads temp and lumionosity
      int t = doc1["t"];
      int b = doc1["b"];
      // set temp and luminosity into virtual sensorboard
      garden->sensorBoard->temp->setTemp(t);
      garden->sensorBoard->photoresistor->setValue(b);
    }
}


void RoutineTask::makeJson(){
  StaticJsonDocument<200> doc;
  doc["led1"] = garden->led_a->getLuminosity() > 0;
  doc["led2"] = garden->led_b->getLuminosity() > 0;
  doc["led3"] = garden->led_c->getLuminosity();
  doc["led4"] = garden->led_d->getLuminosity();
  doc["led_esp"] = garden->led_esp->getLuminosity(); 
  doc["state"] = garden->state;
  doc["w"] = garden->stateIrrigation;
  //stampa json
  serializeJson(doc, Serial);
  // fondamentale
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
  if(garden->stateIrrigation == OPERATING){
      garden->servo->moveServo();
      garden->stateIrrigation = NOT_OPERATING; 
  }
}

void RoutineTask::checkManualControl(){
  if(btChannel.available()){
    StaticJsonDocument<200> docSerial;
    String msg = btChannel.readString();
    Serial.println(msg);
    DeserializationError error = deserializeJson(docSerial, msg);
      if (error) {
        Serial.println("failed blutooth msg: " + msg);
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }
    JsonObject root = docSerial.as<JsonObject>();
    int control = root["state"];
    Serial.println(control);
    if(control == 1){
      this->garden->state = MANUAL;
    }
  }
}

void RoutineTask::checkAlarmDeactivated(JsonObject root){

  this->garden->led_esp->turnOff();
  if(root.containsKey("state")){
    int state = root["state"];
    if(state == 1){
      this->garden->state = MANUAL;
    }else{
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
  if(root.containsKey("w")){
    int op = root["w"];
    if(op == 0) return;
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

void RoutineTask::checkIrrigation(int op){
  garden->servo->setSpeedServo(op);
  activateIrrigationSystem();
}
