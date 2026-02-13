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

  if (line.indexOf("rate limit") != -1) {
    printStatusMessageOnLCD("API rate limit error");
    return 0; // fail
  }

  // Gather last line
  if (lineIndex < 2) {
    line = "";
    while (client.connected() || client.available()) {
      if (client.available()) {
        char c = client.read();
        line += c;
      }
    }
    Serial.println(line);
  }

  Serial.println(String("Will parse line: ") + line);

  // Point pointer to first char of price value
  const char* p = line.c_str();
  int commaCount = 0;
  while (*p && commaCount < 4) {
    if (*p == ',') commaCount++;
    p++;
  }

  float price = atof(p);

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
  for (int i=0; i<stockCount; i++) {
    if (! connectToAPI()) return 0;
    if (! getDataForSymbol(myStocks[i])) return 0;
  }
  return 1; // success
}