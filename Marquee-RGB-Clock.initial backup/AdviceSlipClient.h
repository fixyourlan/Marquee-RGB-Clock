
#pragma once
#include <ESP8266WiFi.h>
#include <JsonListener.h>
#include <JsonStreamingParser.h>

class AdviceSlipClient: public JsonListener {

  private:
    
    String currentKey = "";

    typedef struct {
      String adVice;
    } advicefeed;

    advicefeed advice;
    
    const char* servername = "api.adviceslip.com";  // remote server we will connect to
  
  public:
    AdviceSlipClient();
    void updateAdvice();
    
    String getAdvice();
    String cleanText(String text);
    
    virtual void whitespace(char c);
    virtual void startDocument();
    virtual void key(String key);
    virtual void value(String value);
    virtual void endArray();
    virtual void endObject();
    virtual void endDocument();
    virtual void startArray();
    virtual void startObject();

};
