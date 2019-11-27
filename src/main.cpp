#include "connect_wifi.h"

#define BAUD 9600

char SSID[] = "Nuno Guterres";
char PASS[] = "nuno12345";
char broadcastIP[] = "172.20.10.15";

IPAddress gateway(172, 20, 10, 14);
IPAddress subnet(255, 255, 255, 240);

void setup() {

  Serial.begin(BAUD);

  if (ConnectWifi(SSID, PASS)) {

    if (!(CheckNetwork(broadcastIP))) {
        IPAddress ip(172, 20, 10, 1);
        SetNetwork(ip, gateway, subnet);
    }

  } else {
    Serial.println("Network not available!");
  }
  
}

void loop() {

  Serial.println("On the loop..");
  Serial.print("Ping to broadcast: ");
  CheckNetwork("172.20.10.15");
  //Serial.println("Ping to 10.1:");
  ////CheckNetwork("172.20.10.1");

  delay(2000);


}