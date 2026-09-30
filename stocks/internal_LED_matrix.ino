#include "Arduino_LED_Matrix.h"
#include "global_vars.h"

ArduinoLEDMatrix matrix;

char textOnLedMatrix[10] = "";

void initMatrix() {
  matrix.begin();
}

void printNumberOnMatrix(float value) {
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  // The goal of the complex formula here for rounding is so that
  // the 2 digits on the LED display correspond to the digits before
  // the decmial point on the LCD screen.
  // For example if value is 18.97% we want to show
  // 19.0% on the LCD screen and 19% on the LED matrix.
  snprintf(textOnLedMatrix, sizeof(textOnLedMatrix), "%.0f%% ", floor(round(10*value)/10));
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(textOnLedMatrix);
  matrix.endText();
  matrix.endDraw();
}