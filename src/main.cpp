#include "CLI11/CLI11.hpp"
#include "core/cli_parser.cpp"
#include "core/cli_parser.hpp"
#include "log/logger.hpp"
#include <pcap/pcap.h>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {
  try {
    LOG_INFO("Starting miniDPI");

    if (getuid() != 0) {
      throw std::runtime_error("Root privileges required. Please run it with sudo.");
    }

    auto cli = core::CLIParser(argc, argv);
    cli.parse();
    auto config = cli.get_config();
    std::cout << config.interface << "\n";

  } catch (const std::runtime_error& e) {
    LOG_CRITICAL("Runtime Error: {}", e.what());
  }
  return 0;
}
