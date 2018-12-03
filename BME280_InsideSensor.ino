
 
void checkForBME280(){

 if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    scrollMessage("BME280 sensor not found, check wiring!");
    while (1);
  }
  scrollMessage("BME280 sensor OK!");
} 


void getInsideWeather() {
    temp = 0;
    tempF = 0; 
     
    hum = bme.readHumidity();
    temp = bme.readTemperature();
    tempF = temp*1.8+27.0;  //wss 32 , subtracted 5 for temp adjustment
    dew = tempF-0.36*(100.0-hum);
    
    pres = bme.readPressure()/100.0F;
    pin = 0.02953*pres;
    dtostrf(temp, 3, 0, tempStr);
    dtostrf(tempF, 3, 0, tempFStr);
    dtostrf(hum, 5, 1, humStr);
    dtostrf(pres, 6, 1, presStr);
    dtostrf(pin, 5, 1, presInchStr);
    dtostrf(dew, 3, 0, dewStr);
    delay(100);
 
}
  
