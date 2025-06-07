//
// Created by dev on 6/5/25.
//

#include "../include/logger.hpp"
namespace ashk{

Logger & Logger::getInstance() {
    static Logger logger;
    return logger;

}

Logger::Logger()=default;

void Logger::log(const std::string &log) {
    for (const auto &i: log_methods) {
        i(log);
    }
}

void Logger::add_log_method(const std::function<void(const std::string &)> &method) {
    log_methods.push_back(method);
}

}