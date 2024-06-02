#include "../include/UIPanel.hpp"

UIPanel::UIPanel() {

}

UIPanel::~UIPanel() {
    
}

void UIPanel::render(Scene* scene) {
    // Code for Gui
    //ImGui::ShowDemoWindow();
    ImGui::Begin("Debug", &my_tool_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
            if (ImGui::MenuItem("Close", "Ctrl+W"))  { my_tool_active = false; }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // Edit a color stored as 4 floats
    ImGui::ColorEdit4("Color", color);
    ImGui::End();

    scene->onChangeColor(color);
}