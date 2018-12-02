/*
//#include <NtpClientLib.h>
//#include <ESP8266WiFi.h>          
#include <DNSServer.h>            
//#include <ESP8266WebServer.h>     
//#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <Adafruit_NeoPixel.h>


#define NUMPIXELS      60       // number of NeoPixel LEDs
#define PIN            D4        // digital pin on ESP8266 for the NeoPixel data line
#define mirror_hands   true     // true for 4 piece ring / false for 1 piece ring 

int hour_hand, minute_hand, second_hand, previous_second;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
*/


// clear all the leds to off
void clearHands() {
  for (byte i=0; i<=NUMPIXELS;i++) {
    pixels.setPixelColor(i,pixels.Color(0,0,0));
  }
}

void drawHands(){
  clearHands();
  
   pixels.setPixelColor(hour_hand-1,pixels.Color(0,0,100));
   pixels.setPixelColor(hour_hand,pixels.Color(100,0,0));
   pixels.setPixelColor(hour_hand+1,pixels.Color(0,0,100));
   if (hour_hand==12) pixels.setPixelColor(1,pixels.Color(0,0,100));
  // if hour and minute are the same led, use a different color to show that
  if (hour_hand==minute_hand) {
    pixels.setPixelColor(minute_hand,pixels.Color(100,100,0));
  } else {
    pixels.setPixelColor(minute_hand,pixels.Color(0,100,0));
  }

  // draw the second LED, using medium brightness white
//  pixels.setPixelColor(second_hand,pixels.Color(50,50,50));

  // show all the LED's, only the ones we have set with a color will be visible.
  pixels.show();

  // just a debug string, can be removed
//  Serial.printf("hour:%d (%d), minute:%d second:%d (%d) \n",hour(),hour_hand,minute_hand,true_second,second_hand);
}


void doRGBClock() {
  byte hour_offset; 

  drawHands();  
//  minute_hand=minute();
  minute_hand=(timeClient.getMinutes().toInt());
  if (minute_hand>=10) {
    hour_offset=(minute_hand / 10)-1;
  }else
  {
    hour_offset=0;
  }
  
  if (timeClient.getHours().toInt() >= 12) {
    hour_hand = ((timeClient.getHours().toInt() - 12) * 5); // + hour_offset;
  }
  else {
    hour_hand = (timeClient.getHours().toInt() * 5); // + hour_offset;
  }
   
  if (mirror_hands) {
    hour_hand=60-hour_hand;
    minute_hand=60-minute_hand;
    second_hand=(60 - timeClient.getSeconds().toInt());
    if (second_hand==60) {
      second_hand=0;
    }
    if (minute_hand==60) {
      minute_hand=0;
    }
    if (hour_hand==60) {
      hour_hand=0;
    }
  } else {
    second_hand = timeClient.getSeconds().toInt();
  }
  
  if (second_hand!=previous_second) {
    previous_second=second_hand;
    drawHands();
  }
}

