#ifndef NETWORKROBOT_H
#define NETWORKROBOT_H

#include <sys/socket.h>

class NetworkRobot {
public:
    NetworkRobot();
    virtual ~NetworkRobot();
    void send();
};

#endif /* NETWORKROBOT_H */
