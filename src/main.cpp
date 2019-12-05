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

    
     WiFi.macAddress(macaddr);
     // A4:CF:12:54:DD:D4

    if (!strcmp((const char*) *macaddr, "A4:CF:12:54:DD:D4")) {
        Serial.println("success!!");

    #ifdef A
      node* a;
      IPAddress ipA(172,20,10,1);
      SetAddress(ipA, gateway, subnet);
      a = (node*) malloc(sizeof(node));
      a->father = ROOT;
      strcpy(a->ipaddr, "172.20.10.1");
      a->children[0] = B;
      a->children[1] = C;

      free(a);

    #endif
    } else if(!strcmp((const char*) *macaddr, "")) {
        Serial.println("success!!");

    #ifdef B
      node* b;
      IPAddress ipB(172,20,10,2);
      SetAddress(ipB, gateway, subnet);
      b = (node*) malloc(sizeof(node));
      b->father = A;
      strcpy(b->ipaddr, "172.20.10.2");
      b->children[0] = 0;
      b->children[1] = 0;
      free(b);
    #endif

    } else if(!strcmp((const char*) *macaddr, "")) {
        Serial.println("success!!");

    #ifdef C
      node* c;
      IPAddress ipB(172,20,10,3);
      SetAddress(ipB, gateway, subnet);
      c = (node*) malloc(sizeof(node));
      c->father = A;
      strcpy(c->ipaddr, "172.20.10.3");
      c->children[0] = 0;
      c->children[1] = 0;

      free(c);

    #endif
  } else {
    Serial.println("Network not available!");
  }
  
}
}

void loop() {


}