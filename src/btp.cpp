#include <btp.h>

std::map <std::string, node> mac_t {
    {"A4:CF:12:54:DD:D4", node_a},
    {"3C:71:BF:EA:B6:A8", node_b},
    {"30:AE:A4:15:1C:0C", node_c}
};

std::map <node, String> node_names = {
    {root, "root"},
    {node_a, "node A"},
    {node_b, "node B"},
    {node_c, "node C"}
};


std::map <node, std::vector <node>> tree_init {
    {node_a, {root, node_b, node_c}},
    {node_b, {node_a}},
    {node_c, {node_a}}
};

std::map <instruc, String> instructions {
    {LED, "Change LED state"},
    {HELLO, "Say Hello"},
    {RECONF, "Reconfigure tree"}
};

bool Node::connectWifi() {
    uint8_t count = 0;
    Serial.print("Connecting to WiFi.");
    vTaskDelay(1000);

    WiFi.begin(NET, PASS);

    while(WiFi.status() != WL_CONNECTED) {
        if(count < 14)
            Serial.print(".");
        else if(count == 14)
            return false ;
        count++;
        vTaskDelay(1000);
    }

    ip_id = mac_t.find(WiFi.macAddress().c_str())->second;

    return true;
}

bool Node::setIP() {
    IPAddress ip(172, 20, 10, ip_id);
    IPAddress gateway(172, 20, 10, 14);
    IPAddress subnet(255, 255, 255, 240);

    if (!WiFi.config(ip, gateway, subnet))
        return false;

    return true;
}

bool Node::setTree() {
    monkey = (tree_init.find((node)ip_id)->second)[MONKEY];
    
    for(int i = 1; i < (tree_init.find((node)ip_id)->second).size(); i++)
        banana.push_back((node)(tree_init.find((node)ip_id)->second)[i]);
    return true;
}

void Node::startUDP() {
    udp.begin(PORT);
}


int8_t Node::getID(){
    return ip_id;
}

String Node::getIP() {
    return (WiFi.localIP().toString());
}

node Node::getMonkey() {
    return monkey;
}

std::vector <node> Node::getBananas() {
    return banana;
}

String Node::getNames(node n) {
    return node_names.find(n)->second;
}

String Node::getSSID() {
    return WiFi.SSID();
}

String Node::getInstruction(instruc i) {
    return instructions.find(i)->second;
}

void Node::sendPacket(node from, node to, instruc instruction) {
    uint8_t packet[5], pac[5];

    pac[0] = from;
    pac[1] = instruction;
    pac[2] = to;

    DATA_S.push_front(pac);

    if(!DATA_S.empty()) {
        uint8_t* data = DATA_S.back();
        DATA_S.pop_back();

        packet[0] = data[0] + 48;
        packet[1] = data[1] + 48;
        packet[2] = data[2] + 48;
        Serial.println(data[2]);
        IPAddress ip(172, 20, 10, data[2]);

        udp.beginPacket(ip, PORT);
        udp.write(packet, 5);
        udp.endPacket();
    }
  }

  void Node::sendPacket(uint8_t* data) {
    this->sendPacket((node)data[0], (node)data[1], (instruc)data[2]);
  }

WiFiUDP Node::getUDP() {
    return udp;
}

ret_t Node::readPacket(uint8_t* par) {
    uint8_t data[5] = {0}, size = 0;
    size = udp.parsePacket();

    if(size > 0) {
        udp.read(data, size);
        strcpy((char*)par, (char*)data);
        udp.flush();
        if((node)(data[FROM] - 48) == ip_id) 
            return KEEP;
        else if((tree_init.find((node)ip_id)->second).size() - 1 > 0) 
            return FOWARD;
        else
            return IGNORE;
    }
    return EMPTY;
}

void Node::scanNetworks() {
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }
    Serial.println("");
}