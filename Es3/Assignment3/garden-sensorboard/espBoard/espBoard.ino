/*
 * HTTPClient lib --  Performing an HTTP POST to our REST service
 *
 * Remark:
 * - Going through ngrok
 *
 */
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Vodafone-A45840614";
const char* password = "";

const char *serviceURI = "https://9288-2-42-108-46.eu.ngrok.io";

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
  connectToWifi(ssid, password);
}

int sendData(String address, float value, String place){  
  
   HTTPClient http;    
   http.begin(address + "/garden/boardsensor");      
   //http.addHeader("Content-Type", "application/json");    
    
   String msg = 
    String("{ \"origin\": ") + String(value) + 
    ", \"place\": \"" + place +"\" }";
   
   int retCode = http.POST(msg);   
   http.end();  
      
   return retCode;
}

void loop() {
  if (WiFi.status()== WL_CONNECTED){      

    int value = random(15,20);
    int code = sendData(serviceURI, value, "home");
    if (code == 200){
       Serial.println("ok");   
     } else {
       Serial.println(String("error: ") + code);
     }
    
    delay(5000);

  } else {
    Serial.println("WiFi Disconnected... Reconnect.");
    connectToWifi(ssid, password);
  }
}
