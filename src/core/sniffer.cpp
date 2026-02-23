#include "core/sniffer.hpp"

namespace core {

Sniffer::Sniffer(std::string_view dev_name, core::RingBuffer<core::Packet> packet_buffer) {}
Sniffer::~Sniffer() {}
} // namespace core
