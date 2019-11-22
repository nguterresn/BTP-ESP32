#include "connect_wifi.h"

boolean ConnectWifi() {

    IPAddress ip(172, 20, 10, 1); //28
    IPAddress gateway(172, 20, 10, 14);
    IPAddress subnet(255, 255, 255, 240);
    //WiFiServer server(80);

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
    
    WiFi.config(ip, gateway, subnet);
    Serial.println("Connected to network");
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());

    return true;
}

boolean CheckNetwork(const char *addr) {

    bool success = Ping.ping(addr, 1); // broadcast
 
    if(!success){
        Serial.println("Ping failed");
        return false;
    }
 
    Serial.println("Ping succesful.");
    return true;
}

boolean SetNetwork(IPAddress ip, IPAddress gateway, IPAddress subnet) {

    bool result = WiFi.config(ip, gateway, subnet);

    if (!result)
      return false;
  
    return true;
}