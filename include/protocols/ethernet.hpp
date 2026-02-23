#ifndef ETHERNET_HPP
#define ETHERNET_HPP

#include <cstdint>
struct Ethernet {
  uint8_t dst_addr[6];
  uint8_t src_addr[6];
  uint16_t eth_type;
};

#endif
