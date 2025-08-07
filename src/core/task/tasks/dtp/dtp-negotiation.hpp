//
// Created by dev on 7/9/25.
//

#ifndef ASHKANTOOL_DTP_NEGOTIATION_HPP
#define ASHKANTOOL_DTP_NEGOTIATION_HPP

#include <netinet/in.h>

#include "PcapLiveDevice.h"
#include "PcapLiveDeviceList.h"
#include "Packet.h"

#include "core/task/task.hpp"

namespace ashk::tasks {
class DTPNegotiation : public Task {
 public:
  explicit DTPNegotiation(pcpp::PcapLiveDevice *dev,
                          pcpp::IPv4Address iface_ip,
                          std::string domain_name,
                          int last_task_id);
  std::string GetData(tasks_data_id data_id) override;
 private:
  void Exec_() override;
  pcpp::PcapLiveDevice *dev_ = nullptr;
  pcpp::IPv4Address iface_ip_;
  std::string domain_name_;

};

}

#endif //ASHKANTOOL_DTP_NEGOTIATION_HPP
