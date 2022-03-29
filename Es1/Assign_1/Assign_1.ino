#include <avr/sleep.h>

#include <EnableInterrupt.h>

#define LEDa 13
#define LEDb 12
#define LEDc 11
#define LEDd 10

#define BTNa 7
#define BTNb 6
#define BTNc 5
#define BTNd 4

#define RED 9
#define POT A0

#define SETUP_GAME 0
#define START 1
#define ROUTINE 2
#define POLLING 3
#define WAITING 4

#define TEN_SEC 10000
#define DIV 128


int count;
int state;
int speedLed;
int timer;
int mov;
double limitTime;
int score;
double diff;
int brightness = 0;
int fadeAmount = 5;
unsigned long startMillis;
unsigned long currentMillis;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  pinMode(LEDa, OUTPUT);
  pinMode(LEDb, OUTPUT);
  pinMode(LEDc, OUTPUT);
  pinMode(LEDd, OUTPUT);
  pinMode(RED, OUTPUT);

  pinMode(BTNa, INPUT);
  pinMode(BTNb, INPUT);
  pinMode(BTNc, INPUT);
  pinMode(BTNd, INPUT);
  
  setParams();
}

void setParams(){
  score=0;
  count = 12;
  mov = 1;
  speedLed = 1000;
  diff=0;
  state = 0;
  limitTime = 15000;
  Serial.println("Welcome to the Catch the Bouncing Led Ball Game. Press Key T1 to Start");
  startMillis = millis();
}

void setupGame(){
    currentMillis = millis();
     if(currentMillis - startMillis < TEN_SEC ){
       analogWrite(RED, brightness);
        brightness = brightness + fadeAmount;
        if (brightness <= 0 || brightness >= 255) {
          fadeAmount = -fadeAmount;
       } 
       delay(30);
     if(digitalRead(BTNa) == LOW){
        diff=(int)(analogRead(POT)/DIV);
        diff++;
        Serial.print("Difficult set to: ");
        Serial.println((int)diff);
        state++;
        digitalWrite(RED, LOW);
    }
  }else {
      sleepNow();
  }
}

void sleepNow()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
  digitalWrite(RED, LOW);
  enableInterrupt(BTNd, setTimer, RISING);
  enableInterrupt(BTNc, setTimer, RISING);
  enableInterrupt(BTNb, setTimer, RISING);
  enableInterrupt(BTNa, setTimer, RISING);

  sleep_enable(); 
 
  sleep_mode(); 

  sleep_disable(); 


  disableInterrupt(BTNb);
  disableInterrupt(BTNa);
  disableInterrupt(BTNd);
  disableInterrupt(BTNc);
}

void setTimer(){
  Serial.println("Waking up");
  startMillis = millis();
}

void startGame(){
  timer = random(1000, 10000);
  startMillis = millis();
  state++;
  if(score!= 0){
      limitTime -= (diff*100);
      speedLed-=(diff*10);
    }
}

void routine(){
  currentMillis = millis();
  digitalWrite(count, LOW);
  count += mov;
  mov = count == 13 ? -1 : (count == 10 ? 1 : mov);
  digitalWrite(count, HIGH);
  if(currentMillis - startMillis >= timer){
    state++;
    startMillis = millis();
    Serial.print("You have ");
    Serial.print(limitTime/1000);
    Serial.println(" seconds to press the button");
  }
  delay(speedLed);
}

void polling(){
  currentMillis = millis();
  if(currentMillis - startMillis < limitTime){
    if(digitalRead(count-6) == LOW){
    digitalWrite(count, LOW);
    score++;
    Serial.print("New point! Score: ");
    Serial.println(score);
    state=1;
    }
  }else{
    Serial.print("Game Over. Final Score: ");
    Serial.println(score);
    startMillis = millis();
    state++;
  }
}

void waiting(){
  digitalWrite(count, LOW);
  currentMillis = millis();
  if(currentMillis - startMillis >= TEN_SEC ){
    state=0;
    setParams();
  }
}

void loop() {
   switch(state){
    case 0:
      setupGame();
    break;
    case 1:
      startGame();
      break;
    case 2:
      routine();
    break;
    case 3:
      polling();
    break;
    case 4:
      waiting();
    break;
    default:
    break;
  }
}
