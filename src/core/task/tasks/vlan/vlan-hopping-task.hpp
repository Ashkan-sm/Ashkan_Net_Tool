//
// Created by dev on 6/10/25.
//

#ifndef ASHKANTOOL_VLAN_HOPPING_TASK_HPP
#define ASHKANTOOL_VLAN_HOPPING_TASK_HPP

#include "PcapLiveDevice.h"

#include "core/task/task.hpp"
#include "core/packet-receiver/packet-receiver.hpp"
#include "core/capture-wrapper.hpp"

namespace ashk::tasks {
class VlanHoppingTask : public Task {
 public:
  explicit VlanHoppingTask(pcpp::PcapLiveDevice *dev,
                           pcpp::IPv4Address iface_ip,
                           int outer_id,
                           int inner_id,
                           int last_task_id);
  std::string GetData(tasks_data_id data_id) override;
 private:
  void Exec_() override;
  pcpp::PcapLiveDevice *dev_ = nullptr;
  pcpp::IPv4Address iface_ip_;
  CaptureWrapper &capture_wrapper_ = CaptureWrapper::getInstance();
  int outer_id_;
  int inner_id_;

};

}

#endif //ASHKANTOOL_VLAN_HOPPING_TASK_HPP
