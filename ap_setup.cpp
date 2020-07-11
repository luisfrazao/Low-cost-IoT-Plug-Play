#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "ap_setup.h"
#include "wifi_setup.h"
#include "flash_mem_manager.h";
#include "node_conn_handler.h";

extern WebServer server(80);

//AP credentials
const char* ap_ssid     = "ESP32-Access-Point";
const char* ap_password = "123456789";

char htmlResponse[3000];

//Handler to show this HTML page
void handleRoot() {

  snprintf ( htmlResponse, 3000,
  "<!DOCTYPE html><html>\
  <head><meta name='viewport' content='width=device-width, initial-scale=1'>\
  <link rel='icon' href='data:,'>\
  <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\
  .button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;\
  text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style>\
  <title>ESP Input Form</title><meta charset='utf-8' name='viewport' content='width=device-width, initial-scale=1'></head>\
  <body><h1>Device Register</h1>\
  <h2>In this form, we are asking for data so we can register your device for you</h2>\
  <form action='/get'>\
  <p>Please enter your network credentials</p><br>\
  SSID: <input type='text' name='input_ssid'><br>\
  Password: <input type='text' name='input_password'><br><br>\
  <p>Please describe the device you're registering</p><br>\
  Type: <input type='text' name='input_type'><br>\
  Location: <input type='text' name='input_location'><br><br>\
  <p>We're almost done! Please enter the email of your account on our platform</p><br>\
  Email: <input type='text' name='input_email'><br><br><br>\
  <input class='button' type='submit' value='Submit'>\
  </form>\
  </body></html>");
  
  server.send(200, "text/html", htmlResponse);
}

//Handler if not found
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/html", message);
}

//Handler to save data from input
void handleSave() {

    //Saves inputs on constants
    String ssid = server.arg("input_ssid");
    String password = server.arg("input_password");
    String type = server.arg("input_type");
    String location = server.arg("input_location");
    String email = server.arg("input_email");

    //If none are empty, sends back success message
    if (ssid!= "" && password!= "" && type != "" && location != "" && email != ""){
      server.send(200, "text/html", "<div style=text-align:center;> <h3> Credenciais inseridas: </h3>" 
                                         + ssid + " " + password +
                                         "<br><a href=\"/\">Inserir novas credenciais</a>");

      const char* wifi_ssid = ssid.c_str();
      const char* wifi_password = password.c_str();
      wifiSetup(wifi_ssid, wifi_password);
      
      Serial.println("Registering device!");
      Serial.print("Type: ");
      Serial.println(type);
      Serial.print("Location: ");
      Serial.println(location);
      Serial.print("Email: ");
      Serial.println(email);
      //Send POST request
      registerDevice(type, location, email);

      Serial.println("Writing Data!");
      Serial.print("SSID: ");
      Serial.println(ssid);
      Serial.print("Password: ");
      Serial.println(password);
      //Changes mode option and saves data on flash memory
      writeData(1, ssid, 21, password, 1);
  } else {
    //If some inputs are empty, sends back error message
    server.send(200, "text/html", "<div style=text-align:center;> <h3> Server Error. Please click below and try again.</h3> <br><a href=\"/\">Try again</a>");
  }
}

//Connects as AP
void setAPnWebServer () {

      // Connect to Wi-Fi network with SSID and password
      Serial.print("Setting AP (Access Point)…");
      WiFi.mode(WIFI_AP);
      WiFi.softAP(ap_ssid, ap_password);
      IPAddress Ip(192, 168, 4, 1);
      IPAddress NMask(255, 255, 255, 0);
      WiFi.softAPConfig(Ip, Ip, NMask);
      IPAddress IP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(IP);

      Serial.println("");

      if (MDNS.begin("esp32")) {
        Serial.println("MDNS responder started");
      }

      server.on("/", handleRoot);

      server.on("/get", handleSave);

      server.onNotFound(handleNotFound);

      server.begin();
      Serial.println("HTTP server started"); 
  
}

//Client handler
void serverHandleClient() {
  server.handleClient();
}



































/*#include "ap_setup.h"
#include "flash_mem_manager.h";

//Credenciais para o AP
const char* ap_ssid     = "ESP32-Access-Point";
const char* ap_password = "123456789";

        String inputMessageSSID = "";
        String inputParamSSID = "";
        String inputMessagePWD = "";
        String inputParamPWD = "";

// Set web server port number to 80
AsyncWebServer server(80);

// HTML web page to handle 3 input fields (input1, input2, input3)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head>
  <title>ESP Input Form</title>
  <meta charset="utf-8" name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <div style="text-align:center;">
    <h1>ESP Plug&Play Platform</h1>
    <p>Please enter your network credentials</p>
    <form action="/get">
      SSID: <input type="text" name="input_ssid">
      <br>
      Password: <input type="text" name="input_password">
      <br>
      <input type="submit" value="Submit">
      <br>
    </form>
  </div>
</body></html>)rawliteral";

//Credenciais input
const char* SSID_INPUT = "input_ssid";
const char* PASSWORD_INPUT = "input_password";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setAPnWebServer () {

      // Connect to Wi-Fi network with SSID and password
      Serial.print("Setting AP (Access Point)…");
      WiFi.mode(WIFI_AP);
      WiFi.softAP(ap_ssid, ap_password);
      IPAddress Ip(192, 168, 1, 1);
      IPAddress NMask(255, 255, 255, 0);
      WiFi.softAPConfig(Ip, Ip, NMask);
      IPAddress IP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(IP);

      // Send web page with input fields to client
      server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html);
      });
    
      // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
      server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    
        // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
        if (request->hasParam(SSID_INPUT) && request->hasParam(PASSWORD_INPUT)) {
          inputMessageSSID = request->getParam(SSID_INPUT)->value();
          inputParamSSID = SSID_INPUT;
          inputMessagePWD = request->getParam(PASSWORD_INPUT)->value();
          inputParamPWD = PASSWORD_INPUT;
        }
        else {
          Serial.println("Both credentials are needed");
        }
       
        request->send(200, "text/html", "<div style=text-align:center;> <h3> Credenciais inseridas: </h3>" 
                                         + inputMessageSSID + " " + inputMessagePWD +
                                         "<br><a href=\"/\">Inserir novas credenciais</a>");
        
      });

        delay(5000);
  
        Serial.println("Writing Data!");
        Serial.print("SSID: ");
        Serial.println(inputMessageSSID);
        Serial.print("Password: ");
        Serial.println(inputMessagePWD);
        writeData(1, inputMessageSSID, 21, inputMessagePWD, 1);
      
      server.onNotFound(notFound);
      
      server.begin();
  
}*/
