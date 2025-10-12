//
// Created by dev on 10/12/25.
//

#ifndef ASHKANTOOL_SERVICES_HPP
#define ASHKANTOOL_SERVICES_HPP

#include "ui-services.grpc.pb.h"
#include "core/interface.hpp"

class Services final : public UiServie::Service {
 public:
  Services(std::shared_ptr<ashk::ModelInterface> core);
  grpc::Status Arp(::grpc::ClientContext* context, const ::ArpRequestType& request, ::ArpResponseType* response);
  grpc::Status SendArpReq(::grpc::ServerContext* context,
                          const ::SendArpReqRequestType* request,
                          ::SendArpReqResponseType* response) override;

  grpc::Status StartArpPoison(::grpc::ServerContext* context,
                              const ::StartArpPoisonRequestType* request,
                              ::StartArpPoisonResponseType* response) override;

 private:
  std::shared_ptr<ashk::ModelInterface> core_;

};

#endif  //ASHKANTOOL_SERVICES_HPP
