#include "connect_wifi.h"

char SSID[] = "Nuno Guterres";
char PASS[] = "nuno12345";



IPAddress gateway(172, 20, 10, 14);
IPAddress subnet(255, 255, 255, 240);

void setup() {

  Serial.begin(BAUD);

  if (ConnectWifi(SSID, PASS)) {

    
    Serial.println(WiFi.macAddress());
    if (!strcmp(WiFi.macAddress().c_str(), "A4:CF:12:54:DD:D4")) {
        Serial.println("success!!");
     node* a;  
     rout* rout_a;  
     #ifdef A
      
      IPAddress ipA(172,20,10,1);
      SetAddress(ipA, gateway, subnet);

      a = (node*) malloc(sizeof(node));
      rout_a = (rout*) malloc(sizeof(rout));

      a->monkey = ROOT;
      strcpy(a->macaddr, "A4:CF:12:54:DD:D4");
      strcpy(a->ipaddr, "172.20.10.1");
      a->banana[0] = B;
      a->banana[1] = C;

      rout_a->route_A = A;
      rout_a->route_B = B;
      rout_a->route_C = C;


    #endif
    }

    else if (!strcmp(WiFi.macAddress().c_str(), "3C:71:BF:EA:B6:A8")) {
        Serial.println("success!!");
    
     #ifdef B
      //rout* rout_a; 
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


    #endif
    }
    if (!strcmp(WiFi.macAddress().c_str(), "MAC C")) {
        Serial.println("success!!");

     node* c;   
     #ifdef C
      
      IPAddress ipA(172,20,10,3);
      SetAddress(ipA, gateway, subnet);

      c = (node*) malloc(sizeof(node));

      c->monkey = A;

      //strcpy(a->macaddr, WiFi.macAddress().c_str());

      strcpy(c->macaddr, "mac C");

      strcpy(c->ipaddr, "172.20.10.3");

      c->banana[0] = 0;
      c->banana[1] = 0;


    #endif
    }

   

  } else {
    Serial.println("Network not available!");
  }
  
}

void loop() {


}