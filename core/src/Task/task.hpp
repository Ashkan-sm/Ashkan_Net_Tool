//
// Created by dev on 6/7/25.
//

#ifndef ASHKANTOOL_TASK_HPP
#define ASHKANTOOL_TASK_HPP

#include <memory>
#include <thread>
#include <atomic>
#include "../../../utils/logger.hpp"
namespace ashk {
    class Task {
    public:
        void start();
        void end();
        bool is_running();
    protected:
        virtual void exec() = 0;
        utils::Logger &logger= utils::Logger::getInstance();
        std::shared_ptr<std::thread> thread_;
        std::atomic_flag m = ATOMIC_FLAG_INIT;

    };

}
#endif //ASHKANTOOL_TASK_HPP
