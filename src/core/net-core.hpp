//
// Created by dev on 6/5/25.
//

#ifndef ASHKANTOOL_NET_CORE_HPP
#define ASHKANTOOL_NET_CORE_HPP

#include <map>

#include "MacAddress.h"
#include "IpAddress.h"
#include "Logger.h"
#include "PcapPlusPlusVersion.h"
#include "PcapLiveDeviceList.h"
#include "PcapLiveDevice.h"
#include "NetworkUtils.h"
#include <getopt.h>
#include "SystemUtils.h"
#include "EthLayer.h"
#include "Packet.h"

#include "utils/logger.hpp"
#include "utils/net-utils.hpp"

#include "core/task/task.hpp"
#include "core/task/tasks/arp/arp-poisoning-task.hpp"
#include "core/task/tasks/arp/arp-poison-detection-task.hpp"
#include "core/task/tasks/vlan/vlan-hopping-task.hpp"
#include "core/task/tasks/dtp/dtp-negotiation.hpp"
#include "core/task/tasks/man-in-the-middle/mitm-packet-forwarding.hpp"
#include "core/task/tasks/dtp/dtp-domain-extraction-task.hpp"
#include "core/task/tasks/wireless/wifi-ap-scanning-task.hpp"
#include "core/task/tasks/wireless/wifi-host-scanning-task.hpp"
#include "core/task/tasks/wireless/deauth-packet-sending.hpp"
#include "core/task/tasks/wireless/wpa-2-hand-shake-capture-task.hpp"
#include "core/task/tasks/wireless/wifi-password-cracking-task.hpp"

#include "core/data-holders/wifi.hpp"
#include "core/packet-receiver/packet-receiver.hpp"
#include "core/capture-wrapper.hpp"

namespace ashk {
class NetCore {
 public:
  friend class ModelInterface;
  NetCore();

 private:
  pcpp::MacAddress Arp(pcpp::IPv4Address ip);
  void SendArpReq(pcpp::IPv4Address iface_ip, pcpp::IPv4Address ip);
  int DiscoverInterface();
  std::vector<pcpp::PcapLiveDevice *> DiscoverInterfaces();

  pcpp::IPv4Address InterfaceIp();
  std::string InterfaceName();

  void StartArpPoisoning(pcpp::IPv4Address iface_ip, pcpp::IPv4Address vic_src_ip, pcpp::IPv4Address vic_dst_ip,
                         pcpp::IPv4Address forward_to_ip);
  void StartArpPoisonDetection(pcpp::IPv4Address iface_ip);
  void StartMitmForwarding(pcpp::IPv4Address iface_ip,
                           pcpp::IPv4Address victim_ip,
                           pcpp::IPv4Address gateway_ip,
                           pcpp::MacAddress victim_mac,
                           pcpp::MacAddress gateway_mac);
  void StartVlanHopping(pcpp::IPv4Address iface_ip, int outer_id, int inner_id);
  void StartDtpNegotiation(pcpp::IPv4Address iface_ip, const std::string &domain_name);
  void StartDtpDomainExtraction(pcpp::IPv4Address iface_ip, char *buffer);
  void StartDetectingWifiAps(std::string iface_name_or_ip, std::vector<WifiAp> &ap_list);
  void StartDetectingWifiHosts(const std::string &iface_ip_name_str,
                               std::vector<std::shared_ptr<WifiHost>> &host_list);
  void StartSendingDeauthPackets(const std::string &iface_ip_name_str,
                                 WifiAp *wifi_ap,
                                 std::vector<std::shared_ptr<WifiHost>> &host_list);
  void StartPasswordCracking(const std::string &iface_ip_name_str, std::shared_ptr<HandShakeData> handshake_data);
  void StartWpa2HandshakeCapturing(const std::string &iface_ip_name_str,
                                   std::shared_ptr<HandShakeData> handshake_data);

  void AddLoggerMethod(const std::function<void(const std::string &)> &method);
  void EndTask(int id);

  std::vector<int> GetRunningTasks();

  pcpp::PcapLiveDevice *dev_ = nullptr;
  utils::Logger &logger_ = utils::Logger::getInstance();
  CaptureWrapper &capture_wrapper_ = CaptureWrapper::getInstance();
  std::map<int, std::shared_ptr<Task>> tasks_;
  int last_added_task_id_ = 0;
};
}

#endif //ASHKANTOOL_NET_CORE_HPP
