//
// Created by dev on 10/12/25.
//
#include "grpc-interface/server-interface.hpp"
#include "core/interface.hpp"

#include <fstream>
#include <string>

int main(int, char **) {

  auto system=std::make_shared<ashk::ModelInterface>();
  system->AddLoggerMethod([](std::string a){std::cout << a << std::endl;});
  ServerInterface server_interface(system,"0.0.0.0:5000");
  return server_interface.Exec();

}
