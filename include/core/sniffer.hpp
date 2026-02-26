#ifndef SNIFFER_HPP
#define SNIFFER_HPP

#include "core/packet.hpp"
#include "core/ring_buffer.hpp"
#include <string_view>
namespace core {
class Sniffer {
  Sniffer(std::string_view dev_name, core::RingBuffer<core::Packet> packet_buffer);
  void loop();
  ~Sniffer();

private:
  core::RingBuffer<core::Packet> buffer_(std::size_t 4096) {};
};
} // namespace core
#endif
