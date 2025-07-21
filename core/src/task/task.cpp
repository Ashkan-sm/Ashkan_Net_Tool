//
// Created by dev on 6/7/25.
//

#include "task.hpp"
namespace ashk {
    void Task::start() {
        if (!m.test_and_set()) {
            thread_ = std::make_unique<std::thread>([this]() {
                exec();
            });
            thread_->detach();
            return;
        }
        utils::Logger::getInstance().log("Unable to start task");
    }

    void Task::end() {
        m.clear();
        utils::Logger::getInstance().log("Sent end signal to task");
    }

    bool Task::is_running() {
        if(m.test_and_set()){
            return true;
        }
        m.clear();
        return false;
    }


}


