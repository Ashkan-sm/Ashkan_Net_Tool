//
// Created by dev on 6/4/25.
//

#include "interface.hpp"

#include <utility>

std::string ashk::ModelInterface::GetInterfaceIp() {
  return core_.InterfaceIp().toString();
}
std::vector<pcpp::PcapLiveDevice *> ashk::ModelInterface::GetInterfaces() {
  return core_.DiscoverInterfaces();
}

std::string ashk::ModelInterface::Arp(const std::string &ip) {
  return core_.Arp(pcpp::IPv4Address(ip)).toString();
}

void ashk::ModelInterface::StartArpPoison(const std::string &iface_ip,
                                          const std::string &vic_src_ip,
                                          const std::string &vic_dst_ip,
                                          const std::string &forward_to_ip) {
  pcpp::IPv4Address iface;
  pcpp::IPv4Address vic_src;
  pcpp::IPv4Address vic_dst;
  pcpp::IPv4Address forward_to;

  try {
    iface = pcpp::IPv4Address(iface_ip);
    vic_src = pcpp::IPv4Address(vic_src_ip);
    vic_dst = pcpp::IPv4Address(vic_dst_ip);
    forward_to = pcpp::IPv4Address(forward_to_ip);

  }
  catch (const std::exception &) {
    logger_.Log("invalid ip inputs\n");
    return;
  }

  core_.StartArpPoisoning(iface, vic_src, vic_dst, forward_to);

}

void ashk::ModelInterface::AddLoggerMethod(const std::function<void(const std::string &)> &method) {
  logger_.AddLogMethod(method);
}

std::vector<int> ashk::ModelInterface::GetRunningTasks() {
  return core_.GetRunningTasks();
}

void ashk::ModelInterface::EndTask(int id) {
  core_.EndTask(id);
}

void ashk::ModelInterface::StartArpPoisonDetection(const std::string &iface_ip) {
  pcpp::IPv4Address iface;

  try {
    iface = pcpp::IPv4Address(iface_ip);

  }
  catch (const std::exception &) {
    logger_.Log("invalid ip inputs\n");
    return;
  }
  core_.StartArpPoisonDetection(iface_ip);

}

void ashk::ModelInterface::SendArpReq(const std::string &iface_ip_str, const std::string &ip_str) {
  pcpp::IPv4Address iface;
  pcpp::IPv4Address ip;

  try {
    iface = pcpp::IPv4Address(iface_ip_str);
    ip = pcpp::IPv4Address(ip_str);

  }
  catch (const std::exception &) {
    logger_.Log("invalid ip inputs\n");
    return;
  }
  core_.SendArpReq(iface, ip);
}
void ashk::ModelInterface::StartMitmForwarding(const std::string &iface_ip_str,
                                               const std::string &victim_ip_str,
                                               const std::string &gateway_ip_str,
                                               const std::string &victim_mac_str,
                                               const std::string &gateway_mac_str) {
  pcpp::IPv4Address iface;
  pcpp::MacAddress victim_mac;
  pcpp::MacAddress gateway_mac;
  pcpp::IPv4Address victim_ip;
  pcpp::IPv4Address gateway_ip;
  try {
    iface = pcpp::IPv4Address(iface_ip_str);
    victim_mac = pcpp::MacAddress(victim_mac_str);
    gateway_mac = pcpp::MacAddress(gateway_mac_str);
    victim_ip = pcpp::IPv4Address(victim_ip_str);
    gateway_ip = pcpp::IPv4Address(gateway_ip_str);
  }
  catch (const std::exception &) {
    logger_.Log("invalid ip inputs\n");
    return;
  }
  core_.StartMitmForwarding(iface, victim_ip, gateway_ip, victim_mac, gateway_mac);
}

void ashk::ModelInterface::StartVlanHopping(const std::string &iface_ip_str,
                                            const std::string &outer_str,
                                            const std::string &inner_str) {
  pcpp::IPv4Address iface;
  int outer_tag = 0;
  int inner_tag = 0;
  try {
    iface = pcpp::IPv4Address(iface_ip_str);
    if (!outer_str.empty()) {
      outer_tag = std::stoi(outer_str);
    }
    if (!inner_str.empty()) {
      inner_tag = std::stoi(inner_str);
    }

  }
  catch (const std::exception &) {
    logger_.Log("invalid inputs\n");
    return;
  }
  core_.StartVlanHopping(iface, outer_tag, inner_tag);
}

void ashk::ModelInterface::StartDtpNegotiation(const std::string &iface_ip_str, const std::string &domain_name) {
  pcpp::IPv4Address iface;
  try {
    iface = pcpp::IPv4Address(iface_ip_str);
  }
  catch (const std::exception &) {
    logger_.Log("invalid inputs\n");
    return;
  }
  core_.StartDtpNegotiation(iface, domain_name);

}

void ashk::ModelInterface::StartDtpDomainExtraction(const std::string &iface_ip_str, char buffer[32]) {
  pcpp::IPv4Address iface;
  try {
    iface = pcpp::IPv4Address(iface_ip_str);
  }
  catch (const std::exception &) {
    logger_.Log("invalid inputs\n");
    return;
  }
  core_.StartDtpDomainExtraction(iface, buffer);
}

std::string ashk::ModelInterface::GetTaskData(const std::string &task_id, tasks_data_id data_id) {
  int task_id_int = 0;
  try {
    task_id_int = std::stoi(task_id);
  } catch (const std::exception &) {
    logger_.Log("invalid inputs\n");
    return "";
  }
  if (!core_.Tasks().count(task_id_int))
    return "";
  return core_.Tasks()[task_id_int]->GetData(data_id);
}

void ashk::ModelInterface::StartDetectingWifiAps(const std::string &iface_ip_str, std::vector<WifiAp> &ap_list) {

  core_.StartDetectingWifiAps(iface_ip_str, ap_list);

}

void ashk::ModelInterface::StartDetectingWifiHosts(const std::string &iface_ip_name_str,
                                                   std::vector<std::shared_ptr<WifiHost>> &host_list) {
  core_.StartDetectingWifiHosts(iface_ip_name_str, host_list);
}

std::string ashk::ModelInterface::GetInterfaceNmae() {
  return core_.InterfaceName();
}

void ashk::ModelInterface::StartSendingDeauthPackets(const std::string &iface_ip_name_str,
                                                     WifiAp *wifi_ap,
                                                     std::vector<std::shared_ptr<WifiHost>> &host_list) {
  core_.StartSendingDeauthPackets(iface_ip_name_str, wifi_ap, host_list);
}

void ashk::ModelInterface::StartPasswordCracking(const std::string &iface_ip_name_str,
                                                 std::shared_ptr<HandShakeData> handshake_data) {
  core_.StartPasswordCracking(iface_ip_name_str, std::move(handshake_data));
}

void ashk::ModelInterface::StartWpa2HandshakeCapturing(const std::string &iface_ip_name_str,
                                                       std::shared_ptr<HandShakeData> handshake_data) {
  core_.StartWpa2HandshakeCapturing(iface_ip_name_str, std::move(handshake_data));
}


