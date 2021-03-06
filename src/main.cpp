#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "config.h"
#include "utils.h"
#include "setupmode.h"

void setup() {
    //Set WiFi to station mode
    WiFi.mode(WIFI_STA);
    //Set GPIO4 to HIGH for retain on APixel board useless on others boards
    pinMode(RETPIN, OUTPUT);
    digitalWrite(RETPIN, HIGH);
    //Init Serial port and SPIFFS
    Serial.begin(115200);
    Serial.println();
    SPIFFS.begin();
    //Init RGB LED
    led.begin();
    led.show();
    blinkLed.green(&led, 100, 2);
    //DEBUG!
    //printConfig();
    //debugSPIFFS();

    //Try to load saved config
    if (!loadWiFiSavedConfig()) {
        Serial.println("WARNING: WiFi configuration not found");
        blinkLed.red(&led, 100, 2);
        setupMode();
        return;
    }

    //Check connection
    if (!checkWiFiConnection()) {
        Serial.println("ERROR: Connection lost");
        blinkLed.red(&led, 100, 2);
        setupMode();
        return;
    }

    //TODO
    //Button is connected! try to call to IFTTT
    if (loadJsonParam("ifttt")) {
        for (int i = 0; i < 3; i++) {
            if (ifttt()) {
                blinkLed.green(&led, 100, 2);
                break;
            } else {
                int attempt = i + 1;
                Serial.println("WARNING: IFTTT failed! attempt nr "
                               + String(attempt));
                blinkLed.red(&led, 100, 2);
            }
        }
    }

    //Button is connected! try to call custom URL
    if (loadJsonParam("custom")) {
        for (int i = 0; i < 3; i++) {
            if (customurl()) {
                blinkLed.green(&led, 100, 2);
                break;
            } else {
                int attempt = i + 1;
                Serial.println("WARNING: Custom URL failed! attempt nr "
                               + String(attempt));
                blinkLed.red(&led, 100, 2);
            }
        }
    }

    //Button is connected! try to call MQTT
    if (loadJsonParam("mqtt")) {
        for (int i = 0; i < 3; i++) {
            if (mqtt()) {
                blinkLed.green(&led, 100, 2);
                break;
            } else {
                int attempt = i + 1;
                Serial.println("WARNING: MQTT failed! attempt nr "
                               + String(attempt));
                blinkLed.red(&led, 100, 2);
            }
        }
    }
    if (APixelBoard) {
        //put retain pin to LOW for power off APixel board
        Serial.println("WARNING: APixel Board power off");
        APixelPowerOff(RETPIN);
    } else {
        Serial.println("WARNING: Deep Sleep Mode");
        powerOff();
    }
    //If chip is still on, button is pressed (Apixel board)
    Serial.println("WARNING: Button pressed ");
    setupMode();
}

void loop() {
    if (setupModeStatus) {
        DNS_SERVER.processNextRequest();
        WEB_SERVER.handleClient();
        blinkLed.violet(&led, 0, 10);
        if ((millis() - startTime) > TIMEOUT) {
            Serial.println("Set up mode timed out.");
            Serial.println("WARNING: APixel Board power off");
            delay(1000);
            APixelPowerOff(RETPIN);
        }
    } else {
        Serial.println("ERROR: Something wrong :-( ");
        blinkLed.red(&led, 200, 1);
        blinkLed.blue(&led, 200, 1);
        blinkLed.green(&led, 200, 1);
    }
}
