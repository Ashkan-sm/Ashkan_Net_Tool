//
// Created by dev on 6/4/25.
//

#include "include/sub_window.h"
ISubWindow::ISubWindow(ModelInterface *core) :core_(core){

}

ArpSpoofWindow::ArpSpoofWindow(ModelInterface *core) : ISubWindow(core) {

}
void ArpSpoofWindow::draw() {
    static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoNavFocus ;
    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x - conf::toolbar_width, ImGui::GetIO().DisplaySize.y));

    ImGui::Begin("ArpSpoofWindow", nullptr, window_flags);



    static char interface_ip[16] = "";
    ImGui::InputTextWithHint("interface(ip)", "0.0.0.0", interface_ip, IM_ARRAYSIZE(interface_ip),input_text_ip_flag);
    ImGui::SameLine(); if (ImGui::Button("discover")){
        std::string ip=core_->get_interface_ip();
        std::memcpy(interface_ip,ip.c_str(),ip.size());
    }

    static char victim_src_ip[16] = "";
    ImGui::InputTextWithHint("victim_src(ip)", "0.0.0.0", victim_src_ip, IM_ARRAYSIZE(victim_src_ip),input_text_ip_flag);

    static char victim_dst_ip[16] = "";
    ImGui::InputTextWithHint("victim_dst(ip)", "0.0.0.0", victim_dst_ip, IM_ARRAYSIZE(victim_dst_ip),input_text_ip_flag);

    static char forward_to_ip[16] = "";
    ImGui::InputTextWithHint("forward_to(ip)", "0.0.0.0", forward_to_ip, IM_ARRAYSIZE(forward_to_ip),input_text_ip_flag);

    ImGui::NewLine();if (ImGui::Button("start poisoning")){}
    ImGui::End();
}


DefaultWindow::DefaultWindow(ModelInterface *core) : ISubWindow(core) {

}
void DefaultWindow::draw() {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoNavFocus ;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x - conf::toolbar_width, ImGui::GetIO().DisplaySize.y));

    ImGui::Begin("default window", nullptr, window_flags);
    ImGui::Text("This subwindow fills the entire screen");
    ImGui::End();
}



