#pragma once

#include "NetworkFira/NetworkFira.h"
#include "NetworkRobot/NetworkRobot.h"
#include "../pb/command.pb.h"

#include <sys/socket.h>

class Network {
public:
    Network();
    virtual ~Network();
    void send();
};
