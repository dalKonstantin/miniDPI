#include "core/sniffer.hpp"
#include "log/logger.hpp"
#include <cstdio>
#include <pcap.h>
#include <pcap/dlt.h>
#include <pcap/pcap.h>
#include <stdexcept>

namespace core {

Sniffer::Sniffer(std::string_view iface) : iface_(iface) {
  LOG_TRACE("Finding device with specified name: {}", iface);

  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t* handle;
  bpf_u_int32 mask; /* Our netmask */
  bpf_u_int32 net;  /* Our IP */

  handle = pcap_open_live(iface_.data(), BUFSIZ, 1, 1000, errbuf);
  if (handle == nullptr) {
    throw std::runtime_error("Cannot find device with specified name");
  }
  LOG_INFO("Found device with name: {}", iface_);
  if (pcap_datalink(handle) != DLT_EN10MB) {
    throw std::runtime_error("Specified device doesnt provide Ethernet headers");
  }
  LOG_INFO("Specified device supports Ethernet");

  pcap_close(handle);
}
Sniffer::~Sniffer() {}
} // namespace core
