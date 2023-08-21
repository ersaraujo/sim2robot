#ifndef NETWORK_H
#define NETWORK_H

#include <sys/socket.h>

class Network {
public:
    Network();
    virtual ~Network();
    void send();
};

#endif /* NETWORK_H */
