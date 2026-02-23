#ifndef TCP_HPP
#define TCP_HPP

#include <cstdint>
struct Tcp {
  uint16_t src_port;
  uint16_t dst_port;
  uint32_t sn;
  uint32_t ack_sn;
  uint8_t
};
#endif
