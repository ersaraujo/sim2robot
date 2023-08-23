#pragma once

#include <cstdint>

#define VSS_CH 108
#define VSS_CH_2 110
#define VSS_ADDR_1 0x752FAF0A9ALL
#define VSS_ADDR_2 0x5D4BFBC2BBLL

#define ACK_RADIO 0

#define VSS_PAYLOAD_SIZE 4
#define VSS_CONTROL_SIZE VSS_PAYLOAD_SIZE
#define DEFAULT_PAYLOAD_LENGTH 10
#define BST_CONFIG_LENGTH 21

#pragma pack(push, 1)

namespace RC::Comm {

    template <class T, std::size_t N = DEFAULT_PAYLOAD_LENGTH>
    union encodedData {
        unsigned char encoded[N];
        T decoded;
    };

    enum class CommType {
        NONE = -1,
        BST_CONFIG,
        VSS
    };

    struct genericPacket {
        uint8_t typeComm    : 4;
        uint8_t id          : 4;
        int64_t rest_a      : 64;
        int64_t rest_b      : 64;
        int64_t rest_c      : 64;
        int64_t rest_d      : 56;
    };
    using generic = encodedData<genericPacket, BST_CONFIG_LENGTH>;

    struct BStConfig {
        uint8_t typeMsg     : 4;
        uint8_t id          : 4;
        bool duplex         : 1;
        uint8_t team        : 4;
        uint64_t addr1      : 64;
        uint64_t addr2      : 64;
        uint8_t payload     : 8;
        uint8_t channel1    : 8;
        uint8_t channel2    : 8;
        uint8_t free        : 3;
    };
    using bstConfig = encodedData<BStConfig, BST_CONFIG_LENGTH>;

    struct VSSPacket {
        uint8_t typeComm    : 4;
        uint8_t id          : 4;
        int8_t m1           : 8;
        int8_t m2           : 8;
        uint16_t rest       : 8;
    };
    using vss = encodedData<VSSPacket, VSS_CONTROL_SIZE>;
}

#pragma pack(pop)
