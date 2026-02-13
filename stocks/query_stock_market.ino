#include <WiFiSSLClient.h>

#define API_RETRIES 30

WiFiSSLClient client;

const char* host = "www.alphavantage.co";

int getDataForSymbol(const char* symbol) {
  String line;

  printStatusMessageOnLCD(String("Getting symbol ") + symbol);

  String path = String("/query?function=GLOBAL_QUOTE&symbol=") + symbol + "&apikey=" + ALPHAVANTAGE_API_KEY + "&datatype=csv";

  String request = String("GET ") + path + " HTTP/1.1\r\n" +
                  "Host: " + host + "\r\n" +
                  "Connection: close\r\n\r\n";

  Serial.println(request); // for debug
  client.print(request); // Send HTTP request

  // Skip HTTP headers
  while (client.connected()) {
    line = client.readStringUntil('\n');
    Serial.println(line);
    if (line == "\r") break;
  }

  int lineIndex = 0;
  while (client.connected()) {
    line = client.readStringUntil(lineIndex == 1 ? '%' : '\n');
    Serial.println(line);
    lineIndex++;
    if (lineIndex == 2) break;
  }

  if (lineIndex < 2) {
    printStatusMessageOnLCD(String("Miss line for ") + symbol);
    return 0; // fail
  }

  if (line.indexOf("rate limit") != -1) {
    printStatusMessageOnLCD("API rate limit error");
    return 0; // fail
  }

  double open, high, low, price;
  sscanf(line.c_str(), "%s,%f,%f,%f,%f", &open, &high, &low, &price);

  printStatusMessageOnLCD(String(symbol) + " " + price);
  return 1; // success
}

int connectToAPI() {
  for (int i=0; i<API_RETRIES; i++) {
    printStatusMessageOnLCD("Conn to API...");
    if (client.connect(host, 443)) {
      printStatusMessageOnLCD("Connected to API");
      return 1; // success
    } else {
      printStatusMessageOnLCD("Will retry API");
      delay(1000);
    }
  }
  printStatusMessageOnLCD("API fail gave up");
  return 0; // fail
}

int updateStockMarketData() {
  if (! connectToAPI()) return 0;
  if (! getDataForSymbol("COST")) return 0;
  return 1; // success
}