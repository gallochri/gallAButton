#include "ifttt.h"

boolean ifttt() {
    Serial.println("IFTT Button fired");

    const char* IFTTT_URL= "maker.ifttt.com";
    String KEY = ABconfigs.getparam(IFTTT_KEY);
    String EVENT = ABconfigs.getparam(IFTTT_EVENT);

    // Define the WiFi Client
    WiFiClient client;

    // Make sure we can connect
    if (!client.connect(IFTTT_URL, 80)) {
        Serial.println("ERROR: Can't connect to IFTTT!");
        return false;
    }
    
    // We now create a URI for the request
    String url = "/trigger/" + EVENT + "/with/key/" + KEY;

    // Build JSON data string
    String value_1 = WiFi.macAddress();
    String value_2 = WiFi.SSID();
    String value_3 = String(vcc());
    String data;
    data = data + "\n" + "{\"value1\":\"" + value_1 + "\",\"value2\":\"" + value_2 + "\",\"value3\":\"" + value_3 + "\"}";

    blinkLed.blue(&led, 100, 1);

    Serial.println("=== IFTT ===");

    String strPayload;
    strPayload += "POST " + url + " HTTP/1.1\r\n";
    strPayload += "Host: " + String(IFTTT_URL) + "\r\n";
    strPayload += "User-Agent: Arduino/1.0\r\n";
    strPayload += "Connection: close\r\n";
    strPayload += "Accept: */*\r\n";
    strPayload += "Content-Type: application/json\r\n";
    strPayload += "Content-Length: " + String(data.length()) + "\r\n\r\n";
    strPayload += data + "\r\n\r\n";

    client.println(strPayload);
    Serial.println(strPayload);

    // Wait for a response
    while (client.connected()) {
        if (client.available()){
            char response = client.read();
            Serial.print(response);
        }
    }

    blinkLed.blue(&led, 100, 1);

    Serial.println("IFTTT request sent. Goodbye");
    return true;
}

void handleIFTTT(){
    String s = "<h2>IFTTT Settings</h2>\n";
    s += "<form method='get' action='setifttt'>\n";
    s += "<label>IFTTT Key: </label><input value='" + ABconfigs.getparam(IFTTT_KEY) + "' name='KEY' maxlenght='32'><br>\n";
    s += "<br><label>IFTTT Event: </label><input value='" + ABconfigs.getparam(IFTTT_EVENT) + "' name='EVENT' maxlenght='32'><br>\n";
    s += "<br><br><input type='submit' value='Submit'>\n</form>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"IFTTT Settings", s));
}

void handleSetIFTTT(){

    wipeConfig(96,160);

    String KEY = urlDecode(WEB_SERVER.arg("KEY"));
    Serial.print("IFTTT Key: ");
    Serial.println(KEY);

    String EVENT = urlDecode(WEB_SERVER.arg("EVENT"));
    Serial.print("IFTTT Event: ");
    Serial.println(EVENT);

    Serial.println("Writing IFTTT Key to EEPROM...");
    for (int i = 0; i < KEY.length(); ++i) {
        EEPROM.write(96 + i, KEY[i]);
    }
    Serial.println("Writing IFTTT Event to EEPROM...");
    for (int i = 0; i < EVENT.length(); ++i) {
        EEPROM.write(128 + i, EVENT[i]);
    }
    EEPROM.commit();
    Serial.println("IFTTT settings write to EEPROM done!");
    String s = "<h1>IFTTT Setup complete.</h1>\n";
    s += "<p>At restart airbutton will try to send data to <br>\n";
    s += "IFTTT event: ";
    s += EVENT;
    s += " with key: ";
    s += KEY;
    s += " .\n";
    s +="\n<a href='/'>Back</a></p>\n";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"Write IFTTT Settings", s));
}
