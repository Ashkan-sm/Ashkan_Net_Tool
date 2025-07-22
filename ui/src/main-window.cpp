#include "main-window.hpp"
MainWindow::MainWindow(ashk::ModelInterface *core) :core_(core){
//    std::memcpy(log_buffer_,0,sizeof(log_buffer_));
    ImGuiIO& io = ImGui::GetIO();


    default_window=std::make_shared<DefaultWindow>(core_);
    arp_spoof_window=std::make_shared<ArpSpoofWindow>(core_);
    arp_poison_detection_window=std::make_shared<ArpPoisonDetectionWindow>(core_);
    send_arp_request_window=std::make_shared<SendArpRequestWindow>(core_);
    vlan_hopping_window=std::make_shared<VlanHoppingWindow>(core_);
    man_in_the_middle_window=std::make_shared<MITMWindow>(core_);
    wifi_attack_window=std::make_shared<WIFIAttackWindow>(core_);

    sub_window_=default_window;

    core_->add_logger_method([&](const std::string &a){
        if(strlen(log_buffer_)+ strlen(log_buffer_) >= sizeof(log_buffer_)){
            memset(log_buffer_,'\0',sizeof(log_buffer_));
        }
        memcpy(log_buffer_+ strlen(log_buffer_),a.c_str(),a.length());
    });
}
void MainWindow::draw(){
    draw_main_toolbar();
    draw_log_window();
    sub_window_->draw();

}

void MainWindow::draw_main_toolbar() {
    ImGuiIO& io = ImGui::GetIO();

    ImGuiWindowFlags toolbar_flags = ImGuiWindowFlags_NoResize |
                                     ImGuiWindowFlags_NoMove |
                                     ImGuiWindowFlags_NoCollapse |
                                     ImGuiWindowFlags_NoScrollbar |
                                     ImGuiWindowFlags_NoSavedSettings;

    float toolbar_height = io.DisplaySize.y;

    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - conf::toolbar_width, 0));
    ImGui::SetNextWindowSize(ImVec2(conf::toolbar_width, toolbar_height));

    ImGui::Begin("Tools", nullptr, toolbar_flags);

    if (ImGui::Button("ArpSpoof", ImVec2(conf::toolbar_width-16, conf::toolbar_button_height)))
    {
        sub_window_=arp_spoof_window;
    }

    if (ImGui::Button("ArpPoisoningDetection", ImVec2(conf::toolbar_width-16, conf::toolbar_button_height)))
    {
        sub_window_=arp_poison_detection_window;
    }
    if (ImGui::Button("SendArpRequest", ImVec2(conf::toolbar_width-16, conf::toolbar_button_height)))
    {
        sub_window_=send_arp_request_window;
    }
    if (ImGui::Button("VlanHopping", ImVec2(conf::toolbar_width-16, conf::toolbar_button_height)))
    {
        sub_window_=vlan_hopping_window;
    }
    if (ImGui::Button("MITMPacketForwarding", ImVec2(conf::toolbar_width-16, conf::toolbar_button_height)))
    {
        sub_window_=man_in_the_middle_window;
    }
    if (ImGui::Button("WIFIAttackWindow", ImVec2(conf::toolbar_width-16, conf::toolbar_button_height)))
    {
        sub_window_=wifi_attack_window;
    }
    ImGui::End();
}

void MainWindow::draw_log_window() {
    ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0, 0, 0, 255));
    ImGuiIO& io = ImGui::GetIO();
    ImGuiWindowFlags log_window_flags =
                                     ImGuiWindowFlags_NoMove |
                                     ImGuiWindowFlags_NoSavedSettings;
    static float log_window_h=conf::log_window_height;
    ImGui::SetNextWindowSizeConstraints(
            ImVec2(io.DisplaySize.x - conf::toolbar_width, 100),    // min size (width, height)
            ImVec2(io.DisplaySize.x - conf::toolbar_width, FLT_MAX) // max size (fixed width, unlimited height)
    );
    ImGui::SetNextWindowSize(ImVec2(0,log_window_h), ImGuiCond_FirstUseEver);
    if(!ImGui::Begin("Log", nullptr, log_window_flags)){
        ImGui::SetWindowPos(ImVec2(0,io.DisplaySize.y));
    } else{
        ImGui::SetWindowPos(ImVec2(0,io.DisplaySize.y-log_window_h));
    }


    log_window_h=ImGui::GetWindowHeight();


    ImGui::TextUnformatted(log_buffer_);

    bool auto_scroll = false;
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 1.0f)
        auto_scroll = true;
    if (auto_scroll)
        ImGui::SetScrollHereY(1.0f);

    ImGui::End();
    ImGui::PopStyleColor();
}


