#include "core/ring_buffer.hpp"
#include "log/logger.hpp"
#include <iostream>
int main() {
  logger::Logger::get_instance()->set_level_from_env("A_LOG");

  LOG_INFO("Starting miniDPI");

  auto rb = core::RingBuffer<int>(16);

  for (std::size_t i = 0; i < 16; ++i) {
    if (rb.push(i))
      LOG_TRACE("Pushed {} to RingBuffer. Size {}", i, rb.size());
  }

  for (std::size_t i = 0; i < 16; ++i) {
    auto x = rb.pop();
    LOG_TRACE("Poped {} from RingBuffer", *x);
  }
}
