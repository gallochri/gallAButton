#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <FS.h>
#include "utils.h"
#include "setupmode.h"

extern String DEVICE_TITLE;

String getContentType(String filename);
bool handleFileRead(String path);

//Web Server root
void handleNotFound();

void handleReboot();

//WiFi form and write down WiFi config
void handleWiFi();

void handleSetWiFi();

// Test SPIFFS file
void testSPIFFS();

#endif // WEBSERVER_H
