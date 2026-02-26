#ifndef SNIFFER_HPP
#define SNIFFER_HPP

#include <string>
#include <string_view>
namespace core {
class Sniffer {
public:
  Sniffer(std::string_view iface);
  void loop();
  ~Sniffer();

private:
  std::string iface_{};
  // core::RingBuffer<core::Packet> buffer_(std::size_t 4096) {};
};
} // namespace core
#endif
