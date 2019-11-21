#include <WiFi.h>
#include <Arduino.h>

#define BAUD 9600
#define NEDUROAM 

void setup() {

  Serial.begin(BAUD);

  #ifdef NEDUROAM
    
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
 
}

void loop() {

    Serial.println("Connected to network");
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());

    delay(2000);
}