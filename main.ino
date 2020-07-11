#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <EEPROM.h>
#define EEPROM_SIZE 512

#include "ap_setup.h"
#include "wifi_setup.h"
#include "flash_mem_manager.h"
#include "node_conn_handler.h"

const int buttonPin = 0;
int modeOption = 0;
int buttonState;

//WiFi credentials
char wifi_ssid[20];
char wifi_password[20];

/////DUMMY DATA VALUE
int value = 0;

void setup() {
 
  Serial.begin(115200);

  EEPROM.begin(EEPROM_SIZE);

  pinMode(buttonPin,INPUT);

  //Read modeOption from flash
  modeOption = EEPROM.read(0);

  //Read credentials from flash
  read_Data(wifi_ssid, 1);
  read_Data(wifi_password, 21);

  switch(modeOption){
    //Connect to WiFi
    case 1:
      wifiSetup(wifi_ssid, wifi_password);
      break;
    //Connect as AP
    default:
      setAPnWebServer();
      break;
   }
 
}
 
void loop() {

  
  //If connected as AP
  if (modeOption == 0) 
  {
      Serial.println("Currently connected as AP!");
      Serial.print("IP: ");
      Serial.println(WiFi.softAPIP());
      serverHandleClient();
      delay(2000);
    } else //If connected to WiFi
    {
      Serial.println("Currently connected to WiFi!");
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());

      postValue(15);
    }
      
  //Reads BOOT state
  buttonState = digitalRead(buttonPin);

  //If BOOT is LOW it means it was pressed
  //If that happens, change the mode option
  if (buttonState != HIGH) 
  {
    if (modeOption == 0)
    {
      modeOption = 1;
    } else 
    {
      modeOption = 0;
    }
    Serial.println("Action detected! We will now process to apply the changes.");
    EEPROM.write(0, modeOption);
    EEPROM.commit();
    ESP.restart();
  }
}


  
