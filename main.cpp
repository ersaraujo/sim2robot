#include <iostream>
#include "Network/Network.h"

int main() {
    NetworkFira fira(20011);  // Substitua pelo IP multicast e porta corretos
    fira_message::Packet receivedPacket;

    while (true) {
        receivedPacket = fira.receiveData();

        // Processar o pacote recebido no NetworkFira
        fira.processData(receivedPacket);  // Simule o processamento dos dados
    }

    return 0;
}
