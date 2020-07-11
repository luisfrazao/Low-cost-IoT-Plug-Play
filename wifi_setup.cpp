#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

#include <WiFiMulti.h>

#include "wifi_setup.h"

WiFiMulti wifiMulti;

//Connects device to WiFi
void wifiSetup (const char* ssid, const char* password) {
  
  wifiMulti.addAP(ssid, password);

  int wifiCounterError= 0;

   //While not connected
  while (wifiMulti.run() != WL_CONNECTED) //Check for the connection
  { 
    delay(1000);
    Serial.println("Connecting to WiFi..");
    wifiCounterError++;
    if (wifiCounterError> 10) ESP.restart();
  }

  //Prints IP address
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
}
