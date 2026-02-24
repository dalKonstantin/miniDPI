#ifndef CLI_PARSE_HPP
#define CLI_PARSE_HPP
#include <string>

namespace core {
class CLIParser {
public:
  struct Config {
    std::string interface; // Interface name
    bool show_version = false;
    bool show_help = false;
  };
  explicit CLIParser(int argc, char** argv);

  bool parse();

  std::string print_help();

  const Config& get_config() const;
  bool has_error() const;
  std::string get_error_message() const;

private:
  int argc_;
  char** argv_;
  Config config_;
  std::string error_message_;
};
} // namespace core

#endif
