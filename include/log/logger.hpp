#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <format>
#include <iostream>
#include <mutex>
#include <string>

namespace logger {
enum class LogLevel {
  TRACE,
  DEBUG,
  INFO,
  WARNING,
  ERROR,
  CRITICAL,
};

std::string to_string(LogLevel level);
LogLevel from_string(const std::string &str);

class Logger {
public:
  static Logger *get_instance() {
    static Logger instance;
    return &instance;
  }

  template <typename... Args> void trace(std::string_view fmt, Args &&...args) {
    write_message(LogLevel::TRACE, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args> void debug(std::string_view fmt, Args &&...args) {
    write_message(LogLevel::DEBUG, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args> void info(std::string_view fmt, Args &&...args) {
    write_message(LogLevel::INFO, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args> void warning(std::string_view fmt, Args &&...args) {
    write_message(LogLevel::WARNING, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args> void error(std::string_view fmt, Args &&...args) {
    write_message(LogLevel::ERROR, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args> void critical(std::string_view fmt, Args &&...args) {
    write_message(LogLevel::CRITICAL, fmt, std::forward<Args>(args)...);
  }

  void set_level(LogLevel level) { log_level_ = level; }
  void set_level_from_env(std::string env);

private:
  template <typename... Args>
  void write_message(LogLevel level, std::string_view fmt, Args &&...args) {
    if (level < log_level_) {
      return;
    }

    auto now = std::chrono::system_clock::now();
    std::string formatted_time = std::format("{:%H:%M:%S}", now);
    std::string formated_args{std::vformat(fmt, std::make_format_args(args...))};
    std::string formated_string{
        std::format("[{}] [{}]: {}", formatted_time, to_string(level), formated_args)};
    std::lock_guard<std::mutex> lock(mtx_);
    std::cout << formated_string << std::endl;
  }

  std::mutex mtx_;
  LogLevel log_level_{LogLevel::INFO};
};
} // namespace logger
#define LOG_TRACE(...) ::logger::Logger::get_instance()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) ::logger::Logger::get_instance()->debug(__VA_ARGS__)
#define LOG_INFO(...) ::logger::Logger::get_instance()->info(__VA_ARGS__)
#define LOG_WARNING(...) ::logger::Logger::get_instance()->warning(__VA_ARGS__)
#define LOG_ERROR(...) ::logger::Logger::get_instance()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::logger::Logger::get_instance()->critical(__VA_ARGS__)
#endif
