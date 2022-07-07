#include "Scheduler.h"
#include "Garden.h"

#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define RX 2
#define TX 3

Scheduler scheda;
Garden* garden;

SoftwareSerial btChannel(RX, TX);


void setup() {
  // put your setup code here, to run once:
  //xSerial.begin(9600);
  Serial.begin(9600);
  garden = new Garden();
  btChannel.begin(9600);
  /////////////////////////////////////////  
  StaticJsonDocument<200> doc;
  doc["sensor"] = "gps";
  doc["time"] = 1351824120;

  JsonArray data = doc.createNestedArray("data");
  data.add(48.756080);
  data.add(2.302038);

  //stampa json
  serializeJsonPretty(doc, Serial);
/////////////////////////////////////////////////


////////////////////////////////////////////////////

 StaticJsonDocument<200> doc1;
 char json[] =
      "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

   DeserializationError error = deserializeJson(doc1, json);

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
  const char* sensor = doc1["sensor"];
  long time = doc1["time"];
  double latitude = doc1["data"][0];
  double longitude = doc1["data"][1];

  // Print values.
  Serial.println(sensor);
  Serial.println(time);
  Serial.println(latitude, 6);
  Serial.println(longitude, 6);

////////////////////////////////////////////////

}

String msg = "";

void loop() {
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
//        i = i - 5;
//    }

  garden->led_a->turnOn();
  garden->led_d->setLuminosity(0);

 if (btChannel.available()){
    msg = btChannel.readString();
    Serial.println(msg);
  }
  
}