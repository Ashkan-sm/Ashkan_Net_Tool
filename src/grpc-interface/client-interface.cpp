//
// Created by dev on 10/12/25.
//

#include "client-interface.hpp"

ClientInterface::ClientInterface(std::string ip) {
  channel_ = grpc::CreateChannel(ip, grpc::InsecureChannelCredentials());
  stub_=UiServie::NewStub(channel_);

}
std::string ClientInterface::Arp(const std::string& ip) {

  ArpRequestType request;
  ArpResponseType response;
  grpc::ClientContext context;
  grpc::Status status = stub_->Arp(&context, request, &response);
  if (status.ok()) {
    return response.ip();
  }

  std::cerr << "RPC failed: " << status.error_message() << std::endl;
  return std::string();
}
void ClientInterface::SendArpReq(const std::string& iface_ip_str,
                                 const std::string& ip_str) {
  SendArpReqRequestType request;
  SendArpReqResponseType response;
  grpc::ClientContext context;
  grpc::Status status = stub_->SendArpReq(&context, request, &response);
  if (status.ok()) {
    std::cout<<"sent arp"<<std::endl;
    return;
  }

  std::cerr << "RPC failed: " << status.error_message() << std::endl;
  return;


}
void ClientInterface::StartArpPoison(const std::string& iface_ip,
                                     const std::string& vic_src_ip,
                                     const std::string& vic_dst_ip,
                                     const std::string& forward_to_ip) {}
void ClientInterface::StartArpPoisonDetection(const std::string& iface_ip) {}
void ClientInterface::StartVlanHopping(const std::string& iface_ip_str,
                                       const std::string& outer_str,
                                       const std::string& inner_str) {}
void ClientInterface::StartDtpNegotiation(const std::string& iface_ip_str,
                                          const std::string& domain_name) {}
void ClientInterface::StartDtpDomainExtraction(const std::string& iface_ip_str,
                                               char* buffer) {}
void ClientInterface::StartDetectingWifiAps(const std::string& iface_ip_str,
                                            std::vector<WifiAp>& ap_list) {}
void ClientInterface::StartMitmForwarding(const std::string& iface_ip_str,
                                          const std::string& victim_ip_str,
                                          const std::string& gateway_ip_str,
                                          const std::string& victim_mac_str,
                                          const std::string& gateway_mac_str) {}
void ClientInterface::StartDetectingWifiHosts(
    const std::string& iface_ip_name_str,
    std::vector<std::shared_ptr<WifiHost>>& host_list) {}
void ClientInterface::StartSendingDeauthPackets(
    const std::string& iface_ip_name_str, WifiAp* wifi_ap,
    std::vector<std::shared_ptr<WifiHost>>& host_list) {}
void ClientInterface::StartPasswordCracking(
    const std::string& iface_ip_name_str,
    std::shared_ptr<HandShakeData> handshake_data) {}
void ClientInterface::StartWpa2HandshakeCapturing(
    const std::string& iface_ip_name_str,
    std::shared_ptr<HandShakeData> handshake_data) {}
void ClientInterface::AddLoggerMethod(
    const std::function<void(const std::string&)>& method) {}
std::vector<int> ClientInterface::GetRunningTasks() {
  return std::vector<int>();
}
void ClientInterface::EndTask(int id) {}
std::vector<std::string> ClientInterface::GetInterfaces() {
  GetInterfacesRequestType request;
  GetInterfacesResponseType response;
  grpc::ClientContext context;
  grpc::Status status = stub_->GetInterfaces(&context, request, &response);
  if (status.ok()) {
    std::vector<std::string> device_names;
    for (int i = 0;i<response.devices_names_size();i++){
      device_names.push_back(response.devices_names(i));
    }
    return device_names;
  }

  std::cerr << "RPC failed: " << status.error_message() << std::endl;
  return std::vector<std::string>();
}
