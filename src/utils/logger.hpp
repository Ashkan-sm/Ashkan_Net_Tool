//
// Created by dev on 6/5/25.
//

#ifndef ASHKANTOOL_LOGGER_HPP
#define ASHKANTOOL_LOGGER_HPP

#include <functional>
#include <vector>
#include <string>

namespace ashk::utils {
class Logger {
 public:
  static Logger &getInstance();
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  void Log(const std::string &log);
  void AddLogMethod(const std::function<void(const std::string &)> &method);

 private:
  Logger();
  std::vector<std::function<void(const std::string &)>> log_methods_;
};
}

#endif //ASHKANTOOL_LOGGER_HPP
