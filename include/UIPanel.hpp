#ifndef UIPANEL_HH
#define UIPANEL_HH

#include "../libs/ImGui/imgui.h"
#include "../libs/ImGui/imgui_impl_glfw.h"
#include "../libs/ImGui/imgui_impl_opengl3.h"

#include "Scene.hpp"

class UIPanel {
private:
    
public:
    bool my_tool_active;
    float color[4] = {0.0f};
    UIPanel(/* args */);
    ~UIPanel();

    void render(Scene* scene);
};

#endif