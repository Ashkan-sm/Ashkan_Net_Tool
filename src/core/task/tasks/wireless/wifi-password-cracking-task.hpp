//
// Created by dev on 8/4/25.
//

#ifndef ASHKANTOOL_WIFI_PASSWORD_CRACKING_TASK_HPP
#define ASHKANTOOL_WIFI_PASSWORD_CRACKING_TASK_HPP

#include "PcapLiveDevice.h"

#include "wpa-2-cracking-thread.hpp"
#include "core/task/task.hpp"

namespace ashk::tasks {
class WifiPasswordCrackingTask : public Task {
 public:
  explicit WifiPasswordCrackingTask(pcpp::PcapLiveDevice *dev,
                                    std::string iface_name_or_ip, std::shared_ptr<HandShakeData> handshake_data,
                                    int last_task_id);
  std::string GetData(tasks_data_id data_id) override;
 private:
  void Exec_() override;
  pcpp::PcapLiveDevice *dev_ = nullptr;
  std::string iface_name_or_ip_;
  std::shared_ptr<HandShakeData> handshake_data_;

};
}

#endif //ASHKANTOOL_WIFI_PASSWORD_CRACKING_TASK_HPP
