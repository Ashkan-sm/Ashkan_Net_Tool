//
// Created by dev on 6/4/25.
//

#ifndef ASHKANTOOL_MAIN_WINDOW_H
#define ASHKANTOOL_MAIN_WINDOW_H

#include "imgui_headers.h"
#include "config.h"
#include "sub_window.h"
#include <memory>
#include "../../model/interface.h"

enum class SelectedWindow{
    defualt,
    arp_spoofing,
};

class MainWindow{
public:
    MainWindow(ModelInterface *core);
    void draw();

private:
    ModelInterface *core_;
    std::shared_ptr<ISubWindow> default_window;
    std::shared_ptr<ISubWindow> arp_spoof_window;

    void draw_main_toolbar();
    void draw_log_window();
    std::shared_ptr<ISubWindow> sub_window_;

    char log_buffer_[1024]="";

};
#endif //ASHKANTOOL_MAIN_WINDOW_H
