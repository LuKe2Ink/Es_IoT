#include <WiFi.h>
#include <HTTPClient.h>
#include "Scheduler.h"
#include "SensorBoard.h"

//const char *ssid = "Vodafone-A45840614";
const char *ssid = "TCL";
const char *password = "caccapopo";

Scheduler scheda;
SensorBoard* sensorboard;

void connectToWifi(const char *ssid, const char *password)
{
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup()
{
  Serial.begin(115200);
  // First connection to WIFI
  connectToWifi(ssid, password);

  scheda.init(100);
  sensorboard = new SensorBoard();
  sensorboard->init(1000);
  scheda.addTask(sensorboard);
}



void loop()
{
  //digitalWrite(RED, HIGH);

  if (WiFi.status() == WL_CONNECTED)
  {
    //tick()
/*     int code = sendData(serviceURI, msg);
    if (code == 200)
    {
      Serial.println("ok");
    }
    else
    {
      Serial.println(String("error: ") + code);
    }
    delay(1000); */
    scheda.schedule();
  }
  else
  {
    Serial.println("WiFi Disconnected... Reconnect.");
    connectToWifi(ssid, password);
  }
}
