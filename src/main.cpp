#include "core/ring_buffer.hpp"
#include "log/logger.hpp"
#include <iostream>
#include <pcap/pcap.h>
#include <thread>

int main() {
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_if_t* all_devs;

  if (pcap_findalldevs(&all_devs, errbuf) == -1) {
    LOG_ERROR("Error finding devices: {}", errbuf);
    return 1;
  }

  LOG_INFO("libpcap linked");
  pcap_freealldevs(all_devs);
  return 0;
}
