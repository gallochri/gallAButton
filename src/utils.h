#ifndef UTILS_H
#define UTILS_H

boolean checkWiFiConnection() {
  int count = 0;
  Serial.print("Waiting to connect to WiFi network");
  while ( count < 10 ) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println();
      Serial.println("Connected!");
      blinkLed.green(&led, 1000, 1);
      return (true);
    }
    delay(500);
    Serial.print(".");
    blinkLed.blue(&led, 200, 1);
    count++;
  }
  Serial.println("Timed out.");
  blinkLed.red(&led, 1000, 1);
  return false;
}

String ssidList(){
	int n = WiFi.scanNetworks();
	String SSID_LIST = "";
	for (int i = 0; i < n; ++i) {
			SSID_LIST += "<option value=\"";
			SSID_LIST += WiFi.SSID(i);
			SSID_LIST += "\">";
			SSID_LIST += WiFi.SSID(i);
			SSID_LIST += "</option>";
		}
	return SSID_LIST;
}
#endif
