#include <Arduino.h>
#include <EEPROM.h>

#include "flash_mem_manager.h";

//Used to write the WiFi credentials 
void writeData(char addSSID, String SSID, char addPWD, String PWD, int wifiMode)
{
  int ssid_size = SSID.length();
  int pwd_size = PWD.length();
  int i;

  //For each bit of memore, writes one character
  for(i=0;i<ssid_size;i++)
  {
    EEPROM.write(addSSID+i,SSID[i]);
  }
  EEPROM.write(addSSID+ssid_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
  
  for(i=0;i<pwd_size;i++)
  {
    EEPROM.write(addPWD+i,PWD[i]);
  }
  EEPROM.write(addPWD+pwd_size,'\0');   //Add termination null character for String Data

  //Changes mode to WiFi
  EEPROM.write(0, wifiMode);
  
  EEPROM.commit();

  delay(5000);

  //Restarts device
  Serial.println("Restarting");
  ESP.restart();
}

//Used to read the WiFi credentials 
void read_Data(char* array, char add)
{
  int i;
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  
  //Read each bit of memory and saves it in the array sent by parameter
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    array[len]=k;
    len++;
  }
}
