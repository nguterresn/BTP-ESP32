#include "connect_wifi.h"

#define MASTER
//#define CHILD1
//#define CHILD2
#define BAUD 9600
#define WIFI_CONNECT 

void setup() {

  Serial.begin(BAUD);

  #ifdef WIFI_CONNECT
    ConnectWifi();
    #ifdef MASTER
      IPAddress ip(172, 20, 10, 1); //28
      IPAddress gateway(172, 20, 10, 14);
      IPAddress subnet(255, 255, 255, 240);
      SetNetwork(ip, gateway, subnet);
    #endif
    #ifdef CHILD1
      IPAddress ip(172, 20, 10, 2); //28
      IPAddress gateway(172, 20, 10, 14);
      IPAddress subnet(255, 255, 255, 240);
      SetNetwork(ip, gateway, subnet);
    #endif
    #ifdef CHILD2
      IPAddress ip(172, 20, 10, 3); //28
      IPAddress gateway(172, 20, 10, 14);
      IPAddress subnet(255, 255, 255, 240);
      SetNetwork(ip, gateway, subnet);
    #endif
  #endif
  #ifndef WIFI_CONNECT
    Serial.println("Please enable Wifi Connection!");
  #endif
}

void loop() {

    Serial.println("Connected to network");
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());
    Serial.println("Ping to broadcast:");
    CheckNetwork("172.20.10.15");
    //Serial.println("Ping to 10.1:");
    //CheckNetwork("172.20.10.1");

    delay(2000);
}