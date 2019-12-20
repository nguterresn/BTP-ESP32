#include <stdio.h>
#include <WiFi.h>
#include <stdint.h>
#include <IPAddress.h>
#include <btp_configs.h>

class Node {
    private:
        uint8_t ip_id;
        node monkey;
        std::vector <node> banana;
        std::list<String> DATA_S;
        std::list<String> DATA_T;
        std::array<String,5> packet;
        WiFiUDP udp;
    public:
        bool setTree();
        bool setIP();
        String getIP();
        bool connectWifi();
        int8_t getID();
        void startUDP();
        node getMonkey();
        std::vector <node> getBananas();
        String getNames(node n);
        void sendPacket(uint8_t instruction);
        WiFiUDP getUDP();
        void readPacket();
};


