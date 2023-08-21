// NetworkFira.cpp
#include "NetworkFira.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

NetworkFira::NetworkFira(int port)
    : port_(port), socket_(-1) {
    // Crie o socket UDP
    socket_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_ == -1) {
        std::cerr << "Failed to create socket" << std::endl;
    }

    // Configure a estrutura de endereço do servidor
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port_);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Associe o socket à porta e endereço
    if (bind(socket_, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
    }
}

NetworkFira::~NetworkFira() {
    close(socket_);
}

fira_message::Packet NetworkFira::receiveData() {
    char buffer[1024];  // Tamanho do buffer para armazenar os dados recebidos
    memset(buffer, 0, sizeof(buffer));  // Limpa o buffer

    ssize_t bytesRead = recv(socket_, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        std::cerr << "Failed to receive data" << std::endl;
        return fira_message::Packet();  // Retorna um pacote vazio em caso de erro
    }

    // Suponha que o buffer contém os dados recebidos
    std::string receivedData(buffer, static_cast<size_t>(bytesRead));

    // Agora você pode desserializar os dados recebidos em um pacote protobuf
    fira_message::Packet packet;
    if (!packet.ParseFromString(receivedData)) {
        std::cerr << "Failed to parse received data as protobuf" << std::endl;
        return fira_message::Packet();  // Retorna um pacote vazio em caso de erro
    }

    return packet;
}

void NetworkFira::processData(const fira_message::Packet& packet) {
    for (const fira_message::Command& command : packet.commands().robot_commands()) {
        std::cout << "Received Command:" << std::endl;
        std::cout << "  ID: " << command.id() << std::endl;
        std::cout << "  Yellow Team: " << (command.yellowteam() ? "true" : "false") << std::endl;
        std::cout << "  Wheel Left: " << command.wheel_left() << std::endl;
        std::cout << "  Wheel Right: " << command.wheel_right() << std::endl;
    }
}
