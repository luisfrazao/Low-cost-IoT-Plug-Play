#ifndef H_WIFI_SETUP
#define H_WIFI_SETUP

#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

#include <WiFiMulti.h>

void wifiSetup (const char* ssid, const char* password);

#endif //H_WIFI_SETUP
