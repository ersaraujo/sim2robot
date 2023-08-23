// NetworkFira.cpp
#include "NetworkFira.h"

NetworkFira::NetworkFira(int port)
    : port_(port), socket_(-1) {

    socket_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_ == -1) {
        std::cerr << "Failed to create socket" << std::endl;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port_);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(socket_, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
    }
}

NetworkFira::~NetworkFira() {
    close(socket_);
}

fira_message::Packet NetworkFira::receiveData() {
    char buffer[1024]; 
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytesRead = recv(socket_, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        std::cerr << "Failed to receive data" << std::endl;
        return fira_message::Packet();
    }

    std::string receivedData(buffer, static_cast<size_t>(bytesRead));

    fira_message::Packet packet;
    if (!packet.ParseFromString(receivedData)) {
        std::cerr << "Failed to parse received data as protobuf" << std::endl;
        return fira_message::Packet();
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
