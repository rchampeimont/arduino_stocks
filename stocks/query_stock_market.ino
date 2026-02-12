#include <WiFiSSLClient.h>

#define API_RETRIES 5

WiFiSSLClient client;

const char* host = "www.alphavantage.co";

void getDataForSymbol(const char* symbol) {
  String line;

  printStatusMessageOnLCD("Getting %s", symbol);

  String path = String("/query?function=GLOBAL_QUOTE&symbol=") + symbol + "&apikey=" + ALPHAVANTAGE_API_KEY + "&datatype=csv";

  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  // Skip HTTP headers
  while (client.connected()) {
    line = client.readStringUntil('\n');
    if (line == "\r") break;
  }

  int lineIndex = 0;
  while (client.connected()) {
    line = client.readStringUntil('\n');
    Serial.print(line);
    lineIndex++;
    if (lineIndex == 2) break;
  }

  if (lineIndex < 2) {
    fatalError("Miss line for %s", symbol);
  }

  double open, high, low, price;
  sscanf(line.c_str(), "%s,%f,%f,%f,%f", &open, &high, &low, &price);

  printStatusMessageOnLCD("%s: %f", symbol, price);
}

void connectToAPI() {
  for (int i=0; i<API_RETRIES; i++) {
    printStatusMessageOnLCD("Conn to API...");
    if (client.connect(host, 443)) {
      printStatusMessageOnLCD("Connected to API");
      return;
    } else {
      printStatusMessageOnLCD("Will retry API");
      delay(5000);
    }
  }
  fatalError("API fail gave up");
}

void updateStockMarketData() {
  connectToAPI();
  getDataForSymbol("COST");
}