#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP

#include <atomic>
#include <cstddef>
#include <exception>
#include <optional>
#include <stdexcept>
#include <vector>

#include "log/logger.hpp"

namespace core {
template <typename T> class RingBuffer {
public:
  RingBuffer(std::size_t capacity) : capacity_(capacity), size_(0), head_(0), tail_(0) {
    LOG_TRACE("Creating RingBuffer with capacity: {}", capacity);
    if (capacity_ == 0) {
      throw std::invalid_argument("Capacity cannot be 0");
    }
    buffer_.resize(capacity_);
  }

  bool is_empty() const noexcept { return size_ == 0; };
  bool is_full() const noexcept { return size_ == capacity_; }
  std::size_t size() const noexcept { return size_; }

  bool push(T val) noexcept {
    // buff[tail % capacity] = val
    // tail = tail + 1
    // size + 1

    auto current_tail = head_.load(std::memory_order_relaxed);
    auto next_tail = (current_tail + 1) % capacity_;
    auto current_head = head_.load(std::memory_order_acquire);
    if (next_tail == current_head) {
      return false;
    }

    buffer_[current_tail] = val;

    ++size_;
    tail_.store(next_tail, std::memory_order_release);
    return true;
  }

  std::optional<T> pop() noexcept {
    // current_head = head
    // head = (head + 1) % capacity
    // size - 1
    // return buffer[head]

    auto current_tail = tail_.load(std::memory_order::relaxed);
    auto current_head = head_.load(std::memory_order::acquire);
  }

private:
  alignas(64) std::atomic<std::size_t> capacity_;
  alignas(64) std::atomic<std::size_t> size_;
  alignas(64) std::atomic<std::size_t> head_;
  alignas(64) std::atomic<std::size_t> tail_;
  alignas(64) std::vector<T> buffer_;
};
} // namespace core
#endif // RING_BUFFER_HPP
