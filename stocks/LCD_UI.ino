#include <LiquidCrystal.h>
#include "ArduinoGraphics.h"

// Connections to the circuit: LCD screen
const int LCD_RS_PIN = 7;
const int LCD_ENABLE_PIN = 6;
const int LCD_DATA_PIN_D4 = 5;
const int LCD_DATA_PIN_D5 = 4;
const int LCD_DATA_PIN_D6 = 3;
const int LCD_DATA_PIN_D7 = 2;

LiquidCrystal lcd(LCD_RS_PIN, LCD_ENABLE_PIN, LCD_DATA_PIN_D4, LCD_DATA_PIN_D5, LCD_DATA_PIN_D6, LCD_DATA_PIN_D7);

#define LCD_ROWS 2
#define LCD_COLS 16

#define MAX_STATUS_MESSAGE_LENGTH (LCD_ROWS * LCD_COLS)

void initLCD() {
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.clear();
}

void updateLCD(float value) {
  initLCD();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(value);
}

void printStatusMessageOnLCD(const char *format, ...) {
  char buf[MAX_STATUS_MESSAGE_LENGTH + 1];
  va_list args;
  va_start(args, format);
  vsnprintf(buf, MAX_STATUS_MESSAGE_LENGTH + 1, format, args);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(buf);
  delay(2000);

  va_end(args);
}
