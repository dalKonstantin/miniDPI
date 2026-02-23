#include "log/logger.hpp"
#include <pcap/pcap.h>
#include <stdexcept>
#include <sys/types.h>
#include <unistd.h>

int main() {
  try {
    LOG_INFO("Starting miniDPI");

    if (getuid() != 0) {
      throw std::runtime_error("Root privileges required. Please run it with sudo.");
    }
  } catch (const std::runtime_error& e) {
    LOG_CRITICAL("Runtime Error: {}", e.what());
  }
  return 0;
}
