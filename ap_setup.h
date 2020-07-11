#ifndef H_AP_SETUP
#define H_AP_SETUP

#include <ESPmDNS.h>
#include <WebServer.h>

void serverHandleClient();
void handleRoot();
void handleNotFound();
void handleSave();
void setAPnWebServer ();

#endif //H_AP_SETUP
