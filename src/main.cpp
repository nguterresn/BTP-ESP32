#include <WiFi.h>
#include <Arduino.h>

#define BAUD 9600
#define WIFI_CONNECT 

void setup() {

  Serial.begin(BAUD);

  #ifdef WIFI_CONNECT
    
    const char* ssid = "Nuno Guterres";
    const char* pass = "nuno1234";

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Establishing connection to WiFi..");
    }
 
    Serial.println("Connected to network");
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());

  #endif
  #ifndef WIFI_CONNECT
    Serial.println("Please enable Wifi Connection!");
  #endif

 
}

void loop() {

    Serial.println("Connected to network");
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());

    delay(2000);
}