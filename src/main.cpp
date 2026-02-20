#include "log/logger.hpp"
int main() {
  logger::Logger::get_instance()->set_level_from_env("A_LOG");

  LOG_INFO("Starting miniDPI");
}
