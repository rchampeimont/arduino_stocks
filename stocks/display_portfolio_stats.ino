#include "global_vars.h"
#include <algorithm>

void printStockStats(double averageChange) {
  // Print stats about porfolio on LCD display:
  // Summary line (first line):
  char summaryLine[LCD_COLS + 1];
  snprintf(summaryLine, sizeof(summaryLine), "River %.1f%% SP %.1f%%", averageChange, compIndex.gain);
  replaceRowLCD(0, String(summaryLine));

  // Sort stocks by gain
  std::sort(myStocks, myStocks + stockCount, compareByGain);

  // Debug: Print on serial stocks ordered by gain
  for (int i=0; i<stockCount; i++) {
    struct stock* currentStock = &myStocks[i];

    Serial.println(String(currentStock->symbol)
      + String(" Price: ") + currentStock->currentPrice
      + String(" / Book cost: ") + currentStock->bookCost
      + String(" / Gain: ") + currentStock->gain + String(" %"));
  }

}
