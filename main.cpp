#include <iostream>
#include "Network/Network.h"

int main() {
    NetworkFira fira(20011);
    fira_message::Packet receivedPacket;

    while (true) {
        receivedPacket = fira.receiveData();

        fira.processData(receivedPacket); 
    }

    return 0;
}
