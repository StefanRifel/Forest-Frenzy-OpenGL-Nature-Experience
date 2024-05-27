#include "../../include/UIPanel.hpp"

UIPanel::UIPanel() {

}

UIPanel::~UIPanel() {
    
}

void UIPanel::init() {

}

void UIPanel::render(ecs::Coordinator& coordinator) {
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

    float oldColor[4] {0.0f};
    oldColor[0] = color[0];
    oldColor[1] = color[1];
    oldColor[2] = color[2];
    oldColor[3] = color[3];

    // Edit a color stored as 4 floats
    ImGui::ColorEdit4("Color", color);
    
    if(oldColor[0] != color[0]){
        Event e {event::CHANGECOLOR};
        e.setData(e.getType(), color);
        coordinator.sendEvent(e);
    }
    
    

    ImGui::End();
}