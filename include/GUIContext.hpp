#ifndef GUICONTEXT_HH
#define GUICONTEXT_HH

#include "RenderContext.hpp"
#include <iostream>
#include "WindowManager.hpp"

#include "../libs/ImGui/imgui.h"
#include "../libs/ImGui/imgui_impl_glfw.h"
#include "../libs/ImGui/imgui_impl_opengl3.h"

class GUIContext : public RenderContext {

public:
    GUIContext();
    ~GUIContext();

    virtual bool init(WindowManager* windowManager) override;
    virtual void preRender() override;
    virtual void postRender() override;
};

#endif