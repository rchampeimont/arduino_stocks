#include <SPI.h>
#include <WiFiS3.h>
#include "secrets.h"

WiFiClient client;

void stop() {
  digitalWrite(LED_BUILTIN, HIGH);
  while (true);
}

void initWifi() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    printStatusMessageOnLCD("WiFi hard fail");
    stop();
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    printStatusMessageOnLCD("Upgrade firmware");
    stop();
  }

  //WiFi.lowPowerMode();

  printStatusMessageOnLCD("%s...", WIFI_NAME);
  if (WiFi.begin(WIFI_NAME, WIFI_PASSWORD) != WL_CONNECTED) {
    printStatusMessageOnLCD("FAIL %s", WIFI_NAME);
    stop();
  }

  printStatusMessageOnLCD("Wifi OK");
}
