//
// Created by dev on 6/4/25.
//

#ifndef ASHKANTOOL_INTERFACE_HPP
#define ASHKANTOOL_INTERFACE_HPP

#include <string>

#include "core/net-core.hpp"

#include "utils/logger.hpp"
#include "core/data-holders/wifi.hpp"

namespace ashk {

class ModelInterface {
 public:
  ModelInterface() = default;

  std::string Arp(const std::string &ip);
  void SendArpReq(const std::string &iface_name, const std::string &ip_str);

  std::string GetInterfaceIp();
  std::vector<pcpp::PcapLiveDevice *> GetInterfaces();
  std::string GetInterfaceNmae();

  void StartArpPoison(const std::string &iface_name, const std::string &vic_src_ip, const std::string &vic_dst_ip,
                      const std::string &forward_to_ip);
  void StartArpPoisonDetection(const std::string &iface_name);
  void StartVlanHopping(const std::string &iface_name, const std::string &outer_str, const std::string &inner_str);
  void StartDtpNegotiation(const std::string &iface_name, const std::string &domain_name);
  void StartDtpDomainExtraction(const std::string &iface_name,std::string &buffer);
  void StartMitmForwarding(const std::string &iface_name,
                           const std::string &victim_ip_str,
                           const std::string &gateway_ip_str,
                           const std::string &victim_mac_str,
                           const std::string &gateway_mac_str);
  int StartDetectingWifiAps(const std::string &iface_name);
  int StartDetectingWifiHosts(const std::string &iface_name);
  void StartSendingDeauthPackets(const std::string &iface_name,
                                 WifiAp* wifi_ap);
  void StartPasswordCracking(const std::string &iface_name, std::shared_ptr<HandShakeData> handshake_data);
  void StartWpa2HandshakeCapturing(const std::string &iface_name,
                                   std::shared_ptr<HandShakeData> handshake_data);

  void AddLoggerMethod(const std::function<void(const std::string &)> &method);
  std::vector<int> GetRunningTasks();
  void EndTask(int id);
  void WaitTasksChange();

  std::string GetTaskData(const std::string &task_id, tasks_data_id data_id);

  [[nodiscard]] utils::SignalVector<WifiAp>& getWifiApList();
  [[nodiscard]] utils::SignalVector<WifiHost>& getWifiHostList();
  [[nodiscard]] const TaskWatcher& taskWatcher() const;
 private:
  NetCore core_;
  utils::Logger &logger_ = utils::Logger::getInstance();

};

}
#endif //ASHKANTOOL_INTERFACE_HPP
