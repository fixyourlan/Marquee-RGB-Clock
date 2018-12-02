
#include "AdviceSlipClient.h"

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

AdviceSlipClient::AdviceSlipClient() {

}

void AdviceSlipClient::updateAdvice() {
  JsonStreamingParser parser;
  parser.setListener(this);
  WiFiClient adviceClient;

  String apiGetData = "GET /advice HTTP/1.1";

  Serial.println("Getting Advice Data");
  Serial.println(apiGetData);

  if (adviceClient.connect(servername, 80)) {  //starts client connection, checks for connection
    adviceClient.println(apiGetData);
    adviceClient.println("Host: " + String(servername));
    adviceClient.println("User-Agent: ArduinoWiFi/1.1");
    adviceClient.println("Connection: close");
    adviceClient.println();
  } 
  else {
    Serial.println("connection for advice data failed: " + String(servername)); //error message if no client connect
    Serial.println();
    return;
  }
  
  while(adviceClient.connected() && !adviceClient.available()) delay(1); //waits for data
 
  Serial.println("Waiting for data");

  int size = 0;
  char c;
  boolean isBody = false;
  while (adviceClient.connected() || adviceClient.available()) { //connected or data available
    c = adviceClient.read(); //gets byte from ethernet buffer
    if (c == '{' || c == '[') {
      isBody = true;
    }
    if (isBody) {
      parser.parse(c);
    }
  }
  adviceClient.stop(); //stop client
}

String AdviceSlipClient::getAdvice() {
  return advice.adVice;
}

void AdviceSlipClient::whitespace(char c) {

}

void AdviceSlipClient::startDocument() {
  
}

void AdviceSlipClient::key(String key) {
  currentKey = key;
}

void AdviceSlipClient::value(String value) {
  if (currentKey == "advice") {
    advice.adVice = cleanText(value);
  }
  Serial.println(currentKey + "=" + value);
}

void AdviceSlipClient::endArray() {
}

void AdviceSlipClient::endObject() {
}
void AdviceSlipClient::startArray() {
}

void AdviceSlipClient::startObject() {
}

void AdviceSlipClient::endDocument() {
}

String AdviceSlipClient::cleanText(String text) {
  text.replace("’", "'");
  text.replace("“", "\"");
  text.replace("”", "\"");
  text.replace("`", "'");
  text.replace("‘", "'");
  text.replace("\\\"", "'");
  text.replace("•", "-");
  return text;
}
