
#pragma once
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

class BitcoinApiClient {

private:

  String myCurrency = "";
  
  const char* servername = "api.coindesk.com";  // remote server we will connect to https://www.coindesk.com/api/

  typedef struct {
    String code;
    String rate;
    String description;
    float  rate_float;
  } bpi;

  bpi bpiData;
  
public:
  BitcoinApiClient();
  void updateBitcoinData(String currencyCode);

  String getCode();
  String getRate();
  String getDescription();
  float getRateFloat();
};

