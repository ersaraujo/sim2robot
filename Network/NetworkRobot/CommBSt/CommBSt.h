#pragma once

#include "../../Network.h"

#include "CommConfig.h"
#include <cstdint>
#include <iostream>
#include <cstring>

#define IP_ADDRESS "199.0.1.1"
#define PORT 9600

class CommBSt {

public:

    explicit CommBSt();
    ~CommBSt();

    using generic = RC::Comm::generic;
    using vss = RC::Comm::vss;

    void setVSS(uint8_t id, int8_t m1, int8_t m2);
    void sendVSS();

private:
    void sendBSt();
    RC::Comm::bstConfig makeBSt();
protected:
    RC::Comm::VSSPacket vssPacket_;
    int socket_;
};