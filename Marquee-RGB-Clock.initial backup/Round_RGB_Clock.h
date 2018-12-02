#include <Adafruit_NeoPixel.h>

#define NUMPIXELS      60       // number of NeoPixel LEDs
#define PIN            D4        // digital pin on ESP8266 for the NeoPixel data line
#define mirror_hands   true     // true for 4 piece rings / false for 1 piece rings 

int hour_hand, minute_hand, second_hand, previous_second;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

