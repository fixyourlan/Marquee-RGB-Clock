/*
Modified by David Payne for use in the Scrolling Marquee
*/
#pragma once
#include <ESP8266WiFi.h>

#define NTP_PACKET_SIZE 48

class TimeClient {

  private:
    float myUtcOffset = 0;
    long localEpoc = 0;
    long localMillisAtUpdate;
    const char* ntpServerName = "www.google.com";
    const int httpPort = 80;    
    byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

  public:
    TimeClient(float utcOffset);
    void updateTime();
    
    void setUtcOffset(float utcOffset);
    String getHours();
    String getAmPmHours();
    String getAmPm();
    String getMinutes();
    String getSeconds();
    String getFormattedTime();
    String getAmPmFormattedTime();
    long getCurrentEpoch();
    long getCurrentEpochWithUtcOffset();

};

