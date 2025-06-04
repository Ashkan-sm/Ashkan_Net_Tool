#include "main_window.h"
void MainWindow::main_window(){

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

    main_toolbar();


}

void MainWindow::main_toolbar() {
    ImGuiIO& io = ImGui::GetIO();

    ImGuiWindowFlags toolbar_flags = ImGuiWindowFlags_NoTitleBar |
                                     ImGuiWindowFlags_NoResize |
                                     ImGuiWindowFlags_NoMove |
                                     ImGuiWindowFlags_NoCollapse |
                                     ImGuiWindowFlags_NoScrollbar |
                                     ImGuiWindowFlags_NoSavedSettings;

    float toolbar_height = io.DisplaySize.y;

    // Position toolbar on the left edge
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - conf::toolbar_width, 0));
    ImGui::SetNextWindowSize(ImVec2(conf::toolbar_width, toolbar_height));

    ImGui::Begin("VerticalToolbar", nullptr, toolbar_flags);
    if (ImGui::Button("arpSpoof", ImVec2(conf::toolbar_width-16, conf::toolbar_button_height)))
    {
        // Handle New
    }

    if (ImGui::Button("ArpPoiseningDetection", ImVec2(conf::toolbar_width-16, conf::toolbar_button_height)))
    {
        // Handle Open
    }


    // Add more buttons or icons here

    ImGui::End();
}
