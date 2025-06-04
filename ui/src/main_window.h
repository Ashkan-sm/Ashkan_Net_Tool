//
// Created by dev on 6/4/25.
//

#ifndef ASHKANTOOL_MAIN_WINDOW_H
#define ASHKANTOOL_MAIN_WINDOW_H

#include "imgui_headers.h"
#include "config.h"
enum class SelectedWindow{
    defualt,
    arp_spoofing,
};

class MainWindow{
public:
    static void main_window();

private:
    static void main_toolbar();


    SelectedWindow selected_window_=SelectedWindow::defualt;
};
#endif //ASHKANTOOL_MAIN_WINDOW_H
