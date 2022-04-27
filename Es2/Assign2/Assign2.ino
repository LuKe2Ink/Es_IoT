
#define BTN_UP 7
#define BNT_DOWN 6
#define MAKE_BTN 5
#define PIR_PIN 4
#define TEMP_PIN A0 
#define TRIG 13
#define ECHO 12
#define POT A1


#define CALIBRATION_TIME_SEC 10

const float vs = 331.45 + 0.62*20;


#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo servo;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);
/* Wiring: SDA => A4, SCL => A5 */
/* I2C address of the LCD: 0x27 */

void setup() {
  //LDC setup
  lcd.init();
  lcd.backlight();

  //Choice buttons
  pinMode(BTN_UP, INPUT);
  pinMode(BNT_DOWN, INPUT);
  pinMode(MAKE_BTN, INPUT);

  //Pulsar setup 
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT); 
  Serial.begin(9600);

  //Servo motor 
  servo.attach(10);

  // Pir 
  pinMode(PIR_PIN,INPUT);

   Serial.print("Calibrating sensor... ");
  for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("PIR SENSOR READY.");
  delay(50);

  // Pot 
}

float getDistance()
{
    /* invio impulso */
    digitalWrite(TRIG,LOW);
    delayMicroseconds(3);
    digitalWrite(TRIG,HIGH);
    delayMicroseconds(5);
    digitalWrite(TRIG,LOW);
    
    /* ricevi l’eco */
    float tUS = pulseIn(ECHO, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*vs;
    return d;
}

int val = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(MAKE_BTN) == HIGH){
      Serial.println("cacca");
    }

    int temp = analogRead(TEMP_PIN);
    int value_in_mV = temp *  4.8876 ;
    double value_in_C = value_in_mV * 0.1;
    
    
    lcd.setCursor(2, 2); // Set the cursor on the third column and first row.

    float d = getDistance();
    lcd.print(String("Distance: ") + d);

    

    servo.write(val%180);
    Serial.println(val);
    val += 30;


  int detected = digitalRead(PIR_PIN);
  if (detected == HIGH){
    Serial.println("detected!");  
  }
    
    delay(500);

  int newValue = analogRead(POT_PIN);
  if (newValue != current){
    current = newValue;
    Serial.println(current);
  }
}
