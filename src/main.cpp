#include <FreeRTOS.h>
#include <WiFiUdp.h>
#include <freertos/task.h>
#include <freertos/StackMacros.h>
#include <btp.h>

#define BAUD 9600

Node n;

void read_task(void* pvParameters) {
    while(1)
        n.readPacket();
}

void send_task(void* pvParameters) {
    int inst = 0;
    Serial.println("Send anything:");
    while(1) {
        if(Serial.available()){
            Serial.read();
            n.sendPacket(inst);
            inst++;
            if(inst == 10)
                inst = 0;
        }    
        delay(1000);
    }
}

void setup() {
	Serial.begin(BAUD);
    Serial.println("\n***************************************");
    Serial.println("Routine start.");
  	
    uint8_t count = 0;
    while(!n.connectWifi()) {
        if(count < 14)
            Serial.println("Connecting to WiFi...");
        else if(count == 14) {
            Serial.println("Cannot connect to WiFi. Restarting in: ");
            Serial.println((24 - count));
        } else if(count > 14) {
            if(count == 24) 
                ESP.restart();
            Serial.println((24 - count)); 
        }       
        count++;
        delay(1000);
    }

    Serial.print("Connected to WiFi network ");
    Serial.println(n.getSSID());

    if(n.setIP())
        Serial.println("=> IP well set.");
    else
        Serial.println("=> IP not well set.");

    if(n.setTree())
        Serial.println("=> Tree well set.");
    else
        Serial.println("=> Tree not well set.\n\n");

    n.startUDP();
    
    Serial.println("+--------------------------------------+");

    Serial.println("|   Node info:");
    Serial.println("+--------------------------------------+");
    Serial.print("|   Node id: ");
    Serial.println(n.getNames((node)n.getID()));
    Serial.println("+--------------------------------------+");
    Serial.print("|   Monkey: ");
    Serial.println(n.getNames(n.getMonkey()));
    Serial.println("+--------------------------------------+");
    Serial.print("|   Bananas: ");
    for(int i = 0; i < n.getBananas().size(); i++) {
        Serial.print(n.getNames(n.getBananas()[i]) + ", ");
    }
    Serial.println("\n+--------------------------------------+");
    Serial.print("|   IP address: ");
    Serial.println(n.getIP());
    Serial.println("+--------------------------------------+\n\n");
    Serial.println("To send a message first give destination then enter, second give the task then enter");

    xTaskCreate(read_task, "Read UDP packets", 10000, NULL, 1, NULL);
    xTaskCreate(send_task, "Send UDP packets", 10000, NULL, 1, NULL);
    //vTaskStartScheduler();
}


void loop() {
    delay(10000);
}
