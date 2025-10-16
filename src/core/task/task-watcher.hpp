//
// Created by dev on 10/15/25.
//

#ifndef ASHKANTOOL_TASK_WATCHER_HPP
#define ASHKANTOOL_TASK_WATCHER_HPP

#include "task.hpp"
#include <map>
#include <condition_variable>
#include "utils/logger.hpp"

class TaskWatcher {
 public:
  int AddAndStartTask(std::shared_ptr<ashk::Task> task_ptr);
  void EndTask(int id);
  void WaitChange();
  bool IsRunning(int id) const;
  std::vector<int> GetRunningTaskIds();
//  ashk::Task& GetTask();

 private:
  std::map<int, std::shared_ptr<ashk::Task>> tasks_;
  std::mutex mutex_;
  std::condition_variable cnv_;
  int last_task_id_=0;
};

#endif  //ASHKANTOOL_TASK_WATCHER_HPP
