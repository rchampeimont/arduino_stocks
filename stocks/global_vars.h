#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#define LCD_ROWS 4
#define LCD_COLS 20

struct stock {
  const char* symbol;
  double bookCost;
  double currentPrice;
  double gain;
};

extern struct stock compIndex;
extern struct stock myStocks[];
extern size_t stockCount;

void printStockStats(double averageChange);

#endif