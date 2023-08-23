// NetworkRobot.h
#pragma once

#include "../Network.h"
#include "../../pb/command.pb.h"

class NetworkRobot {
public:
    explicit NetworkRobot(const std::string& ipAddress, int port);
    ~NetworkRobot();

    void receiveData(const fira_message::Packet& packet);
    void processData();
    void sendData();

private:
    std::string ipAddress_;
    int port_;
    
    fira_message::Packet receivedPacket_;
    std::string processedData_;
    int clientSocket_;
};