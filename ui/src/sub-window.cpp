//
// Created by dev on 6/4/25.
//

#include "sub-window.hpp"
ISubWindow::ISubWindow(ashk::ModelInterface *core) :core_(core){

}
pcpp::PcapLiveDevice * ISubWindow::draw_interface_widget(){
    static std::vector<pcpp::PcapLiveDevice *> devices=core_->get_interfaces();
    static int item_selected_idx = 0;
    const std::string &combo_preview_value = devices[item_selected_idx]->getName();
    if(devices.empty()){
        ashk::utils::Logger::getInstance().log("No network device found\n");
    }
    else{
        if (ImGui::BeginCombo("interface",combo_preview_value.c_str()))
        {
            static ImGuiTextFilter filter;
            if (ImGui::IsWindowAppearing())
            {
                ImGui::SetKeyboardFocusHere();
                filter.Clear();
            }
            ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F);
            filter.Draw("##Filter", -FLT_MIN);

            for (int n = 0; n < devices.size(); n++)
            {
                const bool is_selected = (item_selected_idx == n);
                if (filter.PassFilter(devices[n]->getName().c_str()))
                    if (ImGui::Selectable((devices[n]->getName()+" "+devices[n]->getIPv4Address().toString()).c_str(), is_selected))
                        item_selected_idx = n;
            }
            ImGui::EndCombo();
        }
    }
    ImGui::SameLine(); if (ImGui::Button("discover")){
        devices=core_->get_interfaces();
    }
    return devices[item_selected_idx];
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
    pcpp::PcapLiveDevice * device=draw_interface_widget();

    static char victim_src_ip[16] = "";
    ImGui::InputTextWithHint("victim_src(ip)", "0.0.0.0", victim_src_ip, IM_ARRAYSIZE(victim_src_ip),input_text_ip_flag);

    static char victim_dst_ip[16] = "";
    ImGui::InputTextWithHint("victim_dst(ip)", "0.0.0.0", victim_dst_ip, IM_ARRAYSIZE(victim_dst_ip),input_text_ip_flag);

    static char forward_to_ip[16] = "";
    ImGui::InputTextWithHint("forward_to(ip)", "0.0.0.0", forward_to_ip, IM_ARRAYSIZE(forward_to_ip),input_text_ip_flag);

    ImGui::NewLine();if (ImGui::Button("start poisoning")){core_->start_arp_poison(device->getIPv4Address().toString(),victim_src_ip,victim_dst_ip,forward_to_ip);}


    ImGui::End();
}


DefaultWindow::DefaultWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}
void DefaultWindow::draw() {
}


void ArpPoisonDetectionWindow::draw() {
    draw_base("ArpPoisonDetectionWindow");

    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;

    pcpp::PcapLiveDevice * device=draw_interface_widget();


    ImGui::NewLine();if (ImGui::Button("start detection")){core_->start_arp_poison_detection(device->getIPv4Address().toString());}


    ImGui::End();
}

ArpPoisonDetectionWindow::ArpPoisonDetectionWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}

SendArpRequestWindow::SendArpRequestWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}

void SendArpRequestWindow::draw() {
    draw_base("SendArpRequestWindow");

    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;
    pcpp::PcapLiveDevice * device=draw_interface_widget();
    static char dst_ip[16] = "";
    ImGui::InputTextWithHint("arp(ip)", "0.0.0.0", dst_ip, IM_ARRAYSIZE(dst_ip),input_text_ip_flag);
    ImGui::NewLine();if (ImGui::Button("send")){core_->send_arp_req(device->getIPv4Address().toString(),dst_ip);}

    ImGui::End();
}

VlanHoppingWindow::VlanHoppingWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}

void VlanHoppingWindow::draw() {
    draw_base("VlanHoppingWindow");

    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;

    pcpp::PcapLiveDevice * device=draw_interface_widget();

    ImGui::NewLine();
    ImGui::Text("Double_Tagging");
    static char outer_tag[16] = "";
    static char inner_tag[16] = "";
    ImGui::InputTextWithHint("outer_tag", "0", outer_tag, IM_ARRAYSIZE(outer_tag),input_text_ip_flag);
    ImGui::InputTextWithHint("inner_tag", "0", inner_tag, IM_ARRAYSIZE(inner_tag),input_text_ip_flag);
    if (ImGui::Button("Start Hopping")){core_->start_vlan_hopping(device->getIPv4Address().toString(),outer_tag,inner_tag);}

    ImGui::NewLine();
    ImGui::Text("DTP_Negotiation");
    static char domain_name[32] = "";
    ImGui::InputTextWithHint("domain_name", "name", domain_name, 32);
    ImGui::SameLine(); if (ImGui::Button("extract")){core_->start_dtp_domain_extraction(device->getIPv4Address().toString(),domain_name);}
    if (ImGui::Button("Start Negotiation")){core_->start_dtp_negotiation(device->getIPv4Address().toString(),domain_name);}


    ImGui::End();
}

MITMWindow::MITMWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}

void MITMWindow::draw() {
    draw_base("ManInTheMiddleWindow");
    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;

    pcpp::PcapLiveDevice * device=draw_interface_widget();
    static char victim_ip[17] = "";
    ImGui::InputTextWithHint("victim(ip)", "0.0.0.0", victim_ip, IM_ARRAYSIZE(victim_ip));

    static char gateway_ip[17] = "";
    ImGui::InputTextWithHint("gateway(ip)", "0.0.0.0", gateway_ip, IM_ARRAYSIZE(gateway_ip));

    static char victim_mac[18] = "";
    ImGui::InputTextWithHint("victim(mac)", "00:00:00:00:00:00", victim_mac, IM_ARRAYSIZE(victim_mac));

    static char gateway_mac[18] = "";
    ImGui::InputTextWithHint("gateway(mac)", "00:00:00:00:00:00", gateway_mac, IM_ARRAYSIZE(gateway_mac));

    static char task_id[2] = "";
    ImGui::InputTextWithHint("task id", "0", task_id, IM_ARRAYSIZE(task_id),input_text_ip_flag);
    ImGui::SameLine(); if (ImGui::Button("get_data from arpSpoofing")){
        std::string vic_mac_str=core_->get_task_data(task_id,ashk::tasks_data_id::VICTIM_SRC_MAC);
        std::string gate_mac_str=core_->get_task_data(task_id,ashk::tasks_data_id::VICTIM_DST_MAC);
        std::memcpy(victim_mac,vic_mac_str.c_str(),vic_mac_str.size());
        std::memcpy(gateway_mac,gate_mac_str.c_str(),gate_mac_str.size());
    }

    ImGui::NewLine();if (ImGui::Button("start forwarding")){core_->start_mitm_forwarding(device->getIPv4Address().toString(),victim_ip,gateway_ip,victim_mac,gateway_mac);}


    ImGui::End();
}

WIFIAttackWindow::WIFIAttackWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}

void WIFIAttackWindow::draw() {
    draw_base("WIFIAttackWindow");
    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;

    pcpp::PcapLiveDevice * device=draw_interface_widget();

    static std::vector<WifiAp> ap_list;
    if (ImGui::Button("detect networks")){core_->start_detecting_wifi_aps(device->getName(),ap_list);}

    static auto selectedAp=new WifiAp("None");
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
//    window_flags |= ImGuiWindowFlags_MenuBar;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("ApListChildWindow", ImVec2(0, 180), ImGuiChildFlags_Borders, window_flags);

    for(auto &i :ap_list){
        if (ImGui::Button((" "+i.e_ssid).c_str())) {
            selectedAp=&i;
        }
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();


    ImGui::Text("selected access point: %s", selectedAp->e_ssid.c_str());


    static std::vector<std::shared_ptr<WifiHost>> host_list{std::make_unique<WifiHost>(pcpp::MacAddress::Broadcast)};
    if (ImGui::Button("detect hosts")){
        core_->start_detecting_wifi_hosts(device->getName(),host_list);
    }
    ImGui::SameLine();
    if(ImGui::Button("Select All")){
        for(auto &i:host_list){
            i->is_selected= true;
        }
    };

    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("ApHostsChildWindow", ImVec2(0, 180), ImGuiChildFlags_Borders, window_flags);

    for(auto &i :host_list){
        ImGui::Checkbox(i->mac.toString().c_str(),&i->is_selected);
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();

    if (ImGui::Button("Start Deauthentication")){
        core_->start_sending_deauth_packets(device->getName(),selectedAp,host_list);
    }
    ImGui::End();
}
