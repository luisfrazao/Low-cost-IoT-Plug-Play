#include <HTTPClient.h>

#include "node_conn_handler.h"

//Registers device
void registerDevice(String type, String location, String email)
{
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");

    //Endpoint to send POST request
    String endpoint = String("https://192.168.1.83:4005/api/devices/new");

    //Building the full path with variables
    String macAddress = String(WiFi.macAddress());
    String path = String();
    path = endpoint + "/" + macAddress + "/" + type + "/" + location + "/" + email;

    Serial.print("Path: ");
    Serial.println(path);

    http.begin(path);

    Serial.print("[HTTP] POST...\n");

  //Sends POST request
    int httpCode = http.POST("");

    // httpCode will be negative on error
    if (httpCode > 0)
    {
        // HTTP header has been send and Server response header has been handled
        Serial.print("[HTTP] POST... code: ");
        Serial.println(httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK)
        {
            String response = http.getString();
            Serial.println(response);
        }
    }
    else
    {
        //Sends back error message
        Serial.print("[HTTP] POST... failed, error: ");
        Serial.println(http.errorToString(httpCode).c_str());
    }

    http.end();

    delay(5000);
}

//Posts value
void postValue(int value)
{
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");

    //Endpoint to send POST request
    String endpoint = String("https://192.168.1.83:4005/api/devices");

   // Building the path with the variables
    String macAddress = String(WiFi.macAddress());
    String path = String();
    path = endpoint + "/" + macAddress + "/" + value;

    Serial.print("Path: ");
    Serial.println(path);

    http.begin(path);

    Serial.print("[HTTP] POST...\n");

    //Sends POST request
    int httpCode = http.POST("");

    // httpCode will be negative on error
    if (httpCode > 0)
    {
        // HTTP header has been send and Server response header has been handled
        Serial.print("[HTTP] POST... code: ");
        Serial.println(httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK)
        {
            String response = http.getString();
            Serial.println(response);
        }
    }
    else
    {
      //Sends back error message
        Serial.print("[HTTP] POST... failed, error: ");
        Serial.println(http.errorToString(httpCode).c_str());
    }

    http.end();

    delay(5000);
}
