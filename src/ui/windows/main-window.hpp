//
// Created by dev on 6/4/25.
//

#ifndef ASHKANTOOL_MAIN_WINDOW_HPP
#define ASHKANTOOL_MAIN_WINDOW_HPP

#include <memory>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "config.h"
#include "sub-window.hpp"

#include "core/interface.hpp"

enum class SelectedWindow{
    defualt,
    arp_spoofing,
};

class MainWindow{
public:
    MainWindow(ashk::ModelInterface *core);
    void draw();

private:
    ashk::ModelInterface *core_;
    std::shared_ptr<ISubWindow> default_window;
    std::shared_ptr<ISubWindow> arp_spoof_window;
    std::shared_ptr<ISubWindow> arp_poison_detection_window;
    std::shared_ptr<ISubWindow> send_arp_request_window;
    std::shared_ptr<ISubWindow> vlan_hopping_window;
    std::shared_ptr<ISubWindow> man_in_the_middle_window;
    std::shared_ptr<ISubWindow> wifi_attack_window;

    void draw_main_toolbar();
    void draw_log_window();
    std::shared_ptr<ISubWindow> sub_window_;

    char log_buffer_[1024]="";

};
#endif //ASHKANTOOL_MAIN_WINDOW_HPP
