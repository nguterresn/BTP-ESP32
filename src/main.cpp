#include <FreeRTOS.h>
#include <WiFiUdp.h>
#include <freertos/task.h>
#include <freertos/StackMacros.h>
#include <btp.h>

#define BAUD 9600

Node n;

instruc instruction;
node destination;

void send_task(void* pvParameters) {
    char data[5];

    strcpy(data, (char*)pvParameters);

    n.sendPacket((uint8_t*)data);

    vTaskDelete(NULL);
}

void read_task(void* pvParameters) {
    ret_t ret;
    TickType_t xLastWakeTime;
    TickType_t freq_ticks = 50;  // Periodic task of 50ms
    xLastWakeTime = xTaskGetTickCount();
    uint8_t data[5];
    while(1){
        ret = n.readPacket(data);
        if(ret != EMPTY) {
            Serial.println("Received packet.");
            Serial.print("From ");
            Serial.println(n.getNames((node)(data[FROM] - 48)));
            Serial.print("To ");
            Serial.println(n.getNames((node)(data[TO] - 48)));
            Serial.print("Instruction:  ");
            Serial.println(n.getInstruction((instruc)(data[MESSAGE]- 48)));

            if(ret == KEEP) {
                Serial.println("Process message.");
            } else if(ret == FOWARD) {
                Serial.println("Foward message");
                xTaskCreate(send_task, "Send UDP packets", 10000, (void*)data, configMAX_PRIORITIES - 1, NULL);
            } else if(ret == IGNORE) {
                Serial.println("Ignore message");
            }
        }
        vTaskDelayUntil(&xLastWakeTime, freq_ticks);
    }
}

void check_serial(void* pvParameters) {
    TaskHandle_t t = ((TaskHandle_t*)pvParameters)[0];

    TickType_t xLastWakeTime;
    TickType_t freq_ticks = 100;  // Periodic task of 100ms
    xLastWakeTime = xTaskGetTickCount();

    while(1) {
        Serial.println("Checking serial port.");
        if(Serial.available() > 0) {
            vTaskResume(t);
            vTaskDelete(NULL);
        }
        vTaskDelayUntil(&xLastWakeTime, freq_ticks);
    }
}


void control_task(void *pvParameters) {
    while(1) {
        Serial.println("Enter command: ");
        xTaskCreate(check_serial, "Check Serial Port", 1000, (void*)(xTaskGetCurrentTaskHandle()), configMAX_PRIORITIES - 1, NULL);
        vTaskSuspend(NULL);

        char cmd[10];
        uint8_t i = 0;

        while(Serial.available())
            cmd[i++] = Serial.read();
        
        if(strcmp(cmd, "send")) {
            uint8_t packet[5];
            packet[FROM] = n.getID();
            packet[TO] = node_a;
            packet[MESSAGE] = LED;
            xTaskCreate(send_task, "Send UDP packets", 10000, (void*)packet, configMAX_PRIORITIES - 1, NULL);
        }
    }
}

void get_info() {
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
}

void setup() {
    // Start code
	Serial.begin(BAUD);
    Serial.println("\n***************************************");
    Serial.println("Routine start.");
    
    if(!n.connectWifi()) {
        Serial.println("\nCannot connect to WiFi. Rebooting... ");
        ESP.restart();
    }

    Serial.println("\nConnected to WiFi network.");

    if(n.setIP())
        Serial.println("=> IP well set.");
    else
        Serial.println("=> IP not well set.");

    if(n.setTree())
        Serial.println("=> Tree well set.");
    else
        Serial.println("=> Tree not well set.\n\n");

    n.startUDP();
    
    get_info();
    
    xTaskCreate(read_task, "Read UDP packets", 10000, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(control_task, "Control", 10000, NULL, configMAX_PRIORITIES - 1, NULL);
}

void loop() {

}
