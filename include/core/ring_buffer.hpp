#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP

#include <algorithm>
#include <atomic>
#include <cstddef>
#include <exception>
#include <optional>
#include <stdexcept>
#include <vector>

#include "log/logger.hpp"

// =====SPSC Lock-free RingBuffer=====
namespace core {
template <typename T> class RingBuffer {
public:
  RingBuffer(std::size_t capacity) : capacity_(capacity), head_(0), tail_(0), buffer_(capacity_) {
    LOG_TRACE("Creating RingBuffer with capacity: {}", capacity);
    if (capacity_ < 2) {
      throw std::invalid_argument("Capacity must be  >= 2 for SPSC ringbuffer");
    }
  }

  bool push(const T& val) noexcept {
    // buff[tail % capacity] = val
    // tail = tail + 1
    // size + 1

    const auto tail = tail_.load(std::memory_order_relaxed);
    const auto next = inc(tail);

    if (next == head_.load(std::memory_order_acquire)) {
      return false;
    }

    buffer_[tail] = val;

    tail_.store(next, std::memory_order_release);
    return true;
  }

  // Producer Method
  bool push(T&& val) noexcept {
    // buff[tail % capacity] = val
    // tail = tail + 1
    // size + 1

    const auto tail = tail_.load(std::memory_order_relaxed);
    const auto next = inc(tail);

    if (next == head_.load(std::memory_order_acquire)) {
      return false;
    }

    buffer_[tail] = std::move(val);

    tail_.store(next, std::memory_order_release);
    return true;
  }

  // Consumer method
  std::optional<T> pop() noexcept {
    const auto head = head_.load(std::memory_order_relaxed);

    if (head == tail_.load(std::memory_order_acquire)) {
      return std::nullopt;
    }

    T value = std::move(buffer_[head]);

    head_.store(inc(head), std::memory_order_release);
    return value;
  }

private:
  std::size_t inc(std::size_t i) const noexcept {
    ++i;
    return (i == capacity_) ? 0 : i;
  }
  alignas(64) std::atomic<std::size_t> capacity_;
  alignas(64) std::atomic<std::size_t> head_;
  alignas(64) std::atomic<std::size_t> tail_;
  alignas(64) std::vector<T> buffer_;
};
} // namespace core
#endif // RING_BUFFER_HPP
