#include <WiFiSSLClient.h>
#include "global_vars.h"

#define API_RETRIES 30

WiFiSSLClient client;

const char* host = "www.alphavantage.co";

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

int getDataForSymbol(struct stock* currentStock) {
  if (! connectToAPI()) return 0;

  const char* symbol = currentStock->symbol;
  String line = "", lastLine = "";

  printStatusMessageOnLCD(String("Getting ") + symbol);
  Serial.println(String("Getting ") + symbol);

  String path = String("/query?function=GLOBAL_QUOTE&symbol=") + symbol + "&apikey=" + ALPHAVANTAGE_API_KEY + "&datatype=csv";

  String request = String("GET ") + path + " HTTP/1.1\r\n" +
                  "Host: " + host + "\r\n" +
                  "Connection: close\r\n\r\n";

  Serial.println(request); // for debug
  client.print(request); // Send HTTP request

  while (client.connected() || client.available()) {
    if (client.available()) {
      char c = client.read();
      if (c == '\n') {
        //Serial.println(String("LINE: ") + line);
        lastLine = line;
        line = "";
      } else if (c == '\r') {
        // ignore CR
      } else {
        line += c;
      }
    }
  }
  Serial.println(String("LAST LINE: ") + lastLine);

  // Point pointer to first char of the price value
  const char* p = lastLine.c_str();
  int commaCount = 0;
  while (*p && commaCount < 4) {
    if (*p == ',') commaCount++;
    p++;
  }

  double price = atof(p);

  if (price != 0) {
    currentStock->currentPrice = price;
    currentStock->gain = (100.0f * (currentStock->currentPrice - currentStock->bookCost)) / currentStock->bookCost;
    
    displayStockInfo(currentStock);
  } else {
    printStatusMessageOnLCD(String("Cannot get ") + symbol);
    return 0;
  }

  return 1; // success
}

bool compareByGain(const stock& a, const stock& b) {
    return a.gain > b.gain;
}

int updateStockMarketData(double* averageChange) {
  double totalChanges = 0.0;
  
  if (! getDataForSymbol(&compIndex)) return 0;

  for (int i=0; i<stockCount; i++) {
    struct stock* currentStock = &myStocks[i];

    if (! getDataForSymbol(currentStock)) return 0;
    totalChanges += currentStock->gain;
  }

  *averageChange = totalChanges / stockCount;

  return 1; // success
}
