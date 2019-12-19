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

bool Node::connectWifi() {
    uint32_t time = 0;

    WiFi.begin(NET, PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        time += 1000;
        if (time > 15000)
            return false;
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
    udp.begin(6535);
    return true;
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

void Node::send_data(uint8_t instruction){
     uint8_t packet[5];

    if(!DATA_S.empty()) {
        String data = DATA_S.back();
        DATA_S.pop_back();

        if(data[2] == getMonkey() || 
        std::find(getBananas().begin(),getBananas().end(),data[2]) != getBananas().end()){ 
        // Destination is father or children
            packet[0] = data[0];
            packet[1] = data[1];
            packet[2] = data[2];
            packet[3] = ip_id;
            IPAddress ip(172,20,10,data[2]);
            udp.beginPacket(ip,6535);
            udp.write(packet,5);
            udp.endPacket();

        }
        else if(data[3] == getMonkey()){
        // Only know that I received from father and that the destination address is not a neightbor
            packet[0] = data[0];
            packet[1] = data[1];
            packet[2] = data[2];
            packet[3] = ip_id;
            for(int i = 0; i<getBananas().size();i++){
                IPAddress ip(172,20,10,getBananas().at(i));
                udp.beginMulticast(ip,6535);
            }
            udp.beginMulticastPacket();
            udp.write(packet,5);
            udp.endPacket();
        
        }
        else if(std::find(getBananas().begin(),getBananas().end(),data[3]) != getBananas().end()){
            //Received from children and destination is not a neightbor
            packet[0] = data[0];
            packet[1] = data[1];
            packet[2] = data[2];
            packet[3] = ip_id;
            for(int i = 0; i<getBananas().size();i++){
                if(data[3]!=getBananas().at(i)){
                IPAddress ip(172,20,10,getBananas().at(i));
                udp.beginMulticast(ip,6535);
                }
            }
            IPAddress ip(172,20,10,getMonkey());
            udp.beginMulticast(ip,6535);
            udp.beginMulticastPacket();
            udp.write(packet,5);
            udp.endPacket();
        }
        else if(data[1] == getID()){ 
        //Send data to a destiantion that is not a neightbor and i didnt received from anyone
            packet[0] = data[0];
            packet[1] = data[1];
            packet[2] = data[2];
            packet[3] = ip_id;
            for(int i = 0; i<getBananas().size();i++){
                IPAddress ip(172,20,10,getBananas().at(i));
                udp.beginMulticast(ip,6535);
            }
            IPAddress ip(172,20,10,getMonkey());
            udp.beginMulticast(ip,6535);
            udp.beginMulticastPacket();
            udp.write(packet,5);
            udp.endPacket();

        }
    }
  }


void Node::received_data(uint8_t* data) {
    uint8_t *aux = data;
    if(udp.parsePacket()) {
        udp.read(aux, 5);
        strcpy((char *) data, (char *) aux);
    }
}

WiFiUDP Node::getUDP() {
    return udp;
}