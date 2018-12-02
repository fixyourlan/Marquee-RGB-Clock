
/******************************************************************************
 * This is designed for the Wemos D1 ESP8266
 * Wemos D1 Mini:  https://amzn.to/2qLyKJd
 * MAX7219 Dot Matrix Module 4-in-1 Display For Arduino
 * Matrix Display:  https://amzn.to/2HtnQlD
 ******************************************************************************/
/******************************************************************************
 * NOTE: The settings here are the default settings for the first loading.  
 * After loading you will manage changes to the settings via the Web Interface.  
 * If you want to change settings again in the settings.h, you will need to 
 * erase the file system on the Wemos or use the “Reset Settings” option in 
 * the Web Interface.
 ******************************************************************************/
 
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include "FS.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include "OpenWeatherMapClient.h"
#include "GeoNamesClient.h"
#include "TimeClient.h" // Using updated lib by Qrome
#include "NewsApiClient.h" 
#include "OctoPrintClient.h"
#include "AdviceSlipClient.h"
#include "BitcoinApiClient.h"
#include "BME280_InsideSensor.h"  //setup Inside Temp Sensor
#include "Round_RGB_Clock.h"      //setup RGB Ring
//#include "max7219_Bitmaps.h"      //setup the Scrolling Display


//******************************
// Start Settings
//******************************

String APIKEY = "1e825293849a4070b9091dfd4d78f7e3"; // Your API Key from http://openweathermap.org/
// Default City Location (use http://openweathermap.org/find to find city ID)
int CityIDs[] = { 4726206 }; //Only USE ONE for weather marquee
String marqueeMessage = "";
boolean IS_METRIC = false; // false = Imperial and true = Metric
boolean IS_24HOUR = false; // 23:00 millitary 24 hour clock
boolean IS_DST = true; // Does your TimeZone use Daylight Savings Time (DST)?
const int WEBSERVER_PORT = 80; // The port you can access this device on over HTTP
const boolean WEBSERVER_ENABLED = true;  // Device will provide a web interface via http://[ip]:[port]/
boolean IS_BASIC_AUTH = true;  // Use Basic Authorization for Configuration security on Web Interface
char* www_username = "Jim";  // User account for the Web Interface
char* www_password = "nikond1x";  // Password for the Web Interface
int minutesBetweenDataRefresh = 10;  // Time in minutes between data refresh (default 15 minutes)
int minutesBetweenScrolling = 1; // Time in minutes between scrolling data (default 1 minutes and max is 10)
int displayScrollSpeed = 25; // In milliseconds -- Configurable by the web UI (slow = 35, normal = 25, fast = 15)

boolean NEWS_ENABLED = true;
String NEWS_API_KEY = "addefaa7a7524a7c904a423548a1751e"; // Get your News API Key from https://newsapi.org
String NEWS_SOURCE = "reuters";  // https://newsapi.org/sources to get full list of news sources available

boolean ADVICE_ENABLED = false;

// Display Settings
// CLK -> D5 (SCK)  
// CS  -> D6 
// DIN -> D7 (MOSI)

const int pinCS = D6; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int displayIntensity = 1;  //(This can be set from 0 - 15)
const int numberOfHorizontalDisplays = 4; // default 4 for standard 4 x 1 display Max size of 16
const int numberOfVerticalDisplays = 1; // default 1 for a single row height

String timeDisplayTurnsOn = "";  // 24 Hour Format HH:MM -- Leave blank for always on. (ie 05:30)
String timeDisplayTurnsOff = ""; // 24 Hour Format HH:MM -- Leave blank for always on. Both must be set to work.

const String GEONAMES_USER = "fixyourlan"; // user account for  http://www.geonames.org/ -- this service is used to lookup TimeZone Offsets

// OctoPrint Monitoring -- Monitor your 3D printer OctoPrint Server
boolean OCTOPRINT_ENABLED = true;
String OctoPrintApiKey = "12A389A4DC914F35B00571DD664C9892";  // ApiKey from your User Account on OctoPrint
String OctoPrintServer = "192.168.1.31"; // IP or Address of your OctoPrint Server (DO NOT include http://)
int OctoPrintPort = 80; // the port you are running your OctoPrint server on (usually 80);
String OctoAuthUser = "Jim";      // only used if you have haproxy or basic athentintication turned on (not default)
String OctoAuthPass = "nikond1x";      // only used with haproxy or basic auth (only needed if you must authenticate)

// Bitcoin Client - NONE or empty is off
String BitcoinCurrencyCode = "NONE";  // Change to USD, GBD, EUR, or NONE -- this can be managed in the Web Interface

boolean ENABLE_OTA = true;  // this will allow you to load firmware to the device over WiFi (see OTA for ESP8266)
String OTA_Password = "";      // Set an OTA password here -- leave blank if you don't want to be prompted for password

//******************************
// End Settings
//******************************
