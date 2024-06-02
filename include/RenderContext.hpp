#ifndef RENDERCONTEXT_HH
#define RENDERCONTEXT_HH

#include <iostream>

class Window;

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class RenderContext {
public:
    Window* window;
    
    RenderContext() : window {nullptr} {};

    virtual bool init(Window* window) {
        this->window = window;
        return true;
    };

    virtual void preRender() = 0;
    virtual void postRender() = 0;
};

#endif