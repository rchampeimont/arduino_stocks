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

## Schematic
![Schematic](stocks_schem.png)
