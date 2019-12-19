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
        WiFiUDP udp;
        std::list<String> DATA_S;
        std::list<String> DATA_T;
        std::array<String,5> packet;

    public:
        bool setTree();
        bool setIP();
        String getIP();
        bool connectWifi();
        int8_t getID();
        node getMonkey();
        std::vector <node> getBananas();
        String getNames(node n);
        void received_data(uint8_t* data);
        void send_data(uint8_t instruction);
        WiFiUDP getUDP();
};


