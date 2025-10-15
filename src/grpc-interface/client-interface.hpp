//
// Created by dev on 10/12/25.
//

#ifndef ASHKANTOOL_CLIENT_INTERFACE_HPP
#define ASHKANTOOL_CLIENT_INTERFACE_HPP

#include <string>

#include <grpcpp/grpcpp.h>
#include "ui-services.grpc.pb.h"

#include "utils/logger.hpp"
#include "core/data-holders/wifi.hpp"

class ClientInterface {
 public:
  ClientInterface(std::string ip);

  std::string Arp(const std::string &ip);
  std::vector<std::string> GetInterfaces();
  void SendArpReq(const std::string &iface_ip_str, const std::string &ip_str);
  void StartArpPoison(const std::string &iface_ip, const std::string &vic_src_ip, const std::string &vic_dst_ip,
                      const std::string &forward_to_ip);
  void StartArpPoisonDetection(const std::string &iface_ip);
  void StartVlanHopping(const std::string &iface_ip_str, const std::string &outer_str, const std::string &inner_str);
  void StartDtpNegotiation(const std::string &iface_ip_str, const std::string &domain_name);
  void StartDtpDomainExtraction(const std::string &iface_ip_str, char buffer[32]);
  void StartMitmForwarding(const std::string &iface_ip_str,
                           const std::string &victim_ip_str,
                           const std::string &gateway_ip_str,
                           const std::string &victim_mac_str,
                           const std::string &gateway_mac_str);
  void StartDetectingWifiAps(const std::string &iface_ip_str, std::vector<WifiAp> &ap_list);
  void StartDetectingWifiHosts(const std::string &iface_ip_name_str,
                               std::vector<std::shared_ptr<WifiHost>> &host_list);
  void StartSendingDeauthPackets(const std::string &iface_ip_name_str,
                                 WifiAp *wifi_ap,
                                 std::vector<std::shared_ptr<WifiHost>> &host_list);
  void StartPasswordCracking(const std::string &iface_ip_name_str, std::shared_ptr<HandShakeData> handshake_data);
  void StartWpa2HandshakeCapturing(const std::string &iface_ip_name_str,
                                   std::shared_ptr<HandShakeData> handshake_data);

  void AddLoggerMethod(const std::function<void(const std::string &)> &method);
  void GetRunningTasks(std::vector<int>& running_tasks);
  void EndTask(int id);

//  std::string GetTaskData(const std::string &task_id, tasks_data_id data_id);


 private:
  std::shared_ptr<grpc::Channel> channel_;
  std::unique_ptr<UiServie::Stub> stub_;


};

#endif  //ASHKANTOOL_CLIENT_INTERFACE_HPP
