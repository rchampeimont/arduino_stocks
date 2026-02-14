struct stock {
  const char* symbol;
  double bookCost;
  double currentPrice;
};

struct stock myStocks[] = {
  { "RMS.PAR", 2150 }, // – Hermes (France)
  { "ALB", 176.80 } // - Albemarle Corp (US)
};

size_t stockCount = sizeof(myStocks) / sizeof(myStocks[0]);