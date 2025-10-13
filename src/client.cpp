//
// Created by dev on 10/12/25.
//
#include "grpc-interface/client-interface.hpp"
#include "ui/imgui-ui.hpp"

int main(int, char **) {

  ClientInterface grpc_interface("localhost:5000");
  ImguiUi ui(&grpc_interface);
  return ui.Exec();

}
