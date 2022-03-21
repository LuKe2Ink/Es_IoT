#define LEDa 13
#define LEDb 12
#define LEDc 11
#define LEDd 10

#define BTNa 9
#define BTNb 8
#define BTNc 7
#define BTNd 6

#define SETUP_GAME 0
#define ROUTINE 1
#define POLLING 2

#define SPEED 500

bool DEBUG = true;

int count;
int state;
int timer;
unsigned long limitTime;
int mov;
int score;
unsigned long startMillis;
unsigned long currentMillis;
const float F = 1.2;

void setup() {
  Serial.begin(9600);

  pinMode(LEDa, OUTPUT);
  pinMode(LEDb, OUTPUT);
  pinMode(LEDc, OUTPUT);
  pinMode(LEDd, OUTPUT);

  pinMode(BTNa, INPUT);
  pinMode(BTNb, INPUT);
  pinMode(BTNc, INPUT);
  pinMode(BTNd, INPUT);

  score=0;
  state = 0;
  limitTime = 10000;
}

void setupGame(){
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
    if(digitalRead(count-4) == HIGH){
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
  switch(state){
    case 0:
      setupGame();
    break;
    case 1:
      routine();
    break;
    case 2:
      polling();
    break;
    default:
    break;
  }
}
