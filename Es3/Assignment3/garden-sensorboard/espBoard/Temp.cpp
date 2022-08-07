#include "Temp.h"
#include "Arduino.h"

Temp::Temp(int pin)
{
  this->pin = pin;
}
#define ADC_VREF_mV    3300.0 // in millivolt
#define ADC_RESOLUTION 4096.0

int Temp::getTemp()
{
  // analog read in esp32 is a value between 0 and 4095, so i tried to map it
 
   int adcVal = analogRead(this->pin);
  // convert the ADC value to voltage in millivolt
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  // convert the voltage to the temperature in °C
  float tempC = milliVolt / 10;
  // convert the °C to °F
  float tempF = tempC * 9 / 5 + 32;

  // print the temperature in the Serial Monitor:
//  Serial.print("Temperature: ");
//  Serial.print(tempC);   // print the temperature in °C
//  Serial.print("°C");
//  Serial.print("  ~  "); // separator between °C and °F
//  Serial.print(tempF);   // print the temperature in °F
//  Serial.println("°F");
//  Serial.println(map(tempC, 0 , 29, 0, 5));
    return map(tempC, 0 , 29, 0, 5);
//  return (analogRead(this->pin) * 0.48828125);
}
