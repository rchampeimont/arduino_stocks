// Code designed for Arduino Uno R4 Wifi

#include <math.h>

// Reload data every 24 hours (unit is ms)
#define UPDATE_PERIOD 86400000

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
  initLCD();
  if (! initWifi()) return 0;

  float value = random(-100, 100) / 10.0;
  if (!updateStockMarketData()) return 0;
  printNumberOnMatrix(value);

  return 1;
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
