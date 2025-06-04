//
// Created by dev on 6/4/25.
//

#include "sub_window.h"

void ArpSpoofWindow::draw() {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
                                    ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoBringToFrontOnFocus |
                                    ImGuiWindowFlags_NoNavFocus ;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x - conf::toolbar_width, ImGui::GetIO().DisplaySize.y));

    ImGui::Begin("Fullscreen Window", nullptr, window_flags);
    ImGui::Text("This window fills the entire screen");
    ImGui::End();

}
