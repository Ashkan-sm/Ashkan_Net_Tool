//
// Created by dev on 10/12/25.
//

#include "services.hpp"

#include <utility>

Services::Services(std::shared_ptr<ashk::ModelInterface> core) : core_(std::move(core)){

}

grpc::Status Services::Arp(::grpc::ServerContext* context,
                           const ::ArpRequestType* request,
                           ::ArpResponseType* response) {
  core_->Arp(request->ip());
  return grpc::Status::OK;
}
grpc::Status Services::SendArpReq(::grpc::ServerContext* context,
                                  const ::SendArpReqRequestType* request,
                                  ::SendArpReqResponseType* response) {
  core_->SendArpReq(request->iface_name(),request->ip());
  return grpc::Status::OK;
}
grpc::Status Services::StartArpPoison(
    ::grpc::ServerContext* context, const ::StartArpPoisonRequestType* request,
    ::StartArpPoisonResponseType* response) {

  core_->StartArpPoison(request->iface_name(),request->vic_src_ip(),request->vic_dst_ip(),request->forward_to_ip());
  return grpc::Status::OK;
}
grpc::Status Services::GetInterfaces(::grpc::ServerContext* context,
                                     const ::GetInterfacesRequestType* request,
                                     ::GetInterfacesResponseType* response) {
  auto devices=core_->GetInterfaces();

  for(auto i:devices){
    response->add_devices_names(i->getName());
  }

  return grpc::Status::OK;
}
grpc::Status Services::StartArpPoisonDetection(
    ::grpc::ServerContext* context,
    const ::StartArpPoisonDetectionRequestType* request,
    ::StartArpPoisonDetectionResponseType* response) {
  core_->StartArpPoisonDetection(request->iface_name());
  return grpc::Status::OK;
}
grpc::Status Services::StartVlanHopping(
    ::grpc::ServerContext* context,
    const ::StartVlanHoppingRequestType* request,
    ::StartVlanHoppingResponseType* response) {
  core_->StartVlanHopping(request->iface_name(),request->outer_str(),request->inner_str());
  return grpc::Status::OK;
}
grpc::Status Services::StartDtpNegotiation(
    ::grpc::ServerContext* context,
    const ::StartDtpNegotiationRequestType* request,
    ::StartDtpNegotiationResponseType* response) {
  core_->StartDtpNegotiation(request->iface_name(),request->domain_name());
  return grpc::Status::OK;
}
grpc::Status Services::StartDtpDomainExtraction(
    ::grpc::ServerContext* context,
    const ::StartDtpDomainExtractionRequestType* request,
    ::StartDtpDomainExtractionResponseType* response) {

  std::string buffer="EMPTY";
  core_->StartDtpDomainExtraction(request->iface_name(),buffer);
  while (!context->IsCancelled() && buffer=="EMPTY"){
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  response->set_domain_name(buffer);
  return grpc::Status::OK;
}
grpc::Status Services::StartMitmForwarding(
    ::grpc::ServerContext* context,
    const ::StartMitmForwardingRequestType* request,
    ::StartMitmForwardingResponseType* response) {
  core_->StartMitmForwarding(request->iface_name(),request->victim_ip(),request->gateway_ip(),request->victim_mac(),request->gateway_mac());
  return grpc::Status::OK;
}

grpc::Status Services::StartDetectingWifiHosts(
    ::grpc::ServerContext* context,
    const ::StartDetectingWifiHostsRequestType* request,
    ::StartDetectingWifiHostsResponseType* response) {
  // to be done
  return grpc::Status::OK;
}
grpc::Status Services::StartSendingDeauthPackets(
    ::grpc::ServerContext* context,
    const ::StartSendingDeauthPacketsRequestType* request,
    ::StartSendingDeauthPacketsResponseType* response) {
//  core_->StartSendingDeauthPackets(request->iface_name(),request->wifi_ap(),request,)
// to do
  return grpc::Status::OK;
}
grpc::Status Services::StartPasswordCracking(
    ::grpc::ServerContext* context,
    const ::StartPasswordCrackingRequestType* request,
    ::StartPasswordCrackingResponseType* response) {
//  core_->StartPasswordCracking(request->iface_name(),request->handshake_data())
  return grpc::Status::OK;
}
grpc::Status Services::StartWpa2HandshakeCapturing(
    ::grpc::ServerContext* context,
    const ::StartWpa2HandshakeCapturingRequestType* request,
    ::StartWpa2HandshakeCapturingResponseType* response) {
//  core_->StartWpa2HandshakeCapturing(request->iface_name());
  return grpc::Status::OK;
}

grpc::Status Services::EndTask(::grpc::ServerContext* context,
                               const ::EndTaskRequestType* request,
                               ::EndTaskResponseType* response) {
  core_->EndTask(request->id());
  return grpc::Status::OK;
}
grpc::Status Services::GetRunningTasks(
    ::grpc::ServerContext* context, const ::GetRunningTasksRequestType* request,
    ::grpc::ServerWriter<::GetRunningTasksResponseType>* writer) {


  while(!context->IsCancelled()){
    GetRunningTasksResponseType tasks;
    for (auto i:core_->GetRunningTasks()){
      tasks.add_task_ids(i);
    }
    writer->Write(tasks);
    core_->WaitTasksChange();

  }

  return grpc::Status::OK;
}
grpc::Status Services::ReadLogs(
    ::grpc::ServerContext* context, const ::ReadLogsRequestType* request,
    ::grpc::ServerWriter<::ReadLogsResponseType>* writer) {
  core_->AddLoggerMethod([=](std::string a){
    ReadLogsResponseType response;
    response.set_log(a);
    writer->Write(response);});

  while (!context->IsCancelled()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  return grpc::Status::OK;
}
grpc::Status Services::StartDetectingWifiAps(
    ::grpc::ServerContext* context,
    const ::StartDetectingWifiApsRequestType* request,
    ::grpc::ServerWriter<::StartDetectingWifiApsResponseType>* writer) {

  while(!context->IsCancelled()) {
    StartDetectingWifiApsResponseType Aps;
    for (auto i : core_->getWifiApList()) {
      Aps.add_ap_list(i->e_ssid);
    }
    writer->Write(Aps);
    core_->getWifiApList().WaitChange();

  }
  return grpc::Status::OK;
}
