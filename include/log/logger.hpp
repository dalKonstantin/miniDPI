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

namespace log {
enum class LogLevel {
  TRACE,
  DEBUG,
  INFO,
  WARNING,
  ERROR,
  CRITICAL,
};

std::string to_string(LogLevel level) {
  switch (level) {
  case LogLevel::TRACE:
    return "TRACE";
  case LogLevel::DEBUG:
    return "DEBUG";
  case LogLevel::INFO:
    return "INFO";
  case LogLevel::WARNING:
    return "WARNING";
  case LogLevel::ERROR:
    return "ERROR";
  case LogLevel::CRITICAL:
    return "CRITICAL";
  default:
    return "TRACE";
  }
}

LogLevel from_string(const std::string &str) {
  std::string lower_case(str.size(), ' ');
  std::transform(str.begin(), str.end(), lower_case.begin(),
                 [](char ch) { return std::tolower(ch); });

  if (lower_case == "trace")
    return LogLevel::TRACE;
  else if (lower_case == "debug")
    return LogLevel::DEBUG;
  else if (lower_case == "info")
    return LogLevel::INFO;
  else if (lower_case == "warning")
    return LogLevel::WARNING;
  else if (lower_case == "error")
    return LogLevel::ERROR;
  else if (lower_case == "critical")
    return LogLevel::CRITICAL;
  else
    return LogLevel::INFO;
}
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
  void set_level_from_env(std::string env) {
    char const *val = std::getenv(env.c_str());
    if (val == nullptr) {
      set_level(LogLevel::INFO);
    } else {
      set_level(from_string(val));
    }
  }

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
} // namespace log
#define LOG_TRACE(...) ::log::Logger::get_instance()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) ::log::Logger::get_instance()->debug(__VA_ARGS__)
#define LOG_INFO(...) ::log::Logger::get_instance()->info(__VA_ARGS__)
#define LOG_WARNING(...) ::log::Logger::get_instance()->warning(__VA_ARGS__)
#define LOG_ERROR(...) ::log::Logger::get_instance()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::log::Logger::get_instance()->critical(__VA_ARGS__)
#endif
