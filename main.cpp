#include "ui/imgui_ui.h"
#include "model/interface.h"
#include <iostream>
int main(int, char**)
{
    ModelInterface system;
    ImguiUi ui(&system);
    return ui.exec();

}
