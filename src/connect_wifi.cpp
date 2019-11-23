#include "connect_wifi.h"

boolean ConnectWifi(const char* ssid, const char* pass) {

    uint32_t time_conter = 0;

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);

      time_conter += 1000;
      if (time_conter > 15000) 
        return false;

      Serial.println("Establishing connection to WiFi...");
    }
    
    Serial.print("Connected to network: ");
    Serial.print(WiFi.localIP());
    Serial.print(" | ");
    Serial.println(WiFi.macAddress());

    return true;
}

boolean CheckNetwork(const char *addr) {

    bool success = Ping.ping(addr, 1); 
 
    if(!success){
        Serial.println("Ping failed. There is no nodes in the network, should establish as root!");
        return false;
    }
 
    Serial.println("Ping succesful. There is nodes in the network!");
    return true;
}

boolean SetNetwork(IPAddress ip, IPAddress gateway, IPAddress subnet) {

    bool result = WiFi.config(ip, gateway, subnet);

    if (!result) {
      Serial.println("Node was not set correctly.");
      return false;
    }

    Serial.print("Node is well set: ");
    Serial.println(WiFi.localIP());
    return true;
}

boolean Node_Election(IPAddress gateway, IPAddress subnet, const char* broadcast) {

  /* There is nodes in network */
  if (CheckNetwork(broadcast)) {

    //ping_resp pingr;
    //uint32_t info = pingr.total_bytes;
    //Serial.println("%%%%%%%%%%%%%% %%%%%%%%%%%%%%%");
    //Serial.println(info);
    //IPAddress ip(172, 20, 10, 2);
    //SetNetwork(ip, gateway, subnet);

  }

  /* There is no nodes in the network, therefore this one is the master.  */
  else {

    /* Master IP .1 */
    IPAddress ip(172, 20, 10, 1);
    SetNetwork(ip, gateway, subnet);
    return false;

  }

}