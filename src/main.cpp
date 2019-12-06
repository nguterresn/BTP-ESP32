#include "connect_wifi.h"
#include "node_selection.h"

/* Serial */
#define BAUD 9600

void setup() {

	Serial.begin(BAUD);

  	if (ConnectWifi(SSID, PASS)) {

		if (NodeSetup()){
        	Serial.println("Node_setup success!");
      	}
      	else Serial.println("Node_setup error!");
    }
    else {
    Serial.println("Network not available!");
  }
  
}

void loop() {

}