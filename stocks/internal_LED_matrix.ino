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
  snprintf(textOnLedMatrix, sizeof(textOnLedMatrix), "%.0f%% ", value);
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(textOnLedMatrix);
  matrix.endText();
  matrix.endDraw();
}