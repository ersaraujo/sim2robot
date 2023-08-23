// NetworkFira.h
#pragma once

#include "../Network.h"
#include "../../pb/command.pb.h"


class NetworkFira {
public:
    explicit NetworkFira(int port);
    ~NetworkFira();

    fira_message::Packet receiveData();
    void processData(const fira_message::Packet& packet);

private:
    int port_;
    int socket_;
};