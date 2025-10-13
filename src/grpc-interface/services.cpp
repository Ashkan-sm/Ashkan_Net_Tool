//
// Created by dev on 10/12/25.
//

#include "services.hpp"

Services::Services(std::shared_ptr<ashk::ModelInterface> core) : core_(core){

}


grpc::Status Services::Arp(::grpc::ServerContext* context,
                           const ::ArpRequestType* request,
                           ::ArpResponseType* response) {
  std::cout<<"client asked for Arp"<<std::endl;
  core_->Arp(request->ip());
  return grpc::Status::OK;
}
grpc::Status Services::SendArpReq(::grpc::ServerContext* context,
                                  const ::SendArpReqRequestType* request,
                                  ::SendArpReqResponseType* response) {
  std::cout<<"client asked for SendArpReq"<<std::endl;
  core_->SendArpReq(request->iface_ip(),request->ip());
  return grpc::Status::OK;
}
grpc::Status Services::StartArpPoison(
    ::grpc::ServerContext* context, const ::StartArpPoisonRequestType* request,
    ::StartArpPoisonResponseType* response) {

  core_->StartArpPoison(request->iface_ip(),request->vic_src_ip(),request->vic_dst_ip(),request->forward_to_ip());
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
