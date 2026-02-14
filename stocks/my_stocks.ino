#include "global_vars.h"

// Index for comparison with portfolio
struct stock compIndex = { "IVV", 695.32 }; // S&P 500 ETF

struct stock myStocks[] = {
  { "RMS.PAR", 2150.0 }, // – Hermes (France)
  { "COST", 914.252 }, // – Costco (US)
  { "ALB", 176.80 } // - Albemarle Corp (US)
};

size_t stockCount = sizeof(myStocks) / sizeof(myStocks[0]);
