// NetworkRobot.cpp
#include "NetworkRobot.h"

NetworkRobot::NetworkRobot(const std::string& ipAddress, int port)
    : ipAddress_(ipAddress), port_(port), clientSocket_(-1) {

    clientSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket_ == -1) {
        std::cerr << "Failed to create socket" << std::endl;
    }
}

NetworkRobot::~NetworkRobot() {
    close(clientSocket_);
}

void NetworkRobot::receiveData(const fira_message::Packet& packet) {
    receivedPacket_ = packet;
}

void NetworkRobot::processData() {
    for (const fira_message::Command& command : receivedPacket_.commands().robot_commands()) {
        
    }
}

void NetworkRobot::sendData() {
    if (clientSocket_ == -1) {
        std::cerr << "Socket is not created" << std::endl;
        return;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port_);
    serverAddress.sin_addr.s_addr = inet_addr(ipAddress_.c_str());

    if (connect(clientSocket_, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to connect" << std::endl;
        return;
    }

    std::string dataToSend = processedData_;
    send(clientSocket_, dataToSend.c_str(), dataToSend.size(), 0);
}
