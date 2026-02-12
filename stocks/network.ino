#include <SPI.h>
#include <WiFiS3.h>
#include "secrets.h"

void initWifi() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    fatalError("WiFi hard fail");
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    fatalError("Upgrade firmware");
  }

  printStatusMessageOnLCD("%s...", WIFI_NAME);
  if (WiFi.begin(WIFI_NAME, WIFI_PASSWORD) != WL_CONNECTED) {
    fatalError("Connfail %s", WIFI_NAME);
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  printStatusMessageOnLCD("Wifi OK");
}
