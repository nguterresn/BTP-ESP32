#include "connect_wifi.h"

boolean ConnectWifi() {

    //IPAddress ip(192, 168, 0, 177);

    const char* ssid = "Nuno Guterres";
    const char* pass = "nuno1234";

    uint32_t time_conter = 0;

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      time_conter += 1000;
      if (time_conter > 15000) 
        return false;
      Serial.println("Establishing connection to WiFi...");
    }
 
    Serial.println("Connected to network");
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());

    return true;
}