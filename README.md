# Arduino Stocks
Stock portfolio monitoring on Arduino Uno R4 Wifi with an LCD display

Parts:
* Arduino Uno R4 Wifi
* LCD display: NHD-0420DZ-FSW-FBW - https://newhavendisplay.com/fr/content/specs/NHD-0420DZ-FSW-FBW.pdf

## Features
* 🌐 Connects to WiFi
* 📡 Queries stock prices from a market API (Alpha Vantage)
* 📊 Tracks personal portfolio with book cost vs. current price
* 📈 Computes absolute gain per stock
* 🔄 Sorts stocks by gain
* 🖥 Displays portfolio stats on:
  * External LCD display
  * Internal UNO R4 LED matrix
* 🧩 Modular architecture across multiple .ino files

Limitation: I assume that you bought for the same amount of each stock,
but if you have a different strategy it should be easy to adapt the code
to take into account weights.

## To make it work for you
You need to create a file called secrets.h in which you set:
```
// The Wifi network name (SSID) to connect to
#define WIFI_NAME "your Wifi name"

// Wifi password
#define WIFI_PASSWORD "your Wifi password"

// To get stock market data
#define ALPHAVANTAGE_API_KEY "your API key"
```

Add your own stocks in my_stocks.ino and the price at which you bought them.

You can also adjust which ETF is used for comparison (as an approximation of S&P 500) which is displayed for comparison,
and you need to provide the price of this ETF so we can compare to its value now. It makes sense to provide
its price roughly at the moment when you bought your stocks.

Note that the list of stocks I provide only contain 3 stocks, it's obviously a bad idea to diversity that little
but I did not provide my actual complete list to avoid disclosing my own portfolio.

## Schematic
![Schematic](stocks_schem.png)
