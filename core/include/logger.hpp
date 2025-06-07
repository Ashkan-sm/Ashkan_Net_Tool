//
// Created by dev on 6/5/25.
//

#ifndef ASHKANTOOL_LOGGER_HPP
#define ASHKANTOOL_LOGGER_HPP

#include <functional>
#include <vector>
#include <string>
namespace ashk {
    class Logger {
    public:
        static Logger &getInstance();

        void log(const std::string &log);

        void add_log_method(const std::function<void(const std::string &)> &method);

    private:
        Logger();

        Logger(const Logger &) = delete;

        Logger &operator=(const Logger &) = delete;

        std::vector<std::function<void(const std::string &)>> log_methods;
    };
}

#endif //ASHKANTOOL_LOGGER_HPP
