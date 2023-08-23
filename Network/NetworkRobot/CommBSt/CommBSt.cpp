#include "CommBSt.h"

CommBSt::CommBSt() {
    std::cout << "CommBSt constructor" << std::endl;
    this->socket_ = socket(AF_INET, SOCK_DGRAM, 0);
}

CommBSt::~CommBSt() {
}

void CommBSt::setVSS(uint8_t id, int8_t m1, int8_t m2) {
    memset(&vssPacket_, 0, sizeof(vssPacket_));
    this->vssPacket_.id = id;
    this->vssPacket_.m1 = m1;
    this->vssPacket_.m2 = m2;
}

RC::Comm::bstConfig CommBSt::makeBSt() {
    RC::Comm::bstConfig bstConfig;

    bstConfig.decoded.typeMsg = static_cast<uint8_t>(RC::Comm::CommType::BST_CONFIG);
    bstConfig.decoded.duplex = false;
    bstConfig.decoded.team = 3;
    bstConfig.decoded.addr1 = VSS_ADDR_1;
    bstConfig.decoded.addr2 = VSS_ADDR_2;
    bstConfig.decoded.payload = VSS_PAYLOAD_SIZE;
    bstConfig.decoded.channel1 = VSS_CH;
    bstConfig.decoded.channel2 = VSS_CH_2;

    return bstConfig;
}

void CommBSt::sendVSS() {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_aton(IP_ADDRESS, &addr.sin_addr);

    sendto(this->socket_, &this->vssPacket_, sizeof(this->vssPacket_), 0, (struct sockaddr *)&addr, sizeof(addr));
}

void CommBSt::sendBSt() {

    auto configBSt = this->makeBSt();
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_aton(IP_ADDRESS, &addr.sin_addr);

    sendto(this->socket_, configBSt.encoded, sizeof(this->vssPacket_), 0, (struct sockaddr *)&addr, sizeof(addr));
}


