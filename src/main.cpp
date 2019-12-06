#include "connect_wifi.h"

char SSID[] = "Nuno Guterres";
char PASS[] = "nuno12345";

IPAddress gateway(172, 20, 10, 14);
IPAddress subnet(255, 255, 255, 240);

void setup() {

  Serial.begin(BAUD);
  node_t* n;

  n = (node_t*) malloc(sizeof(node_t));
  n->route = (route_t*) malloc(sizeof(route_t));

  if (ConnectWifi(SSID, PASS)) {
    Serial.println(WiFi.macAddress());
    if (!strcmp(WiFi.macAddress().c_str(), MAC_A)) {
      strcpy(n->macaddr, MAC_A);
      n->ip_id = 1;
    }
    else if (!strcmp(WiFi.macAddress().c_str(), MAC_B)) {
      strcpy(n->macaddr, MAC_B);
      n->ip_id = 2;
    }
    else if (!strcmp(WiFi.macAddress().c_str(), MAC_C)) {
      strcpy(n->macaddr, MAC_C);
      n->ip_id = 3;
    }

    IPAddress ip(172, 20, 10, n->ip_id);
    SetAddress(ip, gateway, subnet);

      

      n->monkey = ROOT;
      strcpy(n->macaddr, "A4:CF:12:54:DD:D4");
      strcpy(n->ipaddr, IP_A);
      n->banana[0] = 1;
      n->banana[1] = 2;

      n->route->A = 0;
      n->route->B = 1;
      n->route->C = 2;
    }

    else if (!strcmp(WiFi.macAddress().c_str(), "3C:71:BF:EA:B6:A8")) {
        Serial.println("success!!");
   
      /*rout* rout_a; 
      node* b; 
      IPAddress ipA(172,20,10,2);
      SetAddress(ipA, gateway, subnet);

      b = (node*) malloc(sizeof(node));
      

      b->monkey = A;

      //strcpy(a->macaddr, WiFi.macAddress().c_str());

      strcpy(b->macaddr, "mac B");

      strcpy(b->ipaddr, "172.20.10.2");

      b->banana[0] = 0;
      b->banana[1] = 0;


*/
    }
    if (!strcmp(WiFi.macAddress().c_str(), "MAC C")) {
        Serial.println("success!!");

       
     /*#ifdef C
      node* c; 
      IPAddress ipA(172,20,10,3);
      SetAddress(ipA, gateway, subnet);

      c = (node*) malloc(sizeof(node));

      c->monkey = A;

      //strcpy(a->macaddr, WiFi.macAddress().c_str());

      strcpy(c->macaddr, "mac C");

      strcpy(c->ipaddr, "172.20.10.3");

      c->banana[0] = 0;
      c->banana[1] = 0;


    #endif*/
    }

   

  } else {
    Serial.println("Network not available!");
  }
  
}

void loop() {


}