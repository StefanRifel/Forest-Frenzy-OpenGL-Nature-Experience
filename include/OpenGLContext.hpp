#ifndef OPENGLCONTEXT_HH
#define OPENGLCONTEXT_HH

#include "RenderContext.hpp"
#include "WindowManager.hpp"

class OpenGLContext : public RenderContext {
public:
    OpenGLContext();
    ~OpenGLContext();

    virtual bool init(WindowManager* windowManager) override;
    virtual void preRender() override;
    virtual void postRender() override;
};

#endif