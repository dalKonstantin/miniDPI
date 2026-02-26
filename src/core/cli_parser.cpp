#include "core/cli_parser.hpp"
#include "CLI11/CLI11.hpp"

namespace core {

CLIParser::CLIParser(int argc, char** argv) : argc_(argc), argv_(argv) {};

bool CLIParser::parse() {
  CLI::App app("miniDPI");
  argv_ = app.ensure_utf8(argv_);
  app.add_option("-i,--interface", config_.interface, "Interface name")->required(true);

  try {
    CLI11_PARSE(app, argc_, argv_);
    return true;
  } catch (const CLI::ParseError& e) {
    error_message_ = app.help();
    return false;
  } catch (const CLI::Error& e) {
    error_message_ = e.what();
    return false;
  }
};

std::string CLIParser::print_help() {
  CLI::App app("miniDPI");
  app.add_option("-i,--interface", "Interface name")->required(true);
  app.set_version_flag("-v,--version", "miniDPI 0.1.0");
  app.set_help_flag("-h,--help");

  return app.help();
}

const CLIParser::Config& CLIParser::get_config() const { return config_; }
bool CLIParser::has_error() const { return !error_message_.empty(); }
std::string CLIParser::get_error_message() const { return error_message_; }
} // namespace core
