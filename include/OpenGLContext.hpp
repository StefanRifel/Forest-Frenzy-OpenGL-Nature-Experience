#ifndef OPENGLCONTEXT_HH
#define OPENGLCONTEXT_HH

#include "RenderContext.hpp"
#include "Window.hpp"

class OpenGLContext : public RenderContext {
public:
    OpenGLContext();
    ~OpenGLContext();

    virtual bool init(Window* window) override;
    virtual void preRender() override;
    virtual void postRender() override;
};

#endif