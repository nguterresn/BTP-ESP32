#include "node_selection.h"
#include "connect_wifi.h"

IPAddress gateway(172, 20, 10, 14);
IPAddress subnet(255, 255, 255, 240);

boolean NodeSetup() {

    node_t* n;
    n = (node_t*) malloc(sizeof(node_t));
    n->route = (route_t*) malloc(sizeof(route_t));
    
    /* NODE SELECTION */
    if (!strcmp(WiFi.macAddress().c_str(), MAC_A)) {

        strcpy(n->macaddr, MAC_A);
        n->ip_id = 1;

        IPAddress ip(172, 20, 10, n->ip_id);

        /* Sets NODE Address */
        if (!(SetAddress(ip, gateway, subnet)))
            return false;
        
        /* A has no Monkey */
        n->monkey = ROOT;
        
        strcpy(n->macaddr, WiFi.macAddress().c_str());
        Serial.println(n->macaddr);

        /* Children are set as 1 -> B and 2 -> C */
        n->banana[0] = 1;
        n->banana[1] = 2;

        /* COMMUNICATION IS NOT CONFIRMED YET, so route is 0 for others nodes */
        n->route->A = 1;
      	n->route->B = 0;
      	n->route->C = 0;

        Serial.println("MAC_A DEVICE WELL SET!");

        return true;
    }
    else if (!strcmp(WiFi.macAddress().c_str(), MAC_B)) {
        strcpy(n->macaddr, MAC_B);
        n->ip_id = 2;

        IPAddress ip(172, 20, 10, n->ip_id);

        /* Sets NODE Address */
        if (!(SetAddress(ip, gateway, subnet)))
            return false;

        n->monkey = ROOT;

        strcpy(n->macaddr, WiFi.macAddress().c_str());
        Serial.println(n->macaddr);

        /* COMMUNICATION IS NOT CONFIRMED YET, so route is 0 for others nodes */
      	n->route->B = 1;

        Serial.println("MAC_B DEVICE WELL SET!");
        return true;

    }
    else if (!strcmp(WiFi.macAddress().c_str(), MAC_C)) {
        strcpy(n->macaddr, MAC_C);
        n->ip_id = 3;

        IPAddress ip(172, 20, 10, n->ip_id);

        /* Sets NODE Address */
        if (!(SetAddress(ip, gateway, subnet)))
            return false;

        n->monkey = ROOT;

        strcpy(n->macaddr, WiFi.macAddress().c_str());
        Serial.println(n->macaddr);

        /* COMMUNICATION IS NOT CONFIRMED YET, so route is 0 for others nodes */
      	n->route->C = 1;

        Serial.println("MAC_C DEVICE WELL SET!");
        return true;
    }

    return false;

}

boolean CreateSocket (node_t *n) {
    
    /* Create Server */
    if (n->banana[0] > 0) {

        /* Two cases: 
        1. -> Has a father and children: needs to be able to communicate above and below.
        2. -> Has only children (ROOT): needs only to communicate below.
        */

    }
    /* Create Client */
    else { 

        WiFiClient client;
        IPAddress server(172,20,10,n->ip_id);
        /* In a Client Side, the server is the father of the node */
        if (client.connect(server, 80)) {
            Serial.println("connected");
            // Make a HTTP request:
            client.println("GET /search?q=arduino HTTP/1.0");
            client.println();
        }
    }
}    	