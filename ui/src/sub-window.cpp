//
// Created by dev on 6/4/25.
//

#include "sub-window.hpp"
ISubWindow::ISubWindow(ashk::ModelInterface *core) :core_(core){

}

void ISubWindow::draw_base(const std::string &name) {
    ImVec2 avail(ImGui::GetMainViewport()->Size.x-ImGui::FindWindowByName("Tools")->Size.x,ImGui::GetMainViewport()->Size.y-ImGui::FindWindowByName("Log")->Size.y);
    static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize |
                                           ImGuiWindowFlags_NoMove |
                                           ImGuiWindowFlags_NoCollapse |
                                           ImGuiWindowFlags_NoNavFocus ;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(avail);

    ImGui::Begin(name.c_str(), nullptr, window_flags);
}

ArpSpoofWindow::ArpSpoofWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}
void ArpSpoofWindow::draw() {
    draw_base("ArpSpoofingWindow");
    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;

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

    ImGui::NewLine();if (ImGui::Button("start poisoning")){core_->start_arp_poison(interface_ip,victim_src_ip,victim_dst_ip,forward_to_ip);}


    for(auto i:core_->get_running_tasks()) {
        if (ImGui::Button(("kill thread " + std::to_string(i)).c_str())) {
            core_->end_task(i);
        }
    }
    ImGui::End();
}


DefaultWindow::DefaultWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}
void DefaultWindow::draw() {
}


void ArpPoisonDetectionWindow::draw() {
    draw_base("ArpPoisonDetectionWindow");

    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;
    static char interface_ip[16] = "";
    ImGui::InputTextWithHint("interface(ip)", "0.0.0.0", interface_ip, IM_ARRAYSIZE(interface_ip),input_text_ip_flag);
    ImGui::SameLine(); if (ImGui::Button("discover")){
        std::string ip=core_->get_interface_ip();
        std::memcpy(interface_ip,ip.c_str(),ip.size());
    }


    ImGui::NewLine();if (ImGui::Button("start detection")){core_->start_arp_poison_detection(interface_ip);}


    for(auto i:core_->get_running_tasks()) {
        if (ImGui::Button(("kill thread " + std::to_string(i)).c_str())) {
            core_->end_task(i);
        }
    }

    ImGui::End();
}

ArpPoisonDetectionWindow::ArpPoisonDetectionWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}

SendArpRequestWindow::SendArpRequestWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}

void SendArpRequestWindow::draw() {
    draw_base("SendArpRequestWindow");

    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;
    static char interface_ip[16] = "";
    ImGui::InputTextWithHint("interface(ip)", "0.0.0.0", interface_ip, IM_ARRAYSIZE(interface_ip),input_text_ip_flag);
    ImGui::SameLine(); if (ImGui::Button("discover")){
        std::string ip=core_->get_interface_ip();
        std::memcpy(interface_ip,ip.c_str(),ip.size());
    }
    static char dst_ip[16] = "";
    ImGui::InputTextWithHint("arp(ip)", "0.0.0.0", dst_ip, IM_ARRAYSIZE(interface_ip),input_text_ip_flag);
    ImGui::NewLine();if (ImGui::Button("send")){core_->send_arp_req(interface_ip,dst_ip);}

    for(auto i:core_->get_running_tasks()) {
        if (ImGui::Button(("kill thread " + std::to_string(i)).c_str())) {
            core_->end_task(i);
        }
    }

    ImGui::End();
}

VlanHoppingWindow::VlanHoppingWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}

void VlanHoppingWindow::draw() {
    draw_base("VlanHoppingWindow");

    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;

    static char interface_ip[16] = "";
    ImGui::InputTextWithHint("interface(ip)", "0.0.0.0", interface_ip, IM_ARRAYSIZE(interface_ip),input_text_ip_flag);
    ImGui::SameLine(); if (ImGui::Button("discover")){
        std::string ip=core_->get_interface_ip();
        std::memcpy(interface_ip,ip.c_str(),ip.size());
    }

    ImGui::NewLine();
    ImGui::Text("Double_Tagging");
    static char outer_tag[16] = "";
    static char inner_tag[16] = "";
    ImGui::InputTextWithHint("outer_tag", "0", outer_tag, IM_ARRAYSIZE(interface_ip),input_text_ip_flag);
    ImGui::InputTextWithHint("inner_tag", "0", inner_tag, IM_ARRAYSIZE(interface_ip),input_text_ip_flag);
    if (ImGui::Button("Start Hopping")){core_->start_vlan_hopping(interface_ip,outer_tag,inner_tag);}

    ImGui::NewLine();
    ImGui::Text("DTP_Negotiation");
    static char domain_name[32] = "";
    ImGui::InputTextWithHint("domain_name", "name", domain_name, 32);
    ImGui::SameLine(); if (ImGui::Button("extract")){}
    if (ImGui::Button("Start Negotiation")){core_->start_dtp_negotiation(interface_ip,domain_name);}

    ImGui::NewLine();for(auto i:core_->get_running_tasks()) {
        if (ImGui::Button(("kill thread " + std::to_string(i)).c_str())) {
            core_->end_task(i);
        }
    }

    ImGui::End();
}

MITMWindow::MITMWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}

void MITMWindow::draw() {
    draw_base("ManInTheMiddleWindow");
    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;

    static char interface_ip[16] = "";
    ImGui::InputTextWithHint("interface(ip)", "0.0.0.0", interface_ip, IM_ARRAYSIZE(interface_ip),input_text_ip_flag);
    ImGui::SameLine(); if (ImGui::Button("discover")){
        std::string ip=core_->get_interface_ip();
        std::memcpy(interface_ip,ip.c_str(),ip.size());
    }

    static char victim_ip[16] = "";
    ImGui::InputTextWithHint("victim(ip)", "0.0.0.0", victim_ip, IM_ARRAYSIZE(victim_ip),input_text_ip_flag);

    static char gateway_ip[16] = "";
    ImGui::InputTextWithHint("gateway(ip)", "0.0.0.0", gateway_ip, IM_ARRAYSIZE(gateway_ip),input_text_ip_flag);


    ImGui::NewLine();if (ImGui::Button("start forwarding")){core_->start_mitm_forwarding(interface_ip,victim_ip,gateway_ip);}


    for(auto i:core_->get_running_tasks()) {
        if (ImGui::Button(("kill thread " + std::to_string(i)).c_str())) {
            core_->end_task(i);
        }
    }
    ImGui::End();
}
