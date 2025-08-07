#include "main-window.hpp"
MainWindow::MainWindow(ashk::ModelInterface *core) :core_(core){
//    std::memcpy(log_buffer_,0,sizeof(log_buffer_));
    ImGuiIO& io = ImGui::GetIO();


  default_window_=std::make_shared<DefaultWindow>(core_);
  arp_spoof_window_=std::make_shared<ArpSpoofWindow>(core_);
  arp_poison_detection_window_=std::make_shared<ArpPoisonDetectionWindow>(core_);
  send_arp_request_window_=std::make_shared<SendArpRequestWindow>(core_);
  vlan_hopping_window_=std::make_shared<VlanHoppingWindow>(core_);
  man_in_the_middle_window_=std::make_shared<MITMWindow>(core_);
  wifi_attack_window_=std::make_shared<WIFIAttackWindow>(core_);

    sub_window_=default_window_;

  core_->AddLoggerMethod([&](const std::string &a) {
    if (strlen(log_buffer_) + strlen(log_buffer_) >= sizeof(log_buffer_)) {
      memset(log_buffer_, '\0', sizeof(log_buffer_));
    }
    memcpy(log_buffer_ + strlen(log_buffer_), a.c_str(), a.length());
  });
}
void MainWindow::Draw(){
  DrawMainToolbar();
  DrawLogWindow();
  sub_window_->Draw();

}

void MainWindow::DrawMainToolbar() {
    ImGuiIO& io = ImGui::GetIO();

    ImGuiWindowFlags toolbar_flags = ImGuiWindowFlags_NoResize |
                                     ImGuiWindowFlags_NoMove |
                                     ImGuiWindowFlags_NoCollapse |
                                     ImGuiWindowFlags_NoScrollbar |
                                     ImGuiWindowFlags_NoSavedSettings;


    float toolbar_height = io.DisplaySize.y;
    float threads_child_height = 180.0f;
    float top_child_height = toolbar_height - threads_child_height ;

    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - conf::toolbar_width, 0));
    ImGui::SetNextWindowSize(ImVec2(conf::toolbar_width, toolbar_height));
    ImVec2 old_padding = ImGui::GetStyle().FramePadding;
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, old_padding.y));
    ImGui::Begin("Tools", nullptr, toolbar_flags|
                                   ImGuiWindowFlags_NoScrollWithMouse);
    float padding=30;
    // Top child occupies everything above the bottom child
    ImGui::BeginChild("Tools_Top", ImVec2(conf::toolbar_width, top_child_height-35),toolbar_flags);
// Reduce horizontal padding

    if (ImGui::Button("ArpSpoof", ImVec2(conf::toolbar_width-padding, conf::toolbar_button_height))) {
        sub_window_ = arp_spoof_window_;
    }
    if (ImGui::Button("ArpPoisoningDetection", ImVec2(conf::toolbar_width-padding, conf::toolbar_button_height))) {
        sub_window_ = arp_poison_detection_window_;
    }
    if (ImGui::Button("SendArpRequest", ImVec2(conf::toolbar_width-padding, conf::toolbar_button_height))) {
        sub_window_ = send_arp_request_window_;
    }
    if (ImGui::Button("VlanHopping", ImVec2(conf::toolbar_width -padding, conf::toolbar_button_height))) {
        sub_window_ = vlan_hopping_window_;
    }
    if (ImGui::Button("MITMPacketForwarding", ImVec2(conf::toolbar_width -padding, conf::toolbar_button_height))) {
        sub_window_ = man_in_the_middle_window_;
    }
    if (ImGui::Button("WIFIAttackWindow", ImVec2(conf::toolbar_width-padding , conf::toolbar_button_height))) {
        sub_window_ = wifi_attack_window_;
    }
    ImGui::PopStyleVar();

    ImGui::EndChild();

    // Move to the bottom of the main window to draw the Threads panel
    ImGui::SetCursorPosY(toolbar_height - threads_child_height);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("Threads", ImVec2(0, threads_child_height), ImGuiChildFlags_Borders, window_flags);
    for (auto i : core_->GetRunningTasks()) {
        if (ImGui::Button(("kill thread " + std::to_string(i)).c_str())) {
          core_->EndTask(i);
        }
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();

    ImGui::End();
}


void MainWindow::DrawLogWindow() {
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


