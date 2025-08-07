//
// Created by dev on 6/4/25.
//

#include "sub-window.hpp"
ISubWindow::ISubWindow(ashk::ModelInterface *core) :core_(core){

}
pcpp::PcapLiveDevice * ISubWindow::DrawInterfaceWidget(){
    static std::vector<pcpp::PcapLiveDevice *> devices= core_->GetInterfaces();
    static int item_selected_idx = 0;
    const std::string &combo_preview_value = devices[item_selected_idx]->getName();
    if(devices.empty()){
      ashk::utils::Logger::getInstance().Log("No network device found\n");
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
        devices= core_->GetInterfaces();
    }
    return devices[item_selected_idx];
}
void ISubWindow::DrawBase(const std::string &name) {
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
void ArpSpoofWindow::Draw() {
  DrawBase("ArpSpoofingWindow");
    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;
    pcpp::PcapLiveDevice * device= DrawInterfaceWidget();

    static char victim_src_ip[16] = "";
    ImGui::InputTextWithHint("victim_src(ip)", "0.0.0.0", victim_src_ip, IM_ARRAYSIZE(victim_src_ip),input_text_ip_flag);

    static char victim_dst_ip[16] = "";
    ImGui::InputTextWithHint("victim_dst(ip)", "0.0.0.0", victim_dst_ip, IM_ARRAYSIZE(victim_dst_ip),input_text_ip_flag);

    static char forward_to_ip[16] = "";
    ImGui::InputTextWithHint("forward_to(ip)", "0.0.0.0", forward_to_ip, IM_ARRAYSIZE(forward_to_ip),input_text_ip_flag);

    ImGui::NewLine();if (ImGui::Button("start poisoning")){
    core_->StartArpPoison(device->getIPv4Address().toString(),
                          victim_src_ip,
                          victim_dst_ip,
                          forward_to_ip);}


    ImGui::End();
}


DefaultWindow::DefaultWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}
void DefaultWindow::Draw() {
}


void ArpPoisonDetectionWindow::Draw() {
  DrawBase("ArpPoisonDetectionWindow");

    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;

    pcpp::PcapLiveDevice * device= DrawInterfaceWidget();


    ImGui::NewLine();if (ImGui::Button("start detection")){ core_->StartArpPoisonDetection(device->getIPv4Address().toString());}


    ImGui::End();
}

ArpPoisonDetectionWindow::ArpPoisonDetectionWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}

SendArpRequestWindow::SendArpRequestWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}

void SendArpRequestWindow::Draw() {
  DrawBase("SendArpRequestWindow");

    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;
    pcpp::PcapLiveDevice * device= DrawInterfaceWidget();
    static char dst_ip[16] = "";
    ImGui::InputTextWithHint("arp(ip)", "0.0.0.0", dst_ip, IM_ARRAYSIZE(dst_ip),input_text_ip_flag);
    ImGui::NewLine();if (ImGui::Button("send")){ core_->SendArpReq(device->getIPv4Address().toString(), dst_ip);}

    ImGui::End();
}

VlanHoppingWindow::VlanHoppingWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}

void VlanHoppingWindow::Draw() {
  DrawBase("VlanHoppingWindow");

    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;

    pcpp::PcapLiveDevice * device= DrawInterfaceWidget();

    ImGui::NewLine();
    ImGui::Text("Double_Tagging");
    static char outer_tag[16] = "";
    static char inner_tag[16] = "";
    ImGui::InputTextWithHint("outer_tag", "0", outer_tag, IM_ARRAYSIZE(outer_tag),input_text_ip_flag);
    ImGui::InputTextWithHint("inner_tag", "0", inner_tag, IM_ARRAYSIZE(inner_tag),input_text_ip_flag);
    if (ImGui::Button("Start Hopping")){
      core_->StartVlanHopping(device->getIPv4Address().toString(),
                              outer_tag,
                              inner_tag);}

    ImGui::NewLine();
    ImGui::Text("DTP_Negotiation");
    static char domain_name[32] = "";
    ImGui::InputTextWithHint("domain_name", "name", domain_name, 32);
    ImGui::SameLine(); if (ImGui::Button("extract")){
    core_->StartDtpDomainExtraction(device->getIPv4Address().toString(),
                                    domain_name);}
    if (ImGui::Button("Start Negotiation")){
      core_->StartDtpNegotiation(device->getIPv4Address().toString(),
                                 domain_name);}


    ImGui::End();
}

MITMWindow::MITMWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}

void MITMWindow::Draw() {
  DrawBase("ManInTheMiddleWindow");
    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;

    pcpp::PcapLiveDevice * device= DrawInterfaceWidget();
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
    ImGui::SameLine(); if (ImGui::Button("GetData from arpSpoofing")){
        std::string vic_mac_str= core_->GetTaskData(task_id, ashk::tasks_data_id::VICTIM_SRC_MAC);
        std::string gate_mac_str= core_->GetTaskData(task_id, ashk::tasks_data_id::VICTIM_DST_MAC);
        std::memcpy(victim_mac,vic_mac_str.c_str(),vic_mac_str.size());
        std::memcpy(gateway_mac,gate_mac_str.c_str(),gate_mac_str.size());
    }

    ImGui::NewLine();if (ImGui::Button("start forwarding")){
    core_->StartMitmForwarding(device->getIPv4Address().toString(),
                               victim_ip,
                               gateway_ip,
                               victim_mac,
                               gateway_mac);}


    ImGui::End();
}

WIFIAttackWindow::WIFIAttackWindow(ashk::ModelInterface *core) : ISubWindow(core) {

}

void WIFIAttackWindow::Draw() {
  DrawBase("WIFIAttackWindow");
    static ImGuiInputTextFlags input_text_ip_flag = ImGuiInputTextFlags_CharsDecimal;

    pcpp::PcapLiveDevice * device= DrawInterfaceWidget();

    static std::vector<WifiAp> ap_list;
    if (ImGui::Button("detect networks")){ core_->StartDetectingWifiAps(device->getName(), ap_list);}

    static auto selectedAp=new WifiAp("None");
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
//    window_flags |= ImGuiWindowFlags_MenuBar;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("ApListChildWindow", ImVec2(0, 180), ImGuiChildFlags_Borders, window_flags);

    for(auto &i :ap_list){
        if (ImGui::Button((i.e_ssid+" ("+i.b_ssid.toString()+")").c_str())) {
            selectedAp=&i;
        }
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();


    ImGui::Text("selected access point: %s", selectedAp->e_ssid.c_str());


    static std::vector<std::shared_ptr<WifiHost>> host_list{std::make_unique<WifiHost>(pcpp::MacAddress::Broadcast)};
    if (ImGui::Button("detect hosts")){
      core_->StartDetectingWifiHosts(device->getName(), host_list);
    }
    ImGui::SameLine();
    static bool select_hosts=false;
    ImGui::Checkbox("Select All",&select_hosts);
    if(select_hosts) {
        for (auto &i: host_list) {
            i->is_selected = true;
        }
    }

    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("ApHostsChildWindow", ImVec2(0, 180), ImGuiChildFlags_Borders, window_flags);

    for(auto &i :host_list){
        ImGui::Checkbox(i->mac.toString().c_str(),&i->is_selected);
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();

    if (ImGui::Button("Start Deauthentication")){
      core_->StartSendingDeauthPackets(device->getName(), selectedAp, host_list);
    }
    static std::shared_ptr<HandShakeData> hand_shake_data;
    if (ImGui::Button("Capture WPA2 Handshake")){
        if(selectedAp->e_ssid== "None"){
          ashk::utils::Logger::getInstance().Log("no AP selected\n");
        }
        else {
            hand_shake_data = std::make_unique<HandShakeData>(selectedAp);
          core_->StartWpa2HandshakeCapturing(device->getName(), hand_shake_data);
        }
    }
    if (ImGui::Button("CRACK PASSWORD")){
        if(hand_shake_data && hand_shake_data->got_msg_2){
          core_->StartPasswordCracking(device->getName(), hand_shake_data);
        }
        else{
          ashk::utils::Logger::getInstance().Log("no HandShake data available\n");
        }

    }

    ImGui::End();
}
