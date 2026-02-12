// Code designed for Arduino Uno R4 Wifi

#include <math.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  initMatrix();
  initLCD();
  initWifi();
}

void loop() {
  float value = random(-100, 100) / 10.0;
  
  printNumberOnMatrix(value);
  updateLCD(value);

  delay(5000);
}
