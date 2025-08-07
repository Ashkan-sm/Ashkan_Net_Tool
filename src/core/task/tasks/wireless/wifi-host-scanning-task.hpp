//
// Created by dev on 7/23/25.
//

#ifndef ASHKANTOOL_WIFI_HOST_SCANNING_TASK_HPP
#define ASHKANTOOL_WIFI_HOST_SCANNING_TASK_HPP

#include "PcapLiveDevice.h"

#include "core/task/task.hpp"
#include "core/data-holders/wifi.hpp"
#include "core/packet-receiver/packet-receiver.hpp"
#include "core/capture-wrapper.hpp"

namespace ashk::tasks {
class WifiHostScanningTask : public Task {
 public:
  explicit WifiHostScanningTask(pcpp::PcapLiveDevice *dev,
                                std::string iface_name_or_ip,
                                std::vector<std::shared_ptr<WifiHost>> &host_list,
                                int last_task_id);
  std::string GetData(tasks_data_id data_id) override;
 private:
  void Exec_() override;
  pcpp::PcapLiveDevice *dev_ = nullptr;
  std::string iface_name_or_ip_;
  std::vector<std::shared_ptr<WifiHost>> *host_list_;
  CaptureWrapper &capture_wrapper_ = CaptureWrapper::getInstance();

};
}

#endif //ASHKANTOOL_WIFI_HOST_SCANNING_TASK_HPP
