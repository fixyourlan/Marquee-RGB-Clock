#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

float hum, temp, tempF, pres, pin, dew;
char tempStr[3];
char tempFStr[3];
char dewStr[6];
char humStr[6];
char presStr[7];
char presInchStr[6];

Adafruit_BME280 bme; // I2C
