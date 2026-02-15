#include "global_vars.h"
#include <algorithm>

#define GAIN_PRFIX " Gain: "

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

void displayStockInfo(struct stock* currentStock) {
  replaceRowLCD(1, String(currentStock->symbol) + " " + currentStock->currentPrice);
  replaceRowLCD(2, String(" Book cost: ") + currentStock->bookCost);

  char pct[LCD_COLS - sizeof(GAIN_PRFIX) + 1];
  snprintf(pct, sizeof(pct), "%+.1f %%", currentStock->gain);

  replaceRowLCD(3, String(GAIN_PRFIX) + pct);
}

// Cycle through stocks on the LCD display
void cycleThroughStocks(unsigned long delaySeconds, unsigned long totalTimeSeconds) {
  unsigned long endAfterCount = totalTimeSeconds / delaySeconds;
  for (unsigned long i=0; i<endAfterCount; i++) {
    struct stock* currentStock = &myStocks[i % stockCount];
    displayStockInfo(currentStock);
    delay(1000 * delaySeconds);
  }
}