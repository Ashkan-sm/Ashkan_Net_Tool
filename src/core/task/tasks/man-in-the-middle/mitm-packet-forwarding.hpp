//
// Created by dev on 6/28/25.
//

#ifndef ASHKANTOOL_MITM_PACKET_FORWARDING_HPP
#define ASHKANTOOL_MITM_PACKET_FORWARDING_HPP

#include "PcapLiveDevice.h"
#include "PcapLiveDeviceList.h"

#include "core/task/task.hpp"
#include "core/packet-receiver/packet-receiver.hpp"
#include "core/capture-wrapper.hpp"

namespace ashk::tasks {
class MITMPacketForwarding : public Task {
 public:
  explicit MITMPacketForwarding(pcpp::IPv4Address iface_ip,
                                pcpp::IPv4Address victim_ip,
                                pcpp::IPv4Address gateway_ip,
                                pcpp::MacAddress victim_mac,
                                pcpp::MacAddress gateway_mac,
                                int last_task_id);
  std::string GetData(tasks_data_id data_id) override;
 private:
  void Exec_() override;
  pcpp::PcapLiveDevice *dev_ = nullptr;
  pcpp::IPv4Address iface_ip_;
  pcpp::IPv4Address victim_ip_;
  pcpp::IPv4Address gateway_ip_;
  pcpp::MacAddress victim_mac_;
  pcpp::MacAddress gateway_mac_;
  CaptureWrapper &capture_wrapper_ = CaptureWrapper::getInstance();

};
}

#endif //ASHKANTOOL_MITM_PACKET_FORWARDING_HPP
