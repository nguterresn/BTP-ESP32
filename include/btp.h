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
        std::list<uint8_t*> DATA_S;
        std::array<String, 5> packet;
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
        String getInstruction(instruc i);
        String getSSID();
        void sendPacket(node from, node to, instruc instruction);
        void sendPacket(uint8_t *data);
        WiFiUDP getUDP();
        ret_t readPacket(uint8_t* par);
        void scanNetworks();
};


