//
// Created by dev on 6/9/25.
//

#ifndef ASHKANTOOL_ARP_POISON_DETECTION_TASK_HPP
#define ASHKANTOOL_ARP_POISON_DETECTION_TASK_HPP

#include "core/task/task.hpp"
#include "core/capture-wrapper.hpp"
#include "core/packet-receiver/packet-receiver.hpp"

namespace ashk::tasks {
class ArpPoisonDetectionTask : public Task {
 public:
  explicit ArpPoisonDetectionTask(pcpp::IPv4Address iface_ip, int last_task_id);
  std::string GetData(tasks_data_id data_id) override;
 private:
  void Exec_() override;
  pcpp::PcapLiveDevice *dev_ = nullptr;
  pcpp::IPv4Address iface_ip_;
  CaptureWrapper &capture_wrapper_ = CaptureWrapper::getInstance();

};
}

#endif //ASHKANTOOL_ARP_POISON_DETECTION_TASK_HPP
