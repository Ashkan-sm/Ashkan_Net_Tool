//
// Created by dev on 6/5/25.
//

#include "logger.hpp"
namespace ashk::utils {

Logger &Logger::getInstance() {
  static Logger logger;
  return logger;

}

Logger::Logger() = default;

void Logger::Log(const std::string &log) {
  for (const auto &i : log_methods_) {
    i(log);
  }
}

void Logger::AddLogMethod(const std::function<void(const std::string &)> &method) {
  log_methods_.push_back(method);
}

}