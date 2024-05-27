#include "../include/GUIContext.hpp"

GUIContext::GUIContext() {}

GUIContext::~GUIContext() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

bool GUIContext::init(WindowManager* windowManager) {
    // call parent class init
    if(!RenderContext::init(windowManager)) {
        std::cerr << "ERROR::OPENGLCONTEXT::FAILED_TO_INIT_RENDERCONTEXT" << std::endl;
        return false;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(windowManager->window, true);
    ImGui_ImplOpenGL3_Init();

    return true;
}

void GUIContext::preRender() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUIContext::postRender() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}