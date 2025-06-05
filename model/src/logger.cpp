//
// Created by dev on 6/5/25.
//

#include "../include/logger.h"

Logger& Logger::getInstance() {
    static Logger logger;
    return logger;

}

Logger::Logger() {

}

void Logger::log(const std::string &log) {
    for(auto i:log_methods){
        i(log);
    }
}

void Logger::add_log_method(std::function<void(const std::string &)> method) {
    log_methods.push_back(method);
}
