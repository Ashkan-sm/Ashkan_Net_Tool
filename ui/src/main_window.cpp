#include "include/main_window.h"
MainWindow::MainWindow(ModelInterface *core) :core_(core){
    default_window=std::make_shared<DefaultWindow>(core_);
    arp_spoof_window=std::make_shared<ArpSpoofWindow>(core_);


    sub_window_=default_window;
}
void MainWindow::draw(){

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
                                    ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoBringToFrontOnFocus |
                                    ImGuiWindowFlags_NoNavFocus ;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    ImGui::Begin("Fullscreen Window", nullptr, window_flags);
    ImGui::Text("This window fills the entire screen");
    ImGui::End();

    draw_main_toolbar();
    sub_window_->draw();
}

void MainWindow::draw_main_toolbar() {
    ImGuiIO& io = ImGui::GetIO();

    ImGuiWindowFlags toolbar_flags = ImGuiWindowFlags_NoTitleBar |
                                     ImGuiWindowFlags_NoResize |
                                     ImGuiWindowFlags_NoMove |
                                     ImGuiWindowFlags_NoCollapse |
                                     ImGuiWindowFlags_NoScrollbar |
                                     ImGuiWindowFlags_NoSavedSettings;

    float toolbar_height = io.DisplaySize.y;

    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - conf::toolbar_width, 0));
    ImGui::SetNextWindowSize(ImVec2(conf::toolbar_width, toolbar_height));

    ImGui::Begin("VerticalToolbar", nullptr, toolbar_flags);

    if (ImGui::Button("ArpSpoof", ImVec2(conf::toolbar_width-16, conf::toolbar_button_height)))
    {
        sub_window_=arp_spoof_window;
    }

    if (ImGui::Button("ArpPoisoningDetection", ImVec2(conf::toolbar_width-16, conf::toolbar_button_height)))
    {

    }


    ImGui::End();
}


