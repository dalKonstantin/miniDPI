#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP

#include <atomic>
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

  bool is_empty() { return size_ == 0; };
  bool is_full() { return size_ == capacity_; }

  void push(T val);
  T pop();

private:
  std::atomic<std::size_t> capacity_;
  std::atomic<std::size_t> size_;
  std::atomic<std::size_t> head_;
  std::atomic<std::size_t> tail_;
  std::vector<T> buffer_;
};
} // namespace core
#endif // RING_BUFFER_HPP
