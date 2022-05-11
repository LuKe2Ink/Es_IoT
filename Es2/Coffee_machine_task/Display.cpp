#include <LiquidCrystal_I2C.h>
#include "Display.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

Display::Display() {
  lcd.init();
  lcd.backlight();
}

void Display::setText(String msg) {
  lcd.clear();
  lcd.setCursor(0, 1); // Set the cursor on the third column and first row.
  lcd.print(msg);
}

void Display::off(){
  lcd.noBacklight();
}

void Display::on(){
  lcd.backlight();
}
