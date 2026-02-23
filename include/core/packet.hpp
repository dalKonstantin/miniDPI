#ifndef PACKET_HPP
#define PACKET_HPP

#include <chrono>
#include <cstddef>
#include <span>
struct Packet {
  std::chrono::milliseconds timestamp;
  std::span<const std::byte> data;

  void advance(std::size_t bytes) { data = data.subspan(bytes); }
};

#endif
