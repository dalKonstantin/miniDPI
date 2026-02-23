#ifndef ETHERNET_HPP
#define ETHERNET_HPP

#include <cstdint>
// Save current setting and set new aligment to 1
#pragma pack(push, 1)
struct Ethernet {
  uint8_t dst_addr[6];
  uint8_t src_addr[6];
  uint16_t eth_type; // Big-Endian
  // uint32_t checksum; NIC will drop this
};
// Restore previous alignment
#pragma pack(pop)

#endif
