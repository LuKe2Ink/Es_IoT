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

int count;
int state;
int timer;
int mov;
unsigned long startMillis;
unsigned long currentMillis;

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

  state = 0;
}

void setupGame(){
  count = 13;
  timer = random(1000, 10000);
  Serial.println(timer);
  startMillis = millis();
  state++;
}

void routine(){
  currentMillis = millis();
  digitalWrite(count, LOW);
  mov = count == 13 ? -1 : (count == 10 ? 1 : mov);
  count += mov;
  digitalWrite(count, HIGH);
  if(currentMillis - startMillis >= timer){
    state++;
  }
  delay(500);
}

void polling(){
  if(digitalRead(count-4) == LOW){
    Serial.println("Click");
    state=0;
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
