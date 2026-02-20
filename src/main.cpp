#include "core/ring_buffer.hpp"
#include "log/logger.hpp"
int main() {
  logger::Logger::get_instance()->set_level_from_env("A_LOG");

  LOG_INFO("Starting miniDPI");

  auto rb = core::RingBuffer<int>(20);
}
