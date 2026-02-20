#include "log/logger.hpp"

namespace logger {

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

void Logger::set_level_from_env(std::string env) {
  char const *val = std::getenv(env.c_str());
  if (val == nullptr) {
    set_level(LogLevel::INFO);
  } else {
    set_level(from_string(val));
  }
}
} // namespace logger
