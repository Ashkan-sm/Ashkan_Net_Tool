//
// Created by dev on 10/12/25.
//

#ifndef ASHKANTOOL_SERVER_INTERFACE_HPP
#define ASHKANTOOL_SERVER_INTERFACE_HPP

#include <grpcpp/grpcpp.h>

#include "core/interface.hpp"
#include "services.hpp"

#include <memory>
class ServerInterface {
 public:
  ServerInterface(std::shared_ptr<ashk::ModelInterface> core,
                  std::string server_address);
  int Exec();
 private:
  std::shared_ptr<ashk::ModelInterface> core_;
  std::string server_address_;
  std::shared_ptr<Services> service_;
  std::shared_ptr<grpc::ServerBuilder> builder_;
};

#endif  //ASHKANTOOL_SERVER_INTERFACE_HPP
