#include <LiquidCrystal.h>
#include "ArduinoGraphics.h"
#include "global_vars.h"

// Connections to the circuit: LCD screen
const int LCD_RS_PIN = 7;
const int LCD_ENABLE_PIN = 6;
const int LCD_DATA_PIN_D4 = 5;
const int LCD_DATA_PIN_D5 = 4;
const int LCD_DATA_PIN_D6 = 3;
const int LCD_DATA_PIN_D7 = 2;

LiquidCrystal lcd(LCD_RS_PIN, LCD_ENABLE_PIN, LCD_DATA_PIN_D4, LCD_DATA_PIN_D5, LCD_DATA_PIN_D6, LCD_DATA_PIN_D7);

void initLCD() {
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.noAutoscroll();
  lcd.clear();
}

void clearRowLCD(int row) {
  lcd.setCursor(0, row);
  for (int i=0; i<LCD_COLS; i++) {
    lcd.print(" ");
  }
}

void replaceRowLCD(int row, String s) {
  clearRowLCD(row);
  lcd.setCursor(0, row);
  lcd.print(s);
}

void printStatusMessageOnLCD(String s) {
  replaceRowLCD(0, s);
}
