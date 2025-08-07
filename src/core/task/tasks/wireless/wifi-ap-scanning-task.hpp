//
// Created by dev on 7/22/25.
//

#ifndef ASHKANTOOL_WIFI_AP_SCANNING_TASK_HPP
#define ASHKANTOOL_WIFI_AP_SCANNING_TASK_HPP

#include "core/task/task.hpp"
#include "core/data-holders/wifi.hpp"
#include "core/capture-wrapper.hpp"
#include "core/packet-receiver/packet-receiver.hpp"

namespace ashk::tasks {
class WifiApScanningTask : public Task {
 public:
  explicit WifiApScanningTask(pcpp::PcapLiveDevice *dev,
                              std::string iface_name_or_ip,
                              std::vector<WifiAp> &ap_list,
                              int last_task_id);
  std::string GetData(tasks_data_id data_id) override;
 private:
  void Exec_() override;
  pcpp::PcapLiveDevice *dev_ = nullptr;
  std::string iface_name_or_ip_;
  std::vector<WifiAp> *ap_list_;
  CaptureWrapper &capture_wrapper_ = CaptureWrapper::getInstance();

};
}

#endif //ASHKANTOOL_WIFI_AP_SCANNING_TASK_HPP
