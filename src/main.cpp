#include "connect_wifi.h"

char SSID[] = "Nuno Guterres";
char PASS[] = "nuno12345";

uint8_t *macaddr;

IPAddress gateway(172, 20, 10, 14);
IPAddress subnet(255, 255, 255, 240);

void setup() {

  Serial.begin(BAUD);

  if (ConnectWifi(SSID, PASS)) {

    node* a;
  
    if (!strcmp(WiFi.macAddress().c_str(), "A4:CF:12:54:DD:D4")) {
        Serial.println("success!!");
    }

    #ifdef A
      
      IPAddress ipA(172,20,10,1);
      SetAddress(ipA, gateway, subnet);

      a = (node*) malloc(sizeof(node));

      a->monkey = ROOT;

      //strcpy(a->macaddr, WiFi.macAddress().c_str());

      strcpy(a->macaddr, "A4:CF:12:54:DD:D4");

      strcpy(a->ipaddr, "172.20.10.1");

      a->banana[0] = B;
      a->banana[1] = C;

      Serial.println(a->monkey);
      Serial.println(a->banana[0]);
      Serial.println(a->banana[1]);
      Serial.println(a->ipaddr);
      Serial.println(a->macaddr);

      free(a);

    #endif

  } else {
    Serial.println("Network not available!");
  }
  
}

void loop() {


}