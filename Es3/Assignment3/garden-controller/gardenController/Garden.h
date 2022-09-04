#ifndef __GARDEN__
#define __GARDEN__

#define LED_A 13
#define LED_B 12
#define LED_C 11
#define LED_D 9
#define LED_ESP 9
#define TEMP A0
#define PHOTORESISTOR A1
#define SERVO 10

#include "Led.h"
#include "Temp.h"
#include "Photoresistor.h"
#include "ServoMotor.h"
#include "ServoMotorImpl.h"
#include "SensorBoard.h"

enum stato
{
  AUTO,
  MANUAL,
  ALARM
};

enum statoIrrigation
{
  OPERATING,
  NOT_OPERATING
};

class Garden {
    public:
        stato state;
        Led* led_a = new Led(LED_A);
        Led* led_b = new Led(LED_B);
        Led* led_c = new Led(LED_C);
        Led* led_d = new Led(LED_D);
        Led* led_esp = new Led(LED_ESP);
        SensorBoard* sensorBoard = new SensorBoard();
        ServoMotor *servo = new ServoMotorImpl(SERVO);
        statoIrrigation stateIrrigation;
        bool moveServo = false;
};

#endif
