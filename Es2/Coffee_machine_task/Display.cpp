#include <LiquidCrystal_I2C.h>
#include "Display.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LCD_ADDR, COLS, ROWS);

Display::Display()
{
  lcd.init();
  lcd.backlight();
}

void Display::setText(String msg)
{
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(msg);
}

void Display::off()
{
  // obscure display during sleep
  lcd.noBacklight();
}

void Display::on()
{
  lcd.backlight();
}
