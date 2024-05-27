#ifndef RENDERCONTEXT_HH
#define RENDERCONTEXT_HH

#include <iostream>

class WindowManager;

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class RenderContext {
public:
    WindowManager* windowManager;
    
    RenderContext() : windowManager {nullptr} {};

    virtual bool init(WindowManager* windowManager) {
        this->windowManager = windowManager;
        return true;
    };

    virtual void preRender() = 0;
    virtual void postRender() = 0;
};

#endif