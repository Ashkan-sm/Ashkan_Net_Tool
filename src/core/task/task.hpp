//
// Created by dev on 6/7/25.
//

#ifndef ASHKANTOOL_TASK_HPP
#define ASHKANTOOL_TASK_HPP

#include <memory>
#include <thread>
#include <atomic>
#include <set>

#include "utils/logger.hpp"

namespace ashk {
enum tasks_data_id { VICTIM_DST_MAC, VICTIM_SRC_MAC, WPA2_CRACK_T };
class Task {

 public:
  void start();
  void end();
  bool is_running();
  virtual std::string get_data(tasks_data_id data_id) = 0;
 protected:
  virtual void exec() = 0;
  explicit Task(int last_task_id) : last_task_id(last_task_id) {}
  utils::Logger &logger = utils::Logger::getInstance();
  std::shared_ptr<std::thread> thread_;
  std::atomic_flag m = ATOMIC_FLAG_INIT;
  std::set<tasks_data_id> extractable_data;
  int last_task_id;
};

}
#endif //ASHKANTOOL_TASK_HPP
