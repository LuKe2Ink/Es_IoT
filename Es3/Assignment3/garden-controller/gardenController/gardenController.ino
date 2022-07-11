#include "Scheduler.h"
#include "Garden.h"

#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "RoutineTask.h"
#include "IrrigationTask.h"

#define RX 2
#define TX 3

Scheduler scheda;
Garden* garden;
RoutineTask *routine;
IrrigationTask *irrigation;

//SoftwareSerial btChannel(RX, TX);

void setup() {
  Serial.begin(9600);
  garden = new Garden();
 // btChannel.begin(9600);
  scheda.init(100);

  routine = new RoutineTask(garden);
  //routine->tick();
  routine->init(100);
  scheda.addTask(routine);

  irrigation = new IrrigationTask(garden);
  irrigation->init(20);
  scheda.addTask(irrigation);
  /////////////////////////////////////////  
//   StaticJsonDocument<200> doc;
//
//  doc["sensor"] = "gps";
//  doc["time"] = 1351824120;
//
//  JsonArray data = doc.createNestedArray("data");
//  data.add(48.756080);
//  data.add(2.302038);
//
//  //stampa json
//  serializeJson(doc, Serial);
//  // fondamentale
//  Serial.println("\r\n");

/////////////////////////////////////////////////


////////////////////////////////////////////////////
//
// StaticJsonDocument<200> doc1;
// char json[] =
//      "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
//
//   DeserializationError error = deserializeJson(doc1, json);
//
//  // Test if parsing succeeds.
//  if (error) {
//    Serial.print(F("deserializeJson() failed: "));
//    Serial.println(error.f_str());
//    return;
//  }
//
//  // Fetch values.
//  //
//  // Most of the time, you can rely on the implicit casts.
//  // In other case, you can do doc["time"].as<long>();
//  const char* sensor = doc1["sensor"];
//  long time = doc1["time"];
//  double latitude = doc1["data"][0];
//  double longitude = doc1["data"][1];


  // Print values.
  /*Serial.println(sensor);
  Serial.println(time);
  Serial.println(latitude, 6);
  Serial.println(longitude, 6);*/
////////////////////////////////////////////////

  garden->state = AUTO;

}

//String msg = "";

String inData = "";


void loop() {
 scheda.schedule(); 


// while (Serial.available() > 0) {
//        char received = Serial.read();
//        inData.concat(received);
//
//        // Process message when new line character is received
//        if (received == '\n') {
//            // Message is ready in inDate
//            break;
//        }
//    }
//    Serial.print(inData);
    if(Serial.available() > 0){
      inData = Serial.readString();
  

   // Serial.println(inData);
 StaticJsonDocument<200> doc1;
// char json[] =
//      "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

   DeserializationError error = deserializeJson(doc1, inData);

  //Serial.println(String(inData));
  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  // Fetch values.
  //

  
  
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do doc["time"].as<long>();
  
  int led = doc1["led1"];
  int led2 = doc1["led2"];
  int led3 = doc1["led3"];
  int led4 = doc1["led4"];
  
    //Serial.println(led);
 //   Serial.println(led2);
    Serial.println(led3);
  //  Serial.println(led4);

    if(led3 == 0){
        garden->led_c->setLuminosity(0);
      }else {
        garden->led_d->setLuminosity(0);
     }
   }
    inData = " ";



//  if (Serial.available() > 0) {
//    String incomingString = Serial.readString();
//
//    // prints the received data
//    //Serial.print("I received: ");
//    Serial.println(incomingString);
//  }
  // put your main code here, to run repeatedly:
  //garden->led_c->turnOn();
//  int i;
//
//  i = 0;
//    while ( i <= 255 ){
//      garden->led_c->setLuminosity(i);
//        delay( 50);
//        i = i + 5;
//    }
//
//    i = 255;
//    while ( i >= 0 ){
//      garden->led_c->setLuminosity(i);
//        delay( 50);
//        i = i - 5;  StaticJsonDocument<200> doc;
  //serializeJson(doc, Serial);
//  
//  garden->led_a->turnOn();
//  garden->led_d->setLuminosity(0);
//
// if (btChannel.available()){
//    msg = btChannel.readString();
//    Serial.println(msg);
//  }
///////////////////////////////////////////  
//   StaticJsonDocument<200> doc;
//
//  doc["led1"] = garden->led_a->getLuminosity();
//  doc["led2"] = garden->led_b->getLuminosity();
//  doc["led3"] = garden->led_c->getLuminosity();
//  doc["led4"] = garden->led_d->getLuminosity();
//
//  doc["water"] = 0;
//
////  JsonArray data = doc.createNestedArray("data");
////  data.add(48.756080);
////  data.add(2.302038);
//
//  //stampa json
//  serializeJson(doc, Serial);
//  // fondamentale
//  Serial.println("\r\n");
//
///////////////////////////////////////////////////
//  delay(500);

  /*
  if (garden.obj != null){
    scheda.schedule();
  }
  */
  
}
