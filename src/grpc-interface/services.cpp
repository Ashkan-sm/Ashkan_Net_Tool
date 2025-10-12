//
// Created by dev on 10/12/25.
//

#include "services.hpp"

Services::Services(std::shared_ptr<ashk::ModelInterface> core) : core_(core){

}

grpc::Status Services::Arp(::grpc::ClientContext* context,
                           const ArpRequestType& request,
                           ::ArpResponseType* response) {
  core_->Arp(request.ip());
  return grpc::Status::OK;
}
grpc::Status Services::SendArpReq(::grpc::ServerContext* context,
                                  const ::SendArpReqRequestType* request,
                                  ::SendArpReqResponseType* response) {

  core_->SendArpReq(request->iface_ip(),request->ip());
  return grpc::Status::OK;
}
grpc::Status Services::StartArpPoison(
    ::grpc::ServerContext* context, const ::StartArpPoisonRequestType* request,
    ::StartArpPoisonResponseType* response) {

  core_->StartArpPoison(request->iface_ip(),request->vic_src_ip(),request->vic_dst_ip(),request->forward_to_ip());
  return grpc::Status::OK;
}
