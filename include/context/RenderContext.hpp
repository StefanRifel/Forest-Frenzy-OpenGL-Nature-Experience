#ifndef RENDER_CONTEXT_HH
#define RENDER_CONTEXT_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window;

/**
 * @brief The RenderContext class provides an abstract base for managing rendering context operations.
 */
class RenderContext {
public:
    Window* pWindow;
    
    RenderContext() : pWindow {nullptr} {};

    virtual bool init(Window* window) {
        this->pWindow = window;
        return true;
    };

    virtual void preRender() = 0;
    virtual void postRender() = 0;
};

#endif