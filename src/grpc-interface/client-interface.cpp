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

  request.set_ip(ip);

  grpc::ClientContext context;
  grpc::Status status = stub_->Arp(&context, request, &response);
  if (status.ok()) {
    return response.ip();
  }

  std::cerr << "RPC failed: " << status.error_message() << std::endl;
  return std::string();
}
void ClientInterface::SendArpReq(const std::string& iface_name,
                                 const std::string& ip_str) {
  SendArpReqRequestType request;
  SendArpReqResponseType response;

  request.set_iface_name(iface_name);
  request.set_ip(ip_str);

  grpc::ClientContext context;
  grpc::Status status = stub_->SendArpReq(&context, request, &response);
  if (status.ok()) {
    std::cout<<"sent arp"<<std::endl;
    return;
  }

  std::cerr << "RPC failed: " << status.error_message() << std::endl;
  return;


}
void ClientInterface::StartArpPoison(const std::string& iface_name,
                                     const std::string& vic_src_ip,
                                     const std::string& vic_dst_ip,
                                     const std::string& forward_to_ip) {
  StartArpPoisonRequestType request;
  StartArpPoisonResponseType response;
  
  request.set_iface_name(iface_name);
  request.set_vic_src_ip(vic_src_ip);
  request.set_vic_dst_ip(vic_dst_ip);
  request.set_forward_to_ip(forward_to_ip);
  
  grpc::ClientContext context;
  grpc::Status status = stub_->StartArpPoison(&context, request, &response);
  if (status.ok()) {
    return;
  }
  std::cerr << "RPC failed: " << status.error_message() << std::endl;

}
void ClientInterface::StartArpPoisonDetection(const std::string& iface_name) {
  StartArpPoisonDetectionRequestType request;
  StartArpPoisonDetectionResponseType response;
  
  request.set_iface_name(iface_name);
  
  grpc::ClientContext context;
  grpc::Status status = stub_->StartArpPoisonDetection(&context, request, &response);
  if (status.ok()) {
    return;
  }
  std::cerr << "RPC failed: " << status.error_message() << std::endl;

}
void ClientInterface::StartVlanHopping(const std::string& iface_name,
                                       const std::string& outer_str,
                                       const std::string& inner_str) {
  StartVlanHoppingRequestType request;
  StartVlanHoppingResponseType response;

  request.set_iface_name(iface_name);
  request.set_outer_str(outer_str);
  request.set_inner_str(inner_str);

  grpc::ClientContext context;
  grpc::Status status = stub_->StartVlanHopping(&context, request, &response);
  if (status.ok()) {
    return;
  }
  std::cerr << "RPC failed: " << status.error_message() << std::endl;
}
void ClientInterface::StartDtpNegotiation(const std::string& iface_name,
                                          const std::string& domain_name) {
  StartDtpNegotiationRequestType request;
  StartDtpNegotiationResponseType response;

  request.set_iface_name(iface_name);
  request.set_domain_name(domain_name);

  grpc::ClientContext context;
  grpc::Status status = stub_->StartDtpNegotiation(&context, request, &response);
  if (status.ok()) {
    return;
  }
  std::cerr << "RPC failed: " << status.error_message() << std::endl;
}
void ClientInterface::StartDtpDomainExtraction(const std::string& iface_name,
                                               char* buffer) {
  std::thread a([=](){
    StartDtpDomainExtractionRequestType request;
    StartDtpDomainExtractionResponseType response;

    request.set_iface_name(iface_name);

    grpc::ClientContext context;
    grpc::Status status = stub_->StartDtpDomainExtraction(&context, request, &response);
    if (status.ok()) {

      memcpy(buffer,response.domain_name().c_str(),(response.domain_name().size() <= 32) ? response.domain_name().size() : 32);
    }
    else {
      std::cerr << "RPC failed: " << status.error_message() << std::endl;
    }
  });
  a.detach();

}
void ClientInterface::StartDetectingWifiAps(const std::string& iface_name,
                                            std::vector<WifiAp>& ap_list) {
  std::thread a([&](){
    StartDetectingWifiApsRequestType request;
    StartDetectingWifiApsResponseType response;

    request.set_iface_name(iface_name);

    grpc::ClientContext context;
    grpc::Status status =
        stub_->StartDetectingWifiAps(&context, request, &response);
    if (status.ok()) {

    }
    else {
      std::cerr << "RPC failed: " << status.error_message() << std::endl;
    }
  });
  a.detach();
}
void ClientInterface::StartMitmForwarding(const std::string& iface_name,
                                          const std::string& victim_ip_str,
                                          const std::string& gateway_ip_str,
                                          const std::string& victim_mac_str,
                                          const std::string& gateway_mac_str) {
  StartMitmForwardingRequestType request;
  StartMitmForwardingResponseType response;
  grpc::ClientContext context;
  grpc::Status status = stub_->StartMitmForwarding(&context, request, &response);
  if (status.ok()) {
    return;
  }
  std::cerr << "RPC failed: " << status.error_message() << std::endl;
}
void ClientInterface::StartDetectingWifiHosts(
    const std::string& iface_name,
    std::vector<std::shared_ptr<WifiHost>>& host_list) {
  StartDetectingWifiHostsRequestType request;
  StartDetectingWifiHostsResponseType response;
  grpc::ClientContext context;
  grpc::Status status = stub_->StartDetectingWifiHosts(&context, request, &response);
  if (status.ok()) {
    return;
  }
  std::cerr << "RPC failed: " << status.error_message() << std::endl;
}
void ClientInterface::StartSendingDeauthPackets(
    const std::string& iface_name_name_str, WifiAp* wifi_ap,
    std::vector<std::shared_ptr<WifiHost>>& host_list) {
  StartSendingDeauthPacketsRequestType request;
  StartSendingDeauthPacketsResponseType response;
  grpc::ClientContext context;
  grpc::Status status = stub_->StartSendingDeauthPackets(&context, request, &response);
  if (status.ok()) {
    return;
  }
  std::cerr << "RPC failed: " << status.error_message() << std::endl;
}
void ClientInterface::StartPasswordCracking(
    const std::string& iface_name_name_str,
    std::shared_ptr<HandShakeData> handshake_data) {
  StartPasswordCrackingRequestType request;
  StartPasswordCrackingResponseType response;
  grpc::ClientContext context;
  grpc::Status status = stub_->StartPasswordCracking(&context, request, &response);
  if (status.ok()) {
    return;
  }
  std::cerr << "RPC failed: " << status.error_message() << std::endl;
}
void ClientInterface::StartWpa2HandshakeCapturing(
    const std::string& iface_name_name_str,
    std::shared_ptr<HandShakeData> handshake_data) {
  StartWpa2HandshakeCapturingRequestType request;
  StartWpa2HandshakeCapturingResponseType response;
  grpc::ClientContext context;
  grpc::Status status = stub_->StartWpa2HandshakeCapturing(&context, request, &response);
  if (status.ok()) {
    return;
  }
  std::cerr << "RPC failed: " << status.error_message() << std::endl;
}
void ClientInterface::AddLoggerMethod(
    const std::function<void(const std::string&)>& method) {

}
void ClientInterface::GetRunningTasks(std::vector<int>& running_tasks) {
  std::thread a([&](){
    GetRunningTasksRequestType request;
    grpc::ClientContext context;
    std::unique_ptr<grpc::ClientReader<GetRunningTasksResponseType>> reader(stub_->GetRunningTasks(&context, request));
    GetRunningTasksResponseType response;
    while (reader->Read(&response)) {
      running_tasks.clear();
      for (auto& i : response.task_ids()) running_tasks.push_back(i);
    }});
  a.detach();
}

void ClientInterface::EndTask(int id) {
  EndTaskRequestType request;
  EndTaskResponseType response;
  grpc::ClientContext context;
  request.set_id(id);
  grpc::Status status = stub_->EndTask(&context, request, &response);
  if (status.ok()) {
    return;
  }
  std::cerr << "RPC failed: " << status.error_message() << std::endl;
}
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

void ClientInterface::ReadLogsFromServer() {
  std::thread a([&](){
    ReadLogsRequestType request;
    grpc::ClientContext context;
    std::unique_ptr<grpc::ClientReader<ReadLogsResponseType>> reader(stub_->ReadLogs(&context, request));
    ReadLogsResponseType response;
    while (reader->Read(&response)) {
      ashk::utils::Logger::getInstance().Log(response.log());
    }});
  a.detach();
}

