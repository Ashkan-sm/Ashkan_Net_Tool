#include "ui/imgui-ui.hpp"
#include "core/interface.hpp"
#include <iostream>
int main(int, char**)
{
    ashk::ModelInterface system;
    ImguiUi ui(&system);
    return ui.exec();

}
