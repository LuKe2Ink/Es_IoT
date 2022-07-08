#include <WiFi.h>
#include <HTTPClient.h>

#include "Photoresistor.h"
#include "Temp.h"

#define RED 18
#define PIN_LM35 1
#define LIGHT_SENSOR_PIN 2

const char *ssid = "Vodafone-A45840614";
const char *password = "p372xc2mywxb9sts";

const char *serviceURI = "https://9322-2-42-108-46.eu.ngrok.io";

String msg;
Photoresistor *photoresistor;
Temp *temp;

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

  pinMode(RED, OUTPUT);
  photoresistor = new Photoresistor(LIGHT_SENSOR_PIN);
  temp = new Temp(PIN_LM35);
  // First connection to WIFI
  connectToWifi(ssid, password);
}

int sendData(String address, String msg)
{

  HTTPClient http;
  http.begin(address + "/garden/boardsensor");
  http.addHeader("Content-Type", "application/json");

  Serial.println(msg);

  // add body to POST
  int retCode = http.POST(msg);
  http.end();

  return retCode;
}

void loop()
{
  digitalWrite(RED, HIGH);

  int tempC = temp->getTemp();

  int lumValue = photoresistor->getValue();

  String msg =
      String("{ \"origin\": ") + "\"sensor-board\"" +
      ", \"temperature\": " + tempC +
      ", \"luminosity\": " + lumValue +
      +" }";

  delay(350);

  if (WiFi.status() == WL_CONNECTED)
  {
    int code = sendData(serviceURI, msg);
    if (code == 200)
    {
      Serial.println("ok");
    }
    else
    {
      Serial.println(String("error: ") + code);
    }
    delay(1000);
  }
  else
  {
    Serial.println("WiFi Disconnected... Reconnect.");
    connectToWifi(ssid, password);
  }
}
