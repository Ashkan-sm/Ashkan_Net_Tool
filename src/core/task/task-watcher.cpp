//
// Created by dev on 10/15/25.
//

#include "task-watcher.hpp"
void TaskWatcher::AddAndStartTask(std::shared_ptr<ashk::Task> task_ptr) {
  std::lock_guard<std::mutex> lock(mutex_);
  tasks_[last_task_id_]=task_ptr;
  task_ptr->SetTaskId(last_task_id_);
  task_ptr->SetWatcherNotify(&cnv_);
  task_ptr->Start();
  last_task_id_++;
  cnv_.notify_all();
}
void TaskWatcher::EndTask(int id) {
  if(!tasks_.contains(id)) {
    ashk::utils::Logger::getInstance().Log("invalid task id\n");
    return;
  }
  tasks_[id]->End();
  cnv_.notify_all();
}
void TaskWatcher::WaitChange() {
  std::unique_lock<std::mutex> lock(mutex_);
  cnv_.wait(lock);
}
std::vector<int> TaskWatcher::GetRunningTaskIds() {
  std::vector<int> out;
  out.reserve(last_task_id_);
  for(auto i : tasks_){
    if (i.second->IsRunning())
      out.push_back(i.first);
  }
  return std::move(out);
}
