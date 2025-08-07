//
// Created by dev on 6/9/25.
//

#ifndef ASHKANTOOL_ARP_POISONING_TASK_HPP
#define ASHKANTOOL_ARP_POISONING_TASK_HPP

#include "PcapLiveDevice.h"
#include "PcapLiveDeviceList.h"
#include "EthLayer.h"
#include "Packet.h"

#include "utils/net-utils.hpp"
#include "core/task/task.hpp"
namespace ashk::tasks {
class ArpPoisoningTask : public Task {
 public:
  explicit ArpPoisoningTask(pcpp::PcapLiveDevice *dev,
                            pcpp::IPv4Address vic_src_ip,
                            pcpp::IPv4Address vic_dst_ip,
                            pcpp::IPv4Address forward_to_ip,
                            pcpp::IPv4Address iface_ip,
                            int last_task_id);
  std::string GetData(tasks_data_id data_id) override;
 private:
  void Exec_() override;
  pcpp::PcapLiveDevice *dev_ = nullptr;
  pcpp::IPv4Address vic_src_ip_;
  pcpp::IPv4Address vic_dst_ip_;
  pcpp::IPv4Address forward_to_ip_;
  pcpp::IPv4Address iface_ip_;
  pcpp::MacAddress vic_dst_mac_;
  pcpp::MacAddress vic_src_mac_;

  std::set<tasks_data_id> extractable_data_{
      VICTIM_DST_MAC,
      VICTIM_SRC_MAC
  };
};
}

#endif //ASHKANTOOL_ARP_POISONING_TASK_HPP
