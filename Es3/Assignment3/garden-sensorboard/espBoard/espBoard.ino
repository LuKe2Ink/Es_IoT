/*
 * HTTPClient lib --  Performing an HTTP POST to our REST service
 *
 * Remark:
 * - Going through ngrok
 *
 */
#include <WiFi.h>
#include <HTTPClient.h>

#define RED 18
#define ADC_VREF_mV    3300.0 // in millivolt
#define ADC_RESOLUTION 4096.0
#define PIN_LM35       1 // ESP32 pin GIOP36 (ADC0) connected to LM35
#define LIGHT_SENSOR_PIN 2 // ESP32 pin GIOP36 (ADC0)

const char* ssid = "Vodafone-A45840614";
const char* password = "p372xc2mywxb9sts";

const char *serviceURI = "https://9322-2-42-108-46.eu.ngrok.io";

String msg;

void connectToWifi(const char* ssid, const char* password){
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200); 
  pinMode(RED, OUTPUT);
  pinMode(LIGHT_SENSOR_PIN, OUTPUT);
  connectToWifi(ssid, password);
}

int sendData(String address, float value, String place, String msg){  
  
   HTTPClient http;    
   http.begin(address + "/garden/boardsensor");      
   http.addHeader("Content-Type", "application/json");    
    
//   String msg = 
//    String("{ \"origin\": ") + String(value) + 
//    ", \"place\": \"" + place +"\" }";
//   
    Serial.println(msg);
   
   int retCode = http.POST(msg);   
   http.end();  
      
   return retCode;
}

void loop() {
  digitalWrite(RED, HIGH);
   // read the ADC value from the temperature sensor
  int adcVal = analogRead(PIN_LM35);
  //Serial.print(adcVal);
  // convert the ADC value to voltage in millivolt
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  // convert the voltage to the temperature in °C
  float tempC = milliVolt / 10;
  // convert the °C to °F
  //float tempF = tempC * 9 / 5 + 32;



  int lumValue = analogRead(LIGHT_SENSOR_PIN);
  Serial.println(lumValue);
  lumValue = map(lumValue, 0, 1023, 0, 7);

  String msg = 
    String("{ \"origin\": ") + "\"sensor-board\"" + 
    ", \"temperature\": " + tempC + 
    ", \"luminosity\": " + lumValue + 
    + " }";
  //delay(500);

 // Serial.println(msg);
 
  if (WiFi.status()== WL_CONNECTED){      

    int value = random(15,20);
    int code = sendData(serviceURI, value, "home", msg);
    if (code == 200){
       Serial.println("ok");   
     } else {
       Serial.println(String("error: ") + code);
     }
    
    delay(1000);

  } else {
    Serial.println("WiFi Disconnected... Reconnect.");
    connectToWifi(ssid, password);
    }
}
