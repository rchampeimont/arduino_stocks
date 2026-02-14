// Code designed for Arduino Uno R4 Wifi

#include <math.h>
#include "global_vars.h"

// Reload data every 12 hours (unit is ms)
#define UPDATE_PERIOD 43200000

// If cycle fails, retry after this number of seconds
#define CYCLE_RETRY_DELAY 600

void setup() {
  Serial.begin(9600); // for debug
  Serial.println("Restarted.");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  initMatrix();
}

int runOneCycle() {
  double averageChange;

  initLCD();
  if (! initWifi()) return 0;

  if (! updateStockMarketData(&averageChange)) return 0;
  Serial.println(String("Average change: ") + averageChange);
  
  // Print average gain on LED matrix on Arduino itself
  printNumberOnMatrix(averageChange);

  printStockStats(averageChange);

  return 1;
}

void announceRetryLCD(int seconds) {
  replaceRowLCD(LCD_ROWS - 1, String("Will retry in ") + seconds + String(" s"));
}

void loop() {
  int success = runOneCycle();

  // Stop Wifi chip which has burts of power causing LCD to flicker.
  stopWifi();

  if (success) {
    delay(UPDATE_PERIOD);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    for (int i=CYCLE_RETRY_DELAY; i>0; i--) {
      announceRetryLCD(i);
      delay(1000);
    }
  }
}
