//
// Created by dev on 6/7/25.
//

#include "core/task/task.hpp"

namespace ashk {
void Task::Start() {
  if (!m_.test_and_set()) {
    thread_ = std::make_unique<std::thread>([this]() {
      Exec_();
    });
    thread_->detach();
    return;
  }
  utils::Logger::getInstance().Log("Unable to start task");
}

void Task::End() {
  m_.clear();

}

bool Task::IsRunning() {
  if (m_.test_and_set()) {
    return true;
  }
  m_.clear();
  return false;
}

}


