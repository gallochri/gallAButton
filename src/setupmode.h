#ifndef SETUPMODE_H
#define SETUPMODE_H

#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "utils.h"
#include "webserver.h"
#include "ifttt.h"
#include "customurl.h"

extern uint8_t RETPIN;
extern boolean setupModeStatus;
extern IPAddress AP_IP;
extern String AP_SSID;
extern unsigned long startTime;
extern String SSID_LIST;
extern ESP8266WebServer WEB_SERVER;
extern Adafruit_NeoPixel led;
extern ColorBlink blinkLed;



void setupMode();
void testSPIFFS();

#endif // SETUPMODE_H
