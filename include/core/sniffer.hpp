#ifndef SNIFFER_HPP
#define SNIFFER_HPP

#include "core/packet.hpp"
#include "core/ring_buffer.hpp"
#include <string_view>
class Sniffer {
  Sniffer(std::string_view dev_name, core::RingBuffer<core::Packet> packet_buffer);
  ~Sniffer();
};
#endif
