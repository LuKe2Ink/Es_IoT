#include "Scheduler.h"
#include "Garden.h"

#include <ArduinoJson.h>

Scheduler scheda;
Garden* garden;

void setup() {
  // put your setup code here, to run once:
  //xSerial.begin(9600);
  Serial.begin(9600);
  garden = new Garden();
}

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
}
