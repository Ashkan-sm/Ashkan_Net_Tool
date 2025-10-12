//
// Created by dev on 10/12/25.
//

#include "server-interface.hpp"
ServerInterface::ServerInterface(std::shared_ptr<ashk::ModelInterface> core,
                                 std::string server_address) :
                                                               core_(core),
                                                               server_address_(server_address){
  service_=std::make_shared<Services>(core_);
  builder_=std::make_shared<grpc::ServerBuilder>();

}
int ServerInterface::Exec() {
  builder_->AddListeningPort(server_address_, grpc::InsecureServerCredentials());
  builder_->RegisterService(service_.get());

  std::unique_ptr<grpc::Server> server(builder_->BuildAndStart());
  std::cout << "Server listening on " << server_address_ << std::endl;
  server->Wait();

  return 0;
}

