#include "ui/imgui-ui.hpp"
#include "core/interface.hpp"

#include <fstream>
#include <string>

int main(int, char **) {

  ashk::ModelInterface system;
  ImguiUi ui(&system);
  return ui.exec();

}
