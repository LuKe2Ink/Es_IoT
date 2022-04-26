#include "MsgService.h"
#include "Display.h"
#include "Product.h"
#include "ButtonImpl.h"
#include <EnableInterrupt.h>

enum {
  WELCOME,
  READY,
  SELECT,
  MAKING
}state;

#define N_MAX_QUANTITY 50
#define B_UP 2
#define B_DOWN 3
#define B_MAKE 4
#define T_OUT 5000L



Display* display_lcd;
Product* coffee;
Product* tea;
Product* chocolate;
Button* bUp;
Button* bDown;
Button* bMake;
int selectedProduct;
String productName[] = {"Coffee", "Tea", "Chocolate"};
unsigned long startMillis;
unsigned long currentMillis;

void setup() {
  /*MsgService.init();*/
  Serial.begin(9600);
  state = WELCOME;
  display_lcd = new Display();
  coffee = new Product(N_MAX_QUANTITY);
  tea = new Product(N_MAX_QUANTITY);
  chocolate = new Product(N_MAX_QUANTITY);
  bUp = new ButtonImpl(B_UP);
  bDown = new ButtonImpl(B_DOWN);
  bMake = new ButtonImpl(B_MAKE);

}

void loop() {

  switch(state){
    case WELCOME:
        display_lcd->setText("Welcome");
        Serial.println("Welcome");
        delay(4000);
        state = READY;
    break;
    case READY:
      display_lcd->setText("Ready");
      selectedProduct = 0;
      startMillis = 0;
      Serial.println("Ready");
      state = SELECT;
    break;
    case SELECT:
      enableInterrupt(B_UP, incSelect, RISING);
      enableInterrupt(B_DOWN, decSelect, RISING);
      enableInterrupt(B_MAKE, makeProduct, RISING);
      
      currentMillis = millis();

      if(currentMillis - startMillis > T_OUT && startMillis != 0){
        state = READY;
      }
      
      disableInterrupt(B_UP);
      disableInterrupt(B_DOWN);
      disableInterrupt(B_MAKE);
    break;
  }
 
}

void incSelect(){
  if(selectedProduct < 2){
    selectedProduct++;
    Serial.println(productName[selectedProduct]);
  }
  startTimer();
}

void decSelect(){
  if(selectedProduct > 0){
    selectedProduct--;
    Serial.println(productName[selectedProduct]);
  }
  startTimer();
}

void makeProduct(){
  //display_lcd->setText("Make");
  Serial.print("Making: ");
  Serial.println(productName[selectedProduct]);
  checkSugar();
}

void startTimer(){
  startMillis = millis();
}

void checkSugar(){
  int sugarValue = analogRead(A0);
  sugarValue /= 128;
  sugarValue /= 2;
  Serial.print(sugarValue);
  Serial.println(" cucchiaini di zucchero");
}
