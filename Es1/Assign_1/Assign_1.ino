#include <Sleep_n0m1.h>

#define LEDa 13
#define LEDb 12
#define LEDc 11
#define LEDd 10

#define BTNa 5
#define BTNb 4
#define BTNc 3
#define BTNd 2

#define RED 7
#define POT 3

#define SETUP_GAME 0
#define START 1
#define ROUTINE 2
#define POLLING 3

#define SPEED 500



bool DEBUG = true;

int count;
int state;
int timer;
unsigned long limitTime;
int mov;
int score;
int brightness = 0;
int fadeAmount = 5;
unsigned long startMillis;
unsigned long currentMillis;

const float F = 1.4;

void setup() {
  Serial.begin(9600);

  pinMode(LEDa, OUTPUT);
  pinMode(LEDb, OUTPUT);
  pinMode(LEDc, OUTPUT);
  pinMode(LEDd, OUTPUT);
  pinMode(RED, OUTPUT);

  pinMode(BTNa, INPUT);
  pinMode(BTNb, INPUT);
  pinMode(BTNc, INPUT);
  pinMode(BTNd, INPUT);

  score=0;
  state = 0;
  limitTime = 10000;

  Serial.println("Welcome to the Catch the Bouncing Led Ball Game. Press Key T1 to Start");
  startMillis = millis();
}

void start(){
  count = 13;
  timer = random(1000, 10000);
  startMillis = millis();
  state++;

  if(score!= 0){
      limitTime /=F;
      if(DEBUG){
          Serial.print("Now i will wait   ");
          Serial.println(limitTime);
        }
    }
}

void setupGame(){
    Serial.println("ECCCO");
    currentMillis = millis();
     if(currentMillis - startMillis < limitTime){
       analogWrite(RED, brightness);
        brightness = brightness + fadeAmount;
        if (brightness <= 0 || brightness >= 255) {
          fadeAmount = -fadeAmount;
       } 
       delay(30);
     if(digitalRead(BTNa) == HIGH){
        state++;
        digitalWrite(RED, LOW);
    }
  }else {
      Serial.println("Ngul a' mammt'");
      sleepNow();
  }
}

  void sleepNow() // here we put the arduino to sleep
{
set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
// enables the sleep bit in the mcucr register
// so sleep is possible. just a safety pin
/* Now it is time to enable an interrupt.*/
attachInterrupt(digitalPinToInterrupt(BTNd),cacca, LOW); // use interrupt 0 (pin 2) and run function
sleep_enable(); 
// wakeUpNow when pin 2 gets LOW
sleep_mode(); // here the device is actually put to sleep!!
// THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP



Serial.println("Ngul a' mammt'");

sleep_disable(); // first thing after waking from sleep:
// disable sleep...
detachInterrupt(digitalPinToInterrupt(BTNd)); // disables interrupt 0 on pin 2 so the
// wakeUpNow code will not be executed
// during normal running time.
}

void cacca(){
  Serial.println("SOno una cacca");
  }


void routine(){
  currentMillis = millis();
  digitalWrite(count, LOW);
  mov = count == 13 ? -1 : (count == 10 ? 1 : mov);
  count += mov;
  digitalWrite(count, HIGH);
  if(currentMillis - startMillis >= timer){
    state++;
    startMillis = millis();
  }
  delay(SPEED);
  if(DEBUG){
    Serial.print("lamping led: "); 
    Serial.println(count);
    }
}

void polling(){
  if(DEBUG){
    Serial.println("Im waiting hooman...."); 
  }
  currentMillis = millis();
  if(currentMillis - startMillis < limitTime){
    if(digitalRead(count-8) == LOW){
    score++;
    Serial.print("New point! Score: ");
    Serial.println(score);
    state=0;
    }
  }else{
    Serial.print("Game Over. Final Score: ");
    Serial.print(score);
    state++;
  }
}

void loop() {
  //Serial.println(analogRead(A0));
   switch(state){
    case 0:
      setupGame();
    break;
    case 1:
      start();
      break;
    case 2:
      routine();
    break;
    case 3:
      polling();
    break;
    default:
    break;
  }
}
