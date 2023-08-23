#pragma once

#include "NetworkFira/NetworkFira.h"
#include "NetworkRobot/NetworkRobot.h"

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Network {
public:
    Network();
    virtual ~Network();
    void send();
};
