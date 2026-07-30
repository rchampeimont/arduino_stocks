#include "global_vars.h"

// Index for comparison with portfolio (weight is ignored here)
struct stock compIndex = { 1.0, "IVV", 695.32 }; // S&P 500 ETF

struct stock myStocks[] = {
  { 1.3, "RMS.PAR", 2150.0 }, // – Hermes (France)
  { 0.4, "COST", 914.252 }, // – Costco (US)
  { 1.3, "STMPA.PAR", 24.60182 } // – STMicroelectronics (France/Italy)
};

size_t stockCount = sizeof(myStocks) / sizeof(myStocks[0]);
