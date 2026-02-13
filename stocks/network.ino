#include <SPI.h>
#include <WiFiS3.h>
#include "secrets.h"

int initWifi() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    printStatusMessageOnLCD("WiFi hard fail");
    return 0;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    printStatusMessageOnLCD("Upgrade firmware");
    return 0;
  }

  printStatusMessageOnLCD(WIFI_NAME "...");
  if (WiFi.begin(WIFI_NAME, WIFI_PASSWORD) != WL_CONNECTED) {
    printStatusMessageOnLCD("Connfail " WIFI_NAME);
    return 0;
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  printStatusMessageOnLCD("Wifi OK");
  return 1;
}

void stopWifi() {
  WiFi.end();
}
