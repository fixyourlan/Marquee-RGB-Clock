

#pragma once
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

class GeoNamesClient {

private:
  String myLat = "";
  String myLon = "";
  String myUserName = "";
  boolean isDst = true; // Daylight Savings Time

  int hours = 0;
  int minutes = 0;
  String datetime = "";
  
  const char* servername = "api.geonames.org";  // remote server we will connect to

public:
  GeoNamesClient(String UserName, String lat, String lon, boolean useDst);
  void updateClient(String UserName, String lat, String lon, boolean useDst);
  float getTimeOffset();
  String getHours();
  String getMinutes();
  String getYear();
  String getMonth00();
  String getMonth(boolean zeroPad);
  String getMonthName();
  String getDay00();
  String getDay(boolean zeroPad);
};
