#include "connect_wifi.h"
#include <WiFi.h>

#define BAUD 9600
#define NUMBER_NODES 3

char SSID[] = "Nuno Guterres";
char PASS[] = "nuno12345";

uint8_t *macaddr;

IPAddress gateway(172, 20, 10, 14);
IPAddress subnet(255, 255, 255, 240);

void setup() {

  Serial.begin(BAUD);

  if (ConnectWifi(SSID, PASS)) {

    node* a, b, c;

    WiFi.macAddress(); // A4:CF:12:54:DD:D4

    /*if (!strcmp((const char*)macaddr, "A4:CF:12:54:DD:D4")) {
        Serial.println("success!!");
    }*/

    #ifdef A
      
      IPAddress ipA(172,20,10,1);
      SetAddress(ipA, gateway, subnet);
     /* a = (node*) malloc(sizeof(node));

      a->father = ROOT;

      strcpy(a->ipaddr, "172.20.10.1");
      
      a->children[0] = B;
      a->children[1] = C;

      free(a);*/

    #endif

  } else {
    Serial.println("Network not available!");
  }
  
}

void loop() {


}