#include "node_selection.h"
#include "connect_wifi.h"


/*boolean CreateSocket (node_t *n) {
    
    // Create Server 
    if (n->banana[0] > 0) {

        Two cases: 
        1. -> Has a father and children: needs to be able to communicate above and below.
        2. -> Has only children (ROOT): needs only to communicate below.
        *

    }
    //Create Client 
    else { 

        WiFiClient client;
        IPAddress server(172,20,10,n->ip_id);
        // In a Client Side, the server is the father of the node 
        if (client.connect(server, 80)) {
            Serial.println("connected");
            // Make a HTTP request:
            client.println("GET /search?q=arduino HTTP/1.0");
            client.println();
        }
    }
}   */ 
 
